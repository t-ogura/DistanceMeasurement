#include "measurement.h"

Measurement::Measurement(double pSize, double fLength, double bLength,int VCC_Threshold, bool centerCamera, double centerFocal){

	initParams ip;
	readInitFile(INIT_FILE_PATH, &ip);

	this->GNUPLOT = ip.GNUPLOT;
	this->LEFT_OR_RIGHT = ip.LEFT_OR_RIGHT;

	this->pixelSize = pSize;
	this->focalLength = fLength;
	this->baselineLength = bLength;

	this->centerCameraFlag = centerCamera;
	this->centerCameraFocalLength = centerFocal;

	this->camera_L = new Camera(ip.LEFT_CAMERA_ID);
	this->camera_L->setCameraExposure(ip.LEFT_CAMERA_EXPOSURE);
	this->camera_R = new Camera(ip.RIGHT_CAMERA_ID);
	this->camera_R->setCameraExposure(ip.RIGHT_CAMERA_EXPOSURE);
	if (this->centerCameraFlag){
		this->camera_C = new Camera(ip.CENTER_CAMERA_ID, true, 25);
		this->camera_C->setCameraExposure(ip.CENTER_CAMERA_EXPOSURE);
	}

	this->platform_comnumber = ip.COM_PORT_NUMBER;

	this->VCC_Th = VCC_Threshold;

	this->vcc_L = new VCC(this->VCC_Th);
	this->vcc_R = new VCC(this->VCC_Th);
	if (this->centerCameraFlag){
		this->vcc_C = new VCC(this->VCC_Th);
		this->vcc_C->kalmanFlag = false;
		this->vcc_C->allSeekThreshold = 200;
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

	this->kalmanInitialize(ip.MEASUREMENT_KALMANFILTER_PROCESS_NOISE_COV,ip.MEASUREMENT_KALMANFILTER_MEASUREMENT_NOISE_COV);

	this->trackingLoopFlag = false;
	this->trackingState = "No connect";
	this->trackingThreshold = 170;
	this->trackingHomeFlag = false;
	this->trackingMoveFlag = true;
	this->trackingTiming = false;
	this->outControlFlag = false;
	this->outControlAbs = false;

	this->linear_a2 = 0.0;
	this->linear_a1 = 0.0;
	this->linear_a0 = 0.0;
}

Measurement::~Measurement(){}


int Measurement::readInitFile(std::string filename, initParams *ini){
	std::ifstream ifs(filename);
	if (ifs.fail()){
		std::cerr << "File open error [" << filename << "]" << std::endl;
		std::cin.get();
	}

	std::string str;
	while (ifs&&std::getline(ifs, str)){
		if (str.size() > 1){
			if (str.c_str()[0] == '%'){
				continue; 
			}
		}
		std::string token1, token2;
		std::istringstream stream(str);
		std::getline(stream, token1, ' ');
		std::getline(stream, token2);
		std::stringstream ss;
		ss << token2;
		if (token1 == "LEFT_CAMERA_EXPOSURE") ss >> ini->LEFT_CAMERA_EXPOSURE;
		else if (token1 == "RIGHT_CAMERA_EXPOSURE") ss >> ini->RIGHT_CAMERA_EXPOSURE;
		else if (token1 == "CENTER_CAMERA_EXPOSURE") ss >> ini->CENTER_CAMERA_EXPOSURE;
		else if (token1 == "MEASUREMENT_KALMANFILTER_PROCESS_NOISE_COV") ss >> ini->MEASUREMENT_KALMANFILTER_PROCESS_NOISE_COV;
		else if (token1 == "MEASUREMENT_KALMANFILTER_MEASUREMENT_NOISE_COV") ss >> ini->MEASUREMENT_KALMANFILTER_MEASUREMENT_NOISE_COV;
		else if (token1 == "LEFT_CAMERA_ID") ss >> ini->LEFT_CAMERA_ID;
		else if (token1 == "RIGHT_CAMERA_ID") ss >> ini->RIGHT_CAMERA_ID;
		else if (token1 == "CENTER_CAMERA_ID") ss >> ini->CENTER_CAMERA_ID;
		else if (token1 == "COM_PORT_NUMBER") ini->COM_PORT_NUMBER = "\\\\.\\" + token2;
		else if (token1 == "LEFT_OR_RIGHT") ini->LEFT_OR_RIGHT = token2;
		else if (token1 == "GNUPLOT") ini->GNUPLOT = token2;
	}
	return 0;
}

void Measurement::kalmanInitialize(double processNoisCov, double measurementNoiseCov){
	this->KF = new cv::KalmanFilter(2, 1, 0);
	this->KF_State = new cv::Mat_<float>(2, 1);
	this->KF_ProcessNoise = new cv::Mat(2, 1, CV_32F);
	this->KF_Measurement = new cv::Mat_<float>(1, 1);
	this->KF_Measurement->setTo(cv::Scalar(0));

	this->KF->statePre.at<float>(0) = 0;
	this->KF->statePre.at<float>(1) = 0;
	this->KF->transitionMatrix = *(cv::Mat_<float>(2, 2) << 1, 0, 0, 1);

	cv::setIdentity(this->KF->measurementMatrix);
	cv::setIdentity(this->KF->processNoiseCov, cv::Scalar::all(processNoisCov));
	cv::setIdentity(this->KF->measurementNoiseCov, cv::Scalar::all(measurementNoiseCov));
	cv::setIdentity(this->KF->errorCovPost, cv::Scalar::all(.1));

	this->KF->statePre.at<float>(0) = 0;
	this->KF->statePre.at<float>(1) = 0;
}

void Measurement::tracking(char* com, int baudrate){
	PTU ptu(com, baudrate);
	//ptu.turnHome();
	Sleep(2000);
	ptu.setSpeed();
	this->trackingState = "Working";
	while (this->trackingLoopFlag){
		if (this->trackingHomeFlag){
			this->trackingState = "Turn home";
			ptu.turnHome();
			Sleep(2000);
			ptu.setSpeed();
			this->trackingHomeFlag = false;
			this->trackingState = "Working";
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
		this->mtx.lock();
		bool pcFlag = this->outControlFlag;
		this->mtx.unlock();
		if (pcFlag){
			this->mtx.lock();
			this->trackingMoveFlag = false;
			bool abs = this->outControlAbs;
			PanTilt movePT = this->outControlPT;
			this->mtx.unlock();
			if (abs){
				ptu.turn(movePT.pan, movePT.tilt, true);
				this->mtx.lock();
				this->outControlAbs = false;
				this->mtx.unlock();
			}
			else{
				ptu.turn(movePT.pan, movePT.tilt);
			}

			this->mtx.lock();
			this->outControlFlag = false;
			this->mtx.unlock();
		}

		if (this->trackingMoveFlag){
			this->trackingState = "Working";
			if (this->centerCameraFlag){
				int mC = this->vcc_C->matchingParameters[8];
				//std::cout << this->vcc_C->matchingParameters[8] << std::endl;
				if (mC < this->trackingThreshold){
					ptu.turn(this->angle_C.pan*0.4, this->angle_C.tilt*0.4);
					//std::cout << "pan[" << RAD2DEG(this->angle_C.pan) << "]\ttilt[" << RAD2DEG(this->angle_C.tilt) << "]" << std::endl;
				}
				else{ ptu.turn(0, 0); }
			}
			else{
				this->mtx.lock();
				int mL = this->vcc_L->matchingParameters[8];
				int mR = this->vcc_R->matchingParameters[8];
				this->mtx.unlock();
				if (mL < this->trackingThreshold && mR < this->trackingThreshold){
					ptu.turn(pt.pan*0.4, pt.tilt*0.4);
				}
				else{ ptu.turn(0, 0); }
			}
		}
		else{
			this->trackingState = "Stoping";
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

	if (this->vcc_L->matchingParameters[8] < this->vcc_L->databaseSearchThreshold && this->vcc_R->matchingParameters[8] < this->vcc_R->databaseSearchThreshold){
		if (prev_distances.size() < 5) prev_distances.push_back(this->distance.original);
		else{
			for (int i = 1; i < prev_distances.size(); i++){
				prev_distances[i - 1] = prev_distances[i];
			}
			prev_distances.pop_back();
			prev_distances.push_back(non_offset.original);
		}
	}
	double prev_dist_kf = this->distance.kf;
	double prev_dist_mid = this->distance.mid;
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
	if (fabs(this->non_offset.mid - prev_average_distance)>500){ (*this->KF_Measurement)(0) = prev_dist_kf;}
	else if (this->vcc_L->matchingParameters[8] > this->vcc_L->databaseSearchThreshold && this->vcc_R->matchingParameters[8] > this->vcc_R->databaseSearchThreshold){ (*this->KF_Measurement)(0) = prev_dist_kf; }
	else (*this->KF_Measurement)(0) = this->distance.mid;
	cv::Mat estimated = this->KF->correct((*this->KF_Measurement));
	this->distance.kf = estimated.at<float>(0);
	if (estimated.at<float>(1) != 0){
		initParams ip;
		readInitFile(INIT_FILE_PATH, &ip);
		this->kalmanInitialize(ip.MEASUREMENT_KALMANFILTER_PROCESS_NOISE_COV, ip.MEASUREMENT_KALMANFILTER_MEASUREMENT_NOISE_COV);
		std::cout << "catch error" << std::endl;
	}
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
