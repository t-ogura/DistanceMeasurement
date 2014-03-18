#if !defined (PMD_H)
#define	PMD_H

//////////////////////////////////////////////////////////////////////////
// Copyright © 2002 by Bryn Wolfe and Metrica Inc.                        //
// All rights reserved. No part of this software or source code may be  //
// used or reproduced in any form or by any means, or stored in a       //
// database or retrieval system, without prior written aprroval from    //
// Metrica. This notice must not be removed or modified under penalty   //
// of United States copyright law.                                      //
//////////////////////////////////////////////////////////////////////////
//  PMD.h (adapted from PMD's c-motion.h) -- PMD Navigator and Pilot API

// PROGRAMMERS NOTE:
// This class implements all of the functions defined in the PMD programmers
// reference. All parameters are in the native units of the PMD controller.
// Any variations to those parameters must be accomodated through a higher-
// level or derived class.


#define CMOTION_MAJOR_VERSION	2
#define CMOTION_MINOR_VERSION	0;

#include "PMDTypes.h"
#include "PMDErrorCodes.h"
#include "PMDTransport.h"
#include "PortableSerial.h"     // For def of Parity type

class PMD : public PMDTransport {
public:

    PMD(PMDIOTransport* pmdIOTransport = NULL, PMDAxis axis = PMDAxis1);
    void SetTransportAndAxis(PMDIOTransport* pmdIOTransport, PMDAxis axis);
    
    PMDuint16 SetProfileMode(PMDuint16 mode);
    PMDuint16 GetProfileMode(PMDuint16 &mode);
    PMDuint16 SetPosition(PMDint32 position);
    PMDuint16 GetPosition(PMDint32 &position);
    PMDuint16 SetVelocity(PMDint32 velocity);
    PMDuint16 GetVelocity(PMDint32 &velocity);
    PMDuint16 SetStartVelocity(PMDuint32 velocity);
    PMDuint16 GetStartVelocity(PMDuint32 &velocity);
    PMDuint16 SetAcceleration(PMDuint32 acceleration);
    PMDuint16 GetAcceleration(PMDuint32 &acceleration);
    PMDuint16 SetDeceleration(PMDuint32 deceleration);
    PMDuint16 GetDeceleration(PMDuint32 &deceleration);
    PMDuint16 SetJerk(PMDuint32 jerk);
    PMDuint16 GetJerk(PMDuint32 &jerk);
    PMDuint16 SetGearRatio(PMDint32 ratio);
    PMDuint16 GetGearRatio(PMDint32 &ratio);
    PMDuint16 SetGearMaster(PMDAxis masterAxis, PMDuint8 source);
    PMDuint16 GetGearMaster(PMDAxis &masterAxis, PMDuint8 &source);
    PMDuint16 SetStopMode(PMDuint16 mode);
    PMDuint16 GetStopMode(PMDuint16 &mode);
    PMDuint16 GetCommandedPosition(PMDint32 &position);
    PMDuint16 GetCommandedVelocity(PMDint32 &velocity);
    PMDuint16 GetCommandedAcceleration(PMDint32 &acceleration);

    // Servo Filter
    PMDuint16 SetKp(PMDuint16 kp);
    PMDuint16 GetKp(PMDuint16 &kp);
    PMDuint16 SetKd(PMDuint16 kd);
    PMDuint16 GetKd(PMDuint16 &kd);
    PMDuint16 SetKi(PMDuint16 ki);
    PMDuint16 GetKi(PMDuint16 &ki);
    PMDuint16 SetKvff(PMDuint16 kvff);
    PMDuint16 GetKvff(PMDuint16 &kvff);
    PMDuint16 SetKaff(PMDuint16 kaff);
    PMDuint16 GetKaff(PMDuint16 &kaff);
    PMDuint16 SetKout(PMDuint16 kout);
    PMDuint16 GetKout(PMDuint16 &kout);
    PMDuint16 SetIntegrationLimit(PMDuint32 limit);
    PMDuint16 GetIntegrationLimit(PMDuint32 &limit);
    PMDuint16 SetLimitSwitchMode(PMDuint16 mode);
    PMDuint16 GetLimitSwitchMode(PMDuint16 &mode);
    PMDuint16 SetMotorLimit(PMDuint16 limit);
    PMDuint16 GetMotorLimit(PMDuint16 &limit);
    PMDuint16 SetMotorBias(PMDuint16 bias);
    PMDuint16 GetMotorBias(PMDuint16 &bias);
    PMDuint16 SetPositionErrorLimit(PMDuint32 limit);
    PMDuint16 GetPositionErrorLimit(PMDuint32 &limit);
    PMDuint16 SetAutoStopMode(PMDuint16 mode);
    PMDuint16 GetAutoStopMode(PMDuint16 &mode);
    PMDuint16 SetDerivativeTime(PMDuint16 derivativeTime);
    PMDuint16 GetDerivativeTime(PMDuint16 &derivativeTime);
    PMDuint16 SetSettleTime(PMDuint16 settleTime);
    PMDuint16 GetSettleTime(PMDuint16 &settleTime);
    PMDuint16 SetSettleWindow(PMDuint16 settleWindow);
    PMDuint16 GetSettleWindow(PMDuint16 &settleWindow);
    PMDuint16 SetTrackingWindow(PMDuint16 trackingWindow);
    PMDuint16 GetTrackingWindow(PMDuint16 &trackingWindow);
    PMDuint16 SetMotionCompleteMode(PMDuint16 mode);
    PMDuint16 GetMotionCompleteMode(PMDuint16 &mode);
    PMDuint16 ClearPositionError();
    PMDuint16 GetDerivative(PMDint16 &derivative);
    PMDuint16 GetIntegral(PMDint32 &integral);
    PMDuint16 GetPositionError(PMDint32 &positionError);
    PMDuint16 SetSampleTime(PMDuint16 sampleTime);
    PMDuint16 GetSampleTime(PMDuint16 &sampleTime);

    // Parameter Update & Breakpoints
    PMDuint16 SetBreakpoint(PMDuint16 breakpointID, 
        PMDAxis breakAxis, PMDuint8 action, PMDuint8 trigger);
    PMDuint16 GetBreakpoint(PMDuint16 breakpointID, 
        PMDAxis &breakAxis, PMDuint8 &action, PMDuint8 &trigger);
    PMDuint16 SetBreakpointValue(PMDuint16 breakpointID, 
        PMDint32 breakpointValue);
    PMDuint16 GetBreakpointValue(PMDuint16 breakpointID, 
        PMDint32 &breakpointValue);
    PMDuint16 Update();
    PMDuint16 MultiUpdate(PMDuint16 axisMask);

    // Interrupt Processing
    PMDuint16 SetInterruptMask(PMDuint16 interruptMask);
    PMDuint16 GetInterruptMask(PMDuint16 &interruptMask);
    PMDuint16 ClearInterrupt();
    PMDuint16 GetInterruptAxis(PMDuint16 &interruptingAxisMask);

    // Status Register Control
    PMDuint16 ResetEventStatus(PMDuint16 eventStatus);
    PMDuint16 GetEventStatus(PMDuint16 &eventStatus);
    PMDuint16 GetActivityStatus(PMDuint16 &activityStatus);
    PMDuint16 SetSignalSense(PMDuint16 mask);
    PMDuint16 GetSignalSense(PMDuint16 &mask);
    PMDuint16 GetSignalStatus(PMDuint16 &signalStatus);

    // Encoder
    PMDuint16 AdjustActualPosition(PMDint32 position);
    PMDuint16 SetActualPosition(PMDint32 position);
    PMDuint16 GetActualPosition(PMDint32 &position);
    PMDuint16 SetActualPositionUnits(PMDuint16 mode);
    PMDuint16 GetActualPositionUnits(PMDuint16 &mode);
    PMDuint16 SetCaptureSource(PMDuint16 captureSource);
    PMDuint16 GetCaptureSource(PMDuint16 &captureSource);
    PMDuint16 SetEncoderSource(PMDuint16 encoderSource);
    PMDuint16 GetEncoderSource(PMDuint16 &encoderSource);
    PMDuint16 SetEncoderModulus(PMDuint16 modulus);
    PMDuint16 GetEncoderModulus(PMDuint16 &modulus);
    PMDuint16 SetEncoderToStepRatio(PMDuint16 encoderCounts, PMDuint16 steps);
    PMDuint16 GetEncoderToStepRatio(PMDuint16 &encoderCounts, PMDuint16 &steps);
    PMDuint16 GetActualVelocity(PMDint32 &actualValue);
    PMDuint16 GetCaptureValue(PMDint32 &captureValue);

    // Motor
    PMDuint16 SetOutputMode(PMDuint16 mode);
    PMDuint16 GetOutputMode(PMDuint16 &mode);
    PMDuint16 SetMotorMode(PMDuint16 mode);
    PMDuint16 GetMotorMode(PMDuint16 &mode);
    PMDuint16 SetMotorCommand(PMDint16 motorCommand);
    PMDuint16 GetMotorCommand(PMDint16 &motorCommand);
    PMDuint16 GetCurrentMotorCommand(PMDint16 &motorCommand);

    // Commutation
    PMDuint16 SetCommutationMode(PMDuint16 mode);
    PMDuint16 GetCommutationMode(PMDuint16 &mode);
    PMDuint16 SetNumberPhases(PMDuint16 numberPhases);
    PMDuint16 GetNumberPhases(PMDuint16 &numberPhases);
    PMDuint16 SetPhaseInitializeMode(PMDuint16 mode);
    PMDuint16 GetPhaseInitializeMode(PMDuint16 &mode);
    PMDuint16 SetPhasePrescale(PMDuint16 phasePrescale);
    PMDuint16 GetPhasePrescale(PMDuint16 &phasePrescale);
    PMDuint16 SetPhaseCounts(PMDuint16 phaseCounts);
    PMDuint16 GetPhaseCounts(PMDuint16 &phaseCounts);
    PMDuint16 SetPhaseInitializeTime(PMDuint16 phaseInitTime);
    PMDuint16 GetPhaseInitializeTime(PMDuint16 &phaseInitTime);
    PMDuint16 SetPhaseOffset(PMDuint16 phaseOffset);
    PMDuint16 GetPhaseOffset(PMDuint16 &phaseOffset);
    PMDuint16 SetPhaseAngle(PMDuint16 phaseAngle);
    PMDuint16 GetPhaseAngle(PMDuint16 &phaseAngle);
    PMDuint16 SetPhaseCorrectionMode(PMDuint16 mode);
    PMDuint16 GetPhaseCorrectionMode(PMDuint16 &mode);
    PMDuint16 InitializePhase();
    PMDuint16 GetPhaseCommand(PMDuint16 phase, PMDint16 &command);

    // External Memory
    PMDuint16 SetBufferStart(PMDuint16 bufferID, PMDuint32 bufferStart);
    PMDuint16 GetBufferStart(PMDuint16 bufferID, PMDuint32 &bufferStart);
    PMDuint16 SetBufferLength(PMDuint16 bufferID, PMDuint32 bufferLength);
    PMDuint16 GetBufferLength(PMDuint16 bufferID, PMDuint32 &bufferLength);
    PMDuint16 SetBufferFunction(PMDuint16 function, PMDint16 bufferID);
    PMDuint16 GetBufferFunction(PMDuint16 function, PMDint16 &bufferID);
    PMDuint16 WriteBuffer(PMDuint16 bufferID, PMDint32 data);
    PMDuint16 ReadBuffer(PMDuint16 bufferID, PMDint32 &data);
    PMDuint16 SetBufferWriteIndex(PMDuint16 bufferID, PMDuint32 writeIndex);
    PMDuint16 GetBufferWriteIndex(PMDuint16 bufferID, PMDuint32 &writeIndex);
    PMDuint16 SetBufferReadIndex(PMDuint16 bufferID, PMDuint32 readIndex);
    PMDuint16 GetBufferReadIndex(PMDuint16 bufferID, PMDuint32 &readIndex);

    // Trace Operations
    PMDuint16 SetTraceMode(PMDuint16 mode);
    PMDuint16 GetTraceMode(PMDuint16 &mode);
    PMDuint16 SetTracePeriod(PMDuint16 tracePeriod);
    PMDuint16 GetTracePeriod(PMDuint16 &tracePeriod);
    PMDuint16 SetTraceVariable(PMDuint16 traceID, PMDAxis traceAxis, PMDuint8 variable);
    PMDuint16 GetTraceVariable(PMDuint16 traceID, PMDAxis &traceAxis, PMDuint8 &variable);
    PMDuint16 SetTraceStart(PMDAxis traceAxis, PMDuint8 condition, PMDuint8 bit, PMDuint8 state);
    PMDuint16 GetTraceStart(PMDAxis &traceAxis, PMDuint8 &condition, PMDuint8 &bit, PMDuint8 &state);
    PMDuint16 SetTraceStop(PMDAxis traceAxis, PMDuint8 condition, PMDuint8 bit, PMDuint8 state);
    PMDuint16 GetTraceStop(PMDAxis &traceAxis, PMDuint8 &condition, PMDuint8 &bit, PMDuint8 &state);
    PMDuint16 GetTraceStatus(PMDuint16 &status);
    PMDuint16 GetTraceCount(PMDuint32 &count);

    // Miscellaneous
    PMDuint16 SetAxisMode(PMDuint16 mode);
    PMDuint16 GetAxisMode(PMDuint16 &mode);
    PMDuint16 SetAxisOutSource(PMDAxis outAxis, PMDuint8 bit, PMDuint8 sourceRegister);
    PMDuint16 GetAxisOutSource(PMDAxis &outAxis, PMDuint8 &bit, PMDuint8 &sourceRegister);
    PMDuint16 WriteIO(PMDuint16 address, PMDuint16 data);
    PMDuint16 ReadIO(PMDuint16 address, PMDuint16 &data);
    PMDuint16 ReadAnalog(PMDuint16 analogID, PMDuint16 &data);
    PMDuint16 Reset();
    PMDuint16 NoOperation();
    PMDuint16 GetVersion(PMDuint16 &generation, PMDuint16 &motorType, 
        PMDuint16 &numberAxes, PMDuint16 &special,
        PMDuint16 &custom, PMDuint16 &major, PMDuint16 &minor);
    PMDuint16 GetHostIOError(PMDuint16 &hostIOError);

    // Override this port configuration method to handle both the host and 
    //controller parameters
    PMDuint16 SetSerialPortMode(tagPMDSerialBaudRate baud, 
                                tagPMDSerialParity parity, 
                                tagPMDSerialStopBits stopBits, 
                                tagPMDSerialProtocol protocol, 
                                PMDuint8 multiDropID);
    PMDuint16 GetSerialPortMode(tagPMDSerialBaudRate &baud, 
                                tagPMDSerialParity &parity, 
                                tagPMDSerialStopBits &stopBits, 
                                tagPMDSerialProtocol &protocol, 
                                PMDuint8 &multiDropID);
    PMDuint16 SetSerialPortMode(int baud, 
                                PortableSerial::Parity parity, 
                                PortableSerial::StopBits stopBits, 
                                tagPMDSerialProtocol protocol, 
                                PMDuint8 multiDropID);
    PMDuint16 GetSerialPortMode(int &baud, 
                                PortableSerial::Parity &parity,
                                PortableSerial::StopBits &stopBits, 
                                tagPMDSerialProtocol &protocol, 
                                PMDuint8 &multiDropID);
    
    PMDuint16 SetDiagnosticPortMode(PMDuint16 mode);
    PMDuint16 GetDiagnosticPortMode(PMDuint16 &mode);
    PMDuint16 GetTime(PMDuint32 &numberServoCycles);
    
    PMDuint16 GetChecksum(PMDuint32 &checksum);
    
    PMDuint16 SetStepRange(PMDuint16 range);
    PMDuint16 GetStepRange(PMDuint16 &range);
    
    static void GetCMotionVersion(PMDuint8 &MajorVersion, PMDuint8 &MinorVersion);

private:
        bool isConnected;

};

#endif
