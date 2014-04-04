/*
 * Rewitten by Yoshiaki Mizuchi on 2014-01-13
 *
 */

#pragma once

#include <TLD.h>
#include "../tld/Gui.h"
#include "../tld/Trajectory.h"

using namespace cv;

enum Retval
{
	PROGRAM_EXIT = 0,
	SUCCESS      = 1
};

class RobotTLD
{
public:

	RobotTLD();
	~RobotTLD();

	tld::TLD *tld;
	tld::Gui *gui;

	// Configure
	bool       showOutput;
	bool       showTrajectory;
	int        trajectoryLength;
	double     threshold;
	bool       saveImages;
	const char *saveImageDir;
	bool       exportModelAfterRun;
	const char *modelExportFile;
	bool       loadModel;
	const char *modelPath;
	int        seed;
	bool       selectManually;
	int        *initialBB;

	// Image frame number
	unsigned int framenum;

	// Keyboard input
	char key;

	// Trajectory
	tld::Trajectory trajectory;

	// Image
	IplImage *img;
	Mat      gray;

	// Flag
	bool reuseFrameOnce;
	bool skipProcessingOnce;

	// Time
	double tic;
	double fps;

	// Configure
	void configure();

	// Initialize
	void init( IplImage *_img );

	// Main loop
	void doWork( IplImage *_img );

	// Boundary Box
	void selectBB();
	void setObject( cv::Rect *rect );

	// Keyboard function
	void keyfunc();

	// Result
	void drawOutput( int showOutput );

	// Result image
	void saveResultImages();

	// Frame per sec.
	void   tickCountBegin();
	double tickCountEnd();

	// Detection point
	CvPoint detectionPoint;
};

