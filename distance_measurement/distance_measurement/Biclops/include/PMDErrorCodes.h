#ifndef PMD_ErrorCodes
#define	PMD_ErrorCodes

//  PMDErrorCodes.h -- error codes
//
//  Performance Motion Devices, Inc.
//

#if defined(__cplusplus)
extern "C" {
#endif

typedef enum PMDErrorCodesEnum {

	// MC2xxx Chipset error codes
	PMD_ERR_OK=0,
	PMD_ERR_ChipsetReset=0x01,
	PMD_ERR_InvalidInstruction=0x02,
	PMD_ERR_InvalidAxis=0x03,
	PMD_ERR_InvalidParameter=0x04,
	PMD_ERR_TraceRunning=0x05,
	PMD_ERR_BadFlashUpdateFile=0x06,
	PMD_ERR_BlockOutOfBounds=0x07,
	PMD_ERR_TraceBufferZero=0x08,
	PMD_ERR_BadSerialChecksum=0x09,
	PMD_ERR_NotPrimaryPort=0x0A,
	PMD_ERR_InvalidNegativeValue=0x0B,
	PMD_ERR_InvalidParameterChange=0x0C,
	PMD_ERR_LimitEventPending=0x0D,
	PMD_ERR_InvalidMoveIntoLimit=0x0E,

	// DK2000 initialization errors
	PMD_ERR_NotConnected=0x7FD1,
	PMD_ERR_ChipsetNotResponding=0x7FD2,
	PMD_ERR_CommPortRead=0x7FD3,
	PMD_ERR_CommPortWrite=0x7FD4,
	PMD_ERR_InvalidCommPortAddress=0x7FD5,
	PMD_ERR_InvalidCommPortBaudRate=0x7FD6,
	PMD_ERR_InvalidCommPortParity=0x7FD7,
	PMD_ERR_InvalidCommPortStopBits=0x7FD8,
	PMD_ERR_InvalidCommPortProtocol=0x7FD9,
	PMD_ERR_InvalidCommPortMDropID=0x7FDA,
	PMD_ERR_InvalidSerialPort=0x7FDB,
	PMD_ERR_InvalidDK2000IOBase=0x7FDC,
	PMD_ERR_InvalidDK2000IRQ=0x7FDD,
	PMD_ERR_InvalidDK2000IOMode=0x7FDE,
	PMD_ERR_DK2000NotInitialized=0x7FDF,

	// run-time errors
	PMD_ERR_CommunicationsError=0x7FFC,
	PMD_ERR_CommTimeoutError=0x7FFD,
	PMD_ERR_ChecksumError=0x7FFE,
	PMD_ERR_CommandError=0x7FFF
} PMD_ResultCodes;

#if defined(__cplusplus)
}
#endif

#endif
