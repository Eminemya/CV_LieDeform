function writeTransforms(fname,transVecs)

fid=fopen(fname,'w');
for i=1:size(transVecs,1)
  t=getXfrm(transVecs(i,:));
  fprintf(fid,'%6.2f ',t(1,1));
  fprintf(fid,'%6.2f ',t(1,2));
  fprintf(fid,'%6.2f ',t(1,3));
  fprintf(fid,'%6.2f ',t(2,1));
  fprintf(fid,'%6.2f ',t(2,2));
  fprintf(fid,'%6.2f ',t(2,3));
  fprintf(fid,'\n');
end
fclose(fid);

  