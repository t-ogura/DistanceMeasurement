#include "ptu\include\opcodes.h"
#include "ptu\include\w32seria.h"
#include "ptu\include\ptu.h"

#define _USE_MATH_DEFINES
#include <cmath>

#define PAN_RES 11109
#define TILT_RES 2777
#define PAN_DEG2STEP(X) (-X/(PAN_RES/ 3600. / 60.))
#define TILT_DEG2STEP(X) (-X/(TILT_RES/ 3600. / 60.))
#define PAN_STEP2DEG(X) (-X*(PAN_RES/ 3600. / 60.))
#define TILT_STEP2DEG(X) (-X*(TILT_RES/ 3600. / 60.))
#define DEG2RAD(X) (X/180.*M_PI)
#define RAD2DEG(X) (X*180/M_PI)

#define SPEED_PAN_MAX 2801
#define SPEED_TILT_MAX 2833
#define SPEED_FACTOR 5

class PTU{
public:
	PTU(char* comPort,int baudrate = 9600,unsigned short deviceID = 0);
	~PTU();
	int turnHome();
	int turn(double panAngleRadian, double tiltAngleRadian);
	int setSpeed();
	int getPosition();

	double panAngle;
	double tiltAngle;
private:
	int initialize();
	portstream_fd COMstream;
	unsigned short id;
};