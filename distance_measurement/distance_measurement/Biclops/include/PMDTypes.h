#ifndef PMD_CommonTypes
#define PMD_CommonTypes

//  PMDtypes.h -- common type declarations
//
//  Performance Motion Devices, Inc.
//

#include <math.h>       // for pow()

// common types
#define PMDnull 0
#define nibbleMask 0x0F
#define byteMask 0xFF
#define PMDAxis1 0
#define PMDAxis2 1
#define PMDAxis3 2
#define PMDAxis4 3
#define PMDNoAxisMask 0x00
#define PMDAxis1Mask 0x01
#define PMDAxis2Mask 0x02
#define PMDAxis3Mask 0x04
#define PMDAxis4Mask 0x08
#define PMDBreakpoint1 0
#define PMDBreakpoint2 1
#define PMDActivityPhasingInitializedMask 0x0001
#define PMDActivityAtMaximumVelocityMask 0x0002
#define PMDActivityTrackingMask 0x0004
#define PMDActivityProfileModeMask 0x0038
#define PMDActivityAxisSettledMask 0x0080
#define PMDActivityMotorOnMask 0x0100
#define PMDActivityPositionCaptureMask 0x0200
#define PMDActivityInMotionMask 0x0400
#define PMDActivityInPositiveLimitMask 0x0800
#define PMDActivityInNegativeLimitMask 0x1000
#define PMDActivityStatusMask 0x1FB
#define PMDEventMotionCompleteMask 0x0001
#define PMDEventWrapAroundMask 0x0002
#define PMDEventBreakpoint1Mask 0x0004
#define PMDEventCaptureReceivedMask 0x0008
#define PMDEventMotionErrorMask 0x0010
#define PMDEventInPositiveLimitMask 0x0020
#define PMDEventInNegativeLimitMask 0x0040
#define PMDEventInstructionErrorMask 0x0080
#define PMDEventCommutationErrorMask 0x0800
#define PMDEventBreakpoint2Mask 0x4000
#define PMDEventStatusMask 0x48FF
#define PMDSignalEncoderAMask 0x0001
#define PMDSignalEncoderBMask 0x0002
#define PMDSignalEncoderIndexMask 0x0004
#define PMDSignalEncoderHomeMask 0x0008
#define PMDSignalPositiveLimitMask 0x0010
#define PMDSignalNegativeLimitMask 0x0020
#define PMDSignalAxisInMask 0x0040
#define PMDSignalHallAMask 0x0080
#define PMDSignalHallBMask 0x0100
#define PMDSignalHallCMask 0x0200
#define PMDSignalAxisOutMask 0x0400
#define PMDSignalMotorOutputInvertMask 0x1000
#define PMDSignalMask 0x07FF
#define PMDTraceStatusMode 0x0001
#define PMDTraceStatusActivity 0x0002
#define PMDTraceStatusDataWrap 0x0004
#define PMDTraceStatusMask 0x07
#define PMDActivityPhasingInitializedBit 0
#define PMDActivityAtMaximumVelocityBit 1
#define PMDActivityTrackingBit 2
#define PMDActivityAxisSettledBit 7
#define PMDActivityMotorOnBit 8
#define PMDActivityPositionCaptureBit 9
#define PMDActivityInMotionBit 10
#define PMDActivityInPositiveLimitBit 11
#define PMDActivityInNegitiveLimitBit 12
#define PMDEventMotionCompleteBit 0
#define PMDEventWrapAroundBit 1
#define PMDEventBreakpoint1Bit 2
#define PMDEventCaptureReceivedBit 3
#define PMDEventMotionErrorBit 4
#define PMDEventInPositiveLimitBit 5
#define PMDEventInNegativeLimitBit 6
#define PMDEventInstructionErrorBit 7
#define PMDEventCommutationErrorBit 11
#define PMDEventBreakpoint2Bit 14
#define PMDSignalEncoderABit 0
#define PMDSignalEncoderBBit 1
#define PMDSignalEncoderIndexBit 2
#define PMDSignalEncoderHomeBit 3
#define PMDSignalPositiveLimitBit 4
#define PMDSignalNegativeLimitBit 5
#define PMDSignalAxisInBit 6
#define PMDSignalHallABit 7
#define PMDSignalHallBBit 8
#define PMDSignalHallCBit 9
#define PMDSignalAxisOutBit 10
#define PMDSignalMotorOutputInvertBit 12

typedef long PMDint32;
typedef unsigned long  PMDuint32;
typedef long PMDlong32;
typedef unsigned short PMDuint16;
typedef short PMDint16;
typedef unsigned char  PMDuint8;

typedef PMDuint16 PMDAxis;

//typedef enum {nibbleMask=0x0F, byteMask=0xFF};

const int PMDMaxAxes = 4;
const double PMDVelScaling = 1<<16;
const double PMDAccScaling = 1<<16;
const double PMDJerkScaling = pow(2.0,32.0);//1<<32;


/*
typedef enum {
        PMDAxis1=0,
        PMDAxis2=1,
        PMDAxis3=2,
        PMDAxis4=3
};

typedef enum {
        PMDNoAxisMask=0x00,
        PMDAxis1Mask=0x01,
        PMDAxis2Mask=0x02,
        PMDAxis3Mask=0x04,
        PMDAxis4Mask=0x08
};
  */
// Profile Generation
typedef enum {
        PMDTrapezoidalProfile=0,
        PMDVelocityContouringProfile=1,
        PMDSCurveProfile=2,
        PMDElectronicGearProfile=3,
        PMDExternalProfile=4
} tagPMDProfileMode;

typedef enum {
        PMDPositionSourceActual=0, 
        PMDPositionSourceCommanded=1
} tagPMDPositionSource;

typedef enum {
        PMDNoStopMode=0, 
        PMDAbruptStopMode=1, 
        PMDSmoothStopMode=2
} tagPMDStopMode;

// Servo Filter
typedef enum {
        PMDLimitDisabled=0, 
        PMDLimitEnabled=1
} tagPMDLimitMode;

typedef enum {
        PMDAutoStopDisabled=0, 
        PMDAutoStopEnabled=1
} tagPMDAutoStopMode;

typedef enum {
        PMDMotionCompleteCommandedPosition=0, 
        PMDMotionCompleteActualPosition=1
} tagPMDMotionCompleteMode;

/*
// Parameter Update & Breakpoints
typedef enum {
        PMDBreakpoint1=0,
        PMDBreakpoint2=1
};
*/

typedef enum {
        PMDBreakpointDisable=0,
        PMDBreakpointGreaterOrEqualCommandedPosition=1,
        PMDBreakpointLessOrEqualCommandedPosition=2,
        PMDBreakpointGreaterOrEqualActualPosition=3,
        PMDBreakpointLessOrEqualActualPosition=4,
        PMDBreakpointCommandedPositionCrossed=5,
        PMDBreakpointActualPositionCrossed=6,
        PMDBreakpointTime=7,
        PMDBreakpointEventStatus=8,
        PMDBreakpointActivityStatus=9,
        PMDBreakpointSignalStatus=10
} tagPMDBreakpointTrigger;

typedef enum {
        PMDBreakpointNoAction=0,
        PMDBreakpointActionUpdate=1,
        PMDBreakpointActionAbruptStop=2,
        PMDBreakpointActionSmoothStop=3,
        PMDBreakpointActionMotorOff=4
} tagPMDBreakpointAction;
/*
// Status Register Control
typedef enum {
        PMDActivityPhasingInitializedMask=0x0001,
        PMDActivityAtMaximumVelocityMask=0x0002,
        PMDActivityTrackingMask=0x0004,
        PMDActivityProfileModeMask=0x0038,
        PMDActivityAxisSettledMask=0x0080,
        PMDActivityMotorOnMask=0x0100,
        PMDActivityPositionCaptureMask=0x0200,
        PMDActivityInMotionMask=0x0400,
        PMDActivityInPositiveLimitMask=0x0800,
        PMDActivityInNegativeLimitMask=0x1000,
        PMDActivityStatusMask=0x1FBF
};

typedef enum {
        PMDEventMotionCompleteMask=0x0001,
        PMDEventWrapAroundMask=0x0002,
        PMDEventBreakpoint1Mask=0x0004,
        PMDEventCaptureReceivedMask=0x0008,
        PMDEventMotionErrorMask=0x0010,
        PMDEventInPositiveLimitMask=0x0020,
        PMDEventInNegativeLimitMask=0x0040,
        PMDEventInstructionErrorMask=0x0080,
        PMDEventCommutationErrorMask=0x0800,
        PMDEventBreakpoint2Mask=0x4000,
        PMDEventStatusMask=0x48FF
};

typedef enum {
        PMDSignalEncoderAMask=0x0001,
        PMDSignalEncoderBMask=0x0002,
        PMDSignalEncoderIndexMask=0x0004,
        PMDSignalEncoderHomeMask=0x0008,
        PMDSignalPositiveLimitMask=0x0010,
        PMDSignalNegativeLimitMask=0x0020,
        PMDSignalAxisInMask=0x0040,
        PMDSignalHallAMask=0x0080,
        PMDSignalHallBMask=0x0100,
        PMDSignalHallCMask=0x0200,
        PMDSignalAxisOutMask=0x0400,
        PMDSignalMotorOutputInvertMask=0x1000,
        PMDSignalMask=0x07FF
};*/

// Encoder
typedef enum {
        PMDCaptureSourceIndex=0,
        PMDCaptureSourceHome=1
} tagPMDCaptureSource;

typedef enum {
        PMDEncoderSourceIncremental=0,
        PMDEncoderSourceParallel=1
} tagPMDEncoderSource;

// Motor
typedef enum {
        PMDMotorOutputDAC=0,
        PMDMotorOutputPWMSignMagnitude=1,
        PMDMotorOutputPWM5050Magnitude=2
} tagPMDMotorOutputMode;

typedef enum {
        PMDMotorOff=0,
        PMDMotorOn=1
} tagPMDMotorMode;

// Commutation
typedef enum {
        PMDCommutationModeSinusoidal=0,
        PMDCommutationModeHallBased=1,
        PMDCommutationModeMicrostepping=2
} tagPMDCommutationMode;

typedef enum {
        PMDPhaseInitAlgorithmic=0,
        PMDPhaseInitHallBased=1
} tagPMDPhaseInitializeMode;

typedef enum {
        PMDPhaseCorrectionDisabled=0,
        PMDPhaseCorrectionEnabled=1
} tagPMDPhaseCorrectionMode;

typedef enum {
        PMDPhasePrescaleOff=0,
        PMDPhasePrescaleOn=1
} tagPMDPhasePrescaleMode;

typedef enum {
        PMDPhaseA=0,
        PMDPhaseB=1,
        PMDPhaseC=2
} tagPMDPhaseNumber;

// Trace Operations
typedef enum {
        PMDTrace1=0,
        PMDTrace2=1,
        PMDTrace3=2,
        PMDTrace4=3
} tagPMDTraceNumber;

typedef enum {
        PMDTraceOneTime=0,
        PMDTraceRollingBuffer=1
} tagPMDTraceMode;

typedef enum {
        PMDTraceNoVariable=0,
        PMDTracePositionError=1,
        PMDTraceCommandedPosition=2,
        PMDTraceCommandedVelocity=3,
        PMDTraceCommandedAcceleration=4,
        PMDTraceActualPosition=5,
        PMDTraceActualVelocity=6,
        PMDTraceCurrentMotorCommand=7,
        PMDTraceTime=8,
        PMDTraceCaptureValue=9,
        PMDTraceIntegral=10,
        PMDTraceDerivative=11,
        PMDTraceEventStatus=12,
        PMDTraceActivityStatus=13,
        PMDTraceSignalStatus=14,
        PMDTracePhaseAngle=15,
        PMDTracePhaseOffset=16,
        PMDTracePhaseACommand=17,
        PMDTracePhaseBCommand=18,
        PMDTracePhaseCCommand=19,
        PMDTraceAnalogInput1=20,
        PMDTraceAnalogInput2=21,
        PMDTraceAnalogInput3=22,
        PMDTraceAnalogInput4=23,
        PMDTraceAnalogInput5=24,
        PMDTraceAnalogInput6=25,
        PMDTraceAnalogInput7=26,
        PMDTraceAnalogInput8=27
} tagPMDTraceVariable;

typedef enum {
        PMDTraceConditionImmediate=0,
        PMDTraceConditionUpdate=1,
        PMDTraceConditionEventStatus=2,
        PMDTraceConditionActivityStatus=3,
        PMDTraceConditionSignalStatus=4
} tagPMDTraceCondition;

typedef enum {
        PMDTraceTriggerStateLow=0,
        PMDTraceTriggerStateHigh=1
} tagPMDTraceTriggerState;
/*
typedef enum {
        PMDTraceStatusMode=0x0001,
        PMDTraceStatusActivity=0x0002,
        PMDTraceStatusDataWrap=0x0004,
        PMDTraceStatusMask=0x07
};

// Miscellaneous
typedef enum {
        PMDActivityPhasingInitializedBit=0,
        PMDActivityAtMaximumVelocityBit=1,
        PMDActivityTrackingBit=2,
        PMDActivityAxisSettledBit=7,
        PMDActivityMotorOnBit=8,
        PMDActivityPositionCaptureBit=9,
        PMDActivityInMotionBit=10,
        PMDActivityInPositiveLimitBit=11,
        PMDActivityInNegitiveLimitBit=12
};

typedef enum {
        PMDEventMotionCompleteBit=0,
        PMDEventWrapAroundBit=1,
        PMDEventBreakpoint1Bit=2,
        PMDEventCaptureReceivedBit=3,
        PMDEventMotionErrorBit=4,
        PMDEventInPositiveLimitBit=5,
        PMDEventInNegativeLimitBit=6,
        PMDEventInstructionErrorBit=7,
        PMDEventCommutationErrorBit=11,
        PMDEventBreakpoint2Bit=14
};

typedef enum {
        PMDSignalEncoderABit=0,
        PMDSignalEncoderBBit=1,
        PMDSignalEncoderIndexBit=2,
        PMDSignalEncoderHomeBit=3,
        PMDSignalPositiveLimitBit=4,
        PMDSignalNegativeLimitBit=5,
        PMDSignalAxisInBit=6,
        PMDSignalHallABit=7,
        PMDSignalHallBBit=8,
        PMDSignalHallCBit=9,
        PMDSignalAxisOutBit=10,
        PMDSignalMotorOutputInvertBit=12
};
*/
typedef enum {
        PMDAxisOutSourceNone=0,
        PMDAxisOutSourceEventStatus=1,
        PMDAxisOutSourceActivityStatus=2,
        PMDAxisOutSourceSignalStatus=3
} tagPMDAxisOutSource;

typedef enum {
        PMDDiagnosticPortModeLimited=0,
        PMDDiagnosticPortModeFull=1
} tagPMDDiagnosticPortMode;

typedef enum {
        PMDAxisOff=0,
        PMDAxisOn=1
} tagPMDAxisMode;

typedef enum {
        PMDSerialBaud1200=0,
        PMDSerialBaud2400=1,
        PMDSerialBaud9600=2,
        PMDSerialBaud19200=3,
        PMDSerialBaud57600=4,
        PMDSerialBaud115200=5,
        PMDSerialBaud250000=6,
        PMDSerialBaud416667=7
} tagPMDSerialBaudRate;

typedef enum {
        PMDSerial1StopBit=0,
        PMDSerial2StopBits=1
} tagPMDSerialStopBits;

typedef enum {
        PMDSerialProtocolPoint2Point=0,
        PMDSerialProtocolMultiDropUsingAddressBit=2,
		PMDSerialProtocolMultiDropUsingIdleLineDetection=3
} tagPMDSerialProtocol;

typedef enum {
        PMDSerialParityNone=0,
        PMDSerialParityOdd=1,
        PMDSerialParityEven=2
} tagPMDSerialParity;

typedef enum {
        PMDBrushedServo=1,
        PMDBrushlessServo=3,
        PMDMicroStepping=4,
        PMDStepping=5
} tagPMDMotorType;

#endif
