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

	Camera *camera_L;
	Camera *camera_R;
	ControlBiclops *controlBiclops;

	VCC *vcc_L;
	VCC *vcc_R;

	bool trakingLoopFlag;

private:
	double pixelSize;
	double focalLength;
	double baselineLength;

	struct TrackingAxes{
		double pan;
		double tilt;
	}trakingAxes;

	void kalmanInitialize();
	cv::KalmanFilter *KF;
	cv::Mat_<float> *KF_State;
	cv::Mat *KF_ProcessNoise;
	cv::Mat_<float> *KF_Measurement;

	std::mutex mtx;
};

#endif