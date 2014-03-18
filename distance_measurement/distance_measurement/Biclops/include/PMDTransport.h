#ifndef PMDTransport_h
#define	PMDTransport_h

#include "PMDTypes.h"
#include "PMDIOTransport.h"

class PMDTransport {
public:

    // Constructors
    PMDTransport(PMDIOTransport* pmdIOTransport, PMDAxis axis);

    void SetIOTransport(PMDIOTransport* pmdIOTransport) {
        this->pmdIOTransport = pmdIOTransport;
    };

    // General purpose command-word formatter.
    static PMDuint16 BuildCommandWord(PMDuint16 opCode, PMDuint16 axis) {	
        return ((PMDuint16)((PMDuint32)opCode | ((PMDuint32)axis << 8)));
    };

    PMDuint16 SendCommand               (PMDuint16 opCode);
    PMDuint16 SendCommandWord           (PMDuint16 opCode, PMDuint16 data1);
    PMDuint16 SendCommandWordWord       (PMDuint16 opCode, PMDuint16 data1, PMDuint16 data2);
    PMDuint16 SendCommandWordWordWord   (PMDuint16 opCode, PMDuint16 data1, PMDuint16 data2, PMDuint16 data3);
    PMDuint16 SendCommandLong           (PMDuint16 opCode, PMDuint32 data1);
    PMDuint16 SendCommandLongWord       (PMDuint16 opCode, PMDuint32 data1, PMDuint16 data2);
    PMDuint16 SendCommandWordLong       (PMDuint16 opCode, PMDuint16 data1, PMDuint32 data2);
    PMDuint16 SendCommandGetWord        (PMDuint16 opCode, PMDuint16 &data1);
    PMDuint16 SendCommandGetWordWord    (PMDuint16 opCode, PMDuint16 &data1, PMDuint16 &data2);
    PMDuint16 SendCommandGetWordWordWord(PMDuint16 opCode, PMDuint16 &data1, PMDuint16 &data2, PMDuint16 &data3);
    PMDuint16 SendCommandGetLong        (PMDuint16 opCode, PMDuint32 &data1);
    PMDuint16 SendCommandGetWordLong    (PMDuint16 opCode, PMDuint16 &data1, PMDuint32 &data2);
    PMDuint16 SendCommandWordGetWord    (PMDuint16 opCode, PMDuint16 data1, PMDuint16 &data2);
    PMDuint16 SendCommandWordGetLong    (PMDuint16 opCode, PMDuint16 data1, PMDuint32 &data2);
    PMDuint16 SendCommandLongGetWord    (PMDuint16 opCode, PMDuint32 data1, PMDuint16 &data2);
    PMDuint16 SendCommandWordWordGetWord(PMDuint16 opCode,
									     PMDuint16 data1, PMDuint16 data2, PMDuint16 &data3);

    // Methods giving access to private variables
    inline PMDAxis GetAxisNumber() {return axis;};
    void SetAxis(PMDAxis axis) {this->axis = axis;};

    inline int GetDebugLevel() { return debugLevel;}
    void SetDebugLevel(int debugLevel);

protected:
	PMDIOTransport* pmdIOTransport;

private:
	PMDAxis	axis;
    int debugLevel;

  };

#endif
