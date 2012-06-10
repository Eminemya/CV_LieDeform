#include <mex.h>
#include <math.h>
#include <stdio.h>
#include "td.h"



void mexFunction(int nlhs, mxArray *plhs[], int nrhs,
const mxArray *prhs[])
{
int row1,row2,col,ww;
int choice[]={1,1,1,1,1,1,1,1,1};
/*={0,0,0,0,0,0,1,0,0};*/
/*choice[]={1,1,1,1,1,1,0,0,0};*/
double * img1, *img2, *imgout,background=0.0;

/*1) Read */
/*test*/
img1= mxGetPr(prhs[0]);
/*train*/
img2= mxGetPr(prhs[1]);
/*choice =mxGetPr(prhs[2]);*/
row1= mxGetN(prhs[0]);
row2= mxGetN(prhs[0]);
col= mxGetM(prhs[0]);
ww=(int)sqrt(col);


/*2) Calculate the tangent space at train */
int i,numTangents=0,numTangentsRemaining;
double ** tangents;
  for(i=0;i<maxNumTangents;++i) {
   /*printf("nn %d,%\n",i,choice[i]);*/
    if(choice[i]>0) numTangents++;
  }

  tangents=(double **)malloc(numTangents*sizeof(double *));
  for(i=0;i<numTangents;++i) {
    tangents[i]=(double *)malloc(col*sizeof(double));
  }

  /* determine the tangents of the first image*/
   calculateTangents(img2, tangents, numTangents,ww,ww, choice, background);

  /* find the orthonormal tangent subspace */
  numTangentsRemaining = normalizeTangents(tangents, numTangents, ww, ww);

/*3) Project test onto the tangent space*/
plhs[0] =mxCreateDoubleMatrix(1,col, mxREAL);
imgout = mxGetPr(plhs[0]);

calculateClosest(img2, img1,tangents, numTangents, col,imgout);

  for(i=0;i<numTangents;++i) {
    free(tangents[i]);
  }
    free(tangents);
}
