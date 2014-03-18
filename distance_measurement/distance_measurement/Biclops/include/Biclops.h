#if !defined BICLOPS_H
#define BICLOPS_H

#include <time.h>           // for clock_t and clock
#include <list>
using namespace std;

//#include <stdio.h>          // for FILE defn
#include <cstdio>          // for FILE defn

#include "PMDAxisControl.h"

class Biclops {
public:
    enum Axes { Pan,Tilt,Roll,Verge};
    enum {  PanMask     = 1, 
            TiltMask    = 1<<1, 
            RollMask    = 1<<2, 
            VergeMask   = 1<<3,
            AllAxesMask = PanMask+TiltMask+RollMask+VergeMask};


    Biclops();	//コンストラクタ定義していないから、いれるとエラーになる

    // Load configuration information from the supplied file, connect to 
    // the controller, and populate axes with configuration parameters.
    // This method provides a single call to prepare the controller and
    // interface for axis control.
    bool Initialize(const char *fileName);
    bool IsInitialized() {return hasBeenInitialized;};

    // Get access to the specified axis.
    PMDAxisControl *GetAxis(int axis);
    PMDAxisControl *GetAxis(const char *axis);

    // Axis motion control
    bool HomeAxes(int axes, bool forceHoming = false);
    bool Move(int axes, long waitPeriod = 100);

    // Returns true if any axis of Biclops is powered.
    bool AnAxisIsPowered();

    void SetDebugLevel(int level);

private:

    PMDAxisControl *axes[4];

    bool allAxesOnOneController;
    bool hasBeenInitialized;
};
#endif

