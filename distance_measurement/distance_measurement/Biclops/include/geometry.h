#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

#include "mathfuncs.h"

// forward declaration
class CObstacle;


/* CLine2 holds a point and a unit vector in 2D.  
It would be theoretically nice to use a CAngle1 here, but all the accessor functions use the vector
(and none of them use the trig functions), so we might as well just store that in the interest of time.

Set() fails if the incoming vector is zero.
*/


class CLine2{       // checked in MathTest.cpp

 public:
  CLine2(){SetZero(&m_Point); SetZero(&m_Vector);}
   ~CLine2(){;}

  bool Set(pVec2_t P, pVec2_t V);
  void Get(pVec2_t P, pVec2_t V){*P = m_Point;*V = m_Vector;}

  double L2Distance(pVec2_t pPoint, pVec2_t pPtOn, double *T); // distance, closest pt, and signed distance along Vector to PtOn
  double L2Distance(pVec2_t pPoint, pVec2_t pPtOn); // returns the distance to the point, plus the closest point on the line
  double L2Distance(pVec2_t pPoint, double *T); // returns distance, packs signed distance along Vector to closest point
  double L2Distance(pVec2_t pPoint); // returns the distance to the point
  bool L2Intersect(CLine2 *pLine, pVec2_t pPoint);  // returns true and packs the intersection point, or false and doesn't touch it
  bool Parallel_p(CLine2 *pLine); // returns true if the lines are parallel, false otherwise

 protected:
  Vec2_t m_Point;
 private:
  Vec2_t m_Vector; // unit vector

};

typedef CLine2 *pCLine2;

/* CLine2Seg is an extension of the 2-D line that has finite extent.  */

class CLine2Seg : public CLine2{       // checked in MathTest.cpp
 public:
  CLine2Seg(){SetZero(&m_EndPt); m_Length = 0.0;}
  ~CLine2Seg(){;}

  bool Set(pVec2_t P, pVec2_t V, double len);
  bool SetEndPts(pVec2_t P1, pVec2_t P2);
  void GetEndPts(pVec2_t P1, pVec2_t P2){ *P1 = m_Point;*P2 = m_EndPt;}
  bool ClosestPtIn(pVec2_t P, double *D); // true if the closest point to P is inside the segment
 private:
  double m_Length;
  Vec2_t m_EndPt;
};

typedef CLine2Seg* pCLine2Seg;

class CLine3{       // checked in MathTest.cpp

 public:
  CLine3();
  ~CLine3(){;}

  bool Set(pVec3_t P, pVec3_t V);
  void Get(pVec3_t P, pVec3_t V){*P = m_Point;*V = m_Vector;}

  double L3Distance(CLine3 *pline);  // returns the biperp distance
  double L3Distance(CLine3 *pline, pVec3_t pPtOn, double *T);  // returns the biperp distance, endpoint, plus signed distance along Vector
  double L3Distance(CLine3 *pline, pVec3_t pPtOn);  // returns the biperp distance, plus its endpoint
  double L3Distance(CLine3 *pline, double *T);  // returns the biperp distance, plus signed distance along Vector
  double L3Distance(pVec3_t pPoint, pVec3_t pPtOn, double *T); // returns the distance to the point plus the closest point on the line
  double L3Distance(pVec3_t pPoint, pVec3_t pPtOn); // returns the distance to the point plus the closest point on the line
  double L3Distance(pVec3_t pPoint, double *T); // returns the distance to the point plus the signed distance along Vector to PtOn.
  double L3Distance(pVec3_t pPoint); // returns the unsigned distance to the point
  bool   Parallel_p(CLine3 *pLine);
 private:
  Vec3_t m_Point;
  Vec3_t m_Vector; // unit vector

};

typedef CLine3 *pCLine3;


/*
  The rotation is basically a transform:
  m_Axes == ABR, where frame B is the world, frame A is the plane.  Rows are the axes of frame A in frame B.
  m_Point == BPAorg: the origin of frame A in frame B
*/
class CPlane{       // checked in MathTest.cpp

 public:
  CPlane();
  ~CPlane(){;}

  // rows of M represent the XYZ axes.  By convention, Z is normal to plane
  bool Set(pVec3_t P, pMat3_t M){ m_Point = *P; if(!Rotation_p(M)) return false; m_Axes = *M; return true;}
  void Get(pVec3_t P, pMat3_t M){*P = m_Point; *M = m_Axes;}
  pMat3_t GetRot(pMat3_t M){*M = m_Axes; return M;}
  pVec3_t GetPoint(pVec3_t P){*P = m_Point; return P;}

  double PDistance(pVec3_t pPoint);  // this is a signed quantity!
  double PDistance(pVec3_t pPoint, pVec3_t pPtOn);  // returns distance plus closest point.
  double PDistance(pVec3_t pPoint, pVec3_t pPtOn, double *T);  // returns signed distance plus closest point.
  // returns vector in frame of the plane
  pVec3_t PRotateV(pVec3_t pVin, pVec3_t pVout){ return(Mult_mv(&m_Axes, pVin, pVout));}
  // returns pPin (in frame B) in frame coords of the plane (must shift origin) (frame A)
  pVec3_t PRotateP(pVec3_t pPin, pVec3_t pPout){ Vec3_t tmpV, tmpV2; 
  return(Sub_v(Mult_mv(&m_Axes, pPin, &tmpV), Mult_mv(&m_Axes, &m_Point, &tmpV2), pPout));}
  //  bool PIntersect(CPlane *pPlane, pCLine3 pLine3);  // this returns the line of intersection between the planes
  bool PIntersect(pCLine3 pLine3, pVec3_t pPt3);  // this returns the point of intersection between the plane and line, false if none
  bool PIntersect(pCLine3 pLine3, pVec2_t pPt2);  // this returns the point of intersection in Plane coords, false if none

 private:
  Vec3_t m_Point;
  Mat3_t m_Axes; // By convention, Z is normal to plane -- orthogonal unit vectors, rows are : XYZ.
};

typedef CPlane *pCPlane;


/*
  The cylinder is centered on its line's point, and aligned with the line's vector.
  m_Radius is its radius
  m_Length is *HALF* the total length
*/

class CCylinder{       // checked in MathTest.cpp -- all but the obstacle intersection

 public:
  CCylinder(){ m_Radius = 0.0; m_Length = 0.0;}
  ~CCylinder(){;}

  void SetLine(pCLine3 pL){ m_Line = *pL;}
  void SetLine(pVec3_t P, pVec3_t V){m_Line.Set(P, V);}
  void SetPhys(pVec2_t pPhys){m_Radius = pPhys->val[0]; m_Length = pPhys->val[1];}
  pVec2_t GetPhys(pVec2_t pPhys){pPhys->val[0] = m_Radius; pPhys->val[1] = m_Length; return(pPhys);}
  pCLine3 GetLine(pCLine3 pLine){*pLine = m_Line; return(pLine);}
  void Get(pVec3_t P, pVec3_t V) {m_Line.Get(P, V);}
  bool Inside_p(pVec3_t pPt);
  bool Intersect_p(CCylinder* pCyl);

  bool Intersect_p(CObstacle* pObst); // unchecked

 private:
  double m_Radius;
  double m_Length; // half of the physical length
  CLine3 m_Line;

};

typedef CCylinder* pCCyl;
/*
class Cylinder{       // checked in MathTest.cpp -- all but the obstacle intersection
    
public:
    Cylinder(){ radius = 0.0; length = 0.0;}
    ~Cylinder(){;}
    
    void SetLine(pCLine3 pL){ line = *pL;}
    void SetLine(pVec3_t P, pVec3_t V){line.Set(P, V);}
    void SetPhys(pVec2_t pPhys){radius = pPhys->val[0]; length = pPhys->val[1];}
    pVec2_t GetPhys(pVec2_t pPhys){pPhys->val[0] = radius; pPhys->val[1] = length; return(pPhys);}
    pCLine3 GetLine(pCLine3 pLine){*pLine = line; return(pLine);}
    void Get(pVec3_t P, pVec3_t V) {line.Get(P, V);}
    bool Inside(double point[3]);
    bool Intersect(const Cylinder &cylinder);
    bool Intersect(const Obstacle &obstacle); // unchecked
    
private:
    double radius;
    double length; // half of the physical length
    CLine3 line;
    
};
*/
#endif 
