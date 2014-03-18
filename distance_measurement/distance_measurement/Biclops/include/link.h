#ifndef _LINK_H_
#define _LINK_H_

/*
  This class is a very simple structure to hold some parameters for a straight cylindrical link.
  
  The incoming values are:  
           len: the length of the link, 
	   R: the two radii: [0] for the first, [1] for the second (going away from the base of the robot)

	   alpha is the angle between the cone and a straight cylinder (assuming R[0] > R[1], alpha > 0)
	   rho is the length of the diagonal.

  Outgoing values are:
           vals: [0]: len, [1]: alpha, [2]: rho
	   R: radii.
 */



#include "mathfuncs.h"

class CLink      // checked in MathTest.cpp
{

 public:
  CLink(){ m_len = 0.0; m_alpha = 0.0; m_rho = 0.0; SetZero(&m_R);}
  ~CLink(){;}
  
  void Set(double len, pVec2_t R);
  void Get(pVec3_t vals, pVec2_t R){ *R = m_R; vals->val[0] = m_len; vals->val[1] = m_alpha; vals->val[2] = m_rho;} // vals: len, alpha, rho
  double GetLen(){ return m_len;}
  double GetAlpha(){ return m_alpha;}
  double GetRho(){ return m_rho;}

  // private:
  double m_len;
  double m_alpha;
  double m_rho;
  Vec2_t m_R;
};


#endif
