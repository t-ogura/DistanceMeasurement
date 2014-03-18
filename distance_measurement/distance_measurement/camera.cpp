#include "camera.h"

//【DirectShow関係（USBカメラにアクセスするのに必要）】
#include "ewclib21/ewclib.h"     //cv.hより後でインクルードする

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
	this->colorImage = cv::Mat(cv::Size(CAMERA_RESIZE_IMAGE_WIDTH, CAMERA_GET_IMAGE_HEIGHT), CV_8UC3);
	this->grayImage = cv::Mat(cv::Size(CAMERA_RESIZE_IMAGE_WIDTH, CAMERA_GET_IMAGE_HEIGHT), CV_8UC1);
	if (cameraInitialize){
		std::cerr << "Camera initialization failed   ID:"<< this->ID << std::endl;
		std::cin.get();
	}
	std::cout << "Number of found camera :" << EWC_GetCamera() << std::endl;

	EWC_SetBuffer(this->ID, cameraImage.data);
	
	EWC_SetAuto(this->ID, EWC_EXPOSURE);
}

Camera::~Camera(){
	EWC_CloseAll();
}

void Camera::getImage(){
	while (1){	
		EWC_IsCaptured(this->ID);
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