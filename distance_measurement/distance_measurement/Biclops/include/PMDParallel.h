#ifndef PMDParallel_h
#define	PMDParallel_h

//  PMDParallel.h -- (Adapted from PMDpar.h) parallel IO
//
//  TRACLabs -- A division of Metrica, Inc.
//
#include "PMDIOTransport.h"

#ifdef WIN32
#include <conio.h> // needed for definition of _outpw,_inpw,_inp,_outp
#endif

class PMDParallel : public PMDIOTransport {

public:
    enum {PMDParallelIOMode_16_16=0, PMDParallelIOMode_8_16, PMDParallelIOMode_8_8};
    PMDParallel(int IOMode);

    bool Open() {return true;};
    void Close() {};

    // Implementation of superclass pure virtual functions
    PMDuint16 SendCommand(PMDuint8 xCt, PMDuint16* xDat, PMDuint8 rCt, PMDuint16* rDat);
    PMDuint16 ReceiveResponse(PMDuint16 length, PMDuint16 buffer[]);
    PMDuint16 GetStatus(){ return InPStatus(mStatusPort);};
    bool IsReady() { return ((InPStatus(mStatusPort) & mReadyMask) == mReadyValue);};
    bool HasInterrupt() { return ((InPStatus(mStatusPort) & mHostInterruptMask) == mHostInterruptValue);};
    bool HasError() { return ((InPStatus(mStatusPort) & mCommandStatusMask) == mCommandStatusValue);};

private:
    PMDuint16 WaitForReady();
    PMDuint16 GetCommandStatus();
#ifdef WIN32
    static void OutP16Bit(PMDuint16 port, PMDuint16 dataword) {_outpw(port, dataword);};
    static PMDuint16 InP16Bit(PMDuint16 port) {return _inpw(port);};
    static void OutP8Bit(PMDuint16 port, PMDuint16 dataword) {
	    _outp(port, (PMDuint8)(dataword>>8)&0xFF);
	    _outp(port, (PMDuint8)dataword&0xFF);
    };
    static PMDuint16 InP8Bit(PMDuint16 port) {return (PMDuint16) (((_inp(port) & 0xFF) << 8) | (_inp(port) & 0xFF));};
    static void OutP8BitCmd(PMDuint16 port, PMDuint16 dataword) {_outp(port, (PMDuint8)dataword&0xFF);};
    static PMDuint16 InP8BitStatus(PMDuint16 port) {return (PMDuint16)(_inp(port) & 0xFF);};
#else
    static void OutP16Bit(PMDuint16 port, PMDuint16 dataword) {;};
    static PMDuint16 InP16Bit(PMDuint16 port) {return (PMDuint16) 123;};
    static void OutP8Bit(PMDuint16 port, PMDuint16 dataword) {;};
    static PMDuint16 InP8Bit(PMDuint16 port) {return (PMDuint16) 123;};
    static void OutP8BitCmd(PMDuint16 port, PMDuint16 dataword) {;};
    static PMDuint16 InP8BitStatus(PMDuint16 port) {return (PMDuint16) 123;};
#endif

    // Member variables
	PMDuint16 mDataPort;
	PMDuint16 mCommandPort;
	PMDuint16 mStatusPort;

	PMDuint16 mReadyMask;
	PMDuint16 mReadyValue;
	PMDuint16 mHostInterruptMask;
	PMDuint16 mHostInterruptValue;
	PMDuint16 mCommandStatusMask;
	PMDuint16 mCommandStatusValue;

	PMDuint16 mVerifyChecksum;
	PMDuint16 mDiagnostics;

	void (*OutPData)(PMDuint16 port, PMDuint16 dataword);
	void (*OutPCmd)(PMDuint16 port, PMDuint16 dataword);
	PMDuint16 (*InPData)(PMDuint16 port);
	PMDuint16 (*InPStatus)(PMDuint16 port);

};
#endif
