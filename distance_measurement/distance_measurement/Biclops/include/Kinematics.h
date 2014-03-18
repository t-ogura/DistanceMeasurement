#ifndef _MANIPULATORKIN_H_
#define _MANIPULATORKIN_H_

#include <vector>
using std::vector;
#include <map>
using std::map;
#include <string>
using std::string;

#include "obstacle.h"
#include <stdio.h>

class Kinematics {
    
public:

    typedef vector<double> DoublesVector;
    static const char *StartToken;
    static const char *EndToken;

    Kinematics() {};
    virtual ~Kinematics() {};
    
    // Physical parameters setup
    void SetDegreesOfFreedom(unsigned short dofs) {degreesOfFreedom = dofs;};
    unsigned short GetDegreesOfFreedom() {return degreesOfFreedom;};
    DoublesVector *AllocateJointsVector() {return new DoublesVector(degreesOfFreedom);};
    virtual bool Initialize(FILE *file, char *token) {return true;};
    virtual void SetJointPhysParams(int jointNum, const DoublesVector &params) {};
    virtual void SetAllJointPhysParams( const DoublesVector &radii, 
        const DoublesVector &lengths) {};
    virtual void SetAllJointCenterOffsets(const DoublesVector &centerOffset) {};
    virtual void SetLinkParams( const DoublesVector &length, 
                        const DoublesVector &lower, 
                        const DoublesVector &upper) {};
    virtual void SetDHParams(   const DoublesVector &alpha, 
                        const DoublesVector &a, 
                        const DoublesVector &d) {};
    virtual void SetJointLimits(const DoublesVector &jointLowerLimits, 
                        const DoublesVector &jointUpperLimits) {};

    // Collision detection (NOTE: no strict limit to the # of obstacles)
    enum CollisionType {NO_COLLISION=0,LIMIT_COLLISION,SELF_COLLISION,OBSTACLE_COLLISION};
    typedef map<string,CObstacle*> Obstacles;
    Obstacles obstacles;
    virtual CollisionType DetectCollision(const DoublesVector &desiredPos) {return NO_COLLISION;};

    // Kinematics calculations
    virtual bool Forward(const DoublesVector &desiredJointPose, 
        DoublesVector &resultingCartesianPose) {return false;};
    virtual bool Inverse(const DoublesVector &desiredCartesianPose, 
        // void *furtherConstraints,
        DoublesVector &resultingJointPose, const void *otherConstraints = NULL) {return false;};

private:

    unsigned short degreesOfFreedom;
};

#endif
