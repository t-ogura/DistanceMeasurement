#ifndef _JOINT_H_
#define _JOINT_H_

#include "mathfuncs.h"

class CObstacleGroup;
/* The local transform is updated whenever position or DH parameters change */
class CJoint{ // tested in MathTest.cpp -- except Collide_p for obstacles.

 public:
  CJoint(){ SetZero(&m_DH);m_offset = 0.0;} // other member classes take care of themselves
  ~CJoint(){;}

  void SetPos(double pos){ m_pos.Set(pos);UpdateTransform(); }
  void SetPos(pCAng pos){ m_pos = *pos;UpdateTransform(); }
  void SetPhys(pVec2_t phys) {m_cyl.SetPhys(phys);}
  void GetPhys(pVec2_t phys) {m_cyl.GetPhys(phys);}
  void SetDH(pVec3_t DH) {
      m_DH = *DH;
      UpdateTransform(); }
  void SetDH(double alpha, double a, double d){ m_DH.val[0] = alpha; m_DH.val[1] = a; m_DH.val[2] = d; UpdateTransform();}
  void SetLimits(double min, double max){ m_Max.Set(max); m_Min.Set(min);} 
  void SetLimits(pCAng min, pCAng max){ m_Max = *max; m_Min = *min;}
  void SetCylLoc(pVec3_t P, pVec3_t V){ m_cyl.SetLine(P, V);}
  void SetCenterOffset(double offset){m_offset = offset;} // the offset along the z axis (usually negative)
  CTransform* GetTransform(CTransform *T){*T = m_T; return T;}
  double GetPos(){return m_pos.Get();}
  double GetPosExtended(){return m_pos.GetExtended();}
  double GetMax(){return m_Max.GetExtended();}
  double GetMin(){return m_Min.GetExtended();}
  void GetCylLoc(pVec3_t P, pVec3_t V) { m_cyl.Get(P, V);}
  pCCyl GetCyl(pCCyl pC){ *pC = m_cyl; return pC;}
  CCylinder *GetCylinder() {return &m_cyl;};
  void GetLimits(double* min, double* max){*max = m_Max.GetExtended(); *min = m_Min.GetExtended();}
  pVec3_t GetDH(pVec3_t pDH) {*pDH = m_DH;return(pDH);}
  double GetCenterOffset(){return m_offset;}
  int InsideLimits(double pos){ if(pos > m_Max.GetExtended()) return 1; if(pos < m_Min.GetExtended()) return -1; return 0;}
  bool Collide_p(CJoint *J){return(m_cyl.Intersect_p(&(J->m_cyl)));}
  bool Collide_p(CObstacleGroup &group);

 private:
  void UpdateTransform();

  // State variables
  CAng m_pos;
  
  CTransform m_T; // local -- just this joint -- transforms point expressed in output frame to same point expressed in input frame

  // Limits
  CAng m_Min; 
  CAng m_Max; 

  // physical appearance
  CCylinder m_cyl; 

  // kinematics
  Vec3_t m_DH;   // alpha, a, d
  double m_offset; // center offset for locating the cylinder relative to the output frame
};

#endif
