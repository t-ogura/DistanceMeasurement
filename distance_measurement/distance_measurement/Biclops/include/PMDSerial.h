#ifndef PMDSerial_h
#define	PMDSerial_h
//  PMDSerial.h -- (Adapted from PMDw32ser.h) serial IO
//
//  TRACLabs -- A division of Metrica, Inc.
//
//  Description: 
//      While PortableSerial controls the host-specific aspects of a
//      serial interface, this class maintains PMD-specific aspects of the 
//      serial interface as they pertain to a specific controller. One
//      serial interface may be shared by multiple controllers, so this
//      class encapsulates each controller's serial interface and uses
//      the PortableSerial instance to actually move data between the
//      host application and an individual controller.
//
#include <cstdio>          // for FILE defn
//#include <stdio.h>          // for FILE type
#include "PortableSerial.h" // Needed for type definitions
#include "PMDNetwork.h"     // The serial interface
#include "PMDAxisControl.h" // for GetSerialPortMode()
#include "PMDIOTransport.h" // Base transport class

class PMDSerial : public PMDIOTransport {
public:

    PMDSerial(  PMDNetwork *network,
                tagPMDSerialProtocol protocol, 
                PMDuint8             multiDropID = 0);
    PMDSerial(FILE *file, char *token); // Constructor using configuration file.
    virtual ~PMDSerial();

    void SetDefaults();

    PMDNetwork *GetNetwork() { return network;}
    void SetNetwork(PMDNetwork *network);

    // Gives instance access to commands to change controller's serial settings.
    // This must be called before attempting to talk to controller.
    void SetPrimaryAxisInterface(PMDAxisControl *axis) { primaryAxis = axis;}

    // Set the serial communication parameters. These values are used
    // to build the command buffer needed to communicate to the controller.
    // These values are not used to change the controller settings directly.
    void SetProtocol( tagPMDSerialProtocol protocol, 
                      PMDuint8             multiDropID = 0);

    // Get the current port settings for this controller.
    void GetProtocol( tagPMDSerialProtocol &protocol,
                      PMDuint8             &multiDropID);

    // Attempt connection to the controller using the current settings.
    bool Open();
    void Close();

    // Create the command buffer that will be sent to the controller.
    // Returns the number of bytes to be sent.
    PMDuint8 BuildCommandBuffer(PMDuint8 *cmdBuf, 
                                const PMDuint16* data, 
                                PMDuint8 dataWordCount);

    // Access to the number of times a command may be reissued if comm 
    // errors are detected. 
    unsigned int GetCommandRepeatAttemptLimit();
    void SetCommandRepeatAttemptLimit(unsigned int);

    // Implementation of superclass pure virtual functions
    PMDuint16 SendCommand(PMDuint8 xmtWordCount, PMDuint16* xmtData, 
                          PMDuint8 rcvWordCount, PMDuint16* rcvData);
    PMDuint16 GetStatus() { return 0;};
    bool IsReady() { return isConnected;};
//    bool HasInterrupt() { return false;};
    bool HasError() { return false;};

    // Constants
    static const tagPMDSerialBaudRate defaultPMDBaud;
    static const tagPMDSerialParity defaultPMDParity;
    static const tagPMDSerialStopBits defaultPMDStopBits;
    static const tagPMDSerialProtocol defaultPMDProtocol;
    static const PMDuint8 defaultPMDMulidropID;

    // Type conversion utilities
    static int  PMDToHostBaud(tagPMDSerialBaudRate pmdBaud);
    static PortableSerial::Parity 
                PMDToHostParity(tagPMDSerialParity pmdParity);
    static PortableSerial::StopBits 
                PMDToHostStopBits(tagPMDSerialStopBits pmdStopBits); 
    static tagPMDSerialBaudRate HostToPMDBaud(int hostBaud);
    static tagPMDSerialParity 
                HostToPMDParity(PortableSerial::Parity hostParity);
    static tagPMDSerialStopBits 
                HostToPMDStopBits(PortableSerial::StopBits hostStopBits);

    // Change serial settings to conform to PMD requirements.
    // Returns true if any of the parameters were modified.
    static bool ConstrainSerialSettings(
        int &baud, PortableSerial::Parity &parity,
        PortableSerial::StopBits &stopBits);
    static bool ConstrainSerialSettings(
        tagPMDSerialBaudRate &baud, tagPMDSerialParity &parity,
        tagPMDSerialStopBits &stopBits);

    // Ensure baud rate conforms to PMD values.
    // Return true if baud was modified.
    static bool ConstrainBaud(int &baud);

    static const char *StartToken;
    static const char *EndToken;
    void ReadParameters(FILE *file, char *token);

private:
    static const char* classStr;

    PMDuint16 Sync();
    PMDuint16 ReSync();
    void SetProtocol(PMDuint16 mode);
    void ChangeComm();
    void OpenPortWithSearch();

    bool isConnected;
    tagPMDSerialProtocol protocol;
    PMDuint8             multiDropID;
    unsigned int         failedCommandRepeatAttemptLimit;

	PMDuint16 verifyChecksum;
	PMDuint16 diagnostics;

//    PortableSerial *serialPort;
    PMDNetwork *network;
    PMDAxisControl *primaryAxis;

    unsigned char statusByte;

};

#endif
