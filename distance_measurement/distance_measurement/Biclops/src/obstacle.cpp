#include <cstdio>
//#include<stdio.h>

#include "../include/mathfuncs.h"

// Check whether a point is inside the obstacle 
bool CObstacle::Inside_p(pVec3_t P)
{
  return( (P->val[0] > Limit[0][0]) &&
	  (P->val[0] < Limit[0][1]) &&
	  (P->val[1] > Limit[1][0]) &&
	  (P->val[1] < Limit[1][1]) &&
	  (P->val[2] > Limit[2][0]) &&
	  (P->val[2] < Limit[2][1]));
}

// Check whether obstacles intersect
bool CObstacle::Intersect_p(CObstacle* pObst)
{ // it must be true in one of the dimensions that the segments in that dimension don't overlap
  if((Limit[0][0] > pObst->Limit[0][1]) || (pObst->Limit[0][0] > Limit[0][1])) return false;
  if((Limit[1][0] > pObst->Limit[1][1]) || (pObst->Limit[1][0] > Limit[1][1])) return false;
  if((Limit[2][0] > pObst->Limit[2][1]) || (pObst->Limit[2][0] > Limit[2][1])) return false;
  return true;
}


// This is slightly conservative -- may return true for situations that are physically close but not intersecting.
// Consider that a buffer zone. 
bool CObstacle::Intersect_p(CCylinder* pCyl)
{
  CPlane ThePlane;
  CLine3 TheLine;
  Vec2_t Phys;
  Vec3_t P3, V3;
  Vec2_t P2, V2;
  Vec2_t A[4], B[4];
  pVec2_t pA[4], pB[4];
  double R, L, alpha, theta, newL;
  int i;
  double rho1, rho2;
  Vec3_t del;
  Vec3_t Ctr;

  for(i = 0;i<4;i++)
    {
      pA[i] = &(A[i]); pB[i] = &(B[i]);
    }

  pCyl->GetLine(&TheLine); pCyl->GetPhys(&Phys);
  TheLine.Get(&P3, &V3);
  R = Phys.val[0];
  L = Phys.val[1];

  // A first, simple test is to check whether the two centers are further apart than the sum of the longest
  // radius within each object.  This will quickly filter out the pairs of objects that are too separated to matter.
  for(i = 0;i<3;i++){ del.val[i] = Limit[i][1] - Limit[i][0]; Ctr.val[i] = 0.5*(Limit[i][1] + Limit[i][0]);}
  rho1 = 0.5*Length(&del);
  rho2 = Length(L, R);
  if(Distance(&P3, &Ctr) > rho1 + rho2)return false;

  // If they're close enough to potentially hit, project cylinder and obstacles into axis planes and check for overlap.


  // Faces perp. to the z axis...
  // project X and Y limits
  A[0].val[0] =  Limit[0][0];  A[0].val[1] =  Limit[1][0];
  A[1].val[0] =  Limit[0][1];  A[1].val[1] =  Limit[1][0];
  A[2].val[0] =  Limit[0][1];  A[2].val[1] =  Limit[1][1];
  A[3].val[0] =  Limit[0][0];  A[3].val[1] =  Limit[1][1];

  // project cylinder onto XY plane
  P2.val[0] =  P3.val[0];
  P2.val[1] =  P3.val[1];
  V2.val[0] =  V3.val[0];
  V2.val[1] =  V3.val[1];

  theta = fabs(asin(V3.val[2]));
  newL = L*cos(theta) + R*sin(theta);

  alpha = atan2(V2.val[1], V2.val[0]);
  B[0].val[0] = P2.val[0] + newL*cos(alpha) + R*sin(alpha);
  B[1].val[0] = P2.val[0] + newL*cos(alpha) - R*sin(alpha);
  B[2].val[0] = P2.val[0] - newL*cos(alpha) - R*sin(alpha);
  B[3].val[0] = P2.val[0] - newL*cos(alpha) + R*sin(alpha);
  B[0].val[1] = P2.val[1] + newL*sin(alpha) - R*cos(alpha);
  B[1].val[1] = P2.val[1] + newL*sin(alpha) + R*cos(alpha);
  B[2].val[1] = P2.val[1] - newL*sin(alpha) + R*cos(alpha);
  B[3].val[1] = P2.val[1] - newL*sin(alpha) - R*cos(alpha);

  if(!IntersectQuad_p(pA, pB))return false; // if the projection of the cylinder doesn't overlap the obstacle, no collision
  // Faces perp. to the y axis...
  // project Z and X limits
  A[0].val[0] =  Limit[2][0];  A[0].val[1] =  Limit[0][0];
  A[1].val[0] =  Limit[2][1];  A[1].val[1] =  Limit[0][0];
  A[2].val[0] =  Limit[2][1];  A[2].val[1] =  Limit[0][1];
  A[3].val[0] =  Limit[2][0];  A[3].val[1] =  Limit[0][1];

  // project cylinder onto ZX plane
  P2.val[0] =  P3.val[2];
  P2.val[1] =  P3.val[0];
  V2.val[0] =  V3.val[2];
  V2.val[1] =  V3.val[0];

  theta = fabs(asin(V3.val[1]));
  newL = L*cos(theta) + R*sin(theta);

  alpha = atan2(V2.val[1], V2.val[0]);
  B[0].val[0] = P2.val[0] + newL*cos(alpha) + R*sin(alpha);
  B[1].val[0] = P2.val[0] + newL*cos(alpha) - R*sin(alpha);
  B[2].val[0] = P2.val[0] - newL*cos(alpha) - R*sin(alpha);
  B[3].val[0] = P2.val[0] - newL*cos(alpha) + R*sin(alpha);
  B[0].val[1] = P2.val[1] + newL*sin(alpha) - R*cos(alpha);
  B[1].val[1] = P2.val[1] + newL*sin(alpha) + R*cos(alpha);
  B[2].val[1] = P2.val[1] - newL*sin(alpha) + R*cos(alpha);
  B[3].val[1] = P2.val[1] - newL*sin(alpha) - R*cos(alpha);
  if(!IntersectQuad_p(pA, pB))return false; // if the projection of the cylinder doesn't overlap the obstacle, no collision

  // Faces perp. to the x axis...
  // project Y and Z limits
  A[0].val[0] =  Limit[1][0];  A[0].val[1] =  Limit[2][0];
  A[1].val[0] =  Limit[1][1];  A[1].val[1] =  Limit[2][0];
  A[2].val[0] =  Limit[1][1];  A[2].val[1] =  Limit[2][1];
  A[3].val[0] =  Limit[1][0];  A[3].val[1] =  Limit[2][1];

  // project cylinder onto YZ plane
  P2.val[0] =  P3.val[1];
  P2.val[1] =  P3.val[2];
  V2.val[0] =  V3.val[1];
  V2.val[1] =  V3.val[2];

  theta = fabs(asin(V3.val[0]));
  newL = L*cos(theta) + R*sin(theta);

  alpha = atan2(V2.val[1], V2.val[0]);
  B[0].val[0] = P2.val[0] + newL*cos(alpha) + R*sin(alpha);
  B[1].val[0] = P2.val[0] + newL*cos(alpha) - R*sin(alpha);
  B[2].val[0] = P2.val[0] - newL*cos(alpha) - R*sin(alpha);
  B[3].val[0] = P2.val[0] - newL*cos(alpha) + R*sin(alpha);
  B[0].val[1] = P2.val[1] + newL*sin(alpha) - R*cos(alpha);
  B[1].val[1] = P2.val[1] + newL*sin(alpha) + R*cos(alpha);
  B[2].val[1] = P2.val[1] - newL*sin(alpha) + R*cos(alpha);
  B[3].val[1] = P2.val[1] - newL*sin(alpha) - R*cos(alpha);

  if(!IntersectQuad_p(pA, pB)) return false; // if the projection of the cylinder doesn't overlap the obstacle, no collision

  // It is possible for all three to overlap and still not have a true collision, if cylinder straddles a corner.
  // For now, we'll call that a collision too.  

  return true;
}

//////////////////////////////////////         CObstacleGroup       //////////////////////////////



CObstacleGroup::CObstacleGroup()
{
  int i;
  for(i = 0;i < MAX_OBS_GRP_SIZE;i++) 
    {
      m_pObst[i] = NULL;
    } // loop i
  m_NumObs = 0;
}

CObstacleGroup::~CObstacleGroup()
{
  int i;
  for(i = 0;i < MAX_OBS_GRP_SIZE;i++) 
    {
      if(m_pObst[i] != NULL){ delete m_pObst[i]; m_pObst[i] = NULL;}
    } // loop i
}

void CObstacleGroup::ClearAll()
{
  int i;
  for(i = 0;i < MAX_OBS_GRP_SIZE;i++)
    {
      if(m_pObst[i]){ delete m_pObst[i]; m_pObst[i] = NULL;}
    }
  m_NumObs = 0;
}

bool CObstacleGroup::AddObstacle(pCObs pObs)
{
  if(m_NumObs == MAX_OBS_GRP_SIZE) return false;
  m_pObst[m_NumObs] = new CObstacle();
  *(m_pObst[m_NumObs]) = *pObs;
  m_NumObs++;
  return true;
}

bool CObstacleGroup::AddObstacle(pVec3_t Min, pVec3_t Max)
{
  if(m_NumObs == MAX_OBS_GRP_SIZE) return false;
  m_pObst[m_NumObs] = new CObstacle();
  (m_pObst[m_NumObs])->SetLimits(Min, Max);
  m_NumObs++;
  return true;
}

bool CObstacleGroup::AddObstacle(double Min[3], double Max[3])
{
  Vec3_t Min3, Max3;
  int i;
  for(i=0;i<3;i++){Min3.val[i] = Min[i]; Max3.val[i] = Max[i];}
  if(m_NumObs == MAX_OBS_GRP_SIZE) return false;
  m_pObst[m_NumObs] = new CObstacle();
  (m_pObst[m_NumObs])->SetLimits(&Min3, &Max3);
  m_NumObs++;
  return true;
}

bool CObstacleGroup::RemoveObstacle(int ObsNum)
{
  int i;
  if((ObsNum < 0) || (ObsNum > m_NumObs - 1)) return false;

  delete m_pObst[ObsNum];
  for(i = ObsNum;i < --m_NumObs;i++) m_pObst[i] = m_pObst[i+1];
  m_pObst[m_NumObs] = NULL;
  return true;
}

/* Returns the true pointers into the obstacle array */
int CObstacleGroup::GetObstacles(pCObs pObst[MAX_OBS_GRP_SIZE])
{
  int i;
  for(i = 0;i < MAX_OBS_GRP_SIZE;i++) 
    {
      if(m_pObst[i] != NULL) pObst[i] = m_pObst[i];
      else pObst[i] = NULL;
    } // loop i
  return m_NumObs;
}

bool CObstacleGroup::Intersect_p(CObstacle* pObst)
{
  int i;
  for(i = 0;i < m_NumObs; i++) 
    {
      if(m_pObst[i]->Intersect_p(pObst)) return true;
    }
  return false;
}

bool CObstacleGroup::Intersect_p(CObstacleGroup* pObstG)
{
  int i;
  for(i = 0;i < m_NumObs; i++) 
    {
      if(pObstG->Intersect_p(m_pObst[i])) return true;
    }
  return false;

}

bool CObstacleGroup::Intersect_p(CCylinder* pCyl)
{
  int i;
  for(i = 0;i < m_NumObs; i++) 
    {
      if(m_pObst[i]->Intersect_p(pCyl)) return true;
    }
  return false;
}

