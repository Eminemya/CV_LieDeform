alpha = 0.05;
ratio = 0.5;
minWidth = 7;
nOuterFPIterations = 7;
nInnerFPIterations = 1;
nSORIterations = 30;
para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];

p = 0.9;
tol = 1e-2;
maxiter = 1000;
%sum((tmp1(:)-face_r(:,ctrs(seed(j)))).^2)
%sum((tmp1(:)-face_r(:,ctrs(seed(1)))).^2)
src = zeros(20,30);
tar = zeros(20,30);
src(5:15,5:25)=1;
tar(8:18,5:25)=1;
x=20;y=30;
[xorg,yorg]=meshgrid(0.5:1:y-0.5,0.5:1:x-0.5);
[vx,vy] = Coarse2FineTwoFrames( tar, src,para);
%vx=zeros(x,y);
%vy=-3*ones(x,y);
norgx = xorg - vx;
norgy = yorg - vy;
tmp1 = interp2(xorg,yorg,tar,norgx,norgy);
tmp1(isnan(tmp1))=0;

