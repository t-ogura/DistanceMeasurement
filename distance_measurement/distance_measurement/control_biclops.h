#ifndef _CONTROL_BICLOPS_H_
#define _CONTROL_BICLOPS_H_

//【Biclops関係】
#include "Biclops/include/Biclops.h"
#include "Biclops/include/PMDUtils.h"
#include "Biclops/include/PMDAxisControl.h"
//#if _DEBUG
//#pragma comment (lib, "Biclops/lib/libBiclopsD.lib")
//#pragma comment (lib, "Biclops/lib/libPMDD.lib")
//#pragma comment (lib, "Biclops/lib/libUtilsD.lib")
//#else
//#pragma comment (lib, "Biclops/lib/libBiclops.lib")
//#pragma comment (lib, "Biclops/lib/libPMD.lib")
//#pragma comment (lib, "Biclops/lib/libUtils.lib")
//#endif
#pragma comment (lib, "pthread/lib/pthreadVC.lib")
#pragma comment (lib, "pthread/lib/pthreadVCE.lib")
#pragma comment (lib, "pthread/lib/pthreadVSE.lib")

#include <time.h>

//【Biclops関連の変数】
const int axisMask = Biclops::PanMask + Biclops::TiltMask;//回転軸の指定

#define CONTROL_BICLOPS_IMAGE_WIDTH 640
#define CONTROL_BICLOPS_IMAGE_HEIGHT 480

class ControlBiclops /*雲台：camera platform*/
{
public:
	//Biclops関連の変数・関数
	Biclops biclops;
	PMDAxisControl *AxisParam;
	PMDAxisControl *panAxis;    //軸制御用のポインタ変数
	PMDAxisControl *tiltAxis;   //軸制御用のポインタ変数
	PMDAxisControl::Profile profile;//軸情報格納変数
	PMDint32 pan_pos, tilt_pos, past_pan, past_tilt; //回転台の現在位置(カウント数）
	PMDint32 pan_pos_init;	//回転台の初期化の際の位置
	double pan_angle_rad, tilt_angle_rad;
	void  deviceTurn(double pan, double tilt); //カメラの回転に使用する関数

	//コンストラクタ
	ControlBiclops(const char *p);	//pにはBiclopsの設定ファイルのパスを入れる
	//デコンストラクタ
	~ControlBiclops();

	void getPosition();					//回転台角度取得メソッド
	void turnHome();				//ホームポジションに戻るメソッド
	void directionTurn(double X, double Y);	//回転台の方向を変える関数


};


#endif _CONTROL_BICLOPS_H_