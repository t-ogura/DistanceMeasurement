#pragma once


#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "opencv2/opencv.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/legacy/legacy.hpp"


//#define QVGA


#define CV_LIBPATH_STR "C:/opencv2.4.8/build/x86/vc12/lib/"
#define CV_VERSION_STR CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)
#if _DEBUG
#define CV_EXTENSION_STR "d.lib"
#else
#define CV_EXTENSION_STR ".lib"
#endif

#pragma comment(lib, CV_LIBPATH_STR "opencv_core" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_imgproc" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_highgui" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_objdetect" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_contrib" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_features2d" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_flann" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_legacy" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_ts" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_video" CV_VERSION_STR CV_EXTENSION_STR)
#pragma comment(lib, CV_LIBPATH_STR "opencv_calib3d" CV_VERSION_STR CV_EXTENSION_STR)

#pragma comment(lib, CV_LIBPATH_STR "opencv_nonfree" CV_VERSION_STR CV_EXTENSION_STR)
