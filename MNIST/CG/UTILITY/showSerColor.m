function showSerColor(ser,figNum)

figure(figNum);
clf;

row=ceil(sqrt(size(ser,4))-.000001);
for i=1:size(ser,4)
  subplot(row,row,i);
  imagesc(ser(:,:,:,i));
end

drawnow;