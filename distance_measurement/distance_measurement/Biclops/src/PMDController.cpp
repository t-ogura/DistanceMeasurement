#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include <iostream>         // for cout
using namespace std;
#include <string.h>         // for strcpy_s
#include <cstdio>          // For sccanf definition
//#include <stdio.h>          // For sccanf definition
#include <typeinfo>

#include "../include/PMDUtils.h"       // for parsing routines
#include "../include/PMDCollections.h" // for access to Axes collection
#include "../include/PMDController.h"  // class being implemented here

// Debug declarations
const char* PMDController::classStr = "PMDController::";
#define dbgCout cout << classStr << methodStr 
#define ifDbgCout if (GetDebugLevel() > 0) dbgCout

const char *PMDController::StartToken = "[controller]";
const char *PMDController::EndToken = "[/controller]";

//----------------------------------------------------------------------------
PMDController::PMDController() {
    SetDefaults();

    // Use of the default constructor implies desire to use the default 
    // communication mechanism as well, which is currently a serial port using
    // the same defaults that the PMD controller uses.
    ioTransport = NULL;

} 

//----------------------------------------------------------------------------
PMDController::PMDController(PMDIOTransport *ioTransport) {

    SetDefaults();

    // Record the transport mechanism and indicate that it came from
    // and external source.
    this->ioTransport = ioTransport;

    for (int axis = 0; axis < PMDMaxAxes; axis++) axes[axis] = NULL;
}

//----------------------------------------------------------------------------
void PMDController::SetDefaults() {
    debugLevel = 0;
    ioTransport = NULL;
    primaryAxis = NULL;
    axisCount = 0;
    axisCollection = new AxisCollection;

    // Clear the digital outputs
    for (int i = 0; i < 256; i++) digitalOutput[i] = 0;

    // Make sure all axis references start out empty.
    for (int axis = 0; axis < PMDMaxAxes; axis++) axes[axis] = NULL;

    brakeState = 0;

    // Set cycle time to the slowest necessary rate assuming only 
    // 1 axis is running and the longest minimum cycle period.
    // Once the controller is accessible this value will be overwritten
    // with the default value pulled from the controller chip itself.
    cyclePeriodInUSec = (PMDuint16)(
                        PMDAxisControl::ExtendedControllerCycleMin *
                        PMDAxisControl::CyclePeriodStepSizeInUSec);
}

//----------------------------------------------------------------------------
PMDController::PMDController(FILE *file, char *token) {

    // Initialize this instance with the defaults.
    SetDefaults();

    // Load values from the configuration file.
    ReadParameters(file,token);
}

//----------------------------------------------------------------------------
PMDAxisControl* PMDController::GetAxis(char *axis) {
    AxisCollection::iterator it = axisCollection->find(axis);
    if (it == axisCollection->end()) return NULL;
    else return it->second;
//        return (*axisCollection)[axis];
}

//----------------------------------------------------------------------------
void PMDController::AddAxis(PMDAxisControl* axis) {

    // Record this axis in the indexable axis table.
    int axisNumber = axis->GetAxisNumber();
    axes[axisNumber] = axis;

    // Add the axis to the string-searchable axis collection.
    (*axisCollection)[axis->uniqueID] = axis;

    // Connect the axis to this controller's transport mechanism.
    axis->SetIOTransport(ioTransport);

    // Create a shortcut to the primary axis if this is it.
    if (axisNumber == 0) {
        primaryAxis = axis;
        if (typeid(PMDSerial) == typeid(*ioTransport))
            ((PMDSerial *)ioTransport)->SetPrimaryAxisInterface(axis);
    }
}

//----------------------------------------------------------------------------
void PMDController::SetIOTransport(PMDIOTransport *ioTransport) {
    this->ioTransport = ioTransport;
    for (int axis = 0; axis < PMDMaxAxes; axis++)
        if (axes[axis] != NULL) 
            axes[axis]->SetIOTransport(ioTransport);
}

//----------------------------------------------------------------------------
void PMDController::ReadParameters(FILE *file, char *token) {

    // Define the tokens used here.
    const char TokenDebugLevel[] = "debugLevel";

    bool tokenRecognized = true;
    unsigned int val;

    // Prime token stream.
    PMDUtils::ReadToken(file,token);

    // Parse the stream.
    do {
        if (!strcmp(token,PMDUtils::TokenUniqueID)) {
            PMDUtils::ReadToken(file,token);
            strcpy_s(uniqueID,token);
        } else if (!strcmp(token,TokenDebugLevel)) {
            PMDUtils::ReadToken(file,token);
            if (sscanf_s(token,"%u",&val) == 1) {
                SetDebugLevel(val);
            } else tokenRecognized = false;
        } else if (!strcmp(token,PMDSerial::StartToken)) {
            ioTransport = new PMDSerial(file,token);
            if (!strcmp(token,PMDSerial::EndToken)) {
                ((PMDSerial *)ioTransport)->GetNetwork()->
                    AddController(uniqueID,this);
            } else 
                tokenRecognized = false;
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}

//----------------------------------------------------------------------------
bool PMDController::Connect() {
//    char methodStr[] = "Connect: ";

    return ioTransport->Open();
}

//----------------------------------------------------------------------------
void PMDController::Disconnect() {
    //%%%%%%%%%%%%%%%%%%%%%% not sure what to do here
//    primaryAxis->transport->mTransport->Close();
}

//----------------------------------------------------------------------------
bool PMDController::IsConnected() {
    return ioTransport->IsReady();
}

//----------------------------------------------------------------------------
bool PMDController::ChangeComm(int baud) {

    // Change the host interface settings to match.
    PortableSerial *comm = 
        ((PMDSerial *)ioTransport)->GetNetwork()->GetSerial();
    char portName[32];
    int oldBaud;
    PortableSerial::Parity parity;
    PortableSerial:: StopBits stopBits;
    comm->GetConfig(portName,oldBaud,parity,stopBits);
    comm->SetConfig(portName,baud,parity,stopBits);
    return ((PMDSerial *)ioTransport)->Open();
}

//----------------------------------------------------------------------------
bool PMDController::ResetController() {

    char methodStr[] = "ResetController: ";
    // A reset command to any axis of the chipset affects all axes of that
    // chipset, so arbitrarily send the reset command to the first axis.
	// If more than one chip set is present, all of them should be
	// reset here
	PMDuint16 result = primaryAxis->Reset();

	// after the reset the chip will be in the PMDChipsetReset state
	PMDuint16 error;
	result = primaryAxis->GetHostIOError(error);

	// the above command should execute without error but we need to check
	if ( (result != PMD_ERR_OK) || (error != PMD_ERR_ChipsetReset) ) {
        ifDbgCout << "Error: " << PMDUtils::GetErrorMessage(result) << endl;
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------
bool PMDController::ConfigureController() {

//    char methodStr[] = "Configure: ";

    // Determine the number of axes on the controller
    PMDuint16 productFamily,motorType,specialAttributes,customizationCode,
        majorSWVersion,minorSWVersion;
    primaryAxis->GetVersion(
        productFamily,motorType,axisCount,specialAttributes,customizationCode,
        majorSWVersion,minorSWVersion);

    // Create additional axes if the axis count for this controller is greater
    // than one.
    PMDAxis axis;

    // Create the number of axis instances consistent with the quantity the
    // current controller supports. Avoid overwriting instances that have
    // already been populated.
    for (axis = 0; axis < axisCount; axis++) 
        if (axes[axis] == NULL)
            axes[axis] = new PMDAxisControl(this,ioTransport,axis);


    // Clear all axes that are unallowable
    for (; axis <= PMDAxis4; axis++)
        if (axes[axis] != NULL) {
            // Eliminate the axis from all collections.
            PMDAxes::Instance()->erase(axes[axis]->uniqueID);
            axisCollection->erase(axes[axis]->uniqueID);
            axes[axis] = NULL;
        }

    // Get the true sample time from the chip and record it's value for 
    // future calculations.
    primaryAxis->GetSampleTime(cyclePeriodInUSec);

/*    //test code
    PMDint32 int32;
    PMDuint16 uint16;
    while (1) {
        primaryAxis->GetSignalStatus(uint16);
        PMDUtils::DoSleep(250);
    }
    // end test code
*/
    ConfigureAxes();

    return true;
}

//----------------------------------------------------------------------------
bool PMDController::ConfigureAxes() {
    bool success = true;
    for (int axis = PMDAxis1; axis <= axisCount; axis++)
        if (axes[axis] != NULL)
            success = success && axes[axis]->ConfigureHardware();
    return success;
}

//----------------------------------------------------------------------------
void PMDController::SetDebugLevel(int level) {
    debugLevel = level;
    for (int axis = PMDAxis1; axis <= PMDAxis4; axis++)
        if (axes[axis] != NULL)
            axes[axis]->SetDebugLevel(level);
}

//----------------------------------------------------------------------------
unsigned short PMDController::GetDigitalOutput(unsigned char address) {
    return digitalOutput[address];
}

//----------------------------------------------------------------------------
void PMDController::SetDigitalOutput(unsigned char address, unsigned short data) {
    primaryAxis->WriteIO(address,data);
}

