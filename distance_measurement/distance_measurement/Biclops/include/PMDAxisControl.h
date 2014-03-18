#if !defined PMDAXISCONTROL_H
#define PMDAXISCONTROL_H

#include <stdio.h>      // for FILE
#include <cstdio>          // for FILE defn

class PMDController;

#include "PMD.h"

class PMDAxisControl : public PMD {
public:

    typedef struct {
		PMDuint16 kP;               // Proportional gain
		PMDuint16 kD;               // Derivative gain
		PMDuint16 kI;               // Integral gain
		PMDuint16 kVFF;             // Velocity feed-forward
		PMDuint16 kAFF;             // Acceleration feed-forward
        PMDuint16 kOut;             // Output scale factor (%)
		PMDuint32 integrationLimit; // count*cycles
		PMDuint16 motorLimit;       // % of maximum
		PMDuint16 motorBias;        // Motor bias voltage(% of output)
		PMDuint32 errorLimit;       // counts
    } ServoFilter;

    typedef struct {
        PMDint32    pos;        // Counts
        PMDint32    vel;        // Counts/second
        PMDuint32   acc;        // Counts/second/second
        PMDuint32   dec;        // Counts/second/second
        PMDuint32   jerk;       // Counts/second/second/second
    } CountsProfile;

    typedef struct {
        double pos;                 // Units
        double vel;                 // Units/second
        double acc;                 // Units/second/second
        double dec;                 // Units/second/second
        double jerk;                // Units/second/second/second
    } Profile;

    // Control chip cycle times
    static const double CyclePeriodStepSizeInUSec;
    static const int NormalControllerCycleMin;
    static const int ExtendedControllerCycleMin;

    char uniqueID[50];
    PMDuint8 ctrlID;

    PMDAxisControl(PMDController *controller,
            PMDIOTransport* pmdIOTransport = NULL, PMDAxis axis = PMDAxis1);
    PMDAxisControl(FILE *file, char *token); // Constructor using configuration file.
    void SetDefaults();

    PMDController *GetController() {return controller;};

    // Configures the chip settings for the specific axis interface.
    // This method may be overridden from the defaults. 
    // See the implementation for default configuration details.
    virtual bool ConfigureHardware();

    // Load/store all axis parameters to/from a file.
    static const char *StartToken;
    static const char *EndToken;
    bool ReadParameters(FILE *file, char *token);
    bool WriteParameters(FILE *file);

    // Access to the servo control parameters. With the homing flag asserted 
    // (true), these methods get/set the homing control parameters.
    void GetFilter(ServoFilter& sp, bool homing = false);
    void SetFilter(const ServoFilter& sp, bool homing = false);

    // Access to profile generator parameters
    void GetProfile(Profile& profile, bool homing = false);
    void GetProfile(CountsProfile& profile, bool homing = false);
    void SetProfile(const Profile& profile, bool homing = false, 
                    bool doLoad = true);
    void SetProfile(const CountsProfile& profile, bool homing = false, 
                    bool doLoad = true);
    bool CropProfile(CountsProfile& profile);

    // Homing
    bool IsAlreadyHomed();
    bool AxisKnowsPosition();
    bool FindHome(bool forceHoming = false);
    void SetHomingLimits(
		    const long hardLimitForward, const long hardLimitReverse,
                    const long softLimitForward, const long softLimitReverse);
    void GetHomingLimits(
		    long& hardLimitForward, long& hardLimitReverse,
                    long& softLimitForward, long& softLimitReverse);

    // Axis motion control
    static const PMDuint16 MoveEventMask;
    static const PMDuint16 AutostopEventMask;
    void SetMoveWaitPeriod(unsigned long waitPeriod) {this->waitPeriod = waitPeriod;};
    unsigned long GetMoveWaitPeriod() { return waitPeriod;};
    void PreMove(bool waitForMotionToStop); // Only call if NOT using Move()
    void PostMove();                        // Only call if NOT using Move()
    bool WaitForMotionToStop(bool includeCaptureEvent = false);
    bool Move(bool waitForMotionToStop = true);
    bool MoveWithCaptureInterrupt(bool waitForMotionToStop = true);
											// Returns from move if capture event occurs
    bool Move(bool waitForMotionToStop, double pos, 
        double vel = 0.0, double acc = 0.0,
        double dec = 0.0, double jerk = 0.0);
    bool Move(bool waitForMotionToStop, PMDint32 pos, 
        PMDint32 vel = 0, PMDuint32 acc = 0,
        PMDuint32 dec = 0, PMDuint32 jerk = 0);

    bool IsMotionDone(bool includeCaptureEvent = false);

    // Amplifier control
    bool IsAmpEnabled() { return ampIsOn;};
    void EnableAmp();
    void DisableAmp();

    // Brake control
    bool HasBrake() { return hasBrake;};
    void EngageBrake();
    void DisengageBrake();
    bool IsBrakeEngaged();

    // Composite joint commands
    void Park();    // Lock brake, disable amp, and turn off closed loop control.
    void Unpark();  // Turn on closed loop control, enable amp, and unlock brake.
    bool ParkAndSave(); // Park axis and save joint state to file
    bool RecoverFromParkAndSave();  // Just what it says

    // Encoder/real world units conversion
    double CountsToUnits(PMDint32 val) {return ((double)val)/countsPerAxisCycle;};
    PMDuint32 UnitsToCounts(double val) {return (PMDint32)(val*countsPerAxisCycle);};
    void CountsToProfile(Profile& profile, const CountsProfile& counts);
    void ProfileToCounts(const Profile& profile, CountsProfile& counts);

    // Conversions to/from native PMD units
    // These conversions are only used for sending values to a PMD controller
    // or getting values back from there. The PMD units are not used otherwise.
    PMDint32    CountsVelToPMD(PMDint32 countsVel);
    PMDuint32   CountsAccToPMD(PMDuint32 countsAcc);
    PMDuint32   CountsJerkToPMD(PMDuint32 countsJerk);
    PMDint32    PMDToCountsVel(PMDint32 pmdVel);
    PMDuint32   PMDToCountsAccToPMD(PMDuint32 pmdAcc);
    PMDuint32   PMDToCountsJerkToPMD(PMDuint32 pmdJerk);

    // Get the latest value of the event status register.
    PMDuint16 GetLastEventStatus();

    // Communication changes
    bool ChangeComm(int baud);

    // File parsing helper methods.
    bool ReadAngle(FILE *file, char *token, double &angle);
    bool ReadAxisStateFromFile();
    bool WriteAxisStateToFile();

private:
    
    enum {BrakeEngaged = 0, BrakeDisengaged = 1};
    static const PMDuint16 BrakeIOAddress;

    enum Polarity {ActiveHigh = 0, ActiveLow = 1};

    //Axis # within the controller is stored in PMDTransport via GetAxisNumber()

    bool configurationWasLoaded;    // True if config data was loaded from file
    // Actuator info
    bool            hasBrake;
    PMDuint16       brakeState;
    tagPMDMotorOutputMode 
                    ampType;
    Polarity        ampPolarity;
    bool            isBrushless;
    unsigned short  poleCount;
    tagPMDPhaseInitializeMode
                    phaseInitMode;
    bool            invertHalls;
    tagPMDCommutationMode 
                    commutationMode;
    bool            reverseMotorOutput;

    // Encoder info
    unsigned long   countsPerEncoderCycle;
    double          encoderCyclesPerAxisCycle;
    double          motorCyclesPerEncoderCycle;
    double          countsPerAxisCycle;
    double          countsPerMotorCycle;
//    unsigned long   countsPerUnitMeasure;
    unsigned long   rangeOfMotion;
    
    // Homing info
    enum HomingMode {NoHoming, ReverseLimit, ForwardLimit, BothLimits, HomeAndIndex}
                    homingMode;
    bool            isHomed;
    long            homeCountsOffset;
    bool            hasLimitSensors;
    bool            hasHardLimits;          // true if axis has hard limits
    bool            hasHomeSensor;          // true if a home sensor exists
    Polarity        homeSignalPolarity;
    Polarity        limitSignalPolarity;
    bool            limitsMayBind;          // true if hard limits can bind
                                            // such as with a screw drive
    ServoFilter     homingFilter;
    Profile         homingProfile;
    CountsProfile   homingProfileCounts;
    long            forwardLimit;
    long            reverseLimit;
    long            softForwardLimit;
    long            softReverseLimit;
    long            homeDelta;
    unsigned long   waitPeriod;
    bool mustEnableClosedLoopControl;

    ServoFilter     runFilter;
    Profile         runProfile;

    // active control values
    bool            eventStatusLoadedSinceLastMove;
    PMDuint16       signalSense;
    PMDuint16       eventStatus;
    PMDuint16       activityStatus;
    PMDuint16       signalStatus;
    ServoFilter     activeFilter;
    Profile         cmdProfile;
    Profile         actProfile;
    CountsProfile   cmdProfileCounts;
    CountsProfile   actProfileCounts;
    bool            ampIsOn;
    bool            brakeEngaged;

    int debugLevel;
    static const char*  classStr;

    void GoToLimit(CountsProfile &p);
    void WithdrawFromLimit(CountsProfile &p);
    bool FindHomeWithLimits();
    bool FindHomeWithHomeSensor();

    // Transfers commanded values to controller
    void SendProfileToController(const CountsProfile& countsProfile);

    // Reference to parent controller for access to cycle time value.
    PMDController   *controller;
    double GetCycleTimeInSecs();

    // File parsing helper methods.
    bool ReadPolarity(FILE *file, char *token, Polarity &polarity);
    void ReadMotorParameters(FILE *file, char *token);
    void ReadEncoderParameters(FILE *file, char *token);
    void ReadHomingParameters(FILE *file, char *token);
    void ReadProfile(FILE *file, char *token, Profile &profile);
    void ReadFilter(FILE *file, char *token, ServoFilter &filter);

};

#endif

