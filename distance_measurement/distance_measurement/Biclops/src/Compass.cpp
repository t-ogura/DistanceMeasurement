#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include <iostream>     // for cout
#if defined WIN32
using namespace std;    // required for VC++6 compiler
#include <time.h>       // for timeGetTime()
#endif

#include <string.h>     // for strcmp
#include "../include/PMDUtils.h"   // for DoSleep
#include "../include/PMDCollections.h"
                        // for access to the controller collection
#include "../include/Compass.h"    // the class implemented here

/*-----------------------------------------*/
//ÅyñkÅzí«â¡ÇµÇΩÇ‡ÇÃ
#include <mmsystem.h>
#pragma comment (lib, "winmm.lib")
/*-----------------------------------------*/

const int Compass::compassBaud = 9600;
const PortableSerial::Parity Compass::compassParity = PortableSerial::NoParity;
const PortableSerial::StopBits Compass::compassStopBits = PortableSerial::OneStopBit;
const char *Compass::StartToken = "[compass]";
const char *Compass::EndToken = "[/compass]";

//----------------------------------------------------------------------------
Compass::Compass(FILE *file, char *token) {

    // Valid token definitions
    const char TokenController[] = "controller";
    const char TokenNetwork[] = "network";

    // Set default values.
    network = NULL;
    serial = NULL;
    controller = NULL;
    compassChannelIsOpen = false;
    compassIsInitialized = false;
#if defined WIN32
    lastCommandTime = timeGetTime();
#endif

    bool tokenRecognized = true;

    // Prime token stream.
    PMDUtils::ReadToken(file,token);

    // Parse the stream.
    do {
        if (!strcmp(token,PMDUtils::TokenUniqueID)) {
            PMDUtils::ReadToken(file,token);
            strcpy(uniqueID,token);
        } else if (!strcmp(token,TokenController)) {

            // Get the name of the controller
            PMDUtils::ReadToken(file,token);

            // Get access to that controller.
            ControllerCollection *controllers = PMDControllers::Instance();
            controller = (*controllers)[token];

            // Get access to that controller's host port and record it
            if (controller != NULL) {
//                network = ((PMDSerial*)(controller->GetIOTransport()))->GetHostPort();
                network = controller->GetNetwork();
                serial = network->GetSerial();
            }
        } else if (!strcmp(token,TokenNetwork)) {

            // Get the name of the network
            PMDUtils::ReadToken(file,token);

            // Get access to the network and record it's associated serial port
            NetworkCollection *networks = PMDNetworks::Instance();
            network = (*networks)[token];
            serial = network->GetSerial();

        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);

}

//----------------------------------------------------------------------------
bool Compass::Connect() {

//    bool portIsOpen = false;

    // First, make sure comm port is open.
    if (controller == NULL) {

        // Must be on dedicated serial bus, so make sure serial port is open.
        if (!serial->IsOpen()) 
            compassChannelIsOpen = serial->Open();

    } else {

        // assume port was opened by the controller.
        compassChannelIsOpen = true;

    }

    if (compassChannelIsOpen) {

        // Ensure that the compass is not able to transmit over the serial bus.
        DisableCompassTransmission();

        // Desired default for the compass is to be quiet. Make it so.
        SetHeadingOutputMode();     // set desired output mode
        serial->FlushRecv();
        Reset();                    // establishes known output conditions
        PMDUtils::DoSleep(3000);    // wait for reset to finish.
        ToggleDataOutputMode();     // turns off continuous compass output
        serial->FlushRecv();
/*
        // Validate the response to the reset command if the compass is on its own
        // comm channel. If the controller is on a shared bus with other
        // controllers then it's ability to transmit is disabled so no response
        // can be gotten.
        char response[32];
        if (controller == NULL) GetResponse(response);

        // Flush any responses that occured after the reset command
        FlushResponses(true);

        if (controller == NULL) {
            // Verify communication with the compass by comparing the response 
            // to what is expected.
            char *startOfValidResponse = strchr(response,'H');
            if (startOfValidResponse != NULL) {
                if(strcmp("Honeywell HMR3300 (0.6)",startOfValidResponse) == 0)
                    compassIsInitialized = true;
                else 
                    compassIsInitialized = false;
            } else
                compassIsInitialized = false;
        } else
            compassIsInitialized = true;
*/
        // Now that the compass is under control, reenable its output.
        EnableCompassTransmission();

        // Test the compass interface by issuing a request that gives a known response.
//        compassIsInitialized = TestCompassComm();
        compassIsInitialized = true;

    }

    return compassIsInitialized;

}

const unsigned char Compass::CompassXmtEnaAddr = 0x80;
const unsigned short Compass::CompassXmtMask = 0x8000;

//----------------------------------------------------------------------------
void Compass::EnableCompassTransmission() {
    // Compass transmission output is controlled through the LSb of the first
    // word in the peripheral I/O address space.
    if (controller != NULL) {
        unsigned short digOut = controller->GetDigitalOutput(CompassXmtEnaAddr);
        digOut |= CompassXmtMask;
        controller->SetDigitalOutput(CompassXmtEnaAddr, digOut);
    }
}

//----------------------------------------------------------------------------
void Compass::DisableCompassTransmission() {
    if (controller != NULL) {
        unsigned short digOut = controller->GetDigitalOutput(CompassXmtEnaAddr);
        digOut &= ~CompassXmtMask;
        controller->SetDigitalOutput(CompassXmtEnaAddr, digOut);
    }
}

//----------------------------------------------------------------------------
bool Compass::TestCompassComm() {
    
//    FlushResponses(true);

    // send nonsense command
    SendCommand("*?");
    
    // Expect back a response indicating an invalid command
    char response[10];
    GetResponse(response);
    return (strcmp(response,"#I") == 0);

}

//----------------------------------------------------------------------------
void Compass::SetHeadingOutputMode() {
    SendCommand("*h");
}

//----------------------------------------------------------------------------
void Compass::SetMagnetometerOutputMode() {
    SendCommand("*m");
}

//----------------------------------------------------------------------------
void Compass::ToggleDataOutputMode() {
    SendCommand("*s");
}

//----------------------------------------------------------------------------
bool Compass::QueryData(float &val1, float &val2, float &val3) {
    char response[32];
    serial->FlushRecv();
    SendCommand("*q");
    if (!GetResponse(response)) return false;
    sscanf(response,"%f,%f,%f",&val1,&val2,&val3);
    return true;
}

//----------------------------------------------------------------------------
void Compass::RollAxisRezero() {
    SendCommand("*O");
}

//----------------------------------------------------------------------------
void Compass::PitchAxisRezero() {
    SendCommand("*P");
}

//----------------------------------------------------------------------------
bool Compass::QueryAveragedData(float &val1, float &val2, float &val3) {
    char response[32];
    SendCommand("*A");
    if (!GetResponse(response)) return false;
    sscanf(response,"%f,%f,%f",&val1,&val2,&val3);
    return true;
}

//----------------------------------------------------------------------------
void Compass::SplitFilterToggle() {
    SendCommand("*F");
}

//----------------------------------------------------------------------------
void Compass::Reset() {
//    SendCommand("*w");
    SendCommand("*r");
}

//----------------------------------------------------------------------------
void Compass::UserCalibration() {
    SendCommand("*C");
    printf ("move the compass over the expected full range of motion for one minute");
    PMDUtils::DoSleep(60000);
    SendCommand("*C");

    // Flush any data received while the compass was in calibration mode.
    serial->FlushRecv();
}

//----------------------------------------------------------------------------
void Compass::SetVariationInput(int variation) {
}

//----------------------------------------------------------------------------
void Compass::SetDeviationInput(int deviation) {
}

//----------------------------------------------------------------------------
void Compass::SetUserMagneticOffset(int x, int y, int z) {
}

//----------------------------------------------------------------------------
void Compass::SetBaudRate(int baud) {
    char cmd[10];
    sprintf(cmd,"#BAU=%d",baud);
    SendCommand(cmd);

    // The device must be reset after changing baud for the new baud to 
    // take effect.
    Reset();
}

//----------------------------------------------------------------------------
void Compass::SetSystemFilter(int filterValue) {
    char cmd[10];
    sprintf(cmd,"#SFL=%d",filterValue);
    SendCommand(cmd);
}

//----------------------------------------------------------------------------
void Compass::SetMagneticFilter(int filterValue) {
    char cmd[10];
    sprintf(cmd,"#MFL=%d",filterValue);
    SendCommand(cmd);
}

//----------------------------------------------------------------------------
void Compass::GetConfiguration( bool &magneticOutputSentenceSelected,
                                bool &headingOutputSentenceSelected, 
                                bool &temperatureBelowNeg10C,
                                bool &temperatureBelowNeg20C,
                                bool &splitFilterOn) {
    const int magneticOutputSentenceSelectedMask = 0x02;
    const int headingOutputSentenceSelectedMask = 0x08;
    const int temperatureBelowNeg10CMask = 0x10;
    const int temperatureBelowNeg20CMask = 0x20;
    const int splitFilterOnMask = 0x40;

    char response[10];
    SendCommand("#CON?");
    GetResponse(response);
    int respWord;
    sscanf(response,"%d",&respWord);
    magneticOutputSentenceSelected  = 
        (respWord & magneticOutputSentenceSelectedMask) > 0;
    headingOutputSentenceSelected   = 
        (respWord & headingOutputSentenceSelectedMask) > 0;
    temperatureBelowNeg10C = (respWord & temperatureBelowNeg10CMask) > 0;
    temperatureBelowNeg20C = (respWord & temperatureBelowNeg20CMask) > 0;
    splitFilterOn          = (respWord & splitFilterOnMask) > 0;
}

//----------------------------------------------------------------------------
void Compass::FlushResponses(bool displayFlushedResponses) {
    bool gotResponse = false;
    char response[32];
    do {
        gotResponse = GetResponse(response);
        if (displayFlushedResponses && gotResponse) 
            cout << "Flushed response: " <<response << endl;
    } while (gotResponse);
}

//----------------------------------------------------------------------------
void Compass::SendCommand(const char *str) {
    const unsigned long MinimumIntercommandTime = 50;   // in milliseconds
    if (compassChannelIsOpen) {

        // Ensure delay between commands to compass
#if defined WIN32
        DWORD currentTime = timeGetTime();
        DWORD elapsedTimeSinceLastCommand = currentTime - lastCommandTime;
        if (elapsedTimeSinceLastCommand < MinimumIntercommandTime)
            PMDUtils::DoSleep(MinimumIntercommandTime - elapsedTimeSinceLastCommand);
#else
        PMDUtils::DoSleep(MinimumIntercommandTime);  // Ensure delay between commands to compass
#endif

        // Issue command to compass.
        serial->Write((unsigned char *)str,strlen(str));
        serial->Write((unsigned char *)"\r\n",2);

#if defined WIN32
        lastCommandTime = timeGetTime();
#endif

    }
}

//----------------------------------------------------------------------------
bool Compass::GetResponse(char *response, int maxDelay) {
    unsigned char c[2];
    int i = 0, gotResponse = 2;
    bool gotCR = false;     // true if a carriage return is seen
    bool gotValidNonemptyResponse = false;
                            // true if a complete, nonempty response is seen
    do {
        if (serial->Read(c,1)) {
            if (isprint(*c)) response[i++] = *c;
            gotValidNonemptyResponse = (gotCR && *c == '\n' && i > 0);
            if (gotCR && *c == '\n' && i == 0) cout << "got empty msg \n";
            gotCR = (*c == '\r');
        } else {
            gotResponse--;
            // Only delay one time.
            if (gotResponse > 0) PMDUtils::DoSleep(maxDelay);
        }

    // Keep getting chars until a complete message or too much time has elapsed
    } while (!gotValidNonemptyResponse && gotResponse);   
    if (gotResponse) response[i] = '\0';   // Append string termination character
    return (gotResponse > 0);
}
