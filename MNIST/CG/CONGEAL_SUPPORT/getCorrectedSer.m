function corSer=getCorrectedSer(ser,b,transVecs)

corSer=zeros(size(ser));
[rows,cols,imgCount]=size(ser);

for i=1:imgCount
  corSer(:,:,i)=getCorrectedIm(b,ser(:,:,i),transVecs(i,:));
end
