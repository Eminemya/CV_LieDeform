function corImg=getCorrectedIm(b,img,transVec)

bias=zeros(size(b,1),size(b,2));
for i=1:length(transVec)
  bias=bias+transVec(i)*b(:,:,i);
end

corImg=bias.*img;


