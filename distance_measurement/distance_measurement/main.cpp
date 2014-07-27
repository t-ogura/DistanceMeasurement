
#include <iostream>
#include <fstream>

#include "measurement.h"
#include "view.h"
#include "form_connection.h"

#include <winbase.h>
#include <chrono>

#define MAIN_PIXEL_SIZE       0.0075
#define MAIN_FOCAL_LENGTH     16.0
#define MAIN_BASELINE_LENGTH  220
#define MAIN_CENTER_CAMERA_FOCAL_LENGTH     8.0
#define USE_CENTER_CAMERA true
#define OUTPUT_FILENAME "param_files/send.param"
#define INPUT_FILENAME "param_files/receive.param"
#define CENTER_OUTPUT_FILENAME "param_files/center_send.param"
#define CENTER_INPUT_FILENAME "param_files/center_receive.param"
#define PLATFORMCONTROLLER_OUTPUT_FILENAME "param_files/pc_send.param"
#define PLATFORMCONTROLLER_INPUT_FILENAME "param_files/pc_receive.param"
#define QUIT_FILENAME "param_files/quit.param"


std::string GNUPLOT_PATH = "C:\\gnuplot\\bin\\gnuplot.exe";	// pgnuplotの場所

int frame = 0;
std::mutex mtx;
bool gnuLoop = true;

std::list<double> frame_list;
std::list<double> origin_list;
std::list<double> dist_list;
std::list<double> kf_list;

int gnuplot(){
	FILE *gnu;

	if ((gnu = _popen(GNUPLOT_PATH.c_str(), "w")) == NULL) {
		printf("gnuplot open error!!\n");
		exit(EXIT_FAILURE);	// エラーの場合は通常、異常終了する
	}
	//fprintf(gnu, "set size square\n");		// figureを正方形に
	fprintf(gnu, "unset key\n");		// 凡例を表示しない
	std::ofstream plot("plot.dat");
	int prev_frame = 0;

	while (gnuLoop){
		cv::waitKey(100);
		mtx.lock();
		std::list<double> frame_list_copy(frame_list);
		std::list<double> origin_list_copy(origin_list);
		std::list<double> dist_list_copy(dist_list);
		std::list<double> kf_list_copy(kf_list);
		mtx.unlock();
		std::list<double>::iterator frame_it = frame_list_copy.begin();
		std::list<double>::iterator origin_it = origin_list_copy.begin();
		std::list<double>::iterator dist_it = dist_list_copy.begin();
		std::list<double>::iterator kf_it = kf_list_copy.begin();
		if (frame == prev_frame) continue;

		std::ofstream plot("plot.dat");
		while (frame_it != frame_list_copy.end() || origin_it != origin_list_copy.end() || dist_it != dist_list_copy.end() || kf_it != kf_list_copy.end()){
			plot << *(frame_it++) << " " << *(origin_it++) << " " << *(dist_it++) << " " << *(kf_it++) << std::endl;
		}
		fprintf(gnu, "set title 'frame = %d'\n", frame); // タイトルを設定
		fprintf(gnu, "plot [%d:%d][%lf:%lf] 'plot.dat' u 1:2 w l,\'plot.dat' u 1:3 w l ,\'plot.dat' u 1:4 w l \n", frame - 500, frame, *(--kf_it) - 500, *(--kf_it) + 500);	// gnuplotで点を描く
		fflush(gnu);	// バッファに格納されているデータを吐き出す（必須）
		plot.close();
		prev_frame = *(frame_list.end());
	}
	fprintf(gnu, "exit\n"); // gnuplotの終了
	fflush(gnu); // バッファに格納されているデータを吐き出す（必須）
	return 0;
}


int main(){
	Measurement measurement(MAIN_PIXEL_SIZE, MAIN_FOCAL_LENGTH, MAIN_BASELINE_LENGTH, 12, USE_CENTER_CAMERA, MAIN_CENTER_CAMERA_FOCAL_LENGTH);
	View view_L("LEFT", 320, 400);
	View view_R("RIGHT", 670, 400);
	View *view_C;
	if (USE_CENTER_CAMERA) view_C = new View("CENTER", 515, 100);
	FormConnection connect; 
	char *cstr = new char[measurement.platform_comnumber.length() + 1];
	strcpy(cstr, measurement.platform_comnumber.c_str());
	std::cout << "com port [" << cstr << "]" << std::endl;
	measurement.threadTracking(cstr, 9600);

	std::thread gnu_thread(gnuplot);

	while (1){
		const auto start = std::chrono::system_clock::now();
		mtx.lock();
		if (frame > 0){
			if (origin_list.size() > 500){
				frame_list.pop_front();
				origin_list.pop_front();
				dist_list.pop_front();
				kf_list.pop_front();
			}
			frame_list.push_back(frame);
			origin_list.push_back(measurement.non_offset.original);
			dist_list.push_back(measurement.distance.original);
			kf_list.push_back(measurement.distance.kf);
		}
		frame++;
		mtx.unlock();

		int key = cv::waitKey(1);
		if (key == 0x1b || key == 'q'){
			break;
		}
		connect.input(&measurement, INPUT_FILENAME);
		connect.output(&measurement, OUTPUT_FILENAME);
		connect.platform_input(&measurement, PLATFORMCONTROLLER_INPUT_FILENAME);
		connect.platform_output(&measurement, PLATFORMCONTROLLER_OUTPUT_FILENAME);
		if (USE_CENTER_CAMERA){
			measurement.mtx.lock();
			connect.center_input(&measurement, CENTER_INPUT_FILENAME);
			connect.center_output(&measurement, CENTER_OUTPUT_FILENAME);
			measurement.mtx.unlock();
		}
		measurement.measure();
		int *param_L = measurement.vcc_L->matchingParameters;
		int *param_R = measurement.vcc_R->matchingParameters;
		int *param_C;
		if (USE_CENTER_CAMERA) param_C = measurement.vcc_C->matchingParameters;
		view_L.show(measurement.camera_L->colorImage, *(param_L + 2), *(param_L + 3), *(param_L + 6), *(param_L + 7), true);
		view_R.show(measurement.camera_R->colorImage, *(param_R + 2), *(param_R + 3), *(param_R + 6), *(param_R + 7), true);
		cv::Mat tmp_gray;
		cv::cvtColor(measurement.camera_C->colorImage,tmp_gray, CV_BGR2GRAY);
		cv::Mat tmp_color;
		cv::cvtColor(tmp_gray, tmp_color, CV_GRAY2BGR);
		if (USE_CENTER_CAMERA) if (*(param_C + 8)>20) view_C->show(tmp_color, *(param_C + 2), *(param_C + 3), *(param_C + 6), *(param_C + 7), true);
		connect.doSave(&measurement);
		//cv::imshow("test", measurement.vcc_L->templateImage[measurement.vcc_L->targetDB_x][measurement.vcc_L->targetDB_y]);
		const auto end = std::chrono::system_clock::now();
		//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;

		std::ifstream ifs(QUIT_FILENAME);
		if (ifs.fail()) continue;
		std::string line;
		std::getline(ifs, line);
		if (line == "quit") break;
	}
	gnuLoop = false;
	gnu_thread.join();
	measurement.trackingLoopFlag = false;
	measurement.threadTrackingJoin();
	delete[] cstr;
	return 0;
}