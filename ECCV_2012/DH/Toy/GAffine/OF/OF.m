load ../data/45_dis6
addpath('mex');

% load the two frames

src = reshape(strain(1,:),21,21);
tar = reshape(strain(100,:),21,21);

% set optical flow parameters (see Coarse2FineTwoFrames.m for the definition of the parameters)
alpha = 0.05;
ratio = 0.5;
minWidth = 10;
nOuterFPIterations = 7;
nInnerFPIterations = 1;
nSORIterations = 30;

para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];

[vx,vy,warpI2] = Coarse2FineTwoFrames(src,tar,para);

figure;subplot(1,3,1);imagesc(src');subplot(1,3,2);imagesc(warpI2');subplot(1,3,3);imagesc(tar');
%{%}
