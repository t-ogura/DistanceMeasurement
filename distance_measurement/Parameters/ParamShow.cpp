#include "ParamShow.h"

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


using namespace Parameters;
using namespace System;

std::vector<double> prev_angles;

cv::KalmanFilter *KF_Angle;
cv::Mat_<float> *KF_Angle_State;
cv::Mat *KF_Angle_ProcessNoise;
cv::Mat_<float> *KF_Angle_Measurement;

double angleKF = 0;
double prev_angle = 0;

System::Void ParamShow::kalmanInit(){

	KF_Angle = new cv::KalmanFilter(2, 1, 0);
	KF_Angle_State = new cv::Mat_<float>(2, 1);
	KF_Angle_ProcessNoise = new cv::Mat(2, 1, CV_32F);
	KF_Angle_Measurement = new cv::Mat_<float>(1, 1);
	KF_Angle_Measurement->setTo(cv::Scalar(0));

	KF_Angle->statePre.at<float>(0) = 0;
	KF_Angle->statePre.at<float>(1) = 0;
	KF_Angle->transitionMatrix = *(cv::Mat_<float>(2, 2) << 1, 0, 0, 1);

	cv::setIdentity(KF_Angle->measurementMatrix);
	cv::setIdentity(KF_Angle->processNoiseCov, cv::Scalar::all(1e-4));
	cv::setIdentity(KF_Angle->measurementNoiseCov, cv::Scalar::all(1e-1));
	cv::setIdentity(KF_Angle->errorCovPost, cv::Scalar::all(.1));

	KF_Angle->statePre.at<float>(0) = 0;
	KF_Angle->statePre.at<float>(1) = 0;
}

double ParamShow::panKF(double platform, double ditected){
	double angle = platform + ditected;
	int correlation = Convert::ToInt32(this->corr_c->Text);
	int tracking_th = Convert::ToInt32(this->plat_th_box->Text);

	if (correlation<tracking_th - 20){
		if (prev_angles.size() < 5) prev_angles.push_back(angle);
		else{
			for (int i = 1; i < prev_angles.size(); i++){
				prev_angles[i - 1] = prev_angles[i];
			}
			prev_angles.pop_back();
			prev_angles.push_back(angle);
		}
	}
	double prev_angle_kf = angleKF;
	double prev_average_angle = 0;
	for (int i = 0; i < prev_angles.size(); i++){
		prev_average_angle += prev_angles[i];
	}
	prev_average_angle /= prev_angles.size();

	cv::Mat prediction = KF_Angle->predict();
	double predictDist = prediction.at<float>(0);
	if (fabs(angle - prev_average_angle)>10.0){ (*KF_Angle_Measurement)(0) = prev_angle_kf; }
	else if (correlation > tracking_th - 20){ (*KF_Angle_Measurement)(0) = prev_angle_kf; }
	else (*KF_Angle_Measurement)(0) = angle;
	cv::Mat estimated = KF_Angle->correct((*KF_Angle_Measurement));
	angleKF = estimated.at<float>(0);
	return angleKF;
}