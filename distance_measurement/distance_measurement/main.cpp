#include "measurement.h"
#include "view.h"

#define MAIN_PIXEL_SIZE       0.0075
#define MAIN_FOCAL_LENGTH     50.0
#define MAIN_BASELINE_LENGTH  178

int main(){
	Measurement measurement(MAIN_PIXEL_SIZE,MAIN_FOCAL_LENGTH,MAIN_BASELINE_LENGTH);
	return 0;
}