#include "view.h"

View::View(std::string windowName, int windowPlace_x, int windowPlace_y){
	this->myWindowName = windowName;
	cv::namedWindow(this->myWindowName);
	cv::moveWindow(this->myWindowName, windowPlace_x, windowPlace_y);
	cv::setMouseCallback(this->myWindowName,this->onMouse);
}

View::~View(){}

void View::onMouse(int event, int x, int y, int flags, void* param){
	if (event == CV_EVENT_MOUSEMOVE){

	}
	else if (event == CV_EVENT_LBUTTONDOWN){

	}
	else if (event == CV_EVENT_RBUTTONDOWN){

	}
}

void View::show(cv::Mat image, int vcc_x, int vcc_y, int area_x, int area_y, bool isColor){
	cv::Mat showImage;
	if (isColor){
		showImage = image.clone();
	}
	else{
		cv::cvtColor(image, showImage, CV_GRAY2BGR);
	}
	cv::rectangle(showImage, cv::Point(area_x - VCC_SEEK_AREA_HALF_SIZE, area_y - VCC_SEEK_AREA_HALF_SIZE),
		                     cv::Point(area_x + VCC_SEEK_AREA_HALF_SIZE, area_y + VCC_SEEK_AREA_HALF_SIZE),
		                     cv::Scalar(0, 0, 255),
		                     VIEW_DROW_RECTANGLE_THICKNESS);
	cv::rectangle(showImage, cv::Point(vcc_x - VCC_TEMPLATE_SIZE, vcc_y - VCC_TEMPLATE_SIZE),
		                     cv::Point(vcc_x + VCC_TEMPLATE_SIZE, vcc_y + VCC_TEMPLATE_SIZE),
		                     cv::Scalar(0, 255, 255),
		                     VIEW_DROW_RECTANGLE_THICKNESS);
	cv::Mat showImageResize;	
	cv::resize(showImage, showImageResize, cv::Size(showImage.cols / 2, showImage.rows/2));
	cv::imshow(this->myWindowName, showImageResize);
}