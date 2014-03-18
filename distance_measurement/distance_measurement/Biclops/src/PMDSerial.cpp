//  PMDSerial.cpp -- (Adapted from PMDw32ser.cpp) serial IO
//
//  TRACLabs -- A division of Metrica, Inc.
//
#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include <cstdio>          // For sccanf definition
//#include <stdio.h>
#include <string.h>

#include <iostream>     // for cout
#include <iomanip>      // for setw() method
using namespace std;    // pull in std namespace (for VC++)

#include "../include/PMDTypes.h"
#include "../include/PMDOPCodes.h"
#include "../include/PMDUtils.h"       // for error code conversion
#include "../include/PMDCollections.h" // for access to network collection
#include "../include/PMDSerial.h"      // This class

// Debugging declarations
const char* PMDSerial::classStr = "PMDSerial::";
#define dbgCout cout << classStr << methodStr 
#define ifDbgCout if (GetDebugLevel() > 0) dbgCout
#define ifDbgCout1 if (GetDebugLevel() > 1) dbgCout

// only include this if we are running in diagnostics mode
#include "../include/PMDDiagnostics.h"

const tagPMDSerialBaudRate  PMDSerial::defaultPMDBaud = PMDSerialBaud9600;
const tagPMDSerialParity    PMDSerial::defaultPMDParity = PMDSerialParityNone;
const tagPMDSerialStopBits  PMDSerial::defaultPMDStopBits = PMDSerial1StopBit;
const tagPMDSerialProtocol  PMDSerial::defaultPMDProtocol = 
                                PMDSerialProtocolPoint2Point;
const PMDuint8              PMDSerial::defaultPMDMulidropID = 0;

const char *PMDSerial::StartToken = "[comm]";
const char *PMDSerial::EndToken = "[/comm]";

// ------------------------------------------------------------------------
PMDSerial::PMDSerial(  PMDNetwork *network,
                tagPMDSerialProtocol protocol, 
                PMDuint8             multiDropID) {

    SetDefaults();

    this->network = network;
    this->protocol = protocol;
    this->multiDropID = multiDropID;
}

// ------------------------------------------------------------------------
PMDSerial::PMDSerial(FILE *file, char *token) {
    SetDefaults();
    ReadParameters(file,token);
}

// ------------------------------------------------------------------------
void PMDSerial::SetDefaults() {
	verifyChecksum = 1;    // by default always verify the checksum
	diagnostics = 0;	// by default disable diagnostics
    isConnected = false;
    SetDebugLevel(0);
    SetTransportType (SERIAL);
    protocol = defaultPMDProtocol;
    multiDropID = defaultPMDMulidropID;
    failedCommandRepeatAttemptLimit = 1;
    network = NULL;
}

// ------------------------------------------------------------------------
PMDSerial::~PMDSerial() {
    Close();
}

// ------------------------------------------------------------------------
void PMDSerial::SetProtocol(tagPMDSerialProtocol pmdProtocol, 
                            PMDuint8 pmdMultiDropID) {
    protocol = pmdProtocol;
    multiDropID = pmdMultiDropID;
}

// ------------------------------------------------------------------------
void PMDSerial::GetProtocol(tagPMDSerialProtocol &pmdProtocol, 
                            PMDuint8 &pmdMultiDropID) {
    pmdProtocol = protocol;
    pmdMultiDropID = multiDropID;
}
   
// ------------------------------------------------------------------------
bool PMDSerial::Open() {

    char methodStr[] = "Open: ";    // Debug defn
    PortableSerial *comm = network->GetSerial();

    bool allowedToChangeComm = network->OnlyOneDeviceIsOnNetwork();

    // Get the host port settings
    char portName[32];
    int baud;
    PortableSerial::Parity parity;
    PortableSerial:: StopBits stopBits;
    comm->GetConfig(portName,baud,parity,stopBits);

    // Validate the host port settings against PMD restrictions.
    bool constrained = ConstrainSerialSettings(baud,parity,stopBits);

    //    isConnected = false;

    // Is comm currently established with this controller?
    if (isConnected) {

        // Comm is already established, so the implication is that it is
        // desired to reestablish communication at a different comm setting.
        // Only do this if it is allowed.
        if (allowedToChangeComm) {
            if (constrained) comm->SetConfig(portName,baud,parity,stopBits);
            ChangeComm();
        }

    } else {

        // Comm is not established with this controller.

        if (constrained) ifDbgCout << "Host serial settings constrained\n";

        if (allowedToChangeComm) {
            // Try connecting to controller even if it means changing the
            // host port to do so.
            comm->SetConfig(portName,baud,parity,stopBits);
            OpenPortWithSearch();
        } else if (!constrained) {
            // Not allowed to change the host port, but since the host
            // port settings are within PMD constraints, try opening anyway.
            comm->Open();
        } else {
            // Not allowed to change port and the host port settings are
            // invalid. Abort!
        }
    }

    // Verify that communication with the controller works.
    if (comm->IsOpen()) {

        // This only tells us if there is something on the other end of the wire.
        ifDbgCout << "comm sync test\n";
        if (Sync() != PMD_ERR_OK) {
            ifDbgCout << "comm sync test failed\n";
            isConnected = false;
        } else {
            ifDbgCout << "comm sync test succeeded\n";
            isConnected = true;
        }

    } else isConnected = false;

	return isConnected;
}

// ------------------------------------------------------------------------
void PMDSerial::OpenPortWithSearch() {

    char methodStr[] = "OpenPortWithSearch: ";    // Debug defn
    PortableSerial *comm = network->GetSerial();

    // Get the desired serial port baud rate.
    char portName[32]; 
    int desiredBaud,trialBaud;
    PortableSerial::Parity desiredParity,trialParity;
    PortableSerial::StopBits desiredStopBits,trialStopBits;
    comm->GetConfig(portName,desiredBaud,desiredParity,desiredStopBits);

    // Attempt to open the serial port.
    trialBaud = desiredBaud;
    trialParity = desiredParity;
    trialStopBits = desiredStopBits;

    do {
        // If the port is open presently then connection to the 
        // controller occured, but not at the preferred baud. Use the 
        // established connection to change the controller to the desired 
        // settings and then change the host port to match.
        if (comm->IsOpen()) {
            trialBaud = desiredBaud;
            ifDbgCout << "Retrying connection on " << portName << " @ "
                      << trialBaud << " baud\n";
            ConstrainSerialSettings(trialBaud,trialParity,trialStopBits);
            comm->SetConfig(portName,desiredBaud,desiredParity,desiredStopBits);
            ChangeComm();
        } else {
            ifDbgCout << "Trying connection on " << portName << " @ "
                      << trialBaud << " baud\n";

            ConstrainSerialSettings(trialBaud,trialParity,trialStopBits);
            comm->SetConfig(portName,trialBaud,trialParity,trialStopBits);
            comm->Open();

            // Test the connection.
            if (Sync() != PMD_ERR_OK) {

                ifDbgCout << "Connection @" << trialBaud << " failed\n";

                // step to next speed on failure.
                switch (trialBaud) {
                case   9600: trialBaud =  19200; break;
                case  19200: trialBaud =  57600; break;
                case  57600: trialBaud = 115200; break;
                case 115200: trialBaud =   9600; break;
                }
                trialParity = desiredParity;
                trialStopBits = desiredStopBits;
                comm->Close();
            }
        }
    } while (trialBaud != desiredBaud);
}

//----------------------------------------------------------------------------
void PMDSerial::ChangeComm() {
//    char methodStr[] = "ChangeComm: ";

            
    // Get the current controller settings.
    tagPMDSerialBaudRate pmdBaud;
    tagPMDSerialParity   pmdParity;
    tagPMDSerialStopBits pmdStopBits;
    tagPMDSerialProtocol protocol;
    PMDuint8 multiDropID;
    primaryAxis->GetSerialPortMode(pmdBaud,pmdParity,pmdStopBits,
        protocol,multiDropID);
    
    // Get the desired serial port baud rate.
    char portName[32]; 
    int desiredBaud;
    PortableSerial::Parity parity;
    PortableSerial::StopBits stopBits;
    network->GetSerial()->GetConfig(portName,desiredBaud,parity,stopBits);

    // Change the controller's comm settings.
    pmdBaud = PMDSerial::HostToPMDBaud(desiredBaud);
    primaryAxis->SetSerialPortMode(pmdBaud,pmdParity,pmdStopBits,
        protocol,multiDropID);
    
    // Reopen the host interface with the new settings.
    network->GetSerial()->Open();
            
}

// ------------------------------------------------------------------------
PMDuint8 PMDSerial::BuildCommandBuffer( PMDuint8 *cmdBuf, 
                                    const PMDuint16* dataBuf, 
                                    PMDuint8 dataWordCount) {

    unsigned int c=0;
	unsigned int i;
	char checksum;
//    char methodStr[] = "BuildCommandBuffer: ";

	// Load address byte
	cmdBuf[c++] = (char)( (multiDropID) &0x1f);

    // Clear checksum byte (makes it easier to compute checksum later.
    cmdBuf[c++] = 0;

	// Add axis number and command code
	cmdBuf[c++] = (char)(dataBuf[0]>>8);
	cmdBuf[c++] = (char)(dataBuf[0]&0xff);

	// add data (handling byte swapping)
	for (i=1; i<dataWordCount; i++) {
		cmdBuf[c++] = (char)(dataBuf[i] >> 8);
		cmdBuf[c++] = (char)(dataBuf[i] & 0xFF);
	}

	// calculate checksum
	for (checksum=i=0; i<c; i++) checksum += cmdBuf[i];
	cmdBuf[1] = -checksum;

    if (GetDebugLevel() > 1) {
        cerr << " Xmt" << setfill('0') ;
        unsigned int bufNdx;
        for (bufNdx = 0; bufNdx < 8; bufNdx++) {
            if (bufNdx < c) {
                cerr << ' ' << setw(2) << hex << (unsigned int)(cmdBuf[bufNdx]) << dec;
            } else {
                cerr << "   ";
            }
            if (bufNdx == 3) {
                cerr << '(' << PMDOpcodeText[cmdBuf[bufNdx]].text << ')'
                            << PMDOpcodeText[cmdBuf[bufNdx]].pad << ' ';
            }
        }
        cerr << " || ";
        cerr << setfill(' ');
    }

    return c;
}

// ------------------------------------------------------------------------
PMDuint16 PMDSerial::SendCommand(PMDuint8 xmtWordCount, PMDuint16* xmtData, 
                                 PMDuint8 rcvWordCount, PMDuint16* rcvData) {

	PMDuint8 xbuf[40],rbuf[40];
    PMDuint8 c;
    PMDuint16 status = PMD_ERR_OK;
    PortableSerial *comm = network->GetSerial();

    char methodStr[] = "SendCommand: ";

    c = BuildCommandBuffer(xbuf,xmtData,xmtWordCount);

    // Send the data buffer.
    unsigned int commandAttempts = 0;
    do {

        // Is the serial port configured to be multidrop with an address bit?
	    if (protocol == PMDSerialProtocolMultiDropUsingAddressBit) {

            // Serial port is configured to be multidrop with an address bit.
            // Fake the address bit using the parity bit
            if (!comm->FlushRecv()) {
                status = PMD_ERR_CommPortWrite;
            } else {
                char portName[32];
                int baud;
                PortableSerial::Parity parity;
                PortableSerial::StopBits stopBits;
                comm->GetConfig(portName,baud,parity,stopBits);
                comm->Open(portName, baud, PortableSerial::MarkParity, stopBits);
                if (!comm->Write(xbuf, 1)) {
                    status = PMD_ERR_CommPortWrite;
                } else {
    //                if (!comm->FlushRecv()) {
    //                    status = PMD_ERR_CommPortWrite;
    //                } else {
                        comm->Open(portName, baud, PortableSerial::SpaceParity, stopBits);
		                if (!comm->WriteRead(xbuf+1, c-1,rbuf,2*rcvWordCount+2)) 
                            status = PMD_ERR_CommPortRead;
    //                }
                }
            }
        } else {

            // Serial port is not configured to be multidrop with an address bit.
            // Send the data normally.
            if (xbuf[3] == PMDOPReset) {
                if (!comm->Write(xbuf, c)) 
                    status = PMD_ERR_CommPortWrite;
            }
            else if (!comm->WriteRead(xbuf, c,rbuf,2*rcvWordCount+2)) {
                // try synchronizing and reissuing command.
//                if (ReSync() == PMD_ERR_OK) {
//                    if (!comm->WriteRead(xbuf, c,rbuf,2*rcvWordCount+2))
//                        status = PMD_ERR_CommPortRead;
//                } else
                    status = PMD_ERR_CommPortRead;
            }
        }

        // Continue with comm if there were no errors.
        if (GetDebugLevel() > 1) cerr << " Rcv ";
        if (status == PMD_ERR_OK) {

            if (GetDebugLevel() > 1) {
                if (xbuf[3] == PMDOPReset)
                    cerr << "0: (Reset cmd)";
                else {
                    cerr << 2*rcvWordCount+2 << setfill('0') << ": ";
                    for (unsigned char bufNdx = 0; bufNdx < 2*rcvWordCount+2; bufNdx++)
                        cerr << ' ' << setw(2) << hex << (int)(rbuf[bufNdx]) << dec;
                }
                cerr << endl << setfill(' ');
            }

	        // verify the checksum
            char checksum = 0;
            int i;
	        for (i=0; i<(int)(2*rcvWordCount+2); i++) checksum += rbuf[i];

            if (checksum != 0) {
                status = PMD_ERR_ChecksumError;
            } else {


	            // byte swap return data
	            for( i=0, c=2; i<rcvWordCount; i++ ) {
		            rcvData[i]  = (PMDuint16)(rbuf[c++])<<8;
		            rcvData[i] |= (PMDuint16)(rbuf[c++]);
	            }

            }
        } else {
            if (GetDebugLevel() > 1) cerr << "no response.\n";
        }

    } while (status != PMD_ERR_OK && 
             commandAttempts++ < failedCommandRepeatAttemptLimit);


    // Check the returned status word for errors reported by the chipset.
    // Reflect that status in the method return status.
    if (status == PMD_ERR_OK && rbuf[0] == 0) {
        return PMD_ERR_OK;
    } else if (status == PMD_ERR_OK) {
        status = rbuf[0];
    }
    ifDbgCout << "got \"" << PMDUtils::GetErrorMessage(status) << "\" exception\n";
    throw status;

}

// ------------------------------------------------------------------------
void PMDSerial::Close() {

/*    if (isConnected) {

        // Reset the serial configuration to defaults before closing the handle.
        char portName[32];
        int baud;
        PortableSerial::Parity parity;
        PortableSerial::StopBits stopBits;
        comm->GetConfig(portName,baud,parity,stopBits);
        comm->Open(portName, baud, PortableSerial::MarkParity, stopBits);
	}
*/
    isConnected = false;

}

// ------------------------------------------------------------------------
// Syncronize with the PMD controller. If the data bus is protocol is 
// point-to-point then synchronization is just a matter of sending out a
// series of zeroes until the attached controller responds (implemented
// through the ReSync method). If the data bus is not point-to-point, then
// synchronization can only be verified by issuing a complete command (in
// this case, a NOOP) to the controller and observing the response for 
// correctness.by 
PMDuint16 PMDSerial::Sync() {

    char methodStr[] = "Sync: ";    // Debug defn
    PMDuint16 status = PMD_ERR_OK;
    PortableSerial *comm = network->GetSerial();

    // If point-to-point protocol, send chars until something comes back.
    if (protocol == PMDSerialProtocolPoint2Point) status = ReSync();

    if (status == PMD_ERR_OK) {

	    comm->FlushRecv();

        // Verify that we truely have sync.
        // Send a complete NoOp command and look for a valid response.
        PMDuint16 cmdBuf = PMDOPNoOperation; 
        ifDbgCout << "verify sync with NoOp\n";
        try {
            status = SendCommand(0,&cmdBuf,0,NULL);
        } catch (...) {
            status = PMD_ERR_CommTimeoutError;
        }
        if (status == PMD_ERR_OK)
            ifDbgCout << "sync verified\n";
        else
            ifDbgCout << "sync verification failed\n";
    }

	return status;

}

// ------------------------------------------------------------------------
// Send out zeros (simulating a NoOp) 
// one at a time until the controller spits back response data. Once 
// a response is seen, purge any remaining data from the receive queue,
// at which point the interface is syncronized.
PMDuint16 PMDSerial::ReSync() {
    char methodStr[] = "ReSync: ";  // Debug defn
    PMDuint16 status = PMD_ERR_OK;
    PortableSerial *comm = network->GetSerial();

	// Flush the receive buffer
	comm->FlushRecv();

    // "Tickle" the serial interface until a response is received.
	const int maxSend = 4; // Should get some response after 4 chars if at right baud.
	int i;
    bool gotResponse = false;
    unsigned char ch = 0;

    ifDbgCout1 << "Pinging comm port";
	for( i=1; i<=maxSend && status == PMD_ERR_OK && !gotResponse; i++ ) {

		// write a null character
        if (GetDebugLevel() > 1) cout << '.';
        if (!comm->Write(&ch, 1)) {
            status = PMD_ERR_CommPortWrite;
        } else {

		    // Attemp to read a response
            gotResponse = comm->Read(&ch, 1);
        }

	}
    if (GetDebugLevel() > 1) cout << endl;

	// React to results of tickling
    if (gotResponse) {
        ifDbgCout1  << "got back (0x" << hex << (int)ch << dec
                    << ") after " << i-1 << " characters\n";

        // flush any other data still in the read buffer.
	    comm->FlushRecv();

    } else {
        ifDbgCout1  << "got no response after " << i-1 << " characters\n";
        status = PMD_ERR_CommTimeoutError;
  }

	return status;

}

// ------------------------------------------------------------------------
int PMDSerial::PMDToHostBaud(tagPMDSerialBaudRate pmdBaud) {
    int baudLUT[] = {1200,2400,4800,9600,19200,57600,115200,250000,416667};
    return baudLUT[pmdBaud];
}

// ------------------------------------------------------------------------
PortableSerial::Parity 
PMDSerial::PMDToHostParity(tagPMDSerialParity pmdParity) {
    PortableSerial::Parity parityLUT[] = {
                            PortableSerial::NoParity,
                            PortableSerial::OddParity,
                            PortableSerial::EvenParity};
    return parityLUT[pmdParity];
}

// ------------------------------------------------------------------------
PortableSerial::StopBits 
PMDSerial::PMDToHostStopBits(tagPMDSerialStopBits pmdStopBits) {
    PortableSerial::StopBits stopBitsLUT[] = {PortableSerial::OneStopBit,
                                              PortableSerial::TwoStopBits};
    return stopBitsLUT[pmdStopBits];
}

// ------------------------------------------------------------------------
tagPMDSerialBaudRate PMDSerial::HostToPMDBaud(int hostBaud) {
    switch (hostBaud) {
    case   1200: return PMDSerialBaud1200; break;
    case   2400: return PMDSerialBaud2400; break;
    case   9600: return PMDSerialBaud9600; break;
    case  19200: return PMDSerialBaud19200; break;
    case  57600: return PMDSerialBaud57600; break;
    case 115200: return PMDSerialBaud115200; break;
    case 250000: return PMDSerialBaud250000; break;
    case 416667: return PMDSerialBaud416667; break;
    default: return PMDSerialBaud9600; break;
    }
}
// ------------------------------------------------------------------------
tagPMDSerialParity 
PMDSerial::HostToPMDParity(PortableSerial::Parity hostParity) {
    tagPMDSerialParity parityLUT[] = {PMDSerialParityNone,
        PMDSerialParityOdd,PMDSerialParityEven,
        PMDSerialParityNone,PMDSerialParityNone}; // for mark&space parities
    return parityLUT[hostParity];

}

// ------------------------------------------------------------------------
tagPMDSerialStopBits 
PMDSerial::HostToPMDStopBits(PortableSerial::StopBits hostStopBits) {
    tagPMDSerialStopBits stopBitsLUT[] = {
        PMDSerial1StopBit,PMDSerial1StopBit,PMDSerial2StopBits};
    return stopBitsLUT[hostStopBits];

}

// ------------------------------------------------------------------------
bool PMDSerial::ConstrainSerialSettings(
        int &baud, PortableSerial::Parity &parity,
        PortableSerial::StopBits &stopBits) {

    // Constrain baud.
    bool constrained = ConstrainBaud(baud);

    // Constrain parity.
    // (No constraints on parity right now)

    // Constrain stop bits.
    if (baud == 57600 || baud == 115200) {
        if (stopBits != PortableSerial::TwoStopBits) constrained = true;
        stopBits = PortableSerial::TwoStopBits;
    } else {
        if (stopBits != PortableSerial::OneStopBit) constrained = true;
        stopBits = PortableSerial::OneStopBit;
    }

    return constrained;
}

// ------------------------------------------------------------------------
bool PMDSerial::ConstrainSerialSettings(
        tagPMDSerialBaudRate &baud, tagPMDSerialParity &parity,
        tagPMDSerialStopBits &stopBits) {
    bool constrained = false;
    // Assume baud is correct since it is an enumerated type.
    if (baud == PMDSerialBaud57600 || baud == PMDSerialBaud115200) {
        constrained = (stopBits != PMDSerial2StopBits);
        stopBits = PMDSerial2StopBits;
    }

    return true;
}

// ------------------------------------------------------------------------
bool PMDSerial::ConstrainBaud(int &baud) {
    bool constrained;
    switch (baud) {
    case   1200:
    case   2400:
    case   9600:
    case  19200:
    case  57600:
    case 115200:
    case 250000:
    case 416667:
        constrained = false;
        break;
    default: 
        baud = PMDToHostBaud(defaultPMDBaud);
        constrained = true;
        break;
    }
    return constrained;
}

//----------------------------------------------------------------------------
void PMDSerial::ReadParameters(FILE *file, char *token) {

    // Define the tokens used here.
    const char TokenNetwork[] = "network";
    const char TokenProtocol[] = "protocol";
    const char TokenPoint2Point[] = "Point2Point";
    const char TokenMultiDropAddressBit[] = "MultiDropAddressBit";
    const char TokenMultiDropIdleLine[] = "MultiDropIdleLine";

    bool tokenRecognized = true;
    unsigned int val;

    // Prime token stream.
    PMDUtils::ReadToken(file,token);

    // Parse the stream.
    do {
        if (!strcmp(token,TokenNetwork)) {

            // Get the name of the associated network.
            PMDUtils::ReadToken(file,token);

            // Get access to the named network and attach it to this controller.
            NetworkCollection *networks = PMDNetworks::Instance();
            network = (*networks)[token];
            if (network == NULL) tokenRecognized = false;

        } else if (!strcmp(token,TokenProtocol)) {
            bool doGetAddress = false;
            PMDUtils::ReadToken(file,token);
            if (!strcmp(token,TokenPoint2Point)) {
                protocol = PMDSerialProtocolPoint2Point;
            } else if (!strcmp(token,TokenMultiDropAddressBit)) {
                protocol = PMDSerialProtocolMultiDropUsingAddressBit;
                doGetAddress = true;
            } else if (!strcmp(token,TokenMultiDropIdleLine)) {
                protocol = PMDSerialProtocolMultiDropUsingIdleLineDetection;
                doGetAddress = true;
            } else tokenRecognized = false;
            if (doGetAddress) {
                PMDUtils::ReadToken(file,token);
                if (sscanf_s(token,"%u",&val) == 1) {
                    multiDropID = val;
                } else tokenRecognized = false;
            }
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}
