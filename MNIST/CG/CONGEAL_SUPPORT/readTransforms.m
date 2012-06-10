function xfrms=readTransforms(fname,sz)

fid=fopen(fname,'r');
for i=1:sz
  transposed=fscanf(fid,'%f',[3 2]);
  xfrms(:,:,i)=transposed';
end

fclose(fid);

  