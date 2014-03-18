#include <stdio.h>
//#include <cstdio>
#include <math.h>

// local
#include "../include/mathfuncs.h"

Vec2_t  gZeroV2;
Vec3_t  gZeroV3;
pVec2_t gZVec2 = &gZeroV2;
pVec3_t gZVec3 = &gZeroV3;
Mat2_t  gIdentity2;
Mat3_t  gIdentity3;
pMat2_t gIMat2 = &gIdentity2;
pMat3_t gIMat3 = &gIdentity3;

double Square(double D){double tmpD = (D); return(tmpD*tmpD);}

void InitGlobals(){
  int i,j;
  for(i=0;i<2;i++) gZeroV2.val[i] = 0.0;
  for(i=0;i<3;i++) gZeroV3.val[i] = 0.0;
  for(i=0;i<2;i++) gIdentity2.val[i][i] = 1.0;
  for(i=0;i<2;i++) gIdentity2.val[i][1-i] = 0.0;
  for(i=0;i<3;i++)   for(j=0;j<3;j++)     gIdentity3.val[i][j] = 0.0;
  for(i=0;i<3;i++) gIdentity3.val[i][i] = 1.0;
}

double Length(double V1, double V2){ return(sqrt(Square(V1) + Square(V2)));}
double Length(double V1, double V2, double V3){ return(sqrt(Square(V1) + Square(V2) + Square(V3)));}
double Length(pVec2_t Vin){ return(Length(Vin->val[0], Vin->val[1]));}
double Length(pVec3_t Vin){ return(Length(Vin->val[0], Vin->val[1], Vin->val[2]));}


/*
 * Approximations
 *
 * NOTE: These are magnitude insensitive, so if two items are small enough, then they may be
 * wildly different and still be "approximately" the same.  There are theoretically better 
 * ways to to this, but these should work well enough.
 */

bool Approx(double D1)  { return(fabs(D1) < APPROX_THRESH);}
bool Approx(double V1, double V2){ return(Approx(V1-V2));}
bool Approx(pVec2_t V1) { return(Approx(Length(V1)));}
bool Approx(pVec3_t V1) { return(Approx(Length(V1)));}

bool Approx(pVec2_t V1, pVec2_t V2){ return(Approx(Distance(V1, V2)));}
bool Approx(pVec3_t V1, pVec3_t V2){ return(Approx(Distance(V1, V2)));}

bool Approx(pMat2_t M1) {  // compares to identity -- element by element
  return(Approx(M1->val[0][0], 1.0) && Approx(M1->val[1][1], 1.0) &&
	 Approx(M1->val[1][0]) && Approx(M1->val[0][1]));
}

bool Approx(pMat3_t M1) {// compares to identity -- element by element
  return(Approx(M1->val[0][0], 1.0) && Approx(M1->val[1][1], 1.0) && Approx(M1->val[2][2], 1.0) &&
	 Approx(M1->val[0][1]) && Approx(M1->val[1][2]) && Approx(M1->val[2][0]) &&
	 Approx(M1->val[0][2]) && Approx(M1->val[1][0]) && Approx(M1->val[2][1]));
}

bool Approx(pMat2_t M1, pMat2_t M2){ // compare element by element
  int i,j;
  for(i=0;i<2;i++)
    for(j=0;j<2;j++)
      if(!Approx(M1->val[i][j], M2->val[i][j])) return false;
  return true;
}

bool Approx(pMat3_t M1, pMat3_t M2){ // compare element by element
  int i,j;
  for(i=0;i<3;i++)
    for(j=0;j<3;j++)
      if(!Approx(M1->val[i][j], M2->val[i][j])) return false;
  return true;
}

double Dot(pVec2_t V1, pVec2_t V2){ return(V1->val[0]*V2->val[0] + V1->val[1]*V2->val[1]);}
double DotR(pVec2_t V1, pMat2_t M, int ind) // returns V1 dotted with ind row of M
{
  Vec2_t tmpV;
  int i;
  if((ind < 0)||(ind > 1)) return 0; // could be confused with a real value
  for(i=0;i<2;i++) tmpV.val[i] = M->val[ind][i];
  return(Dot(V1, &tmpV));
}

double DotC(pVec2_t V1, pMat2_t M, int ind) // returns V1 dotted with ind column of M
{
  Vec2_t tmpV;
  int i;
  if((ind < 0)||(ind > 1)) return 0; // could be confused with a real value
  for(i=0;i<2;i++) tmpV.val[i] = M->val[i][ind];
  return(Dot(V1, &tmpV));
}

pVec2_t Dot(pVec2_t V1, pVec2_t V2, pVec2_t Vout) // if V1 is zero, returns zero. otherwise, returns V2 projected onto V1
{
  Vec2_t tmp;
  if(!UnitVector(V1, &tmp)) return(SetZero(Vout));
  return(Mult_sv(Dot(V2, &tmp), &tmp, Vout));
}

pVec2_t DotC(pVec2_t V1, pMat2_t M, int ind, pVec2_t Vout) 
{
  Vec2_t tmpV;
  int i;
  if((ind < 0)||(ind > 1)) return(SetZero(Vout));
  for(i=0;i<2;i++) tmpV.val[i] = M->val[i][ind];
  return(Dot(&tmpV, V1, Vout));
}

pVec2_t DotR(pVec2_t V1, pMat2_t M, int ind, pVec2_t Vout) 
{
  Vec2_t tmpV;
  int i;
  if((ind < 0)||(ind > 1)) return(SetZero(Vout));
  for(i=0;i<2;i++) tmpV.val[i] = M->val[ind][i];
  return(Dot(&tmpV, V1, Vout));
}

double Dot(pVec3_t V1, pVec3_t V2){ return(V1->val[0]*V2->val[0] + V1->val[1]*V2->val[1] + V1->val[2]*V2->val[2]);}

double DotC(pVec3_t V1, pMat3_t M, int ind)
{
  Vec3_t tmpV;
  int i;
  if((ind < 0)||(ind > 2)) return 0; // could be confused with a real value
  for(i=0;i<3;i++) tmpV.val[i] = M->val[i][ind];
  return(Dot(V1, &tmpV));
}

double DotR(pVec3_t V1, pMat3_t M, int ind)
{
  Vec3_t tmpV;
  int i;
  if((ind < 0)||(ind > 2)) return 0; // could be confused with a real value
  for(i=0;i<3;i++) tmpV.val[i] = M->val[ind][i];
  return(Dot(V1, &tmpV));
}

pVec3_t Dot(pVec3_t V1, pVec3_t V2, pVec3_t Vout) // if V1 is zero, returns zero. otherwise, returns V2 projected onto V1
{
  Vec3_t tmp;
  if(!UnitVector(V1, &tmp)) return(SetZero(Vout));
  return(Mult_sv(Dot(V2, &tmp), &tmp, Vout));
}

pVec3_t DotC(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout) // if V1 is zero, returns zero. otherwise, returns V1 projected onto col ind of M
{
  Vec3_t tmpV;
  int i;
  if((ind < 0)||(ind > 2)) return(SetZero(Vout));
  for(i=0;i<3;i++) tmpV.val[i] = M->val[i][ind];
  return(Dot(&tmpV, V1, Vout));
}

pVec3_t DotR(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout) // if V1 is zero, returns zero. otherwise, returns V1 projected onto row ind of M
{
  Vec3_t tmpV;
  int i;
  if((ind < 0)||(ind > 2)) return(SetZero(Vout));
  for(i=0;i<3;i++) tmpV.val[i] = M->val[ind][i];
  return(Dot(&tmpV, V1, Vout));
}


double  Cross(pVec2_t V1, pVec2_t V2){ return(V1->val[0]*V2->val[1] - V1->val[1]*V2->val[0]);}
double  Cross(pVec3_t V1, pVec3_t V2){ Vec3_t tmp; return(Length(Cross(V1, V2, &tmp)));}

pVec3_t Cross(pVec3_t V1, pVec3_t V2, pVec3_t Vout){
  Vout->val[0] = V1->val[1]*V2->val[2] - V1->val[2]*V2->val[1];
  Vout->val[1] = V1->val[2]*V2->val[0] - V1->val[0]*V2->val[2];
  Vout->val[2] = V1->val[0]*V2->val[1] - V1->val[1]*V2->val[0];
  return(Vout);
}

double  CrossR(pVec3_t V1, pMat3_t M, int ind) { Vec3_t tmp; return(Length(CrossR(V1, M, ind, &tmp)));} // unsigned
double  CrossC(pVec3_t V1, pMat3_t M, int ind) { Vec3_t tmp; return(Length(CrossC(V1, M, ind, &tmp)));} // unsigned

pVec3_t CrossR(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout){
  Vec3_t tmpV;
  int i;
  if((ind < 0)||(ind > 2)) return(SetZero(Vout));
  for(i=0;i<3;i++) tmpV.val[i] = M->val[ind][i];
  return(Cross(V1, &tmpV, Vout));
}

pVec3_t CrossC(pVec3_t V1, pMat3_t M, int ind, pVec3_t Vout){
  Vec3_t tmpV;
  int i;
  if((ind < 0)||(ind > 2)) return(SetZero(Vout));
  for(i=0;i<3;i++) tmpV.val[i] = M->val[i][ind];
  return(Cross(V1, &tmpV, Vout));
}

double Det(pMat2_t M){ return(M->val[0][0]*M->val[1][1] - M->val[1][0]*M->val[0][1]);}

double Det(pMat3_t M){
return(M->val[0][0]*(M->val[1][1]*M->val[2][2] - M->val[1][2]*M->val[2][1]) +
       M->val[0][1]*(M->val[1][2]*M->val[2][0] - M->val[1][0]*M->val[2][2]) + 
       M->val[0][2]*(M->val[1][0]*M->val[2][1] - M->val[1][1]*M->val[2][0]));
}

pMat2_t Transpose(pMat2_t in, pMat2_t out){
  out->val[0][0] = in->val[0][0];
  out->val[0][1] = in->val[1][0];
  out->val[1][0] = in->val[0][1];
  out->val[1][1] = in->val[1][1];
  return(out);
}

pMat3_t Transpose(pMat3_t in, pMat3_t out){
  out->val[0][0] = in->val[0][0];
  out->val[0][1] = in->val[1][0];
  out->val[0][2] = in->val[2][0];
  out->val[1][0] = in->val[0][1];
  out->val[1][1] = in->val[1][1];
  out->val[1][2] = in->val[2][1];
  out->val[2][0] = in->val[0][2];
  out->val[2][1] = in->val[1][2];
  out->val[2][2] = in->val[2][2];
  return(out);
}

bool Inverse(pMat2_t in, pMat2_t out){
  double det = Det(in);
  
  if(Approx(det)) return false;

  out->val[0][0] =  in->val[1][1] / det;
  out->val[0][1] = -in->val[0][1] / det;
  out->val[1][0] = -in->val[1][0] / det;
  out->val[1][1] =  in->val[0][0] / det;
  return true;
}

pMat2_t Mult_mm(pMat2_t M1in, pMat2_t M2in, pMat2_t Mout){
  //  Mout->val[i][j] = sum over k: M1in->val[i][k]*M2in->val[k][j];
  Mout->val[0][0] = M1in->val[0][0]*M2in->val[0][0] + M1in->val[0][1]*M2in->val[1][0];
  Mout->val[0][1] = M1in->val[0][0]*M2in->val[0][1] + M1in->val[0][1]*M2in->val[1][1];
  Mout->val[1][0] = M1in->val[1][0]*M2in->val[0][0] + M1in->val[1][1]*M2in->val[1][0];
  Mout->val[1][1] = M1in->val[1][0]*M2in->val[0][1] + M1in->val[1][1]*M2in->val[1][1];
  return(Mout);
}

pMat3_t Mult_mm(pMat3_t M1in, pMat3_t M2in, pMat3_t Mout){
  //  Mout->val[i][j] = sum over k: M1in->val[i][k]*M2in->val[k][j];
  Mout->val[0][0] = M1in->val[0][0]*M2in->val[0][0] + M1in->val[0][1]*M2in->val[1][0] + M1in->val[0][2]*M2in->val[2][0];
  Mout->val[0][1] = M1in->val[0][0]*M2in->val[0][1] + M1in->val[0][1]*M2in->val[1][1] + M1in->val[0][2]*M2in->val[2][1];
  Mout->val[0][2] = M1in->val[0][0]*M2in->val[0][2] + M1in->val[0][1]*M2in->val[1][2] + M1in->val[0][2]*M2in->val[2][2];
  Mout->val[1][0] = M1in->val[1][0]*M2in->val[0][0] + M1in->val[1][1]*M2in->val[1][0] + M1in->val[1][2]*M2in->val[2][0];
  Mout->val[1][1] = M1in->val[1][0]*M2in->val[0][1] + M1in->val[1][1]*M2in->val[1][1] + M1in->val[1][2]*M2in->val[2][1];
  Mout->val[1][2] = M1in->val[1][0]*M2in->val[0][2] + M1in->val[1][1]*M2in->val[1][2] + M1in->val[1][2]*M2in->val[2][2];
  Mout->val[2][0] = M1in->val[2][0]*M2in->val[0][0] + M1in->val[2][1]*M2in->val[1][0] + M1in->val[2][2]*M2in->val[2][0];
  Mout->val[2][1] = M1in->val[2][0]*M2in->val[0][1] + M1in->val[2][1]*M2in->val[1][1] + M1in->val[2][2]*M2in->val[2][1];
  Mout->val[2][2] = M1in->val[2][0]*M2in->val[0][2] + M1in->val[2][1]*M2in->val[1][2] + M1in->val[2][2]*M2in->val[2][2];
  return(Mout);
}


pVec2_t Mult_mv(pMat2_t Min, pVec2_t Vin, pVec2_t Vout){
  Vout->val[0] = Min->val[0][0]*Vin->val[0] + Min->val[0][1]*Vin->val[1];
  Vout->val[1] = Min->val[1][0]*Vin->val[0] + Min->val[1][1]*Vin->val[1];
  return(Vout);
} 

pVec3_t Mult_mv(pMat3_t Min, pVec3_t Vin, pVec3_t Vout){
  Vout->val[0] = Min->val[0][0]*Vin->val[0] + Min->val[0][1]*Vin->val[1] + Min->val[0][2]*Vin->val[2];
  Vout->val[1] = Min->val[1][0]*Vin->val[0] + Min->val[1][1]*Vin->val[1] + Min->val[1][2]*Vin->val[2];
  Vout->val[2] = Min->val[2][0]*Vin->val[0] + Min->val[2][1]*Vin->val[1] + Min->val[2][2]*Vin->val[2];
  return(Vout);
} 

pVec2_t Mult_vm(pMat2_t Min, pVec2_t Vin, pVec2_t Vout){
  Vout->val[0] = Min->val[0][0]*Vin->val[0] + Min->val[1][0]*Vin->val[1];
  Vout->val[1] = Min->val[0][1]*Vin->val[0] + Min->val[1][1]*Vin->val[1];
  return(Vout);
} 

pVec3_t Mult_vm(pMat3_t Min, pVec3_t Vin, pVec3_t Vout){
  Vout->val[0] = Min->val[0][0]*Vin->val[0] + Min->val[1][0]*Vin->val[1] + Min->val[2][0]*Vin->val[2];
  Vout->val[1] = Min->val[0][1]*Vin->val[0] + Min->val[1][1]*Vin->val[1] + Min->val[2][1]*Vin->val[2];
  Vout->val[2] = Min->val[0][2]*Vin->val[0] + Min->val[1][2]*Vin->val[1] + Min->val[2][2]*Vin->val[2];
  return(Vout);
} 

pVec2_t Mult_sv(double s, pVec2_t Vin, pVec2_t Vout){ Vout->val[0] = s*Vin->val[0]; Vout->val[1] = s*Vin->val[1]; return(Vout);}

pVec3_t Mult_sv(double s, pVec3_t Vin, pVec3_t Vout){
  Vout->val[0] = s*Vin->val[0]; 
  Vout->val[1] = s*Vin->val[1];
  Vout->val[2] = s*Vin->val[2];
  return(Vout);
}

pVec2_t Add_v(pVec2_t V1in, pVec2_t V2in, pVec2_t Vout){ 
  Vout->val[0] = V1in->val[0] + V2in->val[0];
  Vout->val[1] = V1in->val[1] + V2in->val[1];
  return(Vout);
}

pVec3_t Add_v(pVec3_t V1in, pVec3_t V2in, pVec3_t Vout){
  Vout->val[0] = V1in->val[0] + V2in->val[0];
  Vout->val[1] = V1in->val[1] + V2in->val[1];
  Vout->val[2] = V1in->val[2] + V2in->val[2];
  return(Vout);
}

pVec2_t Sub_v(pVec2_t V1in, pVec2_t V2in, pVec2_t Vout){
  Vout->val[0] = V1in->val[0] - V2in->val[0];
  Vout->val[1] = V1in->val[1] - V2in->val[1];
  return(Vout);
}

pVec3_t Sub_v(pVec3_t V1in, pVec3_t V2in, pVec3_t Vout){
  Vout->val[0] = V1in->val[0] - V2in->val[0];
  Vout->val[1] = V1in->val[1] - V2in->val[1];
  Vout->val[2] = V1in->val[2] - V2in->val[2];
  return(Vout);
}

pVec2_t Neg_v(pVec2_t Vin, pVec2_t Vout){ Vout->val[0] = -Vin->val[0]; Vout->val[1] = -Vin->val[1]; return(Vout);}
pVec2_t Neg_v(pVec2_t Vin){ Vin->val[0] = -Vin->val[0]; Vin->val[1] = -Vin->val[1]; return(Vin);}

pVec3_t Neg_v(pVec3_t Vin, pVec3_t Vout){ 
  Vout->val[0] = -Vin->val[0];
  Vout->val[1] = -Vin->val[1];
  Vout->val[2] = -Vin->val[2];
  return(Vout);
}

pVec3_t Neg_v(pVec3_t Vin){ 
  Vin->val[0] = -Vin->val[0];
  Vin->val[1] = -Vin->val[1];
  Vin->val[2] = -Vin->val[2];
  return(Vin);
}

double Distance(pVec2_t V1, pVec2_t V2){ Vec2_t tmp; return(Length(Sub_v(V1, V2, &tmp)));}
double Distance(pVec3_t V1, pVec3_t V2){ Vec3_t tmp; return(Length(Sub_v(V1, V2, &tmp)));}

pMat2_t SetIdentity(pMat2_t Min){
  Min->val[0][0] = 1.0; Min->val[1][1] = 1.0;
  Min->val[1][0] = 0.0; Min->val[0][1] = 0.0;
  return(Min);
}

pMat3_t SetIdentity(pMat3_t Min){
  Min->val[0][0] = 1.0; Min->val[1][1] = 1.0; Min->val[2][2] = 1.0;
  Min->val[0][1] = 0.0; Min->val[1][2] = 0.0; Min->val[2][0] = 0.0;
  Min->val[0][2] = 0.0; Min->val[2][1] = 0.0; Min->val[1][0] = 0.0;
  return(Min);
}

pVec2_t SetZero(pVec2_t Vin){ Vin->val[0] = 0.0; Vin->val[1] = 0.0; return(Vin);}
pVec3_t SetZero(pVec3_t Vin){ Vin->val[0] = 0.0; Vin->val[1] = 0.0; Vin->val[2] = 0.0; return(Vin);}

void SplitCol(pMat2_t Mat, pVec2_t Vec[2]){
  Vec[0]->val[0] = Mat->val[0][0]; Vec[0]->val[1] = Mat->val[1][0];
  Vec[1]->val[0] = Mat->val[0][1]; Vec[1]->val[1] = Mat->val[1][1];
}

void SplitCol(pMat3_t Mat, pVec3_t Vec[3]){
  Vec[0]->val[0] = Mat->val[0][0]; Vec[0]->val[1] = Mat->val[1][0]; Vec[0]->val[2] = Mat->val[2][0];
  Vec[1]->val[0] = Mat->val[0][1]; Vec[1]->val[1] = Mat->val[1][1]; Vec[1]->val[2] = Mat->val[2][1];
  Vec[2]->val[0] = Mat->val[0][2]; Vec[2]->val[1] = Mat->val[1][2]; Vec[2]->val[2] = Mat->val[2][2];
}

void SplitRow(pMat2_t Mat, pVec2_t Vec[2]){
  Vec[0]->val[0] = Mat->val[0][0]; Vec[0]->val[1] = Mat->val[0][1];
  Vec[1]->val[0] = Mat->val[1][0]; Vec[1]->val[1] = Mat->val[1][1];
}

void SplitRow(pMat3_t Mat, pVec3_t Vec[3]){
  Vec[0]->val[0] = Mat->val[0][0]; Vec[0]->val[1] = Mat->val[0][1]; Vec[0]->val[2] = Mat->val[0][2];
  Vec[1]->val[0] = Mat->val[1][0]; Vec[1]->val[1] = Mat->val[1][1]; Vec[1]->val[2] = Mat->val[1][2];
  Vec[2]->val[0] = Mat->val[2][0]; Vec[2]->val[1] = Mat->val[2][1]; Vec[2]->val[2] = Mat->val[2][2];
}

pMat3_t GlueRow(pMat3_t Mat, pVec3_t Vec[3]){
  int i,j;
  for(i = 0;i<3;i++)for(j = 0;j<3;j++) Mat->val[i][j] = Vec[i]->val[j]; 
  return Mat;
}

pMat3_t GlueRow(pMat3_t Mat, pVec3_t Vec1, pVec3_t Vec2, pVec3_t Vec3){
  int i;
  for(i = 0;i<3;i++)
    {
      Mat->val[0][i] = Vec1->val[i]; Mat->val[1][i] = Vec2->val[i]; Mat->val[2][i] = Vec3->val[i]; 
    }
  return Mat;
}

pMat3_t GlueCol(pMat3_t Mat, pVec3_t Vec[3]){
  int i,j;
  for(i = 0;i<3;i++)for(j = 0;j<3;j++) Mat->val[j][i] = Vec[i]->val[j]; 
  return Mat;
}


bool UnitVector(pVec2_t Vin, pVec2_t Vout) // creates a unit vector in direction of Vin -- returns false if Vin is zero
{
  double r = Length(Vin);  
  if(Approx(r)) return false;
  Mult_sv(1.0/r, Vin, Vout);
  return true;
}


bool UnitVector(pVec2_t Vin, pVec2_t Vout, double *R) // creates a unit vector in direction of Vin -- returns false if Vin is zero
{
  *R = Length(Vin);  
  if(Approx(*R)) return false;
  Mult_sv(1.0/(*R), Vin, Vout);
  return true;
}


  //-- returns false if Vin is zero or bad index
bool UnitVectorR(pMat2_t M, int ind, pVec2_t Vout) // creates a unit vector in direction of ind row of M 
{
  Vec2_t V1;
  if((ind < 0)||(ind > 1)) return false;
  V1.val[0] = M->val[ind][0]; V1.val[1] = M->val[ind][1];
  return UnitVector(&V1, Vout);
}

  //-- returns false if Vin is zero or bad index
bool UnitVectorC(pMat2_t M, int ind, pVec2_t Vout) // creates a unit vector in direction of ind col of M 
{
  Vec2_t V1;
  if((ind < 0)||(ind > 1)) return false;
  V1.val[0] = M->val[0][ind]; V1.val[1] = M->val[1][ind];
  return UnitVector(&V1, Vout);
}

bool UnitVector(pVec3_t Vin, pVec3_t Vout)
{
  double r = Length(Vin);  
  if(Approx(r)) return false;
  Mult_sv(1.0/r, Vin, Vout);
  return true;
}

bool UnitVector(pVec3_t Vin, pVec3_t Vout, double *R)
{
  *R = Length(Vin);  
  if(Approx(*R)) return false;
  Mult_sv(1.0/(*R), Vin, Vout);
  return true;
}

bool UnitVectorR(pMat3_t M, int ind, pVec3_t Vout)
{
  Vec3_t V1;
  if((ind < 0)||(ind > 2)) return false;
    for(int k=0;k<3;k++) V1.val[k] = M->val[ind][k]; 
  return UnitVector(&V1, Vout);
}

bool UnitVectorC(pMat3_t M, int ind, pVec3_t Vout)
{
  Vec3_t V1;
  if((ind < 0)||(ind > 2)) return false;
    for(int k=0;k<3;k++) V1.val[k] = M->val[k][ind]; 
  return UnitVector(&V1, Vout);
}


// if det is 1 and structure is a;b;-b;a, it has to be a rotation!
bool Rotation_p(pMat2_t M)
{
  if(!Approx(Det(M), 1.0)) return false;
  if(!Approx(M->val[0][0], M->val[1][1])) return false;
  if(!Approx(M->val[1][0], -M->val[0][1])) return false;

  return true;
}

// if det is 1 and the cross product of each pair of rows produces the third, must be a rotation
bool Rotation_p(pMat3_t M)
{
  Vec3_t tmp;
  Vec3_t Vvec1[3];
  pVec3_t VvecR[3];

  VvecR[0] = &(Vvec1[0]);  VvecR[1] = &(Vvec1[1]);  VvecR[2] = &(Vvec1[2]);

  if(!Approx(Det(M), 1.0)) return false;

  SplitRow(M, VvecR);

  if(!Approx(Cross(VvecR[0], VvecR[1], &tmp), VvecR[2])) return false;
  if(!Approx(Cross(VvecR[1], VvecR[2], &tmp), VvecR[0])) return false;
  if(!Approx(Cross(VvecR[2], VvecR[0], &tmp), VvecR[1])) return false;
  return true;
}

/*
 * Vin is the vector in World coordinates.  It must be rotated into the new coord system, then projected down to the
 * appropriate plane.  NOTE: Rot holds the axes of the new coord system (rep in W) in its rows.
 * This is no a full transform, as it is assumed the origins coincide.
 */

pVec2_t Project(pVec3_t Vin, pMat3_t Rot, int plane, pVec2_t Vout) // plane: 0 for Y-Z, 1 for Z-X, 2 for X-Y.
{
  Vec3_t V3out;

  // Rotate Vin ...
  Mult_mv(Rot, Vin, &V3out);
  
  // Project...
  switch(plane){
  case 0: // Y to X;  Z to Y
    Vout->val[0] =  V3out.val[1];
    Vout->val[1] =  V3out.val[2];
    break;
  case 1: //  Z to X;  X to Y
    Vout->val[0] =  V3out.val[2];
    Vout->val[1] =  V3out.val[0];
    break;
  case 2: // X to X; Y to Y
    Vout->val[0] =  V3out.val[0];
    Vout->val[1] =  V3out.val[1];
    break;
  }// switch on plane
  return Vout;
}

pVec2_t Project(pVec3_t Vin, pCPlane pP, int plane, pVec2_t Vout) // plane: 0 for Y-Z, 1 for Z-X, 2 for X-Y.
{
  Vec3_t P;
  Mat3_t M;
  pP->Get(&P, &M);
  return(Project(Vin, &M, plane, Vout));
}


/*
 * These are for debugging.
 * They will need to be commented out for windows.
 */

void PrintStruct(pVec2_t Vin){
  printf("2D Vector: %10.8g\t%10.8g\n", Vin->val[0], Vin->val[1]);
}

void PrintStruct(pVec3_t Vin){
  printf("3D Vector: %10.8g\t%10.8g\t%10.8g\n", Vin->val[0], Vin->val[1], Vin->val[2]);
}

void PrintStruct(pMat2_t Min){
  printf("2D Matrix: %10.8g\t%10.8g\n", Min->val[0][0], Min->val[0][1]);
  printf("           %10.8g\t%10.8g\n", Min->val[1][0], Min->val[1][1]);
}

void PrintStruct(pMat3_t Min){
  printf("3D Matrix: %10.8g\t%10.8g\t%10.8g\n", Min->val[0][0], Min->val[0][1], Min->val[0][2]);
  printf("           %10.8g\t%10.8g\t%10.8g\n", Min->val[1][0], Min->val[1][1], Min->val[1][2]);
  printf("           %10.8g\t%10.8g\t%10.8g\n", Min->val[2][0], Min->val[2][1], Min->val[2][2]);
}


/* Given two line segments: [A1, A2] and [B1, B2], return true if they cross.
 */
bool IntersectLineSegs_p(pVec2_t A1, pVec2_t A2, pVec2_t B1, pVec2_t B2)
{
  Vec2_t DA, DB, DC;
  Vec2_t del1;

  Sub_v(A2, A1, &DA);
  Sub_v(B1, A1, &DC);

  if((Cross(&DA, &DC) > 0) == (Cross(&DA, Sub_v(B2, A1, &del1)) > 0)) return false;

  Sub_v(B2, B1, &DB);

  if((Cross(&DB, &DC) > 0) != (Cross(&DB, Sub_v(A2, B1, &del1)) > 0)) return false;

  return true;
}

/* Given two arbitrary quadrilaterals, do they overlap?   */
/* Result may not be quite as expected if one or both of the quads are self-intersecting. */
bool IntersectQuad_p(pVec2_t A[4], pVec2_t B[4])
{
  int i,j;
  // Check whether any of the lines cross...
  if(IntersectLineSegs_p(A[0], A[3], B[0], B[3])) return true;
  for(i= 1;i<4;i++){
    if(IntersectLineSegs_p(A[0], A[3], B[i], B[i-1])) return true;
    if(IntersectLineSegs_p(A[i], A[i-1], B[0], B[3])) return true;
    for(j = 1;j<4;j++) if(IntersectLineSegs_p(A[j], A[j-1], B[i], B[i-1])) return true;
  } // loop i

  // But... what if one quad is entirely inside the other?
  if((InsideQuad_p(A, B[0])) || (InsideQuad_p(B, A[0]))) return true;

  return false;
}

bool Inside_p(pVec2_t Min, pVec2_t Max, pVec2_t Pt)
{
  return((Pt->val[0] > Min->val[0]) && (Pt->val[0] < Max->val[0]) &&
	 (Pt->val[1] > Min->val[1]) && (Pt->val[1] < Max->val[1]));
}

bool Inside_p(pVec3_t Min, pVec3_t Max, pVec3_t Pt)
{
  return((Pt->val[0] > Min->val[0]) && (Pt->val[0] < Max->val[0]) &&
	 (Pt->val[1] > Min->val[1]) && (Pt->val[1] < Max->val[1]) &&
	 (Pt->val[2] > Min->val[2]) && (Pt->val[2] < Max->val[2]));
}

/*
  There are three categories of quadrilateral: concave, convex, and self-intersecting
  This routine will return false for self-intersecting quads,
  otherwise will return true when the test point is enclosed by the quad.  
*/
bool InsideQuad_p(pVec2_t A[4], pVec2_t Pt)
{
  Vec2_t del1,del2;
  Vec2_t tmpA[3];
  pVec2_t ptmpA[3];
  int i;
  bool res = false;

  for(i=0;i<3;i++) ptmpA[i] = &tmpA[i];

  if(Cross(Sub_v(A[1], A[0], &del1),Sub_v(A[3], A[0], &del2)) > 0)
    { // tri 0-1-3 is counterclockwise
      if(Cross(Sub_v(A[2], A[1], &del1),Sub_v(A[3], A[1], &del2)) > 0)
	{ // 0 and 2 are on opposite sides of line 1-3
	  ptmpA[0] = A[1]; ptmpA[1] = A[3]; 
	  ptmpA[2] = A[0]; res |= InsideTriangle_p(ptmpA, Pt);
	  ptmpA[2] = A[2]; res |= InsideTriangle_p(ptmpA, Pt);
	}
      else if((Cross(Sub_v(A[1], A[0], &del1),Sub_v(A[2], A[0], &del2)) > 0) != 
	      (Cross(Sub_v(A[3], A[0], &del1),Sub_v(A[2], A[0], &del2)) > 0))
	{ // 1 and 3 are on opposite sides of line 0-2
	  ptmpA[0] = A[0]; ptmpA[1] = A[2]; 
	  ptmpA[2] = A[1]; res |= InsideTriangle_p(ptmpA, Pt);
	  ptmpA[2] = A[3]; res |= InsideTriangle_p(ptmpA, Pt);
	}
      else{
	res = false; // self-intersecting
      }
    }
  else
    { // tri 0-1-3 is clockwise
      if(Cross(Sub_v(A[2], A[1], &del1),Sub_v(A[3], A[1], &del2)) < 0)
	{ // 0 and 2 are on opposite sides of line 1-3
	  ptmpA[0] = A[1]; ptmpA[1] = A[3]; 
	  ptmpA[2] = A[0]; res = InsideTriangle_p(ptmpA, Pt);
	  ptmpA[2] = A[2]; res |= InsideTriangle_p(ptmpA, Pt);
	}
      else if((Cross(Sub_v(A[1], A[0], &del1),Sub_v(A[2], A[0], &del2)) > 0) != 
	      (Cross(Sub_v(A[3], A[0], &del1),Sub_v(A[2], A[0], &del2)) > 0))
	{ // 1 and 3 are on opposite sides of line 0-2
	  ptmpA[0] = A[0]; ptmpA[1] = A[2]; 
	  ptmpA[2] = A[1]; res |= InsideTriangle_p(ptmpA, Pt);
	  ptmpA[2] = A[3]; res |= InsideTriangle_p(ptmpA, Pt);
	}
      else
	{
	  res = false; // self-intersecting
	}
    }
  return res;
}

bool InsideTriangle_p(pVec2_t A[3], pVec2_t Pt)
{
  Vec2_t del1, del2;
  if(Cross(Sub_v(A[0], A[2], &del1), Sub_v(A[1], A[2], &del2)) < 0) 
    { // listed clockwise
      if(Cross(Sub_v(A[1], A[2], &del1),Sub_v(Pt, A[2], &del2)) < 0) return false;
      if(Cross(Sub_v(A[2], A[0], &del1),Sub_v(Pt, A[0], &del2)) < 0) return false;
      if(Cross(Sub_v(A[0], A[1], &del1),Sub_v(Pt, A[1], &del2)) < 0) return false;
    }
  else
    { // listed counterclockwise
      if(Cross(Sub_v(A[0], A[2], &del1),Sub_v(Pt, A[2], &del2)) < 0) return false;
      if(Cross(Sub_v(A[1], A[0], &del1),Sub_v(Pt, A[0], &del2)) < 0) return false;
      if(Cross(Sub_v(A[2], A[1], &del1),Sub_v(Pt, A[1], &del2)) < 0) return false;
    }
  return true;
}


bool IntersectCircleLine2Seg_p(pVec2_t Ctr, double Rad, pCLine2Seg CL2S)
{
  Vec2_t P1, P2;
  double D;
  if(CL2S->L2Distance(Ctr) > Rad) return false;
  CL2S->GetEndPts(&P1, &P2);
  if(InsideCircle_p(Ctr, Rad, &P1)) return true;
  if(InsideCircle_p(Ctr, Rad, &P2)) return true;
  return(CL2S->ClosestPtIn(Ctr, &D));
}

bool IntersectCircleRectangle_p(pVec2_t Ctr, double Rad, pVec2_t Min, pVec2_t Max)
{
  CLine2Seg CL2S;
  Vec2_t V1, V2, V3, V4;

  // input sanity check
  if((Min->val[0] > Max->val[0]) || (Min->val[1] > Max->val[1])) return false;
  if((Ctr->val[0] >= Min->val[0]) && (Ctr->val[0] <= Max->val[0]) &&
     (Ctr->val[1] >= Min->val[1]) && (Ctr->val[1] <= Max->val[1])) return true;
  V1.val[0] = Min->val[0]; V1.val[1] = Min->val[1]; if(InsideCircle_p(Ctr, Rad, &V1)) return true;
  V2.val[0] = Min->val[0]; V2.val[1] = Max->val[1]; if(InsideCircle_p(Ctr, Rad, &V2)) return true;
  V3.val[0] = Max->val[0]; V3.val[1] = Min->val[1]; if(InsideCircle_p(Ctr, Rad, &V3)) return true;
  V4.val[0] = Max->val[0]; V4.val[1] = Max->val[1]; if(InsideCircle_p(Ctr, Rad, &V4)) return true;

  CL2S.SetEndPts(&V1, &V2); if(IntersectCircleLine2Seg_p(Ctr, Rad, &CL2S)) return true;
  CL2S.SetEndPts(&V2, &V3); if(IntersectCircleLine2Seg_p(Ctr, Rad, &CL2S)) return true;
  CL2S.SetEndPts(&V3, &V4); if(IntersectCircleLine2Seg_p(Ctr, Rad, &CL2S)) return true;
  CL2S.SetEndPts(&V4, &V1); if(IntersectCircleLine2Seg_p(Ctr, Rad, &CL2S)) return true;
  return false;
}

bool IntersectCircleLine2_p(pVec2_t Ctr, double Rad, CLine2 *CL2){ return(CL2->L2Distance(Ctr) <= Rad);}
bool InsideCircle_p(pVec2_t Ctr, double Rad, pVec2_t Pt){ return(Distance(Ctr, Pt) <= Rad);}
bool IntersectCircleCircle_p(pVec2_t Ctr1, double Rad1, pVec2_t Ctr2, double Rad2){return(Distance(Ctr1, Ctr2) <= Rad1 + Rad2);}
bool IntersectMinMax_p(pVec2_t X1, pVec2_t Y1, pVec2_t X2, pVec2_t Y2)
{
  if((X1->val[0] > X2->val[1])||(X2->val[0] > X1->val[1])) return false;
  if((Y1->val[0] > Y2->val[1])||(Y2->val[0] > Y1->val[1])) return false;
  return true;
}
