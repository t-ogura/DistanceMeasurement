#ifndef _MEASUREMENT_H_
#define _MEASUREMENT_H_

#include "camera.h"
#include "vcc.h"
#include "turnPTU.h"
#include <thread>
#include <mutex>

#define LEFT 0
#define RIGHT 1

class Measurement{
public:
	Measurement(double imagingDevicePixelSize, double lensFocalLength, double stereoBaselineLength, int VCC_Threshold = 12);
	~Measurement();

	void tracking(char* comPortNumber, int baudrate);
	void threadTracking(char* comPortNumber, int baudrate);
	void measure();
	void threadTrackingJoin();

	double pixelSize;
	double focalLength;
	double baselineLength;

	Camera *camera_L;
	Camera *camera_R;

	VCC *vcc_L;
	VCC *vcc_R;

	//ï‚ê≥íl
	double linear_a2;
	double linear_a1;
	double linear_a0;

	PTU *ptu;

	bool trackingTiming;
	bool trackingHomeFlag;
	bool trackingMoveFlag;

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

	PanTilt angleCalculation(VCC *vcc);

	std::vector<double> prev_distances;

private:


	void kalmanInitialize();
	double quadratic(double a2, double a1, double a0);

	cv::KalmanFilter *KF;
	cv::Mat_<float> *KF_State;
	cv::Mat *KF_ProcessNoise;
	cv::Mat_<float> *KF_Measurement;

	std::thread trackingThread;

	std::thread vccThread_L;
	std::thread vccThread_R;
	std::mutex mtx;
};

#endif