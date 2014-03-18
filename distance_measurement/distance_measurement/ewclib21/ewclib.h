// Easy Web Camera LIBrary "ewclib.h"  by I.N.
// OS:Windows XP/Vista/7
// Compiler:Visual C++ 2008 Professional

// 2010/04/15 ver.1.9 EWC_GetLastMessage():Unicode/マルチバイトの両対応化
// 2010/05/04         開始
// 2010/05/06         EWC_Open()/EWC_Close()仕様変更．
// 2010/05/06         EWC_Run()/EWC_Stop()追加．
// 2010/05/08         EWC_CloseAll()追加．
// 2010/05/13 ver.2.0 完成
// 2012/02/28 ver.2.1 メモリ解放時のメモリリークを修正

#pragma once
#define EWCLIB_H

#include <dshow.h>
#pragma include_alias( "dxtrans.h", "qedit.h" )
#define __IDxtCompositor_INTERFACE_DEFINED__
#define __IDxtAlphaSetter_INTERFACE_DEFINED__
#define __IDxtJpeg_INTERFACE_DEFINED__
#define __IDxtKey_INTERFACE_DEFINED__
#include "qedit.h"
#pragma comment(lib,"strmiids.lib")

#include <math.h>	//for floor()

#ifndef EWC_TYPE
	#ifdef _CV_H_
		#define EWC_TYPE MEDIASUBTYPE_RGB24
	#else
		#ifdef __OPENCV_CV_H__
			#define EWC_TYPE MEDIASUBTYPE_RGB24
		#else
			#define EWC_TYPE MEDIASUBTYPE_RGB32
		#endif
	#endif
#endif

#ifndef min
	#define min(a,b) ((a)<(b)?(a):(b))
#endif
#ifndef max
	#define max(a,b) ((a)>(b)?(a):(b))
#endif

#ifndef EWC_NCAMMAX
#define EWC_NCAMMAX 8	//カメラの最大認識数
#endif

int ewc_cominit=0;	//COM初期化フラグ(1なら終了処理を行う)
int ewc_ncam=-1;	//カメラ接続数
int ewc_order[EWC_NCAMMAX];	//初期化した番号の順番
int ewc_ordercnt=0;	//ewc_order[]のためのカウンタ
HRESULT ewc_hr;

#define EWC_RUN_TIMEOUT		3000
#define EWC_STOP_TIMEOUT	3000
#define EWC_RETRYTIMES		3

#define EWC_VPAMPMAX	10
#define EWC_CAMCTLMAX	7
#define EWC_ITEMMAX		(EWC_VPAMPMAX+EWC_CAMCTLMAX)

#define ewc_release(x) {if(x)x->Release();x=0;}

//構造体の定義
struct ewc_struct{
	int wx;
	int wy;
	double fps;
	int device;
	GUID mstype;
	volatile int init;
	volatile int stop;
	volatile int errcode;
	int *pbuf;
	int *buffer;
	volatile long bufsize;
	volatile double stime;	//サンプル時刻(s)
	volatile double ftime;	//フレーム周期(s)
	int vflag[EWC_ITEMMAX];
	IGraphBuilder *pGraph;
	IBaseFilter *pF;
	ISampleGrabber *pGrab;
	ICaptureGraphBuilder2 *pBuilder;
	IBaseFilter *pCap;
	IAMVideoProcAmp *pVPAmp;
	IAMCameraControl *pCamCtl;
	IMediaControl *pMediaControl;
	IAMStreamConfig *pConfig;
	IMoniker *pMoniker;
	IEnumMoniker *pEnum;
	ICreateDevEnum *pDevEnum;
	AM_MEDIA_TYPE *pmt;
	AM_MEDIA_TYPE mt;
	IPin *pSrcOut;
	IPin *pSGrabIn;
	IMediaEvent *pMediaEvent;
};

ewc_struct ewc_s[EWC_NCAMMAX];

//コールバック関数の定義
class ewc_SampleGrabberCB :public ISampleGrabberCB
{
public:
	STDMETHODIMP_(ULONG) AddRef()
	{
		return 2;
	}
	STDMETHODIMP_(ULONG) Release()
	{
		return 1;
	}
	STDMETHODIMP QueryInterface(REFIID riid, void ** ppv)
	{
		if(riid==IID_ISampleGrabberCB || riid==IID_IUnknown){
			*ppv= (void *)static_cast<ISampleGrabberCB*>(this);
			return NOERROR;
		}
		return E_NOINTERFACE;
	}
	STDMETHODIMP SampleCB(double SampleTime, IMediaSample *pSample)
	{
		return S_OK;
	}
	//フレーム毎に呼ばれる関数
	STDMETHODIMP BufferCB(double dblSampleTime, BYTE *pBuffer, long lBufferSize)
	{
		ewc_s[i].bufsize= lBufferSize;
		int wx= ewc_s[i].wx;
		int wy= ewc_s[i].wy;
		int byte= lBufferSize/wy;
		//画像の上下を逆にしてコピー
		for(int y=0; y<wy; y++){
			memcpy((unsigned char *)ewc_s[i].pbuf+(wy-1-y)*byte, pBuffer+y*byte,byte);
		}
		ewc_s[i].ftime= dblSampleTime - ewc_s[i].stime;
		ewc_s[i].stime= dblSampleTime;
		return S_OK;
	}
	//コンストラクタ	
	ewc_SampleGrabberCB(int num)
	{
		i=num;
		ewc_s[i].pbuf=ewc_s[i].buffer;
		ewc_s[i].bufsize=0;
		tm=ewc_s[i].stime=0.;
	}
	//デストラクタ
	~ewc_SampleGrabberCB()
	{
	}
	void TimeSet(double *t)
	{
		*t=tm=ewc_s[i].stime;
	}
	int IsCaptured(void)
	{
		if(tm!=ewc_s[i].stime) return 1;
		else return 0;
	}
private:
	int i;
	double tm;
};

ewc_SampleGrabberCB *ewc_pSampleGrabberCB[EWC_NCAMMAX];

//IAMVideoProcAmp
#define EWC_BRIGHTNESS				0
#define EWC_CONTRAST				1
#define EWC_HUE						2
#define EWC_SATURATION				3
#define EWC_SHARPNESS				4
#define EWC_GAMMA					5
#define EWC_COLORENABLE				6
#define EWC_WHITEBALANCE			7
#define EWC_BACKLIGHTCOMPENSATION	8
#define EWC_GAIN					9
//IAMCameraControl
#define EWC_PAN						10
#define EWC_TILT					11
#define EWC_ROLL					12
#define EWC_ZOOM					13
#define EWC_EXPOSURE				14
#define EWC_IRIS					15
#define EWC_FOCUS					16

//カメラ番号のチェック(戻り値：0ならカメラnumは有効)
int numCheck(int num)
{
	if(num<0 || num>=EWC_NCAMMAX) return 1;
	if(!ewc_s[num].init) return 2;
	return 0;
}

//カメラ台数を返す
int EWC_GetCamera(void)
{
	if(ewc_ncam==-1) return 0;
	return ewc_ncam;
}

//カメラ(番号:num)のフレームバッファサイズ(単位:バイト)を返す
int EWC_GetBufferSize(int num)
{
	if(numCheck(num)) return 0;
	return ewc_s[num].bufsize;
}

//フィルタのピンを取得する
IPin *ewc_GetPin(IBaseFilter *pFilter, PIN_DIRECTION PinDir)
{
	IEnumPins *pEnum;
	IPin *pPin=0;

	ewc_hr= pFilter->EnumPins(&pEnum);
	if(ewc_hr!=S_OK) return NULL;

	while(pEnum->Next(1,&pPin,0)==S_OK){
		PIN_DIRECTION PinDirThis;
		pPin->QueryDirection(&PinDirThis);
		if(PinDir==PinDirThis) break;
		pPin->Release();
	}
	pEnum->Release();
	return pPin;
}

//カメラ(番号:num)の画像取得
int EWC_GetImage(int num, void *buffer)
{
	if(numCheck(num)) return 1;
	memcpy(buffer,ewc_s[num].pbuf,ewc_s[num].bufsize);
	return 0;
}

//バッファアドレスを変更
int EWC_SetBuffer(int num, void *buffer)
{
	if(numCheck(num)) return 1;
	ewc_s[num].pbuf=(int *)buffer;
	return 0;
}

//現在のバッファアドレスを取得
int EWC_GetBuffer(int num, void **buffer)
{
	if(numCheck(num)) return 1;
	*buffer=ewc_s[num].pbuf;
	return 0;
}


//設定値を読み出す
double EWC_GetValue(int num, int prop, int *mode=NULL)
{
	if(numCheck(num)) return -1.0;
	if(prop<0 || prop>=EWC_ITEMMAX) return -1.0;
	if(!ewc_s[num].vflag[prop]) return -1.0;

	long Min,Max,Step,Default,Flags,Val;   

	if(prop<EWC_VPAMPMAX){
		//IAMVideoProcAmpの取得 pVPAmp
		ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
		//IAMVideoProcAmp
		ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pVPAmp->Get(prop,&Val,&Flags);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pVPAmp);
				return -1.0;
			}
			if(mode) if(Flags & VideoProcAmp_Flags_Auto) *mode=1; else *mode=0;
			double value=(Val-Min)*100.0/(double)(Max-Min);
			ewc_release(ewc_s[num].pVPAmp);
			return value;
		}else{
			ewc_release(ewc_s[num].pVPAmp);
			return -1.0;
		}
	}else{
		//IAMCameraControlの取得 pCamCtl
		ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
		//IAMCameraControl
		prop-=EWC_VPAMPMAX;
		ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pCamCtl->Get(prop,&Val,&Flags);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pCamCtl);
				return -1.0;
			}
			if(mode) if(Flags & CameraControl_Flags_Auto) *mode=1; else *mode=0;
			double value=(Val-Min)*100.0/(double)(Max-Min);
			ewc_release(ewc_s[num].pCamCtl);
			return value;
		}else{
			ewc_release(ewc_s[num].pCamCtl);
			return -1.0;
		}
	}
}

//制御を手動モードにし，設定値を変更する
int EWC_SetValue(int num, int prop, double value)
{
	if(numCheck(num)) return 1;
	if(prop<0 || prop>=EWC_ITEMMAX) return 2;
	if(!ewc_s[num].vflag[prop]) return 3;

	long Min, Max, Step, Default, Flags, Val;   

	if(prop<EWC_VPAMPMAX){
		//IAMVideoProcAmpの取得 pVPAmp
		ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
		//IAMVideoProcAmp
		ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			Val=(long) ((value/100.0*(Max-Min))+Min);
			Val=min(max(Val,Min),Max);
			ewc_hr= ewc_s[num].pVPAmp->Set(prop,Val,VideoProcAmp_Flags_Manual);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pVPAmp);
				return 5;
			}
			ewc_release(ewc_s[num].pVPAmp);
		}else{
			ewc_release(ewc_s[num].pVPAmp);
			return 4;
		}
	}else{
		//IAMCameraControlの取得 pCamCtl
		ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
		//IAMCameraControl
		prop-=EWC_VPAMPMAX;
		ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			Val=(long) ((value/100.0*(Max-Min))+Min);
			Val=min(max(Val,Min),Max);
			ewc_hr= ewc_s[num].pCamCtl->Set(prop,Val,CameraControl_Flags_Manual);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pCamCtl);
				return 5;
			}
			ewc_release(ewc_s[num].pCamCtl);
		}else{
			ewc_release(ewc_s[num].pCamCtl);
			return 4;
		}
	}
	return 0;
}

//設定を初期値に戻す
int EWC_SetDefault(int num, int prop)
{
	if(numCheck(num)) return 1;
	if(prop<0 || prop>=EWC_ITEMMAX) return 2;
	if(!ewc_s[num].vflag[prop]) return 3;

	long Min, Max, Step, Default, Flags, Val;   

	if(prop<EWC_VPAMPMAX){
		//IAMVideoProcAmpの取得 pVPAmp
		ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
		//IAMVideoProcAmp
		ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pVPAmp->Get(prop,&Val,&Flags);
			ewc_hr= ewc_s[num].pVPAmp->Set(prop,Default,Flags);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pVPAmp);
				return 5;
			}
			ewc_release(ewc_s[num].pVPAmp);
		}else{
			ewc_release(ewc_s[num].pVPAmp);
			return 4;
		}
	}else{
		//IAMCameraControlの取得 pCamCtl
		ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
		//IAMCameraControl
		prop-=EWC_VPAMPMAX;
		ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pCamCtl->Get(prop,&Val,&Flags);
			ewc_hr= ewc_s[num].pCamCtl->Set(prop,Default,Flags);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pCamCtl);
				return 5;
			}
			ewc_release(ewc_s[num].pCamCtl);
		}else{
			ewc_release(ewc_s[num].pCamCtl);
			return 4;
		}
	}
	return 0;
}

//制御を自動モードにする
int EWC_SetAuto(int num, int prop)
{
	if(numCheck(num)) return 1;
	if(prop<0 || prop>=EWC_ITEMMAX) return 2;
	if(!ewc_s[num].vflag[prop]) return 3;

	long Min, Max, Step, Default, Flags, Val;   

	if(prop<EWC_VPAMPMAX){
		//IAMVideoProcAmpの取得 pVPAmp
		ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
		//IAMVideoProcAmp
		ewc_hr= ewc_s[num].pVPAmp->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pVPAmp->Get(prop,&Val,&Flags);
			ewc_hr= ewc_s[num].pVPAmp->Set(prop,Val,VideoProcAmp_Flags_Auto);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pVPAmp);
				return 5;
			}
			ewc_release(ewc_s[num].pVPAmp);
		}else{
			ewc_release(ewc_s[num].pVPAmp);
			return 4;
		}
	}else{
		//IAMCameraControlの取得 pCamCtl
		ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
		//IAMCameraControl
		prop-=EWC_VPAMPMAX;
		ewc_hr= ewc_s[num].pCamCtl->GetRange(prop,&Min,&Max,&Step,&Default,&Flags);
		if(ewc_hr==S_OK){
			ewc_hr= ewc_s[num].pCamCtl->Get(prop,&Val,&Flags);
			ewc_hr= ewc_s[num].pCamCtl->Set(prop,Val,CameraControl_Flags_Auto);
			if(ewc_hr!=S_OK){
				ewc_release(ewc_s[num].pCamCtl);
				return 5;
			}
			ewc_release(ewc_s[num].pCamCtl);
		}else{
			ewc_release(ewc_s[num].pCamCtl);
			return 4;
		}
	}
	return 0;
}

#pragma comment(lib,"Quartz.lib")

//最後のエラーメッセージを取得する
//s:文字列格納先  size:領域sのサイズ
void EWC_GetLastMessage(char *s, int size)
{
	wchar_t w[MAX_ERROR_TEXT_LEN];
	AMGetErrorTextW(ewc_hr,w,MAX_ERROR_TEXT_LEN);	//1.9
	WideCharToMultiByte(CP_ACP,0,w,-1,s,size,NULL,NULL);
}

//キャプチャの停止
int EWC_Stop(int num)
{
	if(numCheck(num)) return 1;

	//stop
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaControl,(void **)&ewc_s[num].pMediaControl);
	if(ewc_hr==S_OK) ewc_s[num].pMediaControl->Stop(); else return 2;
	ewc_release(ewc_s[num].pMediaControl);

	long evCode;
	ewc_hr= ewc_s[num].pMediaEvent->WaitForCompletion(EWC_STOP_TIMEOUT,&evCode);
	if(ewc_hr!=S_OK){
		if(ewc_hr==E_ABORT) return 3;
	}
	return 0;
}

//キャプチャの再開
int EWC_Run(int num)
{
	if(numCheck(num)) return 1;

	//run
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaControl,(void **)&ewc_s[num].pMediaControl);
	if(ewc_hr==S_OK) ewc_hr= ewc_s[num].pMediaControl->Run(); else return 2;
	ewc_release(ewc_s[num].pMediaControl);

	long evCode;
	ewc_hr= ewc_s[num].pMediaEvent->WaitForCompletion(EWC_RUN_TIMEOUT,&evCode);
	if(ewc_hr!=S_OK){
		if(ewc_hr==E_ABORT) return 3;
	}
	return 0;
}

//プロパティページを表示させる
int EWC_PropertyPage(int num)
{
	if(numCheck(num)) return 1;

	ISpecifyPropertyPages *pProp=0;

	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_ISpecifyPropertyPages, (void **)&pProp);
	if(ewc_hr!=S_OK) return 2;

	CAUUID caGUID;
	pProp->GetPages(&caGUID);
	ewc_release(pProp);

	FILTER_INFO FilterInfo;
	ewc_hr= ewc_s[num].pCap->QueryFilterInfo(&FilterInfo); 
	if(ewc_hr!=S_OK) return 3;

	IUnknown *pFilterUnk=0;
	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_IUnknown,(void **)&pFilterUnk);
	if(ewc_hr!=S_OK){
		ewc_release(FilterInfo.pGraph);
		return 4;
	}

	OleCreatePropertyFrame(
		HWND_DESKTOP,		// Parent window
		0,0,				// Reserved
		FilterInfo.achName,	// Caption for the dialog box
		1,					// Number of objects (just the filter)
		&pFilterUnk,		// Array of object pointers. 
		caGUID.cElems,		// Number of property pages
		caGUID.pElems,		// Array of property page CLSIDs
		0,					// Locale identifier
		0, NULL				// Reserved
	);

	ewc_release(pFilterUnk);
	ewc_release(FilterInfo.pGraph);
	CoTaskMemFree(caGUID.pElems);
	return 0;
}

//新しい画像が到着したかどうか
//  num:カメラ番号  t:取得時刻(秒)
int EWC_IsCaptured(int num, double *t=NULL)
{
	if(numCheck(num)) return 0;

	if(ewc_pSampleGrabberCB[num]->IsCaptured()){
		double tt;
		if(!t) t=&tt;
		ewc_pSampleGrabberCB[num]->TimeSet(t);
		return 1;
	}
	return 0;
}

//画像変換(32ビット->24ビット)
void EWC_Cnv32to24(unsigned char *dst, unsigned int *src, int pxl)
{
	unsigned char R,G,B;
	unsigned int ui;

	for(int n=0; n<pxl; n++){
		ui=*src++;
		B=ui;
		G=(ui>>8);
		R=(ui>>16);
		*(dst+0) = B;
		*(dst+1) = G;
		*(dst+2) = R;
		dst+=3;
	}
}

//画像変換(24ビット->32ビット)
void EWC_Cnv24to32(unsigned int *dst, unsigned char *src, int pxl)
{
	unsigned char R,G,B;

	for(int n=0; n<pxl; n++){
		B = *(src+0);
		G = *(src+1);
		R = *(src+2);
		src+=3;
		*dst++ = (R<<16) | (G<<8) | B;
	}
}

//メモリ解放 v2.1
void ewc_freememory(int num)
{
	ewc_release(ewc_s[num].pMediaEvent);
	ewc_release(ewc_s[num].pMediaControl);
	ewc_release(ewc_s[num].pCamCtl);
	ewc_release(ewc_s[num].pVPAmp);
	ewc_release(ewc_s[num].pGrab);
	ewc_release(ewc_s[num].pF);
	ewc_release(ewc_s[num].pBuilder);
	ewc_release(ewc_s[num].pCap);
	//ewc_release(ewc_pSampleGrabberCB[num]); //削除 v2.1
	if(ewc_s[num].buffer){
		delete[] ewc_s[num].buffer;
		ewc_s[num].buffer=0;
	}
	ewc_release(ewc_s[num].pGraph);
	//追加 v2.1
	if(ewc_pSampleGrabberCB[num]){
		delete ewc_pSampleGrabberCB[num];
		ewc_pSampleGrabberCB[num]=0;
	}
}

//使用開始
void ewc_Open(int num)
{
	int errcode, retryflag, retrytime=EWC_RETRYTIMES;

cont:
	retryflag=0;
	errcode=0;

	//フィルタグラフマネージャ作成 pGraph
	ewc_hr= CoCreateInstance(CLSID_FilterGraph,0,CLSCTX_INPROC_SERVER,IID_IGraphBuilder,(void **)&ewc_s[num].pGraph);
	if(ewc_hr!=S_OK){errcode=3; goto fin;}

	//システムデバイス列挙子の作成
	ewc_hr= CoCreateInstance(CLSID_SystemDeviceEnum,0,CLSCTX_INPROC_SERVER,IID_ICreateDevEnum,(void **)&ewc_s[num].pDevEnum);
	if(ewc_hr!=S_OK){errcode=4; goto fin;}

	//列挙子の取得
	ewc_hr= ewc_s[num].pDevEnum->CreateClassEnumerator(CLSID_VideoInputDeviceCategory,&ewc_s[num].pEnum,0);
	if(ewc_hr!=S_OK){
		//ESP_Printf("No driver\n");
		errcode=5; goto fin;
	}

	//モニカの取得
	ULONG cFetched;
	wchar_t SrcName[32];
	int n=0,m=0;

	//char displayname[512];

	for(int i=0; i<EWC_NCAMMAX; i++){
		if(ewc_s[num].pEnum->Next(1,&ewc_s[num].pMoniker,&cFetched)==S_OK){
			
			//DisplayNameの取得
			LPOLESTR strMonikerName=0;
			ewc_hr= ewc_s[num].pMoniker->GetDisplayName(NULL,NULL,&strMonikerName);
			if(ewc_hr!=S_OK){errcode=6; goto fin;}

			//WideCharToMultiByte(CP_ACP,0,strMonikerName,-1,displayname,sizeof(displayname),0,0);
			//ESP_Printf("displayname(%d):%s\n",i,displayname);

			//DisplayNameに'@device:pnp'があれば登録
			if(wcsstr(strMonikerName,L"@device:pnp")){
				if((ewc_s[num].device==-1 && n==num) || (ewc_s[num].device!=-1 && n==ewc_s[num].device)){
					//オブジェクト初期化 pCap
					ewc_s[num].pMoniker->BindToObject(0,0,IID_IBaseFilter,(void **)&ewc_s[num].pCap);
					//グラフにフィルタを追加
					swprintf_s(SrcName,32,L"Video Capture %d",num);
					ewc_hr= ewc_s[num].pGraph->AddFilter(ewc_s[num].pCap, SrcName);
					if(ewc_hr!=S_OK){errcode=7; goto fin;}
					m++;
				}
				n++;
			}
			ewc_release(ewc_s[num].pMoniker);
		}
	}

	if(ewc_ncam==-1) ewc_ncam=n;

	ewc_release(ewc_s[num].pEnum);
	ewc_release(ewc_s[num].pDevEnum);

	//No camera
	if(!ewc_ncam){errcode=8; goto fin;}
	if(!m){errcode=9; goto fin;}

	//ESP_Printf("camera=%d\n",ewc_ncam);

	//キャプチャビルダの作成 pBuilder
	CoCreateInstance(CLSID_CaptureGraphBuilder2,0,CLSCTX_INPROC_SERVER,
		IID_ICaptureGraphBuilder2,(void **)&ewc_s[num].pBuilder);
	ewc_hr= ewc_s[num].pBuilder->SetFiltergraph(ewc_s[num].pGraph);
	if(ewc_hr!=S_OK){errcode=10; goto fin;}
	
	//IAMStreamConfigインタフェースの取得
	ewc_hr= ewc_s[num].pBuilder->FindInterface(&PIN_CATEGORY_CAPTURE,&MEDIATYPE_Video,
		ewc_s[num].pCap,IID_IAMStreamConfig,(void**)&ewc_s[num].pConfig);
	if(ewc_hr!=S_OK){errcode=11; goto fin;}

	//画像サイズ，フレームレートの設定
	ewc_hr= ewc_s[num].pConfig->GetFormat(&ewc_s[num].pmt);
	VIDEOINFOHEADER *vh = (VIDEOINFOHEADER*)ewc_s[num].pmt->pbFormat;
	vh->bmiHeader.biWidth =ewc_s[num].wx;
	vh->bmiHeader.biHeight=ewc_s[num].wy; 
	vh->AvgTimePerFrame= (REFERENCE_TIME)floor((10000000.0/ewc_s[num].fps+0.5));
	ewc_hr= ewc_s[num].pConfig->SetFormat(ewc_s[num].pmt);
	if(ewc_hr!=S_OK){errcode=12; goto fin;}
	ewc_release(ewc_s[num].pConfig);

	//サンプルグラバの生成 pF,pGrab
	CoCreateInstance(CLSID_SampleGrabber,0,CLSCTX_INPROC_SERVER,IID_IBaseFilter,(LPVOID *)&ewc_s[num].pF);
	ewc_hr= ewc_s[num].pF->QueryInterface(IID_ISampleGrabber,(void **)&ewc_s[num].pGrab);
	if(ewc_hr!=S_OK){errcode=13; goto fin;}

	//メディアタイプの設定
	ZeroMemory(&ewc_s[num].mt,sizeof(AM_MEDIA_TYPE));
	ewc_s[num].mt.majortype= MEDIATYPE_Video;
	//Qcam Pro 4000では次の値が設定可能だった．
	//MEDIASUBTYPE_RGB4
	//MEDIASUBTYPE_RGB8
	//MEDIASUBTYPE_RGB565
	//MEDIASUBTYPE_RGB555
	//MEDIASUBTYPE_RGB24
	//MEDIASUBTYPE_RGB32
	//MEDIASUBTYPE_ARGB32
	ewc_s[num].mt.subtype= ewc_s[num].mstype;
	ewc_s[num].mt.formattype= FORMAT_VideoInfo;
	ewc_hr= ewc_s[num].pGrab->SetMediaType(&ewc_s[num].mt);
	if(ewc_hr!=S_OK){errcode=14; goto fin;}
	//フィルタグラフへの追加
	wchar_t GrabName[32];
	swprintf_s(GrabName,32,L"Grabber %d",num);
	ewc_hr= ewc_s[num].pGraph->AddFilter(ewc_s[num].pF, GrabName);
	if(ewc_hr!=S_OK){errcode=15; goto fin;}

	//サンプルグラバの接続
	// ピンの取得
	ewc_s[num].pSrcOut= ewc_GetPin(ewc_s[num].pCap,PINDIR_OUTPUT);
	ewc_s[num].pSGrabIn= ewc_GetPin(ewc_s[num].pF,PINDIR_INPUT);
	// ピンの接続
	ewc_hr= ewc_s[num].pGraph->Connect(ewc_s[num].pSrcOut, ewc_s[num].pSGrabIn);
	if(ewc_hr!=S_OK){errcode=16; goto fin;}

	ewc_release(ewc_s[num].pSrcOut);
	ewc_release(ewc_s[num].pSGrabIn);

	//グラバのモード設定
	ewc_hr= ewc_s[num].pGrab->SetBufferSamples(FALSE);
	if(ewc_hr!=S_OK){errcode=17; goto fin;}
	ewc_hr= ewc_s[num].pGrab->SetOneShot(FALSE);
	if(ewc_hr!=S_OK){errcode=18; goto fin;}

	//バッファの確保，コールバック関数の登録 buffer,ewc_pSampleGrabberCB[]
	ewc_s[num].buffer= (int *)new int[ewc_s[num].wx*ewc_s[num].wy];
	ewc_pSampleGrabberCB[num]= new ewc_SampleGrabberCB(num);
	ewc_hr= ewc_s[num].pGrab->SetCallback(ewc_pSampleGrabberCB[num],1);
	if(ewc_hr!=S_OK){errcode=19; goto fin;}

	//IAMVideoProcAmpの取得 pVPAmp
	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_IAMVideoProcAmp,(void **)&ewc_s[num].pVPAmp);
	if(ewc_hr!=S_OK){
		//IAMVideoProcAmpが取得できなければ，サポートしてないとみなす．
		for(int j=0;j<EWC_VPAMPMAX;j++){
			//not supported
			ewc_s[num].vflag[j]=0;
		}
	}else{
		for(int j=0;j<EWC_VPAMPMAX;j++){
			long Min, Max, Step, Default, Flags;   
			ewc_hr= ewc_s[num].pVPAmp->GetRange(j,&Min,&Max,&Step,&Default,&Flags);
			if(ewc_hr==S_OK){
				ewc_s[num].vflag[j]=1;
			}else{
				//not supported
				ewc_s[num].vflag[j]=0;
			}
		}
	}
	ewc_release(ewc_s[num].pVPAmp);

	//IAMCameraControlの取得 pCamCtl
	ewc_hr= ewc_s[num].pCap->QueryInterface(IID_IAMCameraControl,(void **)&ewc_s[num].pCamCtl);
	if(ewc_hr!=S_OK){
		//IAMCameraControlが取得できなければ，サポートしてないとみなす．
		for(int j=0;j<EWC_CAMCTLMAX;j++){
			//not supported
			ewc_s[num].vflag[j+EWC_VPAMPMAX]=0;
		}
	}else{
		for(int j=0;j<EWC_CAMCTLMAX;j++){
			long Min, Max, Step, Default, Flags;   
			ewc_hr= ewc_s[num].pCamCtl->GetRange(j,&Min,&Max,&Step,&Default,&Flags);
			if(ewc_hr==S_OK){
				ewc_s[num].vflag[j+EWC_VPAMPMAX]=1;
			}else{
				//not supported
				ewc_s[num].vflag[j+EWC_VPAMPMAX]=0;
			}
		}
	}
	ewc_release(ewc_s[num].pCamCtl);

	//IMediaEventの取得 pMediaEvent
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaEvent,(LPVOID *)&ewc_s[num].pMediaEvent);
	if(ewc_hr!=S_OK){errcode=20; goto fin;}

	//キャプチャ開始 pMediaControl
	ewc_hr= ewc_s[num].pGraph->QueryInterface(IID_IMediaControl,(void **)&ewc_s[num].pMediaControl);
	if(ewc_hr!=S_OK){errcode=21; goto fin;}
	ewc_hr= ewc_s[num].pMediaControl->Run();
	if(ewc_hr!=S_OK){errcode=22; retryflag=1; goto fin;}
	ewc_release(ewc_s[num].pMediaControl);

	//１回以上サンプルされるまで待機
	long evCode;
	ewc_s[num].pMediaEvent->WaitForCompletion(EWC_RUN_TIMEOUT,&evCode);
	if(ewc_hr!=S_OK){
		if(ewc_hr==E_ABORT){errcode=23; retryflag=1; goto fin;}
	}
	int t0=GetTickCount();
	do{
		if((GetTickCount()-t0)>EWC_RUN_TIMEOUT){errcode=24; retryflag=1; goto fin;}
	}while(ewc_s[num].bufsize==0);

fin:
	if(errcode){
		//ESP_Printf("errcode=%d\n",errcode);
		ewc_release(ewc_s[num].pDevEnum);
		ewc_release(ewc_s[num].pEnum);
		ewc_release(ewc_s[num].pMoniker);
		ewc_release(ewc_s[num].pConfig);

		ewc_freememory(num);

		//正常に接続されるまでリトライ
		if(retryflag) if(--retrytime) goto cont;
	}else{
		ewc_s[num].init=1;
		ewc_order[ewc_ordercnt++]=num;
	}

	ewc_s[num].errcode=errcode;
}

//使用開始
int EWC_Open(int num, int wx, int wy, double fps, int device=-1, GUID mstype=EWC_TYPE)
{
	if(num<0 || num>=EWC_NCAMMAX) return 1;

	//COMの初期化
	if(!ewc_cominit && ewc_ncam==-1){
		ewc_hr= CoInitializeEx(NULL,COINIT_MULTITHREADED);
		if(ewc_hr==S_OK) ewc_cominit=1;	//成功したらフラグを立てる
	}

	//構造体の初期化
	if(ewc_ncam==-1){
		for(int i=0;i<EWC_NCAMMAX;i++){
			ZeroMemory(&ewc_s[i],sizeof(ewc_struct));
		}
	}

	if(ewc_s[num].init) return 2;

	ewc_s[num].wx=wx;
	ewc_s[num].wy=wy;
	ewc_s[num].fps=fps;
	ewc_s[num].device=device;
	ewc_s[num].mstype=mstype;
	ewc_s[num].errcode=-1;

	ewc_Open(num);

	return ewc_s[num].errcode;
}

//終了処理
int EWC_Close(int num)
{
	if(numCheck(num)) return 1;

	//キャプチャ停止
	int r=EWC_Stop(num);
	if(r) return 2;

	//メモリ解放
	ewc_freememory(num);
	ewc_s[num].init=0;

	if(ewc_ordercnt){
		if(ewc_order[ewc_ordercnt-1]==num){
			ewc_ordercnt--;
		}
	}

	//すべて終了ならCOM終了
	int c=0;
	for(int i=0;i<EWC_NCAMMAX;i++){
		c += ewc_s[i].init;
	}
	if(c==0){
		if(ewc_cominit){
			CoUninitialize();
			ewc_cominit=0;
		}
		ewc_ncam=-1;
	}
	return 0;
}

//終了処理（すべて）
int EWC_CloseAll(void)
{
	int r=0;
	while(ewc_ordercnt>0){
		r+=EWC_Close(ewc_order[--ewc_ordercnt]);
	}
	return r;
}
