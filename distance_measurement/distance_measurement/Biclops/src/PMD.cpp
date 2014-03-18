//////////////////////////////////////////////////////////////////////////
// Copyright © 2002 by Bryn Wolfe and Metrica Inc.                        //
// All rights reserved. No part of this software or source code may be  //
// used or reproduced in any form or by any means, or stored in a       //
// database or retrieval system, without prior written aprroval from    //
// Metrica. This notice must not be removed or modified under penalty   //
// of United States copyright law.                                      //
//////////////////////////////////////////////////////////////////////////

#include "../include/PMDOPCodes.h"
#include "../include/PMDSerial.h"
#include "../include/PMD.h"
#include <iostream>
using namespace std;

const char classDbgHdr[] = "PMD::"; // For Debugging

// Constructors
PMD::PMD(PMDIOTransport* pmdIOTransport, PMDAxis axis) :
    PMDTransport(pmdIOTransport,axis) {
        isConnected = false;
}

void PMD::SetTransportAndAxis(PMDIOTransport* pmdIOTransport, PMDAxis axis) {
    PMDTransport(pmdIOTransport,axis);
}

// Profile Generation
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetProfileMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetProfileMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetProfileMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetProfileMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPosition(PMDint32 position) {
	return SendCommandLong(PMDOPSetPosition, position);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPosition(PMDint32 &position) {
	return SendCommandGetLong(PMDOPGetPosition, *((PMDuint32*)&position));
//	return SendCommandGetLong(PMDOPGetPosition, (PMDuint32)position);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetVelocity(PMDint32 velocity) {
	return SendCommandLong(PMDOPSetVelocity, velocity);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetVelocity(PMDint32 &velocity) {
	return SendCommandGetLong(PMDOPGetVelocity, *((PMDuint32*)&velocity));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetStartVelocity(PMDuint32 velocity) {
	return SendCommandLong(PMDOPSetStartVelocity, velocity);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetStartVelocity(PMDuint32 &velocity) {
	return SendCommandGetLong(PMDOPGetStartVelocity, velocity);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetAcceleration(PMDuint32 acceleration) {
	return SendCommandLong(PMDOPSetAcceleration, acceleration);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetAcceleration(PMDuint32 &acceleration) {
	return SendCommandGetLong(PMDOPGetAcceleration, acceleration);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetDeceleration(PMDuint32 deceleration) {
	return SendCommandLong(PMDOPSetDeceleration, deceleration);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetDeceleration(PMDuint32 &deceleration) {
	return SendCommandGetLong(PMDOPGetDeceleration, deceleration);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetJerk(PMDuint32 jerk) {
	return SendCommandLong(PMDOPSetJerk, jerk);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetJerk(PMDuint32 &jerk) {
	return SendCommandGetLong(PMDOPGetJerk, jerk);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetGearRatio(PMDint32 ratio) {
	return SendCommandLong(PMDOPSetGearRatio, ratio);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetGearRatio(PMDint32 &ratio) {
	return SendCommandGetLong(PMDOPGetGearRatio, *((PMDuint32*)&ratio));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetGearMaster(PMDAxis masterAxis, PMDuint8 source) {
	PMDint16 value = (masterAxis & nibbleMask) | ((source & nibbleMask) << 8);
	return SendCommandWord( PMDOPSetGearMaster, value);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetGearMaster(PMDAxis &masterAxis, PMDuint8 &source) {
	PMDuint16 result;
	PMDint16 value;

	result = SendCommandGetWord(PMDOPGetGearMaster, *((PMDuint16*)&value));
	masterAxis = (PMDAxis)(value & nibbleMask);
	source = (PMDuint8)((value >> 8) & nibbleMask);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetStopMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetStopMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetStopMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetStopMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetCommandedPosition(PMDint32 &position) {
	return SendCommandGetLong(PMDOPGetCommandedPosition, *((PMDuint32*)&position));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetCommandedVelocity(PMDint32 &velocity) {
	return SendCommandGetLong(PMDOPGetCommandedVelocity, *((PMDuint32*)&velocity));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetCommandedAcceleration(PMDint32 &acceleration) {
	return SendCommandGetLong(PMDOPGetCommandedAcceleration, *((PMDuint32*)&acceleration));
}


// Servo Filter
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetKp(PMDuint16 kp) {
	return SendCommandWord( PMDOPSetKp, kp);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetKp(PMDuint16 &kp) {
	return SendCommandGetWord(PMDOPGetKp, kp);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetKd(PMDuint16 kd) {
	return SendCommandWord( PMDOPSetKd, kd);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetKd(PMDuint16 &kd) {
	return SendCommandGetWord(PMDOPGetKd, kd);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetKi(PMDuint16 ki) {
	return SendCommandWord( PMDOPSetKi, ki);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetKi(PMDuint16 &ki) {
	return SendCommandGetWord(PMDOPGetKi, ki);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetKvff(PMDuint16 kvff) {
	return SendCommandWord( PMDOPSetKvff, kvff);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetKvff(PMDuint16 &kvff) {
	return SendCommandGetWord(PMDOPGetKvff, kvff);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetKaff(PMDuint16 kaff) {
	return SendCommandWord( PMDOPSetKaff, kaff);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetKaff(PMDuint16 &kaff) {
	return SendCommandGetWord(PMDOPGetKaff, kaff);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetKout(PMDuint16 kout) {
	return SendCommandWord( PMDOPSetKout, kout);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetKout(PMDuint16 &kout) {
	return SendCommandGetWord(PMDOPGetKout, kout);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetIntegrationLimit(PMDuint32 limit) {
	return SendCommandLong(PMDOPSetIntegrationLimit, limit);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetIntegrationLimit(PMDuint32 &limit) {
	return SendCommandGetLong(PMDOPGetIntegrationLimit, limit);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetLimitSwitchMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetLimitSwitchMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetLimitSwitchMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetLimitSwitchMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetMotorLimit(PMDuint16 limit) {
	return SendCommandWord( PMDOPSetMotorLimit, limit);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetMotorLimit(PMDuint16 &limit) {
	return SendCommandGetWord(PMDOPGetMotorLimit, limit);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetMotorBias(PMDuint16 bias) {
	return SendCommandWord( PMDOPSetMotorBias, bias);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetMotorBias(PMDuint16 &bias) {
	return SendCommandGetWord(PMDOPGetMotorBias, bias);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPositionErrorLimit(PMDuint32 limit) {
	return SendCommandLong(PMDOPSetPositionErrorLimit, limit);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPositionErrorLimit(PMDuint32 &limit) {
	return SendCommandGetLong(PMDOPGetPositionErrorLimit, limit);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetAutoStopMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetAutoStopMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetAutoStopMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetAutoStopMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetDerivativeTime(PMDuint16 derivativeTime) {
	return SendCommandWord( PMDOPSetDerivativeTime, derivativeTime);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetDerivativeTime(PMDuint16 &derivativeTime) {
	return SendCommandGetWord(PMDOPGetDerivativeTime, derivativeTime);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetSettleTime(PMDuint16 settleTime) {
	return SendCommandWord( PMDOPSetSettleTime, settleTime);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetSettleTime(PMDuint16 &settleTime) {
	return SendCommandGetWord(PMDOPGetSettleTime, settleTime);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetSettleWindow(PMDuint16 settleWindow) {
	return SendCommandWord( PMDOPSetSettleWindow, settleWindow);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetSettleWindow(PMDuint16 &settleWindow) {
	return SendCommandGetWord(PMDOPGetSettleWindow, settleWindow);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetTrackingWindow(PMDuint16 trackingWindow) {
	return SendCommandWord( PMDOPSetTrackingWindow, trackingWindow);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTrackingWindow(PMDuint16 &trackingWindow) {
	return SendCommandGetWord(PMDOPGetTrackingWindow, trackingWindow);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetMotionCompleteMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetMotionCompleteMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetMotionCompleteMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetMotionCompleteMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::ClearPositionError() {
	return SendCommand(PMDOPClearPositionError);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetDerivative(PMDint16 &derivative) {
	return SendCommandGetWord(PMDOPGetDerivative, *((PMDuint16*)&derivative));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetIntegral(PMDint32 &integral) {
	return SendCommandGetLong(PMDOPGetIntegral, *((PMDuint32*)&integral));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPositionError(PMDint32 &error) {
	return SendCommandGetLong(PMDOPGetPositionError, *((PMDuint32*)&error));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetSampleTime(PMDuint16 sampleTime) {
	return SendCommandWord( PMDOPSetSampleTime, sampleTime);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetSampleTime(PMDuint16 &sampleTime) {
	return SendCommandGetWord(PMDOPGetSampleTime, sampleTime);
}


// Parameter Update & Breakpoints
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetBreakpoint(PMDuint16 breakpointID, 
						   PMDAxis breakAxis, PMDuint8 action, PMDuint8 trigger) {
	PMDuint16 value = (breakAxis & nibbleMask) | 
		((action & nibbleMask) << 4) | ((trigger & byteMask) << 8);
	return SendCommandWordWord(PMDOPSetBreakpoint, (PMDuint16)breakpointID, value);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetBreakpoint(PMDuint16 breakpointID, 
						   PMDAxis &breakAxis, PMDuint8 &action, PMDuint8 &trigger) {
	PMDuint16 result;
	PMDuint16 value;

	result = SendCommandWordGetWord(PMDOPGetBreakpoint, breakpointID, value);

	breakAxis = (PMDAxis)(value & nibbleMask);
	action = (PMDuint8)((value >> 4) & nibbleMask);
	trigger = (PMDuint8)((value >> 8) & byteMask);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetBreakpointValue(PMDuint16 breakpointID, PMDint32 breakpointValue) {
	return SendCommandWordLong(PMDOPSetBreakpointValue, breakpointID, breakpointValue);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetBreakpointValue(PMDuint16 breakpointID, PMDint32 &breakpointValue) {
	return SendCommandWordGetLong(PMDOPGetBreakpointValue, breakpointID, 
        *((PMDuint32*)&breakpointValue));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::Update() {
	return SendCommand(PMDOPUpdate);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::MultiUpdate(PMDuint16 axisMask) {
	return SendCommandWord( PMDOPMultiUpdate, axisMask);
}


// Interrupt Processing
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetInterruptMask(PMDuint16 interruptMask) {
	return SendCommandWord( PMDOPSetInterruptMask, interruptMask);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetInterruptMask(PMDuint16 &interruptMask) {
	return SendCommandGetWord(PMDOPGetInterruptMask, interruptMask);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::ClearInterrupt() {
	PMDAxis axisNumber = GetAxisNumber();
	PMDuint16 result;

	// for the ClearInterrupt command, the axis number MUST be zero
	SetAxis(0);

	result = SendCommand(PMDOPClearInterrupt);

	SetAxis(axisNumber);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetInterruptAxis(PMDuint16 &interruptingAxisMask) {
	return SendCommandGetWord(PMDOPGetInterruptAxis, interruptingAxisMask);
}


// Status Register Control
//-----------------------------------------------------------------------------
PMDuint16 PMD::ResetEventStatus(PMDuint16 eventStatus) {
	return SendCommandWord( PMDOPResetEventStatus, eventStatus);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetEventStatus(PMDuint16 &eventStatus) {
    PMDuint16 cmdStatus = SendCommandGetWord(PMDOPGetEventStatus, eventStatus);
    eventStatus &= PMDEventStatusMask;  // Mask off unused bits
    return cmdStatus;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetActivityStatus(PMDuint16 &activityStatus) {
	PMDuint16 cmdStatus = 
        SendCommandGetWord(PMDOPGetActivityStatus, activityStatus);
    activityStatus &= PMDActivityStatusMask;    // Mask off unused bits
    return cmdStatus;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetSignalSense(PMDuint16 mask) {
	return SendCommandWord( PMDOPSetSignalSense, mask);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetSignalSense(PMDuint16 &mask) {
	return SendCommandGetWord(PMDOPGetSignalSense, mask);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetSignalStatus(PMDuint16 &signalStatus) {
	PMDuint16 cmdStatus = 
        SendCommandGetWord(PMDOPGetSignalStatus, signalStatus);
    signalStatus &= PMDSignalMask;  // Mask off unused bits
    return cmdStatus;
}


// Encoder
//-----------------------------------------------------------------------------
PMDuint16 PMD::AdjustActualPosition(PMDint32 position) {
	return SendCommandLong(PMDOPAdjustActualPosition, position);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetActualPosition(PMDint32 position) {
	return SendCommandLong(PMDOPSetActualPosition, position);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetActualPosition(PMDint32 &position) {
	return SendCommandGetLong(PMDOPGetActualPosition, *((PMDuint32*)&position));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetActualPositionUnits(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetActualPositionUnits, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetActualPositionUnits(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetActualPositionUnits, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetCaptureSource(PMDuint16 captureSource) {
	return SendCommandWord( PMDOPSetCaptureSource, captureSource);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetCaptureSource(PMDuint16 &captureSource) {
	return SendCommandGetWord(PMDOPGetCaptureSource, captureSource);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetEncoderSource(PMDuint16 encoderSource) {
	return SendCommandWord( PMDOPSetEncoderSource, encoderSource);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetEncoderSource(PMDuint16 &encoderSource) {
	return SendCommandGetWord(PMDOPGetEncoderSource, encoderSource);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetEncoderModulus(PMDuint16 modulus) {
	return SendCommandWord( PMDOPSetEncoderModulus, modulus);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetEncoderModulus(PMDuint16 &modulu) {
	return SendCommandGetWord(PMDOPGetEncoderModulus, modulu);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetEncoderToStepRatio(PMDuint16 encoderCounts, PMDuint16 steps) {
	return SendCommandWordWord(PMDOPSetEncoderToStepRatio, encoderCounts, steps);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetEncoderToStepRatio(PMDuint16 &encoderCounts, PMDuint16 &steps) {
	return SendCommandGetWordWord(PMDOPGetEncoderToStepRatio, encoderCounts, steps);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetActualVelocity(PMDint32 &actualValue) {
	return SendCommandGetLong(PMDOPGetActualVelocity, *((PMDuint32*)&actualValue));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetCaptureValue(PMDint32 &captureValue) {
	return SendCommandGetLong(PMDOPGetCaptureValue, *((PMDuint32*)&captureValue));
}


// Motor
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetOutputMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetOutputMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetOutputMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetOutputMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetMotorMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetMotorMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetMotorMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetMotorMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetMotorCommand(PMDint16 motorCommand) {
	return SendCommandWord( PMDOPSetMotorCommand, motorCommand);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetMotorCommand(PMDint16 &motorCommand) {
	return SendCommandGetWord(PMDOPGetMotorCommand, *((PMDuint16*)&motorCommand));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetCurrentMotorCommand(PMDint16 &motorCommand) {
	return SendCommandGetWord(PMDOPGetCurrentMotorCommand, 
                              *((PMDuint16*)&motorCommand));
	cout << "yup";
}


// Commutation
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetCommutationMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetCommutationMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetCommutationMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetCommutationMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetNumberPhases(PMDuint16 numberPhases) {
	return SendCommandWord( PMDOPSetNumberPhases, numberPhases);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetNumberPhases(PMDuint16 &numberPhases) {
	return SendCommandGetWord(PMDOPGetNumberPhases, numberPhases);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPhaseInitializeMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetPhaseInitializeMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhaseInitializeMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetPhaseInitializeMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPhasePrescale(PMDuint16 phasePrescale) {
	return SendCommandWord( PMDOPSetPhasePrescale, phasePrescale);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhasePrescale(PMDuint16 &phasePrescale) {
	return SendCommandGetWord(PMDOPGetPhasePrescale, phasePrescale);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPhaseCounts(PMDuint16 phaseCounts) {
	return SendCommandWord( PMDOPSetPhaseCounts, phaseCounts);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhaseCounts(PMDuint16 &phaseCounts) {
	return SendCommandGetWord(PMDOPGetPhaseCounts, phaseCounts);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPhaseInitializeTime(PMDuint16 phaseInitTime) {
	return SendCommandWord( PMDOPSetPhaseInitializeTime, phaseInitTime);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhaseInitializeTime(PMDuint16 &phaseInitTime) {
	return SendCommandGetWord(PMDOPGetPhaseInitializeTime, phaseInitTime);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPhaseOffset(PMDuint16 phaseOffset) {
	return SendCommandWord( PMDOPSetPhaseOffset, phaseOffset);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhaseOffset(PMDuint16 &phaseOffset) {
	return SendCommandGetWord(PMDOPGetPhaseOffset, phaseOffset);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPhaseAngle(PMDuint16 phaseAngle) {
	return SendCommandWord( PMDOPSetPhaseAngle, phaseAngle);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhaseAngle(PMDuint16 &phaseAngle) {
	return SendCommandGetWord(PMDOPGetPhaseAngle, phaseAngle);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetPhaseCorrectionMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetPhaseCorrectionMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhaseCorrectionMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetPhaseCorrectionMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::InitializePhase() {
	return SendCommand(PMDOPInitializePhase);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetPhaseCommand(PMDuint16 phase, PMDint16 &command) {
	return SendCommandWordGetWord(PMDOPGetPhaseCommand, phase, *((PMDuint16*)&command));
}


// External Memory
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetBufferStart(PMDuint16 bufferID, PMDuint32 bufferStart) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordLong(PMDOPSetBufferStart, bufferID, bufferStart);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetBufferStart(PMDuint16 bufferID, PMDuint32 &bufferStart) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordGetLong(PMDOPGetBufferStart, bufferID, bufferStart);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetBufferLength(PMDuint16 bufferID, PMDuint32 bufferLength) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordLong(PMDOPSetBufferLength, bufferID, bufferLength);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetBufferLength(PMDuint16 bufferID, PMDuint32 &bufferLength) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordGetLong(PMDOPGetBufferLength, bufferID, bufferLength);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetBufferFunction(PMDuint16 function, PMDint16 bufferID) {
	return SendCommandWordWord(PMDOPSetBufferFunction, function, bufferID);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetBufferFunction(PMDuint16 function, PMDint16 &bufferID) {
	return SendCommandWordGetWord(PMDOPSetBufferFunction, function, 
        *((PMDuint16*)&bufferID));
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::WriteBuffer(PMDuint16 bufferID, PMDint32 data) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordLong(PMDOPWriteBuffer, bufferID, data);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::ReadBuffer(PMDuint16 bufferID, PMDint32 &data) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordGetLong(PMDOPReadBuffer, bufferID, *((PMDuint32*)&data));

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetBufferWriteIndex(PMDuint16 bufferID, PMDuint32 writeIndex) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordLong(PMDOPSetBufferWriteIndex, bufferID, writeIndex);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetBufferWriteIndex(PMDuint16 bufferID, PMDuint32 &writeIndex) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordGetLong(PMDOPGetBufferWriteIndex, bufferID, writeIndex);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetBufferReadIndex(PMDuint16 bufferID, PMDuint32 readIndex) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordLong(PMDOPSetBufferReadIndex, bufferID, readIndex);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetBufferReadIndex(PMDuint16 bufferID, PMDuint32 &readIndex) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordGetLong(PMDOPGetBufferReadIndex, bufferID, readIndex);

	SetAxis(axis);

	return result;
}


// Trace Operations
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetTraceMode(PMDuint16 mode) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWord( PMDOPSetTraceMode, mode);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTraceMode(PMDuint16 &mode) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandGetWord(PMDOPGetTraceMode, mode);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetTracePeriod(PMDuint16 tracePeriod) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWord( PMDOPSetTracePeriod, tracePeriod);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTracePeriod(PMDuint16 &tracePeriod) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandGetWord(PMDOPGetTracePeriod, tracePeriod);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetTraceVariable(PMDuint16 traceID, PMDAxis traceAxis, PMDuint8 variable) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;
	PMDuint16 value;

	// set the axis number to zero
	SetAxis(0);

	value = (traceAxis & nibbleMask) | ((variable & byteMask) << 8);
	result = SendCommandWordWord(PMDOPSetTraceVariable, traceID, value);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTraceVariable(PMDuint16 traceID, PMDAxis &traceAxis, PMDuint8 &variable) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;
	PMDuint16 value;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandWordGetWord(PMDOPGetTraceVariable, traceID, value);
	traceAxis = (PMDAxis)(value & nibbleMask);
	variable = (PMDuint8)((value >> 8) & byteMask);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetTraceStart(PMDAxis traceAxis, PMDuint8 condition, PMDuint8 bit, PMDuint8 state) {
	PMDuint16 value = (traceAxis & nibbleMask) | ((condition & nibbleMask) << 4);
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);
	
	switch(condition)
	{
	case PMDTraceConditionEventStatus:
	case PMDTraceConditionActivityStatus:
	case PMDTraceConditionSignalStatus:
		value |= ((bit & nibbleMask) << 8) | ((state & nibbleMask) << 12);
		break;
	default:
		break;
	}
	result = SendCommandWord( PMDOPSetTraceStart, value);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTraceStart(PMDAxis &traceAxis, PMDuint8 &condition, PMDuint8 &bit, PMDuint8 &state) {
	PMDuint16 result;
	PMDuint16 value;
	PMDAxis axis = GetAxisNumber();

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandGetWord(PMDOPGetTraceStart, value);
	traceAxis = (PMDAxis)((value & nibbleMask));
	condition = (PMDuint8)((value >> 4) & nibbleMask);
	bit = (PMDuint8)((value >> 8) & nibbleMask);
	state = (PMDuint8)((value >> 12) & nibbleMask);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetTraceStop(PMDAxis traceAxis, PMDuint8 condition, PMDuint8 bit, PMDuint8 state) {
	PMDuint16 value = (traceAxis & nibbleMask) | ((condition & nibbleMask) << 4);
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);
	
	switch(condition)
	{
	case PMDTraceConditionEventStatus:
	case PMDTraceConditionActivityStatus:
	case PMDTraceConditionSignalStatus:
		value |= ((bit & nibbleMask) << 8) | ((state & nibbleMask) << 12);
		break;
	default:
		break;
	}
	result = SendCommandWord( PMDOPSetTraceStop, value);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTraceStop(PMDAxis &traceAxis, PMDuint8 &condition, PMDuint8 &bit, PMDuint8 &state) {
	PMDuint16 result;
	PMDuint16 value;
	PMDAxis axis = GetAxisNumber();

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandGetWord(PMDOPGetTraceStop, value);
	traceAxis = (PMDAxis)((value & nibbleMask));
	condition = (PMDuint8)((value >> 4) & nibbleMask);
	bit = (PMDuint8)((value >> 8) & nibbleMask);
	state = (PMDuint8)((value >> 12) & nibbleMask);

	SetAxis(axis);

	return result;
}


//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTraceStatus(PMDuint16 &status) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandGetWord(PMDOPGetTraceStatus, status);
    status &= PMDTraceStatusMask;  // Mask off unused bits
	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTraceCount(PMDuint32 &count) {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// set the axis number to zero
	SetAxis(0);

	result = SendCommandGetLong(PMDOPGetTraceCount, count);

	SetAxis(axis);

	return result;
}


// Miscellaneous
//-----------------------------------------------------------------------------
PMDuint16 PMD::SetAxisMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetAxisMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetAxisMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetAxisMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetAxisOutSource(PMDAxis sourceAxis, PMDuint8 bit, PMDuint8 sourceRegister) {
	PMDuint16 value = 0;
	
	value = (sourceAxis & nibbleMask) | ((bit & nibbleMask) << 4) | ((sourceRegister & nibbleMask) << 8);
		
	return SendCommandWord( PMDOPSetAxisOutSource, value);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetAxisOutSource(PMDAxis &sourceAxis, PMDuint8 &bit, PMDuint8 &sourceRegister) {
	PMDuint16 result;
	PMDuint16 value;

	result = SendCommandGetWord(PMDOPGetAxisOutSource, value);

	sourceAxis = (PMDAxis)(value & nibbleMask);

	value = value >> 4;
	bit = (PMDuint8)(value & nibbleMask);

	value = value >> 4;
	sourceRegister = (PMDuint8)(value & nibbleMask);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::WriteIO(PMDuint16 address, PMDuint16 data) {
	return SendCommandWordWord(PMDOPWriteIO, address, data);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::ReadIO(PMDuint16 address, PMDuint16 &data) {
	return SendCommandWordGetWord(PMDOPReadIO, address, data);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::ReadAnalog(PMDuint16 analogID, PMDuint16 &data) {
	return SendCommandWordGetWord(PMDOPReadAnalog, analogID, data);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::Reset() {
	PMDAxis axis = GetAxisNumber();
	PMDuint16 result;

	// for the reset command, the axis number MUST be zero
	SetAxis(0);

	result = SendCommand(PMDOPReset);

	SetAxis(axis);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::NoOperation() {
	return SendCommand(PMDOPNoOperation);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetVersion(PMDuint16 &generation, PMDuint16 &motorType, 
						PMDuint16 &numberAxes, PMDuint16 &special,
						PMDuint16 &custom, PMDuint16 &major, PMDuint16 &minor) {
	PMDuint16 chip = 0, software = 0;
	PMDuint16 result;

	result = SendCommandGetWordWord(PMDOPGetVersion, chip, software);

	generation = (chip & 0xF000) >> 12;
	motorType = (chip & 0x0F00) >> 8;
	numberAxes = (chip & 0x00F0) >> 4;
	special = chip & 0x000F;

	custom = (software & 0xFF00) >> 8;
	major = (software & 0x00F0) >> 4;
	minor = software & 0x000F;

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetHostIOError(PMDuint16 &hostIOError) {
	return SendCommandGetWord(PMDOPGetHostIOError, hostIOError);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetSerialPortMode(tagPMDSerialBaudRate baud, 
                                tagPMDSerialParity parity, 
                                tagPMDSerialStopBits stopBits, 
                                tagPMDSerialProtocol protocol, 
                                PMDuint8 multiDropID) {
    // Serial mode command data word
	PMDuint16 serialData = (PMDuint16)( baud            | 
                                        (parity << 4)   | 
                                        (stopBits << 6) | 
		                                (protocol << 7) | 
		// bits 9 and 10 are undefined
		                                (multiDropID << 11));
    try {
	    SendCommandWord(PMDOPSetSerialPortMode, serialData);
    } catch (...) {
        // Guaranteed to get a comm port read exception.
        // Let the higher level logic deal with changing baud rates to 
        // match what the chipset was just set to.
    }
    return true;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetSerialPortMode(tagPMDSerialBaudRate &baud, 
                                tagPMDSerialParity &parity, 
                                tagPMDSerialStopBits &stopBits, 
                                tagPMDSerialProtocol &protocol, 
                                PMDuint8 &multiDropID) {
    typedef enum {
        BaudMask = 0x000F,
        ParityMask = 0x0030,
        StopBitsMask = 0x0040,
        ProtocolMask = 0x0180,
        MultiDropIDMask = 0xF800
    } SerialPortModeMasks;
    typedef enum {
        BaudShift = 0,
        ParityShift = 4,
        StopBitsShift = 6,
        ProtocolShift = 7,
        MultiDropIDShift = 11
    } SerialPortModeShifts;

    PMDuint16 data;
	PMDuint16 result;

	result = SendCommandGetWord(PMDOPGetSerialPortMode, data);

	baud = (tagPMDSerialBaudRate)(data & BaudMask);
	parity = (tagPMDSerialParity)((data & ParityMask) >> ParityShift);
	stopBits = (tagPMDSerialStopBits)((data & StopBitsMask) >> StopBitsShift);
	protocol = (tagPMDSerialProtocol)((data & ProtocolMask) >> ProtocolShift);
	multiDropID = (PMDuint8)((data & MultiDropIDMask) >> MultiDropIDShift);

	return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetSerialPortMode(   int baud, PortableSerial::Parity parity, 
                                    PortableSerial::StopBits stopBits, 
                                    tagPMDSerialProtocol protocol, 
                                    PMDuint8 multiDropID) {

    return SetSerialPortMode(   PMDSerial::HostToPMDBaud(baud),
                                PMDSerial::HostToPMDParity(parity),
                                PMDSerial::HostToPMDStopBits(stopBits), 
                                protocol, multiDropID);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetSerialPortMode( int &baud, PortableSerial::Parity &parity,
                                    PortableSerial::StopBits &stopBits, 
                                    tagPMDSerialProtocol &protocol, 
                                    PMDuint8 &multiDropID) {
    tagPMDSerialBaudRate pmdBaud;
    tagPMDSerialParity pmdParity; 
    tagPMDSerialStopBits pmdStopBits;
	PMDuint16 result;

    result = GetSerialPortMode( pmdBaud,pmdParity,pmdStopBits,
                                protocol,multiDropID);

    baud = PMDSerial::PMDToHostBaud(pmdBaud);
    parity = PMDSerial::PMDToHostParity(pmdParity);
    stopBits = PMDSerial::PMDToHostStopBits(pmdStopBits);

    return result;
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetDiagnosticPortMode(PMDuint16 mode) {
	return SendCommandWord( PMDOPSetDiagnosticPortMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetDiagnosticPortMode(PMDuint16 &mode) {
	return SendCommandGetWord(PMDOPGetDiagnosticPortMode, mode);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetTime(PMDuint32 &numberChipCycles) {
	return SendCommandGetLong(PMDOPGetTime, numberChipCycles);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetChecksum(PMDuint32 &checksum) {
	return SendCommandGetLong(PMDOPGetChecksum, checksum);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::SetStepRange(PMDuint16 range) {
	return SendCommandWord( PMDOPSetStepRange, range);
}

//-----------------------------------------------------------------------------
PMDuint16 PMD::GetStepRange(PMDuint16 &range) {
	return SendCommandGetWord(PMDOPGetStepRange, range);
}


//-----------------------------------------------------------------------------
//static
void PMDGetCMotionVersion(PMDuint8 &MajorVersion, PMDuint8 &MinorVersion) {
	MajorVersion = CMOTION_MAJOR_VERSION;
	MinorVersion = CMOTION_MINOR_VERSION;
}

