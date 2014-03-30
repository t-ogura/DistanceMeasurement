#ifndef _MEASUREMENT_H_
#define _MEASUREMENT_H_

#include "camera.h"
#include "control_biclops.h"
#include "vcc.h"
#include <thread>
#include <mutex>

#define LEFT 0
#define RIGHT 1

class Measurement{
public:
	Measurement(double imagingDevicePixelSize, double lensFocalLength, double stereoBaselineLength, int VCC_Threshold = 12);
	~Measurement();

	void tracking(const char* biclopsConfigFilePath);
	void threadTracking(const char* biclopsConfigFilePath);
	void measure();
	void threadTrackingJoin();

	double pixelSize;
	double focalLength;
	double baselineLength;

	Camera *camera_L;
	Camera *camera_R;
	ControlBiclops *controlBiclops;

	VCC *vcc_L;
	VCC *vcc_R;

	//ï‚ê≥íl
	double correctParallel;
	double linear_a;
	double linear_b;

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
	Distances non_ofset;

	struct PanTilt{
		double pan;
		double tilt;
	};
	PanTilt platformState;
	PanTilt trackingAngle;
	PanTilt angle_L;
	PanTilt angle_R;

	PanTilt angleCalculation(VCC *vcc);

private:


	void kalmanInitialize();
	cv::KalmanFilter *KF;
	cv::Mat_<float> *KF_State;
	cv::Mat *KF_ProcessNoise;
	cv::Mat_<float> *KF_Measurement;

	std::thread trackingThread;
	std::mutex mtx;
};

#endif