#ifndef PMDIOTransport_h
#define PMDIOTransport_h
#include "PMDTypes.h"

class PMDIOTransport {
public:
    enum TransportType {PARALLEL,SERIAL};

    TransportType GetTransportType() { return transportType;};
    void SetTransportType(TransportType transportType) {
        this->transportType = transportType;
    };

    virtual bool Open() = 0;
    virtual void Close() = 0;
//    virtual void DisableInterrupt() {};
//    virtual void EnableInterrupt() {};

	virtual PMDuint16 SendCommand(PMDuint8 xCt, PMDuint16* xDat, PMDuint8 rCt, PMDuint16* rDat) = 0;
    virtual PMDuint16 ReceiveResponse(PMDuint16 length, PMDuint16 buffer[]) {return 1;};
    virtual PMDuint16 VerifyChecksum(PMDuint16 length, PMDuint16 buffer[]) {return 1;};

	virtual PMDuint16 GetStatus() = 0;
	virtual bool IsReady() = 0;
//	virtual bool HasInterrupt() = 0;
	virtual bool HasError() = 0;
    void SetDebugLevel(int debugLevel) {
        this->debugLevel = debugLevel;
    };
    int GetDebugLevel() { return debugLevel;};
private:
    TransportType transportType;
    int debugLevel;
};
#endif
