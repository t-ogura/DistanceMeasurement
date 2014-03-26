#include "camera.h"

//【DirectShow関係（USBカメラにアクセスするのに必要）】
#include "ewclib21/ewclib.h"     //cv.hより後でインクルードする
#include <fstream>

Camera::Camera(int cameraID, bool cameraIsColor){
	this->ID = cameraID;
	this->cameraColorFlag = cameraIsColor;

	int cameraInitialize;
	if (this->cameraColorFlag){
		this->cameraImage = cv::Mat(cv::Size(CAMERA_GET_IMAGE_WIDTH, CAMERA_GET_IMAGE_HEIGHT), CV_8UC3);
		cameraInitialize = EWC_Open(this->ID, CAMERA_GET_IMAGE_WIDTH, CAMERA_GET_IMAGE_HEIGHT, CAMERA_FPS, this->ID, MEDIASUBTYPE_RGB32);
	}
	else{
		this->cameraImage = cv::Mat(cv::Size(CAMERA_GET_IMAGE_WIDTH, CAMERA_GET_IMAGE_HEIGHT), CV_8UC1);
		cameraInitialize = EWC_Open(this->ID, CAMERA_GET_IMAGE_WIDTH, CAMERA_GET_IMAGE_HEIGHT, CAMERA_FPS, this->ID,MEDIASUBTYPE_RGB8);
	}
	this->colorImage = cv::Mat(cv::Size(CAMERA_RESIZE_IMAGE_WIDTH, CAMERA_RESIZE_IMAGE_HEIGHT), CV_8UC3);
	this->grayImage = cv::Mat(cv::Size(CAMERA_RESIZE_IMAGE_WIDTH, CAMERA_RESIZE_IMAGE_HEIGHT), CV_8UC1);
	if (cameraInitialize){
		std::cerr << "Camera initialization failed   ID:"<< this->ID << std::endl;
		std::cin.get();
	}
	std::cout << "Number of found camera :" << EWC_GetCamera() << std::endl;

	EWC_SetBuffer(this->ID, cameraImage.data);

	EWC_SetValue(this->ID, EWC_EXPOSURE, CAMERA_EXPOSURE);
	//EWC_SetAuto(this->ID, EWC_EXPOSURE);
	this->writeCameraParam();
}

Camera::~Camera(){
	EWC_CloseAll();
}

void Camera::getImage(){
	while (1){
		if (EWC_IsCaptured(this->ID))break;
	}
	if (this->cameraColorFlag){
		cv::resize(this->cameraImage, this->colorImage,this->colorImage.size());
		cv::cvtColor(this->colorImage, this->grayImage,CV_RGB2GRAY);
	}
	else{
		cv::resize(this->cameraImage, this->grayImage, this->grayImage.size());
		cv::cvtColor(this->grayImage, this->colorImage, CV_GRAY2BGR);
	}
}

void Camera::writeCameraParam(){
	std::ofstream ofs;
	char filename[50];
	sprintf_s(filename, "Camera[%0d].txt", this->ID);
	ofs.open(filename);
	ofs << filename << std::endl;
	ofs << "EWC_BRIGHTNESS				" << EWC_GetValue(this->ID, EWC_BRIGHTNESS) << std::endl;
	ofs << "EWC_CONTRAST				" << EWC_GetValue(this->ID, EWC_CONTRAST) << std::endl;
	ofs << "EWC_HUE						" << EWC_GetValue(this->ID, EWC_HUE) << std::endl;
	ofs << "EWC_SATURATION				" << EWC_GetValue(this->ID, EWC_SATURATION) << std::endl;
	ofs << "EWC_SHARPNESS				" << EWC_GetValue(this->ID, EWC_SHARPNESS) << std::endl;
	ofs << "EWC_GAMMA					" << EWC_GetValue(this->ID, EWC_GAMMA) << std::endl;
	ofs << "EWC_COLORENABLE				" << EWC_GetValue(this->ID, EWC_COLORENABLE) << std::endl;
	ofs << "EWC_WHITEBALANCE			" << EWC_GetValue(this->ID, EWC_WHITEBALANCE) << std::endl;
	ofs << "EWC_BACKLIGHTCOMPENSATION	" << EWC_GetValue(this->ID, EWC_BACKLIGHTCOMPENSATION) << std::endl;
	ofs << "EWC_GAIN					" << EWC_GetValue(this->ID, EWC_GAIN) << std::endl;
	ofs << "EWC_PAN						" << EWC_GetValue(this->ID, EWC_PAN) << std::endl;
	ofs << "EWC_TILT					" << EWC_GetValue(this->ID, EWC_TILT) << std::endl;
	ofs << "EWC_ROLL					" << EWC_GetValue(this->ID, EWC_ROLL) << std::endl;
	ofs << "EWC_ZOOM					" << EWC_GetValue(this->ID, EWC_ZOOM) << std::endl;
	ofs << "EWC_EXPOSURE				" << EWC_GetValue(this->ID, EWC_EXPOSURE) << std::endl;
	ofs << "EWC_IRIS					" << EWC_GetValue(this->ID, EWC_IRIS) << std::endl;
	ofs << "EWC_FOCUS					" << EWC_GetValue(this->ID, EWC_FOCUS) << std::endl;
	ofs.close();
}