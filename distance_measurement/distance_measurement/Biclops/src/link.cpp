#if defined WIN32
#pragma warning(disable: 4786) // suppresses warning about long identifiers
#endif

#include <math.h>

#include "../include/mathfuncs.h"

void CLink::Set(double len, pVec2_t R)
{
  double del;

  m_R = *R;
  
  if(m_R.val[0] < 0.0) m_R.val[0] = 0.0;
  if(m_R.val[1] < 0.0) m_R.val[1] = 0.0;
  del = R->val[0] - R->val[1];
  if(len <= 0.0)
    {
      m_len = 0.0;
      m_alpha = 0.0;
      m_rho = 0.0;
    }
  else{
    m_len = len;
    m_alpha = atan2(del, len);
    m_rho = Length(del, len);
  }

}

