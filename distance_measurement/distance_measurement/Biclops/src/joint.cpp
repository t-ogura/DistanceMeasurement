#include <math.h>

#include "../include/mathfuncs.h"

// All other methods are in joint.h
bool CJoint::Collide_p(CObstacleGroup &group) {
    return(group.Intersect_p(&m_cyl));
} // unchecked

// Takes the current Pos and the DH parameters and updates m_T.
// m_T transforms point expressed in output frame to same point expressed in input frame
void CJoint::UpdateTransform()
{
  Vec3_t P3;
  Mat3_t M3;
  double sal, cal, cth, sth;
  //  int i;

  cth = m_pos.GetCos();
  sth = m_pos.GetSin();

  sal = sin(m_DH.val[0]);
  cal = cos(m_DH.val[0]);

  P3.val[0] = m_DH.val[1];
  P3.val[1] = -sal*m_DH.val[2];
  P3.val[2] =  cal*m_DH.val[2];

  M3.val[0][0] =  cth;
  M3.val[0][1] = -sth;
  M3.val[0][2] =  0.0;

  M3.val[1][0] =  sth*cal;
  M3.val[1][1] =  cth*cal;
  M3.val[1][2] = -sal;

  M3.val[2][0] =  sth*sal;
  M3.val[2][1] =  cth*sal;
  M3.val[2][2] =  cal;
  m_T.Set(&M3, &P3);
}
