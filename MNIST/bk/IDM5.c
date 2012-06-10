#include <mex.h>
#include <math.h>

double pixel_distance (int A_x,int A_y, int nA ,int nB ,int B_x, int B_y, int A_x_size,int A_y_size, int B_x_size,int B_y_size,double *img1, double *img2, double *img3, double *img4){

double dist=0,temp_h,temp_v;
int x,y,p1,p2;
  for(x=-1;x<=1;x++)
		for(y=-1;y<=1;y++)
		  {
		    if((A_x + x)>=0 && (A_y + y)>=0 && (A_x + x)<A_x_size && (A_y + y)<A_y_size 
		       && (B_x + x)>=0 && (B_y + y)>=0 && (B_x + x)<B_x_size && (B_y + y)<B_y_size)
		      {
                        p1=  ((A_y + y) * A_x_size) + (A_x+nA*A_x_size*A_y_size + x);
                        p2= ((B_y + y) * B_x_size) + (B_x +nB*B_x_size*B_y_size+ x);
			temp_h =img1[p1] - img3[p2];
			temp_v =img2[p1] - img4[p2];
/*printf("h%f,%f,%d,%d,%d,%d\n",img1[((A_y + y) * A_x_size) + (A_x + x)],img3[((B_y + y) * B_x_size) + (B_x + x)],((A_y + y) * A_x_size) + (A_x + x),((B_y + y) * B_x_size) + (B_x + x),A_x,B_x);*/
 
 	dist+=temp_h*temp_h+temp_v*temp_v;

		      }
		  }

return dist;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs,
const mxArray *prhs[])
{

double *img1,*img2,*img3,*img4;
int row1, row2,col;

/*1) Read */
/*test :Sobel Av,Ah*/
img1= mxGetPr(prhs[0]);
img2= mxGetPr(prhs[1]);
row1= mxGetN(prhs[0]);
/*train: Sobel Bv,Bh*/
img3= mxGetPr(prhs[2]);
img4= mxGetPr(prhs[3]);
row2= mxGetN(prhs[2]);
col= mxGetM(prhs[2]);
/*2) IDM Algo*/
  double dis =0 ;
  double best_dis,*z;
  double temp;
  int x,y,xx,yy,z1,z2,ww=(int)sqrt((float)col);

  int warprange=2;
/* 3) Return distance */
plhs[0] =mxCreateDoubleMatrix(row2,row1, mxREAL);
z = mxGetPr(plhs[0]);

for(z1=0;z1<row1;z1++){
for(z2=0;z2<row2;z2++){    
    dis=0;
    /*for each test img*/
    for (y = 0; y <ww; y++){
      for (x = 0; x <ww; x++)
        {
          best_dis=DBL_MAX;
          for(xx=x-warprange;xx<=x+warprange;xx++){
            for(yy=y-warprange;yy<=y+warprange;yy++){
              if(xx >= 0 && yy >= 0 && xx < ww && yy < ww){
                temp=pixel_distance (x, y, z1,z2,xx, yy, ww,ww,ww,ww,img1, img2, img3, img4);
                if(temp<best_dis)
                {
                  best_dis = temp;
                  /*printf("add %d,%f\n",x,best_dis);*/
                }
              }
           }
           if(best_dis==0){break;}
          }  
          dis += best_dis;
/*         printf("add %d,%d,%f\n",x,y,best_dis);*/
        }          
      }
      z[z2+z1*row2]=dis;
    }
}

return;

}

