/*
 * Rewritten by Ysohiaki Mizuchi on 2014-01-13
 *
 */

/*  Copyright 2011 AIT Austrian Institute of Technology
 *
 *   This file is part of OpenTLD.
 *
 *   OpenTLD is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   OpenTLD is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * MainX.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay
 */

#include "../tld/RobotTLD.h"

#include "../tld/Gui.h"
#include <TLDUtil.h>

RobotTLD::RobotTLD()
{
	tld = new tld::TLD();
	gui = new tld::Gui();

	showOutput          = true;
	saveImageDir        = NULL;
	threshold           = 0.5;
	showTrajectory      = false;
	trajectoryLength    = 0;
	selectManually      = 0;
	initialBB           = NULL;
	loadModel           = false;
	exportModelAfterRun = false;
	modelExportFile     = NULL;
	seed                = 0;
	modelPath           = NULL;

	framenum = 0;
	key = 0;
}

RobotTLD::~RobotTLD()
{
	if( exportModelAfterRun && modelExportFile != NULL ){
		tld->writeToFile(modelExportFile);
	}

	delete tld;
	delete gui;
}

void RobotTLD::configure()
{
	/*
	 * Parameters
	 *   trackerEnabled      : 追跡を行うか(false時は検出のみ)
	 *   showOutput          : 結果表示の有無
	 *   showTrajectory      : 追跡時の軌跡を表示するか
	 *   trajectryLength     : 表示する軌跡の長さ
	 *   saveImages          : 出力画像を保存するか
	 *   saveDir             : 出力画像を保存するディレクトリパス
	 *   threshold           : 信頼性の閾値(学習をするかどうかの判定に利用されているはず)
	 *   alternating         : (不明：切り替えると追跡に失敗した時の検出の振る舞いに違いが出そうです)
	 *   learningEnabled     : 学習を行うか
	 *   selectManually      : 起動時に手動で領域を選択する処理を実行するか
	 *   exportModelAfterRun : 終了時にモデルデータを出力するか
	 *   modelExportFile     : 出力モデルデータのファイルパス
	 *   loadModel           : モデルを読み込むか
	 *   modelPath           : 入力モデルデータのファイルパス
	 *   seed                : 乱数のシード
	 */

	tld->trackerEnabled  = true;
	showOutput           = true;
	showTrajectory       = false;
	trajectoryLength     = 30;
	saveImages           = false;
	saveImageDir         = "img";
	threshold            = 0.7;
	tld->alternating     = false;
	tld->learningEnabled = true;
	selectManually       = false;
	exportModelAfterRun  = false;
	modelExportFile      = "model/sample.dat";
	loadModel            = false;
	modelPath            = "model/sample.dat";
	seed                 = 0;
}

void RobotTLD::init( IplImage *_img )
{
	//configure();

	srand(seed);

	if(showOutput)
	{
		gui->init();
	}

	img = cvCloneImage( _img );
	gray = Mat(img->height, img->width, CV_8UC1);
	cvtColor(cvarrToMat(img), gray, CV_BGR2GRAY);
	framenum++;

	tld->detectorCascade->imgWidth = gray.cols;
	tld->detectorCascade->imgHeight = gray.rows;
	tld->detectorCascade->imgWidthStep = gray.step;

	if(showTrajectory)
	{
		trajectory.init(trajectoryLength);
	}

	if(selectManually)
	{
		selectBB();
	}

	reuseFrameOnce = false;
	skipProcessingOnce = false;

	if(loadModel && modelPath != NULL)
	{
		tld->readFromFile(modelPath);
		reuseFrameOnce = true;
	}
	else if(initialBB != NULL)
	{
		Rect bb = tld::tldArrayToRect(initialBB);

		printf("Starting at %d %d %d %d\n", bb.x, bb.y, bb.width, bb.height);

		tld->selectObject(gray, &bb);
		skipProcessingOnce = true;
		reuseFrameOnce = true;
	}
}

void RobotTLD::selectBB()
{
	CvRect box;

	if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
	{
		return;
	}

	if(initialBB == NULL)
	{
		initialBB = new int[4];
	}

	initialBB[0] = box.x;
	initialBB[1] = box.y;
	initialBB[2] = box.width;
	initialBB[3] = box.height;
}

void RobotTLD::setObject( cv::Rect *rect )
{
	tld->selectObject(gray, rect);
}

void RobotTLD::saveResultImages()
{
	if(saveImageDir != NULL)
	{
		char fileName[256];
		sprintf(fileName, "%s/%.5d.png", saveImageDir, framenum);

		cvSaveImage(fileName, img);
	}
}

void RobotTLD::drawOutput( int showOutput )
{
	if( !showOutput )
	{
		return;
	}

	char string[128];

	char learningString[10] = "";

	if(tld->learning)
	{
		strcpy(learningString, "Learning");
	}

	int confident = (tld->currConf >= threshold) ? 1 : 0;

	sprintf(string, "#%d,Posterior %.2f; fps: %.2f, #numwindows:%d, %s", framenum, tld->currConf, fps, tld->detectorCascade->numWindows, learningString);
	CvScalar yellow = CV_RGB(255, 255, 0);
	CvScalar blue = CV_RGB(0, 0, 255);
	CvScalar black = CV_RGB(0, 0, 0);
	CvScalar white = CV_RGB(255, 255, 255);

	if(tld->currBB != NULL)
	{
		CvScalar rectangleColor = (confident) ? blue : yellow;
		cvRectangle(img, tld->currBB->tl(), tld->currBB->br(), rectangleColor, 8, 8, 0);

		/**
		 * 追加要素　検出中心点の取得
		 */
		this->detectionPoint = cvPoint(tld->currBB->x + tld->currBB->width / 2, tld->currBB->y + tld->currBB->height / 2);

		if(showTrajectory)
		{
			CvPoint center = cvPoint(tld->currBB->x+tld->currBB->width/2, tld->currBB->y+tld->currBB->height/2);
			cvLine(img, cvPoint(center.x-2, center.y-2), cvPoint(center.x+2, center.y+2), rectangleColor, 2);
			cvLine(img, cvPoint(center.x-2, center.y+2), cvPoint(center.x+2, center.y-2), rectangleColor, 2);
			trajectory.addPoint(center, rectangleColor);
		}
	}
	else if(showTrajectory)
	{
		trajectory.addPoint(cvPoint(-1, -1), cvScalar(-1, -1, -1));
	}

	if(showTrajectory)
	{
		trajectory.drawTrajectory(img);
	}

	CvFont font;
	cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, .5, .5, 0, 1, 8);
	cvRectangle(img, cvPoint(0, 0), cvPoint(img->width, 50), black, CV_FILLED, 8, 0);
	cvPutText(img, string, cvPoint(25, 25), &font, white);

	gui->showImage(img);

	keyfunc();

	if(saveImages)
	{
		saveResultImages();
	}
}

void RobotTLD::keyfunc()
{
	key = gui->getKey();

	if(key == 'b')
	{
		tld::ForegroundDetector *fg = tld->detectorCascade->foregroundDetector;

		if(fg->bgImg.empty())
		{
			fg->bgImg = gray.clone();
		}
		else
		{
			fg->bgImg.release();
		}
	}

	if(key == 'c')
	{
		//clear everything
		tld->detectorCascade->release();
		tld->medianFlowTracker->cleanPreviousData();
		tld->currBB = NULL;
	}

	if(key == 'l')
	{
		tld->learningEnabled = !tld->learningEnabled;
		printf("LearningEnabled: %d\n", tld->learningEnabled);
	}

	if(key == 'a')
	{
		tld->alternating = !tld->alternating;
		printf("alternating: %d\n", tld->alternating);
	}

	if(key == 'e')
	{
		tld->writeToFile(modelExportFile);
	}

	if(key == 'i')
	{
		tld->readFromFile(modelPath);
	}

	if(key == 'r')
	{
		CvRect box;

		if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
		{
			return;
		}

		Rect r = Rect(box);

		tld->selectObject(gray, &r);
	}
}

void RobotTLD::tickCountBegin()
{
	tic = (double)cvGetTickCount();
}
double RobotTLD::tickCountEnd()
{
	double toc = (cvGetTickCount() - tic) / cvGetTickFrequency();

	toc = toc / 1000000;

	return 1 / toc;
}

void RobotTLD::doWork( IplImage *_img )
{
	if(!reuseFrameOnce)
	{
		cvReleaseImage(&img);
		img = cvCloneImage( _img );
		framenum++;

		if(img == NULL)
		{
			printf("current image is NULL, assuming end of input.\n");
			return;
		}

		cvtColor(cvarrToMat(img), gray, CV_BGR2GRAY);
	}
	tickCountBegin();

	if(!skipProcessingOnce)
	{
		tld->processImage(cvarrToMat(img));
	}
	else
	{
		skipProcessingOnce = false;
	}

	fps = tickCountEnd();


	/**
	 * 検出点の初期化　検出されなかった場合は-1となる
	 */
	this->detectionPoint.x = -1;
	this->detectionPoint.y = -1;

	drawOutput( showOutput );

	if(reuseFrameOnce)
	{
		reuseFrameOnce = false;
	}
	
	cvReleaseImage(&img);
	img = NULL;
}
