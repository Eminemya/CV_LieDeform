function bigIm=ser2Im(ser)

[imHeight,imWidth,ims]=size(ser);

imsPerRow=ceil(sqrt(ims)-.000001);

pixPerRow=imsPerRow*imHeight;
pixPerCol=imsPerRow*imWidth;

bigIm=zeros(pixPerRow,pixPerCol);

curIm=1;
for i=1:imsPerRow   % Indexes the row
  for j=1:imsPerRow % Indexes the col.
    bigIm( (i-1)*imHeight+1:i*imHeight,(j-1)*imWidth+1:j*imWidth)=ser(:,:,curIm);
    curIm=curIm+1;
    if curIm>ims;
      break;
    end
  end
  if curIm>ims;
    break;
  end
end


