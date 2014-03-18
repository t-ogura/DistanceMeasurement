#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "mathfuncs.h"



/* 
 * This class represents the transform from frame B to frame A.
 * Thus, it will operate on a point expressed in frame B and return that point expressed in frame A.
 * So if:
 *       BP is the point expressed in frame B
 *       AP is the point expressed in frame A
 *       APBorg is the location of origin of frame B expressed in frame A
 *       ABR is the rotation from frame A to frame B -- rows are A axes expressed in B (columns are B axes expressed in A)
 *       ABRT is transpose of ABR, rotates B to A: -- rows are B axes expressed in A (columns are A axes expressed in B)
 * 
 * Then ... 
 *       AP = ABR*BP + APBorg
 *
 * This transform is called ABT, such that AP = ABT*BP
 *
 * It will also operate on a frame that takes frame C to frame B and return a frame that takes frame C to frame A.
 *
 * Inverse: take a point expressed in frame A and return that point in frame B:
 *       BP = ABRT*(AP - APBorg)
 *          = ABRT*AP + (- ABRT*APBorg)
 * So ... we keep:
 *       m_offset = APBorg
 *       m_InvOffset = (- ABRT*APBorg)      // == BPAorg ... 
 *       m_ang encodes ABR 
 * and... Apply(BP)    will transform a point expressed in B to one expressed in A
 *        ApplyInv(AP) will transform a point expressed in A to one expressed in B

 *
 * Transform arithmetic: ACT = ABT*BCT
 *
 * Thus... ACT = Apply(BCT)
 * Thus... CAT = ApplyInv(CBT)
 *
 */

class CTransform     // checked in MathTest.cpp
{ 

 public:
  CTransform();
  ~CTransform(){;}
  
  bool Set(pMat3_t pRot, pVec3_t pVec);
  void Set(CAngle3* pAng, pVec3_t pVec){Mat3_t M; pAng->GetRot(&M); Set(&M, pVec);}

  void Get(pMat3_t pRot, pVec3_t pVec){ m_ang.GetRot(pRot); *pVec = m_offset;}
  void Get(CAngle3* pAng, pVec3_t pVec){ *pAng = m_ang; *pVec = m_offset;}
  void GetInv(pMat3_t pRot, pVec3_t pVec){ m_ang.GetRotInv(pRot); *pVec = m_InvOffset;}

  pVec3_t     Apply(pVec3_t Vin, pVec3_t Vout);            // takes a point in frame B and expresses it in frame A.
  CTransform* Apply(CTransform *Tin, CTransform *Tout);    // takes in BCT and produces ACT
  pVec3_t     ApplyInv(pVec3_t Vin, pVec3_t Vout);         // takes a point in frame A and expresses it in frame B.
  CTransform* ApplyInv(CTransform *Tin, CTransform *Tout); // Takes in CBT and produces CAT
  void Print();

 private:

  CAngle3 m_ang;      // rotation is encoded here
  Vec3_t m_offset;    // APBorg: represents origin of frame B expressed in frame A
  Vec3_t m_InvOffset; // BPAorg: represents origin of frame A expressed in frame B
  //  Mat3_t m_rot;       // ABR: rows represent axes of frame A expressed in B -- rotates vector in frame B into frame A
};


#endif
