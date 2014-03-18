// Two functions still need to be verified

// Mostly tested in MathTest.cpp

#ifndef _MAT_VEC_H_
#define _MAT_VEC_H_

#include "mathfuncs.h"

// forward declarations
class CPlane;
class CLine2;
class CLine2Seg;

// approximately zero: 1e-6
#define APPROX_THRESH 0.000001
#define DET_THRESH 0.000001

typedef struct {
  double val[2];
} Vec2_t;
typedef Vec2_t *pVec2_t;

typedef struct {
  double val[3];
} Vec3_t;
typedef Vec3_t *pVec3_t;

typedef struct {
  double val[4];
} Vec4_t;
typedef Vec4_t *pVec4_t;

typedef struct {
  double val[5];
} Vec5_t;
typedef Vec5_t *pVec5_t;

typedef struct {
  double val[6];
} Vec6_t;
typedef Vec6_t *pVec6_t;

typedef struct {
  double val[7];
} Vec7_t;
typedef Vec7_t *pVec7_t;

typedef struct {
  double val[2][2];
} Mat2_t;
typedef Mat2_t *pMat2_t;

typedef struct {
  double val[3][3];
} Mat3_t;
typedef Mat3_t *pMat3_t;

extern pMat2_t gIMat2;
extern pMat3_t gIMat3;
extern pVec2_t gZVec2;
extern pVec3_t gZVec3;

void InitGlobals(); // checked in MathTest.cpp

double Square(double D); // checked in MathTest.cpp

double Length(double V1, double V2); // checked in MathTest.cpp
double Length(double V1, double V2, double V3); // checked in MathTest.cpp
double Length(pVec2_t Vin); // checked in MathTest.cpp
double Length(pVec3_t Vin); // checked in MathTest.cpp

bool Approx(double D1); // test relative to zero // checked in MathTest.cpp
bool Approx(pVec2_t V1); // test relative to zero vector // checked in MathTest.cpp
bool Approx(pVec3_t V1); // test relative to zero vector // checked in MathTest.cpp
bool Approx(pMat2_t M1); // test relative to identity matrix // checked in MathTest.cpp
bool Approx(pMat3_t M1); // test relative to identity matrix // checked in MathTest.cpp

bool Approx(double D1, double D2); // tests difference // checked in MathTest.cpp
bool Approx(pVec2_t V1, pVec2_t V2); // checked in MathTest.cpp
bool Approx(pVec3_t V1, pVec3_t V2); // checked in MathTest.cpp
bool Approx(pMat2_t M1, pMat2_t M2); // checked in MathTest.cpp
bool Approx(pMat3_t M1, pMat3_t M2); // checked in MathTest.cpp

pMat2_t Transpose(pMat2_t in, pMat2_t out); // checked in MathTest.cpp
pMat3_t Transpose(pMat3_t in, pMat3_t out); // checked in MathTest.cpp

double Det(pMat2_t); // checked in MathTest.cpp
double Det(pMat3_t); // checked in MathTest.cpp

bool Inverse(pMat2_t in, pMat2_t out); // checked in MathTest.cpp

bool Rotation_p(pMat2_t M); // checked in MathTest.cpp
bool Rotation_p(pMat3_t M); // checked in MathTest.cpp

pVec2_t Add_v(pVec2_t V1in, pVec2_t V2in, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t Add_v(pVec3_t V1in, pVec3_t V2in, pVec3_t Vout); // checked in MathTest.cpp
pVec2_t Sub_v(pVec2_t V1in, pVec2_t V2in, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t Sub_v(pVec3_t V1in, pVec3_t V2in, pVec3_t Vout); // checked in MathTest.cpp

pVec2_t Neg_v(pVec2_t Vin, pVec2_t Vout); // checked in MathTest.cpp
pVec2_t Neg_v(pVec2_t Vin); // checked in MathTest.cpp
pVec3_t Neg_v(pVec3_t Vin, pVec3_t Vout); // checked in MathTest.cpp
pVec3_t Neg_v(pVec3_t Vin); // checked in MathTest.cpp

pVec2_t Mult_sv(double s, pVec2_t Vin, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t Mult_sv(double s, pVec3_t Vin, pVec3_t Vout); // checked in MathTest.cpp

pVec2_t Mult_mv(pMat2_t Min, pVec2_t Vin, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t Mult_mv(pMat3_t Min, pVec3_t Vin, pVec3_t Vout); // checked in MathTest.cpp
pVec2_t Mult_vm(pMat2_t Min, pVec2_t Vin, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t Mult_vm(pMat3_t Min, pVec3_t Vin, pVec3_t Vout); // checked in MathTest.cpp

pMat2_t Mult_mm(pMat2_t M1in, pMat2_t M2in, pMat2_t Mout); // checked in MathTest.cpp
pMat3_t Mult_mm(pMat3_t M1in, pMat3_t M2in, pMat3_t Mout); // checked in MathTest.cpp

double Distance(pVec2_t V1, pVec2_t V2); // checked in MathTest.cpp
double Distance(pVec3_t V1, pVec3_t V2); // checked in MathTest.cpp

bool UnitVector(pVec2_t Vin, pVec2_t Vout); // checked in MathTest.cpp
bool UnitVector(pVec3_t Vin, pVec3_t Vout); // checked in MathTest.cpp
bool UnitVector(pVec2_t Vin, pVec2_t Vout, double *R); // checked in MathTest.cpp
bool UnitVector(pVec3_t Vin, pVec3_t Vout, double *R); // checked in MathTest.cpp
bool UnitVectorC(pMat2_t M, int ind, pVec2_t Vout); // checked in MathTest.cpp
bool UnitVectorR(pMat2_t M, int ind, pVec2_t Vout); // checked in MathTest.cpp
bool UnitVectorC(pMat3_t M, int ind, pVec3_t Vout); // checked in MathTest.cpp
bool UnitVectorR(pMat3_t M, int ind, pVec3_t Vout); // checked in MathTest.cpp

pMat2_t SetIdentity(pMat2_t Min); // checked in MathTest.cpp
pMat3_t SetIdentity(pMat3_t Min); // checked in MathTest.cpp
pVec2_t SetZero(pVec2_t Vin); // checked in MathTest.cpp
pVec3_t SetZero(pVec3_t Vin); // checked in MathTest.cpp

double Dot(pVec2_t V1, pVec2_t V2); // checked in MathTest.cpp
double Dot(pVec3_t V1, pVec3_t V2); // checked in MathTest.cpp
pVec2_t Dot(pVec2_t V1, pVec2_t V2, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t Dot(pVec3_t V1, pVec3_t V2, pVec3_t Vout); // checked in MathTest.cpp
double DotC(pVec2_t V1, pMat2_t M, int ind); // checked in MathTest.cpp
double DotC(pVec3_t V1, pMat3_t M, int ind); // checked in MathTest.cpp
pVec2_t DotC(pVec2_t V1, pMat2_t M, int ind, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t DotC(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout); // checked in MathTest.cpp
double DotR(pVec2_t V1, pMat2_t M, int ind); // checked in MathTest.cpp
double DotR(pVec3_t V1, pMat3_t M, int ind); // checked in MathTest.cpp
pVec2_t DotR(pVec2_t V1, pMat2_t M, int ind, pVec2_t Vout); // checked in MathTest.cpp
pVec3_t DotR(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout); // checked in MathTest.cpp

double  Cross(pVec2_t V1, pVec2_t V2); // checked in MathTest.cpp
double  Cross(pVec3_t V1, pVec3_t V2); // checked in MathTest.cpp
pVec3_t Cross(pVec3_t V1, pVec3_t V2, pVec3_t Vout); // checked in MathTest.cpp
double  CrossR(pVec3_t V1, pMat3_t M, int ind); // checked in MathTest.cpp
double  CrossC(pVec3_t V1, pMat3_t M, int ind); // checked in MathTest.cpp
pVec3_t CrossR(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout); // checked in MathTest.cpp
pVec3_t CrossC(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout); // checked in MathTest.cpp

void SplitCol(pMat2_t Mat, pVec2_t Vec[2]); // checked in MathTest.cpp
void SplitCol(pMat3_t Mat, pVec3_t Vec[3]); // checked in MathTest.cpp
void SplitRow(pMat2_t Mat, pVec2_t Vec[2]); // checked in MathTest.cpp
void SplitRow(pMat3_t Mat, pVec3_t Vec[3]); // checked in MathTest.cpp
pMat3_t GlueRow(pMat3_t Mat, pVec3_t Vec[3]); // checked in MathTest.cpp
pMat3_t GlueRow(pMat3_t Mat, pVec3_t Vec1, pVec3_t Vec2, pVec3_t Vec3); // checked in MathTest.cpp
pMat3_t GlueCol(pMat3_t Mat, pVec3_t Vec[3]); // checked in MathTest.cpp

pVec2_t Project(pVec3_t Vin, pMat3_t Rot, int plane, pVec2_t Vout); // plane: 0 for Y-Z, 1 for Z-X, 2 for X-Y. // checked in MathTest.cpp

// non-critical -- for debugging
void PrintStruct(pVec2_t Vin); // eyeballed code
void PrintStruct(pVec3_t Vin); // eyeballed code
void PrintStruct(pMat2_t Min); // eyeballed code
void PrintStruct(pMat3_t Min); // eyeballed code

bool InsideQuad_p(pVec2_t A[4], pVec2_t Pt); // checked in MathTest.cpp
bool InsideTriangle_p(pVec2_t A[3], pVec2_t Pt); // checked in MathTest.cpp
bool Inside_p(pVec2_t Min, pVec2_t Max, pVec2_t Pt); // checked in MathTest.cpp
bool Inside_p(pVec3_t Min, pVec3_t Max, pVec3_t Pt); // checked in MathTest.cpp
bool InsideCircle_p(pVec2_t Ctr, double Rad, pVec2_t Pt);
bool IntersectQuad_p(pVec2_t A[4], pVec2_t B[4]); // checked in MathTest.cpp
bool IntersectLineSegs_p(pVec2_t A1, pVec2_t A2, pVec2_t B1, pVec2_t B2); // checked in MathTest.cpp

// unchecked:
pVec2_t Project(pVec3_t Vin, CPlane *pP, int plane, pVec2_t Vout); // plane: 0 for Y-Z, 1 for Z-X, 2 for X-Y.  // needs CPlane verified first
bool IntersectCircleCircle_p(pVec2_t Ctr1, double Rad1, pVec2_t Ctr2, double Rad2);
bool IntersectCircleLine2_p(pVec2_t Ctr, double Rad, CLine2 *CL2);
bool IntersectCircleLine2Seg_p(pVec2_t Ctr, double Rad, CLine2Seg *CL2S);
bool IntersectCircleRectangle_p(pVec2_t Ctr, double Rad, pVec2_t Min, pVec2_t Max);
bool IntersectMinMax_p(pVec2_t X1, pVec2_t Y1, pVec2_t X2, pVec2_t Y2);





#endif
