
#include <iostream>
#include <fstream>

#include "measurement.h"
#include "view.h"
#include "form_connection.h"

#include <winbase.h>

#define MAIN_PIXEL_SIZE       0.0075
#define MAIN_FOCAL_LENGTH     16.0
#define MAIN_BASELINE_LENGTH  220
#define MAIN_CENTER_CAMERA_FOCAL_LENGTH     8.0
#define USE_CENTER_CAMERA true
#define OUTPUT_FILENAME "../param_files/send.param"
#define INPUT_FILENAME "../param_files/receive.param"


#define GNUPLOT_PATH "C:\\gnuplot\\bin\\gnuplot.exe"	// pgnuplotの場所


int main(){
	Measurement measurement(MAIN_PIXEL_SIZE, MAIN_FOCAL_LENGTH, MAIN_BASELINE_LENGTH, 12, USE_CENTER_CAMERA, MAIN_CENTER_CAMERA_FOCAL_LENGTH);
	View view_L("LEFT", 320, 400);
	View view_R("RIGHT", 670, 400);
	View view_C("CENTER", 515, 100);
	FormConnection connect;
	measurement.threadTracking("\\\\.\\COM5",9600);

	FILE *gnu;
	if ((gnu = _popen(GNUPLOT_PATH, "w")) == NULL) {
		printf("gnuplot open error!!\n");
		exit(EXIT_FAILURE);	// エラーの場合は通常、異常終了する
	}
	fprintf(gnu, "set size square\n");		// figureを正方形に
	fprintf(gnu, "unset key\n");		// 凡例を表示しない
	int frame = 0;
	std::ofstream plot("plot.dat");

	while (1){
		int key = cv::waitKey(1);
		if (key == 0x1b || key == 'q'){
			break;
		}
		connect.input(&measurement, INPUT_FILENAME);
		connect.output(&measurement, OUTPUT_FILENAME);
		measurement.measure();
		int *param_L = measurement.vcc_L->matchingParameters;
		int *param_R = measurement.vcc_R->matchingParameters;
		int *param_C = measurement.vcc_C->matchingParameters;
		view_L.show(measurement.camera_L->colorImage, *(param_L + 2), *(param_L + 3), *(param_L + 6), *(param_L + 7), true);
		view_R.show(measurement.camera_R->colorImage, *(param_R + 2), *(param_R + 3), *(param_R + 6), *(param_R + 7), true);
		if (*(param_C+8)>20)view_C.show(measurement.camera_C->colorImage, *(param_C + 2), *(param_C + 3), *(param_C + 6), *(param_C + 7), true);
		connect.doSave(&measurement);
		//cv::imshow("test", measurement.vcc_L->templateImage[measurement.vcc_L->targetDB_x][measurement.vcc_L->targetDB_y]);
		std::ofstream plot("plot.dat", std::ios::app);
		fprintf(gnu, "set title 'frame = %d'\n", frame++); // タイトルを設定
		plot << frame << " " << measurement.non_offset.original << " " << measurement.distance.kf << std::endl;
		fprintf(gnu, "plot [%d:%d][%lf:%lf] 'plot.dat' u 1:2 w l,\'plot.dat' u 1:3 w l \n", frame - 500, frame,measurement.distance.kf-500,measurement.distance.kf+500);	// gnuplotで点を描く
		fflush(gnu);	// バッファに格納されているデータを吐き出す（必須）
		plot.close();
	}
	fprintf(gnu, "exit\n"); // gnuplotの終了
	fflush(gnu); // バッファに格納されているデータを吐き出す（必須）
	measurement.trackingLoopFlag = false;
	measurement.threadTrackingJoin();
	return 0;
}