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
	this->vcc_L->matchingParameters[6] = VCC_INPUT_IMAGE_SIZE_X / 2;
	this->vcc_L->matchingParameters[7] = VCC_INPUT_IMAGE_SIZE_Y / 2;
	this->vcc_R->matchingParameters[6] = VCC_INPUT_IMAGE_SIZE_X / 2;
	this->vcc_R->matchingParameters[7] = VCC_INPUT_IMAGE_SIZE_Y / 2;

	this->kalmanInitialize();

	this->correctParallel = 0.0;
	this->trackingLoopFlag = false;
	this->trackingState = "–¢‰Ò“­";
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
	this->trackingState = "‰Šú‰»’†";
	ControlBiclops cb(path);
	this->trackingState = "‰Ò“­’†";
	while (this->trackingLoopFlag){
		cb.getPosition();
		PanTilt pt,my;
		my.pan = cb.pan_angle_rad;
		my.tilt = cb.tilt_angle_rad;
		this->mtx.lock();
		this->platformState = my;
		pt = this->trackingAngle;
		this->mtx.unlock();
		cb.deviceTurn(pt.pan, pt.tilt);
	}
}

void Measurement::threadTracking(const char* path){
	this->trackingLoopFlag = true;
	this->trackingThread = std::thread(std::bind(&Measurement::tracking, this, path));
}

void Measurement::threadTrackingJoin(){
	if (this->trackingThread.joinable())
		this->trackingThread.join();
}

Measurement::PanTilt Measurement::angleCalculation(VCC *vcc){
	double x = vcc->matchingParameters[2] + vcc->subpixelResult_x - VCC_INPUT_IMAGE_SIZE_X / 2;
	double y = vcc->matchingParameters[3] + vcc->subpixelResult_y - VCC_INPUT_IMAGE_SIZE_Y / 2;
	PanTilt pt;
	pt.pan  = atan2(x*this->pixelSize, this->focalLength);
	pt.tilt = atan2(y*this->pixelSize, this->focalLength);
	return pt;
}

void Measurement::measure(){
	this->camera_L->getImage();
	this->camera_R->getImage();
	this->vcc_L->setInputImage(this->camera_L->grayImage);
	this->vcc_R->setInputImage(this->camera_R->grayImage);
	std::thread vccThread_L(std::bind(&VCC::templateMatching, this->vcc_L));
	std::thread vccThread_R(std::bind(&VCC::templateMatching, this->vcc_R));
	vccThread_L.join();
	vccThread_R.join();
	this->angle_L = angleCalculation(vcc_L);
	this->angle_R = angleCalculation(vcc_R);
	this->distance.original = this->baselineLength / (tan(this->angle_L.pan+this->correctParallel/2.0) - tan(this->angle_R.pan-this->correctParallel/2.0));
	this->distance.mid = sqrt(pow(this->distance.original, 2)*(pow(tan(angle_L.pan), 2) + pow(tan(angle_R.pan), 2) + 2) / 2 - pow((double)this->baselineLength, 2) / 4);
	this->distance.theta = acos(this->distance.original / this->distance.mid);
	if (angle_L.pan + angle_R.pan < 0) this->distance.theta *= -1;
	cv::Mat prediction = this->KF->predict();
	double predictDist = prediction.at<float>(0);
	(*this->KF_Measurement)(0) = this->distance.mid;
	cv::Mat estimated = this->KF->correct((*this->KF_Measurement));
	this->distance.kf = estimated.at<float>(0);
	if (vcc_L->matchingParameters[8] < 850 && vcc_R->matchingParameters[8] < 850){
		PanTilt pt;
		pt.pan = this->distance.theta;
		pt.tilt = (angle_L.tilt + angle_R.tilt) / 2;
		this->mtx.lock();
		this->trackingAngle = pt;
		this->mtx.unlock();
	}
	else{
		PanTilt pt;
		pt.pan = 0;
		pt.tilt = 0;
		this->mtx.lock();
		this->trackingAngle = pt;
		this->mtx.unlock();
	}
}