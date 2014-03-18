#include <cstdio>
//#include<stdio.h>
#include<string.h>
#include<math.h>
#if !defined WIN32
//#include<unistd.h>
#endif
#include<stdlib.h>
#include<stdio.h>

#include "../include/mathfuncs.h"

int main(){

  int i,j,k,l, count;
  double val, valE;
  double val1, val2, val3, val4;
  Mat2_t M2_1, M2_2, M2_3, M2_4;
  Vec2_t V2_1, V2_2, V2_3, V2_4, V2_5, V2_6, V2_7, V2_8;
  Mat3_t M3_1, M3_2, M3_3, M3_4;
  Vec3_t V3_1, V3_2, V3_3, V3_4, V3_5, V3_6, V3_7, V3_8;
  bool fail = false;
  int seed = 17;
  double approxTooSmall[5] = {0.0, 0.00000001, 0.0000001, -0.00000001, -0.0000001};
  double approxTooBig[6] = {0.0000011, 0.00001, 0.0001, -0.0001, -0.0000011,  -0.00001};
  int I1, I2, I3;
  double c1,s1,c2,s2,c3,s3;
  bool B1, B2, conv;
  int countmax,countmin,countin;

  srand(seed);
  // Check Square first, because it's used by Length
  
  for(i = 0;i<100;i++)
    {
      valE = rand()/((double)rand() + 1.0); 
      if(rand()%2){
	valE = -valE;
	val = -sqrt(Square(valE)); 
      }
      else
	{	
	val = sqrt(Square(valE)); 
	}
      if(fabs(valE - val) > APPROX_THRESH) fail = true; 
      if(fail){ printf("Square %f failed!!\n", val);break;}
    }
  if(!fail) printf("Square test succeeded\n"); 
  fail = false;
  
  // Check Length, used by Approx
  for(i = 0;i<100;i++)
    {
      // 2D root method
      val1 = rand()/((double)rand() + 1.0); 
      val2 = rand()/((double)rand() + 1.0); 
      val3 = Length(val1, val2);
      val4 = sqrt(val1*val1 + val2*val2);
      if(fabs(val3 - val4) > APPROX_THRESH) fail = true; 
      if(fail) printf("Length double %f %f failed!!\n", val3, val4);
      V2_1.val[0] = val1; V2_1.val[1] = val2;
      val3 = Length(&V2_1);
      if(fabs(val3 - val4) > APPROX_THRESH) fail = true; 
      if(fail){ printf("Length Vec2_t %f %f failed!!\n", val3, val4);break;}

      // 3D root method
      val1 = rand()/((double)rand() + 1.0); 
      val2 = rand()/((double)rand() + 1.0); 
      val3 = rand()/((double)rand() + 1.0); 
      val4 = Length(val1, val2, val3);
      valE = sqrt(val1*val1 + val2*val2 + val3*val3);
      if(fabs(valE - val4) > APPROX_THRESH) fail = true; 
      if(fail){ printf("Length double3 %f %f failed!!\n", valE, val4);break;}
      V3_1.val[0] = val1; V3_1.val[1] = val2; V3_1.val[2] = val3;
      val4 = Length(&V3_1);
      if(fabs(valE - val4) > APPROX_THRESH) fail = true; 
      if(fail){ printf("Length Vec3_t %f %f failed!!\n", valE, val4);break;}
    }
  if(!fail) printf("Length test............................. succeeded\n"); 
  fail = false;
  

  // Check Approx
  // Check whether a number is near zero
  for(i = 0;i<5;i++){ val = approxTooSmall[i]; if(!Approx(val)) fail = true; if(fail) printf("Approx %g too small failed!!\n", val);}
  for(i = 0;i<6;i++){ val = approxTooBig[i];   if( Approx(val)) fail = true; if(fail) printf("Approx %g too big failed!!\n", val);}

  for(j=0;j<100;j++)
    {
      val1 = rand()/((double)rand() + 1.0); 
      for(i = 0;i<5;i++){ val2 = val1 + approxTooSmall[i]; if(!Approx(val1, val2)) fail = true; if(fail) printf("Approx 2 val too small failed!!\n");}
      for(i = 0;i<6;i++){ val2 = val1 + approxTooBig[i];   if( Approx(val1, val2)) fail = true; if(fail) printf("Approx 2 val too big failed!!\n");}

      for(i = 0;i<5;i++){ 
	V2_1.val[0] = ((rand()%2000000 - 1000000)/2000000.0) * approxTooSmall[i];
	V2_1.val[1] = ((rand()%2000000 - 1000000)/2000000.0) * approxTooSmall[i];
	if(!Approx(&V2_1)) fail = true; if(fail) printf("Approx too small failed!!\n");
      }
      for(i = 0;i<6;i++){ 
	V2_1.val[0] = (rand()%1000000)/1000000.0 + approxTooBig[i];
	V2_1.val[1] = (rand()%1000000)/1000000.0 + approxTooBig[i];
	if(Approx(&V2_1)) fail = true; if(fail) printf("Approx too big failed!!\n");
      }
      
      for(i = 0;i<5;i++){ 
	V3_1.val[0] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	V3_1.val[1] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	V3_1.val[2] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	if(!Approx(&V3_1)) fail = true; if(fail) printf("Approx too small failed!!\n");
      }
      for(i = 0;i<6;i++){ 
	V3_1.val[0] = (rand()%1000000)/1000000.0 + approxTooBig[i];
	V3_1.val[1] = (rand()%1000000)/1000000.0 + approxTooBig[i];
	V3_1.val[2] = (rand()%1000000)/1000000.0 + approxTooBig[i];
	if(Approx(&V3_1)) fail = true; if(fail) printf("Approx too big failed!!\n");
      }

      for(i = 0;i<5;i++){ 
	M2_1.val[0][0] = 1.0 + ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M2_1.val[0][1] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M2_1.val[1][0] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M2_1.val[1][1] = 1.0 + ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	if(!Approx(&M2_1)) fail = true; if(fail) printf("Approx 2D identity failed!!\n");
      }
      M2_1.val[0][0] = 1.0 + approxTooBig[0];
      M2_1.val[0][1] = 0.0;
      M2_1.val[1][0] = 0.0;
      M2_1.val[1][1] = 1.0;
      if(Approx(&M2_1)) fail = true; if(fail) printf("Approx 2D identity too big failed!!\n");
      M2_1.val[0][0] = 1.0;
      M2_1.val[0][1] =  approxTooBig[1];
      if(Approx(&M2_1)) fail = true; if(fail) printf("Approx 2D identity too big failed!!\n");
      M2_1.val[0][1] = 0.0;
      M2_1.val[1][0] = approxTooBig[2];
      if(Approx(&M2_1)) fail = true; if(fail) printf("Approx 2D identity too big failed!!\n");
      M2_1.val[1][0] = 0.0;
      M2_1.val[1][1] = 1.0 + approxTooBig[3];
      if(Approx(&M2_1)) fail = true; if(fail) printf("Approx 2D identity too big failed!!\n");
      
      for(i = 0;i<5;i++){ 
	M3_1.val[0][0] = 1.0 + ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[0][1] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[0][2] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[1][0] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[1][1] = 1.0 + ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[1][2] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[2][0] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[2][1] = ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	M3_1.val[2][2] = 1.0 + ((rand()%2000000 - 1000000)/3000000.0) * approxTooSmall[i];
	if(!Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity failed!!\n");
      }
      M3_1.val[0][0] = 1.0 + approxTooBig[0];
      M3_1.val[0][1] = 0.0;
      M3_1.val[0][2] = 0.0;
      M3_1.val[1][0] = 0.0;
      M3_1.val[1][1] = 1.0;
      M3_1.val[1][2] = 0.0;
      M3_1.val[2][0] = 0.0;
      M3_1.val[2][1] = 0.0;
      M3_1.val[2][2] = 1.0;
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[0][0] = 1.0;
      M3_1.val[0][1] =  approxTooBig[1];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[0][1] = 0.0;
      M3_1.val[0][2] = approxTooBig[2];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[0][2] = 0.0;
      M3_1.val[1][0] = approxTooBig[3];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[1][0] = 0.0;
      M3_1.val[1][1] = 1.0 + approxTooBig[4];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[1][1] = 1.0;
      M3_1.val[1][2] = approxTooBig[5];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[1][2] = 0.0;
      M3_1.val[2][0] = approxTooBig[0];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[2][0] = 0.0;
      M3_1.val[2][1] = approxTooBig[1];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      M3_1.val[2][1] = 0.0;
      M3_1.val[2][2] = 1.0 + approxTooBig[2];
      if(Approx(&M3_1)) fail = true; if(fail) printf("Approx 3D identity too big failed!!\n");
      
      V2_1.val[0] = rand()/((double)rand() + 1.0); 
      V2_1.val[1] = rand()/((double)rand() + 1.0); 
      I1 = rand()%5;
      V2_2.val[0] = V2_1.val[0] + 0.7*approxTooSmall[I1];
      V2_2.val[1] = V2_1.val[1] + 0.7*approxTooSmall[I1];
      if(!Approx(&V2_1, &V2_2)) fail = true; if(fail) printf("Approx 2D vectors too small failed!!\n");
      
      V2_1.val[0] = rand()/((double)rand() + 1.0); 
      V2_1.val[1] = rand()/((double)rand() + 1.0); 
      I1 = rand()%6;
      V2_2.val[0] = V2_1.val[0] + approxTooBig[I1];
      V2_2.val[1] = V2_1.val[1];
      if(Approx(&V2_1, &V2_2)) fail = true; if(fail) printf("Approx 2D vectors too big failed!!\n");
      V2_2.val[0] = V2_1.val[0];
      V2_2.val[1] = V2_1.val[1] + approxTooBig[I1];
      if(Approx(&V2_1, &V2_2)) fail = true; if(fail) printf("Approx 2D vectors too big failed!!\n");
      
      V3_1.val[0] = rand()/((double)rand() + 1.0); 
      V3_1.val[1] = rand()/((double)rand() + 1.0); 
      V3_1.val[2] = rand()/((double)rand() + 1.0); 
      I1 = rand()%5;
      V3_2.val[0] = V3_1.val[0] + 0.55*approxTooSmall[I1];
      V3_2.val[1] = V3_1.val[1] + 0.55*approxTooSmall[I1];
      V3_2.val[2] = V3_1.val[2] + 0.55*approxTooSmall[I1];
      if(!Approx(&V3_1, &V3_2)) fail = true; if(fail) printf("Approx 3D vectors too small failed!!\n");

      V3_1.val[0] = rand()/((double)rand() + 1.0); 
      V3_1.val[1] = rand()/((double)rand() + 1.0); 
      V3_1.val[2] = rand()/((double)rand() + 1.0); 
      I1 = rand()%6;
      V3_2.val[0] = V3_1.val[0] + approxTooBig[I1];
      V3_2.val[1] = V3_1.val[1];
      V3_2.val[2] = V3_1.val[2];
      if(Approx(&V3_1, &V3_2)) fail = true; if(fail) printf("Approx 3D vectors too big failed!!\n");
      V3_2.val[0] = V3_1.val[0];
      V3_2.val[1] = V3_1.val[1] + approxTooBig[I1];
      V3_2.val[2] = V3_1.val[2];
      if(Approx(&V3_1, &V3_2)) fail = true; if(fail) printf("Approx 3D vectors too big failed!!\n");
      V3_2.val[0] = V3_1.val[0];
      V3_2.val[1] = V3_1.val[1];
      V3_2.val[2] = V3_1.val[2] + approxTooBig[I1];
      if(Approx(&V3_1, &V3_2)) fail = true; if(fail) printf("Approx 3D vectors too big failed!!\n");

      I1 = rand()%5;
      M2_1.val[0][0] = rand()/((double)rand() + 1.0); 
      M2_1.val[0][1] = rand()/((double)rand() + 1.0); 
      M2_1.val[1][0] = rand()/((double)rand() + 1.0); 
      M2_1.val[1][1] = rand()/((double)rand() + 1.0); 
      M2_2.val[0][0] = M2_1.val[0][0] + approxTooSmall[I1];
      M2_2.val[0][1] = M2_1.val[0][1] + approxTooSmall[I1];
      M2_2.val[1][0] = M2_1.val[1][0] + approxTooSmall[I1];
      M2_2.val[1][1] = M2_1.val[1][1] + approxTooSmall[I1];
      if(!Approx(&M2_1, &M2_2)) fail = true; if(fail) printf("Approx 2D matrices too small failed!!\n");
      M2_2.val[0][0] = M2_1.val[0][0] + approxTooBig[I1];
      M2_2.val[0][1] = M2_1.val[0][1];
      M2_2.val[1][0] = M2_1.val[1][0];
      M2_2.val[1][1] = M2_1.val[1][1];
      if(Approx(&M2_1, &M2_2)) fail = true; if(fail) printf("Approx 2D matrices too big failed!!\n");
      M2_2.val[0][0] = M2_1.val[0][0];
      M2_2.val[0][1] = M2_1.val[0][1] + approxTooBig[I1];
      if(Approx(&M2_1, &M2_2)) fail = true; if(fail) printf("Approx 2D matrices too big failed!!\n");
      M2_2.val[0][1] = M2_1.val[0][1];
      M2_2.val[1][0] = M2_1.val[1][0] + approxTooBig[I1];
      if(Approx(&M2_1, &M2_2)) fail = true; if(fail) printf("Approx 2D matrices too big failed!!\n");
      M2_2.val[1][0] = M2_1.val[1][0];
      M2_2.val[1][1] = M2_1.val[1][1] + approxTooBig[I1];
      if(Approx(&M2_1, &M2_2)) fail = true; if(fail) printf("Approx 2D matrices too big failed!!\n");
      
      I1 = rand()%5;
      for(i=0;i<3;i++)
	for(k=0;k<3;k++)
	  {
	    M3_1.val[i][k] = rand()/((double)rand() + 1.0); 
	    M3_2.val[i][k] = M3_1.val[i][k] + approxTooSmall[I1];
	  }
      if(!Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too small failed!!\n");
      for(i=0;i<3;i++)
	for(k=0;k<3;k++)
	  {
	    M3_1.val[i][k] = rand()/((double)rand() + 1.0); 
	    M3_2.val[i][k] = M3_1.val[i][k];
	  }
      M3_2.val[0][0] = M3_1.val[0][0] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[0][0] = M3_1.val[0][0];
      M3_2.val[0][1] = M3_1.val[0][1] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[0][1] = M3_1.val[0][1];
      M3_2.val[0][2] = M3_1.val[0][2] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[0][2] = M3_1.val[0][2];
      M3_2.val[1][0] = M3_1.val[1][0] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[1][0] = M3_1.val[1][0];
      M3_2.val[1][1] = M3_1.val[1][1] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[1][1] = M3_1.val[1][1];
      M3_2.val[1][2] = M3_1.val[1][2] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[1][2] = M3_1.val[1][2];
      M3_2.val[2][0] = M3_1.val[2][0] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[2][0] = M3_1.val[2][0];
      M3_2.val[2][1] = M3_1.val[2][1] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
      M3_2.val[2][1] = M3_1.val[2][1];
      M3_2.val[2][2] = M3_1.val[2][2] + approxTooBig[I1];
      if(Approx(&M3_1, &M3_2)) fail = true; if(fail) printf("Approx 3D matrices too big failed!!\n");
    } // loop j to 100
  if(!fail) printf("Approx test............................. succeeded\n"); 
  fail = false;

  // Check globals
  InitGlobals();
  V2_1 = *gZVec2;
  M2_1 = *gIMat2;
  V3_1 = *gZVec3;
  M3_1 = *gIMat3;

  if(!Approx(&V2_1)||!Approx(&M2_1)||!Approx(&V3_1)||!Approx(&M3_1))fail = true; 
  if(fail) printf("Global initialization failed!!\n");
  else printf("Global initialization test.............. succeeded\n"); 


  for(i=0;i<2;i++)
    for(k=0;k<2;k++)
      {
	M2_1.val[i][k] = rand()/((double)rand() + 1.0); 
      }
  Transpose(&M2_1, &M2_2);
  for(i=0;i<2;i++)
    for(k=0;k<2;k++)
      {
	if(!Approx(M2_1.val[i][k], M2_2.val[k][i])) fail = true;
      }

  for(i=0;i<3;i++)
    for(k=0;k<3;k++)
      {
	M3_1.val[i][k] = rand()/((double)rand() + 1.0); 
      }
  Transpose(&M3_1, &M3_2);
  for(i=0;i<3;i++)
    for(k=0;k<3;k++)
      {
	if(!Approx(M3_1.val[i][k], M3_2.val[k][i])) fail = true;
      }
  if(!fail) printf("Transpose test.......................... succeeded\n"); 
  else printf("Transpose test failed\n");
  fail = false;

  for(i=0;i<2;i++)
    for(k=0;k<2;k++)
      {
	M2_1.val[i][k] = rand()/((double)rand() + 1.0); 
      }
  val = Det(&M2_1);
  val1 = M2_1.val[0][0]*M2_1.val[1][1] - M2_1.val[0][1]*M2_1.val[1][0];
  if(!Approx(val, val1)) fail = true;

  for(i=0;i<3;i++)
    for(k=0;k<3;k++)
      {
	M3_1.val[i][k] = rand()/((double)rand() + 1.0); 
      }
  val = Det(&M3_1);
  val1 = M3_1.val[0][0]*(M3_1.val[1][1]*M3_1.val[2][2] - M3_1.val[1][2]*M3_1.val[2][1]) +
    M3_1.val[0][1]*(M3_1.val[1][2]*M3_1.val[2][0] - M3_1.val[1][0]*M3_1.val[2][2]) +
    M3_1.val[0][2]*(M3_1.val[1][0]*M3_1.val[2][1] - M3_1.val[1][1]*M3_1.val[2][0]);
  if(!Approx(val, val1)) fail = true;

  if(!fail) printf("Determinant test........................ succeeded\n"); 
  else printf("Det test failed\n");
  fail = false;


  for(j = 0;j<100;j++){
    for(i=0;i<2;i++)
      for(k=0;k<2;k++)
	{
	  M2_1.val[i][k] = rand()/((double)rand() + 1.0); 
	}
    val = Det(&M2_1);
    if(Inverse(&M2_1, &M2_2))
      {
	if(Inverse(&M2_2, &M2_3))
	  {
	    if(!Approx(&M2_1, &M2_3)) fail = true;
	  }
	else if(val <= 1.0/APPROX_THRESH) fail = true;
      }
    else if(val >= APPROX_THRESH) fail = true;
    for(i=0;i<2;i++){
      M2_1.val[i][0] = rand()/((double)rand() + 1.0); 
      M2_1.val[i][1] = M2_1.val[i][0];
    }
    if(Inverse(&M2_1, &M2_2)) fail = true;
  }
  if(!fail) printf("Inverse test............................ succeeded\n"); 
  else printf("Inverse test failed\n");
  fail = false;

  
  for(i = 0;i<100;i++)
    {
      val = rand()/((double)rand() + 1.0);
      val1 = cos(val);
      val2 = sin(val);
      M2_1.val[0][0] = val1;
      M2_1.val[0][1] = val2;
      M2_1.val[1][0] = -val2;
      M2_1.val[1][1] = val1;
      if(!Rotation_p(&M2_1)) fail = true;
      M2_1.val[0][0] = val1 + 0.1;
      if(Rotation_p(&M2_1)) fail = true;

      val1 = rand()/((double)rand() + 1.0);
      val2 = rand()/((double)rand() + 1.0);
      val3 = rand()/((double)rand() + 1.0);
      c1 = cos(val1); s1 = sin(val1);
      c2 = cos(val2); s2 = sin(val2);
      c3 = cos(val3); s3 = sin(val3);
      M3_1.val[0][0] = c1*c2;
      M3_1.val[0][1] = s1*c2;
      M3_1.val[0][2] =   -s2;
      M3_1.val[1][0] = c1*s2*s3 - s1*c3;
      M3_1.val[1][1] = s1*s2*s3 + c1*c3;
      M3_1.val[1][2] = c2*s3;
      M3_1.val[2][0] = c1*s2*c3 + s1*s3;
      M3_1.val[2][1] = s1*s2*c3 - c1*s3;
      M3_1.val[2][2] = c2*c3;

      if(!Rotation_p(&M3_1)) fail = true;
      I1 = rand()%3;
      I2 = rand()%3;
      M3_1.val[I1][I2] += 0.1;
      if(Rotation_p(&M2_1)) fail = true;

    }

  if(!fail) printf("Rotation test........................... succeeded\n"); 
  else printf("Rotation test failed\n");
  fail = false;

  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = rand()/((double)rand() + 1.0);
    }
    V2_4 = *Add_v(&V2_1, &V2_2, &V2_3);
    for(j= 0;j<2;j++)
      {
	if(!Approx(V2_3.val[j], V2_1.val[j] + V2_2.val[j])) fail = true;
	if(!Approx(&V2_3, &V2_4)) fail = true;
      }

    V2_4 = *Sub_v(&V2_1, &V2_2, &V2_3);
    for(j= 0;j<2;j++)
      {
	if(!Approx(V2_3.val[j], V2_1.val[j] - V2_2.val[j])) fail = true;
	if(!Approx(&V2_3, &V2_4)) fail = true;
      }

    V2_4 = *Neg_v(&V2_1, &V2_3);
    for(j= 0;j<2;j++)
      {
	if(!Approx(V2_3.val[j], -V2_1.val[j])) fail = true;
	if(!Approx(&V2_3, &V2_4)) fail = true;
      }
    V2_3 = V2_1;
    Neg_v(&V2_1);
    for(j= 0;j<2;j++)
      {
	if(!Approx(V2_3.val[j], -V2_1.val[j])) fail = true;
      }

    // 3D
    for(j= 0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
      V3_2.val[j] = rand()/((double)rand() + 1.0);
      V3_3.val[j] = rand()/((double)rand() + 1.0);
    }
    V3_4 = *Add_v(&V3_1, &V3_2, &V3_3);
    for(j= 0;j<3;j++)
      {
	if(!Approx(V3_3.val[j], V3_1.val[j] + V3_2.val[j])) fail = true;
	if(!Approx(&V3_3, &V3_4)) fail = true;
      }

    V3_4 = *Sub_v(&V3_1, &V3_2, &V3_3);
    for(j= 0;j<3;j++)
      {
	if(!Approx(V3_3.val[j], V3_1.val[j] - V3_2.val[j])) fail = true;
	if(!Approx(&V3_3, &V3_4)) fail = true;
      }

    V3_4 = *Neg_v(&V3_1, &V3_3);
    for(j= 0;j<3;j++)
      {
	if(!Approx(V3_3.val[j], -V3_1.val[j])) fail = true;
	if(!Approx(&V3_3, &V3_4)) fail = true;
      }
    V3_3 = V3_1;
    Neg_v(&V3_1);
    for(j= 0;j<3;j++)
      {
	if(!Approx(V3_3.val[j], -V3_1.val[j])) fail = true;
      }
  } // loop i

  if(!fail) printf("Vector arithmetic test.................. succeeded\n"); 
  else printf("Vector arithmetic test failed\n");
  fail = false;


  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
    }
    val = rand()/((double)rand() + 1.0);

    V2_3 = *Mult_sv(val, &V2_1, &V2_2);
    for(j= 0;j<2;j++)
      {
	if(!Approx(V2_3.val[j], val*V2_1.val[j])) fail = true;
	if(!Approx(&V2_3, &V2_2)) fail = true;
      }
    // 3D
    for(j= 0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
    }
    val = rand()/((double)rand() + 1.0);

    V3_3 = *Mult_sv(val, &V3_1, &V3_2);
    for(j= 0;j<3;j++)
      {
	if(!Approx(V3_3.val[j], val*V3_1.val[j])) fail = true;
	if(!Approx(&V3_3, &V3_2)) fail = true;
      }

  } // loop i
  if(!fail) printf("Scalar-Vector arithmetic test........... succeeded\n"); 
  else printf("Scalar-Vector arithmetic test failed\n");
  fail = false;


  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      for(k= 0;k<2;k++)	M2_1.val[j][k] = rand()/((double)rand() + 1.0);
      V2_1.val[j] = rand()/((double)rand() + 1.0);
    }
    V2_3 = *Mult_mv(&M2_1, &V2_1, &V2_2);
    for(j= 0;j<2;j++)
      {
	if(!Approx(V2_2.val[j], M2_1.val[j][0]*V2_1.val[0] + M2_1.val[j][1]*V2_1.val[1])) fail = true;
	if(!Approx(&V2_3, &V2_2)) fail = true;
      }
    V2_3 = *Mult_vm(&M2_1, &V2_1, &V2_2);
    for(j= 0;j<2;j++)
      {
	if(!Approx(V2_2.val[j], M2_1.val[0][j]*V2_1.val[0] + M2_1.val[1][j]*V2_1.val[1])) fail = true;
	if(!Approx(&V2_3, &V2_2)) fail = true;
      }

    // 3D
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++)	M3_1.val[j][k] = rand()/((double)rand() + 1.0);
      V3_1.val[j] = rand()/((double)rand() + 1.0);
    }
    V3_3 = *Mult_mv(&M3_1, &V3_1, &V3_2);
    for(j= 0;j<3;j++)
      {
	if(!Approx(V3_2.val[j], M3_1.val[j][0]*V3_1.val[0] + M3_1.val[j][1]*V3_1.val[1] + M3_1.val[j][2]*V3_1.val[2])) fail = true;
	if(!Approx(&V3_3, &V3_2)) fail = true;
      }
    V3_3 = *Mult_vm(&M3_1, &V3_1, &V3_2);
    for(j= 0;j<3;j++)
      {
	if(!Approx(V3_2.val[j], M3_1.val[0][j]*V3_1.val[0] + M3_1.val[1][j]*V3_1.val[1] + M3_1.val[2][j]*V3_1.val[2])) fail = true;
	if(!Approx(&V3_3, &V3_2)) fail = true;
      }
  } // loop i
  if(!fail) printf("Matrix-Vector mult test................. succeeded\n"); 
  else printf("Matrix-Vector mult test failed\n");
  fail = false;


  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      for(k= 0;k<2;k++){
	M2_1.val[j][k] = rand()/((double)rand() + 1.0);
	M2_2.val[j][k] = rand()/((double)rand() + 1.0);
      }
    }
    M2_4 = *Mult_mm(&M2_1, &M2_2, &M2_3);
    for(j = 0;j<2;j++){
      for(k = 0;k<2;k++){
	val = 0.0;
	for(l = 0;l<2;l++) val += M2_1.val[j][l]*M2_2.val[l][k];
	if(!Approx(val, M2_3.val[j][k])) fail = true;
	if(!Approx(&M2_3, &M2_4)) fail = true;
      } // loop k
    } // loop j
    Inverse(&M2_1, &M2_2);
    if(!Approx(Mult_mm(&M2_1, &M2_2, &M2_3))) fail = true;


    // 3D
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	M3_1.val[j][k] = rand()/((double)rand() + 1.0);
	M3_2.val[j][k] = rand()/((double)rand() + 1.0);
      }
    }
    M3_4 = *Mult_mm(&M3_1, &M3_2, &M3_3);
    for(j = 0;j<3;j++){
      for(k = 0;k<3;k++){
	val = 0.0;
	for(l = 0;l<3;l++) val += M3_1.val[j][l]*M3_2.val[l][k];
	if(!Approx(val, M3_3.val[j][k])) fail = true;
	if(!Approx(&M3_3, &M3_4)) fail = true;
      } // loop k
    } // loop j

  } // loop i
  if(!fail) printf("Matrix-Matrix mult test................. succeeded\n"); 
  else printf("Matrix-Matrix mult test failed\n");
  fail = false;

  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = rand()/((double)rand() + 1.0);
    }
    val = Distance(&V2_1, &V2_2);
    val1 = 0.0;
    for(j = 0;j<2;j++) val1 += Square(V2_1.val[j] - V2_2.val[j]);
    val2 = sqrt(val1);
    if(!Approx(val, val2)) fail = true;

    // 3D
    for(j= 0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
      V3_2.val[j] = rand()/((double)rand() + 1.0);
    }
    val = Distance(&V3_1, &V3_2);
    val1 = 0.0;
    for(j = 0;j<3;j++) val1 += Square(V3_1.val[j] - V3_2.val[j]);
    val2 = sqrt(val1);
    if(!Approx(val, val2)) fail = true;

  } // loop i
  if(!fail) printf("Distance test........................... succeeded\n"); 
  else printf("Distance test failed\n");
  fail = false;

  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++) V2_1.val[j] = rand()/((double)rand() + 1.0);

    B1 = UnitVector(&V2_1, &V2_2);
    val = Length(&V2_1);
    if(Approx(val)){
      if(B1) fail = true;
    }
    else if(!B1) fail = true;
    else{
      for(j=0;j<2;j++) if(!Approx(V2_1.val[j], V2_2.val[j]*val)) fail = true;
    }

    B1 = UnitVector(&V2_1, &V2_2, &val1);
    val = Length(&V2_1);
    if(!Approx(val, val1)) fail = true;
    if(Approx(val)){
      if(B1) fail = true;
    }
    else if(!B1) fail = true;
    else{
      for(j=0;j<2;j++) if(!Approx(V2_1.val[j], V2_2.val[j]*val)) fail = true;
    }

    // 3D
    for(j= 0;j<3;j++) V3_1.val[j] = rand()/((double)rand() + 1.0);

    B1 = UnitVector(&V3_1, &V3_2);
    val = Length(&V3_1);
    if(Approx(val)){
      if(B1) fail = true;
    }
    else if(!B1) fail = true;
    else{
      for(j=0;j<3;j++) if(!Approx(V3_1.val[j], V3_2.val[j]*val)) fail = true;
    }

    B1 = UnitVector(&V3_1, &V3_2, &val1);
    val = Length(&V3_1);
    if(!Approx(val, val1)) fail = true;
    if(Approx(val)){
      if(B1) fail = true;
    }
    else if(!B1) fail = true;
    else{
      for(j=0;j<3;j++) if(!Approx(V3_1.val[j], V3_2.val[j]*val)) fail = true;
    }
  } // loop i

  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      for(k= 0;k<2;k++){
	M2_1.val[j][k] = rand()/((double)rand() + 1.0);
      }
    }
    I1 = rand()%2; // row or column
    I2 = rand()%2;// which one
    if(I1){ // row
      for(j=0;j<2;j++) V2_1.val[j] = M2_1.val[I2][j];
      B2 = UnitVectorR(&M2_1, I2, &V2_3);
    }
    else{ // col
      for(j=0;j<2;j++) V2_1.val[j] = M2_1.val[j][I2];
      B2 = UnitVectorC(&M2_1, I2, &V2_3);
    }
    B1 = UnitVector(&V2_1, &V2_2);
    if(B1 != B2) fail = true;
    if(!Approx(&V2_2, &V2_3)) fail = true;

    // 3D
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	M3_1.val[j][k] = rand()/((double)rand() + 1.0);
      }
    }
    I1 = rand()%2; // row or column
    I2 = rand()%3;// which one
    if(I1){ // row
      for(j=0;j<3;j++) V3_1.val[j] = M3_1.val[I2][j];
      B2 = UnitVectorR(&M3_1, I2, &V3_3);
    }
    else{ // col
      for(j=0;j<3;j++) V3_1.val[j] = M3_1.val[j][I2];
      B2 = UnitVectorC(&M3_1, I2, &V3_3);
    }
    B1 = UnitVector(&V3_1, &V3_2);
    if(B1 != B2) fail = true;
    if(!Approx(&V3_2, &V3_3)) fail = true;
  } // loop i
  if(!fail) printf("Unit Vector test........................ succeeded\n"); 
  else printf("Unit Vector test failed\n");
  fail = false;

  for(j= 0;j<2;j++){
    for(k= 0;k<2;k++){
      M2_1.val[j][k] = rand()/((double)rand() + 1.0);
    }
  }
  SetIdentity(&M2_1);
  if(!Approx(&M2_1, gIMat2)) fail = true;

  for(j= 0;j<3;j++){
    for(k= 0;k<3;k++){
      M3_1.val[j][k] = rand()/((double)rand() + 1.0);
    }
  }
  SetIdentity(&M3_1);
  if(!Approx(&M3_1, gIMat3)) fail = true;

  for(j= 0;j<2;j++) V2_1.val[j] = rand()/((double)rand() + 1.0);
  SetZero(&V2_1);
  if(!Approx(&V2_1, gZVec2)) fail = true;

  for(j= 0;j<3;j++) V3_1.val[j] = rand()/((double)rand() + 1.0);
  SetZero(&V3_1);
  if(!Approx(&V3_1, gZVec3)) fail = true;

  printf("Z/I assignment test.....................");
  if(!fail) printf(" succeeded\n"); 
  else printf(" failed\n");
  fail = false;
  
  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = rand()/((double)rand() + 1.0);
    }
    V2_4 = *Dot(&V2_1, &V2_2, &V2_3);
    if(!Approx(&V2_3, &V2_4)) fail = true;

    val = Dot(&V2_1, &V2_2);
    val1 = 0.0;
    for(j = 0;j<2;j++) val1 += V2_1.val[j]*V2_2.val[j];
    if(!Approx(val, val1)) fail = true;

    if(!Approx(atan2(V2_1.val[1], V2_1.val[0]), atan2(V2_3.val[1], V2_3.val[0]))) fail = true;
    if(!Approx(Length(&V2_3)*Length(&V2_1), val)) fail = true;

    // 3D
    for(j= 0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
      V3_2.val[j] = rand()/((double)rand() + 1.0);
    }
    V3_4 = *Dot(&V3_1, &V3_2, &V3_3);
    if(!Approx(&V3_3, &V3_4)) fail = true;

    val = Dot(&V3_1, &V3_2);
    val1 = 0.0;
    for(j = 0;j<3;j++) val1 += V3_1.val[j]*V3_2.val[j];
    if(!Approx(val, val1)) fail = true;

    if(!Approx(atan2(V3_1.val[1], V3_1.val[0]), atan2(V3_3.val[1], V3_3.val[0]))) fail = true;
    if(!Approx(Length(&V3_3)*Length(&V3_1), val)) fail = true;


  } // loop i


  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      for(k= 0;k<2;k++){
	M2_1.val[j][k] = rand()/((double)rand() + 1.0);
      }
      V2_2.val[j] = rand()/((double)rand() + 1.0);
    }
    I1 = rand()%2; // row or column
    I2 = rand()%2;// which one
    if(I1){ // row
      for(j=0;j<2;j++) V2_1.val[j] = M2_1.val[I2][j];
      val1 = DotR(&V2_2, &M2_1, I2);
      V2_4 = *DotR(&V2_2, &M2_1, I2, &V2_3);
    }
    else{ // col
      for(j=0;j<2;j++) V2_1.val[j] = M2_1.val[j][I2];
      val1 = DotC(&V2_2, &M2_1, I2);
      V2_4 = *DotC(&V2_2, &M2_1, I2, &V2_3);
    }
    val = Dot(&V2_1, &V2_2);
    V2_6 = *Dot(&V2_1, &V2_2, &V2_5);
    if(!Approx(&V2_3, &V2_4)) fail = true;
    if(!Approx(&V2_6, &V2_4)) fail = true;
    if(!Approx(val, val1)) fail = true;

    // 3D
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	M3_1.val[j][k] = rand()/((double)rand() + 1.0);
      }
      V3_2.val[j] = rand()/((double)rand() + 1.0);
    }
    I1 = rand()%2; // row or column
    I2 = rand()%3;// which one
    if(I1){ // row
      for(j=0;j<3;j++) V3_1.val[j] = M3_1.val[I2][j];
      val1 = DotR(&V3_2, &M3_1, I2);
      V3_4 = *DotR(&V3_2, &M3_1, I2, &V3_3);
    }
    else{ // col
      for(j=0;j<3;j++) V3_1.val[j] = M3_1.val[j][I2];
      val1 = DotC(&V3_2, &M3_1, I2);
      V3_4 = *DotC(&V3_2, &M3_1, I2, &V3_3);
    }
    val = Dot(&V3_1, &V3_2);
    V3_6 = *Dot(&V3_1, &V3_2, &V3_5);
    if(!Approx(&V3_3, &V3_4)) fail = true;
    if(!Approx(&V3_6, &V3_4)) fail = true;
    if(!Approx(val, val1)) fail = true;
  } // loop i
  printf("Dot product test........................");
  if(!fail) printf(" succeeded\n"); 
  else printf(" failed\n");
  fail = false;


  for(i=0;i<100;i++){
    // 2D
    for(j=0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = rand()/((double)rand() + 1.0);
    }
    val = Cross(&V2_1, &V2_2);
    val1 = V2_1.val[0]*V2_2.val[1] - V2_1.val[1]*V2_2.val[0];
    if(!Approx(val, val1)) fail = true;

    // 3D
    for(j=0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
      V3_2.val[j] = rand()/((double)rand() + 1.0);
    }
    val = Cross(&V3_1, &V3_2);
    V3_4 = *Cross(&V3_1, &V3_2, &V3_3);
    if(!Approx(&V3_4, &V3_3)) fail = true;
    if(!Approx(val, Length(&V3_3))) fail = true;
    V3_5.val[0] = V3_1.val[1]*V3_2.val[2] - V3_1.val[2]*V3_2.val[1];
    V3_5.val[1] = V3_1.val[2]*V3_2.val[0] - V3_1.val[0]*V3_2.val[2];
    V3_5.val[2] = V3_1.val[0]*V3_2.val[1] - V3_1.val[1]*V3_2.val[0];
    if(!Approx(&V3_5, &V3_4)) fail = true;
  } // loop i

  for(i=0;i<100;i++){
    // 3D
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	M3_1.val[j][k] = rand()/((double)rand() + 1.0);
      }
      V3_2.val[j] = rand()/((double)rand() + 1.0);
    }
    I1 = rand()%2; // row or column
    I2 = rand()%3;// which one
    if(I1){ // row
      for(j=0;j<3;j++) V3_1.val[j] = M3_1.val[I2][j];
      val1 = CrossR(&V3_2, &M3_1, I2);
      V3_4 = *CrossR(&V3_2, &M3_1, I2, &V3_3);
    }
    else{ // col
      for(j=0;j<3;j++) V3_1.val[j] = M3_1.val[j][I2];
      val1 = CrossC(&V3_2, &M3_1, I2);
      V3_4 = *CrossC(&V3_2, &M3_1, I2, &V3_3);
    }
    val = Cross(&V3_2, &V3_1);
    V3_6 = *Cross(&V3_2, &V3_1, &V3_5);
    if(!Approx(&V3_3, &V3_4)) fail = true;
    if(!Approx(&V3_6, &V3_4)) fail = true;
    if(!Approx(val, val1)) fail = true;
  } // loop i
  printf("Cross product test......................");
  if(!fail) printf(" succeeded\n"); 
  else printf(" failed\n");
  fail = false;



  pVec2_t PVEC2[2];
  pVec3_t PVEC3[3];
  PVEC2[0] = &V2_1;
  PVEC2[1] = &V2_2;
  PVEC3[0] = &V3_1;
  PVEC3[1] = &V3_2;
  PVEC3[2] = &V3_3;
  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      for(k= 0;k<2;k++){
	M2_1.val[j][k] = rand()/((double)rand() + 1.0);
      }
    }
    SplitCol(&M2_1, PVEC2);
    for(j= 0;j<2;j++){
      for(k= 0;k<2;k++){
	if(!Approx(M2_1.val[j][k], PVEC2[k]->val[j])) fail = true;
      }
    }
    SplitRow(&M2_1, PVEC2);
    for(j= 0;j<2;j++){
      for(k= 0;k<2;k++){
	if(!Approx(M2_1.val[j][k], PVEC2[j]->val[k])) fail = true;
      }
    }

    // 3D
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	M3_1.val[j][k] = rand()/((double)rand() + 1.0);
      }
    }
    SplitCol(&M3_1, PVEC3);
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	if(!Approx(M3_1.val[j][k], PVEC3[k]->val[j])) fail = true;
      }
    }
    SplitRow(&M3_1, PVEC3);
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	if(!Approx(M3_1.val[j][k], PVEC3[j]->val[k])) fail = true;
      }
    }
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	PVEC3[j]->val[k] = rand()/((double)rand() + 1.0);
      }
    }
    GlueCol(&M3_1, PVEC3);
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	if(!Approx(M3_1.val[j][k], PVEC3[k]->val[j])) fail = true;
      }
    }
    GlueRow(&M3_1, PVEC3);
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	if(!Approx(M3_1.val[j][k], PVEC3[j]->val[k])) fail = true;
      }
    }
    GlueRow(&M3_1, PVEC3[0], PVEC3[1], PVEC3[2]);
    for(j= 0;j<3;j++){
      for(k= 0;k<3;k++){
	if(!Approx(M3_1.val[j][k], PVEC3[j]->val[k])) fail = true;
      }
    }
  } // loop i  
  printf("split and glue test.....................");
  if(!fail) printf(" succeeded\n"); 
  else printf(" failed\n");
  fail = false;

  //pVec2_t Project(pVec3_t Vin, pMat3_t Rot, int plane, pVec2_t Vout) // plane: 0 for Y-Z, 1 for Z-X, 2 for X-Y.
  for(i=0;i<100;i++){
    // 3D
    for(j= 0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
    }
    val1 = rand()/((double)rand() + 1.0);
    val2 = rand()/((double)rand() + 1.0);
    val3 = rand()/((double)rand() + 1.0);
    c1 = cos(val1); s1 = sin(val1);
    c2 = cos(val2); s2 = sin(val2);
    c3 = cos(val3); s3 = sin(val3);
    M3_1.val[0][0] = c1*c2;
    M3_1.val[0][1] = s1*c2;
    M3_1.val[0][2] =   -s2;
    M3_1.val[1][0] = c1*s2*s3 - s1*c3;
    M3_1.val[1][1] = s1*s2*s3 + c1*c3;
    M3_1.val[1][2] = c2*s3;
    M3_1.val[2][0] = c1*s2*c3 + s1*s3;
    M3_1.val[2][1] = s1*s2*c3 - c1*s3;
    M3_1.val[2][2] = c2*c3;

    if(!Rotation_p(&M3_1)) fail = true;
    if(Approx(&V3_1)) fail = true;
    I3 = rand()%3; // choice of plane
    // rotate V3_1 into frame of M3_1, then project into plane.
    V2_2 = *Project(&V3_1, &M3_1, I3, &V2_1);
    if(!Approx(&V2_1, &V2_2)) fail = true;
    switch(I3){
    case 0:
      V2_3.val[0] = M3_1.val[1][0]*V3_1.val[0] + M3_1.val[1][1]*V3_1.val[1] + M3_1.val[1][2]*V3_1.val[2];
      V2_3.val[1] = M3_1.val[2][0]*V3_1.val[0] + M3_1.val[2][1]*V3_1.val[1] + M3_1.val[2][2]*V3_1.val[2];
      break;
    case 1:
      V2_3.val[0] = M3_1.val[2][0]*V3_1.val[0] + M3_1.val[2][1]*V3_1.val[1] + M3_1.val[2][2]*V3_1.val[2];
      V2_3.val[1] = M3_1.val[0][0]*V3_1.val[0] + M3_1.val[0][1]*V3_1.val[1] + M3_1.val[0][2]*V3_1.val[2];
      break;
    case 2:
      V2_3.val[0] = M3_1.val[0][0]*V3_1.val[0] + M3_1.val[0][1]*V3_1.val[1] + M3_1.val[0][2]*V3_1.val[2];
      V2_3.val[1] = M3_1.val[1][0]*V3_1.val[0] + M3_1.val[1][1]*V3_1.val[1] + M3_1.val[1][2]*V3_1.val[2];
      break;
    }
    if(!Approx(&V2_2, &V2_3)) fail = true;
  } // loop i  
  printf("Projection test.........................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;

  for(i=0;i<1000;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = V2_1.val[j] + rand()/((double)rand() + 1.0);
      V2_3.val[j] = rand()/((double)rand() + 1.0);
    }
    B1 = Inside_p(&V2_1, &V2_2, &V2_3);
    B2 = (V2_1.val[0] < V2_3.val[0]) && (V2_3.val[0] < V2_2.val[0]) && 
      (V2_1.val[1] < V2_3.val[1]) && (V2_3.val[1] < V2_2.val[1]);
    if(B1 != B2) fail = true;

    // 3D
    for(j= 0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
      V3_2.val[j] = V3_1.val[j] + rand()/((double)rand() + 1.0);
      V3_3.val[j] = rand()/((double)rand() + 1.0);
    }
    B1 = Inside_p(&V3_1, &V3_2, &V3_3);
    B2 = (V3_1.val[0] < V3_3.val[0]) && (V3_3.val[0] < V3_2.val[0]) && 
      (V3_1.val[1] < V3_3.val[1]) && (V3_3.val[1] < V3_2.val[1]) &&
      (V3_1.val[2] < V3_3.val[2]) && (V3_3.val[2] < V3_2.val[2]);
    if(B1 != B2) fail = true;

  } // loop i
  printf("Minmax containment test.................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;

  //bool InsideTriangle_p(pVec2_t A[3], pVec2_t Pt);

  pVec2_t A[3];
  A[0] = &V2_1;
  A[1] = &V2_2;
  A[2] = &V2_3;
  for(i=0;i<1000;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = rand()/((double)rand() + 1.0);
      V2_3.val[j] = rand()/((double)rand() + 1.0);
      V2_4.val[j] = rand()/((double)rand() + 1.0);
    }
    B1 = InsideTriangle_p(A, &V2_4);
    B2 = Cross(Sub_v(A[1], A[0], &V2_5), Sub_v(A[2], A[0], &V2_6)) > 0;
    if(B2)
      { // counterclockwise
	B2 = (Cross(Sub_v(A[2], &V2_4, &V2_5), Sub_v(A[0], &V2_4, &V2_6)) > 0) &&
	  (Cross(Sub_v(A[1], &V2_4, &V2_5), Sub_v(A[2], &V2_4, &V2_6)) > 0) &&
	  (Cross(Sub_v(A[0], &V2_4, &V2_5), Sub_v(A[1], &V2_4, &V2_6)) > 0);
      }
    else
      { // clockwise
	B2 = (Cross(Sub_v(A[0], &V2_4, &V2_5), Sub_v(A[2], &V2_4, &V2_6)) > 0) &&
	  (Cross(Sub_v(A[2], &V2_4, &V2_5), Sub_v(A[1], &V2_4, &V2_6)) > 0) &&
	  (Cross(Sub_v(A[1], &V2_4, &V2_5), Sub_v(A[0], &V2_4, &V2_6)) > 0);
      }
    if(B2 != B1) fail = true;

  } // loop i
  printf("Triangle containment test...............");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;


  pVec2_t A4[4];
  A4[0] = &V2_1;
  A4[1] = &V2_2;
  A4[2] = &V2_3;
  A4[3] = &V2_4;
  for(i=0;i<1000;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = rand()/((double)rand() + 1.0);
      V2_3.val[j] = rand()/((double)rand() + 1.0);
      V2_4.val[j] = rand()/((double)rand() + 1.0);
      V2_5.val[j] = rand()/((double)rand() + 1.0);
    }
    B1 = InsideQuad_p(A4, &V2_5);
    conv = false;
    A[0] = A4[0]; A[1] = A4[1]; A[2] = A4[2];
    if(InsideTriangle_p(A, A4[3]))
    { // 3 is inside 0-1-2
      A[2] = A4[3]; B2 = InsideTriangle_p(A, &V2_5);
      A[0] = A4[2]; B2 |= InsideTriangle_p(A, &V2_5);
      conv = true;
    }
    A[0] = A4[1]; A[1] = A4[2]; A[2] = A4[3];
    if(InsideTriangle_p(A, A4[0]))
    { // 0 is inside 1-2-3
      A[2] = A4[0]; B2 = InsideTriangle_p(A, &V2_5);
      A[0] = A4[3]; B2 |= InsideTriangle_p(A, &V2_5);
      conv = true;
    }
    A[0] = A4[2]; A[1] = A4[3]; A[2] = A4[0];
    if(InsideTriangle_p(A, A4[1]))
    { // 1 is inside 2-3-0
      A[2] = A4[1]; B2 = InsideTriangle_p(A, &V2_5);
      A[0] = A4[0]; B2 |= InsideTriangle_p(A, &V2_5);
      conv = true;
    }
    A[0] = A4[3]; A[1] = A4[0]; A[2] = A4[1];
    if(InsideTriangle_p(A, A4[2]))
    { // 2 is inside 3-0-1
      A[2] = A4[2]; B2 = InsideTriangle_p(A, &V2_5);
      A[0] = A4[1]; B2 |= InsideTriangle_p(A, &V2_5);
      conv = true;
    }
    if(!conv){
      if((Cross(Sub_v(A4[1], A4[0], &V2_6),Sub_v(A4[2], A4[0], &V2_7)) > 0) ==
	 (Cross(Sub_v(A4[3], A4[0], &V2_6),Sub_v(A4[2], A4[0], &V2_7)) > 0)){
	B2 = false;
      }
      else{
	A[2] = A4[2]; B2 = InsideTriangle_p(A, &V2_5);
	A[0] = A4[1]; B2 |= InsideTriangle_p(A, &V2_5);
      }
    }

    if(B1 != B2) fail = true;
  } // loop i
  printf("Quad containment test...................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;

  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0);
      V2_2.val[j] = rand()/((double)rand() + 1.0);
      V2_3.val[j] = rand()/((double)rand() + 1.0);
      V2_4.val[j] = rand()/((double)rand() + 1.0);
    }
    B1 = IntersectLineSegs_p(&V2_1, &V2_3, &V2_2, &V2_4);

    val1 = Cross(Sub_v(&V2_2, &V2_1, &V2_5), Sub_v(&V2_3, &V2_2, &V2_6));
    val2 = Cross(&V2_6, Sub_v(&V2_4, &V2_3, &V2_5));
    val3 = Cross(&V2_5, Sub_v(&V2_1, &V2_4, &V2_6));
    val4 = Cross(&V2_6, Sub_v(&V2_2, &V2_1, &V2_5));
    
    B2 = ((val1 > 0) && (val2 > 0) && (val3 > 0) && (val4 > 0)) ||
      ((val1 < 0) && (val2 < 0) && (val3 < 0) && (val4 < 0));

    if(B1 != B2) fail = true;

  } // loop i
  printf("line segment intersection test..........");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;

  pVec2_t B4[4];
  Vec2_t B4V[4];
  for(i=0;i<4;i++) B4[i] = &B4V[i];

  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      for(k = 0;k<4;k++){
	A4[k]->val[j] = rand()/((double)rand() + 1.0);
	B4[k]->val[j] = rand()/((double)rand() + 1.0);
      }
    }

    B1 = IntersectQuad_p(A4, B4);

    B2 = false;
    for(j=0;j<4;j++)
      {
	if(InsideQuad_p(A4, B4[j])) B2 = true;
	if(InsideQuad_p(B4, A4[j])) B2 = true;
	if(IntersectLineSegs_p(A4[0], A4[1], B4[j], B4[(j+1)%4])) B2 = true;
	if(IntersectLineSegs_p(A4[1], A4[2], B4[j], B4[(j+1)%4])) B2 = true;
	if(IntersectLineSegs_p(A4[2], A4[3], B4[j], B4[(j+1)%4])) B2 = true;
	if(IntersectLineSegs_p(A4[3], A4[0], B4[j], B4[(j+1)%4])) B2 = true;
      }


    if(B1 != B2)
      { 
	fail = true;
	printf("%d %d\n\n", B1, B2);
	for(j=0;j<4;j++)printf("A%d %f %f\n", j, A4[j]->val[0], A4[j]->val[1]);
	for(j=0;j<4;j++)printf("B%d %f %f\n", j, B4[j]->val[0], B4[j]->val[1]);
      }

  } // loop i
  printf("Quadrilateral intersection test.........");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;


  CAng ang1;
  for(i=0;i<1000;i++){
    val = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    ang1.Set(val);
    val1 = ang1.Get();
    valE = ang1.GetExtended();
    val2 = atan2(ang1.GetSin(),ang1.GetCos());
    if(!Approx(val, valE)||!Approx(val1, val2)) fail = true;
  }
  printf("CAng test...............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;
  
  CAngle1 angle1, angle2, angle3, angle4;
  CAng ang2;
  for(i=0;i<1000;i++){
    val = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    V2_1.val[0] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    V2_1.val[1] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    ang1.Set(val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    angle1.Set(val);
    angle2.Set(ang1);
    angle3.Set(&ang1);
    angle4.Set(&V2_1);

    if(!Approx(val, angle1.GetDExt())) fail = true;
    if(!Approx(angle2.GetD(), atan2(angle2.GetSin(), angle2.GetCos()))) fail = true;
    if(!Approx((angle3.GetAng(&ang2))->Get(), ang1.Get())) fail = true;
    angle4.GetV(&V2_2);
    if(!Approx(&V2_2, (UnitVector(&V2_1, &V2_3), &V2_3))) fail = true;
    angle3.GetM(&M2_1);
    if(!Rotation_p(&M2_1)) fail = true;
    if(!Approx(Transpose(&M2_1, &M2_2), (Inverse(&M2_1, &M2_3), &M2_3))) fail = true;
  }
  angle1.Set(M_2PI/7.0);
  
  V2_2 = V2_1;
  for(j=0;j<7;j++){ angle1.Rotate(&V2_2,&V2_3);V2_2 = V2_3;}
  if(!Approx(&V2_1, &V2_2)) fail = true;
  V2_2 = V2_1;
  for(j=0;j<7;j++){ angle1.RotateInv(&V2_2,&V2_3);V2_2 = V2_3;}
  if(!Approx(&V2_1, &V2_2)) fail = true;

  CAngle1 *angle5 = new CAngle1(val2 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
  if(angle5->GetDExt() != val2) fail = true;
  delete angle5;
  SetZero(&V2_1); if(angle1.Set(&V2_1)) fail = true;
  printf("CAngle1 test............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;
  


  /// CAngle2 test suite
  CAngle2 angle21, angle22, angle23, angle24;
  CAng ang_2[2];
  pCAng pang_2[2];
  pang_2[0] = &ang_2[0]; pang_2[1] = &ang_2[1];
  for(i=0;i<1000;i++){
    val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    val2 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    V2_6.val[0] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    V2_6.val[1] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    V3_1.val[0] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    V3_1.val[1] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    V3_1.val[2] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    ang1.Set(val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    ang2.Set(val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    ang_2[0].Set(val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    ang_2[1].Set(val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    pang_2[0]->Set(val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    pang_2[1]->Set(val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));

    angle21.Set(val1, val2);
    V2_2 = *angle21.GetDExt(&V2_1);
    angle21.GetD(&V2_3);
    if(!Approx(sin(val1), angle21.GetSin(&V2_5)->val[0])||!Approx(sin(val2), angle21.GetSin(&V2_5)->val[1])) fail = true;
    if(!Approx(cos(val1), angle21.GetCos(&V2_5)->val[0])||!Approx(cos(val2), angle21.GetCos(&V2_5)->val[1])) fail = true;
    if(!Approx(V2_1.val[0], val1)||!Approx(V2_1.val[1], val2)||!Approx(&V2_1, &V2_2)) fail = true;
    if(!Approx(&V2_1, &V2_3)){
      if((V2_1.val[0] < M_PI)&&(V2_1.val[0] > -M_PI) && (V2_1.val[1] < M_PI)&&(V2_1.val[1] > -M_PI))fail = true;
    }

    angle21.Set(&ang1, &ang2); angle21.GetDExt(&V2_1);
    if(!Approx(V2_1.val[0], ang1.GetExtended())||!Approx(V2_1.val[1], ang2.GetExtended())) fail = true;

    angle21.Set(ang_2); angle21.GetDExt(&V2_1);
    if(!Approx(V2_1.val[0], ang_2[0].GetExtended())||!Approx(V2_1.val[1], ang_2[1].GetExtended())) fail = true;

    angle21.Set(pang_2); angle21.GetDExt(&V2_1);
    if(!Approx(V2_1.val[0], ang_2[0].GetExtended())||!Approx(V2_1.val[1], ang_2[1].GetExtended())) fail = true;

    angle21.Set(&V2_6); angle21.GetDExt(&V2_1);
    if(!Approx(&V2_1, &V2_6)) fail = true;

    angle21.Set(&V3_1); angle21.GetD(&V2_1);
    UnitVector(&V3_1, &V3_2);
    if(!Approx(V3_2.val[0], cos(V2_1.val[0])*cos(V2_1.val[1]))||
       !Approx(V3_2.val[1], sin(V2_1.val[0])*cos(V2_1.val[1]))||
       !Approx(V3_2.val[2], sin(V2_1.val[1]))) fail = true;
    V3_4 = *angle21.GetV(&V3_3);
    if(!Approx(&V3_4, &V3_3)||!Approx(&V3_2, &V3_3)) fail = true;

  }
  SetZero(&V3_1); if(angle21.Set(&V3_1)) fail = true;

  printf("CAngle2 test............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;
  
  CAngle3 angle31, angle32, angle33, angle34;
  CAng ang_3[3];
  pCAng pang_3[3];
  CAng ang3;
  for(i=0;i<3;i++) pang_3[i] = &ang_3[i];
  for(i=0;i<1000;i++){
    val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    val2 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    val3 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    for(k=0;k<3;k++){
      ang_3[k].Set(((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
      V3_1.val[k] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    ang1.Set(((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    ang2.Set(((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    ang3.Set(((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0));
    
    angle31.Set(val1, val2, val3);
    V3_3 = *angle31.GetDExt(&V3_2);
    angle31.GetD(&V3_4);
    if(!Approx(sin(val1), angle31.GetSin(&V3_5)->val[0])||
       !Approx(sin(val2), angle31.GetSin(&V3_5)->val[1])||
       !Approx(sin(val3), angle31.GetSin(&V3_5)->val[2])) fail = true;
    if(!Approx(cos(val1), angle31.GetCos(&V3_5)->val[0])||
       !Approx(cos(val2), angle31.GetCos(&V3_5)->val[1])||
       !Approx(cos(val3), angle31.GetCos(&V3_5)->val[2])) fail = true;
    if(!Approx(V3_2.val[0], val1)||!Approx(V3_2.val[1], val2)||!Approx(V3_2.val[2], val3)||!Approx(&V3_3, &V3_2)) fail = true;

    if(!Approx(&V3_2, &V3_4)){
      if((V3_2.val[0] < M_PI)&&(V3_2.val[0] > -M_PI) && 
	 (V3_2.val[1] < M_PI)&&(V3_2.val[1] > -M_PI) &&	 
	 (V3_2.val[2] < M_PI)&&(V3_2.val[2] > -M_PI)) fail = true;
    }

    angle31.Set(&ang1, &ang2, &ang3); angle31.GetDExt(&V3_2);
    if(!Approx(V3_2.val[0], ang1.GetExtended())||
       !Approx(V3_2.val[1], ang2.GetExtended())||
       !Approx(V3_2.val[2], ang3.GetExtended())) fail = true;

    angle31.Set(ang_3); angle31.GetDExt(&V3_2);
    if(!Approx(V3_2.val[0], ang_3[0].GetExtended())||
       !Approx(V3_2.val[1], ang_3[1].GetExtended())||
       !Approx(V3_2.val[2], ang_3[2].GetExtended())) fail = true;

    angle31.Set(pang_3); angle31.GetDExt(&V3_2);
    if(!Approx(V3_2.val[0], ang_3[0].GetExtended())||
       !Approx(V3_2.val[1], ang_3[1].GetExtended())||
       !Approx(V3_2.val[2], ang_3[2].GetExtended())) fail = true;

    angle31.Set(&V3_1); angle31.GetDExt(&V3_2);
    if(!Approx(&V3_1, &V3_2)) fail = true;

    val = exp(-0.8*M_PI2);
    UnitVector(&V3_1, &V3_2);
    Mult_sv(val, &V3_2, &V3_3);
    angle31.SetV(&V3_3); angle31.GetDExt(&V3_4);
    if(!Approx(V3_4.val[2], -0.8*M_PI2)) fail = true;

    angle31.GetV(&V3_4);
    if(!Approx(&V3_2, &V3_4)) fail = true;

    angle31.SetV(&V3_3);
    angle31.GetD(&V3_1);
    angle31.GetRot(&M3_1);
    angle32.SetM(&M3_1);
    angle31.GetRot(&M3_2);
    angle32.GetD(&V3_4);
    if(!Approx(&V3_4, &V3_1)) fail = true;

    angle31.SetV(&V3_1);
    angle31.GetRot(&M3_1);
    angle31.GetRotInv(&M3_2);
    if(!Approx(Mult_mm(&M3_1, &M3_2, &M3_3))) fail = true;

    I1 = rand()%3;
    switch(I1){
    case 0:
      val1 = M_2PI/7.0;
      val2 = 0.0;
      val3 = 0.0;
      break;
    case 1:
      val1 = 0.0;
      val2 = M_2PI/7.0;
      val3 = 0.0;
      break;
    case 2:
      val1 = 0.0;
      val2 = 0.0;
      val3 = M_2PI/7.0;
      break;
    }
    angle31.Set(val1,val2,val3);
    V3_2 = V3_1;
    for(j=0;j<7;j++){ angle31.Rotate(&V3_2, &V3_3); V3_2 = V3_3;}
    if(!Approx(&V3_1, &V3_2)) fail = true;
    V3_2 = V3_1;
    for(j=0;j<7;j++){ angle31.RotateInv(&V3_2, &V3_3); V3_2 = V3_3;}
    if(!Approx(&V3_1, &V3_2)) fail = true;
    
    if(!Approx(&V3_2, angle31.RotateInv(angle31.Rotate(&V3_2, &V3_3), &V3_4))) fail = true;
    


  } // loop i
  SetZero(&V3_1); if(angle31.SetV(&V3_1)) fail = true;
  printf("CAngle3 test............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;



  CTransform T1, T2, T3, T4;

  for(i=0;i<1000;i++){
    val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    val2 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    val3 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    for(j=0;j<3;j++) V3_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    angle31.Set(val1,val2,val3);
    B1 = T1.Set(angle31.GetRot(&M3_1),&V3_1);
    T2.Set(&angle31, &V3_1);
    if(!B1) fail = true;
    I1 = rand()%3; I2 = rand()%3;
    val = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    M3_1.val[I1][I2] += val;
    B1 = T1.Set(&M3_1,&V3_1);
    if(B1) fail = true;
    M3_1.val[I1][I2] -= val;

    T1.Get(&angle32,&V3_3);
    T2.Get(&M3_2, &V3_2);
    if(!Approx(&M3_1, &M3_2) || !Approx(&V3_1, &V3_2)) fail = true;
    if(!Approx(angle32.GetRot(&M3_4), &M3_1) || !Approx(&V3_3, &V3_1)) fail = true;

    T1.GetInv(&M3_2, &V3_2);
    for(j=0;j<3;j++) V3_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    // Now we have: ABR in M3_1, ABRT in M3_2, APBorg in V3_1, and BPAorg in V3_2.
    if(!Approx(Mult_mm(&M3_1, &M3_2, &M3_3))) fail = true;
    // suppose V3_3 is a point expressed in frame B: PB.
    // Then PA = ABR*PB + APBorg
    // and PB =  BAR*PA + BPAorg == ABRT*PA - ABRT*APBorg
    Add_v(Mult_mv(&M3_1, &V3_3, &V3_4), &V3_1, &V3_5);
    Add_v(Mult_mv(&M3_2, &V3_5, &V3_4), &V3_2, &V3_6);
    if(!Approx(&V3_3, &V3_6)) fail = true;
    V3_2 = *T1.Apply(&V3_3, &V3_4);
    if(!Approx(&V3_2, &V3_4)) fail = true;
    if(!Approx(&V3_5, &V3_4)) fail = true;
    V3_2 = *T1.ApplyInv(&V3_5, &V3_4);
    if(!Approx(&V3_2, &V3_4)) fail = true;
    if(!Approx(&V3_3, &V3_4)) fail = true;
    //    T1.Print();

    // Checking that the transform composed with its inverse is the identity 
    // isn't a complete test of correctness for composition, but it's a start.
    T1.GetInv(&M3_2, &V3_2);  // T1 is ABT
    T2.Set(&M3_2, &V3_2);     // T2 is BAT
    T1.Apply(&T2, &T3);        // result should be the identity.
    T3.Get(&M3_3, &V3_3);
    if(!Approx(&M3_3) || !Approx(&V3_3)) fail = true;

    T1.ApplyInv(&T2, &T3);        // result should be the identity.
    T3.Get(&M3_4, &V3_4);
    if(!Approx(&M3_4) || !Approx(&V3_4)) fail = true;

  }

  printf("CTransform test.........................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;


  CLink L1;
  for(i=0;i<1000;i++){
    V2_1.val[0] = rand()/((double)rand() + 1.0);
    V2_1.val[1] = rand()/((double)rand() + 1.0);
    val = rand()/((double)rand() + 1.0);
    val1 = V2_1.val[0] - V2_1.val[1];
    L1.Set(val, &V2_1);
    L1.Get(&V3_1, &V2_2);
    if(!Approx(&V2_1, &V2_2)) fail = true;
    if(!Approx(V3_1.val[0], val)) fail = true;
    if(!Approx(V3_1.val[1], (val2 = atan2(val1, val)))) fail = true;
    if(!Approx(V3_1.val[2], (val3 = Length(val1, val)))) fail = true;
    if(!Approx(val, L1.GetLen())) fail = true;
    if(!Approx(val2, L1.GetAlpha())) fail = true;
    if(!Approx(val3, L1.GetRho())) fail = true;
  }
  printf("CLink test..............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;


  CLine2 CL2_1, CL2_2;
  for(i=0;i<1000;i++){
    for(j= 0;j<2;j++){
      V2_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V2_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V2_6.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V2_7.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    CL2_1.Set(&V2_1, &V2_2);
    CL2_1.Get(&V2_3, &V2_4); // 2_1, 2_4 new refs
    if(!Approx(&V2_1, &V2_3) || !Approx(&V2_4, (UnitVector(&V2_2, &V2_5),&V2_5))) fail = true;

    val = CL2_1.L2Distance(&V2_6);
    Sub_v(&V2_6, &V2_1, &V2_5);
    val1 = Cross(&V2_2, &V2_5)/Length(&V2_2);
    if(!Approx(val, val1)) fail = true;
    if(!Approx(CL2_1.L2Distance(&V2_6, &V2_5), val1)) fail = true;
    if(!Approx(CL2_1.L2Distance(&V2_6, &val2), val1)) fail = true;
    if(!Approx(CL2_1.L2Distance(&V2_6, &V2_2, &val3), val1)) fail = true;
    if(!Approx(val2, val3) || !Approx(&V2_5, &V2_2)) fail = true; // just keep val3, V2_2
    if(!Approx(fabs(val3), Distance(&V2_2, &V2_1))) fail = true;
    if(!Approx(Cross(&V2_4, Sub_v(&V2_2, &V2_1, &V2_5)))) fail = true;
    if(!Approx(fabs(val1), Distance(&V2_2, &V2_6))) fail = true;

    CL2_2.Set(&V2_6, &V2_4);
    if(!CL2_1.Parallel_p(&CL2_2)) fail = true;
    if(!CL2_2.Parallel_p(&CL2_1)) fail = true;
    if(CL2_1.L2Intersect(&CL2_2, &V2_8)) fail = true;
    CL2_2.Set(&V2_1, &V2_6);
    if(CL2_1.Parallel_p(&CL2_2)) fail = true;
    if(CL2_2.Parallel_p(&CL2_1)) fail = true;
    
    
    UnitVector(&V2_7, &V2_8);
    CL2_2.Set(&V2_6, &V2_7);
    if(!CL2_1.L2Intersect(&CL2_2, &V2_2)) fail = true;
    if(!Approx(Cross(&V2_4, Sub_v(&V2_2, &V2_1, &V2_5)))) fail = true;
    if(!Approx(Cross(&V2_8, Sub_v(&V2_2, &V2_6, &V2_5)))) fail = true;
  } // loop i
  printf("CLine2 test.............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;


  CLine2Seg CL2S_1, CL2S_2;
  for(i=0;i<1000;i++){
    for(j= 0;j<2;j++){
      V2_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V2_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V2_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V2_4.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    val1 = rand()/((double)rand() + 1.0);
    val2 = rand()/((double)rand() + 1.0);
    CL2S_1.Set(&V2_1, &V2_2, val1);
    CL2S_2.SetEndPts(&V2_1, &V2_2);
    CL2S_1.Get(&V2_5, &V2_6);
    if(!Approx(&V2_1, &V2_5) || !Approx((UnitVector(&V2_2,&V2_7),&V2_7), &V2_6)) fail = true;
    CL2S_1.GetEndPts(&V2_5, &V2_6);
    if(!Approx(&V2_1, &V2_5)) fail = true;
    if(!Approx(Add_v(&V2_1, Mult_sv(val1, &V2_7, &V2_8), &V2_5), &V2_6)) fail = true;
    CL2S_2.GetEndPts(&V2_5, &V2_6);
    if(!Approx(&V2_1, &V2_5) || !Approx(&V2_2, &V2_6)) fail = true;
    B1 = CL2S_1.ClosestPtIn(&V2_3, &val3);
    CL2S_1.L2Distance(&V2_3, &val4);
    if(((val4 >= 0) && (val4 <= val1)) != B1) fail = true;

  } // loop i
  printf("CLine2Seg test..........................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;

  CLine3 CL3_1, CL3_2, CL3_3;
  for(i=0;i<1000;i++){
    for(j= 0;j<3;j++){
      V3_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    if(!CL3_1.Set(&V3_1, &V3_2)) fail = true;
    CL3_1.Get(&V3_6, &V3_4);
    if(!Approx(&V3_1, &V3_6) || !Approx((UnitVector(&V3_2,&V3_5),&V3_5), &V3_4)) fail = true;

    CL3_2.Set(&V3_1, &V3_3);
    CL3_3.Set(&V3_3, &V3_2);
    if(CL3_1.Parallel_p(&CL3_2) || CL3_2.Parallel_p(&CL3_1)) fail = true;
    if(!CL3_1.Parallel_p(&CL3_3) || !CL3_3.Parallel_p(&CL3_1)) fail = true;

    val = CL3_1.L3Distance(&V3_3);
    Sub_v(&V3_3, &V3_1, &V3_4); // save V3_1 and V3_5 as init, V3_3 as test pt.
    val1 = Cross(&V3_4, &V3_5); 
    if(!Approx(val, val1)) fail = true;
    if(!Approx(CL3_1.L3Distance(&V3_3, &V3_2), val1)) fail = true; // test V3_2 as ptOn.
    if(!Approx(CL3_1.L3Distance(&V3_3, &val2), val1)) fail = true;
    if(!Approx(CL3_1.L3Distance(&V3_3, &V3_4, &val3), val1)) fail = true;
    if(!Approx(&V3_2, &V3_4) || !Approx(val2, val3)) fail = true;
    if(!Approx(Add_v(&V3_1, Mult_sv(val2, &V3_5, &V3_4), &V3_6), &V3_2)) fail = true;
    if(!Approx(Distance(&V3_3, &V3_6), val1)) fail = true;

    for(j= 0;j<3;j++){
      V3_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_4.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    CL3_2.Set(&V3_2, &V3_4);
    UnitVector(&V3_4, &V3_6); // save V3_2 and V3_6 as init.
    CL3_3.Set(&V3_1, &V3_6); // parallel to CL3_2

    val = CL3_3.L3Distance(&CL3_2); // parallel biperp
    val2 = fabs(Cross(Sub_v(&V3_2, &V3_1, &V3_3), &V3_6));
    if(!Approx(val, val2)) fail = true;
    if(!Approx(val, CL3_3.L3Distance(&CL3_2, &val2))) fail = true;
    if(!Approx(val, CL3_3.L3Distance(&CL3_2, &V3_7))) fail = true;
    if(!Approx(val, CL3_3.L3Distance(&CL3_2, &V3_8, &val3))) fail = true;
    if(!Approx(val2) || !Approx(val3)) fail = true;
    if(!Approx(&V3_7, &V3_8) || !Approx(&V3_7, &V3_1)) fail = true;

    if(!Approx(CL3_1.L3Distance(&CL3_2), CL3_2.L3Distance(&CL3_1))) fail = true;
    val = CL3_1.L3Distance(&CL3_2); // non-parallel biperp
    val1 = fabs(Dot((UnitVector(Cross(&V3_6, &V3_5, &V3_8),&V3_3),&V3_3), Sub_v(&V3_2, &V3_1, &V3_7)));
    if(!Approx(val, val1)) fail = true;
    if(!Approx(val, (val1 = CL3_1.L3Distance(&CL3_2, &val2)))) fail = true;
    if(!Approx(val, CL3_1.L3Distance(&CL3_2, &V3_7))) fail = true;
    if(!Approx(val, CL3_1.L3Distance(&CL3_2, &V3_8, &val3))) fail = true;
    if(!Approx(val2, val3) || !Approx(&V3_7, &V3_8)) fail = true; // keep val2, V3_7
    if(!Approx(&V3_7, Add_v(&V3_1, Mult_sv(val2, &V3_5, &V3_3), &V3_8))) fail = true; // pt is on line1 the correct distance away
    val2 = CL3_2.L3Distance(&CL3_1, &V3_8, &val3);
    if(!Approx(val, val2)) fail = true;
    if(!Approx(&V3_8, Add_v(&V3_2, Mult_sv(val3, &V3_6, &V3_3), &V3_4))) fail = true; // pt is on line2 the correct distance away
    if(!Approx(val, Distance(&V3_7, &V3_8))) fail = true;
  } // loop i
  if(CL3_1.Set(&V3_1, gZVec3)) fail = true;
  printf("CLine3 test.............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;

  CPlane CP1, CP2, CP3;
  for(i=0;i<1000;i++){
    for(j= 0;j<3;j++){
      V3_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    angle31.Set(V3_2.val[0], V3_2.val[1], V3_2.val[2]);
    angle31.GetRot(&M3_1);
    B1 = CP1.Set(&V3_1, &M3_1);
    if(!B1) fail = true;
    M3_2 = M3_1;
    I1 = rand()%3; I2 = rand()%3;
    M3_2.val[I1][I2] += 1.0;
    if(CP2.Set(&V3_1, &M3_2)) fail = true;
    CP1.Get(&V3_4, &M3_2);
    if(!Approx(&V3_4, &V3_1) || !Approx(&M3_1, &M3_2)) fail = true;
    M3_2 = *CP1.GetRot(&M3_3);
    if(!Approx(&M3_2, &M3_1) || !Approx(&M3_2, &M3_3)) fail = true;
    V3_5 = *CP1.GetPoint(&V3_4);
    if(!Approx(&V3_5, &V3_4) || !Approx(&V3_5, &V3_1)) fail = true;

    val = CP1.PDistance(&V3_3);
    Sub_v(&V3_3, &V3_1, &V3_4);
    val1 = M3_1.val[2][0]*V3_4.val[0] + M3_1.val[2][1]*V3_4.val[1] + M3_1.val[2][2]*V3_4.val[2];
    if(!Approx(val, val1)) fail = true;
    if(!Approx(val, CP1.PDistance(&V3_3, &V3_4))) fail = true;
    if(!Approx(val, CP1.PDistance(&V3_3, &V3_5, &val2))) fail = true;
    if(!Approx(&V3_4, &V3_5)) fail = true;
    if(!Approx(val2, Distance(&V3_4, &V3_1))) fail = true;
    if(!Approx(fabs(val), Distance(&V3_4, &V3_3))) fail = true;
    Sub_v(&V3_4, &V3_1, &V3_8); // 3_8 is the vector in the plane
    Sub_v(&V3_3, &V3_4, &V3_7); // 3_7 is the vector perp to the plane
    if(!Approx(Dot(&V3_8, &V3_7))) fail = true;

    Transpose(&M3_1, &M3_2);
    Neg_v(Mult_mv(&M3_1, &V3_1, &V3_4));
    CP2.Set(&V3_4, &M3_2);

    CP1.PRotateV(&V3_3, &V3_8);
    CP2.PRotateV(&V3_8, &V3_7);
    if(!Approx(&V3_7, &V3_3)) fail = true;

    CP1.PRotateP(&V3_3, &V3_8);
    CP2.PRotateP(&V3_8, &V3_7);
    if(!Approx(&V3_7, &V3_3)) fail = true;

    CP1.PRotateP(&V3_3, &V3_8);
    CP2.PRotateV(&V3_8, &V3_7);
    if(Approx(&V3_7, &V3_3)) fail = true;

    Sub_v(&V3_8, &V3_4, &V3_7);
    CP2.PRotateV(&V3_7, &V3_6);
    if(!Approx(&V3_6, &V3_3)) fail = true;
    
    // CP1 is still set by V3_1, M3_1.
    CL3_1.Set(&V3_2, &V3_3);
    if(!CP1.PIntersect(&CL3_1, &V3_4)) fail = true;
    CP1.PRotateP(&V3_2, &V3_5);
    CP1.PRotateV(&V3_3, &V3_6);
    Add_v(Mult_sv(-V3_5.val[2]/V3_6.val[2], &V3_6, &V3_7), &V3_5, &V3_8);
    if(!Approx(V3_8.val[2])) fail = true;
    CP2.PRotateP(&V3_8, &V3_7);
    if(!Approx(&V3_7, &V3_4)) fail = true;
    CP1.PIntersect(&CL3_1, &V2_1);
    if(!Approx(V2_1.val[0], V3_8.val[0]) || !Approx(V2_1.val[1], V3_8.val[1])) fail = true;

  } // loop i

  printf("CPlane test.............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;


  CCylinder CC1, CC2;
  count = 0;
  for(i=0;i<1000;i++){
    for(j= 0;j<3;j++){
      V3_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0) + 0.5;
    }
    CL3_1.Set(&V3_1, &V3_2);
    CC1.SetLine(&CL3_1);
    CC2.SetLine(&V3_1, &V3_2);
    CC1.Get(&V3_4, &V3_5);
    CL3_3 = *CC2.GetLine(&CL3_2);
    CL3_2.Get(&V3_6, &V3_7);
    UnitVector(&V3_2, &V3_8);
    if(!Approx(&V3_1, &V3_6) || !Approx(&V3_8, &V3_7)) fail = true;
    if(!Approx(&V3_1, &V3_4) || !Approx(&V3_8, &V3_5)) fail = true;
    CC1.SetPhys(&V2_1);
    V2_3 = *CC1.GetPhys(&V2_2);
    if(!Approx(&V2_2, &V2_3)) fail = true;
    if(!Approx(&V2_2, &V2_1)) fail = true;
    CL3_3.Get(&V3_4, &V3_5);
    if(!Approx(&V3_6, &V3_4) || !Approx(&V3_7, &V3_5)) fail = true;

    val = CL3_1.L3Distance(&V3_3, &val1);
    if(((val <= V2_1.val[0]) && (fabs(val1) <= V2_1.val[1])) != CC1.Inside_p(&V3_3)) fail = true;
    for(j= 0;j<3;j++){
      V3_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_4.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0) + 0.5;
      V2_2.val[j] = rand()/((double)rand() + 1.0) + 0.5;
    }
    CC1.SetLine(&V3_1, &V3_2);    CC1.SetPhys(&V2_1);
    CC2.SetLine(&V3_3, &V3_4);    CC2.SetPhys(&V2_2);
    CL3_1.Set(&V3_1, &V3_2);
    CL3_2.Set(&V3_3, &V3_4);
    if(CC1.Intersect_p(&CC2) != CC2.Intersect_p(&CC1)) fail = true;
    if(CC1.Intersect_p(&CC2)){
      count++;
      if(CL3_1.L3Distance(&CL3_2) > V2_1.val[0] + V2_2.val[0]) fail = true;
      if(Distance(&V3_1, &V3_3) > Length(&V2_1) + Length(&V2_2))  fail = true;
    }
    // Not complete, but not bad -- the cyl intersection test is an approximation anyway...
    // I'd probably end up repeating the code to test it.
  } // loop i

  printf("CCylinder test..........................");
  printf(fail?" failed\n":" succeeded\n");
  printf("%d cylinder intersections, %d misses -- should not be zero\n", count, 1000-count);
  fail = false;

  CJoint CJ1, CJ2;
  countmax= 0;countmin=0;countin=0;
  for(i=0;i<1000;i++){
    val = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    for(j= 0;j<3;j++){
      V3_1.val[j] = rand()/((double)rand() + 1.0);
      V3_2.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_4.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
      V3_5.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    CJ2.SetCylLoc(&V3_4, &V3_5); 
    for(j= 0;j<2;j++){
      V2_1.val[j] = rand()/((double)rand() + 1.0) + 0.5;
    }
    ang1.Set(val);
    CJ1.SetPos(val);
    CJ2.SetPos(&ang1);
    val1 = CJ1.GetPos();
    val2 = CJ2.GetPosExtended();
    if(!Approx(val, val2) || !Approx(cos(val1), cos(val))) fail = true;
    CJ1.SetDH(&V3_1);
    CJ2.SetDH(V3_1.val[0],V3_1.val[1],V3_1.val[2]);
    V3_4 = *CJ1.GetDH(&V3_5);
    CJ2.GetDH(&V3_6);
    for(j=0;j<3;j++) V3_7.val[j] = (float)V3_1.val[j];
    if(!Approx(&V3_4, &V3_5) || !Approx(&V3_4, &V3_1) || !Approx(&V3_7, &V3_6)) fail = true;
    val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    val2 = val1 + rand()/((double)rand() + 1.0) + 1.0;
    ang2.Set(val1);
    ang3.Set(val2);
    CJ1.SetLimits(val1, val2);
    CJ2.SetLimits(&ang2, &ang3);
    CJ1.GetLimits(&val3, &val4);
    if(!Approx(val1, val3)||!Approx(val2, val4)) fail = true;
    val3 = CJ1.GetMax();
    val4 = CJ1.GetMin();
    if(!Approx(val2, val3)||!Approx(val1, val4)) fail = true;
    val1 = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    I1 = CJ1.InsideLimits(val1);
    if(I1 == 1){
      if(val1 <= val3) fail = true;
      countmax++;
    }
    if(I1 == -1){
      if(val1 >= val4) fail = true;
      countmin++;
    }
    if(I1 == 0){
      if((val1 < val4) || (val1 > val3)) fail = true;
      countin++;
    }
    CJ1.SetCylLoc(&V3_2, &V3_3);
    CJ1.GetCylLoc(&V3_4, &V3_5);
    UnitVector(&V3_3, &V3_6);
    if(!Approx(&V3_4, &V3_2) || !Approx(&V3_6, &V3_5)) fail = true;
    CJ1.GetCyl(&CC1);
    CC1.Get(&V3_4, &V3_5);
    if(!Approx(&V3_4, &V3_2) || !Approx(&V3_6, &V3_5)) fail = true;
    T1 = *CJ1.GetTransform(&T2);
    T1.Get(&M3_1, &V3_8);
    T2.Get(&M3_2, &V3_7);
    if(!Approx(&M3_1, &M3_2) || !Approx(&V3_8, &V3_7)) fail = true;
    CJ1.SetPos(val);
    CJ1.SetDH(&V3_5);
    CJ1.GetTransform(&T1);
    T1.Apply(&V3_3, &V3_4);
    V3_6.val[0] = V3_4.val[0] - V3_5.val[1];
    V3_6.val[1] = V3_4.val[1]*cos(V3_5.val[0]) + V3_4.val[2]*sin(V3_5.val[0]);
    V3_6.val[2] = V3_4.val[2]*cos(V3_5.val[0]) - V3_4.val[1]*sin(V3_5.val[0]);
    V3_7.val[2] = V3_6.val[2] - V3_5.val[2];
    V3_7.val[0] = V3_6.val[0]*cos(val) + V3_6.val[1]*sin(val);
    V3_7.val[1] = V3_6.val[1]*cos(val) - V3_6.val[0]*sin(val);
    if(!Approx(&V3_7, &V3_3)) fail = true;
    CJ1.GetCyl(&CC1);
    CJ2.GetCyl(&CC2);
    if(CJ1.Collide_p(&CJ2) != CC1.Intersect_p(&CC2)) fail = true;
  } // loop i
  printf("CJoint test.............................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;
  printf("joint limits test: over:%d under:%d in:%d -- should not be zero\n",countmax, countmin, countin);

  // This is definitely not a complete check of obstacle/cylinder collisions, but it's decent
  CObstacle CO1, CO2;
  count = 0;countmin = 0;countmax = 0;
  A4[0] = &V2_1;
  A4[1] = &V2_2;
  A4[2] = &V2_3;
  A4[3] = &V2_4;
  for(i=0;i<1000;i++){
    for(j=0;j<3;j++){
      V3_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0)-1.0;
      V3_3.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0)-1.0;
      V3_2.val[j] = V3_1.val[j] + rand()/((double)rand() + 1.0)+4.0;
      V3_4.val[j] = V3_3.val[j] + rand()/((double)rand() + 1.0)+4.0;
      V3_8.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    CO1.SetLimits(&V3_1, &V3_2);
    CO2.SetLimits(&V3_3, &V3_4);
    CO1.GetLimits(&V3_5, &V3_6);
    if(!Approx(&V3_1, &V3_5) || !Approx(&V3_2, &V3_6)) fail = true;
    B1 = CO1.Inside_p(&V3_8);
    B2 = (V3_8.val[0] > V3_1.val[0]) && (V3_8.val[0] < V3_2.val[0]) &&
      (V3_8.val[1] > V3_1.val[1]) && (V3_8.val[1] < V3_2.val[1]) &&
      (V3_8.val[2] > V3_1.val[2]) && (V3_8.val[2] < V3_2.val[2]);
    if(B1 != B2) fail = true;
    if(B1) count++;
    if(CO1.Intersect_p(&CO2) != CO2.Intersect_p(&CO1)) fail = true;
    if(CO1.Intersect_p(&CO2)){
      countmin++;
      for(j=0;j<3;j++)if((V3_1.val[j] > V3_4.val[j]) || (V3_3.val[j] > V3_2.val[j])) fail = true;
    }
    for(j=0;j<2;j++){
      V2_5.val[j] = rand()/((double)rand() + 1.0);
    }
    UnitVector(&V3_4, &V3_8);
    CC1.SetLine(&V3_3, &V3_8);
    CC1.SetPhys(&V2_5);
    if(CO1.Intersect_p(&CC1)){ // if intersection
      countmax++;
      B1 = false;
      for(I1=0;I1<2;I1++)
	for(I2=0;I2<2;I2++)
	  for(I3=0;I3<2;I3++){
	    V3_7.val[0] = I1? V3_1.val[0]:V3_2.val[0];
	    V3_7.val[1] = I2? V3_1.val[1]:V3_2.val[1];
	    V3_7.val[2] = I3? V3_1.val[2]:V3_2.val[2];
	    if(CC1.Inside_p(&V3_7)) B1 = true;
	  }
      if(CO1.Inside_p(&V3_3)) B1 = true;
      // XY
      V2_1.val[0] = V3_1.val[0]; V2_1.val[1] = V3_1.val[1]; 
      V2_2.val[0] = V3_2.val[0]; V2_2.val[1] = V3_1.val[1]; 
      V2_3.val[0] = V3_2.val[0]; V2_3.val[1] = V3_2.val[1]; 
      V2_4.val[0] = V3_1.val[0]; V2_4.val[1] = V3_2.val[1]; 
      val = fabs(V3_8.val[2]); val1 = sqrt(1.0 - Square(val));
      val2 = val1*V2_5.val[1] + val*V2_5.val[0]; // newL
      val3 = atan2(V3_8.val[1], V3_8.val[0]);
      c3 = cos(val3); s3 = sin(val3);
      B4V[0].val[0] = V3_3.val[0] + c3*val2 + s3*V2_5.val[0];
      B4V[1].val[0] = V3_3.val[0] + c3*val2 - s3*V2_5.val[0];
      B4V[2].val[0] = V3_3.val[0] - c3*val2 - s3*V2_5.val[0];
      B4V[3].val[0] = V3_3.val[0] - c3*val2 + s3*V2_5.val[0];
      B4V[0].val[1] = V3_3.val[1] + s3*val2 - c3*V2_5.val[0];
      B4V[1].val[1] = V3_3.val[1] + s3*val2 + c3*V2_5.val[0];
      B4V[2].val[1] = V3_3.val[1] - s3*val2 + c3*V2_5.val[0];
      B4V[3].val[1] = V3_3.val[1] - s3*val2 - c3*V2_5.val[0];
      if(!IntersectQuad_p(A4, B4)) fail = true;
    } // if intersection
    else{ // no intersection
      B1 = false;
      for(I1=0;I1<2;I1++){
	for(I2=0;I2<2;I2++){
	  for(I3=0;I3<2;I3++){
	    V3_7.val[0] = I1? V3_1.val[0]:V3_2.val[0];
	    V3_7.val[1] = I2? V3_1.val[1]:V3_2.val[1];
	    V3_7.val[2] = I3? V3_1.val[2]:V3_2.val[2];
	    if(CC1.Inside_p(&V3_7)) fail = true; 
	  }
	}
	if(CO1.Inside_p(&V3_3)) fail = true;
      }
    } // else no int

  } // loop i
  printf("CObstacle test..........................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;
  printf("point overlaps: %d -- should not be zero\n", count);
  printf("obstacle overlaps: %d -- should not be zero\n", countmin);
  printf("cylinder overlaps: %d -- should not be zero\n", countmax);

  /*
  // Template
  for(i=0;i<100;i++){
    // 2D
    for(j= 0;j<2;j++){
      V2_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
    // 3D
    for(j= 0;j<3;j++){
      V3_1.val[j] = ((rand()%2)?-1.0:1.0)*rand()/((double)rand() + 1.0);
    }
  } // loop i
  printf("Containment test........................");
  printf(fail?" failed\n":" succeeded\n");
  fail = false;
  */





}
