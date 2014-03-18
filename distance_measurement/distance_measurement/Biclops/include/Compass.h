#if !defined COMPASS_H
#define COMPASS_H

#include "PortableSerial.h" // access to serial interface
#include "PMDNetwork.h"     // access to associated network
#include "PMDController.h"  // needed when compass is attached to controller

class Compass {
public:

    char uniqueID[50];

    // Configuration Methods
    Compass(FILE *file, char *token);

    static const char *StartToken;
    static const char *EndToken;
    void ReadParameters();
    
    bool Connect();
//    bool PrepareCommForCompass(PortableSerial *serialPort, 
//                               bool validateResponse = true);
    void RestoreCommSettings();
    bool TestCompassComm();
    void EnableCompassTransmission();
    void DisableCompassTransmission();

    // Compass data commands
    void SetHeadingOutputMode();
    void SetMagnetometerOutputMode();
    void ToggleDataOutputMode();
    bool QueryData(float &val1, float &val2, float &val3);
    void RollAxisRezero();
    void PitchAxisRezero();
    bool QueryAveragedData(float &val1, float &val2, float &val3);
    void SplitFilterToggle();
    void Reset();
    void UserCalibration();

    // Compass configuration commands
    void SetVariationInput(int variation);
    void SetDeviationInput(int deviation);
    void SetUserMagneticOffset(int x, int y, int z);
    void SetBaudRate(int baud);
    void SetSystemFilter(int filterValue);
    void SetMagneticFilter(int filterValue);
    void GetConfiguration(  bool &magneticOutputSentenceSelected, 
                            bool &headingOutputSentenceSelected, 
                            bool &temperatureBelowNeg10C,
                            bool &temperatureBelowNeg20C,
                            bool &splitFilterOn);

    // Utility methods
    void FlushResponses(bool displayFlushedResponses = false);

private:

    static const unsigned char CompassXmtEnaAddr;
    static const unsigned short CompassXmtMask;

    PMDController *controller;
    bool compassIsInitialized;  // True when the compass has been initialized successfully

    // Transmits string over serial interface, including <cr> <lf>
    void SendCommand(const char *str);
    bool GetResponse(char *response, int maxDelay = 100);
#if defined WIN32
    DWORD lastCommandTime;
#endif

    PMDNetwork *network;
    PortableSerial *serial; // Shortcut to serial port
    bool compassChannelIsOpen;

    // Serial port settings before compass is talked to
    char            portName[32];
	int             baud;
    PortableSerial::Parity          parity;
	PortableSerial::StopBits        stopBits;

    static const int compassBaud;
    static const PortableSerial::Parity compassParity;
    static const PortableSerial::StopBits compassStopBits;

};

#endif

