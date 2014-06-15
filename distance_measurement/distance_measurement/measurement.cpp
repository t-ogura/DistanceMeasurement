#include "measurement.h"

Measurement::Measurement(double pSize, double fLength, double bLength,int VCC_Threshold, bool centerCamera, double centerFocal){
	this->pixelSize = pSize;
	this->focalLength = fLength;
	this->baselineLength = bLength;

	this->centerCameraFlag = centerCamera;
	this->centerCameraFocalLength = centerFocal;

	this->camera_L = new Camera(LEFT);
	this->camera_R = new Camera(RIGHT);
	if (this->centerCameraFlag){
		this->camera_C = new Camera(CENTER,false,25);
	}

	this->VCC_Th = VCC_Threshold;

	this->vcc_L = new VCC(this->VCC_Th);
	this->vcc_R = new VCC(this->VCC_Th);
	if (this->centerCameraFlag){
		this->vcc_C = new VCC(this->VCC_Th);
		this->vcc_C->kalmanFlag = false;
	}
	this->vcc_L->kalmanInitialize(VCC_INPUT_IMAGE_SIZE_X / 2, VCC_INPUT_IMAGE_SIZE_Y / 2); //TEST
	this->vcc_R->kalmanInitialize(VCC_INPUT_IMAGE_SIZE_X / 2, VCC_INPUT_IMAGE_SIZE_Y / 2); //TEST
	if (this->centerCameraFlag)this->vcc_C->kalmanInitialize(VCC_INPUT_IMAGE_SIZE_X / 2, VCC_INPUT_IMAGE_SIZE_Y / 2); //TEST
	this->vcc_L->matchingParameters[6] = VCC_INPUT_IMAGE_SIZE_X / 2;
	this->vcc_L->matchingParameters[7] = VCC_INPUT_IMAGE_SIZE_Y / 2;
	this->vcc_R->matchingParameters[6] = VCC_INPUT_IMAGE_SIZE_X / 2;
	this->vcc_R->matchingParameters[7] = VCC_INPUT_IMAGE_SIZE_Y / 2;
	if (this->centerCameraFlag)this->vcc_C->matchingParameters[6] = VCC_INPUT_IMAGE_SIZE_X / 2;
	if (this->centerCameraFlag)this->vcc_C->matchingParameters[7] = VCC_INPUT_IMAGE_SIZE_Y / 2;

	this->kalmanInitialize();

	this->trackingLoopFlag = false;
	this->trackingState = "–¢‰Ò“­";
	this->trackingThreshold = 170;
	this->trackingHomeFlag = false;
	this->trackingMoveFlag = true;
	this->trackingTiming = false;

	this->linear_a2 = 0.0;
	this->linear_a1 = 0.0;
	this->linear_a0 = 0.0;
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

void Measurement::tracking(char* com, int baudrate){
	this->trackingState = "‰Šú‰»’†";
	PTU ptu(com, baudrate);
	//ptu.turnHome();
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
		PanTilt pt, my;
		my.pan = ptu.panAngle;
		my.tilt = ptu.tiltAngle;
		this->mtx.lock();
		if (!this->centerCameraFlag){
			pt = this->trackingAngle;
		}
		this->platformState = my;
		this->mtx.unlock();
		if (this->centerCameraFlag){
			this->camera_C->getImage();
			cv::waitKey(1);
			this->vcc_C->setInputImage(this->camera_C->grayImage);
			cv::waitKey(1);
			this->vcc_C->templateMatching();
			cv::waitKey(1);
			this->angle_C = angleCalculation(vcc_C,this->centerCameraFocalLength);
		}
		else{
			while (!this->trackingTiming)cv::waitKey(1);
			this->trackingTiming = false;
		}
		if (this->trackingMoveFlag){
			this->trackingState = "‰Ò“­’†";
			if (this->centerCameraFlag){
				int mC = this->vcc_C->matchingParameters[8];
				if (mC < this->trackingThreshold){
					ptu.turn(this->angle_C.pan, this->angle_C.tilt);
					std::cout << "pan[" << RAD2DEG(this->angle_C.pan) << "]\ttilt[" << RAD2DEG(this->angle_C.tilt) << "]" << std::endl;
				}
				else{ ptu.turn(0, 0); }
			}
			else{
				this->mtx.lock();
				int mL = this->vcc_L->matchingParameters[8];
				int mR = this->vcc_R->matchingParameters[8];
				this->mtx.unlock();
				if (mL < this->trackingThreshold && mR < this->trackingThreshold){
					ptu.turn(pt.pan, pt.tilt);
				}
				else{ ptu.turn(0, 0); }
			}
		}
		else{
			this->trackingState = "’âŽ~’†";
		}
	}
}

void Measurement::threadTracking(char* com, int baudrate){
	this->trackingLoopFlag = true;
	this->trackingThread = std::thread(std::bind(&Measurement::tracking, this, com, baudrate));
}

void Measurement::threadTrackingJoin(){
	if (this->trackingThread.joinable())
		this->trackingThread.join();
}

Measurement::PanTilt Measurement::angleCalculation(VCC *vcc, double f){
	double x = vcc->matchingParameters[2] + vcc->subpixelResult_x - VCC_INPUT_IMAGE_SIZE_X / 2;
	double y = vcc->matchingParameters[3] + vcc->subpixelResult_y - VCC_INPUT_IMAGE_SIZE_Y / 2;
	PanTilt pt;
	pt.pan = atan2(x*this->pixelSize, f);
	pt.tilt = atan2(y*this->pixelSize, f);
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
	this->angle_L = angleCalculation(vcc_L,this->focalLength);
	this->angle_R = angleCalculation(vcc_R,this->focalLength);
	this->non_offset.original = this->baselineLength / (tan(this->angle_L.pan) - tan(this->angle_R.pan));
	this->non_offset.mid = sqrt(pow(this->non_offset.original, 2)*(pow(tan(angle_L.pan), 2) + pow(tan(angle_R.pan), 2) + 2) / 2 - pow((double)this->baselineLength, 2) / 4);
	this->non_offset.theta = acos(this->non_offset.original / this->non_offset.mid);

	if (this->vcc_L->matchingParameters[8] < 180 && this->vcc_R->matchingParameters[8] < 180){
		if (prev_distances.size() < 5) prev_distances.push_back(this->distance.original);
		else{
			for (int i = 1; i < prev_distances.size(); i++){
				prev_distances[i - 1] = prev_distances[i];
			}
			prev_distances.pop_back();
			prev_distances.push_back(this->distance.original);
		}
	}
	double prev_average_distance = 0;
	for (int i = 0; i < prev_distances.size(); i++){
		prev_average_distance += prev_distances[i];
	}
	prev_average_distance /= prev_distances.size();
	double qua = quadratic(this->linear_a2, this->linear_a1 + 1, this->linear_a0 - this->non_offset.original);
	if (qua < 0) this->distance.original = this->non_offset.original;
	else this->distance.original = qua;
	this->distance.mid = sqrt(pow(this->distance.original, 2)*(pow(tan(angle_L.pan), 2) + pow(tan(angle_R.pan), 2) + 2) / 2 - pow((double)this->baselineLength, 2) / 4);
	this->distance.theta = acos(this->distance.original / this->distance.mid);
	if (angle_L.pan + angle_R.pan < 0) this->distance.theta *= -1;
	cv::Mat prediction = this->KF->predict();
	double predictDist = prediction.at<float>(0);
	if (fabs(this->distance.mid - prev_average_distance)>200) (*this->KF_Measurement)(0) = prev_distances[prev_distances.size()-1];
	else (*this->KF_Measurement)(0) = this->distance.mid;
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


double Measurement::quadratic(double a2, double a1, double a0)
{
	double Re1, Re2, Im1, Im2, D;

	D = a1*a1 - 4.0*a2*a0;

	if (D>0) {
		Re1 = (-a1 + sqrt(D)) / (2.0*a2);
		Re2 = (-a1 - sqrt(D)) / (2.0*a2);
		Im1 = 0.0;
		Im2 = 0.0;
	}
	else if (D == 0) {
		Re1 = -a1 / (2.0*a2);
		Im1 = 0.0;
	}
	else {
		Re1 = Re2 = -a1 / (2.0*a2);
		Im1 = sqrt(-D) / (2.0*a2);
		Im2 = -Im1;
	}

	if (D == 0) {
		return Re1;
	}
	else {
		if (Re1 > 0) return Re1;
		if (Re2 > 0) return Re2;
	}
	return -1;
}
