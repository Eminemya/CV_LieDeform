load mnist_all
addpath('mex');

% load the two frames
 im1 = double(reshape(train5(1,:),28,28))/255;
 im2 = double(reshape(train5(500,:),28,28))/255;

src = test_image('sin', 0, 0, 0);
tar = test_image('sin', 0, 0, 0.3);

% set optical flow parameters (see Coarse2FineTwoFrames.m for the definition of the parameters)
alpha = 0.01;
ratio = 0.5;
minWidth = 10;
nOuterFPIterations = 7;
nInnerFPIterations = 1;
nSORIterations = 30;

para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];


src = reshape(strain(1,:),21,21);
tar = reshape(strain(100,:),21,21);
[tmp,vx,vy] = Coarse2FineTwoFrames(src, tar,para);

figure;
imshow(overlain2(src, tar));
hold on;
hss(src,vx(:),vy(:),1);





