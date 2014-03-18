#include <math.h>

#include "../include/mathfuncs.h"

/////////////////////     CANG      //////////////////////////

/* NOTE: incoming value need not be within +/- PI 
   m_value will be wrapped around to that interval, 
   m_valueExtended will not be.
*/
 CAng::CAng(){ Set(0.0);}
 CAng::CAng(double val){ Set(val);}


void CAng::Set(double val)
{
  m_valueExtended = val;
  m_value = m_valueExtended;
  if(m_value >   M_PI){m_value -= (((int)(m_value/M_PI)+1)/2)*M_2PI;}
  if(m_value <= -M_PI){m_value -= (((int)(m_value/M_PI)-1)/2)*M_2PI;}
  m_sin = sin(m_value);
  m_cos = cos(m_value);
}


/////////////////////     CANGLE1      //////////////////////////

CAngle1::CAngle1(){ Set(0.0);}

CAngle1::CAngle1(double val){Set(val);}


void CAngle1::Set(double val)
{
  m_ang.Set(val);

  m_vec.val[0] = m_ang.GetCos();
  m_vec.val[1] = m_ang.GetSin();

  m_rot.val[0][0] =  m_vec.val[0];
  m_rot.val[0][1] =  m_vec.val[1];
  m_rot.val[1][0] = -m_vec.val[1];
  m_rot.val[1][1] =  m_vec.val[0];

  Transpose(&m_rot, &m_rotinv);
}


/* NOTE: incoming vector need not be a unit vector
 *
 * Returns false if incoming vector is the zero vector
 */
bool CAngle1::Set(pVec2_t pvec)
{
  if(Approx(pvec)) return false;
  Set(atan2(pvec->val[1], pvec->val[0]));
  return true;
}



/////////////////////     CANGLE2      //////////////////////////
CAngle2::CAngle2()
{
  // NOTE: upon creation, ang[] are set to zero.
  m_vec.val[0] = 1.0;
  m_vec.val[1] = m_vec.val[2] = 0.0;
}

void CAngle2::Set(double A0, double A1)
{
  m_ang[0].Set(A0);
  m_ang[1].Set(A1);

  m_cos.val[0] = m_ang[0].GetCos();
  m_sin.val[0] = m_ang[0].GetSin();
  m_cos.val[1] = m_ang[1].GetCos();
  m_sin.val[1] = m_ang[1].GetSin();

  m_vec.val[0] = m_cos.val[0]*m_cos.val[1];
  m_vec.val[1] = m_sin.val[0]*m_cos.val[1];
  m_vec.val[2] = m_sin.val[1];
}

bool CAngle2::Set(pVec3_t pVec3) // The incoming vector may have arbitrary non-zero magnitude
{
  Vec2_t temp;
  double x = pVec3->val[0];
  double y = pVec3->val[1];
  double z = pVec3->val[2];
  double base;

  base = Length(x, y);

  if(Approx(base)){ // if pointing at a pole...
    temp.val[0] = 0.0;  // longitude is zero
    if(Approx(z)) return false; // zero vector
    else temp.val[1] = atan2(z, base); // set latitude
  }
  else{
    temp.val[1] = atan2(z, base); // set latitude
    temp.val[0] = atan2(y,x);  // set longitude
  }
  Set(temp.val[0], temp.val[1]);

  return true;
}

/////////////////////     CANGLE3      //////////////////////////

void CAngle3::Set(double A0, double A1, double A2){
  double c0,s0,c1,s1,c2,s2;
  m_ang[0].Set(A0);  m_ang[1].Set(A1);  m_ang[2].Set(A2);
  c0 = m_ang[0].GetCos(); s0 = m_ang[0].GetSin();
  c1 = m_ang[1].GetCos(); s1 = m_ang[1].GetSin();
  c2 = m_ang[2].GetCos(); s2 = m_ang[2].GetSin();

  m_vec.val[0] = s1*c0;
  m_vec.val[1] = s1*s0;
  m_vec.val[2] = c1;

  m_rot.val[0][0] =  c0*c1*c2 - s0*s2;
  m_rot.val[0][1] =  s0*c1*c2 + c0*s2;
  m_rot.val[0][2] =    -s1*c2;
  m_rot.val[1][0] = -c0*c1*s2 - s0*c2;
  m_rot.val[1][1] = -s0*c1*s2 + c0*c2;
  m_rot.val[1][2] =     s1*s2;
  m_rot.val[2][0] =  c0*s1;
  m_rot.val[2][1] =  s0*s1;
  m_rot.val[2][2] =     c1;

  m_cos.val[0] = c0; m_cos.val[1] = c1; m_cos.val[2] = c2;
  m_sin.val[0] = s0; m_sin.val[1] = s1; m_sin.val[2] = s2;
}

bool CAngle3::SetM(pMat3_t pMat3)                   // the rotation matrix -- returns false if incoming isn't a good rotation
{
  Vec3_t tmp;

  if(!Rotation_p(pMat3)) return false;

  if(pMat3->val[2][2] >  1.0) pMat3->val[2][2] =  1.0;
  if(pMat3->val[2][2] < -1.0) pMat3->val[2][2] = -1.0;
  tmp.val[1] = acos(pMat3->val[2][2]);
  if(!Approx(tmp.val[1])){
    tmp.val[0] = atan2( pMat3->val[2][1], pMat3->val[2][0]);
    tmp.val[2] = atan2(pMat3->val[1][2], -pMat3->val[0][2]);
  }
  else{
    tmp.val[2] = 0.0;
    tmp.val[0] = atan2(pMat3->val[0][1], pMat3->val[0][0]);
  }
  Set(tmp.val[0], tmp.val[1], tmp.val[2]);

  return true;
}

bool CAngle3::SetV(pVec3_t pAng3)                   // vector, where the log of the magnitude is the roll angle
{
  double r;
  Vec3_t temp;
  Vec3_t unit;

  r = Length(pAng3); if(Approx(r)) return false;
  temp.val[2] = log(r);

  UnitVector(pAng3, &unit);
  temp.val[1] = acos(unit.val[2]);
  if(Approx(fabs(temp.val[1]), 0.0)){ temp.val[0] = 0.0;}
  else{ temp.val[0] = atan2(unit.val[1],unit.val[0]); }

  Set(temp.val[0], temp.val[1], temp.val[2]);
  return true;
}
