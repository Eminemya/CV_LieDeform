function showSerColorTight(ser,figNum,rowCount)

figure(figNum);
clf;

row=ceil(sqrt(size(ser,4))-.000001);
if exist('rowCount')
  row=rowCount;
  colCount=ceil(size(ser,4)/rowCount);
end

margin=1/(row*10+(row+1));
spacePerRow=11*margin;


for i=1:size(ser,4)
  curRow=ceil(i/row)-1;
  curCol=mod(i-1,row);
  top=1-(curRow*spacePerRow+margin);
  bot=1-((curRow+1)*spacePerRow);
  left=curCol*spacePerRow+margin;
  right=(curCol+1)*spacePerRow;
  subplot('position',[left,bot,right-left,top-bot]);
  imagesc(ser(:,:,:,i));
  axis off;
end

drawnow;

