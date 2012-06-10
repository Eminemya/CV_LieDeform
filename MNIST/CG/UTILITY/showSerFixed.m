function showSerFixed(ser,figNum,low,high)

figure(figNum);

row=ceil(sqrt(size(ser,3))-.000001);
for i=1:size(ser,3)
  subplot(row,row,i);
  imagesc(ser(:,:,i),[low high]);
  colormap('gray');
end

drawnow;