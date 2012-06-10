function y=b_dist(im1,im2)

im2(im2<100)=0;
im1(im1<100)=0;

im2(im2>0)=1;
im1(im1>0)=1;
%y=sum((double(im2(:))-double(im1(:))).^2)
y=IDM7(double(im1(:)),double(im2(:)));

end
