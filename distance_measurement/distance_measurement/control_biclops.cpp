#include "control_biclops.h"
#define _USE_MATH_DEFINES
#include <math.h>

//---------------------------------------------------------------------------
//ControlBiclopsクラス関数///////////////////////////////////////////////////
//---------------------------------------------------------------------------
//コンストラクタ/////////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
ControlBiclops::ControlBiclops(const char *p){
	//biclopsの初期化
	this->biclops.Initialize(p);
	this->panAxis = biclops.GetAxis(Biclops::Pan);
	this->tiltAxis = biclops.GetAxis(Biclops::Tilt);
	this->biclops.HomeAxes(axisMask);
	//現在位置の取得
	this->panAxis->GetActualPosition(this->pan_pos_init);
	this->panAxis->GetActualPosition(pan_pos);
	this->tiltAxis->GetActualPosition(tilt_pos);
}

//---------------------------------------------------------------------------
//デコンストラクタ///////////////////////////////////////////////////////////
//---------------------------------------------------------------------------
ControlBiclops::~ControlBiclops(){
}

//---------------------------------------------------------------------------
//回転台の現在位置を取得する関数/////////////////////////////////////////////
//---------------------------------------------------------------------------
void ControlBiclops::getPosition()
{
	//現在位置の取得
	past_pan = pan_pos;	//前回位置の保存
	past_tilt = tilt_pos;	//前回位置の保存
	panAxis->GetActualPosition(pan_pos);
	tiltAxis->GetActualPosition(tilt_pos);
}

//---------------------------------------------------------------------------
//回転台をホームポジションに戻す/////////////////////////////////////////////
//---------------------------------------------------------------------------
void ControlBiclops::turnHome()
{
	panAxis->GetProfile(profile);
	profile.pos = 0;
	panAxis->SetProfile(profile);

	tiltAxis->GetProfile(profile);
	profile.pos = 0;
	tiltAxis->SetProfile(profile);

	biclops.Move(axisMask, 0);
}

//---------------------------------------------------------------------------
//回転台の方向を変える関数///////////////////////////////////////////////////
//---------------------------------------------------------------------------
void ControlBiclops::directionTurn(double X, double Y)
{
	panAxis->GetProfile(profile);
	profile.pos += X / CONTROL_BICLOPS_IMAGE_WIDTH / 64;
	panAxis->SetProfile(profile);

	tiltAxis->GetProfile(profile);
	profile.pos += Y / CONTROL_BICLOPS_IMAGE_HEIGHT / 64;
	tiltAxis->SetProfile(profile);

	biclops.Move(axisMask, 0);
}

//---------------------------------------------------------------------------
//カメラの回転に使用する関数/////////////////////////////////////////////////
//---------------------------------------------------------------------------
void ControlBiclops::deviceTurn(double pan_angle, double tilt_angle)
{
	////制御方式の変更
	////常に移動させる
	time_t start, end;
	panAxis->GetProfile(profile);//0ms
	if (fabs(profile.pos) < 0.4  /*&& abs(dx) > 5*/)//前の条件→角度保障(revs)，後ろの条件→微小移動の制限（ピクセル）
	{
		profile.pos = PMDUtils::RadsToRevs(pan_angle) + PMDUtils::DegsToRevs(pan_pos / 33.33);
		profile.vel = 0.4;  //回転台の速度の変更
		profile.acc = 0.1;  //回転台の加速度の変更
		panAxis->SetProfile(profile);
	}
	tiltAxis->GetProfile(profile);
	if (fabs(profile.pos) < 0.15 && abs(tilt_angle) > 0.15*M_PI / 180. /*&& abs(dy) > 5*/)
	{
		profile.pos = PMDUtils::RadsToRevs(tilt_angle) + PMDUtils::DegsToRevs(tilt_pos / 33.33);//0ms
		profile.vel = 0.4;  //回転台の速度の変更
		profile.acc = 0.1;  //回転台の加速度の変更
		tiltAxis->SetProfile(profile); //16ms
	}
	start = clock();
	biclops.Move(axisMask, 0);//48ms
	end = clock();
	//printf("%d[ms]\n",end-start);
}

