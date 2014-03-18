this class doesn't seem to be used anywhere (BTW)
#ifndef _UTILITY_H_
#define _UTILITY_H_

#include "mathfuncs.h"

#define APPROX_THRESH 0.00001

bool Approx(double D1, double D2);
bool Approx(pVec2_t V1, pVec2_t V2);
bool Approx(pVec3_t V1, pVec3_t V2);
bool Approx(pMat2_t M1, pMat2_t M2);
bool Approx(pMat3_t M1, pMat3_t M2);
bool Approx(double D1); // checks relative to zero
bool Approx(pVec2_t V1); // checks relative to zero vector
bool Approx(pVec3_t V1); // checks relative to zero vector
bool Approx(pMat2_t M1); // checks relative to identity matrix
bool Approx(pMat3_t M1); // checks relative to identity matrix

inline double Square(double D){return( (D)*(D));}
#endif
