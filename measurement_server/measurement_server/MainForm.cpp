#include "MainForm.h"
#include "global.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define SCALE 1000

using namespace measurement_server;

System::Void MainForm::vessel_pose_view(double &common_angle, double &common_x, double &common_y, double &relative_angle, double &relative_x, double &relative_y){
	double targetLength;
	double measureLength;
	double aPan, bPan;
	double aDist, bDist;
	double _aPan, _bPan;
	double _aDist, _bDist;
	
	targetLength = Convert::ToDouble(this->targets_distance->Text);
	measureLength = Convert::ToDouble(this->measures_distance->Text);
	aPan = this->a_pan_angle;
	bPan = this->b_pan_angle;
	aDist = this->a_distance;
	bDist = this->b_distance;
	double widthAlpha = fabs(aDist*sin(aPan)) + fabs(bDist*sin(bPan));


	double maxsize = (std::max)((std::max)(aDist, bDist), (std::max)(targetLength + widthAlpha, measureLength + widthAlpha)) * 1.2;
	if (this->basisFlag){
		_aPan = this->basis_a_pan_angle;
		_bPan = this->basis_b_pan_angle;
		_aDist = this->basis_a_distance;
		_bDist = this->basis_b_distance;
		double _widthAlpha = fabs(_aDist*sin(_aPan)) + fabs(_bDist*sin(_bPan));
		double _maxsize = (std::max)((std::max)(_aDist, _bDist), (std::max)(targetLength + _widthAlpha, measureLength + _widthAlpha)) * 1.2;
		maxsize = (std::max)(maxsize, _maxsize);
	}

	cv::Mat viewImage = cv::Mat::zeros(cv::Size(SCALE, SCALE), CV_8UC3);
	int ta = SCALE / 2. - targetLength / maxsize*SCALE / 2.;
	int tb = SCALE / 2. + targetLength / maxsize*SCALE / 2.;
	cv::rectangle(viewImage, cv::Rect(ta - 15, SCALE*0.1-15, 30, 30), cv::Scalar(0, 255, 0), 5);
	cv::rectangle(viewImage, cv::Rect(tb - 15, SCALE*0.1 - 15, 30, 30), cv::Scalar(0, 255, 0), 5);
	double measure_a_x = -1 * sin(aPan)*aDist - targetLength / 2.;
	double measure_a_y = cos(aPan)*aDist;
	double measure_b_x = -1 * sin(bPan)*bDist + targetLength / 2.;
	double measure_b_y = cos(bPan)*bDist;
	double vessel_angle = atan( (measure_a_y - measure_b_y)/(measure_a_x - measure_b_x));
	common_angle = vessel_angle;
	common_x = (measure_a_x - measure_b_x) / 2.;
	common_y = (measure_a_y - measure_b_y) / 2.;
	this->vessel_angle_rad->Text = String::Format("{0:#0.##########}", vessel_angle);
	this->vessel_angle_deg->Text = String::Format("{0:#0.##########}", vessel_angle / M_PI*180.);
	this->vessel_pos_x->Text = String::Format("{0:#0.00}", (measure_a_x - measure_b_x) / 2.);
	this->vessel_pos_y->Text = String::Format("{0:#0.00}", (measure_a_y - measure_b_y) / 2.);
	if (this->basisFlag){
		double _measure_a_x = -1 * sin(_aPan)*_aDist - targetLength / 2.;
		double _measure_a_y = cos(_aPan)*_aDist;
		double _measure_b_x = -1 * sin(_bPan)*_bDist - targetLength / 2.;
		double _measure_b_y = cos(_bPan)*_bDist;
		double _vessel_angle = atan((_measure_a_y - _measure_b_y)/(_measure_a_x - _measure_b_x));
		this->rela_angle_rad->Text = String::Format("{0:#0.##########}", vessel_angle-_vessel_angle);
		this->rela_angle_deg->Text = String::Format("{0:#0.##########}", (vessel_angle - _vessel_angle) / M_PI*180.);
		this->rela_pos_x->Text = String::Format("{0:#0.00}", (measure_a_x - measure_b_x) / 2. - (_measure_a_x - _measure_b_x) / 2.);
		this->rela_pos_y->Text = String::Format("{0:#0.00}", (measure_a_y - measure_b_y) / 2. - (_measure_a_y - _measure_b_y) / 2.);
		relative_angle = vessel_angle - _vessel_angle;
		relative_x = (measure_a_x - measure_b_x) / 2. - (_measure_a_x - _measure_b_x) / 2.;
		relative_y = (measure_a_y - measure_b_y) / 2. - (_measure_a_y - _measure_b_y) / 2.;
	}
	else {
		relative_angle = 0;
		relative_x = 0;
		relative_y = 0;
	}
	if(this->basisFlag){
		int ax = -1 * sin(_aPan)*_aDist / maxsize*SCALE + ta;
		int ay = cos(_aPan)*_aDist / maxsize*SCALE + SCALE*0.1;
		cv::line(viewImage, cv::Point(ta, SCALE*0.1), cv::Point(ax, ay), cv::Scalar(0, 0, 128), 1);
		int bx = -1 * sin(_bPan)*_bDist / maxsize*SCALE + tb;
		int by = cos(_bPan)*_bDist / maxsize*SCALE + SCALE*0.1;
		cv::line(viewImage, cv::Point(tb, SCALE*0.1), cv::Point(bx, by), cv::Scalar(0, 0, 128), 1);
		cv::circle(viewImage, cv::Point(ax, ay), 15, cv::Scalar(128, 128, 0), 5);
		cv::circle(viewImage, cv::Point(bx, by), 15, cv::Scalar(128, 128, 0), 5);
		cv::line(viewImage, cv::Point(ax, ay), cv::Point(bx, by), cv::Scalar(0, 128, 128), 5);
	}
	{
		int ax = -1 * sin(aPan)*aDist / maxsize*SCALE + ta;
		int ay = cos(aPan)*aDist / maxsize*SCALE + SCALE*0.1;
		cv::line(viewImage, cv::Point(ta, SCALE*0.1), cv::Point(ax, ay), cv::Scalar(0, 0, 255), 1);
		int bx = -1 * sin(bPan)*bDist / maxsize*SCALE + tb;
		int by = cos(bPan)*bDist / maxsize*SCALE + SCALE*0.1;
		cv::line(viewImage, cv::Point(tb, SCALE*0.1), cv::Point(bx, by), cv::Scalar(0, 0, 255), 1);
		cv::circle(viewImage, cv::Point(ax, ay), 15, cv::Scalar(255, 255, 0), 5);
		cv::circle(viewImage, cv::Point(bx, by), 15, cv::Scalar(255, 255, 0), 5);
		cv::line(viewImage, cv::Point(ax, ay), cv::Point(bx, by), cv::Scalar(0, 255, 255), 5);
	}

	cv::Mat vessel = cv::Mat::zeros(SCALE, SCALE, CV_8UC3);
	double measuredis = Convert::ToDouble(this->measures_distance->Text);
	int ma = SCALE / 2. - measuredis / maxsize*SCALE / 2.;
	int mb = SCALE / 2. + measuredis / maxsize*SCALE / 2.;
	cv::circle(vessel, cv::Point(ma, SCALE*0.9), 15, cv::Scalar(255, 255, 0), 5);
	cv::circle(vessel, cv::Point(mb, SCALE*0.9), 15, cv::Scalar(255, 255, 0), 5);
	{
		int ax = sin(aPan)*aDist / maxsize*SCALE + ma;
		int bx = sin(bPan)*bDist / maxsize*SCALE + mb;
		int ay = SCALE*0.9 - cos(aPan)*aDist / maxsize*SCALE;
		int by = SCALE*0.9 - cos(bPan)*bDist / maxsize*SCALE;
		cv::line(vessel, cv::Point(ma, SCALE*0.9), cv::Point(ax, ay), cv::Scalar(0, 0, 255), 1);
		cv::line(vessel, cv::Point(mb, SCALE*0.9), cv::Point(bx, by), cv::Scalar(0, 0, 255), 1);
		cv::rectangle(vessel, cv::Rect(ax - 15, ay - 15, 30, 30), cv::Scalar(0, 255, 0), 5);
		cv::rectangle(vessel, cv::Rect(bx - 15, by - 15, 30, 30), cv::Scalar(0, 255, 0), 5);
		cv::line(vessel, cv::Point(ma, SCALE*0.9), cv::Point(mb, SCALE*0.9), cv::Scalar(0, 255, 255), 5);

	}
	if (this->basisFlag){

		int ax = sin(_aPan)*_aDist / maxsize*SCALE + ma;
		int bx = sin(_bPan)*_bDist / maxsize*SCALE + mb;
		int ay = SCALE*0.9 - cos(_aPan)*_aDist / maxsize*SCALE;
		int by = SCALE*0.9 - cos(_bPan)*_bDist / maxsize*SCALE;
		cv::line(vessel, cv::Point(ma, SCALE*0.9), cv::Point(ax, ay), cv::Scalar(0, 0, 128), 1);
		cv::line(vessel, cv::Point(mb, SCALE*0.9), cv::Point(bx, by), cv::Scalar(0, 0, 128), 1);
		cv::rectangle(vessel, cv::Rect(ax - 15, ay - 15, 30, 30), cv::Scalar(0, 128, 0), 5);
		cv::rectangle(vessel, cv::Rect(bx - 15, by - 15, 30, 30), cv::Scalar(0, 128, 0), 5);
	}



	cv::Mat show, show2;
	cv::resize(viewImage, show, cv::Size(SCALE / 4, SCALE / 4));
	cv::resize(vessel, show2, cv::Size(SCALE / 4, SCALE / 4));
	//cv::imshow("Vessel Position", show);;
	cv::imshow("Vessel Position2", show2);
	cv::waitKey(1);
}
void MainForm::outTimeFile(long time){
	std::ofstream ofs("C:\\Users\\Admin\\Desktop\\PKNU_data\\time.dat");
	ofs << time << std::endl;
	return;
}