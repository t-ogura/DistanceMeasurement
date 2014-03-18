#ifndef _VCC_H_
#define _VCC_H_


#include "global.h"

#define VCC_TEMPLATE_DATABASE_PATH "targetDB/imgcut_%02d.bmp"

#define VCC_DATABASE_SIZE 9
#define VCC_TEMPLATE_SIZE 32
#define VCC_TEMPLATE_HALF_SIZE (VCC_TEMPLATE_SIZE/2)
#define VCC_TEMPLATE_QUARTER_SIZE (VCC_TEMPLATE_SIZE/4)
#define VCC_VC_THRESHOLD 10
#define VCC_INPUT_IMAGE_SIZE_X 640
#define VCC_INPUT_IMAGE_SIZE_Y 480
#define VCC_SEEK_AREA_SIZE 255
#define VCC_SEEK_AREA_SIZE_X (VCC_SEEK_AREA_SIZE-3)
#define VCC_SEEK_AREA_HALF_SIZE ((VCC_SEEK_AREA_SIZE+1)/2)
#define VCC_VECTOR_CODE_THRESHOLD 10
#define VCC_SEEK_AREA_VECTOR_CODE_SIZE (VCC_SEEK_AREA_SIZE+1-VCC_TEMPLATE_SIZE)
#define VCC_SEEK_AREA_VECTOR_CODE_HALF_SIZE (VCC_SEEK_AREA_VECTOR_CODE_SIZE/2)
#define VCC_DISSIMILARITY_THRESHOLD 500
#define VCC_CORRELATION_THRESHOLD 2048
#define VCC_TEMPLATE_HALF_X (VCC_TEMPLATE_SIZE/2+1)

class VCC{
private:
	short threshold;
	//ëää÷åvéZÇÃLookUpTable (4âÊëfï™(16Å~16))
	char VCC_CorrelationMap[65536];//VCCCrrMp
	unsigned char templateImageData[VCC_DATABASE_SIZE][VCC_DATABASE_SIZE][VCC_TEMPLATE_SIZE*VCC_TEMPLATE_QUARTER_SIZE];//TmpImg
	unsigned short templateImageVectorCode[VCC_DATABASE_SIZE][VCC_DATABASE_SIZE][VCC_TEMPLATE_SIZE*VCC_TEMPLATE_QUARTER_SIZE];//TmpBImg
	unsigned char inputImage[VCC_INPUT_IMAGE_SIZE_X*VCC_INPUT_IMAGE_SIZE_Y];//InptImg

	//kalmanfilter	
	cv::KalmanFilter *KF;
	cv::Mat_<float> *state; /* (x, y, Vx, Vy) */
	cv::Mat *processNoise;
	cv::Mat_<float> *measurement;

public:

	VCC(int VCC_Threshold = 12);
	~VCC();

	void kalmanInitialize(double get_x, double get_y);

	std::vector<std::vector< cv::Mat> > templateImage;

	double kalmanx, kalmany;
	bool databaseFlag;
	bool subpixelFlag;
	bool databaseClearFlag;
	bool databaseAllSearchFlag;
	int targetDB_x;//DB_LTrgt_Row
	int targetDB_y;//DB_LTrgt_Col
	void setInputImage(cv::Mat inputImage_Gray);
	void templateMatching();
	int matchingParameters[9];
	double subpixelResult_x;
	double subpixelResult_y;
};

#endif _VCC_H_