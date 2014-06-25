#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "global.h"


#define CAMERA_GET_IMAGE_WIDTH 1280
#define CAMERA_GET_IMAGE_HEIGHT 960
#define CAMERA_RESIZE_IMAGE_WIDTH 640
#define CAMERA_RESIZE_IMAGE_HEIGHT 480


class Camera{
private:
	int ID;
	bool cameraColorFlag;

public:
	Camera(int cameraID, bool cameraIsColor = false, int FPS = 15);
	~Camera(); 
	int setCameraExposure(int ex);

	cv::Mat cameraImage;
	cv::Mat colorImage;
	cv::Mat grayImage;

	void getImage();
	void writeCameraParam();
};

#endif _CAMERA_H_