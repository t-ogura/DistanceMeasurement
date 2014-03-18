#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include <sstream>
#include <iostream>
#include <fstream>     // for homing file reading
using namespace std;

#include <math.h>       // for pow() 
#include <limits.h>	    // for LONG_MIN, LONG_MAX defs
#include "../include/PMDUtils.h"   
#include "../include/PMDOPCodes.h" // for exception handling

#include "../include/PMDCollections.h" // for access to controller collection
#include "../include/PMDController.h"  // need access to controller for comm
#include "../include/PMDAxisControl.h" // class being implemented here

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

// Debug declarations
const char* PMDAxisControl::classStr = "PMDAxisControl";
#define dbgCout cout << classStr << "(" << (int)ctrlID << 'x' << GetAxisNumber() <<  ")::" << methodStr 
#define ifDbgCout if (GetDebugLevel() > 0) dbgCout

PMDuint16 rslt; // Status result returned from all PMD functions.
#define TRYPMDCMD(cmd,exception) if ((rslt = cmd) != PMD_ERR_OK) throw exception;

const double PMDAxisControl::CyclePeriodStepSizeInUSec = 51.2;
const int PMDAxisControl::NormalControllerCycleMin = 2;
const int PMDAxisControl::ExtendedControllerCycleMin = 3;
const PMDuint16 PMDAxisControl::BrakeIOAddress = 0;
const PMDuint16 PMDAxisControl::AutostopEventMask = 
                PMDEventMotionErrorMask | 
                PMDEventInPositiveLimitMask |
                PMDEventInNegativeLimitMask;
const PMDuint16 PMDAxisControl::MoveEventMask = 
                PMDAxisControl::AutostopEventMask | 
//				PMDEventCaptureReceivedMask |
                PMDEventMotionCompleteMask;
const char *PMDAxisControl::StartToken = "[axis]";
const char *PMDAxisControl::EndToken = "[/axis]";

//----------------------------------------------------------------------------
PMDAxisControl::PMDAxisControl( PMDController *controller,
                                PMDIOTransport *pmdIOTransport, 
                                PMDAxis axis) : 
    PMD(pmdIOTransport,axis) {
    this->controller = controller;

    // Choose a default name for this axis.
    stringstream stream(stringstream::in | stringstream::out);
    stream << controller->uniqueID << ":Axis" << GetAxisNumber();
    stream >> uniqueID;

    SetDefaults();

    // Inherit the debug level from the controller.
    SetDebugLevel(controller->GetDebugLevel());

}

//----------------------------------------------------------------------------
PMDAxisControl::PMDAxisControl(FILE *file, char *token) {

    // Initialize this instance with the defaults.
    SetDefaults();

    // Load values from the configuration file.
    ReadParameters(file,token);

    // Inherit the debug level from the controller.
    SetDebugLevel(controller->GetDebugLevel());

    // Load the controller ID # for use by debug messages.
    tagPMDSerialProtocol protocol;
    ((PMDSerial *)controller->GetIOTransport())->GetProtocol(protocol,ctrlID);

}

//----------------------------------------------------------------------------
void PMDAxisControl::SetDefaults() {

    ctrlID = 0;
    debugLevel = 0;
    eventStatus = 0;
    signalSense = 0;
    eventStatusLoadedSinceLastMove = false;

    // Actuator defaults
    hasBrake = false;
    brakeState = 0;  // Failsafe brakes default to engaged
    ampType = PMDMotorOutputPWMSignMagnitude;
    ampPolarity = ActiveHigh;
    ampIsOn = false;        // desired power-on condition, but...
    isBrushless = false;
    poleCount = 6;
    phaseInitMode = PMDPhaseInitAlgorithmic;
    invertHalls = false;
    commutationMode = PMDCommutationModeHallBased;

    // Encoder defaults
    countsPerEncoderCycle = 2000;   // run-of-the-mill 500 count encoder
    encoderCyclesPerAxisCycle = 1;
    motorCyclesPerEncoderCycle = 1;
    countsPerAxisCycle = countsPerEncoderCycle*encoderCyclesPerAxisCycle;
    countsPerMotorCycle = countsPerEncoderCycle*motorCyclesPerEncoderCycle;
    rangeOfMotion = (unsigned long)countsPerAxisCycle;  // default to 1 axis cycle
    reverseMotorOutput = false;

    // Homing defaults
    homingMode = NoHoming;
    isHomed = false;
    homeCountsOffset = 0;
    hasLimitSensors = false;
    hasHardLimits = true;
    hasHomeSensor = false;
    homeSignalPolarity = ActiveLow;   // PMD chipset default
    limitSignalPolarity = ActiveLow;   // PMD chipset default
    limitsMayBind = false;
    reverseLimit = softReverseLimit = LONG_MIN;
    forwardLimit = softForwardLimit = LONG_MAX;
    homeDelta = 0;
    waitPeriod = 100;

    ServoFilter defaultFilter = {0,0,0,0,0,0,0,0,0,0};
    CountsProfile defaultProfile = {0,1,1,0,0};
    SetFilter(defaultFilter,true);
    SetProfile(defaultProfile,true);
    runFilter = defaultFilter;
    CountsToProfile(runProfile,defaultProfile);

    configurationWasLoaded = false;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::ConfigureHardware() {

    char methodStr[] = "ConfigureHardware: ";
    PMDint32 pos;

    // Skip configuration process if axis parameters were never loaded.
    if (!configurationWasLoaded) return true;

    try {

        ResetEventStatus(~MoveEventMask);
        // Configure the axis out pin to drive the motor amplifier output 
        // enable signal.
        // The trick to doing this is to tell the controller not to tie the
        // axis out pin to any internal register bit and then drive the pin 
        // by alternating its "signal sense" command, as implemented in the
        // EnableAmp/DisableAmp methods.
        SetAxisOutSource(GetAxisNumber(),0,PMDAxisOutSourceNone);
    
        // Make sure the brake is enabled.
        EngageBrake();
//        DisengageBrake();
//        PMDUtils::DoSleep(2500);
//        EngageBrake();

        // Turn off the motor amplifier and closed loop control initially.
        SetMotorMode(PMDMotorOff);
        DisableAmp();

        if (false) {
            PMDuint16 val;
            SetCaptureSource(PMDCaptureSourceHome);
            ResetEventStatus(~PMDEventCaptureReceivedMask);
            GetCaptureValue(pos);   // re-arm
            int i;
            for (i = 0; i < 40; i++) {
                GetActivityStatus(val);
                PMDUtils::DoSleep(250);
            }
            for (i = 0; i < 40; i++) {
                GetSignalStatus(val);
                PMDUtils::DoSleep(250);
            }
        }

        if (false) {
            // Encoder direction test
            cout << "Encoder direction test\n";
            cout << "Move axis " << GetAxisNumber() << " to determine + direction\n";
            DisengageBrake();
            for (int i = 0; i < 40; i++) {
                GetActualPosition(pos);
                cout << "Actual pos " << pos << endl;
                PMDUtils::DoSleep(250);
            }
            EngageBrake();
        }

        // Get the current signal sense of the axis from the controller. 
        // This value is modifed throughout the remainder of the
        // configuration process.
        GetSignalSense(signalSense);

        // Set up the hardware limit switch mode and limit signal sense.
        tagPMDLimitMode limitSwitchMode = 
            hasLimitSensors ? PMDLimitEnabled: PMDLimitDisabled;
        SetLimitSwitchMode(limitSwitchMode);

        // Set up encoder parameters as incremental with index active low.
        // The default encoder is usually an Agilent HEDS-5540.
        SetEncoderSource(PMDEncoderSourceIncremental);
        signalSense |= PMDSignalEncoderIndexMask;
        SetSignalSense(signalSense);

        // Set the rotation direction of the motor relative to the encoder
        if (reverseMotorOutput)
            signalSense |= PMDSignalMotorOutputInvertMask;
        else
            signalSense &= ~PMDSignalMotorOutputInvertMask;
        SetSignalSense(signalSense);


        // Set the home & limit sensor signal's active sense
        // NOTE: the home and limit signals should have the same logic,
        // but I don't want to mess up the working home logic right now (BTW).
        if (homeSignalPolarity == ActiveHigh)
            // Invert signal from PMD default
            signalSense |= PMDSignalEncoderHomeMask;
        else
            signalSense &= ~PMDSignalEncoderHomeMask;
        if (limitSignalPolarity == ActiveHigh)
            // Invert limit signals so they are asserted high 
            // when the input signal goes low.
            signalSense |=  PMDSignalPositiveLimitMask |
                            PMDSignalNegativeLimitMask;
        else
            // Make sure the limit signals are stored in the signal status
            // register with the same logic level as they are from the sensor.
            signalSense &= ~(PMDSignalPositiveLimitMask |
                             PMDSignalNegativeLimitMask);
        SetSignalSense(signalSense);

        // Set the motor output mode (either PWM50/50 or sign/magnitude).
        SetOutputMode(ampType);


        // If this axis has a brushless motor, configure the controller 
        // accordingly. Refer to the Pilot User's Guide, section 12.7.2 
        // Hall-based Initialization Sequence, for command sequence explanation.
        // Also, don't need to do this if the axis has already been homed.
        if (isBrushless && !IsAlreadyHomed()) {

            // TESTING
            if (false) {
                SetPhaseInitializeMode(1);
                SetPhaseCounts(933);
                GetSignalSense(signalSense);
                signalSense |= PMDSignalMotorOutputInvertMask;
                SetSignalSense(signalSense);
                SetPhaseCorrectionMode(0);
                SetMotorMode(0);
                InitializePhase();
                SetMotorMode(0);
                SetMotorCommand(-6000);
                EnableAmp();
                Update();
                PMDUtils::DoSleep(2000);
                SetMotorCommand(6000);
                Update();
                PMDUtils::DoSleep(2000);
                SetMotorCommand(0);
                Update();
                DisableAmp();
            }
            // END TESTING

            // Set hall signal sense.
            if (invertHalls)
                signalSense |= PMDSignalHallAMask | PMDSignalHallBMask | PMDSignalHallCMask;
            else
                signalSense &= ~(PMDSignalHallAMask | PMDSignalHallBMask | PMDSignalHallCMask);
            SetSignalSense(signalSense);

            // Always 3 phase brushless.
            SetNumberPhases(3);

            // Set encoder counts/motor phase
            SetPhaseCounts((PMDuint16)(countsPerMotorCycle/(poleCount/2)));

            // Enable index pulse phase correction if encoder counts/motor rev
            // is not an integer multiple of the motor's electrical cycles
            // WARNING: This logic has been commented out because phase 
            // correction will not work if the encoder pulse occurs more 
            // than once per motor rotation. Since our typical application
            // doesn't rotate an axis more than one or two revolutions, 
            // disabling index pulse phase correction should be okay even if
            // the encoder counts/rev is not an integer multiple of the poles
//            if (((int)(countsPerMotorCycle/(poleCount/2)))*(poleCount/2) ==
//                (int)countsPerMotorCycle)
            SetPhaseCorrectionMode(PMDPhaseCorrectionDisabled);
//            else
//                SetPhaseCorrectionMode(PMDPhaseCorrectionEnabled);

            // Set the commutation mode. Sinusoidal 
            // commutation requires encoder feedback with an index pulse if the
            // number of encoder counts/rev is not evenly divisible by half the
            // number of rotor magnetic poles. See Pilot User's Guide section 12.4
            // for further details.
            SetCommutationMode(commutationMode);

            // Only need to do phase initialization for sinusoidal commutation.
            if (commutationMode == PMDCommutationModeSinusoidal) {

                // Select the phase initialization mode.
                SetPhaseInitializeMode(phaseInitMode);
                SetMotorMode(PMDMotorOff);
                if (phaseInitMode == PMDPhaseInitAlgorithmic) {
                    // Prepare axis for algorithmic phase initialization motion.
                    SetPhaseInitializeTime(3000);
                    SetMotorCommand(6000);
                    EnableAmp();
                    DisengageBrake();
                }

                // Initialize phasing and wait for it to complete if algorithmic.
                InitializePhase();
                if (phaseInitMode == PMDPhaseInitAlgorithmic) {
                    PMDuint16 activityStatus;
                    do {
                        GetActivityStatus(activityStatus);
                        PMDUtils::DoSleep(250);
                    } while (!(activityStatus & (1<<PMDActivityPhasingInitializedBit)));
                    EngageBrake();
                    DisableAmp();
                }
            }

            // Display detected phase offset (only valid if index was seen).
//            PMDuint16 phaseOffset;
//            GetPhaseOffset(phaseOffset);
//            cout << "phase offset = " << phaseOffset << endl;

        }

        // Test motor motion.
        if (false) {
            SetMotorMode(PMDMotorOff);
            EnableAmp();
            DisengageBrake();

            int motorCommand = 10000;
            int moveTimeinMSec = 1500;
            SetMotorCommand(motorCommand);
            Update();
            PMDUtils::DoSleep(moveTimeinMSec);
            SetMotorCommand(0);
            Update();
            PMDUtils::DoSleep(moveTimeinMSec);
            SetMotorCommand(-motorCommand);
            Update();
            PMDUtils::DoSleep(2*moveTimeinMSec);

            SetMotorCommand(0);
            Update();
            EngageBrake();
            DisableAmp();
        }

/* I don't think this is necessary after all.
        // Make sure the profiler is commanded to the same position at which 
        // the axis currently sits. This step allows the software to 
        // "synchronize" with the hardware axis position if it is nonzero
        // to prevent lurching to the nonzero position when the axis is first
        // powered.
        GetActualPosition(pos);
        SetPosition(pos);
        Update();
*/
        // Set the profile mode and start closed loop control.
        SetProfileMode(PMDTrapezoidalProfile);
        SetAxisMode(PMDAxisOn);
    } catch (int cmd) {
        ifDbgCout << "exception while commanding " << cmd << endl; 
    }
    return (rslt == PMD_ERR_OK);
}

//----------------------------------------------------------------------------
void PMDAxisControl::GetFilter(ServoFilter& sp, bool homing) {
    if (homing) sp = homingFilter;
    else        sp = activeFilter;
}

//----------------------------------------------------------------------------
void PMDAxisControl::SetFilter(const ServoFilter& sp, bool homing) {
    
    char methodStr[] = "SetFilter: ";

    if (homing) {
        
        // For homing, just record the values in the homing structure for 
        // use when homing is executed.
        homingFilter = sp;
        
    }
    else {
        
        // Send the control parameter values directly to the controller.
        try {
            SetKp(sp.kP);
            SetKd(sp.kD);
            SetKi(sp.kI);
            SetKvff(sp.kVFF);
            SetKaff(sp.kAFF);
            SetKout(sp.kOut);
            SetIntegrationLimit(sp.integrationLimit);
            SetMotorLimit(sp.motorLimit);
            SetMotorBias(sp.motorBias);
            SetPositionErrorLimit(sp.errorLimit);
        
            rslt = Update();

            // Record the new values being commanded for future reference.
            activeFilter = sp;
        } catch (int cmd) {
            ifDbgCout << "exception while commanding " << cmd << endl; 
        }

    }
}

//----------------------------------------------------------------------------
void PMDAxisControl::GetProfile(Profile& profile, bool homing) {
    if (homing) {
        profile = homingProfile;
    }
    else {
        profile = cmdProfile;
    }
}

//----------------------------------------------------------------------------
void PMDAxisControl::GetProfile(CountsProfile& profile, bool homing) {
    if (homing) {
        profile = homingProfileCounts;
    }
    else {
        profile = cmdProfileCounts;
    }
}

//----------------------------------------------------------------------------
void PMDAxisControl::SetProfile(const Profile& profile, bool homing,
                                bool doLoad) {
    if (homing) {
        homingProfile = profile;
        ProfileToCounts(profile,homingProfileCounts);
        // Probably need to test the homing values to make sure they are within
        // acceptible limits, e.g., motorLimit <= 3/4 of max motorLimit
    }
    else {

        // Convert the new profile to counts.
        CountsProfile countsProfile;
        ProfileToCounts(profile, countsProfile);
        if (CropProfile(countsProfile)) {

            // Conversion to counts had at least one parameter that does not
            // match the original profile after conversion. Make the reverse
            // conversion and store this as the actual profile being used.
            CountsToProfile(cmdProfile,countsProfile);

        } else {

            // Store the profile as it was commanded.
            cmdProfile = profile;

        }

        // Transfer the new profile to the controller if desired.
        if (doLoad) SendProfileToController(countsProfile);

    }
}

//----------------------------------------------------------------------------
void PMDAxisControl::SetProfile(const CountsProfile& profile, bool homing,
                                bool doLoad) {
    if (homing) {
        homingProfileCounts = profile;
        CountsToProfile(homingProfile, profile);
        // Probably need to test the homing values to make sure they are within
        // acceptible limits, e.g., motorLimit <= 3/4 of max motorLimit
    }
    else {

        // Make sure the profile is within limits.
        CountsProfile countsProfile = profile;
        CropProfile(countsProfile);

        // Convert the possibly cropped profile from counts to world units.
        CountsToProfile(cmdProfile, countsProfile);

        // Transfer the new profile to the controller if desired.
        if (doLoad) SendProfileToController(countsProfile);

    }
}

//----------------------------------------------------------------------------
bool PMDAxisControl::CropProfile(CountsProfile& profile) {
    
    // For now just check for position limits. 
    // Future versions will have checks for velocity and acceleration.

    // Don't do cropping unless the limits are different.
    PMDint32 pos = profile.pos;
    if (forwardLimit != reverseLimit) {
        profile.pos = min(softForwardLimit,max(softReverseLimit,profile.pos));
    }
    return (pos != profile.pos);
}

//----------------------------------------------------------------------------
bool PMDAxisControl::IsAlreadyHomed() {

    // If homing has not occured since this application started, test the 
    // controller for the flag indicating the axis has been homed since the
    // last reset.
    if (!isHomed) {
        if (controller->IsConnected()) {
            PMDuint16 captureSource;
            GetCaptureSource(captureSource);
            if (captureSource == PMDCaptureSourceHome) {
                // Homing has occured successfully since the last reset/power 
                // cycle of the controller. Try loading the homing parameters
                // from a file automatically generated after successful homing
                // completion.
                isHomed = ReadAxisStateFromFile();
        }
        }
    }
    return isHomed;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::AxisKnowsPosition() {
    PMDuint16 captureSource;
    GetCaptureSource(captureSource);
    return (captureSource == PMDCaptureSourceHome);
}

//----------------------------------------------------------------------------
bool PMDAxisControl::FindHome(bool forceHoming) {
    PMDuint16 rslt;
    char methodStr[] = "FindHome: ";
    bool homingWasSuccessful = false;

    if (forceHoming || !IsAlreadyHomed()) {
        ifDbgCout << "Begin homing sequence for axis \n";

        // Set the axis gains for homing.
        ifDbgCout << "Loading homing gains and profile\n";
        SetFilter(homingFilter);

        // Since the current axis position is unknown, define it to be at zero.
		PMDint32 position;
		rslt = GetActualPosition(position);
        ifDbgCout << "declare current axis position (" << position << ") to be 0\n";
        rslt = SetActualPosition(0);

        // Ensure the axis will not move when closed loop control is enabled.
        SetPosition(0);
        SetVelocity(0);
        Update();

        // Turn on the motor amplifier.
        ifDbgCout << "Enable motor\n";
        EnableAmp();

        // Start closed loop control with the specified profiling mode.
        rslt = SetProfileMode(PMDTrapezoidalProfile);
        rslt = SetMotorMode(PMDMotorOn);

        // Release the brake (if it exists)
        DisengageBrake();

        // Prepare to find the limits of travel by presetting the limits to extremes.
        reverseLimit = softReverseLimit = LONG_MIN;
        forwardLimit = softForwardLimit = LONG_MAX;

        // Start the actual homing process
        switch (homingMode) {
        case ReverseLimit:
        case ForwardLimit:
        case BothLimits:
            homingWasSuccessful = FindHomeWithLimits();
            break;
        case HomeAndIndex:
            homingWasSuccessful = FindHomeWithHomeSensor();
            break;
        default: // case NoHoming
            SetHomingLimits(0,0,0,0);
            homingWasSuccessful = true;
        }
        ifDbgCout << "End homing sequence for axis \n";
    } else {
        // Since a homing sequence wasn't necessary, just ensure that 
        // closed loop control is enabled.
        rslt = SetMotorMode(PMDMotorOn);
        EnableAmp();
        DisengageBrake();
        homingWasSuccessful = true;
    }

    // Record the fact that this axis is homed.
    // This is done by setting the chip's capture source to "home" 
    // because the chip default capture source is index and this signal
    // is not used for normal operation so having it set to a non 
    // default value is a persistent indication that homing was successful.
    if (homingWasSuccessful) {
        rslt = SetCaptureSource(PMDCaptureSourceHome);
        WriteAxisStateToFile();
        isHomed = true;
		ifDbgCout << "Homing was successful.\n";
		ifDbgCout << "New range of motion is " << softReverseLimit <<
			" .. " << softForwardLimit << "\n";
    }

    // With homing complete, stop movement if a motion error occurs.
    rslt = SetAutoStopMode(PMDAutoStopEnabled);

    // At the completion of homing, load the run-time servo filter
    // and velocity profile and move to the run profile's start position.
    SetFilter(runFilter);
    SetProfile(runProfile);
    unsigned long oldPeriod = GetMoveWaitPeriod();
    SetMoveWaitPeriod(250);
    Move();
    SetMoveWaitPeriod(oldPeriod);

    return true;

}


//----------------------------------------------------------------------------
void PMDAxisControl::GoToLimit(CountsProfile &p) {

    char methodStr[] = "GoToLimit: ";
    bool moveCompletedSuccessfully;

    // If limit sensors exist then that's what defines the limit sought.
    // Set the capture source
    if (hasLimitSensors) {

        // Move away from the limit sensor if it is inactive.
        WithdrawFromLimit(p);

    }

    // Move toward the goal
    SetProfile(p);
    GetActualPosition(actProfileCounts.pos);
    unsigned long oldPeriod = GetMoveWaitPeriod();
    SetMoveWaitPeriod(500);
    moveCompletedSuccessfully = Move();
    SetMoveWaitPeriod(oldPeriod);

    // Record limit position
    GetActualPosition(actProfileCounts.pos);

    if (moveCompletedSuccessfully) {
        ifDbgCout << "Desired goal attained at " << actProfileCounts.pos 
                  << "; presume limit not found\n";
    } else {
        ifDbgCout << "Motion interrupted at " << actProfileCounts.pos 
                  << "; presume limit was found\n";
    }

    // Now disable the axis if a motion error occured.
//    if (eventStatus & PMDEventMotionErrorMask)
//        SetMotorMode(PMDMotorOff);

    // Back off of the limit
    WithdrawFromLimit(p);
}

//----------------------------------------------------------------------------
void PMDAxisControl::WithdrawFromLimit(CountsProfile &p) {
    char methodStr[] = "WithdrawFromLimit: ";

    unsigned long oldPeriod = GetMoveWaitPeriod();
    SetMoveWaitPeriod(500);
    if (hasLimitSensors) {

        // Determine if both limits are asserted (an indication that both
        // limits are attached to the same physical switch/sensor).
        GetSignalStatus(signalStatus);
        bool bothLimitsAreAsserted = 
            !(signalStatus & PMDSignalPositiveLimitMask) &&
            !(signalStatus & PMDSignalNegativeLimitMask);
        if (bothLimitsAreAsserted) {
            // Disable limit sensor mode until after the move so that neither
            // sensors is active. Otherwise, the controller will not allow a 
            // move in either direction.
            SetLimitSwitchMode(PMDLimitDisabled);
        }

        // Record commanded pos for later replacement.
        PMDint32 lastCommandedPos = p.pos;

        // Compute direction and distance to "withdrawl" from limit sensors.
        GetActualPosition(p.pos);
        int posDelta = rangeOfMotion/10;    // move 10% of full range away from sensor
        if (lastCommandedPos > p.pos) posDelta = -posDelta;

        // Only withdrawl from limit sensor if the active sensor is in the
        // opposite direction of the desired withdrawl.
        if (posDelta > 0 && !(signalStatus & PMDSignalNegativeLimitMask) ||
            posDelta < 0 && !(signalStatus & PMDSignalPositiveLimitMask)) {
            ifDbgCout << "Withdrawling from current pos because a limit sensor" 
                      << " is asserted.\n";
            p.pos += posDelta;
            SetProfile(p);
            Move();
        }


        // Turn back on limit sensor mode.
        if (bothLimitsAreAsserted) SetLimitSwitchMode(PMDLimitEnabled);

        // Restore the original goal position
        p.pos = lastCommandedPos;

    } else if (limitsMayBind) {

        // Set a more agressive output and error limit to overcome 
        // sticky limits while backing off the hard limit.
        const int MaxOL = 32767;
        SetMotorLimit(MaxOL);
        SetPositionErrorLimit(homingFilter.errorLimit*2);

        // Back off the hard-stop by 10%
        PMDint32 actPos;
        GetActualPosition(actPos);
        if (p.pos < 0)
            p.pos = actPos + rangeOfMotion/10;
        else
            p.pos = actPos - rangeOfMotion/10;
        SetProfile(p);
        ifDbgCout << "Withdrawling from potentially binding limit...\n";
        if (Move()) {
            ifDbgCout << "Withdrawl succeeded\n";
        }
        else {
            ifDbgCout << "Withdrawl failed (limit too sticky?)\n";
        }

        // Reset gains
        SetMotorLimit(homingFilter.motorLimit);
        SetPositionErrorLimit(homingFilter.errorLimit);

    }
    SetMoveWaitPeriod(oldPeriod);

}

//----------------------------------------------------------------------------
bool PMDAxisControl::FindHomeWithLimits() {

    char methodStr[] = "FindHomeWithLimits: ";
    const unsigned int moveBoost = 2;
    PMDuint16 boostedMotorLimit = min(32767,homingFilter.motorLimit*moveBoost);

    unsigned long oldPeriod = GetMoveWaitPeriod();
    SetMoveWaitPeriod(500);

    // Load homing profile
    CountsProfile countsProfile = homingProfileCounts;

    // Find reverse limit & record its position
    if (homingMode == ReverseLimit || homingMode == BothLimits) {

        // If this limit is asserted, the axis must back off of it.
        // This is done by moving 10% in the opposite direction.
        GetSignalStatus(signalStatus);
        if (!(signalStatus & PMDSignalNegativeLimitMask)) {
            countsProfile.pos = rangeOfMotion/10;
            WithdrawFromLimit(countsProfile);
        }

        // Want to move enough in the limit direction to ensure that the limit
        // is surpassed so that either a hard limit is reached or the reverse
        // limit switch is reached. This is done by moving the specified 
        // range of motion PLUS twice the error limit.
        countsProfile.pos = -(signed)rangeOfMotion - 2*homingFilter.errorLimit;
        ifDbgCout << "Attempting to move the entire range of motion (" 
                  << countsProfile.pos
                  << ") towards the -limit in expectation of hitting the limit\n";
        GoToLimit(countsProfile);
        reverseLimit = actProfileCounts.pos;
        ifDbgCout << "Reverse limit encountered at " << reverseLimit << endl;
    }

    // Move more quickly most of the way toward the expected 
    // forward limit if both limits are used for homing.
    // Find positive limit (if desired)
    if (homingMode == BothLimits) {

        countsProfile.pos = reverseLimit + rangeOfMotion*4/5;
        countsProfile.vel *= moveBoost;
        ifDbgCout << "Moving partially (to " << countsProfile.pos
                  << ") back towards expected +limit a little faster\n";
        SetProfile(countsProfile);

        // Boost components of profile and filter to facilitate the faster move.
        SetPositionErrorLimit(homingFilter.errorLimit*moveBoost);
        SetMotorLimit(boostedMotorLimit);

        // Initiate move
        if (Move()) {
            ifDbgCout << "Quick partial forward move done\n";
        }
        else {
            ifDbgCout << "Quick partial forward move ended prematurely\n";
        }

        // Restore original motion parameters
        countsProfile.vel = homingProfileCounts.vel;
        SetPositionErrorLimit(homingFilter.errorLimit);
        SetMotorLimit(homingFilter.motorLimit);
    }

    // Find forward limit & record its position
    if (homingMode == ForwardLimit || homingMode == BothLimits) {

        // If this limit is asserted, the axis must back off of it.
        // This is done by moving 10% in the opposite direction.
        GetSignalStatus(signalStatus);
        if (!(signalStatus & PMDSignalPositiveLimitMask)) {
            GetActualPosition(countsProfile.pos);
            countsProfile.pos -= rangeOfMotion/10;
            WithdrawFromLimit(countsProfile);
        }

        // Want to go past the limit by at least the error limit to ensure
        // that the hard stop is reached and a motion error is triggered.
        countsProfile.pos = rangeOfMotion + 2*homingFilter.errorLimit;
        ifDbgCout << "Attempting to move past the expected +limit (to " 
                  << countsProfile.pos
                  << ") in expectation of hitting a hard limit\n";
        GoToLimit(countsProfile);
        forwardLimit = actProfileCounts.pos;
        ifDbgCout << "Forward limit detected at " << forwardLimit << endl;
    }

    // Compute the new home/zero position
    if (homingMode == ReverseLimit)
        homeDelta = reverseLimit + homeCountsOffset;
    else if (homingMode == ForwardLimit)
        homeDelta = forwardLimit + homeCountsOffset;
    else {
        // Homing fails if measured range of motion is not within a %age
        // of the predicted range of motion.
        long measuredRangeOfMotion = forwardLimit - reverseLimit;
        if (measuredRangeOfMotion > rangeOfMotion*1.1 || 
            measuredRangeOfMotion < rangeOfMotion*0.9) 
            return false;
        homeDelta = (reverseLimit + forwardLimit)/2 + homeCountsOffset;
    }

    // Make the actual position relative to the new home position.
    const float AdjustActualPositionReleaseVersion = 1.6f;
    if (controller->GetControllerVersion() < AdjustActualPositionReleaseVersion) {
        GetActualPosition(actProfileCounts.pos);
        SetActualPosition(actProfileCounts.pos-homeDelta);
    } else
        AdjustActualPosition(-homeDelta);

    // Move to the axis zero (home) position.
    countsProfile.pos = 0;
    countsProfile.vel *= moveBoost;
    ifDbgCout << "Moving to zero (home) position, offset by " << homeCountsOffset << endl;
    SetProfile(countsProfile);

    // Boost components of profile and filter to facilitate the faster move.
    SetPositionErrorLimit(homingFilter.errorLimit*moveBoost);
    SetMotorLimit(boostedMotorLimit);
    SetPositionErrorLimit(homingFilter.errorLimit*moveBoost);

    // Start moving.
    if (Move()) {
        GetActualPosition(actProfileCounts.pos);
        ifDbgCout << "final home position acheived, stopped at " 
                  << actProfileCounts.pos << endl;
    }
    else {
        GetActualPosition(actProfileCounts.pos);
        ifDbgCout << "final home position not acheived, stopped at" 
                  << actProfileCounts.pos << endl;
        ifDbgCout << "However, homing was still successful." << endl;
    }

    // Restore original homing rates
    countsProfile.vel = homingProfileCounts.vel;
    SetPositionErrorLimit(homingFilter.errorLimit);
    SetMotorLimit(homingFilter.motorLimit);

    // Recompute the hard limits relative to what is now the zero position.
    if (homingMode == ReverseLimit) {
        reverseLimit = reverseLimit - homeDelta;
        forwardLimit = reverseLimit + rangeOfMotion;
    } else if (homingMode == ForwardLimit) {
        forwardLimit = forwardLimit - homeDelta;
        reverseLimit = forwardLimit - rangeOfMotion;
    } else {
        reverseLimit = reverseLimit - homeDelta;
        forwardLimit = forwardLimit - homeDelta;
    }

    // Compute soft limits beyond which commanding will be prohibited.
    long axisRange = forwardLimit - reverseLimit;
    softReverseLimit = reverseLimit + axisRange/100;
    softForwardLimit = forwardLimit - axisRange/100;
    SetMoveWaitPeriod(oldPeriod);

    return true;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::FindHomeWithHomeSensor() {

    PMDuint16 rslt;
    char methodStr[] = "FindHomeWithHomeSensor: ";
    PMDint32 captureValue;
	bool captureValueIsValid = false;

    unsigned long oldPeriod = GetMoveWaitPeriod();
    SetMoveWaitPeriod(500);

    // Load homing profile
    CountsProfile countsProfile = homingProfileCounts;

    // Set high speed capture for home signal and re-arm capture.
    rslt = SetCaptureSource(PMDCaptureSourceHome);
    rslt = ResetEventStatus(~PMDEventCaptureReceivedMask);
    rslt = GetCaptureValue(captureValue);   // re-arm

    // May want to change the following logic to look for hard limits while
    // looking for home sensor and recording their positions when encountered.
    // Could also make Move() command accept mask parameter to tell it what
    // to look for when deciding whether a move is complete or not. The move
    // command would default to motion complete and motion error.

    // Find hard limits if they are indicated to exist.
    if (hasHardLimits) {
        homingMode = BothLimits;
        FindHomeWithLimits();
        homingMode = HomeAndIndex; // set back to original value.

        // Get the position of home.
        if (eventStatus & PMDEventCaptureReceivedMask) {
//        GetActivityStatus(activityStatus);
//        if (activityStatus & PMDActivityPositionCaptureMask) {
            rslt = GetCaptureValue(captureValue);
            captureValue -= homeDelta;
			captureValueIsValid = true;
        }

    } else {

        // Since hard limits are not explorable, exercise axis to find
        // home signal by sweeping over the defined range of motion.

		// First check if the home sensor is active to save time having
		// to search for it.
		PMDuint16 signalStatus;
		rslt = GetSignalStatus(signalStatus);
		if (signalStatus & PMDSignalEncoderHomeMask) {

			// Home sensor is active.
			// Record current position as capture value and skip search.
			rslt = GetActualPosition(captureValue);
			captureValueIsValid = true;
            ifDbgCout << "Home signal already active. Skip search for it.\n";

		} else {

			// Start positive rotation for half of full range or to the 
			// soft limit, whichever is less.
			if (softForwardLimit < countsPerAxisCycle/2)
				countsProfile.pos = softForwardLimit;
			else {
				countsProfile.pos = (PMDint32)(rangeOfMotion/2);
			}
			SetProfile(countsProfile);
			ifDbgCout << "Looking for home signal with positive rotation...\n";
			MoveWithCaptureInterrupt();

			// Was the home signal captured during positive rotation?
			rslt = GetEventStatus(eventStatus);
			if (!(eventStatus & PMDEventCaptureReceivedMask)) {

				// Did not see the home signal.
				ifDbgCout << "Didn't find home signal with positive rotation\n";

				// Rotate one whole cycle in the negative direction (or to the 
				// negative soft limit) to capture the home position.
				ifDbgCout << "Looking for home signal with negative rotation...\n";
				if (hasHardLimits && softReverseLimit > -countsPerAxisCycle/2)
					countsProfile.pos = softReverseLimit;
				else
					countsProfile.pos = -(int)countsPerAxisCycle/2;
				SetProfile(countsProfile);
				MoveWithCaptureInterrupt();

				// Was the home signal captured during negative rotation?
				rslt = GetEventStatus(eventStatus);
				if (!(eventStatus & PMDEventCaptureReceivedMask)) {
					ifDbgCout 
						<< "Didn't find home signal with negative rotation\n"
						<< "Home sensor isn't working or axis didn't move!\n";
					SetMoveWaitPeriod(oldPeriod);
				} else {
			        rslt = GetCaptureValue(captureValue);
					captureValueIsValid = true;
					ifDbgCout << "Saw the home signal at " << captureValue << " with negative rotation\n";
				}

			} else {
		        rslt = GetCaptureValue(captureValue);
				captureValueIsValid = true;
				ifDbgCout << "Saw the home signal at " << captureValue << " with positive rotation\n";
			}

	    }
	}

	// If the home signal was detected, find the nearest encoder index pulse.
	if (captureValueIsValid) {

		// Reset the flag for the index search.
		captureValueIsValid = false;

		// Rotate negative half an encoder revolution from the capture position.
		countsProfile.pos = captureValue - countsPerEncoderCycle/2;
		SetProfile(countsProfile);
		ifDbgCout << "Moving back to 1/2 encoder rev  (" << countsProfile.pos << ") from home sensor\n";
		Move();

		// Set high speed capture for index signal and re-arm capture.
		rslt = SetCaptureSource(PMDCaptureSourceIndex);
		rslt = GetCaptureValue(captureValue);
		rslt = ResetEventStatus(~PMDEventCaptureReceivedMask);

		// Rotate one whole encoder cycle in the forward direction.
		ifDbgCout << "Sweeping 1 encoder cycle in + dir to detect index pulse\n";
		countsProfile.pos += countsPerEncoderCycle;
		SetProfile(countsProfile);
		Move();

		// Was the index signal detected?
		rslt = GetEventStatus(eventStatus);
		if (!(eventStatus & PMDEventCaptureReceivedMask)) {

			// Did not see the index signal.
			ifDbgCout << "Didn't find index signal near the home sensor.\n";
			SetMoveWaitPeriod(oldPeriod);

		} else {

			// Record the captured index value
			rslt = GetCaptureValue(captureValue);
			captureValueIsValid = true;
			ifDbgCout << "Saw the index pulse at " << captureValue << "\n";

			// Change the actual position to be relative to the captured location.
			// For example, if the index is detected at 50, then the zero
			// position must be adjusted by -50 so that position is the new zero.
			AdjustActualPosition(-captureValue);

			// Adjust the limits relative to the "new" home
			if (hasHardLimits) {
				// Since a hard limit search occured earlier, just update those values.
				forwardLimit -= captureValue;
				reverseLimit -= captureValue;
				softForwardLimit -= captureValue;
				softReverseLimit -= captureValue;
			} else {
				// Set artificial soft limits at +- one full rotation and leave the
				// hard limits at their max values since there are no hard limits.
				softForwardLimit = (long)rangeOfMotion/2;
				softReverseLimit = -softForwardLimit;
			}

			// Move to our new home.
			countsProfile.pos = 0;
			SetProfile(countsProfile);
			Move(); // Move twice in case capture flag is tripped.
			SetMoveWaitPeriod(oldPeriod);

		}
	}

    return captureValueIsValid;
}

//----------------------------------------------------------------------------
void PMDAxisControl::SetHomingLimits(
                    const long forwardLimit, const long reverseLimit,
                    const long softForwardLimit, const long softReverseLimit) {
    this->forwardLimit = forwardLimit;
    this->reverseLimit = reverseLimit;
    this->softForwardLimit = softForwardLimit;
    this->softReverseLimit = softReverseLimit;

    // Record the fact that this axis is considered homed
    SetCaptureSource(PMDCaptureSourceHome);
    isHomed = true;

}

//----------------------------------------------------------------------------
void PMDAxisControl::GetHomingLimits(
		long& forwardLimit, long& reverseLimit,
                long& softForwardLimit, long& softReverseLimit) {
    forwardLimit = this->forwardLimit;
    reverseLimit = this->reverseLimit;
    softForwardLimit = this->softForwardLimit;
    softReverseLimit = this->softReverseLimit;
}

//----------------------------------------------------------------------------
// Control of the motor amp enable pin is implemented through the axisOut 
// pins. By setting the axisOut state to not be tied to any of the status 
// register bits, the application has direct control of the axisOut value by
// setting the signal sense of the AxisOut signal.
// For example, if the signal sense of the pin is set to non-inverted,
// then the axisOut pin will be low. However, if the signal sense is
// set to inverted, then the axisOut pin will go high, thus enabling
// the amp. 
// Setting of the signal sense for the axisOut pin is done by getting 
// the current state of the signal sense mask from the control chip,
// setting the value of the axisOut bit, and then setting the signal
// sense register to the new value.
// WARNING: axis out defaults to high on powerup or reset, so if the amp enable
// control for the amplifier is active high, the amplifier will be powered
// after reset.
void PMDAxisControl::EnableAmp() {
    PMDuint16 signalSenseMask;
    PMDuint16 rslt = GetSignalSense(signalSenseMask);
    if (ampPolarity == ActiveHigh)
        signalSenseMask &= ~PMDSignalAxisOutMask; 
    else
        signalSenseMask |= PMDSignalAxisOutMask; // Active low so motor defaults to off.
    rslt = SetSignalSense(signalSenseMask);    
    ampIsOn = true;
}
void PMDAxisControl::DisableAmp() {
    PMDuint16 signalSenseMask;
    PMDuint16 rslt = GetSignalSense(signalSenseMask);
    if (ampPolarity == ActiveHigh)
        signalSenseMask |= PMDSignalAxisOutMask; // Active low so motor defaults to off.
    else
        signalSenseMask &= ~PMDSignalAxisOutMask; 
    rslt = SetSignalSense(signalSenseMask);    
    ampIsOn = false;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::IsBrakeEngaged() {
    if (hasBrake) {
        return ((controller->brakeState & (1 << GetAxisNumber())) == 0);
    } else 
        return false;
}

// NOTE: Brakes are currently assumed to be failsafe, meaning that they are 
// engaged when not powered (off). Setting their state high (on) disengages
// the brake.
//----------------------------------------------------------------------------
void PMDAxisControl::EngageBrake() {
    if (hasBrake) {
        PMDuint16 brakeState = controller->brakeState;
        brakeState = brakeState & ~(1<<GetAxisNumber());
        WriteIO(BrakeIOAddress,brakeState);
        controller->brakeState = brakeState;
    }
}

//----------------------------------------------------------------------------
void PMDAxisControl::DisengageBrake() {
    if (hasBrake) {
        PMDuint16 brakeState = controller->brakeState;
        brakeState = brakeState | (1<<GetAxisNumber());
        WriteIO(BrakeIOAddress,brakeState);
        controller->brakeState = brakeState;
    }
}

//----------------------------------------------------------------------------
// Lock brake, disable amp, and turn off closed loop control.
void PMDAxisControl::Park() {
    EngageBrake();
    DisableAmp();
    SetMotorMode(PMDMotorOff);
}

//----------------------------------------------------------------------------
// Turn on closed loop control, enable amp, and unlock brake.
void PMDAxisControl::Unpark() {
    ResetEventStatus(~MoveEventMask);
    EnableAmp();
    SetMotorMode(PMDMotorOn);
    DisengageBrake();
}

//----------------------------------------------------------------------------
bool PMDAxisControl::ParkAndSave() {
    char fName[100];
    stringstream stream(stringstream::in | stringstream::out);
    stream << controller->uniqueID << '-' << uniqueID << ".park" << ends;
    stream >> fName;
    ofstream fp(fName,ios::out);

    if (!fp) {
        return false;
    } else {

        Park();
        long pos,lim[4];
        GetActualPosition(pos);
        GetHomingLimits(lim[0],lim[1],lim[2],lim[3]);
        fp << pos << ' ' << lim[0] << ' ' << lim[1] << ' ' << lim[2] << ' ' << lim[3] << endl;
        fp.close();
        PMDUtils::DoSleep(250); // Slow down the process a little.
        return true;
    }
}

//----------------------------------------------------------------------------
bool PMDAxisControl::RecoverFromParkAndSave() {
    char fName[100];
    stringstream stream(stringstream::in | stringstream::out);
    stream << controller->uniqueID << '-' << uniqueID << ".park" << ends;
    stream >> fName;

    ifstream fp(fName,ios::in);
    if (fp.is_open()) {
        long pos;
        long lim[4];

        // Get the values from the file.
        fp >> pos >> lim[0] >> lim[1] >> lim[2] >> lim[3];
        fp.close();

        SetHomingLimits(lim[0],lim[1],lim[2],lim[3]);
        SetActualPosition(pos);
        Unpark();

        // Load axis control parameters
        SetFilter(runFilter);
        CountsProfile profile;
        ProfileToCounts(runProfile,profile);
        profile.pos = pos;
        SetProfile(profile);
        Move();
        return true;
    } else {
        return false;
    }
}

//----------------------------------------------------------------------------
// Only need to call this if application is NOT calling a Move command.
void PMDAxisControl::PreMove(bool waitForMotionToStop) {

    // Get event status if it hasn't been sampled since the last move
    // command was issued.
    GetLastEventStatus();

    // Determine if closed loop control needs to be restarted due to a 
    // condition that would have automatically turned it off.
    mustEnableClosedLoopControl = ((eventStatus & AutostopEventMask) != 0);

    // Clear (if necessary) all move-related events before issuing move.
    eventStatus &= ~MoveEventMask;
    if (mustEnableClosedLoopControl || waitForMotionToStop) 
        ResetEventStatus(~MoveEventMask);

    // Reissue the velocity since the controller automatically clears it
    // on a motion error or limit switch event.
    if (mustEnableClosedLoopControl) 
        SetVelocity(CountsVelToPMD(cmdProfileCounts.vel));

    // Start moving to the new position.
    eventStatusLoadedSinceLastMove = false;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::Move(bool waitForMotionToStop) {

    PreMove(waitForMotionToStop);

    Update();

    PostMove();

    // Wait for motion to complete if desired.
    if (waitForMotionToStop) {
        return WaitForMotionToStop();
    } else
        return true;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::MoveWithCaptureInterrupt(bool waitForMotionToStop) {

    PreMove(waitForMotionToStop);
	
	// Tell move to return if capture event occurs.
	ResetEventStatus(~PMDEventCaptureReceivedMask);

    Update();

    PostMove();

    // Wait for motion to complete if desired.
    if (waitForMotionToStop) {
        return WaitForMotionToStop();
    } else
        return true;
}

//----------------------------------------------------------------------------
// Returns false if a motion error is detected. Otherwise, returns true when
// motion is complete.
bool PMDAxisControl::WaitForMotionToStop(bool includeCaptureEvent) {
    while (!IsMotionDone(includeCaptureEvent)) {
        PMDUtils::DoSleep(waitPeriod);
    }
    return !(eventStatus & AutostopEventMask);
}

//----------------------------------------------------------------------------
// Only need to call this if application is NOT calling a Move command.
void PMDAxisControl::PostMove() {
    // Re-enable closed loop control if a motion error is asserted.
    if (mustEnableClosedLoopControl) SetMotorMode(PMDMotorOn);
}

//----------------------------------------------------------------------------
bool PMDAxisControl::Move(bool waitForMotionToStop, double pos, 
        double vel, double acc, double dec, double jerk) {
    Profile profile = cmdProfile;
    profile.pos = pos;
    if (vel != 0) profile.vel = vel;
    if (acc != 0) profile.acc = acc;
    if (dec != 0) profile.dec = dec;
    if (jerk != 0) profile.jerk = jerk;
    SetProfile(profile);
    return Move(waitForMotionToStop);
}

//----------------------------------------------------------------------------
bool PMDAxisControl::Move(bool waitForMotionToStop, PMDint32 pos, 
        PMDint32 vel, PMDuint32 acc, PMDuint32 dec, PMDuint32 jerk) {
    CountsProfile newProfile,cmdCountsProfile;
    ProfileToCounts(cmdProfile,cmdCountsProfile);
    newProfile = cmdCountsProfile;
    newProfile.pos = pos;
    if (vel != 0) newProfile.vel = vel;
    if (acc != 0) newProfile.acc = acc;
    if (dec != 0) newProfile.dec = dec;
    if (jerk != 0) newProfile.jerk = jerk;
    SetProfile(newProfile);
    return Move(waitForMotionToStop);
}

//----------------------------------------------------------------------------
bool PMDAxisControl::IsMotionDone(bool includeCaptureEvent) {
    GetEventStatus(eventStatus);
    eventStatusLoadedSinceLastMove = true;
	if (includeCaptureEvent)
		return ((eventStatus & MoveEventMask & PMDEventCaptureReceivedMask) != 0);
	else
		return ((eventStatus & MoveEventMask) != 0);
}

//----------------------------------------------------------------------------
void PMDAxisControl::ProfileToCounts(const Profile& profile, 
                                     CountsProfile& counts) {
    counts.pos  = UnitsToCounts(profile.pos);
    counts.vel  = UnitsToCounts(profile.vel);
    counts.acc  = UnitsToCounts(profile.acc);
    counts.dec  = UnitsToCounts(profile.dec);
    counts.jerk = UnitsToCounts(profile.jerk);
}

//----------------------------------------------------------------------------
void PMDAxisControl::CountsToProfile(Profile& profile, 
                                     const CountsProfile& counts) {
    profile.pos  = CountsToUnits(counts.pos);
    profile.vel  = CountsToUnits(counts.vel);
    profile.acc  = CountsToUnits(counts.acc);
    profile.dec  = CountsToUnits(counts.dec);
    profile.jerk = CountsToUnits(counts.jerk);
}

//----------------------------------------------------------------------------
PMDint32 PMDAxisControl::CountsVelToPMD(PMDint32 countsVel) {
	return (PMDint32) (countsVel*GetCycleTimeInSecs()*PMDVelScaling);
}

//----------------------------------------------------------------------------
PMDuint32 PMDAxisControl::CountsAccToPMD(PMDuint32 countsAcc) {
    return (PMDuint32)(countsAcc*pow(GetCycleTimeInSecs(),2.0)*PMDAccScaling);
}

//----------------------------------------------------------------------------
PMDuint32 PMDAxisControl::CountsJerkToPMD(PMDuint32 countsJerk) {
    return (PMDuint32)(countsJerk*pow(GetCycleTimeInSecs(),3.0)*PMDJerkScaling);
}

//----------------------------------------------------------------------------
PMDint32 PMDAxisControl::PMDToCountsVel(PMDint32 pmdVel) {
	return (PMDint32) (pmdVel/PMDVelScaling/GetCycleTimeInSecs());
}

//----------------------------------------------------------------------------
PMDuint32 PMDAxisControl::PMDToCountsAccToPMD(PMDuint32 pmdAcc) {
    return (PMDuint32)(pmdAcc/PMDAccScaling/pow(GetCycleTimeInSecs(),2.0));
}

//----------------------------------------------------------------------------
PMDuint32 PMDAxisControl::PMDToCountsJerkToPMD(PMDuint32 pmdJerk) {
    return (PMDuint32)(pmdJerk/PMDJerkScaling/pow(GetCycleTimeInSecs(),3.0));
}

//----------------------------------------------------------------------------
void PMDAxisControl::SendProfileToController(const CountsProfile& countsProfile) {
    // Go through each of the profile values and "load"
    // only the values that are different from the current settings.
    // This minimizes the amount of traffic going over the controller
    // interface, which can be significant if the interface is serial.
    bool somethingWasSet = false;
    PMDint32 counts;
    PMDuint32 ucounts;
    if (countsProfile.vel != cmdProfileCounts.vel) {
        counts = CountsVelToPMD(countsProfile.vel);
        if (counts == 0) counts = 1;    // Can't allow a vel of zero
        SetVelocity(counts);
        somethingWasSet = true;
    }
    if (countsProfile.acc != cmdProfileCounts.acc) {
        ucounts = CountsAccToPMD(countsProfile.acc);
//        if (ucounts == 0) ucounts = 1;  // Can't allow an acc of zero
        if (ucounts < 2) ucounts = 2;  // V2.3 of navigator won't allow acc < 2
        SetAcceleration(ucounts);
        somethingWasSet = true;
    }
    if (countsProfile.dec != cmdProfileCounts.dec) {
        ucounts = CountsAccToPMD(countsProfile.dec);
//        if (countsProfile.dec != 0 && ucounts == 0) ucounts = 1;
        if (countsProfile.dec != 0 && ucounts < 2) ucounts = 2;
        SetDeceleration(ucounts);
        somethingWasSet = true;
    }
    if (countsProfile.jerk!= cmdProfileCounts.jerk) {
        ucounts = CountsJerkToPMD(countsProfile.jerk);
        if (countsProfile.jerk != 0 && ucounts == 0) ucounts = 1;
        SetJerk(CountsJerkToPMD(ucounts));
        somethingWasSet = true;
    }
//    if (countsProfile.pos != cmdProfileCounts.pos || 
//        !somethingWasSet) {     // make sure something is always loaded.
        SetPosition(countsProfile.pos);
//    }
    cmdProfileCounts = countsProfile;
}

double PMDAxisControl::GetCycleTimeInSecs() { 
    return controller->GetCycleTime()/1.0E6;
}

//----------------------------------------------------------------------------
PMDuint16 PMDAxisControl::GetLastEventStatus() {

    // If the last move did not have any wait, then the event status probably
    // has not been sampled, so sample it now and indicate that the register
    // has been sampled and the most recent data is stored in the local 
    // variable.
    if (!eventStatusLoadedSinceLastMove) {
        eventStatusLoadedSinceLastMove = true;
        GetEventStatus(eventStatus);
    }
    return eventStatus;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::ChangeComm(int baud) {
    if (controller != NULL)  return controller->ChangeComm(baud);
    else                     return false;
}

//----------------------------------------------------------------------------
bool PMDAxisControl::ReadParameters(FILE *file, char *token) {
    bool tokenRecognized = true;
    unsigned int uval;

    // Define the tokens used here.
    const char TokenController[] = "controller";
    const char TokenMotor[] = "[motor]";
    const char TokenEncoder[] = "[encoder]";
    const char TokenHomingParams[] = "[homing parameters]";
    const char TokenHomingProfile[] = "[homing profile]";
    const char TokenHomingFilter[] = "[homing servo filter]";
    const char TokenProfile[] = "[run profile]";
    const char TokenFilter[] = "[run servo filter]";
    const char AxisToken[] = "axisNumber";
    const char TokenDebugLevel[] = "debugLevel";

    // Prime token stream.
    PMDUtils::ReadToken(file,token);

    // Parse the stream.
    do {
        if (!strcmp(token,PMDUtils::TokenUniqueID)) {
            PMDUtils::ReadToken(file,token);
            strcpy_s(uniqueID,token);
            PMDUtils::ReadToken(file,token);
        } else if (!strcmp(token,TokenDebugLevel)) {
            PMDUtils::ReadToken(file,token);
            if (sscanf_s(token,"%u",&uval) == 1) {
                SetDebugLevel(uval);
            } else tokenRecognized = false;
            PMDUtils::ReadToken(file,token);
        } else if (!strcmp(token,TokenController)) {

            // Get the name of the associated controller.
            PMDUtils::ReadToken(file,token);

            // Get access to the named controller and attach this axis to it.
            ControllerCollection *controllers = PMDControllers::Instance();
            controller = (*controllers)[token];
            if (controller != NULL) {
                controller->AddAxis(this);
            } else tokenRecognized = false;
            PMDUtils::ReadToken(file,token);

        } else if (!strcmp(token,TokenMotor)) {
            ReadMotorParameters(file,token);
        } else if (!strcmp(token,TokenEncoder)) {
            ReadEncoderParameters(file,token);
        } else if (!strcmp(token,TokenHomingParams)) {
            ReadHomingParameters(file,token);
        } else if (!strcmp(token,TokenHomingProfile)) {
            ReadProfile(file,token,homingProfile);
            ProfileToCounts(homingProfile,homingProfileCounts);
        } else if (!strcmp(token,TokenHomingFilter)) {
            ReadFilter(file,token,homingFilter);
            activeFilter = homingFilter;
        } else if (!strcmp(token,TokenProfile)) {
            ReadProfile(file,token,runProfile);
            cmdProfile = runProfile;
        } else if (!strcmp(token,TokenFilter)) {
            ReadFilter(file,token,runFilter);
        } else if (!strcmp(token,AxisToken)) {
            PMDUtils::ReadToken(file,token);
            if (sscanf_s(token,"%u",&uval) == 1 && 
                uval >= PMDAxis1 && uval <= PMDAxis4) {
                SetAxis(uval);
                PMDUtils::ReadToken(file,token);
            } else
                tokenRecognized = false;
        } else tokenRecognized = false;

    } while (!feof(file) && tokenRecognized);

    // Record the results of whether configuration data was successfully 
    // loaded for this axis. Only an axis that has been successfully loaded
    // may be controlled.
    if (!strcmp(token,EndToken)) {
        configurationWasLoaded = true;
        return true;
    } else
        return false;
}

//----------------------------------------------------------------------------
const char TokenActiveHigh[] = "ActiveHigh";
const char TokenActiveLow[] = "ActiveLow";
bool PMDAxisControl::ReadPolarity(FILE *file, char *token, Polarity &polarity) {
    bool tokenRecognized = true;
    PMDUtils::ReadToken(file,token);
    if (!strcmp(token,TokenActiveHigh))
        polarity = ActiveHigh;
    else if (!strcmp(token,TokenActiveLow))
        polarity = ActiveLow;
    else
        tokenRecognized = false;
    return tokenRecognized;
}

//----------------------------------------------------------------------------
const char TokenCounts[] = "counts";
bool PMDAxisControl::ReadAngle(FILE *file, char *token, double &angle) {
    bool tokenRecognized = true;

    // Get the numeric value and save it in a local buffer.
    PMDUtils::ReadToken(file,token);
    char valToken[10];
    strcpy_s(valToken,token);

    // Get the units of measure for the angle value and convert it to revolutions.
    float fangle;
    PMDUtils::ReadToken(file,token);
    if (strcmp(token,PMDUtils::TokenDegrees) == 0) {
        sscanf_s(valToken,"%f",&fangle);
        angle = PMDUtils::DegsToRevs((double)fangle);
    } else if (strcmp(token,PMDUtils::TokenRadians) == 0) {
        sscanf_s(valToken,"%f",&fangle);
        angle = PMDUtils::RadsToRevs((double)fangle);
    } else if (strcmp(token,PMDUtils::TokenRevolutions) == 0) {
        sscanf_s(valToken,"%f",&fangle);
        angle = (double)fangle;
    } else if (strcmp(token,TokenCounts) == 0) {
        int countAngle;
        sscanf_s(valToken,"%d",&countAngle);
        angle = CountsToUnits(countAngle);
    } else
        tokenRecognized = false;
    return tokenRecognized;
}

//----------------------------------------------------------------------------
const char TokenMotorType[] = "motortype";
const char TokenBrushed[] = "brushed";
const char TokenBrushless[] = "brushless";
const char TokenPoleCount[] = "polecount";
const char TokenAmpType[] = "amptype";
const char TokenAmpPolarity[] = "ampPolarity";
const char TokenPWMSignMag[] = "PWMSignMag";
const char TokenPWM5050[] = "PWM50/50";
const char TokenHasBrake[] = "hasBrake";
const char TokenPhaseInitMode[] = "phaseInit";
const char TokenAlgorithmic[] = "Algorithmic";
const char TokenHallBased[] = "HallBased";
const char TokenInvertHalls[] = "invertHalls";
const char TokenCommutationMode[] = "commutationMode";
const char TokenSinusoidal[] = "Sinusoidal";
const char TokenMicrostepping[] = "Microstepping";
const char TokenReverseMotorOutput[] = "reverseMotorOutput";
void PMDAxisControl::ReadMotorParameters(FILE *file, char *token) {
    bool tokenRecognized = true;
    PMDUtils::ReadToken(file,token);
    do {
        if (!strcmp(token,TokenMotorType)) {
            PMDUtils::ReadToken(file,token);
            if (!strcmp(token,TokenBrushed))
                isBrushless = false;
            else if (!strcmp(token,TokenBrushless))
                isBrushless = true;
            else
                tokenRecognized = false;
        } else if (!strcmp(token,TokenPoleCount)) {
            PMDUtils::ReadToken(file,token);
            unsigned int ui;
            tokenRecognized = sscanf_s(token,"%u",&ui) == 1;
            poleCount = (unsigned short) ui;
        } else if (!strcmp(token,TokenAmpType)) {
            PMDUtils::ReadToken(file,token);
            if (!strcmp(token,TokenPWMSignMag))
                ampType = PMDMotorOutputPWMSignMagnitude;
            else if (!strcmp(token,TokenPWM5050))
                ampType = PMDMotorOutputPWM5050Magnitude;
            else
                tokenRecognized = false;
        } else if (!strcmp(token,TokenAmpPolarity)) {
            tokenRecognized = ReadPolarity(file,token,ampPolarity);
        } else if (!strcmp(token,TokenHasBrake)) {
            tokenRecognized = PMDUtils::ReadBool(file,token,hasBrake);
        } else if (!strcmp(token,TokenPhaseInitMode)) {
            PMDUtils::ReadToken(file,token);
            if (!strcmp(token,TokenAlgorithmic))
                phaseInitMode = PMDPhaseInitAlgorithmic;
            else if (!strcmp(token,TokenHallBased))
                phaseInitMode = PMDPhaseInitHallBased;
            else
                tokenRecognized = false;
        } else if (!strcmp(token,TokenCommutationMode)) {
            PMDUtils::ReadToken(file,token);
            if (!strcmp(token,TokenHallBased))
                commutationMode = PMDCommutationModeHallBased;
            else if (!strcmp(token,TokenSinusoidal))
                commutationMode = PMDCommutationModeSinusoidal;
            else if (!strcmp(token,TokenMicrostepping))
                commutationMode = PMDCommutationModeSinusoidal;
            else
                tokenRecognized = false;
        } else if (!strcmp(token,TokenInvertHalls)) {
            tokenRecognized = PMDUtils::ReadBool(file,token,invertHalls);
        } else if (!strcmp(token,TokenReverseMotorOutput)) {
            tokenRecognized = PMDUtils::ReadBool(file,token,reverseMotorOutput);
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}

//----------------------------------------------------------------------------
const char TokenCountsPerEncoderCycle[] = "counts/encodercycle";
const char TokenEncoderCyclesPerAxisCycle[] = "encodercycles/axiscycle";
const char TokenMotorCyclesPerEncoderCycle[] = "motorcycles/encodercycle";
void PMDAxisControl::ReadEncoderParameters(FILE *file, char *token) {
    bool tokenRecognized = true;
    PMDUtils::ReadToken(file,token);
    float ftemp;
    do {
        if (!strcmp(token,TokenCountsPerEncoderCycle)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%lu",&countsPerEncoderCycle) == 1;
        } else if (!strcmp(token,TokenEncoderCyclesPerAxisCycle)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%f",&ftemp) == 1;
            encoderCyclesPerAxisCycle = (double)ftemp;
        } else if (!strcmp(token,TokenMotorCyclesPerEncoderCycle)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%f",&ftemp) == 1;
            motorCyclesPerEncoderCycle = (double)ftemp;
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);

    // Recompute derived values
    countsPerAxisCycle = countsPerEncoderCycle*encoderCyclesPerAxisCycle;
    countsPerMotorCycle = countsPerEncoderCycle/motorCyclesPerEncoderCycle;
    rangeOfMotion = (unsigned long)countsPerAxisCycle;  // default to 1 axis cycle

}

//----------------------------------------------------------------------------
const char TokenHomingMode[] = "homingMode";
const char TokenNoHoming[] = "noHoming";
const char TokenReverseLimit[] = "reverseLimit";
const char TokenForwardLimit[] = "forwardLimit";
const char TokenBothLimits[] = "bothLimits";
const char TokenHomeAndIndex[] = "homeAndIndex";
const char TokenRangeOfMotion[] = "rangeOfMotion";
const char TokenHasHardLimits[] = "hasHardLimits";
const char TokenHasHomeSensor[] = "hasHomeSensor";
const char TokenHasLimitSensors[] = "hasLimitSensors";
const char TokenLimitsMayBind[] = "limitsMayBind";
const char TokenHomeOffset[] = "homeOffset";
const char TokenHomeSignalPolarity[] = "homeSignalPolarity";
const char TokenLimitSignalPolarity[] = "limitSignalPolarity";
void PMDAxisControl::ReadHomingParameters(FILE *file, char *token) {
    bool tokenRecognized = true;
    PMDUtils::ReadToken(file,token);
    do {
        if (!strcmp(token,TokenHomeOffset)) {
            double angle; 
            tokenRecognized = ReadAngle(file,token,angle);
            if (tokenRecognized) homeCountsOffset = UnitsToCounts(angle);
//            PMDUtils::ReadToken(file,token);
//            tokenRecognized = sscanf_s(token,"%d",&homeCountsOffset) == 1;
        } else if (!strcmp(token,TokenRangeOfMotion)) {
            double angle; 
            tokenRecognized = ReadAngle(file,token,angle);
            if (tokenRecognized) rangeOfMotion = UnitsToCounts(angle);
        } else if (!strcmp(token,TokenHasHardLimits)) {
            tokenRecognized = PMDUtils::ReadBool(file,token,hasHardLimits);
        } else if (!strcmp(token,TokenHasHomeSensor)) {
            tokenRecognized = PMDUtils::ReadBool(file,token, hasHomeSensor);
        } else if (!strcmp(token,TokenLimitsMayBind)) {
            tokenRecognized = PMDUtils::ReadBool(file,token, limitsMayBind);
        } else if (!strcmp(token,TokenHomingMode)) {
            PMDUtils::ReadToken(file,token);
            if (!strcmp(token,TokenNoHoming))           homingMode = NoHoming;
            else if (!strcmp(token,TokenReverseLimit))  homingMode = ReverseLimit;
            else if (!strcmp(token,TokenForwardLimit))  homingMode = ForwardLimit;
            else if (!strcmp(token,TokenBothLimits))    homingMode = BothLimits;
            else if (!strcmp(token,TokenHomeAndIndex))  homingMode = HomeAndIndex;
            else tokenRecognized = false;
        } else if (!strcmp(token,TokenHasLimitSensors)) {
            tokenRecognized = PMDUtils::ReadBool(file,token,hasLimitSensors);
        } else if (!strcmp(token,TokenHomeSignalPolarity)) {
            tokenRecognized = ReadPolarity(file,token,homeSignalPolarity);
        } else if (!strcmp(token,TokenLimitSignalPolarity)) {
            tokenRecognized = ReadPolarity(file,token,limitSignalPolarity);
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}

//----------------------------------------------------------------------------
const char TokenPos[] = "pos";
const char TokenVel[] = "vel";
const char TokenAcc[] = "acc";
const char TokenDec[] = "dec";
const char TokenJerk[] = "jerk";
void PMDAxisControl::ReadProfile(FILE *file, char *token, Profile &profile) {
    bool tokenRecognized = true;
    PMDUtils::ReadToken(file,token);
    do {
        if (!strcmp(token,TokenPos))
            tokenRecognized = ReadAngle(file,token,profile.pos);
        else if (!strcmp(token,TokenVel))
            tokenRecognized = ReadAngle(file,token,profile.vel);
        else if (!strcmp(token,TokenAcc))
            tokenRecognized = ReadAngle(file,token,profile.acc);
        else if (!strcmp(token,TokenDec))
            tokenRecognized = ReadAngle(file,token,profile.dec);
        else if (!strcmp(token,TokenJerk))
            tokenRecognized = ReadAngle(file,token,profile.jerk);
        else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}

//----------------------------------------------------------------------------
const char TokenKp[] = "kp";
const char TokenKd[] = "kd";
const char TokenKi[] = "ki";
const char TokenKvff[] = "kvff";
const char TokenKaff[] = "kaff";
const char TokenKout[] = "kout";
const char TokenIl[] = "il";
const char TokenOl[] = "ol";
const char TokenBias[] = "bias";
const char TokenElim[] = "elim";
void PMDAxisControl::ReadFilter(FILE *file, char *token, ServoFilter &filter) {
    bool tokenRecognized = true;
    unsigned int val;
    PMDUtils::ReadToken(file,token);
    do {
        if (!strcmp(token,TokenKp)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.kP = val;
        } else if (!strcmp(token,TokenKd)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.kD = val;
        } else if (!strcmp(token,TokenKi)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.kI = val;
        } else if (!strcmp(token,TokenKvff)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.kVFF = val;
        } else if (!strcmp(token,TokenKaff)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.kAFF = val;
        } else if (!strcmp(token,TokenKout)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.kOut = val;
        } else if (!strcmp(token,TokenIl)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%lu",&filter.integrationLimit) == 1;
        } else if (!strcmp(token,TokenOl)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.motorLimit = val;
        } else if (!strcmp(token,TokenBias)) {
            PMDUtils::ReadToken(file,token);
            tokenRecognized = sscanf_s(token,"%u",&val) == 1;
            filter.motorBias = val;
        } else if (!strcmp(token,TokenElim)) {
            double elim;
            tokenRecognized = ReadAngle(file,token,elim);
            if (tokenRecognized)
                filter.errorLimit = PMDAxisControl::UnitsToCounts(elim);
        } else tokenRecognized = false;
        if (tokenRecognized) PMDUtils::ReadToken(file,token);
    } while (!feof(file) && tokenRecognized);
}

//----------------------------------------------------------------------------
bool PMDAxisControl::ReadAxisStateFromFile() {
    char fName[100];
    stringstream stream(stringstream::in | stringstream::out);
//    stringstream stream(fName,100);
    stream << controller->uniqueID << '-' << uniqueID << ".home" << ends;
    stream >> fName;

    ifstream fp(fName,ios::in);
    if (fp.is_open()) {
        long pos;
        long lim[4];

        // Get the values from the file.
        fp >> pos >> lim[0] >> lim[1] >> lim[2] >> lim[3];

        SetHomingLimits(lim[0],lim[1],lim[2],lim[3]);
        EnableAmp();
        fp.close();
        return true;
    } else {
        return false;
    }
}
//----------------------------------------------------------------------------
bool PMDAxisControl::WriteAxisStateToFile() {
    char fName[100];
    stringstream stream(stringstream::in | stringstream::out);
    stream << controller->uniqueID << '-' << uniqueID << ".home" << ends;
    stream >> fName;
    ofstream fp(fName,ios::out);

    if (!fp) {
        return false;
    } else {
        long pos,lim[4];
        GetActualPosition(pos);
        GetHomingLimits(lim[0],lim[1],lim[2],lim[3]);
        fp << pos << ' ' << lim[0] << ' ' << lim[1] << ' ' << lim[2] << ' ' << lim[3] << endl;
        fp.close();
        return true;
    }
}
