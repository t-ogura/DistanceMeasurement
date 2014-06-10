#include "measurement.h"
#include "view.h"
#include "form_connection.h"


#define MAIN_PIXEL_SIZE       0.0075
#define MAIN_FOCAL_LENGTH     16.0
#define MAIN_BASELINE_LENGTH  220
#define OUTPUT_FILENAME "../param_files/send.param"
#define INPUT_FILENAME "../param_files/receive.param"




int main(){
	Measurement measurement(MAIN_PIXEL_SIZE,MAIN_FOCAL_LENGTH,MAIN_BASELINE_LENGTH);
	View view_L("LEFT",320,400);
	View view_R("RIGHT", 670, 400);
	FormConnection connect;
	measurement.threadTracking("\\\\.\\COM1",9600);
	while (1){
		int key = cv::waitKey(1);
		if (key == 0x1b || key == 'q'){
		}
		connect.input(&measurement, INPUT_FILENAME);
		connect.output(&measurement, OUTPUT_FILENAME);
		measurement.measure();
		int *param_L = measurement.vcc_L->matchingParameters;
		int *param_R = measurement.vcc_R->matchingParameters;
		view_L.show(measurement.camera_L->colorImage, *(param_L + 2), *(param_L + 3), *(param_L + 6), *(param_L + 7), true);
		view_R.show(measurement.camera_R->colorImage, *(param_R + 2), *(param_R + 3), *(param_R + 6), *(param_R + 7), true);
		connect.doSave(&measurement);
		//cv::imshow("test", measurement.vcc_L->templateImage[measurement.vcc_L->targetDB_x][measurement.vcc_L->targetDB_y]);
	}
	measurement.trackingLoopFlag = false;
	measurement.threadTrackingJoin();
	return 0;
}