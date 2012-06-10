% saveSeries
%    saveSeries(fname,ser)
%g
% All ims will we saved as unsigned 8-bit integers from 0-255.
% The input series are assumed to be in the range:
%  0 <= x < 256.0.
% 
% The disk representation will be only the integer part of the
% representation. That is, and value between 25.0 and 25.99999 will
% be represented as a 25. Thus, the floor operator is used.
%
% When re-loaded the images will have a .5 added to each pixel so
% as to approximate the original pre-truncated value as well as
% possible.
function saveSeries(fname,ser)

[imHeight,imWidth,ims]=size(ser);

imsPerRow=ceil(sqrt(ims)-.000001);

pixPerRow=imsPerRow*imWidth;
pixPerCol=imsPerRow*imHeight;

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

b=bigIm';
ubigIm=floor(b(:));

fid=fopen(fname,'w');

fprintf(fid,'P5\n');
fprintf(fid,'# %d %d %d\n',imWidth,imHeight,ims);
fprintf(fid,'%d %d\n',pixPerRow,pixPerCol);
fprintf(fid,'255\n');
fwrite(fid,ubigIm,'uchar');
fclose(fid);
