function select_MR_slices(output_fname)

d=dir('/egmil/medical/Harvard/aligned');
sz=length(d)-2;

j=1;
for i=1:sz
  if strcmp(d(i).name,'.')==0 & strcmp(d(i).name,'..')==0
    s=sprintf('/egmil/medical/Harvard/aligned/%s/spgr/I.060',d(i).name);
    MR_ser(:,:,j)=load_MR_raw(s);
    j=j+1;
  end
end

cnt=size(MR_ser,3);
for i=1:cnt
  MR_ser(:,:,i)=MR_ser(:,:,i)/max(max(MR_ser(:,:,i)));
end

cmd=sprintf('save %s MR_ser',output_fname);
eval(cmd);

