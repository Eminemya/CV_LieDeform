% This function returns (and displays) an rgb image which remaps 
% the positive values of a grayscale image to the green channel
% and the negative values to the red channel.  This is useful
% when you are interesting in differences from zero and are 
% concerned with positive and negative values.
% 
% Usage:
%
%   rgbim=showPosNeg(grayim);
%
function imfull=showPosNeg(im,display);

if nargin < 2
  display=1;
end;

im1=max(im,0);
im2=max(-im,0);
im3=zeros(size(im1));

gamma=.25;
imfull=zeros(size(im1,1),size(im1,2),3);
imfull(:,:,1)=im2.^gamma;
imfull(:,:,2)=im1.^gamma;
imfull(:,:,3)=im3; %.^gamma;

imfull=imfull/max(imfull(:));

if (display)
  imagesc(imfull);
end;
