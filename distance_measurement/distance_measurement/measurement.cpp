#include "measurement.h"

Measurement::Measurement(double pSize, double fLength, double bLength,int VCC_Th){
	this->pixelSize = pSize;
	this->focalLength = fLength;
	this->baselineLength = bLength;

	this->camera_L = new Camera(LEFT);
	this->camera_R = new Camera(RIGHT);

	this->vcc_L = new VCC(VCC_Th);
	this->vcc_R = new VCC(VCC_Th);
	this->vcc_L->kalmanInitialize(VCC_INPUT_IMAGE_SIZE_X / 2, VCC_INPUT_IMAGE_SIZE_Y / 2); //TEST
	this->vcc_R->kalmanInitialize(VCC_INPUT_IMAGE_SIZE_X / 2, VCC_INPUT_IMAGE_SIZE_Y / 2); //TEST

	this->kalmanInitialize();

	this->trakingLoopFlag = false;
}

Measurement::~Measurement(){}

void Measurement::kalmanInitialize(){
	this->KF = new cv::KalmanFilter(2, 1, 0);
	this->KF_State = new cv::Mat_<float>(2, 1);
	this->KF_ProcessNoise = new cv::Mat(2, 1, CV_32F);
	this->KF_Measurement = new cv::Mat_<float>(1, 1);
	this->KF_Measurement->setTo(cv::Scalar(0));

	this->KF->statePre.at<float>(0) = 0;
	this->KF->statePre.at<float>(1) = 0;
	this->KF->transitionMatrix = *(cv::Mat_<float>(2, 2) << 1, 0, 0, 1);

	cv::setIdentity(this->KF->measurementMatrix);
	cv::setIdentity(this->KF->processNoiseCov, cv::Scalar::all(1e-4));
	cv::setIdentity(this->KF->measurementNoiseCov, cv::Scalar::all(1e-1));
	cv::setIdentity(this->KF->errorCovPost, cv::Scalar::all(.1));

	this->KF->statePre.at<float>(0) = 0;
	this->KF->statePre.at<float>(1) = 0;
}

void Measurement::tracking(const char* path){
	ControlBiclops cb(path);
	while (this->trakingLoopFlag){
		cb.getPosition();
		TrackingAxes ta;
		this->mtx.lock();
		ta = this->trakingAxes;
		this->mtx.unlock();
		cb.deviceTurn(ta.pan, ta.tilt);
	}
}

void Measurement::threadTracking(const char* path){
	this->trakingLoopFlag = true;
	std::thread trakingThread(std::bind(&Measurement::tracking, this, path));
}