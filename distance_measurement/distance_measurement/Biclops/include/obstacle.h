#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "mathfuncs.h"

/*
  The obstacle is a rectanguloid block with faces perpendicular to
  the axes of the world coordinate system.
*/

class CObstacle{

 public:
  CObstacle(){for(int i=0;i<3;i++) for(int j=0;j<2;j++) Limit[i][j] = 0.0;}
  CObstacle(pVec3_t Min, pVec3_t Max) { SetLimits(Min,Max);}
  ~CObstacle(){;}
  
  void SetLimits(pVec3_t Min, pVec3_t Max){ for(int i = 0;i<3;i++){ Limit[i][0] = Min->val[i]; Limit[i][1] = Max->val[i];}}
  void GetLimits(pVec3_t Min, pVec3_t Max){ for(int i = 0;i<3;i++){ Min->val[i] = Limit[i][0]; Max->val[i] = Limit[i][1];}}
  bool Inside_p(pVec3_t Point);
  bool Intersect_p(CObstacle* pObst);
  bool Intersect_p(CCylinder* pCyl);

 private:
  double Limit[3][2];  //XYZ, min/max
};

typedef CObstacle* pCObs;


/* The obstacle list might be better handled with a vector, but 10 is more
than enough anyway.
*/

#define MAX_OBS_GRP_SIZE 10

class CObstacleGroup{

 public:
  CObstacleGroup();
  ~CObstacleGroup();

  void ClearAll();
  bool AddObstacle(pCObs pObs);
  bool AddObstacle(pVec3_t Min, pVec3_t Max);
  bool AddObstacle(double Min[3], double Max[3]);
  bool RemoveObstacle(int ObsNum);
  int GetObstacles(pCObs pObst[MAX_OBS_GRP_SIZE]);

  bool Intersect_p(CObstacle* pObst);
  bool Intersect_p(CObstacleGroup* pObstG);
  bool Intersect_p(CCylinder* pCyl);

 private:
  pCObs m_pObst[MAX_OBS_GRP_SIZE];
  int m_NumObs;
};

typedef CObstacleGroup* pCObsG;
/*
//--------------------- Bryn's Obstacle class --------------------------------
class Obstacle {
    
public:

    Obstacle(){for(int i=0;i<3;i++) for(int j=0;j<2;j++) limit[i][j] = 0.0;}
    Obstacle(const double ll[3], const double ul[3]) {
        SetLimits(ll,ul);
    };
    virtual ~Obstacle();
    
    void SetLimits(const double ll[3], const double ul[3]) {
        for(int i=0;i<3;i++) {
            limit[i][0] = ll[i]; limit[i][1] = ul[i];
        }
    };
    void GetLimits(double ll[3], double ul[3]){ 
        for(int i = 0;i<3;i++) {
            ll[i] = limit[i][0]; 
            ul[i] = limit[i][1];
        }
    };
    bool Inside(const double point[3]);
    bool Intersect(const Obstacle &obstacle);
    bool Intersect(const Cylinder &cylinder);

private:
    double limit[3][2];  //XYZ, min/max
};
*/
#endif
