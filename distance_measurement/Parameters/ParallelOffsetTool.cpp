
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "opencv2/opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"


//#define QVGA


#define CV_LIBPATH_STR "C:/opencv2.4.8/build/x86/vc12/lib/"
#define CV_VERSION_STR CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)
#if _DEBUG
#define CV_EXTENSION_STR "d.lib"
#else
#define CV_EXTENSION_STR ".lib"
#endif

#pragma comment(lib, CV_LIBPATH_STR "opencv_core" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_imgproc" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_highgui" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_objdetect" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_contrib" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_features2d" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_flann" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_legacy" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_ts" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_video" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_calib3d" CV_VERSION_STR CV_EXTENSION_STR)

#pragma comment(lib, CV_LIBPATH_STR "opencv_nonfree" CV_VERSION_STR CV_EXTENSION_STR)



#include "ParallelOffsetTool.h"
#include "ParamShow.h"

using namespace Parameters;

class Approximation{
public:
	std::vector<cv::Point2d> plot;
	int calculate();

	double a0; //定数項
	double a1; //1次の項
	double a2; //2次の項
};

int Approximation::calculate(){
	cv::Mat  matX = cv::Mat::zeros(3, 3, CV_64FC1);
	cv::Mat  matY = cv::Mat::zeros(3, 1, CV_64FC1);
	cv::Mat  matA = cv::Mat::zeros(3, 1, CV_64FC1);
	for (int i = 0; i < plot.size(); i++){
		matX.at<double>(0, 0) += 1;
		matX.at<double>(0, 1) += plot[i].x;
		matX.at<double>(0, 2) += pow(plot[i].x, 2);
		matX.at<double>(1, 0) += plot[i].x;
		matX.at<double>(1, 1) += pow(plot[i].x, 2);
		matX.at<double>(1, 2) += pow(plot[i].x, 3);
		matX.at<double>(2, 0) += pow(plot[i].x, 2);
		matX.at<double>(2, 1) += pow(plot[i].x, 3);
		matX.at<double>(2, 2) += pow(plot[i].x, 4);
		matY.at<double>(0, 0) += plot[i].y;
		matY.at<double>(1, 0) += plot[i].y*plot[i].x;
		matY.at<double>(2, 0) += plot[i].y*pow(plot[i].x, 2);
	}
	matA = matX.inv()*matY;
	a0 = matA.at<double>(0, 0);
	a1 = matA.at<double>(1, 0);
	a2 = matA.at<double>(2, 0);
	return 0;
}

int getVec(std::string filename, std::vector<double> &vec){
	std::ifstream ifs(filename);
	std::string str;
	while (std::getline(ifs, str) && ifs){
		std::stringstream ss;
		ss << str;
		double d;
		ss >> d;
		vec.push_back(d);
	}
	return 0;
}


System::Void ParallelOffsetTool::get_distance_button_Click(System::Object^  sender, System::EventArgs^  e) {

	ParamShow^ ps;
	if (this->Owner != nullptr){
		//親のフォームクラス
		ps = static_cast<ParamShow^>(this->Owner);
		this->measure_vaule_box->Text = ps->label3->Text;
	}
}
System::Void ParallelOffsetTool::getBaseLength(){

	ParamShow^ ps;
	if (this->Owner != nullptr){
		//親のフォームクラス
		ps = static_cast<ParamShow^>(this->Owner);
		this->base_length->Text = ps->base_box->Text;
	}
}

System::Void ParallelOffsetTool::ApplyOffset(){
	ParamShow^ ps;
	if (this->Owner != nullptr){
		//親のフォームクラス
		ps = static_cast<ParamShow^>(this->Owner);
		ps->linear_a2->Text = this->linear_a2->Text;
		ps->linear_a1->Text = this->linear_a1->Text;
		ps->linear_a0->Text = this->linear_a0->Text;
		ps->offset_check->Checked = true;
	}
}
System::Void ParallelOffsetTool::timer1_Tick(System::Object^  sender, System::EventArgs^  e){
	if (!base_length_read_flag){
		this->readPrevData();
		//this->getBaseLength();
		this->base_length_read_flag = true;
	}
	this->time_count++;
	linearApprox la;
	std::vector<double> correct;
	std::vector<double> measure;
	for (int i = 0; i < this->true_list->Items->Count; i++){
		std::stringstream ss;
		ss << this->ToStdString(this->true_list->GetItemText(this->true_list->Items[i]));
		double d;
		ss >> d;
		correct.push_back(d);
	}
	for (int i = 0; i < this->measure_list->Items->Count; i++){
		std::stringstream ss;
		ss << this->ToStdString(this->measure_list->GetItemText(this->measure_list->Items[i]));
		double d;
		ss >> d;
		measure.push_back(d);
	}
	if (correct.size() < 2){
		if (this->time_count > 100){
			this->toolStripStatusLabel1->Text = "補正値の算出には２組以上のデータが必要です";
		}
		return;
	}	

	Approximation app;

	std::vector<cv::Point2d> arr;
	for (int i = 0; i < measure.size(); i++){
		cv::Point2d p;
		p.x = correct[i];
		p.y = measure[i] - correct[i];
		arr.push_back(p);
	}
	app.plot = arr;
	app.calculate();

	{
		std::stringstream ss;
		ss << app.a2;
		std::string str = ss.str();
		this->linear_a2->Text = this->ToSystemString(str);
	}
	{
		std::stringstream ss;
		ss << app.a1;
		std::string str = ss.str();
		this->linear_a1->Text = this->ToSystemString(str);
	}
	{
		std::stringstream ss;
		ss << app.a0;
		std::string str = ss.str();
		this->linear_a0->Text = this->ToSystemString(str);
	}
}