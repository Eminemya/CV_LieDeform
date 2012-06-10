#include <mex.h>
#include <math.h>


double pixel_distance (int A_x,int A_y, int nA ,int nB ,int B_x, int B_y, int A_x_size,int A_y_size, int B_x_size,int B_y_size,double *img1, double *img2){
double dist=0,temp_h,temp_v;
int x,y,p1,p2;
  for(x=-1;x<=1;x++){
		for(y=-1;y<=1;y++)
		  {
		    /*if((A_x + x)>=0 && (A_y + y)>=0 && (A_x + x)<A_x_size && (A_y + y)<A_y_size && (B_x + x)>=0 && (B_y + y)>=0 && (B_x + x)<B_x_size && (B_y + y)<B_y_size){*/
            p1=  ((A_y + y) * A_x_size) + (A_x+nA*A_x_size*A_y_size + x);
           p2= ((B_y + y) * B_x_size) + (B_x +nB*B_x_size*B_y_size+ x);
			temp_h =img1[p1] - img2[p2];
			/*temp_v =img2[p1] - img4[p2];*/
/*printf("h%f,%f,%d,%d,%d,%d\n",img1[((A_y + y) * A_x_size) + (A_x + x)],img3[((B_y + y) * B_x_size) + (B_x + x)],((A_y + y) * A_x_size) + (A_x + x),((B_y + y) * B_x_size) + (B_x + x),A_x,B_x);*/
  	/*dist+=fabs(temp_h);*/
   dist+=temp_h*temp_h;
		      /*}*/
          }
		  }
return dist;
}
double pixel_norm (int A_x,int A_y, int nA ,int A_x_size,int A_y_size, double *img1){
double dist=0;
int x,y,p1;
  for(x=-1;x<=1;x++){
		for(y=-1;y<=1;y++)
		  {
            p1=  ((A_y + y) * A_x_size) + (A_x+nA*A_x_size*A_y_size + x);
         	dist+=img1[p1]*img1[p1];
         	/*dist+=fabs(img1[p1]);*/
		  }
        }
return dist;
}
void mexFunction(int nlhs, mxArray *plhs[], int nrhs,
const mxArray *prhs[])
{

double *img1,*img2;
int row1, row2,col1,col2;

/*1) Read */
/*test : 0th pixel A*/
row1= mxGetN(prhs[0]);
col1= mxGetM(prhs[0]);
col2= mxGetM(prhs[1]);

img1= mxGetPr(prhs[0]);
/*train: 0th pixel B*/
if(col2==1){
img2= img1;
row2= row1;
}else{
img2= mxGetPr(prhs[1]);
row2= mxGetN(prhs[1]);
}

/*2) IDM Algo*/
  double dis ,dis2,norm,norm2 ;
  double best_dis,best_dis2,*z;
  double temp,temp2;
  int x,y,xx,yy,z1,z2,ww=(int)sqrt(col1);

  int warprange=2;
/* 3) Return distance */
plhs[0] =mxCreateDoubleMatrix(row2,row1, mxREAL);
z = mxGetPr(plhs[0]);
/*printf("add %d,%d,%d,%d,%d,%d\n",row1,row2,mxGetM(prhs[0]),mxGetM(prhs[1]),mxGetN(prhs[0]),mxGetN(prhs[1]));*/

for(z1=0;z1<row1;z1++){
for(z2=0;z2<row2;z2++){    
   /* printf("add %d,%d,%d,%d,%d,%d\n",z1,z2,row1,row2,mxGetM(prhs[0]),mxGetM(prhs[1]));*/
   if(col2!=1||z1<z2){
    dis=0;dis2=0;norm=0;norm2=0;
    /*for each training img*/
    for (y = 1; y <ww; y+=3){
      for (x = 1; x <ww; x+=3)
        {
          best_dis=DBL_MAX;
          best_dis2=DBL_MAX;
          norm+=pixel_norm(x, y, z1, ww,ww,img1);
          norm2+=pixel_norm(x, y, z2, ww,ww,img2);
          for(xx=x-warprange;xx<=x+warprange;xx++){
            for(yy=y-warprange;yy<=y+warprange;yy++){
             /* garuantee 3*3 patch*/
              if(xx >= 1 && yy >= 1 && xx < ww-1 && yy < ww-1){
                 /*printf("wwww %d,%d\n",xx,yy,ww);*/
                temp=pixel_distance (x, y, z1,z2,xx, yy, ww,ww,ww,ww,img1, img2);
                temp2=pixel_distance (x, y, z2,z1,xx, yy, ww,ww,ww,ww,img2, img1);
                if(temp<best_dis)
                {
                  best_dis = temp;
                }
                if(temp2<best_dis2)
                {
                  best_dis2 = temp2;
                }
              }
           }
           if(best_dis==0 && best_dis2==0){break;}
          }  
          dis += best_dis;
          dis2 += best_dis2;
          /*printf("%d,%d,%f,%f,%f,%f,%f,%f\n",x,y,norm,norm2,dis,dis2,best_dis,best_dis2);*/
        }
      }
    /*take the mean, making it symmetric*/
    dis=dis/norm;
    dis2=dis2/norm2;
    z[z2+z1*row2]=dis<dis2?dis:dis2;
    }
}
}

return;

}

