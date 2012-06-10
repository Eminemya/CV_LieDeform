#include <mex.h>
#include <math.h>
#include <stdio.h>

#define templatefactor1 0.1667
#define templatefactor2 0.6667
#define templatefactor3 0.08
/* the template looks like this (extended Sobel):
   0   f1 0 -f1  0
   f3  f2 0 -f2 -f3
   0   f1 0 -f1  0  */
/* note: this template works well for 16x16 sized images, for different sizes an additional smoothing
   might be helpful */


/* constant for brightness tangent */
#define additiveBrightnessValue 0.1

/* constant size of "choice" = max number of tangents */
#define maxNumTangents 9


int tdIndex(int y, int x, int width){
  return y*width+x;
}
/** Calculates the tangents for one image. */
int calculateTangents2(const double * image, double * tangents, const int numTangents,
                      const int height, const int width, const int * choice, const double background){
  int j,k,ind,tangentIndex,maxdim;
  double tp,factorW,offsetW,factorH,factor,offsetH,halfbg;
  double *tmp, *x1, *x2, *currentTangent;
  
  int size=height*width;
  maxdim=(height>width)?height:width;

  tmp=(double*)malloc(maxdim*sizeof(double));
  x1=(double*)malloc(size*sizeof(double));
  x2=(double*)malloc(size*sizeof(double));
            
  factorW=((double)width*0.5);
  offsetW=0.5-factorW;
  factorW=1.0/factorW;

  factorH=((double)height*0.5);
  offsetH=0.5-factorH;
  factorH=1.0/factorH;

  factor=(factorH<factorW)?factorH:factorW; 
  halfbg=0.5*background;


  /* x1 shift along width */
  /* first use mask 1 0 -1 */
  for(k=0; k<height; k++) {
    /* first column */
    ind=tdIndex(k,0,width);
    x1[ind]= halfbg - image[ind+1]*0.5;
    /* other columns */
    for(j=1; j<width-1;j++) {
      ind=tdIndex(k,j,width);
      x1[ind]=(image[ind-1]-image[ind+1])*0.5;
    }
    /* last column */
    ind=tdIndex(k,width-1,width);
    x1[ind]= image[ind-1]*0.5 - halfbg;
  }
  /* now compute 3x3 template */
  /* first line */
  for(j=0;j<width;j++) {
    tmp[j]=x1[j];
    x1[j]=templatefactor2*x1[j]+templatefactor1*x1[j+width];
  }
  /* other lines */
  for(k=1;k<height-1;k++)
    for(j=0;j<width;j++) {
      ind=tdIndex(k,j,width);
      tp=x1[ind];
      x1[ind]=templatefactor1*tmp[j]+templatefactor2*x1[ind]+
	templatefactor1*x1[ind+width];
      tmp[j]=tp;
    }
  /* last line */
  for(j=0;j<width;j++) {
    ind=tdIndex(height-1,j,width);
    x1[ind]=templatefactor1*tmp[j]+templatefactor2*x1[ind];
  }
  /* now add the remaining parts outside the 3x3 template */
  /* first two columns */
  for(j=0;j<2;j++)
    for(k=0;k<height;k++) {
      ind=tdIndex(k,j,width);
      x1[ind]+=templatefactor3*background;
    } 
  /* other columns */
  for(j=2;j<width;j++)
    for(k=0;k<height;k++) {
      ind=tdIndex(k,j,width);
      x1[ind]+=templatefactor3*image[ind-2];
    } 
  for(j=0;j<width-2;j++)
    for(k=0;k<height;k++) {
      ind=tdIndex(k,j,width);
      x1[ind]-=templatefactor3*image[ind+2];
    }
  /* last two columns*/
  for(j=width-2;j<width;j++)
    for(k=0;k<height;k++) {
      ind=tdIndex(k,j,width);
      x1[ind]-=templatefactor3*background;
    }


  /*x2 shift along height */
  /* first use mask 1 0 -1 */
  for(j=0; j<width;j++) {
    /* first line */
    x2[j]= halfbg - image[j+width]*0.5;
    /* other lines */
    for(k=1; k<height-1; k++) {
      ind=tdIndex(k,j,width);
      x2[ind]=(image[ind-width]-image[ind+width])*0.5;
    }
    /* last line */
    ind=tdIndex(height-1,j,width);
    x2[ind]= image[ind-width]*0.5 - halfbg;
  }

  /* now compute 3x3 template */
  /* first column */
  for(j=0;j<height;j++) {
    ind=tdIndex(j,0,width);
    tmp[j]=x2[ind];
    x2[ind]=templatefactor2*x2[ind]+templatefactor1*x2[ind+1];
  }
  /* other columns */
  for(k=1;k<width-1;k++)
    for(j=0;j<height;j++) {
      ind=tdIndex(j,k,width);
      tp=x2[ind];
      x2[ind]=templatefactor1*tmp[j]+templatefactor2*x2[ind]+
	templatefactor1*x2[ind+1];
      tmp[j]=tp;
    }
  /* last column */
  for(j=0;j<height;j++) {
    ind=tdIndex(j,width-1,width);
    x2[ind]=templatefactor1*tmp[j]+templatefactor2*x2[ind];
  }

  /* now add the remaining parts outside the 3x3 template */
  for(j=0;j<2;j++)
    for(k=0;k<width;k++) {
      ind=tdIndex(j,k,width);
      x2[ind]+=templatefactor3*background;
    } 
  for(j=2;j<height;j++)
    for(k=0;k<width;k++) {
      ind=tdIndex(j,k,width);
      x2[ind]+=templatefactor3*image[ind-2*width];
    } 
  for(j=0;j<height-2;j++)
    for(k=0;k<width;k++) {
      ind=tdIndex(j,k,width);
      x2[ind]-=templatefactor3*image[ind+2*width];
    }
  for(j=height-2;j<height;j++)
    for(k=0;k<width;k++) {
      ind=tdIndex(j,k,width);
      x2[ind]-=templatefactor3*background;
    }


  /* now go through the tangents */

  tangentIndex=0;

  if(choice[0]>0){      for(ind=0;ind<size;ind++) tangents[tangentIndex*size+ind]=x1[ind];
    tangentIndex++;
  }

  if(choice[1]>0){      
    for(ind=0;ind<size;ind++) tangents[tangentIndex*size+ind]=x2[ind];
    tangentIndex++;
  }

  if(choice[2]>0){              
    ind=0;
    for(k=0;k<height;k++)
      for(j=0;j<width;j++) {
	tangents[tangentIndex*size+ind] = ((j+offsetW)*x1[ind] - (k+offsetH)*x2[ind])*factor;
	ind++;
      }
    tangentIndex++;
  }

  if(choice[3]>0){      
    ind=0;
    for(k=0;k<height;k++)  
      for(j=0;j<width;j++) {
	tangents[tangentIndex*size+ind] = ((k+offsetH)*x1[ind] + (j+offsetW)*x2[ind])*factor;
	ind++;
      }
    tangentIndex++;
  }

  if(choice[4]>0){      
    ind=0;
    for(k=0;k<height;k++)
      for(j=0;j<width;j++) {
	tangents[tangentIndex*size+ind] = ((j+offsetW)*x1[ind] + (k+offsetH)*x2[ind])*factor;
	ind++;
      }
    tangentIndex++;
  }

  if(choice[5]>0){      
    ind=0;
    for(k=0;k<height;k++)
      for(j=0;j<width;j++) {
	tangents[tangentIndex*size+ind] = ((k+offsetH)*x1[ind] - (j+offsetW)*x2[ind])*factor;
	ind++;
      }
    tangentIndex++;
  }

  if(choice[6]>0){      
    ind=0;
    for(k=0;k<height;k++)
      for(j=0;j<width;j++) {
	tangents[tangentIndex*size+ind] = x1[ind]*x1[ind] + x2[ind]*x2[ind];
	ind++;
      } 
    tangentIndex++;
  }

  if(choice[7]>0){      
    for(ind=0;ind<size;ind++)
      tangents[tangentIndex*size+ind] = additiveBrightnessValue; 
    tangentIndex++;
  }

  if(choice[8]>0){      
    for(ind=0;ind<size;ind++)
      tangents[tangentIndex*size+ind] = image[ind];
    tangentIndex++;
  }

  free(tmp);
  free(x1);
  free(x2);
  
 return tangentIndex;
}


void mexFunction(int nlhs, mxArray *plhs[], int nrhs,
const mxArray *prhs[])
{
int col,ww;
int choice[]={1,1,1,1,1,1,1,0,0};
/*choice[]={1,1,1,1,1,1,0,0,0};*/
double * img1, background=0.0;

/*1) Read */
img1= mxGetPr(prhs[0]);
/*train*/

col= mxGetM(prhs[0]);
ww=(int)sqrt(col);


/*2) Calculate the tangent space at train */
int i,numTangents=0;
double * tangents;
  for(i=0;i<maxNumTangents;++i) {
    if(choice[i]>0) numTangents++;
  }

plhs[0] =mxCreateDoubleMatrix(col, numTangents,mxREAL);
tangents = mxGetPr(plhs[0]);

  /* determine the tangents of the first image*/
   calculateTangents2(img1, tangents, numTangents,ww,ww, choice, background);
  
}
