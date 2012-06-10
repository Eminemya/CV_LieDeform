im_fname='/home/vis3/data/emiller/MNIST/t10k-images-idx3-ubyte';
label_fname='/home/vis3/data/emiller/MNIST/t10k-labels-idx1-ubyte';
%im_fname='/home/vis3/data/emiller/MNIST/train-images-idx3-ubyte';
%label_fname='/home/vis3/data/emiller/MNIST/train-labels-idx1-ubyte';

sers=zeros(28,28,1000,10);

lfid=fopen(label_fname,'r','ieee-be');
magic=fread(lfid,1,'int32');
magic

count=fread(lfid,1,'int32');
count

fid=fopen(im_fname,'r','ieee-be');
magic=fread(fid,1,'int32');
magic

count=fread(fid,1,'int32');
count
xs=fread(fid,1,'int32');
xs
ys=fread(fid,1,'int32');
ys

curInd=ones(10,1);
for i=1:10000
  i
  im=(fread(fid,[28,28],'uchar'))';
  label=fread(lfid,1,'uchar');
  sers(:,:,curInd(label+1),label+1)=im;
  curInd(label+1)=curInd(label+1)+1;
end


addpath /home/vis3/data/emiller/NIST/matlab/IO;
for i=1:10
  outfname=sprintf('/home/vis3/data/emiller/MNIST/pgm/test_%d.pgm',i-1);
  s=sers(:,:,1:curInd(label+1)-1,i);
  saveSeries(outfname,s);
end


fclose(lfid);
fclose(fid);

  

