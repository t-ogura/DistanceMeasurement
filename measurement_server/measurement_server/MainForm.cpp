#include "MainForm.h"
#include "global.h"
#define _USE_MATH_DEFINES
#include <math.h>

//#define SCALE 1000

#define WIN_SIZE 300
#define WIN_MARGIN 10

using namespace measurement_server;

System::Void MainForm::vessel_pose_view(double &vessel_angle, double &vessel_pos_x, double &vessel_pos_y, double &relative_angle, double &relative_x, double &relative_y){

	cv::Mat resultImage_vesselbased = cv::Mat::zeros(cv::Size(WIN_SIZE, WIN_SIZE), CV_8UC3);
	//cv::Mat resultImage_targetbased = cv::Mat::zeros(cv::Size(WIN_SIZE, WIN_SIZE), CV_8UC3);

	double distanceBetweenTargets = Convert::ToDouble(this->f_distanceBetweenTargets->Text);
	double distanceBetweenSystems = Convert::ToDouble(this->f_distanceBetweenSystems->Text);
	double distanceBetweenTargetsHalf = distanceBetweenTargets / 2;
	double distanceBetweenSystemsHalf = distanceBetweenSystems / 2;
	double pan_L = -this->pan_angle_L; // pan_angle * (-1)
	double pan_R = -this->pan_angle_R; // pan_angle * (-1)
	double dist_L = this->distance_L;
	double dist_R = this->distance_R;
	double fiducial_pan_L;
	double fiducial_pan_R;
	double fiducial_dist_L;
	double fiducial_dist_R;

	cv::Point2d midpointOfSystem;
	cv::Point2d midpointOftarget;
	cv::Point2d systemPos_L, systemPos_R;
	cv::Point2d targetPos_L, targetPos_R;
	cv::Point2d targetPos_L_predicted, targetPos_R_predicted;

	double targetRotation;
	double systemRotation;

	// origin point (center of coordinate system for positioning)
	cv::Point2d originPoint;
	originPoint.x = 0.0;
	originPoint.y = -1000.0;

	// installed position (displacement between center of systems and center of vessel)
	cv::Point2d installedPos;
	installedPos.x = 0.0;
	installedPos.y = -200.0;


	// system position
	systemPos_L.x = -distanceBetweenSystemsHalf;
	systemPos_L.y = 0;
	systemPos_R.x = distanceBetweenSystemsHalf;
	systemPos_R.y = 0;
	midpointOfSystem.x = 0;
	midpointOfSystem.y = 0;

	// target position
	targetPos_L.x = systemPos_L.x + sin(pan_angle_L)*distance_L;
	targetPos_L.y = systemPos_L.y + cos(pan_angle_L)*distance_L;
	targetPos_R.x = systemPos_R.x + sin(pan_angle_R)*distance_R;
	targetPos_R.y = systemPos_R.y + cos(pan_angle_R)*distance_R;
	midpointOftarget.x = (targetPos_L.x + targetPos_R.x) / 2;
	midpointOftarget.y = (targetPos_L.y + targetPos_R.y) / 2;

	// predict target position (simply correct positional and rotational error)
	double dx = targetPos_L.x - targetPos_R.x;
	double dy = targetPos_L.y - targetPos_R.y;
	targetRotation = atan2(dy, dx);
	double cosVal = cos(targetRotation);
	double sinVal = sin(targetRotation);
	targetPos_L_predicted.x = midpointOftarget.x - cosVal*distanceBetweenTargetsHalf;
	targetPos_L_predicted.y = midpointOftarget.y - sinVal*distanceBetweenTargetsHalf;
	targetPos_R_predicted.x = midpointOftarget.x + cosVal*distanceBetweenTargetsHalf;
	targetPos_R_predicted.y = midpointOftarget.y + sinVal*distanceBetweenTargetsHalf;

	// culculate relative position of origin point
	originPoint.x = originPoint.x*cos(targetRotation) - originPoint.y*sin(targetRotation);
	originPoint.y = originPoint.x*sin(targetRotation) + originPoint.y*cos(targetRotation);

	systemRotation = -targetRotation;

	// vessel position and rotation
	vessel_angle = systemRotation;
	vessel_pos_x = cos(targetRotation)*cv::norm(midpointOftarget);
	vessel_pos_y = sin(targetRotation)*cv::norm(midpointOftarget);

	//// update output value
	//this->vessel_angle_rad->Text = String::Format("{0:#0.##########}", vessel_angle);
	//this->vessel_angle_deg->Text = String::Format("{0:#0.##########}", vessel_angle / M_PI*180.);
	//this->vessel_pos_x->Text = String::Format("{0:#0.00}", vessel_pos_x);
	//this->vessel_pos_y->Text = String::Format("{0:#0.00}", vessel_pos_y);

	// 
	double x_size = std::max(targetPos_R.x, systemPos_R.x) - std::min(targetPos_L.x, systemPos_L.x);
	double y_size = std::max(targetPos_L.y, targetPos_R.y) - std::min(systemPos_L.y, systemPos_R.y);
	double scale = (WIN_SIZE - WIN_MARGIN * 2) / std::max(x_size, y_size);



	// draw coordinate
	//int line_interval = 1000 * scale;
	//int itr_x_begin = WIN_MARGIN / (1000 * scale);
	//int itr_x_end = (WIN_SIZE - WIN_MARGIN) / (1000 * scale);
	//int itr_y = WIN_SIZE / (1000 * scale) / 2;
	//cv::Scalar lgray = cv::Scalar(80, 80, 80);
	//cv::Scalar dgray = cv::Scalar(40, 40, 40);
	//for (int i = -itr_x_begin; i < itr_x_end + 1; i++){
	//	cv::line(resultImage_vesselbased,
	//		cv::Point(0, WIN_MARGIN + i*line_interval),
	//		cv::Point(WIN_SIZE, WIN_MARGIN + i*line_interval),
	//		dgray);
	//}
	//for (int i = -itr_y; i < itr_y + 1; i++){
	//	cv::line(resultImage_vesselbased,
	//		cv::Point(WIN_SIZE / 2 + i*itr_y*line_interval, 0),
	//		cv::Point(WIN_SIZE / 2 + i*itr_y*line_interval, WIN_SIZE),
	//		dgray);
	//}

	// draw coordinate
	cv::Point2d shift = cv::Point2d(WIN_SIZE / 2, WIN_MARGIN);
	int line_interval = 1000 * scale;
	cv::Scalar lgray = cv::Scalar(80, 80, 80);
	cv::Scalar dgray = cv::Scalar(40, 40, 40);

	double diff_x = midpointOftarget.x - originPoint.x;
	double diff_y = midpointOftarget.y - originPoint.y;

	int i = 1;
	while (1){
		double y = diff_y*scale + shift.y - i*line_interval;
		double y_left = y + originPoint.x*sinVal;
		double y_right = y - (WIN_SIZE - originPoint.x)*sinVal;
		if (y_left < 0 && y_right < 0){
			break;
		}
		cv::line(resultImage_vesselbased, cv::Point(0, y_left), cv::Point(WIN_SIZE, y_right), dgray);
		i++;
	}
	i = 1;
	while (1){
		double y = diff_y*scale + shift.y + i*line_interval;
		double y_left = y + originPoint.x*sinVal;
		double y_right = y - (WIN_SIZE - originPoint.x)*sinVal;
		if (y_left > WIN_SIZE && y_right > WIN_SIZE){
			break;
		}
		cv::line(resultImage_vesselbased, cv::Point(0, y_left), cv::Point(WIN_SIZE, y_right), dgray);
		i++;
	}
	i = 1;
	while (1){
		double x = diff_x*scale + shift.x - i*line_interval;
		double x_left = x - originPoint.x*sinVal;
		double x_right = x + (WIN_SIZE - originPoint.x)*sinVal;
		if (x_left < 0 && x_right < 0){
			break;
		}
		cv::line(resultImage_vesselbased, cv::Point(x_left, 0), cv::Point(x_right, WIN_SIZE), dgray);
		i++;
	}
	i = 1;
	while (1){
		double x = diff_x*scale + shift.x + i*line_interval;
		double x_left = x - originPoint.x*sinVal;
		double x_right = x + (WIN_SIZE - originPoint.x)*sinVal;
		if (x_left > WIN_SIZE && x_right > WIN_SIZE){
			break;
		}
		cv::line(resultImage_vesselbased, cv::Point(x_left, 0), cv::Point(x_right, WIN_SIZE), dgray);
		i++;
	}

	cv::line(resultImage_vesselbased,
		cv::Point(0, diff_y*scale + shift.y + originPoint.x*sinVal),
		cv::Point(WIN_SIZE, diff_y*scale + shift.y - (WIN_SIZE - originPoint.x)*sinVal),
		lgray);

	cv::line(resultImage_vesselbased,
		cv::Point(diff_x*scale + shift.x - originPoint.x*sinVal, 0),
		cv::Point(diff_x*scale + shift.x + (WIN_SIZE - originPoint.x)*sinVal, WIN_SIZE),
		lgray);

	cv::line(resultImage_vesselbased,
		cv::Point(diff_x*scale + shift.x - originPoint.x*sinVal, 0),
		cv::Point(diff_x*scale + shift.x + (WIN_SIZE - originPoint.x)*sinVal, WIN_SIZE),
		lgray);

	cv::circle(resultImage_vesselbased, midpointOftarget*scale - originPoint*scale + shift, 1, cv::Scalar(255, 255, 255), -1);


	// draw result
	//cv::circle(resultImage_vesselbased, (midpointOftarget - originPoint)*scale + shift, 1, cv::Scalar(255, 255, 255), -1);
	//cv::line(resultImage_vesselbased, shift, midpointOftarget*scale + shift, cv::Scalar(255, 255, 255));
	cv::circle(resultImage_vesselbased, shift, 5, cv::Scalar(255, 255, 255), -1);
	cv::circle(resultImage_vesselbased, midpointOftarget*scale + shift, 5, cv::Scalar(255, 255, 255));

	// draw vessel
	cv::line(resultImage_vesselbased, systemPos_L*scale + shift, systemPos_R*scale + shift, cv::Scalar(0, 0, 255));
	cv::circle(resultImage_vesselbased, systemPos_L*scale + shift, 5, cv::Scalar(255, 255, 0));
	cv::circle(resultImage_vesselbased, systemPos_R*scale + shift, 5, cv::Scalar(255, 255, 0));

	// draw target
	cv::line(resultImage_vesselbased, targetPos_L*scale + shift, targetPos_R*scale + shift, cv::Scalar(0, 255, 0));
	cv::circle(resultImage_vesselbased, targetPos_L*scale + shift, 5, cv::Scalar(255, 255, 0));
	cv::circle(resultImage_vesselbased, targetPos_R*scale + shift, 5, cv::Scalar(255, 255, 0));

	cv::flip(resultImage_vesselbased, resultImage_vesselbased, 0);
	cv::imshow("Relative", resultImage_vesselbased);
	//cv::imshow("result", resultImage_targetbased);
	cv::waitKey(1);


	/*
	double widthAlpha = fabs(dist_L*sin(pan_L)) + fabs(dist_R*sin(pan_R)); // ???
	double maxsize = (std::max)((std::max)(dist_L, dist_R), (std::max)(distanceBetweenTargets + widthAlpha, distanceBetweenSystems + widthAlpha)) * 1.2;  // magic number

	if (this->Flag_UseFiducialPoint){
		fiducial_pan_L = -this->fiducial_pan_angle_L; // pan_angle * (-1)
		fiducial_pan_R = -this->fiducial_pan_angle_R; // pan_angle * (-1)
		fiducial_dist_L = this->fiducial_distance_L;
		fiducial_dist_R = this->fiducial_distance_R;
		double _widthAlpha = fabs(fiducial_dist_L*sin(fiducial_pan_L)) + fabs(fiducial_dist_R*sin(fiducial_pan_R));
		double _maxsize = (std::max)((std::max)(fiducial_dist_L, fiducial_dist_R), (std::max)(distanceBetweenTargets + _widthAlpha, distanceBetweenSystems + _widthAlpha)) * 1.2; // magic number
		maxsize = (std::max)(maxsize, _maxsize);
	}

	int ta = SCALE / 2. - distanceBetweenTargets / maxsize*SCALE / 2.;
	int tb = SCALE / 2. + distanceBetweenTargets / maxsize*SCALE / 2.;
	cv::rectangle(resultImage_vesselbased, cv::Rect(ta - 15, SCALE*0.1 - 15, 30, 30), cv::Scalar(0, 255, 0), 5);
	cv::rectangle(resultImage_vesselbased, cv::Rect(tb - 15, SCALE*0.1 - 15, 30, 30), cv::Scalar(0, 255, 0), 5);


	//double systemPos_L_x = -1 * sin(pan_L)*dist_L - distanceBetweenSystems / 2.;
	//double systemPos_L_y = cos(pan_L)*dist_L;
	//double systemPos_R_x = -1 * sin(pan_R)*dist_R + distanceBetweenSystems / 2.;
	//double systemPos_R_y = cos(pan_R)*dist_R;
	//double systemPos_L_x = sin(pan_L)*dist_L - distanceBetweenSystems / 2.;
	//double systemPos_L_y = cos(pan_L)*dist_L;
	//double systemPos_R_x = sin(pan_R)*dist_R + distanceBetweenSystems / 2.;
	//double systemPos_R_y = cos(pan_R)*dist_R;

	//vessel_angle = atan2(systemPos_L_y - systemPos_R_y, systemPos_L_x - systemPos_R_x);
	//vessel_pos_x = (systemPos_L_x - systemPos_R_x) / 2.;
	//vessel_pos_y = (systemPos_L_y - systemPos_R_y) / 2.;

	//this->vessel_angle_rad->Text = String::Format("{0:#0.##########}", vessel_angle);
	//this->vessel_angle_deg->Text = String::Format("{0:#0.##########}", vessel_angle / M_PI*180.);
	//this->vessel_pos_x->Text = String::Format("{0:#0.00}", (systemPos_L_x - systemPos_R_x) / 2.);
	//this->vessel_pos_y->Text = String::Format("{0:#0.00}", (systemPos_L_y - systemPos_R_y) / 2.);

	if (this->Flag_UseFiducialPoint){
		//double _measure_a_x = -1 * sin(fiducial_pan_L)*fiducial_dist_L - distanceBetweenTargets / 2.;
		//double _measure_a_y = cos(fiducial_pan_L)*fiducial_dist_L;
		//double _measure_b_x = -1 * sin(fiducial_pan_R)*fiducial_dist_R - distanceBetweenTargets / 2.;
		//double _measure_b_y = cos(fiducial_pan_R)*fiducial_dist_R;
		double _measure_a_x = sin(fiducial_pan_L)*fiducial_dist_L - distanceBetweenTargets / 2.;
		double _measure_a_y = cos(fiducial_pan_L)*fiducial_dist_L;
		double _measure_b_x = sin(fiducial_pan_R)*fiducial_dist_R - distanceBetweenTargets / 2.;
		double _measure_b_y = cos(fiducial_pan_R)*fiducial_dist_R;
		double _vessel_angle = atan((_measure_a_y - _measure_b_y) / (_measure_a_x - _measure_b_x));

		this->rela_angle_rad->Text = String::Format("{0:#0.##########}", vessel_angle - _vessel_angle);
		this->rela_angle_deg->Text = String::Format("{0:#0.##########}", (vessel_angle - _vessel_angle) / M_PI*180.);
		this->rela_pos_x->Text = String::Format("{0:#0.00}", (systemPos_L_x - systemPos_R_x) / 2. - (_measure_a_x - _measure_b_x) / 2.);
		this->rela_pos_y->Text = String::Format("{0:#0.00}", (systemPos_L_y - systemPos_R_y) / 2. - (_measure_a_y - _measure_b_y) / 2.);
		relative_angle = vessel_angle - _vessel_angle;
		relative_x = (systemPos_L_x - systemPos_R_x) / 2. - (_measure_a_x - _measure_b_x) / 2.;
		relative_y = (systemPos_L_y - systemPos_R_y) / 2. - (_measure_a_y - _measure_b_y) / 2.;
	}
	else {
		relative_angle = 0;
		relative_x = 0;
		relative_y = 0;
	}
	if(this->Flag_UseFiducialPoint){
		//int ax = -1 * sin(fiducial_pan_L)*fiducial_dist_L / maxsize*SCALE + ta;
		int ax = sin(fiducial_pan_L)*fiducial_dist_L / maxsize*SCALE + ta;
		int ay = cos(fiducial_pan_L)*fiducial_dist_L / maxsize*SCALE + SCALE*0.1;
		cv::line(resultImage_vesselbased, cv::Point(ta, SCALE*0.1), cv::Point(ax, ay), cv::Scalar(0, 0, 128), 1);
		//int bx = -1 * sin(fiducial_pan_R)*fiducial_dist_R / maxsize*SCALE + tb;
		int bx = sin(fiducial_pan_R)*fiducial_dist_R / maxsize*SCALE + tb;
		int by = cos(fiducial_pan_R)*fiducial_dist_R / maxsize*SCALE + SCALE*0.1;
		cv::line(resultImage_vesselbased, cv::Point(tb, SCALE*0.1), cv::Point(bx, by), cv::Scalar(0, 0, 128), 1);
		cv::circle(resultImage_vesselbased, cv::Point(ax, ay), 15, cv::Scalar(128, 128, 0), 5);
		cv::circle(resultImage_vesselbased, cv::Point(bx, by), 15, cv::Scalar(128, 128, 0), 5);
		cv::line(resultImage_vesselbased, cv::Point(ax, ay), cv::Point(bx, by), cv::Scalar(0, 128, 128), 5);
	}
	{
		//int ax = -1 * sin(pan_L)*dist_L / maxsize*SCALE + ta;
		int ax = sin(pan_L)*dist_L / maxsize*SCALE + ta;
		int ay = cos(pan_L)*dist_L / maxsize*SCALE + SCALE*0.1;
		cv::line(resultImage_vesselbased, cv::Point(ta, SCALE*0.1), cv::Point(ax, ay), cv::Scalar(0, 0, 255), 1);
		//int bx = -1 * sin(pan_R)*dist_R / maxsize*SCALE + tb;
		int bx = sin(pan_R)*dist_R / maxsize*SCALE + tb;
		int by = cos(pan_R)*dist_R / maxsize*SCALE + SCALE*0.1;
		cv::line(resultImage_vesselbased, cv::Point(tb, SCALE*0.1), cv::Point(bx, by), cv::Scalar(0, 0, 255), 1);
		cv::circle(resultImage_vesselbased, cv::Point(ax, ay), 15, cv::Scalar(255, 255, 0), 5);
		cv::circle(resultImage_vesselbased, cv::Point(bx, by), 15, cv::Scalar(255, 255, 0), 5);
		cv::line(resultImage_vesselbased, cv::Point(ax, ay), cv::Point(bx, by), cv::Scalar(0, 255, 255), 5);
	}

	cv::Mat vessel = cv::Mat::zeros(SCALE, SCALE, CV_8UC3);
	double measuredis = Convert::ToDouble(this->f_distanceBetweenSystems->Text);
	int ma = SCALE / 2. - measuredis / maxsize*SCALE / 2.;
	int mb = SCALE / 2. + measuredis / maxsize*SCALE / 2.;
	cv::circle(vessel, cv::Point(ma, SCALE*0.9), 15, cv::Scalar(255, 255, 0), 5);
	cv::circle(vessel, cv::Point(mb, SCALE*0.9), 15, cv::Scalar(255, 255, 0), 5);
	{
		int ax = sin(pan_L)*dist_L / maxsize*SCALE + ma;
		int bx = sin(pan_R)*dist_R / maxsize*SCALE + mb;
		int ay = SCALE*0.9 - cos(pan_L)*dist_L / maxsize*SCALE;
		int by = SCALE*0.9 - cos(pan_R)*dist_R / maxsize*SCALE;
		cv::line(vessel, cv::Point(ma, SCALE*0.9), cv::Point(ax, ay), cv::Scalar(0, 0, 255), 1);
		cv::line(vessel, cv::Point(mb, SCALE*0.9), cv::Point(bx, by), cv::Scalar(0, 0, 255), 1);
		cv::rectangle(vessel, cv::Rect(ax - 15, ay - 15, 30, 30), cv::Scalar(0, 255, 0), 5);
		cv::rectangle(vessel, cv::Rect(bx - 15, by - 15, 30, 30), cv::Scalar(0, 255, 0), 5);
		cv::line(vessel, cv::Point(ma, SCALE*0.9), cv::Point(mb, SCALE*0.9), cv::Scalar(0, 255, 255), 5);
	}
	if (this->Flag_UseFiducialPoint){
		int ax = sin(fiducial_pan_L)*fiducial_dist_L / maxsize*SCALE + ma;
		int bx = sin(fiducial_pan_R)*fiducial_dist_R / maxsize*SCALE + mb;
		int ay = SCALE*0.9 - cos(fiducial_pan_L)*fiducial_dist_L / maxsize*SCALE;
		int by = SCALE*0.9 - cos(fiducial_pan_R)*fiducial_dist_R / maxsize*SCALE;
		cv::line(vessel, cv::Point(ma, SCALE*0.9), cv::Point(ax, ay), cv::Scalar(0, 0, 128), 1);
		cv::line(vessel, cv::Point(mb, SCALE*0.9), cv::Point(bx, by), cv::Scalar(0, 0, 128), 1);
		cv::rectangle(vessel, cv::Rect(ax - 15, ay - 15, 30, 30), cv::Scalar(0, 128, 0), 5);
		cv::rectangle(vessel, cv::Rect(bx - 15, by - 15, 30, 30), cv::Scalar(0, 128, 0), 5);
	}

	cv::Mat show, show2;
	cv::resize(resultImage_vesselbased, show, cv::Size(SCALE / 4, SCALE / 4));
	cv::resize(vessel, show2, cv::Size(SCALE / 4, SCALE / 4));
	//cv::imshow("Vessel Position", show);;
	cv::imshow("Vessel Position2", show2);
	cv::waitKey(1);
	*/
}
System::Void MainForm::vessel_pose_view2(double &vessel_angle, double &vessel_pos_x, double &vessel_pos_y){

	cv::Mat resultImage_absolute = cv::Mat::zeros(cv::Size(WIN_SIZE, WIN_SIZE), CV_8UC3);

	double distanceBetweenTargets = Convert::ToDouble(this->f_distanceBetweenTargets->Text);
	double distanceBetweenSystems = Convert::ToDouble(this->f_distanceBetweenSystems->Text);
	double distanceBetweenTargetsHalf = distanceBetweenTargets / 2;
	double distanceBetweenSystemsHalf = distanceBetweenSystems / 2;
	double pan_L = -this->pan_angle_L; // pan_angle * (-1)
	double pan_R = -this->pan_angle_R; // pan_angle * (-1)
	double dist_L = this->distance_L;
	double dist_R = this->distance_R;
	double fiducial_pan_L;
	double fiducial_pan_R;
	double fiducial_dist_L;
	double fiducial_dist_R;

	cv::Point2d midpointOfSystem;
	cv::Point2d midpointOftarget;
	cv::Point2d systemPos_L, systemPos_R;
	cv::Point2d targetPos_L, targetPos_R;
	cv::Point2d targetPos_L_predicted, targetPos_R_predicted;
	cv::Point2d systemPos_L_predicted, systemPos_R_predicted;

	cv::Point2d vesselPos;

	double targetRotation;
	double systemRotation;

	// origin point (center of coordinate system for positioning)
	cv::Point2d originPoint;
	originPoint.x = 0.0;
	originPoint.y = -1000.0;

	// installed position (displacement between center of systems and center of vessel)
	cv::Point2d installedPos;
	installedPos.x = 0;
	installedPos.y = -200.0;

	// target(template) position
	targetPos_L.x = -distanceBetweenTargetsHalf;
	targetPos_L.y = 0;
	targetPos_R.x = distanceBetweenTargetsHalf;
	targetPos_R.y = 0;
	midpointOftarget.x = 0;
	midpointOftarget.y = 0;

	// system position
	systemPos_L.x = targetPos_L.x - sin(pan_angle_L)*distance_L;
	systemPos_L.y = targetPos_L.y - cos(pan_angle_L)*distance_L;
	systemPos_R.x = targetPos_R.x - sin(pan_angle_R)*distance_R;
	systemPos_R.y = targetPos_R.y - cos(pan_angle_R)*distance_R;
	midpointOfSystem.x = (systemPos_L.x + systemPos_R.x) / 2;
	midpointOfSystem.y = (systemPos_L.y + systemPos_R.y) / 2;

	// predict system position (simply correct positional and rotational error)
	double dx = systemPos_R.x - systemPos_L.x;
	double dy = systemPos_R.y - systemPos_L.y;
	systemRotation = atan2(dy, dx);
	double cosVal = cos(systemRotation)*distanceBetweenSystemsHalf;
	double sinVal = sin(systemRotation)*distanceBetweenSystemsHalf;
	systemPos_L_predicted.x = midpointOfSystem.x - cosVal;
	systemPos_L_predicted.y = midpointOfSystem.y - sinVal;
	systemPos_R_predicted.x = midpointOfSystem.x + cosVal;
	systemPos_R_predicted.y = midpointOfSystem.y + sinVal;

	// vessel position and rotation
	double inst_x = installedPos.x*cos(systemRotation) - installedPos.y*sin(systemRotation);
	double inst_y = installedPos.x*sin(systemRotation) + installedPos.y*cos(systemRotation);
	vesselPos.x = midpointOfSystem.x - midpointOftarget.x - originPoint.x + inst_x;
	vesselPos.y = midpointOfSystem.y - midpointOftarget.y - originPoint.y + inst_y;
	vessel_angle = -systemRotation;
	vessel_pos_x = vesselPos.x;
	vessel_pos_y = vesselPos.y;

	// update output value
	this->vessel_angle_rad->Text = String::Format("{0:#0.##########}", vessel_angle);
	this->vessel_angle_deg->Text = String::Format("{0:#0.##########}", vessel_angle / M_PI*180.);
	this->vessel_pos_x->Text = String::Format("{0:#0.00}", vessel_pos_x);
	this->vessel_pos_y->Text = String::Format("{0:#0.00}", vessel_pos_y);


	// culculate size of result image
	double max_x = std::max(std::max(targetPos_R.x, systemPos_R.x), vessel_pos_x + originPoint.x);
	double min_x = std::min(std::min(targetPos_L.x, systemPos_L.x), vessel_pos_x + originPoint.x);
	double max_y = std::max(std::max(targetPos_L.y, targetPos_R.y), vessel_pos_y + originPoint.y);
	double min_y = std::min(std::min(systemPos_L.y, systemPos_R.y), vessel_pos_y + originPoint.y);
	double scale = (WIN_SIZE - WIN_MARGIN * 2) / std::max(max_x - min_x, max_y - min_y);
	cv::Point2d shift = cv::Point2d(WIN_SIZE / 2, WIN_SIZE - WIN_MARGIN);
	midpointOftarget = shift;
	
	// draw coordinate
	int line_interval = 1000 * scale;
	cv::Scalar lgray = cv::Scalar(80, 80, 80);
	cv::Scalar dgray = cv::Scalar(40, 40, 40);
	int i = 1;
	while(1){
		double y = originPoint.y*scale + shift.y - i*line_interval;
		if (y < 0){
			break;
		}
		cv::line(resultImage_absolute, cv::Point(0, y), cv::Point(WIN_SIZE, y), dgray);
		i++;
	}
	i = 1;
	while (1){
		double y = originPoint.y*scale + shift.y + i*line_interval;
		if (y > WIN_SIZE){
			break;
		}
		cv::line(resultImage_absolute, cv::Point(0, y), cv::Point(WIN_SIZE, y), dgray);
		i++;
	}
	i = 1;
	while (1){
		double x = originPoint.x*scale + shift.x - i*line_interval;
		if (x < 0){
			break;
		}
		cv::line(resultImage_absolute, cv::Point(x, 0), cv::Point(x, WIN_SIZE), dgray);
		i++;
	}
	i = 1;
	while (1){
		double x = originPoint.x*scale + shift.x + i*line_interval;
		if (x > WIN_SIZE){
			break;
		}
		cv::line(resultImage_absolute, cv::Point(x, 0), cv::Point(x, WIN_SIZE), dgray);
		i++;
	}

	cv::line(resultImage_absolute,
		cv::Point(0, originPoint.y*scale + shift.y),
		cv::Point(WIN_SIZE, originPoint.y*scale + shift.y),
		lgray);
	cv::line(resultImage_absolute,
		cv::Point(shift.x + originPoint.x*scale, 0),
		cv::Point(shift.x + originPoint.x*scale, WIN_SIZE),
		lgray);


	// draw result
	//cv::circle(resultImage_absolute, originPoint*scale + shift, 1, cv::Scalar(255, 255, 255), -1);
	cv::circle(resultImage_absolute, midpointOftarget, 5, cv::Scalar(255, 255, 255), -1);
	cv::circle(resultImage_absolute, (originPoint + vesselPos)*scale + shift, 5, cv::Scalar(255, 255, 255));

	// draw vessel
	cv::line(resultImage_absolute, systemPos_L_predicted*scale + shift, systemPos_R_predicted*scale + shift, cv::Scalar(0, 0, 255));
	cv::circle(resultImage_absolute, systemPos_L_predicted*scale + shift, 5, cv::Scalar(255, 255, 0), -1);
	cv::circle(resultImage_absolute, systemPos_R_predicted*scale + shift, 5, cv::Scalar(255, 255, 0));
	//cv::circle(resultImage_absolute, systemPos_L*scale + shift, 1, cv::Scalar(255, 255, 255));
	//cv::circle(resultImage_absolute, systemPos_R*scale + shift, 1, cv::Scalar(255, 255, 255));

	// draw target
	cv::rectangle(resultImage_absolute,
		cv::Rect(targetPos_L*scale + shift - cv::Point2d(4, 4), targetPos_L*scale + shift + cv::Point2d(4, 4)),
		cv::Scalar(255, 255, 0),
		-1);
	cv::rectangle(resultImage_absolute,
		cv::Rect(targetPos_R*scale + shift - cv::Point2d(4, 4), targetPos_R*scale + shift + cv::Point2d(4, 4)),
		cv::Scalar(255, 255, 0),
		1);

	cv::flip(resultImage_absolute, resultImage_absolute, 0);
	cv::imshow("Abusolute", resultImage_absolute);

	cv::waitKey(1);
}
//System::Void MainForm::vessel_pose_view3(double &vessel_angle, double &vessel_pos_x, double &vessel_pos_y){
//
//	cv::Mat resultImage_vesselbased = cv::Mat::zeros(cv::Size(WIN_SIZE, WIN_SIZE), CV_8UC3);
//	//cv::Mat resultImage_targetbased = cv::Mat::zeros(cv::Size(WIN_SIZE, WIN_SIZE), CV_8UC3);
//
//	double distanceBetweenTargets = Convert::ToDouble(this->f_distanceBetweenTargets->Text);
//	double distanceBetweenSystems = Convert::ToDouble(this->f_distanceBetweenSystems->Text);
//	double distanceBetweenTargetsHalf = distanceBetweenTargets / 2;
//	double distanceBetweenSystemsHalf = distanceBetweenSystems / 2;
//
//	double pan_L = -this->pan_angle_L; // pan_angle * (-1)
//	double pan_R = -this->pan_angle_R; // pan_angle * (-1)
//	double dist_L = this->distance_L;
//	double dist_R = this->distance_R;
//
//	//double fiducial_pan_L;
//	//double fiducial_pan_R;
//	//double fiducial_dist_L;
//	//double fiducial_dist_R;
//
//	cv::Point2d midpointOfSystem;
//	cv::Point2d midpointOftarget;
//	cv::Point2d systemPos_L, systemPos_R;
//	cv::Point2d targetPos_L, targetPos_R;
//	cv::Point2d targetPos_L_predicted, targetPos_R_predicted;
//
//	//cv::Point2d shift = cv::Point2d(WIN_SIZE / 2, WIN_MARGIN); // for result show
//	cv::Point2d shift = cv::Point2d(WIN_SIZE / 2, WIN_SIZE / 2); // for result show
//
//	double targetRotation;
//	double systemRotation;
//
//	// origin point (center of coordinate system for positioning)
//	cv::Point2d originPoint;
//	originPoint.x = 0.0;
//	originPoint.y = -1000.0;
//
//	// installed position (displacement between center of systems and center of vessel)
//	cv::Point2d installedPos;
//	installedPos.x = 0.0;
//	installedPos.y = -200.0;
//
//
//	// system position
//	systemPos_L.x = -distanceBetweenSystemsHalf;
//	systemPos_L.y = 0;
//	systemPos_R.x = distanceBetweenSystemsHalf;
//	systemPos_R.y = 0;
//	midpointOfSystem.x = 0;
//	midpointOfSystem.y = 0;
//
//	// target position
//	targetPos_L.x = systemPos_L.x + sin(pan_angle_L)*distance_L;
//	targetPos_L.y = systemPos_L.y + cos(pan_angle_L)*distance_L;
//	targetPos_R.x = systemPos_R.x + sin(pan_angle_R)*distance_R;
//	targetPos_R.y = systemPos_R.y + cos(pan_angle_R)*distance_R;
//	midpointOftarget.x = (targetPos_L.x + targetPos_R.x) / 2;
//	midpointOftarget.y = (targetPos_L.y + targetPos_R.y) / 2;
//
//	// predict target position (simply correct positional and rotational error)
//	double dx = targetPos_L.x - targetPos_R.x;
//	double dy = targetPos_L.y - targetPos_R.y;
//	targetRotation = atan2(dy, dx);
//	double cosVal = cos(targetRotation);
//	double sinVal = sin(targetRotation);
//	targetPos_L_predicted.x = midpointOftarget.x - cosVal*distanceBetweenTargetsHalf;
//	targetPos_L_predicted.y = midpointOftarget.y - sinVal*distanceBetweenTargetsHalf;
//	targetPos_R_predicted.x = midpointOftarget.x + cosVal*distanceBetweenTargetsHalf;
//	targetPos_R_predicted.y = midpointOftarget.y + sinVal*distanceBetweenTargetsHalf;
//
//	// culculate relative position of origin point
//	originPoint.x = originPoint.x*cos(targetRotation) - originPoint.y*sin(targetRotation);
//	originPoint.y = originPoint.x*sin(targetRotation) + originPoint.y*cos(targetRotation);
//
//	systemRotation = -targetRotation;
//
//	// vessel position and rotation
//
//
//
//	vessel_angle = systemRotation;
//	vessel_pos_x = cos(targetRotation)*cv::norm(midpointOftarget - midpointOfSystem); // *** wrong equation
//	vessel_pos_y = sin(targetRotation)*cv::norm(midpointOftarget - midpointOfSystem); // *** wrong equation
//
//
//	// transform each point
//	//targetPos_L_predicted -= midpointOftarget;
//	//targetPos_R_predicted -= midpointOftarget;
//	//systemPos_L -= midpointOftarget;
//	//systemPos_R -= midpointOftarget;
//	midpointOfSystem = (systemPos_R + systemPos_L)*0.5;
//
//	//midpointOfSystem.x = midpointOfSystem.x * cos(targetRotation) - midpointOfSystem.y * sin(targetRotation);
//	//midpointOfSystem.y = midpointOfSystem.x * sin(targetRotation) + midpointOfSystem.y * cos(targetRotation);
//
//	//targetPos_L_predicted.x = targetPos_L_predicted.x * cos(targetRotation) - targetPos_L_predicted.y * sin(targetRotation);
//	//targetPos_L_predicted.y = targetPos_L_predicted.x * sin(targetRotation) + targetPos_L_predicted.y * cos(targetRotation);
//	//targetPos_R_predicted.x = targetPos_R_predicted.x * cos(targetRotation) - targetPos_R_predicted.y * sin(targetRotation);
//	//targetPos_R_predicted.y = targetPos_R_predicted.x * sin(targetRotation) + targetPos_R_predicted.y * cos(targetRotation);
//
//	//cv::Mat InvertMat = (cv::Mat_<double>(2, 2) << cos(targetRotation), -sin(targetRotation), cos(targetRotation), sin(targetRotation));
//	//InvertMat = InvertMat.inv();
//
//	//systemPos_L.x = systemPos_L.x * InvertMat.at<double>(0, 0) + systemPos_L.y * InvertMat.at<double>(0, 1);
//	//systemPos_L.y = systemPos_L.x * InvertMat.at<double>(1, 0) + systemPos_L.y * InvertMat.at<double>(1, 1);
//	//systemPos_R.x = systemPos_R.x * InvertMat.at<double>(0, 0) + systemPos_R.y * InvertMat.at<double>(0, 1);
//	//systemPos_R.y = systemPos_R.x * InvertMat.at<double>(1, 0) + systemPos_R.y * InvertMat.at<double>(1, 1);
//
//	//systemPos_L.x = systemPos_L.x * cos(targetRotation) - systemPos_L.y * sin(targetRotation);
//	//systemPos_L.y = systemPos_L.x * sin(targetRotation) + systemPos_L.y * cos(targetRotation);
//	//systemPos_R.x = systemPos_R.x * cos(targetRotation) - systemPos_R.y * sin(targetRotation);
//	//systemPos_R.y = systemPos_R.x * sin(targetRotation) + systemPos_R.y * cos(targetRotation);
//
//
//	midpointOftarget = (targetPos_R_predicted + targetPos_L_predicted)*0.5;
//
//	std::cout << systemPos_L << systemPos_R << std::endl;
//
//
//	// update output value
//	this->vessel_angle_rad->Text = String::Format("{0:#0.##########}", vessel_angle);
//	this->vessel_angle_deg->Text = String::Format("{0:#0.##########}", vessel_angle / M_PI*180.);
//	this->vessel_pos_x->Text = String::Format("{0:#0.00}", vessel_pos_x);
//	this->vessel_pos_y->Text = String::Format("{0:#0.00}", vessel_pos_y);
//
//
//
//
//	// 
//	double x_size = std::max(targetPos_R_predicted.x, systemPos_R.x) - std::min(targetPos_L_predicted.x, systemPos_L.x);
//	//double y_size = std::max(targetPos_L_predicted.y, targetPos_R_predicted.y) - std::min(systemPos_L.y, systemPos_R.y);
//	double y_size = std::max(systemPos_L.y, systemPos_R.y) - std::min(targetPos_L_predicted.y, targetPos_R_predicted.y);
//	//double scale = (WIN_SIZE - WIN_MARGIN * 2) / std::max(x_size, y_size);
//	double scale = 0.02;
//
//
//
//	// draw coordinate
//	//int line_interval = 1000 * scale;
//	//int itr_x_begin = WIN_MARGIN / (1000 * scale);
//	//int itr_x_end = (WIN_SIZE - WIN_MARGIN) / (1000 * scale);
//	//int itr_y = WIN_SIZE / (1000 * scale) / 2;
//	//cv::Scalar lgray = cv::Scalar(80, 80, 80);
//	//cv::Scalar dgray = cv::Scalar(40, 40, 40);
//	//for (int i = -itr_x_begin; i < itr_x_end + 1; i++){
//	//	cv::line(resultImage_vesselbased,
//	//		cv::Point(0, WIN_MARGIN + i*line_interval),
//	//		cv::Point(WIN_SIZE, WIN_MARGIN + i*line_interval),
//	//		dgray);
//	//}
//	//for (int i = -itr_y; i < itr_y + 1; i++){
//	//	cv::line(resultImage_vesselbased,
//	//		cv::Point(WIN_SIZE / 2 + i*itr_y*line_interval, 0),
//	//		cv::Point(WIN_SIZE / 2 + i*itr_y*line_interval, WIN_SIZE),
//	//		dgray);
//	//}
//
//	// draw coordinate
//	//int line_interval = 1000 * scale;
//	//cv::Scalar lgray = cv::Scalar(80, 80, 80);
//	//cv::Scalar dgray = cv::Scalar(40, 40, 40);
//
//	//double diff_x = midpointOftarget.x - originPoint.x;
//	//double diff_y = midpointOftarget.y - originPoint.y;
//
//	//int i = 1;
//	//while (1){
//	//	double y = diff_y*scale + shift.y - i*line_interval;
//	//	double y_left = y + originPoint.x*sinVal;
//	//	double y_right = y - (WIN_SIZE - originPoint.x)*sinVal;
//	//	if (y_left < 0 && y_right < 0){
//	//		break;
//	//	}
//	//	cv::line(resultImage_vesselbased, cv::Point(0, y_left), cv::Point(WIN_SIZE, y_right), dgray);
//	//	i++;
//	//}
//	//i = 1;
//	//while (1){
//	//	double y = diff_y*scale + shift.y + i*line_interval;
//	//	double y_left = y + originPoint.x*sinVal;
//	//	double y_right = y - (WIN_SIZE - originPoint.x)*sinVal;
//	//	if (y_left > WIN_SIZE && y_right > WIN_SIZE){
//	//		break;
//	//	}
//	//	cv::line(resultImage_vesselbased, cv::Point(0, y_left), cv::Point(WIN_SIZE, y_right), dgray);
//	//	i++;
//	//}
//	//i = 1;
//	//while (1){
//	//	double x = diff_x*scale + shift.x - i*line_interval;
//	//	double x_left = x - originPoint.x*sinVal;
//	//	double x_right = x + (WIN_SIZE - originPoint.x)*sinVal;
//	//	if (x_left < 0 && x_right < 0){
//	//		break;
//	//	}
//	//	cv::line(resultImage_vesselbased, cv::Point(x_left, 0), cv::Point(x_right, WIN_SIZE), dgray);
//	//	i++;
//	//}
//	//i = 1;
//	//while (1){
//	//	double x = diff_x*scale + shift.x + i*line_interval;
//	//	double x_left = x - originPoint.x*sinVal;
//	//	double x_right = x + (WIN_SIZE - originPoint.x)*sinVal;
//	//	if (x_left > WIN_SIZE && x_right > WIN_SIZE){
//	//		break;
//	//	}
//	//	cv::line(resultImage_vesselbased, cv::Point(x_left, 0), cv::Point(x_right, WIN_SIZE), dgray);
//	//	i++;
//	//}
//
//	//cv::line(resultImage_vesselbased,
//	//	cv::Point(0, diff_y*scale + shift.y + originPoint.x*sinVal),
//	//	cv::Point(WIN_SIZE, diff_y*scale + shift.y - (WIN_SIZE - originPoint.x)*sinVal),
//	//	lgray);
//
//	//cv::line(resultImage_vesselbased,
//	//	cv::Point(diff_x*scale + shift.x - originPoint.x*sinVal, 0),
//	//	cv::Point(diff_x*scale + shift.x + (WIN_SIZE - originPoint.x)*sinVal, WIN_SIZE),
//	//	lgray);
//
//	//cv::line(resultImage_vesselbased,
//	//	cv::Point(diff_x*scale + shift.x - originPoint.x*sinVal, 0),
//	//	cv::Point(diff_x*scale + shift.x + (WIN_SIZE - originPoint.x)*sinVal, WIN_SIZE),
//	//	lgray);
//
//
//
//
//
//	// draw result
//	//cv::circle(resultImage_vesselbased, (midpointOftarget - originPoint)*scale + shift, 1, cv::Scalar(255, 255, 255), -1);
//	cv::line(resultImage_vesselbased, midpointOfSystem*scale + shift, midpointOftarget*scale + shift, cv::Scalar(255, 255, 255));
//	//cv::circle(resultImage_vesselbased, shift, 5, cv::Scalar(255, 255, 255), -1);
//	cv::circle(resultImage_vesselbased, midpointOftarget*scale + shift, 5, cv::Scalar(255, 255, 255));
//
//	// draw vessel
//	cv::line(resultImage_vesselbased, systemPos_L*scale + shift, systemPos_R*scale + shift, cv::Scalar(0, 0, 255));
//	cv::circle(resultImage_vesselbased, systemPos_L*scale + shift, 5, cv::Scalar(255, 255, 0),-1);
//	//cv::circle(resultImage_vesselbased, systemPos_R*scale + shift, 5, cv::Scalar(255, 255, 0));
//
//	// draw target
//	cv::line(resultImage_vesselbased, targetPos_L_predicted*scale + shift, targetPos_R_predicted*scale + shift, cv::Scalar(0, 255, 0));
//	cv::circle(resultImage_vesselbased, targetPos_L_predicted*scale + shift, 5, cv::Scalar(255, 255, 0), -1);
//	cv::circle(resultImage_vesselbased, targetPos_R_predicted*scale + shift, 5, cv::Scalar(255, 255, 0));
//
//	//cv::flip(resultImage_vesselbased, resultImage_vesselbased, 0);
//	cv::imshow("Absolute", resultImage_vesselbased);
//	//cv::imshow("result", resultImage_targetbased);
//	cv::waitKey(1);
//
//}
System::Void MainForm::vessel_pose_view3(double &vessel_angle, double &vessel_pos_x, double &vessel_pos_y){

	try{
		cv::Mat resultImage_vesselbased = cv::Mat::zeros(cv::Size(WIN_SIZE, WIN_SIZE), CV_8UC3);
		//cv::Mat resultImage_targetbased = cv::Mat::zeros(cv::Size(WIN_SIZE, WIN_SIZE), CV_8UC3);

		double distanceBetweenTargets = Convert::ToDouble(this->f_distanceBetweenTargets->Text);
		double distanceBetweenSystems = Convert::ToDouble(this->f_distanceBetweenSystems->Text);
		double distanceBetweenTargetsHalf = distanceBetweenTargets / 2;
		double distanceBetweenSystemsHalf = distanceBetweenSystems / 2;
		double pan_L = this->pan_angle_L + Convert::ToDouble(this->offset_angle_left->Text) / 180.*CV_PI; // pan_angle * (-1)
		//std::cout << Convert::ToDouble(this->offset_angle_left->Text)<< std::endl;
		double pan_R = this->pan_angle_R + Convert::ToDouble(this->offset_angle_right->Text) / 180.*CV_PI; // pan_angle * (-1)
		double dist_L = this->distance_L;
		double dist_R = this->distance_R;
		double fiducial_pan_L;
		double fiducial_pan_R;
		double fiducial_dist_L;
		double fiducial_dist_R;

		cv::Point2d midpointOfSystem;
		cv::Point2d midpointOftarget;
		cv::Point2d systemPos_L, systemPos_R;
		cv::Point2d targetPos_L, targetPos_R;
		cv::Point2d targetPos_L_predicted, targetPos_R_predicted;

		double targetRotation;
		double systemRotation;

		// origin point (center of coordinate system for positioning)
		cv::Point2d originPoint;
		try{
			originPoint.x = Convert::ToDouble(this->shift_pos_x->Text);
			originPoint.y = Convert::ToDouble(this->shift_pos_y->Text);
		}
		catch (FormatException ^ex){
			originPoint.x = 0;
			originPoint.y = 0;
		}

		// installed position (displacement between center of systems and center of vessel)
		cv::Point2d installedPos;
		try{
			installedPos.x = Convert::ToDouble(this->inst_pos_x->Text);
			installedPos.y = Convert::ToDouble(this->inst_pos_y->Text);
		}
		catch (FormatException ^ex){
			installedPos.x = 0;
			installedPos.y = 0;
		}

		// system position
		systemPos_L.x = -distanceBetweenSystemsHalf;
		systemPos_L.y = 0;
		systemPos_R.x = distanceBetweenSystemsHalf;
		systemPos_R.y = 0;
		midpointOfSystem.x = 0;
		midpointOfSystem.y = 0;

		// target position
		targetPos_L.x = systemPos_L.x + sin(pan_L)*distance_L;
		targetPos_L.y = systemPos_L.y + cos(pan_L)*distance_L;
		targetPos_R.x = systemPos_R.x + sin(pan_R)*distance_R;
		targetPos_R.y = systemPos_R.y + cos(pan_R)*distance_R;
		midpointOftarget.x = (targetPos_L.x + targetPos_R.x) / 2;
		midpointOftarget.y = (targetPos_L.y + targetPos_R.y) / 2;

		// predict target position (simply correct positional and rotational error)
		double dx = targetPos_R.x - targetPos_L.x;
		double dy = targetPos_R.y - targetPos_L.y;
		targetRotation = atan2(dy, dx);
		double cosVal = cos(targetRotation);
		double sinVal = sin(targetRotation);
		targetPos_L_predicted.x = midpointOftarget.x - cosVal*distanceBetweenTargetsHalf;
		targetPos_L_predicted.y = midpointOftarget.y - sinVal*distanceBetweenTargetsHalf;
		targetPos_R_predicted.x = midpointOftarget.x + cosVal*distanceBetweenTargetsHalf;
		targetPos_R_predicted.y = midpointOftarget.y + sinVal*distanceBetweenTargetsHalf;

		//// culculate relative position of origin point
		//originPoint.x = originPoint.x*cos(targetRotation) - originPoint.y*sin(targetRotation);
		//originPoint.y = originPoint.x*sin(targetRotation) + originPoint.y*cos(targetRotation);

		systemRotation = -targetRotation;

		targetPos_L_predicted -= midpointOftarget;
		targetPos_R_predicted -= midpointOftarget;
		systemPos_L -= midpointOftarget;
		systemPos_R -= midpointOftarget;

		targetPos_L_predicted.x = targetPos_L_predicted.x*cos(-targetRotation) - targetPos_L_predicted.y*sin(-targetRotation);
		targetPos_L_predicted.y = targetPos_L_predicted.x*sin(-targetRotation) + targetPos_L_predicted.y*cos(-targetRotation);
		targetPos_R_predicted.x = targetPos_R_predicted.x*cos(-targetRotation) - targetPos_R_predicted.y*sin(-targetRotation);
		targetPos_R_predicted.y = targetPos_R_predicted.x*sin(-targetRotation) + targetPos_R_predicted.y*cos(-targetRotation);

		systemPos_L.x = systemPos_L.x*cos(-targetRotation) - systemPos_L.y*sin(-targetRotation);
		systemPos_L.y = systemPos_L.x*sin(-targetRotation) + systemPos_L.y*cos(-targetRotation);
		systemPos_R.x = systemPos_R.x*cos(-targetRotation) - systemPos_R.y*sin(-targetRotation);
		systemPos_R.y = systemPos_R.x*sin(-targetRotation) + systemPos_R.y*cos(-targetRotation);

		midpointOftarget = (targetPos_L_predicted + targetPos_R_predicted)*0.5;
		midpointOfSystem = (systemPos_L + systemPos_R)*0.5;


		// vessel position and rotation
		dx = systemPos_R.x - systemPos_L.x;
		dy = systemPos_R.y - systemPos_L.y;
		vessel_angle = -atan2(dy, dx);
		vessel_pos_x = midpointOfSystem.x;
		vessel_pos_y = midpointOfSystem.y;

		// update output value
		this->vessel_rad->Text = String::Format("{0:#0.0000}", vessel_angle);
		this->vessel_deg->Text = String::Format("{0:#0.0000}", vessel_angle / M_PI*180.);
		this->vessel_x->Text = String::Format("{0:#0.00}", vessel_pos_x);
		this->vessel_y->Text = String::Format("{0:#0.00}", vessel_pos_y);

		// 
		double x_min = std::min(std::min(std::min(targetPos_L_predicted.x, targetPos_R_predicted.x), systemPos_L.x), systemPos_R.x);
		double x_max = std::max(std::max(std::max(targetPos_L_predicted.x, targetPos_R_predicted.x), systemPos_L.x), systemPos_R.x);
		double y_max = std::max(std::max(std::max(targetPos_L_predicted.y, targetPos_R_predicted.y), systemPos_L.y), systemPos_R.y);
		double y_min = std::min(std::min(std::min(targetPos_L_predicted.y, targetPos_R_predicted.y), systemPos_L.y), systemPos_R.y);
		double x_size = x_max - x_min;
		double y_size = y_max - y_min;
		double scale = (WIN_SIZE - WIN_MARGIN * 2) / std::max(x_size, y_size);


		// draw coordinate
		//cv::Point2d shift = cv::Point2d(WIN_SIZE / 2, WIN_MARGIN);
		cv::Point2d shift = cv::Point2d(WIN_SIZE / 2, WIN_SIZE - WIN_MARGIN);
		int line_interval = 1000 * scale;
		cv::Scalar lgray = cv::Scalar(80, 80, 80);
		cv::Scalar dgray = cv::Scalar(40, 40, 40);

		double diff_x = midpointOftarget.x - originPoint.x;
		double diff_y = midpointOftarget.y - originPoint.y;

		int i = 1;
		while (1){
			double y = originPoint.y*scale + shift.y - i*line_interval;
			if (y < 0){
				break;
			}
			cv::line(resultImage_vesselbased, cv::Point(0, y), cv::Point(WIN_SIZE, y), dgray);
			i++;
		}
		i = 1;
		while (1){
			double y = originPoint.y*scale + shift.y + i*line_interval;
			if (y > WIN_SIZE){
				break;
			}
			cv::line(resultImage_vesselbased, cv::Point(0, y), cv::Point(WIN_SIZE, y), dgray);
			i++;
		}
		i = 1;
		while (1){
			double x = originPoint.x*scale + shift.x - i*line_interval;
			if (x < 0){
				break;
			}
			cv::line(resultImage_vesselbased, cv::Point(x, 0), cv::Point(x, WIN_SIZE), dgray);
			i++;
		}
		i = 1;
		while (1){
			double x = originPoint.x*scale + shift.x + i*line_interval;
			if (x > WIN_SIZE){
				break;
			}
			cv::line(resultImage_vesselbased, cv::Point(x, 0), cv::Point(x, WIN_SIZE), dgray);
			i++;
		}

		cv::line(resultImage_vesselbased,
			cv::Point(0, originPoint.y*scale + shift.y),
			cv::Point(WIN_SIZE, originPoint.y*scale + shift.y),
			lgray);
		cv::line(resultImage_vesselbased,
			cv::Point(originPoint.x*scale + shift.x, 0),
			cv::Point(originPoint.x*scale + shift.x, WIN_SIZE),
			lgray);

		cv::circle(resultImage_vesselbased, originPoint*scale + shift, 0, cv::Scalar(255, 255, 255), -1);


		// draw result
		//cv::circle(resultImage_vesselbased, (midpointOftarget - originPoint)*scale + shift, 1, cv::Scalar(255, 255, 255), -1);
		//cv::line(resultImage_vesselbased, shift, midpointOftarget*scale + shift, cv::Scalar(255, 255, 255));
		cv::circle(resultImage_vesselbased, midpointOfSystem*scale + shift, 5, cv::Scalar(255, 255, 255), -1);
		cv::circle(resultImage_vesselbased, midpointOftarget*scale + shift, 5, cv::Scalar(255, 255, 255));

		// draw vessel
		cv::line(resultImage_vesselbased, systemPos_L*scale + shift, systemPos_R*scale + shift, cv::Scalar(0, 0, 255));
		cv::circle(resultImage_vesselbased, systemPos_L*scale + shift, 5, cv::Scalar(255, 255, 0), -1);
		cv::circle(resultImage_vesselbased, systemPos_R*scale + shift, 5, cv::Scalar(255, 255, 0));

		// draw target
		cv::line(resultImage_vesselbased, targetPos_L_predicted*scale + shift, targetPos_R_predicted*scale + shift, cv::Scalar(0, 255, 0));
		cv::circle(resultImage_vesselbased, targetPos_L_predicted*scale + shift, 5, cv::Scalar(255, 255, 0), -1);
		cv::circle(resultImage_vesselbased, targetPos_R_predicted*scale + shift, 5, cv::Scalar(255, 255, 0));

		cv::flip(resultImage_vesselbased, resultImage_vesselbased, 0);
		cv::imshow("Absolute", resultImage_vesselbased);
		//cv::imshow("result", resultImage_targetbased);
		cv::waitKey(1);
	}
	catch (FormatException ^ex){}
}

void MainForm::outTimeFile(long time){
	std::ofstream ofs("C:\\Users\\Admin\\Desktop\\PKNU_data\\time.dat");
	ofs << time << std::endl;
	return;
}