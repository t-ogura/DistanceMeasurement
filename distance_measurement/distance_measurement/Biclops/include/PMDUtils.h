#if !defined PMDUtils_h
#define PMDUtils_h

#include <time.h>           // Needed for clock_t and clock
#include <list> 
using std::list;
#include <vector> 
using std::vector;

#include "PMDAxisControl.h" // for axis coordination
#include "PMDErrorCodes.h"  // for error message conversion
#include "Kinematics.h"

class PMDUtils {

public:
    static double GetVersion() { return 8.9f;};

    // OS-independent sleep function.
    static void DoSleep(clock_t wait);

    // Unit conversions
    static double DegsToRevs(double degs) {return degs/360;};
    static double RevsToDegs(double revs) {return revs*360;};
    static double RadsToRevs(double rads) {return rads/2/M_PI;};
    static double RevsToRads(double revs) {return revs*2*M_PI;};
    static double DegsToRads(double degs) {return degs*M_PI/180;};
    static double RadsToDegs(double rads) {return rads*180/M_PI;};
    static double InchesToMeters(double inches) {return inches*0.0254;};
    static double MetersToInches(double meters) {return meters/0.0254;};

    // File parsing utilities
    // A '#' character starts an end-of-line comment.
    // Returns true if a valid token is returned, false otherwise.
    static bool ReadToken (FILE *file, char *token, bool returnComments = false);
    static bool ReadBool  (FILE *file, char *token, bool &value);
    static bool ReadAngle (FILE *file, char *token, double &angle);
    static bool ReadLength(FILE *file, char *token, double &length);
    static bool FindToken (FILE *file, char *token, const char *find);
    static const char TokenDegrees[];
    static const char TokenRadians[];
    static const char TokenRevolutions[];
    static const char TokenInches[];
    static const char TokenMeters[];
    static const char TokenUniqueID[];

    // Load the entire configuration from the specified file.
    static bool LoadConfiguration(const char *fileName);

    // Open communication I/F and verify connectivity with the 
    // controllers of all specified axes (and compasses).
    static bool EstablishCommunication();

    // Configure the axes of every defined controller.
    static void ConfigureControllers();

    // Load configuration information from the supplied file, connect to 
    // the controller, and populate axes with configuration parameters.
    // This method provides a single call to prepare the entire 
    // hardware collection of controllers and associated axes for motion
    // control.
    static bool Initialize(const char *fileName,bool connectToControllers = true);

    // ============================== Movement methods =======================

    // Types used by various move methods
    typedef list<PMDAxisControl*> AxisList;
    typedef vector<PMDAxisControl*> AxisVector;

    // Convert a list of axis names into an array of axis pointers.
    // The list of names must have it's last entry be a NULL string.
    static AxisVector *CreateAxisLUT(const char *axisNames[]);
    static void CreateAxisLUT(const char *axisNames[], AxisVector &axisVector);

    // Synchronize two or more axes' motion so that if motion begins 
    // simultaneously for the axes they will stop simultaneously at
    // their goal positions.
    // The first method requires the caller to build the move profile list.
    // The second method does this on behalf of the caller by extracting
    // the data from the provided axes.
    typedef struct {
        PMDAxisControl::Profile uncoord;
        PMDAxisControl::Profile coord;
        double accelTime;
        double decelTime;
        double slewTime;
    } CoordinationData;
    typedef list<CoordinationData> ProfileList;
    static bool Coordinate(ProfileList &profiles);
    static bool Coordinate(AxisList &axes);

    // Move multiple axes simultaneously.
    static bool Move(AxisList &axes, long waitPeriod = 100);
    static bool Move(AxisVector &axes, long waitPeriod = 100);
    static bool Move(Kinematics::DoublesVector &cartesianCoordinate, 
                     AxisVector &axes,
                     Kinematics &kinematics, long waitPeriod = 100);

    // Convert return status from any PMDxxx class method into a textually
    // equivalent human-readable form.
    static char *GetErrorMessage(PMDuint16 errorCode);

private:
    // Collection of parameters needed to coordinate two or more axis' motion.
    typedef struct {
        PMDAxisControl::Profile   prof;
        double  actPos;
        double  accTime;
        double  velTime;
        double  dist;
        double  minAcc;
        double  minVel;
    } CoordinationParameters;
    typedef list<CoordinationParameters> CoordinationParametersList;

    Kinematics *kinematics;
};

#endif

