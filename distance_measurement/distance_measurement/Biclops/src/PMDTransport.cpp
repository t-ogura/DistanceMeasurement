//  PMDTransport.cpp (adapted from PMDTransp.c) -- generic transport interface
//
//  TRACLabs -- A division of Metrica, Inc.
//

#include "../include/PMDTypes.h"
#include "../include/PMDOPCodes.h"
#include "../include/PMDErrorCodes.h"
#include "../include/PMDTransport.h"
const char classDbgHdr[] = "PMDTransport::"; // For Debugging

PMDTransport::PMDTransport(PMDIOTransport* pmdIOTransport, PMDAxis axis) {
    this->pmdIOTransport = pmdIOTransport;
    this->axis = axis;
    debugLevel = 0;
}

PMDuint16 PMDTransport::SendCommand(PMDuint16 opCode) {
        PMDuint16 buffer[1];

        buffer[0] = BuildCommandWord(opCode,axis);

        return pmdIOTransport->SendCommand(1, buffer, 0, PMDnull);
}


PMDuint16 PMDTransport::SendCommandWord(PMDuint16 opCode, PMDuint16 data1) {
        PMDuint16 buffer[2];

        buffer[0] = BuildCommandWord(opCode,axis);
        buffer[1] = (PMDuint16)data1;

        return pmdIOTransport->SendCommand(2, buffer, 0, PMDnull);
}


PMDuint16 PMDTransport::SendCommandWordWord(PMDuint16 opCode, PMDuint16 data1, PMDuint16 data2) {
        PMDuint16 buffer[3];

        buffer[0] = BuildCommandWord(opCode,axis);
        buffer[1] = (PMDuint16)data1;
        buffer[2] = (PMDuint16)data2;

        return pmdIOTransport->SendCommand(3, buffer, 0, PMDnull);
}

PMDuint16 PMDTransport::SendCommandWordWordWord(PMDuint16 opCode, PMDuint16 data1, PMDuint16 data2, PMDuint16 data3) {
        PMDuint16 buffer[4];

        buffer[0] = BuildCommandWord(opCode,axis);
        buffer[1] = (PMDuint16)data1;
        buffer[2] = (PMDuint16)data2;
        buffer[3] = (PMDuint16)data3;

        return pmdIOTransport->SendCommand(4, buffer, 0, PMDnull);
}

PMDuint16 PMDTransport::SendCommandLong(PMDuint16 opCode, PMDuint32 data1) {
        PMDuint16 buffer[3];
        PMDuint16 *ptr;

        buffer[0] = BuildCommandWord(opCode,axis);
        ptr = (PMDuint16 *)&data1;
        buffer[1]=*(ptr+1); //Write MSW first
        buffer[2]=*ptr;

        return pmdIOTransport->SendCommand(3, buffer, 0, PMDnull);
}

PMDuint16 PMDTransport::SendCommandLongWord(PMDuint16 opCode, PMDuint32 data1, PMDuint16 data2) {
        PMDuint16 buffer[4];
        PMDuint16 *ptr;

        buffer[0] = BuildCommandWord(opCode,axis);
        ptr = (PMDuint16 *)&data1;
        buffer[1]=*(ptr+1); //Write MSW first
        buffer[2]=*ptr;
        buffer[3] = data2;

        return pmdIOTransport->SendCommand(4, buffer, 0, PMDnull);
}

PMDuint16 PMDTransport::SendCommandWordLong(PMDuint16 opCode, PMDuint16 data1, PMDuint32 data2) {
        PMDuint16 buffer[4];
        PMDuint16 *ptr;

        buffer[0] = BuildCommandWord(opCode,axis);
        buffer[1] = data1;
        ptr = (PMDuint16 *)&data2;
        buffer[2]=*(ptr+1); //Write MSW first
        buffer[3]=*ptr;

        return pmdIOTransport->SendCommand(4, buffer, 0, PMDnull);
}


PMDuint16 PMDTransport::SendCommandGetWord(PMDuint16 opCode, PMDuint16 &data1) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[2];

        buffer[0] = BuildCommandWord(opCode,axis);

//        result = pmdIOTransport->SendCommand(1, buffer, 1, buffer+1);
        result = pmdIOTransport->SendCommand(1, buffer, 1, &data1);

//        data1 = (PMDuint16)buffer[1];

        return result;
}

PMDuint16 PMDTransport::SendCommandGetWordWord(PMDuint16 opCode, PMDuint16 &data1, PMDuint16 &data2) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[3];

        buffer[0] = BuildCommandWord(opCode,axis);

        result = pmdIOTransport->SendCommand(1, buffer, 2, buffer+1);

        data1 = (PMDuint16)buffer[1];
        data2 = (PMDuint16)buffer[2];

        return result;
}

PMDuint16 PMDTransport::SendCommandGetWordWordWord(PMDuint16 opCode, PMDuint16 &data1, PMDuint16 &data2, PMDuint16 &data3) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[4];

        buffer[0] = BuildCommandWord(opCode,axis);

        result = pmdIOTransport->SendCommand(1, buffer, 3, buffer+1);

        data1 = (PMDuint16)buffer[1];
        data2 = (PMDuint16)buffer[2];
        data3 = (PMDuint16)buffer[3];

        return result;
}

PMDuint16 PMDTransport::SendCommandGetLong(PMDuint16 opCode, PMDuint32 &data1) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[3];

        buffer[0] = BuildCommandWord(opCode,axis);

        result = pmdIOTransport->SendCommand(1, buffer, 2, buffer+1);

        data1 = ((PMDuint32)buffer[1])<<16 | ((PMDuint32)buffer[2]);

        return result;
}

PMDuint16 PMDTransport::SendCommandGetWordLong(PMDuint16 opCode, PMDuint16 &data1, PMDuint32 &data2) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[4];

        buffer[0] = BuildCommandWord(opCode,axis);

        result = pmdIOTransport->SendCommand(1, buffer, 3, buffer+1);

        data1 = (PMDuint16)buffer[1];
        data2 = ((PMDuint32)buffer[2])<<16 | ((PMDuint32)buffer[3]);

        return result;
}

PMDuint16 PMDTransport::SendCommandWordGetWord(PMDuint16 opCode, PMDuint16 data1, PMDuint16 &data2) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[3];

        buffer[0] = BuildCommandWord(opCode,axis);
        buffer[1] = (PMDuint16)data1;

        result = pmdIOTransport->SendCommand(2, buffer, 1, buffer+2);

        data2 = (PMDuint16)buffer[2];

        return result;
}

PMDuint16 PMDTransport::SendCommandWordGetLong(PMDuint16 opCode, PMDuint16 data1, PMDuint32 &data2) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[4];

        buffer[0] = BuildCommandWord(opCode,axis);
        buffer[1] = (PMDuint16)data1;

        result = pmdIOTransport->SendCommand(2, buffer, 2, buffer+2);

        data2 = ((PMDuint32)buffer[2])<<16 | ((PMDuint32)buffer[3]);

        return result;
}

PMDuint16 PMDTransport::SendCommandLongGetWord(PMDuint16 opCode, PMDuint32 data1, PMDuint16 &data2) {
		PMDuint16 result = PMD_ERR_OK;
		PMDuint16 buffer[4];
        PMDuint16 *ptr;

		buffer[0] = BuildCommandWord(opCode,axis);
        ptr = (PMDuint16 *)&data1;
        buffer[0]=*(ptr+1); //Write MSW first
        buffer[1]=*ptr;

		result = pmdIOTransport->SendCommand(2, buffer, 1, buffer+3);

		data2 = (PMDuint16)buffer[2];

		return result;
}

PMDuint16 PMDTransport::SendCommandWordWordGetWord(PMDuint16 opCode, 
									 PMDuint16 data1, PMDuint16 data2, PMDuint16 &data3) {
        PMDuint16 result = PMD_ERR_OK;
        PMDuint16 buffer[4];

        buffer[0] = BuildCommandWord(opCode,axis);
        buffer[1] = (PMDuint16)data1;
        buffer[2] = (PMDuint16)data2;

        result = pmdIOTransport->SendCommand(3, buffer, 1, buffer+3);

        data3 = (PMDuint16)buffer[3];

        return result;
}

void PMDTransport::SetDebugLevel(int debugLevel) {
    this->debugLevel = debugLevel;
    pmdIOTransport->SetDebugLevel(debugLevel);
}
