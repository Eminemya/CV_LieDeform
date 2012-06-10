#include <mex.h>

double pixel_distance (int A_x,int A_y, int num ,int B_x, int B_y, int A_x_size,int A_y_size, int B_x_size,int B_y_size,double *img1, double *img2, double *img3, double *img4){

double dist=0,temp_h,temp_v;
int x,y,p1,p2;
  for(x=-1;x<=1;x++)
		for(y=-1;y<=1;y++)
		  {
		    if((A_x + x)>=0 && (A_y + y)>=0 && (A_x + x)<A_x_size && (A_y + y)<A_y_size 
		       && (B_x + x)>=0 && (B_y + y)>=0 && (B_x + x)<B_x_size && (B_y + y)<B_y_size)
		      {
                        p1=  ((A_y + y) * A_x_size) + (A_x + x);
                        p2= ((B_y + y) * B_x_size) + (B_x +num*B_x_size*B_y_size+ x);
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
int row1, col1,row2, col2;

/*1) Read */
/*test :Sobel Av,Ah*/
img1= mxGetPr(prhs[0]);
img2= mxGetPr(prhs[1]);

/*train: Sobel Bv,Bh*/
img3= mxGetPr(prhs[2]);
img4= mxGetPr(prhs[3]);
row1= mxGetN(prhs[2]);

/*2) IDM Algo*/
  double dis =0 ;
  double best_dis,*z;
  double temp;
  int x,y,xx,yy,zz,ww=30;

  int warprange=3;
/* 3) Return distance */
plhs[0] =mxCreateDoubleMatrix(1,3, mxREAL);
z = mxGetPr(plhs[0]);
z[0]=DBL_MAX;z[1]=DBL_MAX;z[2]=DBL_MAX;
for(zz=0;zz<row1;zz++){
    dis=0;
    /*for each training img*/
    for (y = 0; y <ww; y++){
      for (x = 0; x <ww; x++)
        {
          best_dis=DBL_MAX;
          for(xx=x-warprange;xx<=x+warprange;xx++){
            for(yy=y-warprange;yy<=y+warprange;yy++){
              if(xx >= 0 && yy >= 0 && xx < ww && yy < ww){
                temp=pixel_distance (x, y, zz,xx, yy, ww,ww,ww,ww,img1, img2, img3, img4);
                if(temp<best_dis)
                {
                  best_dis = temp;
                  /*printf("add %d,%f\n",x,best_dis);*/
                }
              }
           }
          }  
          dis += best_dis;
     /*printf("xx %d,%f\n",x,dis);*/
        }
     /*printf("%d,%f\n",y,dis); */
      }
/*printf("%d,%f\n",zz,dis);
printf("%d,%f,%f,%f\n",zz,z[0],z[1],z[2]);*/
   if(dis<z[0]){
     z[2]=z[1];
     z[1]=z[0];
     z[0]=dis;     
    }else if(dis<z[1]){
     z[2]=z[1];
     z[1]=dis;
    }else if(dis<z[2]){
     z[2]=dis;
    }
    
}

return;

}

