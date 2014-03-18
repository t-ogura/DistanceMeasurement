#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include <math.h>       // for sqrt()
#include <iostream>
#include <fstream>      // for ifstream
using namespace std;

#include "../include/PMDUtils.h"   // access to file parsing
#include "../include/PMDCollections.h"
#include "../include/Biclops.h"    // class being implemented here

//----------------------------------------------------------------------------
Biclops::Biclops() {
    for (int i=Pan;i<=Verge;i++) axes[i] = NULL;
    allAxesOnOneController = true;
    hasBeenInitialized = false;
}

//----------------------------------------------------------------------------
PMDAxisControl *Biclops::GetAxis(int axis) {
    if (axes[axis] == NULL) {
        const char *AxisUniqueIDLUT[4] = {"Pan", "Tilt", "Roll", "Verge"};
        GetAxis(AxisUniqueIDLUT[axis]);
    }
    return axes[axis];
}

//----------------------------------------------------------------------------
PMDAxisControl *Biclops::GetAxis(const char *axis) {
    AxisCollection *axisCollection = PMDAxes::Instance();
    PMDAxisControl *axisP = (*axisCollection)[axis];
    if (axisP != NULL)
        axes[axisP->GetAxisNumber()] = axisP;
    return axisP;
}

//----------------------------------------------------------------------------
bool Biclops::Initialize(const char *fileName) {

    if (!hasBeenInitialized) {
        hasBeenInitialized = PMDUtils::Initialize(fileName);

        // Get shortcuts to all the axes
        int i;
        for (i=Pan;i<=Verge;i++) GetAxis(i);

        // Determine if all the axes are on the same controller. 
        // This result is used by the Move() command to know whether a MoveMultiple
        // is possible.
        if (hasBeenInitialized) { 
            PMDController *controller = axes[Pan]->GetController();
            for (i=Tilt;i<=Verge;i++)
                if (axes[i] != NULL)
                    allAxesOnOneController = allAxesOnOneController &&
                                             (axes[i]->GetController() == controller);
        }
    }
    return hasBeenInitialized;
}

//----------------------------------------------------------------------------
bool Biclops::HomeAxes(int axisMask, bool forceHoming) {

    bool panStat = true,tiltStat = true, rollStat = true, vergeStat = true;

    // Homing order is always tilt, roll, verge, pan
    // The logic for each axis is: the axis must be requested to be homed
    // and the axis must be controllable (chipset has that axis) and then
    // find home if forced to or the axis is not already homed.
    if (axisMask & RollMask && axes[Roll] != NULL)  
        rollStat  = axes[Roll]->FindHome(forceHoming);
    if (axisMask & TiltMask && axes[Tilt] != NULL)  
        tiltStat  = axes[Tilt]->FindHome(forceHoming);
    if (axisMask & VergeMask && axes[Verge] != NULL)  
        vergeStat = axes[Verge]->FindHome(forceHoming);
    if (axisMask & PanMask && axes[Pan] != NULL)  
        panStat  = axes[Pan]->FindHome(forceHoming);

    return (panStat && tiltStat && rollStat && vergeStat);

}

//----------------------------------------------------------------------------
bool Biclops::Move(int axisMask, long waitPeriod) {
    PMDuint16 stat;
    PMDAxis axis;

    if (allAxesOnOneController) {

        // To utilize the MultiUpdate command, we essentially have to replicate
        // the PMDAxisControl::Move() method logic here for making sure the
        // axis is in the correct state for moving. 
//        for (axis = PMDAxis1; axis <= PMDAxis4; axis++) {
//            if (axisMask & 1<<axis) {
//                axes[axis]->PreMove(waitPeriod != 0);
////                PMDuint16 eventStatus = axes[axis]->GetLastEventStatus();
////                stat = axes[axis]->ResetEventStatus(PMDAxisControl::MoveEventMask);
////                if (eventStatus & PMDEventMotionErrorMask)
////                    stat = axes[axis]->SetMotorMode(PMDMotorOn);
//            }
//        }

        // Now the axes motion can begin.
        GetAxis(Pan)->MultiUpdate(axisMask);

        for (axis = PMDAxis1; axis <= PMDAxis4; axis++)
            if (axisMask & 1<<axis)
                axes[axis]->PostMove();

    } else {

        // Since axes are on more than one controller, just issue the move
        // command on each axis with no wait time and let the follow-on loop
        // do the actual waiting.
        
        // But first, the event status must be cleared if this multi-axis move
        // wants to wait for motion completion.
        if (waitPeriod > 0)
            for (axis = PMDAxis1; axis <= PMDAxis4; axis++)
                if (axisMask & 1<<axis)
                    axes[axis]->ResetEventStatus(PMDAxisControl::MoveEventMask);

        // Okay, now we can command the moves.
        for (axis = PMDAxis1; axis <= PMDAxis4; axis++) 
            if (axisMask & 1<<axis) axes[axis]->Move(false);

    }


    // Wait for all motion to complete if desired.
    if (waitPeriod > 0) {
        for (axis = PMDAxis1; axis <= PMDAxis4; axis++) {
            if (axisMask & 1<<axis) {
                while (!GetAxis(axis)->IsMotionDone()) {
                    PMDUtils::DoSleep(waitPeriod);
                }
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------------
bool Biclops::AnAxisIsPowered() {
    bool anAxisIsPowered = false;
    for (PMDAxis axis = PMDAxis1; axis <= PMDAxis4; axis++) {
        if (axes[axis] != NULL)
            anAxisIsPowered = anAxisIsPowered || axes[axis]->IsAmpEnabled();
    }
    return anAxisIsPowered;
}

//----------------------------------------------------------------------------
void Biclops::SetDebugLevel(int level) {

    for (int axis = Pan; axis <=Verge; axis++)
        if (axes[axis] != NULL)
            axes[axis]->GetController()->SetDebugLevel(level);
}
