function showSerFixedTight(ser,figNum,low,high)

figure(figNum);
clf;
imsPerRow=ceil(sqrt(size(ser,3))-.000001);
imsPerCol=ceil(size(ser,3)/imsPerRow);
rowmargin=1/(imsPerRow*10+(imsPerRow+1));
colmargin=1/(imsPerCol*10+(imsPerCol+1));
spacePerRow=11*rowmargin;
spacePerCol=11*colmargin;

for i=1:size(ser,3)
  curRow=ceil(i/imsPerRow)-1;
  curCol=mod(i-1,imsPerRow);
  top=1-(curRow*spacePerCol+colmargin);
  bot=1-((curRow+1)*spacePerCol);
  left=curCol*spacePerRow+rowmargin;
  right=(curCol+1)*spacePerRow;
  subplot('position',[left,bot,right-left,top-bot]);
  imagesc(ser(:,:,i),[low high]);
  axis off;
  colormap('gray');
end

drawnow;