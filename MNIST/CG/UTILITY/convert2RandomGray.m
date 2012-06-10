addpath IO
binaryIms=loadSeries('/home/vis3/data/emiller/NIST/pgm/train_30_shuf.pbm',0,1000);

for i=1:1001
  imi=binaryIms(:,:,i);
  imi(imi==0.5)=floor(rand*255.9999999);
  imi(imi==255.5)=floor(rand*255.9999999);
  
  binaryIms(:,:,i)=imi;
  
end


  
saveSeries('/home/vis3/data/emiller/NIST/pgm/grayTrain0.pgm',binaryIms);

  
