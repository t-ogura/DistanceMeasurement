#ifndef PortableSerial_h
#define	PortableSerial_h
//  PortableSerial.h -- A portable serial interface
//
//  TRACLabs -- A division of Metrica, Inc.
//

#ifdef WIN32
   #include <wtypes.h> // Needed for definition of HANDLE type
#else // Linux
 /*   #include <sys/types.h>
    #include <sys/ioctl.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <signal.h>
    #include <termios.h>
    #include <cstdio>   */       // for FILE defn
#endif

#include "pthread.h"        // for mutex protection of serial port
class PortableSerial {
public:

    typedef enum Parity {NoParity, EvenParity, OddParity,
                         MarkParity, SpaceParity} Parity;
    typedef enum StopBits {OneStopBit, OneAndAHalfStopBits, TwoStopBits} StopBits;




    // Default definitions
    static const char       defaultPortName[];
    static const int        defaultBaud;
    static const StopBits   defaultStopBits;
    static const Parity     defaultParity;

    PortableSerial();
    virtual ~PortableSerial();

    // Access to port parameters.
    void SetConfig(const char* portName, int baud, Parity parity, StopBits stopBits);
    void GetConfig(char* portName, int &baud, Parity &parity, StopBits &stopBits);

    // Open the port using the stored port parameters.
    bool Open();

    // Open the port using the provided port parameters.
    bool Open(const char* portName, int baud, Parity parity, StopBits stopBits);
    void Close();

    // True if the port is currently open.
    bool IsOpen() {return isOpen;};

    // Receives COUNT bytes from the serial port into the DATA buffer);
    bool Read(unsigned char* data, int count);

    // Sends COUNT bytes from the DATA buffer to the serial port.
    bool Write(const unsigned char* data, int count);

    // Atomic Write/Read operation as guaranteed by mutual exclusion.
    bool WriteRead( const unsigned char* wdata, int wcount,
                    unsigned char* rdata, int rcount);

    // support functions that may be called directly
    // once the port is initialized
    bool SetTimeout(long msec);
    bool FlushRecv();


private:

    bool            isOpen;
    char            portName[32];
	int             baud;
	Parity          parity;
	StopBits        stopBits;
    pthread_mutex_t serialMutex;

    void SetDefaults();

#ifdef WIN32
	HANDLE portHandle;
#else //Linux
//    int portHandle;
//    sigset_t sigSet;
//    struct termios termIOData;
#endif

};

#endif
