#include <mex.h>

double pixel_distance (int A_x,int A_y, int B_x, int B_y, int A_x_size,int A_y_size, int B_x_size,int B_y_size,double *img1, double *img2, double *img3, double *img4){

double dist=0,temp_h,temp_v;
int x,y;
  for(x=-1;x<=1;x++)
		for(y=-1;y<=1;y++)
		  {
		    if((A_x + x)>=0 && (A_y + y)>=0 && (A_x + x)<A_x_size && (A_y + y)<A_y_size 
		       && (B_x + x)>=0 && (B_y + y)>=0 && (B_x + x)<B_x_size && (B_y + y)<B_y_size)
		      {
			temp_h =img1[((A_y + y) * A_x_size) + (A_x + x)] -
			  img3[((B_y + y) * B_x_size) + (B_x + x)];
			temp_v =img2[((A_y + y) * A_x_size) + (A_x + x)] -
			  img4[((B_y + y) * B_x_size) + (B_x + x)];
/*
if(A_x==0&&A_y==9){
printf("h%f,%f,%d,%d,%d,%d\n",img1[((A_y + y) * A_x_size) + (A_x + x)],img3[((B_y + y) * B_x_size) + (B_x + x)],((A_y + y) * A_x_size) + (A_x + x),((B_y + y) * B_x_size) + (B_x + x),A_x,B_x);
}*/
 
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
col1= mxGetN(prhs[0]);
row1= mxGetM(prhs[0]);

/*train: Sobel Bv,Bh*/
img3= mxGetPr(prhs[2]);
img4= mxGetPr(prhs[3]);
col2= mxGetN(prhs[2]);
row2= mxGetM(prhs[2]);

/*2) IDM Algo*/
  double dis = 0;
  double best_dis;
  double temp;
  int x,y,xx,yy,B_x,B_y;
  int warprange=3;
  if(row1==row2 && col1==col2){
    for (y = 0; y < col1; y++){
      for (x = 0; x <row1; x++)
        {
          best_dis=DBL_MAX;
          for(xx=x-warprange;xx<=x+warprange;xx++){
            for(yy=y-warprange;yy<=y+warprange;yy++){
              if(xx >= 0 && yy >= 0 && xx < row1 && yy < col1){
                temp=pixel_distance (x, y, xx, yy, row1,col1,row2,col2,img1, img2, img3, img4);
                if(temp<best_dis)
                {
                  best_dis = temp;
                  /*printf("add %d,%f\n",x,best_dis);*/
                }
              }
           }
          }  
          dis += best_dis;
/* printf("xx %d,%f\n",x,dis);*/
        }
/* printf("%d,%f\n",y,dis);*/
  
      }
    }else{
    for (y = 0; y < col1; y++){
      for (x = 0; x < row1; x++)
        {
          best_dis=10000;

          B_x=(int) ((double)((row2-1)*x)/(double)(row1-1)+0.5);
          B_y=(int) ((double)((col2-1)*y)/(double)(col1-1)+0.5);

          for(xx=B_x-warprange;xx<=B_x+warprange;xx++)
            for(yy=B_y-warprange;yy<=B_y+warprange;yy++)
              {
                if(xx >= 0 && yy >= 0 && xx < row2 && yy < col2
                   && ((temp=pixel_distance (x, y, xx, yy, row1,col1,row2,col2, img1, img2, img3, img4))<best_dis
                       || (temp==best_dis && xx==B_x && yy==B_y)))
                  {
                    best_dis = temp;
                  }
              }
          dis += best_dis;          
        }
     }

    }
/* 3) Return distance */
plhs[0] =mxCreateDoubleScalar(dis);

return;

}

