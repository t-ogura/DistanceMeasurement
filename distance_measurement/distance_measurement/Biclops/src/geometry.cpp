#include<math.h>
//#include<stdio.h> // RRB debug
#include <cstdio>

#include "../include/mathfuncs.h"

////////////////////////    CLine2    ////////////////////////////////////
bool CLine2::Set(pVec2_t P, pVec2_t V) // returns false if the vector has zero length
{
  if(UnitVector(V, &m_Vector)){ m_Point = *P; return true;}
  return false;
}

double CLine2::L2Distance(pVec2_t pPoint, pVec2_t pPtOn, double *T) // *signed* distance, closest pt, and signed distance along Vector to PtOn
{
  Vec2_t tmpM, tmpS;
  *T = Dot(&m_Vector, Sub_v(pPoint, &m_Point, &tmpS));
  Add_v(&m_Point, Mult_sv(*T, &m_Vector, &tmpM), pPtOn);
  return(Cross(&m_Vector, &tmpS));
}

double CLine2::L2Distance(pVec2_t pPoint, double *T) // returns *signed* distance, packs signed distance along Vector to closest point
{
  Vec2_t tmpS;
  *T = Dot(&m_Vector, Sub_v(pPoint, &m_Point, &tmpS));
  return(Cross(&m_Vector, &tmpS));
}

double CLine2::L2Distance(pVec2_t pPoint, pVec2_t pPtOn) // returns the *signed* distance to the point, plus the closest point on the line
{
  Vec2_t tmpM, tmpS;
  double dist;
  dist = Dot(&m_Vector, Sub_v(pPoint, &m_Point, &tmpS));
  Add_v(&m_Point, Mult_sv(dist, &m_Vector, &tmpM), pPtOn);
  return(Cross(&m_Vector, &tmpS));
}

double CLine2::L2Distance(pVec2_t pPoint) // returns the *signed* distance to the point -- if m_Vector points along X axis, D has sgn(pt_Y)
{
  Vec2_t tmp;
  return(Cross(&m_Vector, Sub_v(pPoint, &m_Point, &tmp)));
}


bool CLine2::L2Intersect(pCLine2 pLine, pVec2_t pPoint)  // returns true and packs the intersection point, or false and doesn't touch it
{
  Vec2_t tmpP, tmpV, tmpS, tmpM;
  double X;
  pLine->Get(&tmpP, &tmpV);
  if(Approx(X = Cross(&m_Vector, &tmpV))) return false; // if the sin of the angle between the vectors is too small, fail
  Add_v(&tmpP, Mult_sv(Cross(&m_Vector, Sub_v(&m_Point, &tmpP, &tmpS))/X, &tmpV, &tmpM), pPoint);
  return true;
}

bool CLine2::Parallel_p(pCLine2 pLine) // returns true if the lines are parallel, false otherwise
{
  Vec2_t tmpP, tmpV;
  pLine->Get(&tmpP, &tmpV);
  return(Approx(Cross(&m_Vector, &tmpV)));
}


////////////////////////    CLine2Seg    ////////////////////////////////////
bool CLine2Seg::Set(pVec2_t P, pVec2_t V, double leng)
{
  Vec2_t tmpV2, tmpV;
  if(!CLine2::Set(P, V)) return false;
  UnitVector(V, &tmpV); 
  Add_v(P, Mult_sv(leng, &tmpV, &tmpV2), &m_EndPt);
  m_Length = leng;
  return true;
}

bool CLine2Seg::SetEndPts(pVec2_t P1, pVec2_t P2)
{
  Vec2_t tmpV;
  if(!CLine2::Set(P1, Sub_v(P2, P1, &tmpV))) return false;
  m_EndPt = *P2;
  m_Length = Length(&tmpV);
  return true;
}

bool CLine2Seg::ClosestPtIn(pVec2_t P, double *D)
{
  double T;
  
  *D = CLine2::L2Distance(P, &T);
  return((T >= 0.0) && (T <= m_Length));
}



////////////////////////    CLine3    ////////////////////////////////////
CLine3::CLine3(){SetZero(&m_Point); SetZero(&m_Vector);}

bool CLine3::Set(pVec3_t P, pVec3_t V)
{
  if(UnitVector(V, &m_Vector)){ m_Point = *P; return true;}
  return false;
}

double CLine3::L3Distance(pCLine3 pline, pVec3_t pPtOn, double *T)  // returns the biperp distance, endpoint, plus signed distance along V
{ 
 Vec3_t P2P, P2V, tmpN, tmpNU, tmpS, tmpD, tmpGarb, C1, C2, tmpS2;
  pline->Get(&P2P, &P2V);  // get data from line 2
  Sub_v(&P2P, &m_Point, &tmpS);
  if(Approx(Cross(&m_Vector, &P2V, &tmpN)))
    {
      *T = 0.0;
      *pPtOn = m_Point;
      return(fabs(Cross(&tmpS, &m_Vector))); 
    } 
  UnitVector(&tmpN, &tmpNU);
  Dot(&tmpNU, &tmpS, &tmpD); // tmpD is the perp vector from plane1 to plane2
  Sub_v(&tmpS, &tmpD, &tmpS2);  // tmpS projected onto plane1
  Cross(&P2V, &tmpS2, &C1);  Cross(&P2V, &m_Vector, &C2);
  *T = Dot(&C1, &tmpNU)/Dot(&C2, &tmpNU); // The number of m_Vector to get from m_Point to closest.
  Add_v(&m_Point, Mult_sv(*T, &m_Vector, &tmpGarb), pPtOn);
  return(Length(&tmpD));
}

double CLine3::L3Distance(pCLine3 pline, pVec3_t pPtOn)  // returns the biperp distance, plus its endpoint
{
  Vec3_t P2P, P2V, tmpN, tmpNU, tmpS, tmpD, tmpX, C1, C2, tmpS2;
  double dist;
  pline->Get(&P2P, &P2V);  // get data from line 2
  Sub_v(&P2P, &m_Point, &tmpS);
  if(Approx(Cross(&m_Vector, &P2V, &tmpN)))
    {
      *pPtOn = m_Point;
      return(fabs(Cross(&tmpS, &m_Vector))); 
    } 
  UnitVector(&tmpN, &tmpNU);
  Dot(&tmpNU, &tmpS, &tmpD); // tmpD is the perp vector from plane1 to plane2
  Sub_v(&tmpS, &tmpD, &tmpS2);  // tmpS projected onto plane1
  Cross(&P2V, &tmpS2, &C1);  Cross(&P2V, &m_Vector, &C2);
  dist = Dot(&C1, &tmpNU)/Dot(&C2, &tmpNU); // The number of m_Vector to get from m_Point to closest.
  Add_v(&m_Point, Mult_sv(dist, &m_Vector, &tmpX), pPtOn);
  return(Length(&tmpD));
}

double CLine3::L3Distance(pCLine3 pline, double *T)  // returns the biperp distance, plus signed distance along Vector
{
  Vec3_t P2P, P2V, tmpN, tmpNU, tmpS, tmpD, C1, C2, tmpS2;
  pline->Get(&P2P, &P2V);  // get data from line 2
  Sub_v(&P2P, &m_Point, &tmpS);
  if(Approx(Cross(&m_Vector, &P2V, &tmpN)))
    {
      *T = 0.0;
      return(fabs(Cross(&tmpS, &m_Vector))); 
    }
  UnitVector(&tmpN, &tmpNU);
  Dot(&tmpNU, &tmpS, &tmpD); // tmpD is the perp vector from plane1 to plane2
  Sub_v(&tmpS, &tmpD, &tmpS2);  // tmpS projected onto plane1
  Cross(&P2V, &tmpS2, &C1);  Cross(&P2V, &m_Vector, &C2);
  *T = Dot(&C1, &tmpNU)/Dot(&C2, &tmpNU); // The number of m_Vector to get from m_Point to closest.
  return(Length(&tmpD));
}

double CLine3::L3Distance(pCLine3 pline)  // returns the biperp distance -- always positive -- ok to be parallel
{
  Vec3_t P2P, P2V, tmpN, tmpNU, tmpS;
  pline->Get(&P2P, &P2V);  // get data from line 2
  Sub_v(&P2P, &m_Point, &tmpS);
  if(Approx(Cross(&m_Vector, &P2V, &tmpN))) return(fabs(Cross(&tmpS, &m_Vector)));
  UnitVector(&tmpN, &tmpNU);
  return(fabs(Dot(&tmpS, &tmpNU)));
}



double CLine3::L3Distance(pVec3_t pPoint, pVec3_t pPtOn, double *T) // returns the uns. distance to the point, closest point, & dist along vector
{
  Vec3_t tmpM, tmpS;
  *T = Dot(&m_Vector, Sub_v(pPoint, &m_Point, &tmpS));
  Add_v(&m_Point, Mult_sv(*T, &m_Vector, &tmpM), pPtOn);
  return(Cross(&m_Vector, &tmpS));
}

double CLine3::L3Distance(pVec3_t pPoint, pVec3_t pPtOn) // returns the uns. distance to the point plus the closest point on the line
{
  Vec3_t tmpM, tmpS;
  Add_v(&m_Point, Dot(&m_Vector, Sub_v(pPoint, &m_Point, &tmpS), &tmpM), pPtOn);
  return(Cross(&m_Vector, &tmpS));
}

double CLine3::L3Distance(pVec3_t pPoint, double *T) // returns the unsigned dist to the point, packs the signed dist along Vector to PtOn.
{
  Vec3_t tmpS;
  *T = Dot(&m_Vector, Sub_v(pPoint, &m_Point, &tmpS));
  return(Cross(&m_Vector, &tmpS));
}

double CLine3::L3Distance(pVec3_t pPoint) // returns the *unsigned* distance to the point
{ Vec3_t tmpS; return(Cross(&m_Vector, Sub_v(pPoint, &m_Point, &tmpS)));}

bool CLine3::Parallel_p(pCLine3 pLine) // returns true if the lines are parallel, false otherwise
{
  Vec3_t tmpP, tmpV;
  pLine->Get(&tmpP, &tmpV);
  return(Approx(Cross(&m_Vector, &tmpV)));
}



////////////////////////    CPlane3    ////////////////////////////////////

CPlane::CPlane(){ SetZero(&m_Point); SetIdentity(&m_Axes);}


double CPlane::PDistance(pVec3_t pPoint) { Vec3_t tmpS; return(DotR(Sub_v(pPoint, &m_Point, &tmpS), &m_Axes, 2));} // signed!!

double CPlane::PDistance(pVec3_t pPoint, pVec3_t pPtOn)  // returns signed distance plus closest point.
{ 
  Vec3_t tmpS, tmpD; 
  double val;
  Vec3_t Z;
  Z.val[0] = m_Axes.val[2][0];  Z.val[1] = m_Axes.val[2][1];  Z.val[2] = m_Axes.val[2][2];
  val = Dot(Sub_v(pPoint, &m_Point, &tmpS), &Z);
  Sub_v(pPoint, Mult_sv(val, &Z, &tmpD), pPtOn);
  return(val);
}

double CPlane::PDistance(pVec3_t pPoint, pVec3_t pPtOn, double *T)  // returns signed distance plus closest point.
{ 
  Vec3_t tmpS, tmpD; 
  double val;
  Vec3_t Z;
  Z.val[0] = m_Axes.val[2][0];  Z.val[1] = m_Axes.val[2][1];  Z.val[2] = m_Axes.val[2][2];
  val = Dot(Sub_v(pPoint, &m_Point, &tmpS), &Z);
  Sub_v(pPoint, Mult_sv(val, &Z, &tmpD), pPtOn);
  *T = Distance(pPtOn, &m_Point); // distance from closest point to origin
  return(val);
}

/*
bool CPlane::PIntersect(CPlane *pPlane, pCLine3 pLine3)  // this returns the line of intersection between the planes
{
  return false;
}
*/

bool CPlane::PIntersect(pCLine3 pLine3, pVec3_t pPt3)  // this returns the point of intersection between the plane and line, false if none
{
  Vec3_t P3P, P3V, tmpC;
  double D, T;

  pLine3->Get(&P3P, &P3V);
  if(Approx(T = DotR(&P3V, &m_Axes, 2))) return false; // T is the dot product
  D = PDistance(&P3P); // signed
  Add_v(&P3P, Mult_sv(-D/T, &P3V, &tmpC), pPt3);
  return true;
}

bool CPlane::PIntersect(pCLine3 pLine3, pVec2_t pPt2)  // this returns the point of intersection in Plane coords, false if none
{
  Vec3_t tmpC, tmpS, tmpA;

  if(!PIntersect(pLine3, &tmpC)) return false; // finds point of intersection
  PRotateV(Sub_v(&tmpC, &m_Point, &tmpS), &tmpA);  // rotates point offset into plane frame
  pPt2->val[0] = tmpA.val[0];
  pPt2->val[1] = tmpA.val[1];
  return true;
}

////////////////////////    CCylinder    ////////////////////////////////////


bool CCylinder::Inside_p(pVec3_t pPt)
{
  double T, D;
  D = m_Line.L3Distance(pPt, &T);
  if((D <= m_Radius) && (fabs(T) <= m_Length)) return true;
  return false;
}



// May need special case for parallel cylinders
bool CCylinder::Intersect_p(CCylinder* pCyl)
{
  CLine3 L;
  Vec2_t Phys, Min, Max;
  Vec3_t P1, V1, P2, V2, N, N2, NU;
  Mat3_t Rot;
  Vec2_t A[4], B[4];
  pVec2_t pA[4], pB[4];
  int i;
  Vec3_t tmpP;
  Vec2_t P22, V22;
  double angle, cT, sT, rho1, rho2, LenVal;

  for(i = 0;i<4;i++){ pA[i] = &(A[i]); pB[i] = &(B[i]);}

  pCyl->GetLine(&L); pCyl->GetPhys(&Phys); L.Get(&P2, &V2); m_Line.Get(&P1, &V1);


  // first, check whether the biperp is larger than the sum of the radii
  if(L.L3Distance(&m_Line) > Phys.val[0] + m_Radius) return false;

  // Let's check whether the two cylinders are too far based on their maximum radii:
  rho1 = sqrt(m_Length*m_Length + m_Radius*m_Radius);
  rho2 = Length(&Phys);
  if(Distance(&P1, &P2) > rho1 + rho2)return false;

  // Next project the two cylinders into rectangles on the plane perp. to the biperp, and see if they overlap.
  // Let the origin be P1, with X axis along V1...

  // We need a special case for when the cylinder lines are parallel!
  if(m_Line.Parallel_p(&L)){
    Dot(&V1, Sub_v(&P2, &P1, &tmpP), &NU);
    Sub_v(&tmpP, &NU, &N);
    UnitVector(&N, &NU);
    Cross(&NU, &V1, &N2);
  }
  else{
    Cross(&V1, &V2, &N); 
    UnitVector(&N, &NU);
    Cross(&NU, &V1, &N2);
  }
  GlueRow(&Rot, &V1, &N2, &NU);

  // Set first quadrilateral.
  A[0].val[0] = -m_Length; A[0].val[1] = -m_Radius;
  A[1].val[0] =  m_Length; A[1].val[1] = -m_Radius;
  A[2].val[0] =  m_Length; A[2].val[1] =  m_Radius;
  A[3].val[0] = -m_Length; A[3].val[1] =  m_Radius;

  Project(Sub_v(&P2, &P1, &tmpP), &Rot, 2, &P22); // so now P22 is P2 in the XY plane
  Project(&V2, &Rot, 2, &V22);
  angle = atan2(V22.val[1], V22.val[0]);
  cT = cos(angle); sT = fabs(sin(angle));

  B[0].val[0] = P22.val[0] + Phys.val[1]*cT + Phys.val[0]*sT; B[0].val[1] = P22.val[1] + Phys.val[1]*sT - Phys.val[0]*cT;
  B[1].val[0] = P22.val[0] + Phys.val[1]*cT - Phys.val[0]*sT; B[1].val[1] = P22.val[1] + Phys.val[1]*sT + Phys.val[0]*cT;
  B[2].val[0] = P22.val[0] - Phys.val[1]*cT - Phys.val[0]*sT; B[2].val[1] = P22.val[1] - Phys.val[1]*sT + Phys.val[0]*cT;
  B[3].val[0] = P22.val[0] - Phys.val[1]*cT + Phys.val[0]*sT; B[3].val[1] = P22.val[1] - Phys.val[1]*sT - Phys.val[0]*cT;

  if(!IntersectQuad_p(pA, pB))return false;

  // Next we're going to project along axis of cyl1
  Project(Sub_v(&P2, &P1, &tmpP), &Rot, 0, &P22); // so now P22 is P2 in the YZ plane
  sT = fabs(Cross(&V1, &V2));
  cT = fabs(Dot(&V1, &V2));
  LenVal = sT*Phys.val[1] + cT*Phys.val[0];

  Min.val[0] = P22.val[0] - LenVal;      
  Max.val[0] = P22.val[0] + LenVal; 
  Min.val[1] = P22.val[1] - Phys.val[0]; 
  Max.val[1] = P22.val[1] + Phys.val[0]; 
  
  if(!IntersectCircleRectangle_p(gZVec2, m_Radius, &Min, &Max)) return false;

  // Now do it for the other cylinder
  Cross(&V2, &V1, &N); UnitVector(&N, &NU);
  Cross(&NU, &V2, &N2);
  GlueRow(&Rot, &V2, &N2, &NU);

  Project(Sub_v(&P1, &P2, &tmpP), &Rot, 0, &P22); // so now P22 is P2 in the YZ plane
  sT = fabs(Cross(&V1, &V2));
  cT = fabs(Dot(&V1, &V2));
  LenVal = sT*m_Length + cT*m_Radius;

  Min.val[0] = P22.val[0] - LenVal;      
  Max.val[0] = P22.val[0] + LenVal; 
  Min.val[1] = P22.val[1] - m_Radius; 
  Max.val[1] = P22.val[1] + m_Radius; 
  
  if(!IntersectCircleRectangle_p(gZVec2, Phys.val[0], &Min, &Max)) return false;

  return true;
}

bool CCylinder::Intersect_p(CObstacle* pObst){ return(pObst->Intersect_p(this));} // unchecked


