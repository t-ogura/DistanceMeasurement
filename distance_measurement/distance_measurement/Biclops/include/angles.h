#ifndef _ANGLES_H_
#define _ANGLES_H_

#include "mathfuncs.h"


//////////////////////////////////////////////////////////////////////
/*
  Class CAng is an angle object.

Behavior: 
    Set() accepts any value in radians
    GetExtended() should return the original value  (allows windup)
    Get() returns the value clipped to:     -pi < "value" <= pi  (this object is true S1)
    GetCos() and GetSin() return the transcendentals, which are always computed when Set is called.

*/
//////////////////////////////////////////////////////////////////////
class CAng // checked in MathTest.cpp
{
 public:
  CAng();
  CAng(double val);
  ~CAng(){;}

  void   Set(double val);        // the angle value
  double Get(){return(m_value);}
  double GetExtended(){return(m_valueExtended);}
  double GetSin(){return(m_sin);}
  double GetCos(){return(m_cos);}

 private:
  double m_value;     // in radians, -pi < "value" <= pi
  double m_valueExtended; // in radians -inf to inf.
  double m_sin;       // sin of "value"
  double m_cos;       // cos of "value"
};

typedef CAng *pCAng;

//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
/*
  Class CAngle1 is a more sophisticated 1-d angle object.

Behavior: 
    Set() accepts any value in radians, class CAng, pCAng, or 2-D vector.  In the last case, returns false if the vector is zero.
    Get: get the value out.  Various sorts:
       GetDExt(): The original value, not clipped.
       GetD: The original angle, clipped to: -pi < "value" <= pi
       GetV(): the unit vector that subtends the angle from the X axis (right hand rule)
       GetM(): the rotation matrix (where the rows are the axes of a frame rotated by the angle.
       GetCos() and GetSin() return the transcendentals, which are always computed when Set is called.
       Rotate() takes a vector represented in W and represents it in F, where F rotated from W by value about the Z axis.
       RotateInv() goes the other way.
*/
//////////////////////////////////////////////////////////////////////
class CAngle1   // checked in MathTest.cpp
{

 public:  

  CAngle1();
  CAngle1(double val);
  ~CAngle1(){;}

  void    Set(double val);        // the angle value
  void    Set(CAng ang){ Set(ang.GetExtended());}
  void    Set(pCAng pang){Set(pang->GetExtended());}
  bool    Set(pVec2_t pvec);      // a vector that is the angle from x-axis

  double  GetD(){return(m_ang.Get());}
  double  GetDExt(){return(m_ang.GetExtended());}
  pCAng   GetAng(pCAng ang){ *ang = m_ang; return ang;}
  pVec2_t GetV(pVec2_t pvec){*pvec = m_vec; return pvec;}
  pMat2_t GetM(pMat2_t pmat){*pmat = m_rot; return pmat;}

  double  GetSin(){return(m_ang.GetSin());}
  double  GetCos(){return(m_ang.GetCos());}
  pVec2_t Rotate(pVec2_t in, pVec2_t out){return(Mult_mv(&m_rot, in, out));}
  pVec2_t RotateInv(pVec2_t in, pVec2_t out){return(Mult_mv(&m_rotinv, in, out));}

private:
  CAng m_ang;
  Vec2_t m_vec;       // unit vector rotated "value" from x-axis in counterclockwise direction
  Mat2_t m_rot;       // rotation -- represents the operator that takes a point in W and represents it in F,
                      // where F is a frame rotated by m_value from W about the Z axis.  
                      // NOTE: the rows represent the axes of F represented in W, the columns are the axes of W in F.
                      // NOTE: this is equivalent to rotating the vector by -m_value
  Mat2_t m_rotinv;    // inverse rotation 
};

typedef CAngle1 *pCAng1;

//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////
/*
  Class CAngle2 is a  2-d angle object.
  
  Basically, it represents a point on a sphere, or S2.
  Think of latitude and longitude.

Behavior: 
    Set() accepts many different types of value.  In the case of a 3-D vector, returns false if the vector is zero.
    The core function is Set(double longitude, double latitude), where the angles are in radians
    Get: get the values out.  Various sorts:
       GetDExt(): The original values, not clipped.
       GetD: The angles clipped to: -pi < "value" <= pi
       GetV(): the unit vector that points to the point on the sphere
       GetCos() and GetSin() return the transcendentals, which are always computed when Set is called.
*/
//////////////////////////////////////////////////////////////////////
class CAngle2    // checked in MathTest.cpp
{

 public:  

  CAngle2();
  ~CAngle2(){;}

  void   Set(double A0, double A1);  // two angles
  void   Set(CAng ang[2]){Set(ang[0].GetExtended(), ang[1].GetExtended());}  // array of two angles
  void   Set(pCAng pang[2]){Set(pang[0]->GetExtended(), pang[1]->GetExtended());}  // array of two angle pointers
  void   Set(pCAng ang1, pCAng ang2){Set(ang1->GetExtended(), ang2->GetExtended());}  // two separate angle pointers
  void   Set(pVec2_t pAng2){Set(pAng2->val[0], pAng2->val[1]);}         // two angles
  bool   Set(pVec3_t pAng3);         // 3-d vector -- need not be a unit vector -- false if the zero vector

  pVec2_t   GetD(pVec2_t pAng2){pAng2->val[0] = m_ang[0].Get();pAng2->val[1] = m_ang[1].Get();return(pAng2);}
  pVec2_t   GetDExt(pVec2_t pAng2){pAng2->val[0] = m_ang[0].GetExtended();pAng2->val[1] = m_ang[1].GetExtended();return(pAng2);}
  pVec3_t   GetV(pVec3_t pAng3){*pAng3 = m_vec;return(pAng3);;}   // this will return a unit vector
  pVec2_t   GetSin(pVec2_t pSin2){pSin2->val[0] = m_sin.val[0]; pSin2->val[1] = m_sin.val[1];return(pSin2);}
  pVec2_t   GetCos(pVec2_t pCos2){pCos2->val[0] = m_cos.val[0]; pCos2->val[1] = m_cos.val[1];return(pCos2);}

  

 private:
  CAng   m_ang[2];    // in radians, -pi < "value" <= pi -- [0] for longitude, [1] for latitude.
                      // NOTE that [0] is restricted to +/- pi
                      // NOTE that [1] is restricted to +/- pi -- this covers the sphere TWICE
  Vec3_t m_vec;       // unit vector rotated m_value[0] from x-axis about z-axis, 
                      // then m_value[1] from XY plane about y-axis
  Vec2_t m_sin;
  Vec2_t m_cos;
};


//////////////////////////////////////////////////////////////////////
/*
  Class CAngle3 is a  3-d angle object.
  
  Basically, it represents a point on a hypersphere, or S3.
  Think of latitude, longitude, and twist; OR: roll, pitch, and yaw.
  

Behavior: 
    Set() accepts many different types of value.  In the case of a 3-D vector, returns false if the vector is zero. Also fails for bad rotations.
    The core function is Set(double yaw, double pitch, double roll), where the angles are in radians
    Get: get the values out.  Various sorts:
       GetDExt(): The original values, not clipped.
       GetD: The angles clipped to: -pi < "value" <= pi
       GetV(): the unit vector that points to the point on the sphere
       GetCos() and GetSin() return the transcendentals, which are always computed when Set is called.
       Rotate(): takes a vector in W and represents it in F
*/
//////////////////////////////////////////////////////////////////////
class CAngle3    // checked in MathTest.cpp
{
 public:  

  CAngle3(){ Set(0.0, 0.0, 0.0); }
  ~CAngle3(){;}

  void   Set(double A0, double A1, double A2); // the 3 angles
  void   Set(CAng ang[3]) {Set(ang[0].GetExtended(), ang[1].GetExtended(), ang[2].GetExtended());}
  void   Set(pCAng pang[3]) {Set(pang[0]->GetExtended(), pang[1]->GetExtended(), pang[2]->GetExtended());}
  void   Set(pCAng pang1, pCAng pang2, pCAng pang3) {Set(pang1->GetExtended(), pang2->GetExtended(), pang3->GetExtended());}
  void   Set(pVec3_t pAng3) {Set(pAng3->val[0], pAng3->val[1], pAng3->val[2]);}
  bool   SetM(pMat3_t pMat3);                   // the rotation matrix -- fails if incoming isn't a rotation
  bool   SetV(pVec3_t pAng3);                   // vector, where the natural log of the magnitude is the roll. false if vector is zero

  pVec3_t   GetD(pVec3_t pAng3){for(int i=0;i<3;i++) pAng3->val[i] = m_ang[i].Get(); return(pAng3);}
  pVec3_t   GetDExt(pVec3_t pAng3){for(int i=0;i<3;i++) pAng3->val[i] = m_ang[i].GetExtended(); return(pAng3);}
  pVec3_t   GetV(pVec3_t pAng3){*pAng3 = m_vec; return(pAng3);}
  pMat3_t   GetRot(pMat3_t pMat3){*pMat3 = m_rot; return(pMat3);}
  pMat3_t   GetRotInv(pMat3_t pMat3){return(Transpose(&m_rot, pMat3));}
  pVec3_t   GetSin(pVec3_t pSin3){*pSin3 = m_sin;return(pSin3);}
  pVec3_t   GetCos(pVec3_t pCos3){*pCos3 = m_cos;return(pCos3);}
  pVec3_t   Rotate(pVec3_t Vin, pVec3_t Vout){return(Mult_mv(&m_rot, Vin, Vout));}
  pVec3_t   RotateInv(pVec3_t Vin, pVec3_t Vout){return(Mult_vm(&m_rot, Vin, Vout));}

 private:
  CAng m_ang[3];

  Vec3_t m_vec;       // unit vector rotated m_value[0] from x-axis about z-axis, 
                      // then m_value[1] from XY plane about y-axis -- NOTE: roll doesn't make a difference here
                      // this is simply the Z axis
  Mat3_t m_rot;       // rotation -- represents the rotation necessary to get from W to F. NOTE: rows represent
                      // axes of F in W; columns represent axes of W in F.    ZYZ
  Vec3_t m_sin;
  Vec3_t m_cos;
};

#endif // defined _ANGLES_H_
