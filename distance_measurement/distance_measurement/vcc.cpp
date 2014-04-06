#include "vcc.h"

VCC::VCC(int thres){
	char VCC_CorrelationMapB[256] = { 
		0, 1, 1, 1, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3,
		1, 2, 2, 2, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3, 1, 2, 2, 2, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3,
		1, 2, 2, 2, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4,
		2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4,
		1, 2, 2, 2, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4,
		2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4,
		1, 2, 2, 2, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3, 2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4,
		2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4, 2, 3, 3, 3, 3, 4, 4, 4, 3, 4, 4, 4, 3, 4, 4, 4 
	};
	char* MapG = this->VCC_CorrelationMap;
	char* MapA = VCC_CorrelationMapB;
	for (short a = 256; a; a--, MapA++){
		char* MapB = VCC_CorrelationMapB;
		for (short b = 256; b; b--, MapB++, MapG++){
			*MapG = -(*MapA + *MapB);
		}
	}
	this->threshold = thres;
	for (int j = 0; j < VCC_DATABASE_SIZE; j++){
		std::vector<cv::Mat> templateImage_x;
		for (int i = 0; i < VCC_DATABASE_SIZE; i++){
			char filename[256];
			sprintf_s(filename, VCC_TEMPLATE_DATABASE_PATH, j*VCC_DATABASE_SIZE + i);
			cv::Mat templateReadImage = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
			templateImage_x.push_back(templateReadImage);
			cv::Mat templateResizeImage(VCC_TEMPLATE_SIZE + 2, VCC_TEMPLATE_SIZE + 2, CV_8UC1);
			cv::resize(templateReadImage, templateResizeImage,templateResizeImage.size());
			for (int y = 0; y < VCC_TEMPLATE_SIZE + 2; y++){
				for (int x = 0; x < VCC_TEMPLATE_SIZE + 2; x++){
					this->templateImageData[j][i][y*(VCC_TEMPLATE_SIZE + 2) + x]
						= (unsigned char)*(templateResizeImage.data + y*templateResizeImage.cols + x);
				}
			}
		}
		this->templateImage.push_back(templateImage_x);
	}
	for (int i = 0; i<VCC_DATABASE_SIZE; i++){
		for (int j = 0; j<VCC_DATABASE_SIZE; j++){

			unsigned char* input = this->templateImageData[i][j] + VCC_TEMPLATE_SIZE + 2 + 1;//テンプレート画像データの先頭アドレス+1列分のピクセル+1ピクセル(VCC_TEMPLATE_SIZE+2)+1
			unsigned short* templateAddress = this->templateImageVectorCode[i][j];	//テンプレートVCC画像の先頭アドレス
			for (int z = VCC_TEMPLATE_SIZE; z; z--, input += (VCC_TEMPLATE_SIZE + 2) - VCC_TEMPLATE_SIZE){
				for (int y = VCC_TEMPLATE_QUARTER_SIZE; y; y--, templateAddress++){
					unsigned short VC = 0;
					for (int x = 4; x; x--, input++){
						VC <<= 4;
						int VCX = *(input + (VCC_TEMPLATE_SIZE + 2) + 1) + *(input + 1) + *(input - (VCC_TEMPLATE_SIZE + 2) + 1) - *(input + (VCC_TEMPLATE_SIZE + 2) - 1) - *(input - 1) - *(input - (VCC_TEMPLATE_SIZE + 2) - 1);
						int VCY = *(input + (VCC_TEMPLATE_SIZE + 2) + 1) + *(input + (VCC_TEMPLATE_SIZE + 2)) + *(input + (VCC_TEMPLATE_SIZE + 2) - 1) - *(input - (VCC_TEMPLATE_SIZE + 2) + 1) - *(input - (VCC_TEMPLATE_SIZE + 2)) - *(input - (VCC_TEMPLATE_SIZE + 2) - 1);
						if (VCX>VCC_VC_THRESHOLD)VC += 1; else if (VCX<-VCC_VC_THRESHOLD)VC += 2;
						if (VCY>VCC_VC_THRESHOLD)VC += 4; else if (VCY<-VCC_VC_THRESHOLD)VC += 8;
					}
					*templateAddress = VC;
				}
			}
			//this->MkTmpBL = false;
		}
	}

	//kalmanfilter

	this->KF = new cv::KalmanFilter(4, 2, 0);
	this->state = new cv::Mat_<float>(4, 1); /* (x, y, Vx, Vy) */
	this->processNoise = new cv::Mat(4, 1, CV_32F);
	this->measurement = new cv::Mat_<float>(2, 1);
	this->measurement->setTo(cv::Scalar(0));


	this->targetDB_x = 4;
	this->targetDB_y = 4;
	this->databaseFlag = true;
	this->subpixelFlag = true;
	this->kalmanFlag = true;
	this->allSeekFlag = true;
	this->databaseClearFlag = false;
	this->databaseAllSearchFlag = true;
	this->allSeekThreshold = 800;
	this->databaseSearchThreshold = 800;
}

VCC::~VCC()
{
}

void VCC::kalmanInitialize(double get_x, double get_y){

	KF->statePre.at<float>(0) = get_x;
	KF->statePre.at<float>(1) = get_y;
	KF->statePre.at<float>(2) = 0;
	KF->statePre.at<float>(3) = 0;
	KF->transitionMatrix = *(cv::Mat_<float>(4, 4) << 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

	setIdentity(KF->measurementMatrix);
	setIdentity(KF->processNoiseCov, cv::Scalar::all(1e-3));
	setIdentity(KF->measurementNoiseCov, cv::Scalar::all(1e-1));
	setIdentity(KF->errorCovPost, cv::Scalar::all(.1));

}

void VCC::setInputImage(cv::Mat image){
	unsigned char *imagePointer = image.data;
	for (int i = 0; i < VCC_INPUT_IMAGE_SIZE_X*VCC_INPUT_IMAGE_SIZE_Y; i++){
		this->inputImage[i] = *(imagePointer++);
	}
}

void VCC::templateMatching(){
	unsigned char* input;//Inpt 入力画像アクセスポインタ
	unsigned short* vectorCode;//VcCd 入力ベクトル符号画像アクセスポインタ
	unsigned short* matchingPosition;//McPs マッチング箇所
	unsigned short inputVectorCodeSeekArea[VCC_SEEK_AREA_SIZE_X*VCC_SEEK_AREA_SIZE];//VcCdImg 領域探索用マッチング格納配列
	unsigned short inputVectorCodeAllArea[(VCC_INPUT_IMAGE_SIZE_X - 5)*(VCC_INPUT_IMAGE_SIZE_Y - 2)];//McSt 全探索用マッチング格納配列
	unsigned short* matchingCoordinate;//McXY マッチング座標値保存ポインタ
	char* correlationMap = VCC_CorrelationMap;//CrrMp 相関値計算用テーブルアクセスポインタ
	int* matchingParameterPointer = this->matchingParameters;//MPrm パラメータアクセスポインタ
	int correlationMinimam = 2048;//CrrMin 相関値の最小


	/*********************しきい値以下の場合(領域探索)*******************************/
	if (*(matchingParameterPointer + 8) < this->allSeekThreshold || !this->allSeekFlag){
		/*---------------------ベクトル符号化-------------------------------------------*/
		input = inputImage + (*(matchingParameterPointer + 6) - VCC_SEEK_AREA_HALF_SIZE) + (*(matchingParameterPointer + 7) - VCC_SEEK_AREA_HALF_SIZE)*VCC_INPUT_IMAGE_SIZE_X;	//探索領域の先頭アドレスの入力
		vectorCode = inputVectorCodeSeekArea;
		for (int y = VCC_SEEK_AREA_SIZE; y; y--, input += VCC_INPUT_IMAGE_SIZE_X - VCC_SEEK_AREA_SIZE)
		{
			unsigned short VC = 0;
			for (int x = 3; x; x--, input++)
			{
				VC <<= 4;
				int VCX = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + 1) + *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				int VCY = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + VCC_INPUT_IMAGE_SIZE_X) + *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input - VCC_INPUT_IMAGE_SIZE_X) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				if (VCX > VCC_VECTOR_CODE_THRESHOLD)VC += 1; else if (VCX < -VCC_VECTOR_CODE_THRESHOLD)VC += 2;
				if (VCY > VCC_VECTOR_CODE_THRESHOLD)VC += 4; else if (VCY < -VCC_VECTOR_CODE_THRESHOLD)VC += 8;
			}
			for (int x = VCC_SEEK_AREA_SIZE_X; x; x--, input++, vectorCode++)
			{
				VC <<= 4;
				int VCX = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + 1) + *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				int VCY = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + VCC_INPUT_IMAGE_SIZE_X) + *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input - VCC_INPUT_IMAGE_SIZE_X) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				if (VCX>VCC_VECTOR_CODE_THRESHOLD)VC += 1; else if (VCX<-VCC_VECTOR_CODE_THRESHOLD)VC += 2;
				if (VCY>VCC_VECTOR_CODE_THRESHOLD)VC += 4; else if (VCY < -VCC_VECTOR_CODE_THRESHOLD)VC += 8;
				*vectorCode = VC;
			}
		}
		/*---------------------相関計算-------------------------------------------------*/
		matchingPosition = inputVectorCodeSeekArea;
		for (int yy = VCC_SEEK_AREA_VECTOR_CODE_SIZE; yy; yy--, matchingPosition += VCC_SEEK_AREA_SIZE_X - VCC_SEEK_AREA_VECTOR_CODE_SIZE){
			for (int xx = VCC_SEEK_AREA_VECTOR_CODE_SIZE; xx; xx--, matchingPosition++){
				unsigned short* templateVC;//TmpB

				templateVC = this->templateImageVectorCode[this->targetDB_x][this->targetDB_y];

				int correlationScore = correlationMinimam;
				vectorCode = matchingPosition;
				for (int y = VCC_TEMPLATE_SIZE/4; y&&correlationScore > 0; y--, vectorCode += VCC_SEEK_AREA_SIZE_X - VCC_TEMPLATE_SIZE)
				for (int x = VCC_TEMPLATE_QUARTER_SIZE; x; x--, vectorCode += 4, templateVC++)
					correlationScore += *(correlationMap + (*vectorCode^*templateVC));
				if (correlationScore <= 0)continue;
				correlationMinimam -= correlationScore;
				matchingCoordinate = matchingPosition;
			}
		}

		/*---------------------DB探索（相違度が大きかったら実行）---必要ない場合はここをコメントアウト----*/
		if (this->databaseClearFlag){
			this->targetDB_x = 4;
			this->targetDB_y = 4;
			this->databaseClearFlag = false;
		}
		if ((correlationMinimam >= this->databaseSearchThreshold) && this->databaseFlag || this->databaseAllSearchFlag){
			//テンプレートデータベース探索の際の一時保管用変数
			int tempCorrelationMinimum;//tmpCrrMin
			int targetDB_x_min, targetDB_y_min;

			if (this->databaseAllSearchFlag){
				for (int j = this->targetDB_x - 8; j <= this->targetDB_x + 8; j++){
					for (int i = this->targetDB_y - 8; i <= this->targetDB_y + 8; i++){
						if (j < 0 || VCC_DATABASE_SIZE - 1 < j) continue;	//データベースの範囲外を探索しない
						if (i < 0 || VCC_DATABASE_SIZE - 1 < i) continue;

						unsigned short* tempMatchingPosition = inputVectorCodeSeekArea;
						unsigned short* tempMatchingCoordinate;
						tempCorrelationMinimum = 2048;

						/*相関計算----------------------------------------------------------*/
						for (int yy = VCC_SEEK_AREA_VECTOR_CODE_SIZE; yy; yy--, tempMatchingPosition += VCC_SEEK_AREA_SIZE_X - VCC_SEEK_AREA_VECTOR_CODE_SIZE){
							for (int xx = VCC_SEEK_AREA_VECTOR_CODE_SIZE; xx; xx--, tempMatchingPosition++){
								unsigned short* templateVC;//TmpB
								templateVC = this->templateImageVectorCode[j][i];

								int correlationScore = tempCorrelationMinimum;
								vectorCode = tempMatchingPosition;
								for (int y = VCC_TEMPLATE_SIZE; y&&correlationScore > 0; y--, vectorCode += VCC_SEEK_AREA_SIZE_X - VCC_TEMPLATE_SIZE)
								for (int x = VCC_TEMPLATE_QUARTER_SIZE; x; x--, vectorCode += 4, templateVC++)
									correlationScore += *(correlationMap + (*vectorCode^*templateVC));
								if (correlationScore <= 0)continue;
								tempCorrelationMinimum -= correlationScore;
								tempMatchingCoordinate = tempMatchingPosition;
							}
						}
						//printf("[%d,%d][correlationMinimam=%d]\n", j,i,tempCorrelationMinimum);
						/*相関値計算ここまで------------------------------------------------------*/
						if (tempCorrelationMinimum < correlationMinimam){
							correlationMinimam = tempCorrelationMinimum;
							matchingCoordinate = tempMatchingCoordinate;
							targetDB_x_min = j;
							targetDB_y_min = i;
							this->targetDB_x = targetDB_x_min;
							this->targetDB_y = targetDB_y_min;
						}
					}//列の探索
				}//行の探索
				this->databaseAllSearchFlag = false;
			}
			else{
				for (int j = this->targetDB_x - 1; j <= this->targetDB_x + 1; j++){
					for (int i = this->targetDB_y - 1; i <= this->targetDB_y + 1; i++){
						if (j < 0 || VCC_DATABASE_SIZE - 1 < j) continue;	//データベースの範囲外を探索しない
						if (i < 0 || VCC_DATABASE_SIZE - 1 < i) continue;
						//if (!(j == this->targetDB_x || i == this->targetDB_y)) continue;


						unsigned short* tempMatchingPosition = inputVectorCodeSeekArea;
						unsigned short* tempMatchingCoordinate;
						tempCorrelationMinimum = 2048;

						/*相関計算----------------------------------------------------------*/
						tempMatchingPosition += (matchingCoordinate - inputVectorCodeSeekArea - 9 - 124 * 9);
						for (int yy = 50; yy; yy--, tempMatchingPosition += 74){
							for (int xx = 50; xx; xx--, tempMatchingPosition++){
								unsigned short* templateVC;//TmpB
								templateVC = this->templateImageVectorCode[j][i];

								int correlationScore = tempCorrelationMinimum;
								vectorCode = tempMatchingPosition;
								for (int y = VCC_TEMPLATE_SIZE/4; y&&correlationScore > 0; y--, vectorCode += VCC_SEEK_AREA_SIZE_X - VCC_TEMPLATE_SIZE)
								for (int x = VCC_TEMPLATE_QUARTER_SIZE; x; x--, vectorCode += 4, templateVC++)
									correlationScore += *(correlationMap + (*vectorCode^*templateVC));
								if (correlationScore <= 0)continue;
								tempCorrelationMinimum -= correlationScore;
								tempMatchingCoordinate = tempMatchingPosition;
							}
						}
						//printf("[%d,%d][correlationMinimam=%d]\n", j,i,tempCorrelationMinimum);
						/*相関値計算ここまで------------------------------------------------------*/
						if (tempCorrelationMinimum < correlationMinimam){
							correlationMinimam = tempCorrelationMinimum;
							matchingCoordinate = tempMatchingCoordinate;
							targetDB_x_min = j;
							targetDB_y_min = i;
							this->targetDB_x = targetDB_x_min;
							this->targetDB_y = targetDB_y_min;
						}
					}//列の探索
				}//行の探索
			}
		}
		/*--------------------------------------------------------------------DB探索ここまで--------------*/
		/*---------------------サブピクセル推定法------------------------------------------*/
		if (this->subpixelFlag){
			int Crrpm1[4] = { VCC_CORRELATION_THRESHOLD, VCC_CORRELATION_THRESHOLD, VCC_CORRELATION_THRESHOLD, VCC_CORRELATION_THRESHOLD };
			for (int i = 0; i < 4; i++)
			{
				//X+1の相違度
				//WORD* TmpB=TmpBImg;
				unsigned short* templateVC;
				templateVC = this->templateImageVectorCode[this->targetDB_x][this->targetDB_y];

				int correlationScore = VCC_CORRELATION_THRESHOLD;
				switch (i){
				case 0: vectorCode = matchingCoordinate + 1; break;    //X+1のアドレス
				case 1: vectorCode = matchingCoordinate - 1; break;    //X-1のアドレス
				case 2: vectorCode = matchingCoordinate + VCC_SEEK_AREA_SIZE_X; break;//Y+1のアドレス
				case 3: vectorCode = matchingCoordinate - VCC_SEEK_AREA_SIZE_X; break;//Y-1のアドレス
				}

				for (int y = VCC_TEMPLATE_SIZE; y&&correlationScore > 0; y--, vectorCode += VCC_SEEK_AREA_SIZE_X - VCC_TEMPLATE_SIZE)
				for (int x = VCC_TEMPLATE_QUARTER_SIZE; x; x--, vectorCode += 4, templateVC++)
					correlationScore += *(correlationMap + (*vectorCode^*templateVC));
				Crrpm1[i] -= correlationScore;
			}

			subpixelResult_x = (double)(Crrpm1[1] - Crrpm1[0]) / (Crrpm1[0] + Crrpm1[1] - 2 * correlationMinimam) / 2.0;
			subpixelResult_y = (double)(Crrpm1[3] - Crrpm1[2]) / (Crrpm1[2] + Crrpm1[3] - 2 * correlationMinimam) / 2.0;
		}
		/*--------------------カルマンフィルタ処理-------------------------------------*/

		cv::Mat prediction = this->KF->predict();
		cv::Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

		(*measurement)(0) = ((int)matchingCoordinate - (int)inputVectorCodeSeekArea) / 2 % VCC_SEEK_AREA_SIZE_X + *(matchingParameterPointer + 6) - VCC_SEEK_AREA_VECTOR_CODE_HALF_SIZE + this->subpixelResult_x;
		(*measurement)(1) = ((int)matchingCoordinate - (int)inputVectorCodeSeekArea) / 2 / VCC_SEEK_AREA_SIZE_X + *(matchingParameterPointer + 7) - VCC_SEEK_AREA_VECTOR_CODE_HALF_SIZE + this->subpixelResult_y;

		cv::Mat estimated = KF->correct((*measurement));
		kalmanx = estimated.at<float>(0);
		kalmany = estimated.at<float>(1);

		/*---------------------検出結果の計算処理---------------------------------------*/
		//前回の検出位置
		* matchingParameterPointer = *(matchingParameterPointer + 2);
		*(matchingParameterPointer + 1) = *(matchingParameterPointer + 3);

		if (this->kalmanFlag){
			////今回の検出位置（中心座標）カルマンフィルターあり
			*(matchingParameterPointer + 2) = kalmanx;
			*(matchingParameterPointer + 3) = kalmany;
		}
		else{
			//今回の検出位置（中心座標）
			*(matchingParameterPointer + 2) = ((int)matchingCoordinate - (int)inputVectorCodeSeekArea) / 2 % VCC_SEEK_AREA_SIZE_X + *(matchingParameterPointer + 6) - VCC_SEEK_AREA_VECTOR_CODE_HALF_SIZE + this->subpixelResult_x;
			*(matchingParameterPointer + 3) = ((int)matchingCoordinate - (int)inputVectorCodeSeekArea) / 2 / VCC_SEEK_AREA_SIZE_X + *(matchingParameterPointer + 7) - VCC_SEEK_AREA_VECTOR_CODE_HALF_SIZE + this->subpixelResult_y;
		}

		//対象の予測位置(中心座標）
		*(matchingParameterPointer + 4) = (std::max)((std::min)(*(matchingParameterPointer + 2), VCC_INPUT_IMAGE_SIZE_X - VCC_TEMPLATE_HALF_X), VCC_TEMPLATE_HALF_X);
		*(matchingParameterPointer + 5) = (std::max)((std::min)(*(matchingParameterPointer + 3), VCC_INPUT_IMAGE_SIZE_Y - VCC_TEMPLATE_HALF_X), VCC_TEMPLATE_HALF_X);

		//処理領域の予測位置(中心座標)
		*(matchingParameterPointer + 6) = (std::max)((std::min)(*(matchingParameterPointer + 2), VCC_INPUT_IMAGE_SIZE_X - VCC_SEEK_AREA_HALF_SIZE), VCC_SEEK_AREA_HALF_SIZE + 1);
		*(matchingParameterPointer + 7) = (std::max)((std::min)(*(matchingParameterPointer + 3), VCC_INPUT_IMAGE_SIZE_Y - VCC_SEEK_AREA_HALF_SIZE), VCC_SEEK_AREA_HALF_SIZE + 1);

		//相関値(中心座標)
		*(matchingParameterPointer + 8) = correlationMinimam;
	}



	/**********************しきい値を超えた場合(全探索)************************************/
	else{
		/*---------------------ベクトル符号化-------------------------------------------*/
		input = inputImage + VCC_INPUT_IMAGE_SIZE_X + 1;//+(*(matchingParameterPointer+6)-VCC_SEEK_AREA_HALF_SIZE)+(*(matchingParameterPointer+7)-VCC_SEEK_AREA_HALF_SIZE)*VCC_INPUT_IMAGE_SIZE_X;	//探索領域の先頭アドレスの入力
		vectorCode = inputVectorCodeAllArea;
		for (int y = VCC_INPUT_IMAGE_SIZE_Y - 2; y; y--, input += 2)
		{
			unsigned short VC = 0;
			for (int x = 3; x; x--, input++)
			{
				VC <<= 4;
				int VCX = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + 1) + *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				int VCY = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + VCC_INPUT_IMAGE_SIZE_X) + *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input - VCC_INPUT_IMAGE_SIZE_X) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				if (VCX > VCC_VECTOR_CODE_THRESHOLD)VC += 1; else if (VCX<-VCC_VECTOR_CODE_THRESHOLD)VC += 2;
				if (VCY>VCC_VECTOR_CODE_THRESHOLD)VC += 4; else if (VCY<-VCC_VECTOR_CODE_THRESHOLD)VC += 8;
			}
			for (int x = VCC_INPUT_IMAGE_SIZE_X - 5; x; x--, input++, vectorCode++)
			{
				VC <<= 4;
				int VCX = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + 1) + *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				int VCY = *(input + VCC_INPUT_IMAGE_SIZE_X + 1) + *(input + VCC_INPUT_IMAGE_SIZE_X) + *(input + VCC_INPUT_IMAGE_SIZE_X - 1) - *(input - VCC_INPUT_IMAGE_SIZE_X + 1) - *(input - VCC_INPUT_IMAGE_SIZE_X) - *(input - VCC_INPUT_IMAGE_SIZE_X - 1);
				if (VCX>VCC_VECTOR_CODE_THRESHOLD)VC += 1; else if (VCX<-VCC_VECTOR_CODE_THRESHOLD)VC += 2;
				if (VCY>VCC_VECTOR_CODE_THRESHOLD)VC += 4; else if (VCY < -VCC_VECTOR_CODE_THRESHOLD)VC += 8;
				*vectorCode = VC;
			}
		}
		/*---------------------相関計算-------------------------------------------------*/
		matchingPosition = inputVectorCodeAllArea;
		for (int yy = VCC_INPUT_IMAGE_SIZE_Y - 2 - VCC_TEMPLATE_SIZE / 4 + 1; yy; yy--, matchingPosition += VCC_TEMPLATE_SIZE - 4){
			for (int xx = VCC_INPUT_IMAGE_SIZE_X - 2 - VCC_TEMPLATE_SIZE + 1; xx; xx--, matchingPosition++){
				//WORD* TmpB=TmpBImg;
				unsigned short* templateVC;

				//変数DB_LTrgt_Col, DB_LTrgt_Row, DB_RTrgt_Col, DB_RTrgt_Rowを使う
				//マッチングさせるテンプレートの先頭アドレスをtemplateVCに代入する
				this->targetDB_x = 4;
				this->targetDB_y = 4;
				templateVC = this->templateImageVectorCode[4][4];

				int correlationScore = correlationMinimam;
				vectorCode = matchingPosition;
				for (int y = VCC_TEMPLATE_SIZE / 4; y&&correlationScore > 0; y--, vectorCode += (VCC_INPUT_IMAGE_SIZE_X - 5) - VCC_TEMPLATE_SIZE)
				for (int x = VCC_TEMPLATE_QUARTER_SIZE; x; x--, vectorCode += 4, templateVC++)
					correlationScore += *(correlationMap + (*vectorCode^*templateVC));
				if (correlationScore <= 0)continue;
				correlationMinimam -= correlationScore;
				matchingCoordinate = matchingPosition;
			}
		}
		///*---------------------サブピクセル推定法------------------------------------------*/
		if (this->subpixelFlag && matchingCoordinate + VCC_INPUT_IMAGE_SIZE_X + 1 < &(inputVectorCodeAllArea[303530-1])){
			int Crrpm1[4] = { VCC_CORRELATION_THRESHOLD, VCC_CORRELATION_THRESHOLD, VCC_CORRELATION_THRESHOLD, VCC_CORRELATION_THRESHOLD };
			for (int i = 0; i < 4; i++)
			{
				//X+1の相違度
				//WORD* TmpB=TmpBImg;
				unsigned short* templateVC;
				templateVC = this->templateImageVectorCode[this->targetDB_x][this->targetDB_y];

				int correlationScore = VCC_CORRELATION_THRESHOLD;
				switch (i){
				case 0: vectorCode = matchingCoordinate + 1; break;    //X+1のアドレス
				case 1: vectorCode = matchingCoordinate - 1; break;    //X-1のアドレス
				case 2: vectorCode = matchingCoordinate + VCC_INPUT_IMAGE_SIZE_X -5; break;//Y+1のアドレス
				case 3: vectorCode = matchingCoordinate - VCC_INPUT_IMAGE_SIZE_X -5; break;//Y-1のアドレス
				}

				for (int y = VCC_TEMPLATE_SIZE / 4; y&&correlationScore > 0; y--, vectorCode += (VCC_INPUT_IMAGE_SIZE_X - 5) - VCC_TEMPLATE_SIZE)
				for (int x = VCC_TEMPLATE_QUARTER_SIZE; x; x--, vectorCode += 4, templateVC++)
					correlationScore += *(correlationMap + (*vectorCode^*templateVC));
				Crrpm1[i] -= correlationScore;
			}

			subpixelResult_x = (double)(Crrpm1[1] - Crrpm1[0]) / (Crrpm1[0] + Crrpm1[1] - 2 * correlationMinimam) / 2.0;
			subpixelResult_y = (double)(Crrpm1[3] - Crrpm1[2]) / (Crrpm1[2] + Crrpm1[3] - 2 * correlationMinimam) / 2.0;
		}
		/*--------------------カルマンフィルタ処理-------------------------------------*/

		cv::Mat prediction = this->KF->predict();
		cv::Point predictPt(prediction.at<float>(0), prediction.at<float>(1));

		(*measurement)(0) = ((int)matchingCoordinate - (int)inputVectorCodeAllArea) / 2 % (VCC_INPUT_IMAGE_SIZE_X - 5) + VCC_TEMPLATE_SIZE / 2;
		(*measurement)(1) = ((int)matchingCoordinate - (int)inputVectorCodeAllArea) / 2 / (VCC_INPUT_IMAGE_SIZE_X - 5) + VCC_TEMPLATE_SIZE / 2;

		cv::Mat estimated = KF->correct((*measurement));
		kalmanx = estimated.at<float>(0);
		kalmany = estimated.at<float>(1);

		/*---------------------検出結果の計算処理---------------------------------------*/
		//前回の検出位置
		* matchingParameterPointer = *(matchingParameterPointer + 2);
		*(matchingParameterPointer + 1) = *(matchingParameterPointer + 3);

		if (this->kalmanFlag){
			//今回の検出位置（中心座標）カルマンフィルターあり
			*(matchingParameterPointer + 2) = kalmanx;
			*(matchingParameterPointer + 3) = kalmany;
		}
		else{
			//今回の検出位置（中心座標）
			*(matchingParameterPointer + 2) = ((int)matchingCoordinate - (int)inputVectorCodeAllArea) / 2 % (VCC_INPUT_IMAGE_SIZE_X - 5) + VCC_TEMPLATE_SIZE / 2;
			*(matchingParameterPointer + 3) = ((int)matchingCoordinate - (int)inputVectorCodeAllArea) / 2 / (VCC_INPUT_IMAGE_SIZE_X - 5) + VCC_TEMPLATE_SIZE / 2;
		}

		//対象の予測位置(中心座標）
		*(matchingParameterPointer + 4) = (std::max)((std::min)(*(matchingParameterPointer + 2), VCC_INPUT_IMAGE_SIZE_X - VCC_TEMPLATE_HALF_X), VCC_TEMPLATE_HALF_X);
		*(matchingParameterPointer + 5) = (std::max)((std::min)(*(matchingParameterPointer + 3), VCC_INPUT_IMAGE_SIZE_Y - VCC_TEMPLATE_HALF_X), VCC_TEMPLATE_HALF_X);

		//処理領域の予測位置(中心座標)
		*(matchingParameterPointer + 6) = (std::max)((std::min)(*(matchingParameterPointer + 2), VCC_INPUT_IMAGE_SIZE_X - VCC_SEEK_AREA_HALF_SIZE), VCC_SEEK_AREA_HALF_SIZE + 1);
		*(matchingParameterPointer + 7) = (std::max)((std::min)(*(matchingParameterPointer + 3), VCC_INPUT_IMAGE_SIZE_Y - VCC_SEEK_AREA_HALF_SIZE), VCC_SEEK_AREA_HALF_SIZE + 1);

		//相関値(中心座標)
		*(matchingParameterPointer + 8) = correlationMinimam;
	}
}
