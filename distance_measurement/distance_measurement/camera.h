#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "global.h"


#define CAMERA_GET_IMAGE_WIDTH 1280
#define CAMERA_GET_IMAGE_HEIGHT 960
#define CAMERA_RESIZE_IMAGE_WIDTH 640
#define CAMERA_RESIZE_IMAGE_HEIGHT 480
#define CAMERA_FPS 79.60
#define CAMERA_EXPOSURE 41

class Camera{
private:
	int ID;
	bool cameraColorFlag;

public:
	Camera(int cameraID, bool cameraIsColor = false);
	~Camera();

	cv::Mat cameraImage;
	cv::Mat colorImage;
	cv::Mat grayImage;

	void getImage();
	void writeCameraParam();
};

#endif _CAMERA_H_