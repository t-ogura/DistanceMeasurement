#ifndef _MEASUREMENT_H_
#define _MEASUREMENT_H_

#include "camera.h"
#include "vcc.h"
#include "turnPTU.h"
#include <thread>
#include <mutex>

#define INIT_FILE_PATH "initialize.cfg"

#define CENTER 2
#define LEFT 1
#define RIGHT 0

class Measurement{
public:
	Measurement(double imagingDevicePixelSize, double lensFocalLength, double stereoBaselineLength, int VCC_Threshold = 12, bool centerCamera = false, double senterCameraFocalLength = 8.);
	~Measurement();

	struct initParams{
		int LEFT_CAMERA_EXPOSURE = 41;
		int RIGHT_CAMERA_EXPOSURE = 41;
		int CENTER_CAMERA_EXPOSURE = 41;
		double MEASUREMENT_KALMANFILTER_PROCESS_NOISE_COV = 1e-4;
		double MEASUREMENT_KALMANFILTER_MEASUREMENT_NOISE_COV = 1e-1;
		int LEFT_CAMERA_ID = 0;
		int RIGHT_CAMERA_ID = 1;
		int CENTER_CAMERA_ID = 2;
		std::string COM_PORT_NUMBER = "\\\\.\\COM5";
		std::string LEFT_OR_RIGHT = "LEFT";
		std::string GNUPLOT = "SHOW";
	};

	std::string platform_comnumber;

	int readInitFile(std::string filename,initParams *ini);

	void tracking(char* comPortNumber, int baudrate);
	void threadTracking(char* comPortNumber, int baudrate);
	void measure();
	void threadTrackingJoin();

	double pixelSize;
	double focalLength;
	double baselineLength;

	int VCC_Th;
	bool centerCameraFlag;
	double centerCameraFocalLength;

	std::string GNUPLOT;
	std::string LEFT_OR_RIGHT;

	Camera *camera_L;
	Camera *camera_R;
	Camera *camera_C;

	VCC *vcc_L;
	VCC *vcc_R;
	VCC *vcc_C;

	//ï‚ê≥íl
	double linear_a2;
	double linear_a1;
	double linear_a0;

	PTU *ptu;

	bool trackingTiming;
	bool trackingHomeFlag;
	bool trackingMoveFlag;
	bool outControlFlag;
	bool outControlAbs;


	int trackingThreshold;
	std::string trackingState;
	bool trackingLoopFlag;
	struct Distances{
		double original;
		double mid;
		double theta;
		double kf;
	};
	Distances distance;
	Distances non_offset;

	struct PanTilt{
		double pan;
		double tilt;
	};
	PanTilt platformState;
	PanTilt trackingAngle;
	PanTilt angle_L;
	PanTilt angle_R;
	PanTilt angle_C;

	PanTilt outControlPT;

	PanTilt angleCalculation(VCC *vcc, double cameraFocalLength);

	std::vector<double> prev_distances;
	std::mutex mtx;

	cv::KalmanFilter *KF;
	cv::Mat_<float> *KF_State;
	cv::Mat *KF_ProcessNoise;
	cv::Mat_<float> *KF_Measurement;

private:


	void kalmanInitialize(double processNoisCov, double measurementNoiseCov);
	double quadratic(double a2, double a1, double a0);


	std::thread trackingThread;

	std::thread vccThread_L;
	std::thread vccThread_R;
};

#endif