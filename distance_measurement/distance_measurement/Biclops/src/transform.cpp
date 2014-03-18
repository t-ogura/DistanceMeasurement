//#include <cstdio>
#include <stdio.h>

// local
#include "../include/mathfuncs.h"

/////////////////////     Transform      //////////////////////////
CTransform::CTransform(){
  // Angle members are initialized by themselves
  SetZero(&m_offset);
  SetZero(&m_InvOffset);
}

bool CTransform::Set(pMat3_t pRot, pVec3_t pVec){
  Vec3_t tmpV;

  if(!Rotation_p(pRot)) return false;
  m_ang.SetM(pRot);
  m_offset = *pVec;
  Neg_v(m_ang.RotateInv(&m_offset, &tmpV), &m_InvOffset);

  return true;
}


// Vout = Rot*Vin + offset
pVec3_t CTransform::Apply(pVec3_t Vin, pVec3_t Vout) // takes a point in frame B and expresses it in frame A.
{
  Vec3_t Vtmp;

  Add_v(m_ang.Rotate(Vin, &Vtmp), &m_offset, Vout);
  return Vout;
}

// Vout = InvRot*Vin + Invoffset
pVec3_t CTransform::ApplyInv(pVec3_t Vin, pVec3_t Vout) // takes a point in frame A and expresses it in frame B.
{
  Vec3_t Vtmp;

  Add_v(m_ang.RotateInv(Vin, &Vtmp), &m_InvOffset, Vout);
  return Vout;
}

// ACT = ABT*BCT
CTransform* CTransform::Apply(CTransform *pTin, CTransform *pTout){
  Mat3_t mat1, mat2, Mtmp;
  Vec3_t vec1, vec2, vec3;

  pTin->Get(&mat1, &vec1);
  Mult_mm(m_ang.GetRot(&Mtmp), &mat1, &mat2);
  Add_v(m_ang.Rotate(&vec1, &vec2), &m_offset, &vec3);
  pTout->Set(&mat2, &vec3);
  return(pTout);
}

// CAT = CBT*BAT
CTransform* CTransform::ApplyInv(CTransform *pTin, CTransform *pTout){
  Mat3_t mat1, mat2, Mtmp;
  Vec3_t vec1, vec2, vec3;

  pTin->GetInv(&mat1, &vec1);
  Mult_mm(&mat1, m_ang.GetRotInv(&Mtmp), &mat2);
  Mult_mv(&mat1, &m_InvOffset, &vec2);
  Add_v(&vec2, &vec1, &vec3);
  pTout->Set(&mat2, &vec3);
  return pTout;
}

void CTransform::Print(){
  Mat3_t Mtmp;
  printf("Transform:\n");
  PrintStruct(m_ang.GetRot(&Mtmp));
  PrintStruct(&m_offset);
}
