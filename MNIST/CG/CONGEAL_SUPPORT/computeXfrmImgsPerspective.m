function adjSer=computeXfrmImgsPerspective(ser,transVecs)

n=size(ser,3);

for i=1:n
  adjSer(:,:,i)=computeXfrmImgPerspective(ser(:,:,i),transVecs(i,:));
end

 