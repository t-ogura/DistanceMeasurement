#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include "../include/PMDNetwork.h"     // This class
#include "../include/PMDUtils.h"       // For config file parsing

// Populate constants defined by this class
const char PMDNetwork::StartToken[] = "[network]";
const char PMDNetwork::StopToken[] = "[/network]";


//----------------------------------------------------------------------------
PMDNetwork::PMDNetwork(const char *uniqueID, PortableSerial *comm) {
    strcpy(this->uniqueID,uniqueID);
    this->comm = comm;
    controllers = new ControllerCollection;
    compasses = new CompassCollection;
}

// ------------------------------------------------------------------------
PMDNetwork::PMDNetwork(FILE *file, char *token) {

    controllers = new ControllerCollection;
    compasses = new CompassCollection;
    comm = new PortableSerial();

    // Load configuration from the file.
    ReadConfig(file,token);

}

//----------------------------------------------------------------------------
PMDNetwork::~PMDNetwork() {

}

//----------------------------------------------------------------------------
bool PMDNetwork::AddController(char* str, PMDController* controller) {
    (*controllers)[str] = controller;
    return ((*controllers)[str] != NULL);
}

//----------------------------------------------------------------------------
bool PMDNetwork::AddCompass(char *str, Compass* compass) {
    (*compasses)[str] = compass;
    return ((*compasses)[str] != NULL);
}

//----------------------------------------------------------------------------
bool PMDNetwork::OnlyOneDeviceIsOnNetwork() {
    return ((controllers->size() + compasses->size()) == 1);
}

// ------------------------------------------------------------------------
void PMDNetwork::ReadConfig(FILE *file, char *token) {

    // Valid token definitions
    const char TokenPort[] = "port";
    const char TokenBaud[] = "baud";
    const char TokenStopBits[] = "stopBits";
    const char TokenParity[] = "parity";
    const char TokenNoParity[] = "noParity";
    const char TokenOddParity[] = "oddParity";
    const char TokenEvenParity[] = "evenParity";

    // Local declarations
    char                        portName[32];
    int                         baud = PortableSerial::defaultBaud;
    PortableSerial::Parity      parity = PortableSerial::defaultParity;
    PortableSerial::StopBits    stopBits = PortableSerial::defaultStopBits;
    bool                        tokenRecognized = true;
    unsigned int                val;

    // Prime token stream.
    PMDUtils::ReadToken(file,token);

    // Parse the stream.
    do {
        if (!strcmp(token,PMDUtils::TokenUniqueID)) {
            PMDUtils::ReadToken(file,token);
            strcpy(uniqueID,token);
        } else if (!strcmp(token,TokenPort)) {
            PMDUtils::ReadToken(file,token);
            strcpy(portName,token);
        } else if (!strcmp(token,TokenBaud)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf(token,"%u",&val) == 1;
            baud = val;
        } else if (!strcmp(token,TokenStopBits)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf(token,"%u",&val) == 1;
            if (val == 1) stopBits = PortableSerial::OneStopBit;
            else if (val == 2) stopBits = PortableSerial::TwoStopBits;
            else tokenRecognized = false;
        } else if (!strcmp(token,TokenParity)) {
            PMDUtils::ReadToken(file,token);
            if (!strcmp(token,TokenNoParity))           
                parity = PortableSerial::NoParity;
            else if (!strcmp(token,TokenOddParity))     
                parity = PortableSerial::OddParity;
            else if (!strcmp(token,TokenEvenParity))    
                parity = PortableSerial::EvenParity;
            else tokenRecognized = false;
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);

    if (!tokenRecognized && !strcmp(token,StopToken))
        comm->SetConfig(portName,baud,parity,stopBits);
}

