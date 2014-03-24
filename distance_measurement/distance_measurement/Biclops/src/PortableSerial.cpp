//  PortableSerial.cpp -- (Adapted from PMDw32ser.cpp) serial IO
//
//  TRACLabs -- A division of Metrica, Inc.
//

#include <iostream>     // for cout
using namespace std;    // pull in std namespace (for VC++)

#if !defined WIN32
#include <errno.h>
#endif

#include "../include/PortableSerial.h" // This class

#ifdef WIN32
const char PortableSerial::defaultPortName[] = "COM1";
#else
const char PortableSerial::defaultPortName[] = "/dev/ttyS0";
#endif
const int PortableSerial::defaultBaud = 9600;
const PortableSerial::StopBits PortableSerial::defaultStopBits 
        = PortableSerial::OneStopBit;
const PortableSerial::Parity PortableSerial::defaultParity 
        = PortableSerial::NoParity;

// ------------------------------------------------------------------------
PortableSerial::PortableSerial() {
    SetDefaults();
}

// ------------------------------------------------------------------------
void PortableSerial::SetDefaults() {
#ifdef WIN32
    portHandle = INVALID_HANDLE_VALUE;
#else
    portHandle = -1;
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGINT);
#endif

    isOpen = false;
    SetConfig(defaultPortName,defaultBaud,defaultParity,defaultStopBits);

    // Initialize the serial mutex
    pthread_mutex_init (&serialMutex, NULL);

}

// ------------------------------------------------------------------------
PortableSerial::~PortableSerial() {
    Close();
    pthread_mutex_destroy(&serialMutex);
}

// ------------------------------------------------------------------------
bool PortableSerial::Open(
    const char* portName, int baud, Parity parity, StopBits stopBits) {

    // Record the communication parameters
    strcpy(this->portName,portName);
    this->baud   = baud;
	this->parity = parity;
	this->stopBits = stopBits;

    return Open();

}

// ------------------------------------------------------------------------
bool PortableSerial::Open() {

    // Make sure that if a port is currently opened then it is closed.
    Close();

    // Get exclusive access to the serial interface
    pthread_mutex_lock (&serialMutex);

    // Open the port
#ifdef WIN32
    portHandle = CreateFile(   portName, GENERIC_READ|GENERIC_WRITE, 0, 
//		                        NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 
		                        NULL, OPEN_EXISTING, FILE_FLAG_WRITE_THROUGH, 
                                NULL );
	if (portHandle != INVALID_HANDLE_VALUE) isOpen = true;
#else
    portHandle = open(portName, O_RDWR | O_NOCTTY);
    if (portHandle >= 0) isOpen = true;
#endif

    // Configure the communication characteristics of the port.
    if (isOpen) {
#ifdef WIN32

        // Translate PortableSerials internal definitions to OS-specific values.
        const int windowsParityLUT[] = {NOPARITY,ODDPARITY,EVENPARITY, MARKPARITY,SPACEPARITY};
        const int windowsStopBitsLUT[] = {ONESTOPBIT,ONE5STOPBITS,TWOSTOPBITS};

	    DCB dcb;
	    dcb.DCBlength         = sizeof(DCB);
	    dcb.BaudRate          = baud;
	    dcb.fBinary           = TRUE;               // Windows requires this to be true
	    dcb.fParity           = FALSE;
	    dcb.fOutxCtsFlow      = FALSE;
	    dcb.fOutxDsrFlow      = FALSE;
	    dcb.fDtrControl       = DTR_CONTROL_DISABLE; // High for port-powered RS232-485 converter
	    dcb.fDsrSensitivity   = FALSE;
	    dcb.fTXContinueOnXoff = FALSE;
	    dcb.fOutX             = FALSE;
	    dcb.fInX              = FALSE;
	    dcb.fErrorChar        = FALSE;
	    dcb.fNull             = FALSE;              // Don't want to discard null characters
	    dcb.fRtsControl       = RTS_CONTROL_DISABLE; // High for port-powered RS232-485 converter
	    dcb.fAbortOnError     = FALSE;              // Let this app detect and handle errors
	    dcb.XonLim            = 0;
	    dcb.XoffLim           = 0;
	    dcb.ByteSize          = 8;                  // Does anybody use 7-bit characters anymore?
	    dcb.Parity            = windowsParityLUT[parity];
	    dcb.StopBits          = windowsStopBitsLUT[stopBits];
	    dcb.XonChar           = 0;
	    dcb.XoffChar          = 0;
	    dcb.ErrorChar         = 0;
	    dcb.EofChar           = 0;
	    dcb.EvtChar           = 0;

	    if (!SetCommState( portHandle, &dcb )) {
		    CloseHandle( portHandle );
		    portHandle = INVALID_HANDLE_VALUE;
		    isOpen = false;
	    }

#else

        // Clear the port descriptor.
        bzero(&termIOData, sizeof(termIOData));

        // Ignore breaks, ignore parity errors.
        // Why we do these things, I do not know (BTW).
        termIOData.c_iflag = IGNBRK | IGNPAR;

        // Don't do anything special for outputs.
        termIOData.c_oflag = 0;

        // Set up the interface for raw (unmodified) transmission.
        termIOData.c_lflag = 0;

        // Fill structure baud rate entry using translator function
        cfsetspeed(&termIOData, baud);

        // Make port a local line (don't change owner of port) and enable
        // character receiving.
        termIOData.c_cflag |= (CLOCAL | CREAD);

        // Translate PortableSerials internal definitions to OS-specific values.
        switch (parity) {
            case NoParity : 
                if (stopBits != OneStopBit) termIOData.c_cflag |= CSTOPB;
                break;
            case OddParity :
                termIOData.c_cflag |= PARENB;
                termIOData.c_cflag |= PARODD;
                if (stopBits != OneStopBit) termIOData.c_cflag |= CSTOPB;
                break;
            case EvenParity :
                termIOData.c_cflag |= PARENB;
                if (stopBits != OneStopBit) termIOData.c_cflag |= CSTOPB;
                break;
            case MarkParity : // Mark parity is simulated by two stop bits (ignore stop def)
                termIOData.c_cflag |= CSTOPB;
                break;
            case SpaceParity : // Space parity is the same as no parity
                break;
        }

        // Set the character size to 8 bits.
        termIOData.c_cflag |= CS8;

        // Issue the port changes.
        tcsetattr(portHandle, TCSAFLUSH, &termIOData);

#endif

        // Set the port timeouts to a default value because the interface 
        // won't work without it.
        SetTimeout(100);

    }

    // Release exclusive access to the serial interface
    pthread_mutex_unlock (&serialMutex);

    FlushRecv();
	return isOpen;

}

// ------------------------------------------------------------------------
bool PortableSerial::SetTimeout(long msec) {
    bool status = true;
#ifdef WIN32
    COMMTIMEOUTS timeouts;

	if ( portHandle == INVALID_HANDLE_VALUE ) 
        status = false;
    else {
        // Compute character time based on current baud rate.
        // Read timeout is #chars*ReadTotalTimeoutMultiplier + ReadTotalTimeoutConstant
        // ReadIntervalTimeout -> max msecs between two reach characters
        // Baud is really bits/second, so a single character time, 
        // in milliseconds, is 1000msec/sec * 10 bits/character / bits/second =
        // msec/char. Unfortunately, Windows time resolution is 1 msec, so any
        // baud faster than 9600 baud results in a char time of 0.
        DWORD characterTimeInMilliseconds = max(10*1000/baud,1);
//	    timeouts.ReadIntervalTimeout         = characterTimeInMilliseconds;
	    timeouts.ReadIntervalTimeout         = 0;   // Only care about total time
        timeouts.ReadTotalTimeoutMultiplier  = 10; // Should be based on baud!
        timeouts.ReadTotalTimeoutConstant    = 500;
        timeouts.WriteTotalTimeoutMultiplier = 0;
        timeouts.WriteTotalTimeoutConstant   = 0;

	    status = !SetCommTimeouts( portHandle, &timeouts );
    }
#else
	if (portHandle == 0) status = false;
    else {
        termIOData.c_cc[VMIN] = 0;
        termIOData.c_cc[VTIME] = msec/100;  // VTIME in tenths of a second
        tcsetattr(portHandle, TCSANOW, &termIOData);
    }
#endif
    return status;
}

// ------------------------------------------------------------------------
void PortableSerial::Close() {

    // Get exclusive access to the serial interface
    pthread_mutex_lock (&serialMutex);

    // Reset the serial configuration to defaults before closing the handle.
#ifdef WIN32
    if (portHandle != INVALID_HANDLE_VALUE)
        CloseHandle(portHandle);
    portHandle = INVALID_HANDLE_VALUE;
#else
    if (portHandle >= 0) 
        close(portHandle);
    portHandle = -1;
#endif

    isOpen = false;

    // Release exclusive access to the serial interface
    pthread_mutex_unlock (&serialMutex);

}

// ------------------------------------------------------------------------
void PortableSerial::SetConfig(const char* portName, int baud, Parity parity, 
                               StopBits stopBits) {
    strcpy(this->portName,portName);
    this->baud = baud;
    this->parity = parity;
    this->stopBits = stopBits;
}

// ------------------------------------------------------------------------
void PortableSerial::GetConfig(char* portName, int &baud, 
        Parity &parity, StopBits &stopBits) {
    strcpy(portName, this->portName);
    baud = this->baud;
    parity = this->parity;
    stopBits = this->stopBits;
}

// ------------------------------------------------------------------------
bool PortableSerial::FlushRecv() {

    // Get exclusive access to the serial interface
    pthread_mutex_lock (&serialMutex);

    bool flushSuccess = true;

#ifdef WIN32
	if (portHandle == INVALID_HANDLE_VALUE ) flushSuccess = false;
    else PurgeComm(portHandle,PURGE_RXCLEAR);

#else
	if (portHandle < 0) 
        flushSuccess = false;
    else
        tcflush(portHandle, TCIFLUSH);
#endif

    // Release exclusive access to the serial interface
    pthread_mutex_unlock (&serialMutex);

    return flushSuccess;
}

// ------------------------------------------------------------------------
bool PortableSerial::Read(unsigned char* data, int count) {
    bool success;

    // Get exclusive access to the serial interface
    pthread_mutex_lock (&serialMutex);

#ifdef WIN32
    unsigned long bytes;
	if (ReadFile(portHandle, data, count, &bytes, NULL) != 0)
        success = (bytes == (unsigned long)count);
    else
        success = false;
#else
    success = read(portHandle, data, count) == count;
#endif

    // Release exclusive access to the serial interface
    pthread_mutex_unlock (&serialMutex);

    return success;
}

// ------------------------------------------------------------------------
bool PortableSerial::Write(const unsigned char* data, int count) {

    bool success;

    // Get exclusive access to the serial interface
    pthread_mutex_lock (&serialMutex);

#ifdef WIN32
	unsigned long bytes;
    if (WriteFile(portHandle, data, count, &bytes, NULL) != 0)
        success = (bytes == (unsigned long)count);
    else 
    	success = false;
#else
	success = write(portHandle, data, count) == count;
#endif

    // Release exclusive access to the serial interface
    pthread_mutex_unlock (&serialMutex);

    return success;

}

// ------------------------------------------------------------------------
bool PortableSerial::WriteRead( const unsigned char* wdata, int wcount,
                                unsigned char* rdata, int rcount) {

    bool success;

    // Get exclusive access to the serial interface
    pthread_mutex_lock (&serialMutex);

#ifdef WIN32
	unsigned long bytes;
    int ioStatus;
	ioStatus = WriteFile( portHandle, wdata, wcount, &bytes, NULL );
    if (ioStatus != 0) {
        if (bytes == (unsigned long)wcount) 
            success = true;
        else
            success = false;
    } else success = false;
#else
	size_t ioStatus = write(portHandle, wdata, wcount); 
    success = ioStatus == (unsigned int)wcount;
    if (!success)  cout << "Failed write " << ioStatus << " " << errno << endl;
#endif

#ifdef WIN32
    if (ioStatus != 0) {
        unsigned long bytes;
	    ioStatus = ReadFile(portHandle, rdata, rcount, &bytes, NULL);
        if (ioStatus != 0) {
            if (bytes == (unsigned long)rcount) {
                // Got all the data requested.
                success = true;
//            } else if (bytes > 0) {
//                // Got some, but not all data. Try to get the rest.
//                unsigned long bytesLeft = rcount - bytes;
//	            ioStatus = ReadFile(portHandle, rdata, bytesLeft, &bytes, NULL);
//                if (ioStatus != 0) {
//                    if (bytes == bytesLeft) 
//                        success = true;
//                    else
//                        success = false;
//                } else success = false;
            } else 
                success = false;
        } else {
            DWORD err = GetLastError();
            cout << "ReadFile error msg => " << err << endl;
            success = false;
        }
//                char msgBuf[100];
//                FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM,NULL,0,0,msgBuf
    }
#else
    if (ioStatus > 0) {
        ioStatus = read(portHandle, rdata, rcount); 
        success = ioStatus == (unsigned int)rcount;
        if (!success)  cout << "Failed read " << ioStatus << " " << errno << endl;
    }
#endif

    // Release exclusive access to the serial interface
    pthread_mutex_unlock (&serialMutex);

    return success;

}
