#include <mex.h>
#include <math.h>

double pixel_distance (int A_x,int A_y, int nA ,int nB ,int B_x, int B_y, int A_x_size,int A_y_size, int B_x_size,int B_y_size,double *img1, double *img2){

double dist=0,temp_h,temp_v;
int x,y,p1,p2;
  for(x=-2;x<=1;x++)
		for(y=-2;y<=1;y++)
		  {
		   /* if((A_x + x)>=0 && (A_y + y)>=0 && (A_x + x)<A_x_size && (A_y + y)<A_y_size&& (B_x + x)>=0 && (B_y + y)>=0 && (B_x + x)<B_x_size && (B_y + y)<B_y_size){*/
            p1 =  ((A_y + y) * A_x_size) + (A_x+nA*A_x_size*A_y_size + x);
            p2 = ((B_y + y) * B_x_size) + (B_x +nB*B_x_size*B_y_size+ x);
			temp_h = img1[p1] - img2[p2];
			/*temp_v =img2[p1] - img4[p2];*/
/*printf("h%f,%f,%d,%d,%d,%d\n",img1[((A_y + y) * A_x_size) + (A_x + x)],img3[((B_y + y) * B_x_size) + (B_x + x)],((A_y + y) * A_x_size) + (A_x + x),((B_y + y) * B_x_size) + (B_x + x),A_x,B_x);*/
         	dist+=temp_h*temp_h;
		/*}*/
		  }

return dist;
}

void mexFunction(int nlhs, mxArray *plhs[], int nrhs,
const mxArray *prhs[])
{

double *img1,*img2,*img3,*img4;
int row1, row2,col;

/*1) Read */
/*test : 0th pixel A*/
img1= mxGetPr(prhs[0]);
/*train: 0th pixel B*/
img2= mxGetPr(prhs[1]);
row1= mxGetN(prhs[0]);
col= mxGetM(prhs[0]);
row2= mxGetN(prhs[1]);

/*2) IDM Algo*/
  double dis =0 ;
  double best_dis,*z;
  double temp;
  int x,y,xx,yy,z1,z2,ww=(int)sqrt(col);

  int warprange=2;
/* 3) Return distance */
plhs[0] =mxCreateDoubleMatrix(row2,row1, mxREAL);
z = mxGetPr(plhs[0]);

for(z1=0;z1<row1;z1++){
for(z2=0;z2<row2;z2++){    

    /*printf("add %d,%d,%d,%d,%d,%d\n",z1,z2,row1,row2,mxGetM(prhs[0]),mxGetM(prhs[1]));*/
    dis=0;
    /*for each training img*/
    for (y = 2; y <ww-1; y+=4){
      for (x = 2; x <ww-1; x+=4)
        {
          best_dis=DBL_MAX;
          for(xx=x-warprange;xx<=x+warprange;xx++){
            for(yy=y-warprange;yy<=y+warprange;yy++){
             /* garuantee 3*3 patch*/
              if(xx >= 2 && yy >= 2 && xx < ww-1 && yy < ww-1){
                 /*printf("wwww %d,%d\n",xx,yy,ww);*/
                temp=pixel_distance (x, y, z1,z2,xx, yy, ww,ww,ww,ww,img1, img2);
                if(temp<best_dis)
                {
                  best_dis = temp;
                }
              }
           }
           if(best_dis==0){break;}
          }  
          dis += best_dis;
        }
      }
    z[z2+z1*row2]=dis;
    }
    }

return;

}

