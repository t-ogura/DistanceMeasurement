#include "measurement.h"
#include "view.h"

#define MAIN_PIXEL_SIZE       0.0075
#define MAIN_FOCAL_LENGTH     50.0
#define MAIN_BASELINE_LENGTH  178

int main(){
	Measurement measurement(MAIN_PIXEL_SIZE,MAIN_FOCAL_LENGTH,MAIN_BASELINE_LENGTH);
	View view_L("LEFT",0,300);
	View view_R("RIGHT", 670, 300);
	measurement.threadTracking("Biclops/data/BiclopsDefaultRight.cfg");
	while (1){
		int key = cv::waitKey(1);
		if (key == 0x1b || key == 'q'){
		}
		measurement.measure();
		int *param_L = measurement.vcc_L->matchingParameters;
		int *param_R = measurement.vcc_R->matchingParameters;
		view_L.show(measurement.camera_L->colorImage, *(param_L + 2), *(param_L + 3), true);
		view_R.show(measurement.camera_R->colorImage, *(param_R + 2), *(param_R + 3), true);
	}
	measurement.trackingLoopFlag = false;
	measurement.threadTrackingJoin();
	return 0;
}