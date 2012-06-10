function showSerFixedTightRowCol(ser,figNum,low,high,rows,cols)

figure(figNum);
clf;
imsPerRow=cols;
imsPerCol=rows;
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