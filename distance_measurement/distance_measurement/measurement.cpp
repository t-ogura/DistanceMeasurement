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
	this->trackingThreshold = 170;
	this->trackingHomeFlag = false;
	this->trackingMoveFlag = true;
	this->trackingTiming = false;

	this->linear_a = 0.0;
	this->linear_b = 0.0;
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

void Measurement::tracking(char* com,int baudrate){
	this->trackingState = "‰Šú‰»’†";
	PTU ptu(com, baudrate);
	ptu.turnHome();
	Sleep(2000);
	ptu.setSpeed();
	this->trackingState = "‰Ò“­’†";
	while (this->trackingLoopFlag){
		if (this->trackingHomeFlag){
			this->trackingState = "ƒz[ƒ€‚Ö";
			ptu.turnHome();
			Sleep(2000);
			ptu.setSpeed();
			this->trackingHomeFlag = false;
			this->trackingState = "‰Ò“­’†";
		}
		ptu.getPosition();
		PanTilt pt,my;
		my.pan = ptu.panAngle;
		my.tilt = ptu.tiltAngle;
		this->mtx.lock();
		pt = this->trackingAngle;
		this->platformState = my;
		this->mtx.unlock();
		while (!this->trackingTiming)cv::waitKey(1);
		this->trackingTiming = false;
		if (this->trackingMoveFlag){
			this->trackingState = "‰Ò“­’†";
			this->mtx.lock();
			int mL = this->vcc_L->matchingParameters[8];
			int mR = this->vcc_R->matchingParameters[8];
			this->mtx.unlock();
			if (mL < this->trackingThreshold && mR < this->trackingThreshold){
				ptu.turn(pt.pan, pt.tilt);
			}			
			else{ ptu.turn(0, 0); }
		}
		else{
			this->trackingState = "’âŽ~’†";
		}
	}
}

void Measurement::threadTracking(char* com, int baudrate){
	this->trackingLoopFlag = true;
	this->trackingThread = std::thread(std::bind(&Measurement::tracking, this, com,baudrate));
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
	this->mtx.lock();
	vccThread_L = std::thread(std::bind(&VCC::templateMatching, this->vcc_L));
	vccThread_R = std::thread(std::bind(&VCC::templateMatching, this->vcc_R));
	vccThread_L.join();
	vccThread_R.join();
	this->mtx.unlock();
	this->angle_L = angleCalculation(vcc_L);
	this->angle_R = angleCalculation(vcc_R);
	this->non_offset.original = this->baselineLength / (tan(this->angle_L.pan) - tan(this->angle_R.pan));
	this->non_offset.mid = sqrt(pow(this->non_offset.original, 2)*(pow(tan(angle_L.pan), 2) + pow(tan(angle_R.pan), 2) + 2) / 2 - pow((double)this->baselineLength, 2) / 4);
	this->non_offset.theta = acos(this->non_offset.original / this->non_offset.mid);
	double tmp = this->baselineLength / (tan(this->angle_L.pan + this->correctParallel / 2.0) - tan(this->angle_R.pan - this->correctParallel / 2.0));
	this->distance.original = tmp / (1.0 + this->linear_a) - this->linear_b;
	this->distance.mid = sqrt(pow(this->distance.original, 2)*(pow(tan(angle_L.pan), 2) + pow(tan(angle_R.pan), 2) + 2) / 2 - pow((double)this->baselineLength, 2) / 4);
	this->distance.theta = acos(this->distance.original / this->distance.mid);
	if (angle_L.pan + angle_R.pan < 0) this->distance.theta *= -1;
	cv::Mat prediction = this->KF->predict();
	double predictDist = prediction.at<float>(0);
	(*this->KF_Measurement)(0) = this->distance.mid;
	cv::Mat estimated = this->KF->correct((*this->KF_Measurement));
	this->distance.kf = estimated.at<float>(0);
	PanTilt pt;
	pt.pan = this->distance.theta;
	pt.tilt = (angle_L.tilt + angle_R.tilt) / 2.0;
	this->mtx.lock();
	this->trackingAngle = pt;
	this->mtx.unlock();
	this->trackingTiming = true;
}