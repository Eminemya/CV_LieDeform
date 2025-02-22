#include "mex.h"
#include "project.h"
#include "Image.h"
#include "OpticalFlow.h"
#include <iostream>

using namespace std;

// void LoadImage(DImage& image,const mxArray* matrix)
// {
// 	if(mxIsClass(matrix,"uint8"))
// 	{
// 		image.LoadMatlabImage<unsigned char>(matrix);
// 		return;
// 	}
// 	if(mxIsClass(matrix,"int8"))
// 	{
// 		image.LoadMatlabImage<char>(matrix);
// 		return;
// 	}
// 	if(mxIsClass(matrix,"int32"))
// 	{
// 		image.LoadMatlabImage<int>(matrix);
// 		return;
// 	}
// 	if(mxIsClass(matrix,"uint32"))
// 	{
// 		image.LoadMatlabImage<unsigned int>(matrix);
// 		return;
// 	}
// 	if(mxIsClass(matrix,"int16"))
// 	{
// 		image.LoadMatlabImage<short int>(matrix);
// 		return;
// 	}
// 	if(mxIsClass(matrix,"uint16"))
// 	{
// 		image.LoadMatlabImage<unsigned short int>(matrix);
// 		return;
// 	}
// 	if(mxIsClass(matrix,"double"))
// 	{
// 		image.LoadMatlabImage<double>(matrix);
// 		return;
// 	}
// 	mexErrMsgTxt("Unknown type of the image!");
// }

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	DImage Im1,Im2;
    Im1.LoadMatlabImage(prhs[0]);
    Im2.LoadMatlabImage(prhs[1]);
		double* para=(double *)mxGetData(prhs[2]);
	
	// get the parameters
	double alpha= para[0];
	double ratio=para[1];
	int minWidth= para[2];
	int nOuterFPIterations =para[3];
	int nInnerFPIterations =para[4];
	int nSORIterations= para[5];
		
	DImage vx,vy,warpI2;
	OpticalFlow::Coarse2FineFlow(vx,vy,warpI2,Im1,Im2,alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations);

	// output the parameters
	if(nlhs==2){
	vx.OutputToMatlab(plhs[0]);
	vy.OutputToMatlab(plhs[1]);
	}else{
	warpI2.OutputToMatlab(plhs[0]);
	}
}
