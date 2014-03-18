//  PMDParallel.h -- (Adapted from PMDpar.h) parallel IO
//
//  TRACLabs -- A division of Metrica, Inc.
//
//  Description: parallel interface command/data transfer functions for the MC2xxx
//

#include <cstdio>
#include <stdio.h>

#define __TIME_WAITFORREADY
#ifdef __TIME_WAITFORREADY
#include <sys/timeb.h>
#endif // ! __TIME_WAITFORREADY

#include "../include/PMDTypes.h"
#include "../include/PMDOPCodes.h"
#include "../include/PMDErrorCodes.h"
#include "../include/PMDParallel.h"

// only include this if we are running in diagnostics mode
//#include "PMDDiagnostics.h"

//#define PMDBASE 0x370
PMDParallel::PMDParallel(int IOMode) {
	// assign default values
    const PMDuint16 PMDBASE = 0x370;
	mDataPort = PMDBASE;
	mCommandPort = (PMDuint16)((long)PMDBASE+2);
	mStatusPort = (PMDuint16)((long)PMDBASE+2);

	mReadyMask = 0x8000;
	mReadyValue = 0x8000;
	mHostInterruptMask = 0x4000;
	mHostInterruptValue = 0x4000;
	mCommandStatusMask = 0x2000;
	mCommandStatusValue = 0x2000;

	// by default always verify the checksum
	mVerifyChecksum = 1;
	// by default disable diagnostics
	mDiagnostics = 0;

	// assign default handlers/masks according to IO mode
	switch (IOMode) {
	case PMDParallelIOMode_16_16:
		OutPData = OutP16Bit;
		OutPCmd = OutP16Bit;
		InPData = InP16Bit;
		InPStatus = InP16Bit;
		break;
	case PMDParallelIOMode_8_16:
		OutPData = OutP8Bit;
		OutPCmd = OutP8Bit;
		InPData = InP8Bit;
		InPStatus = InP8Bit;
		break;
	case PMDParallelIOMode_8_8:
		OutPData = OutP8Bit;
		OutPCmd = OutP8BitCmd;
		InPData = InP8Bit;
		InPStatus = InP8BitStatus;
		mReadyMask = 0x80;
		mReadyValue = 0x80;
		mHostInterruptMask = 0x40;
		mHostInterruptValue = 0x40;
		mCommandStatusMask = 0x20;
		mCommandStatusValue = 0x20;
		break;
	}
    SetTransportType (PARALLEL);
}

// send the command and data to the DK2000
PMDuint16 PMDParallel::SendCommand(PMDuint8 xCt, PMDuint16* xDat, PMDuint8 rCt, PMDuint16* rDat) {
    PMDuint16 result;
    PMDuint16 index;
    long messageChecksum=0;
    PMDuint16 chipsetChecksum=0;

    result = PMD_ERR_DK2000NotInitialized;
    if((result = WaitForReady()) == PMD_ERR_OK) {
        // put the command into the DK2000
        OutPCmd(mCommandPort, xDat[0]);

        // put the data into the DK2000
        // one word at a time
        for(index=1; index<xCt; index++) {
            if((result = WaitForReady()) != PMD_ERR_OK) break;
            OutPData(mDataPort,xDat[index]);
        }
        // get the status
        if(result == PMD_ERR_OK) result = GetCommandStatus();
    }
/*	if ((result!=PMD_ERR_OK) && mDiagnostics) {
		printf("C-Motion: %s ",PMDOpcodeText[xDat[0]&0xff].text);
		for(index=0; index<xCt; index++)
			printf("%X ",xDat[index]);
		printf("\n");
	}
*/
    // get the data from the DK2000
    for(index=0; index<rCt; index++) {
        if((result = WaitForReady()) != PMD_ERR_OK) break;
        rDat[index] = InPData(mDataPort);
    }

	if (mVerifyChecksum) {
		for(index=0; index<xCt; index++)
            messageChecksum += xDat[index];
		for(index=0; index<rCt; index++)
            messageChecksum += rDat[index];
		messageChecksum = messageChecksum & 0xFFFF;

		result = ReceiveResponse(1, &chipsetChecksum);

		if ( messageChecksum != chipsetChecksum ) {
			if (mDiagnostics)
				printf("Checksum failure.  expected: %04x,  got: %04x\n",
                       (unsigned int)messageChecksum,chipsetChecksum);
			return PMD_ERR_ChecksumError;
		}
	}

   	return result;
}

// send the command to and get data from the DK2000
PMDuint16 PMDParallel::ReceiveResponse(PMDuint16 length, PMDuint16 buffer[]) {
    PMDuint16 result;
    PMDuint16 index;

    result = PMD_ERR_DK2000NotInitialized;

    // get the data from the DK2000
    for(index=0; index<length; index++) {
        if((result = WaitForReady()) != PMD_ERR_OK) break;
        buffer[index] = InPData(mDataPort);
    }

    return result;
}

// wait for the DB2000 to be ready for the next command
PMDuint16 PMDParallel::WaitForReady() {
	PMDuint16 in_val;
#ifdef __TIME_WAITFORREADY
    struct timeb stopTime, currentTime;
    PMDuint32 milliSeconds, seconds;

    ftime( &stopTime );
    milliSeconds = stopTime.millitm + 1000;
    seconds = milliSeconds/1000;
    stopTime.time += seconds;
    stopTime.millitm = (PMDuint16)(milliSeconds - seconds*1000);
#endif

    for(;;) {
        // poll ready port, if not ready, loop
        in_val = InPStatus(mStatusPort);

        if ((in_val != 0xFFFF) 
			&& ((in_val & mReadyMask) == mReadyValue))
                return PMD_ERR_OK;

#ifdef __TIME_WAITFORREADY
        ftime( &currentTime );

        if((currentTime.time > stopTime.time) || 
           ((currentTime.time == stopTime.time) && (currentTime.millitm > stopTime.millitm))) {
            // recheck the busy flag on last time
            in_val = InP16Bit(mStatusPort);

		    if ((in_val != 0xFFFF) 
				&& ((in_val & mReadyMask) == mReadyValue))
				return PMD_ERR_OK;
            return PMD_ERR_CommTimeoutError;
        }
#endif
    }
}

// wait for the DK2000 to be ready for the next command
PMDuint16 PMDParallel::GetCommandStatus() {
	PMDuint16 result;
	int     in_val;

	if((result = WaitForReady()) != PMD_ERR_OK)
        return result;

	in_val = InPStatus(mStatusPort);
	if ((in_val & mCommandStatusMask) == mCommandStatusValue) {
		if (mDiagnostics)
			printf("C-Motion: Command Error bit set.\n");
		return PMD_ERR_CommandError;
	}

	return PMD_ERR_OK;
}

