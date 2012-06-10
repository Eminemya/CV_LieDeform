function adjSer=computeXfrmImgs(ser,transVecs)

persistent oldx oldy;
persistent xorg yorg orgCoords;

xfrms=getXfrms(transVecs);
  
[y,x,imgCount]=size(ser);
  
if isempty(oldx) | y~=oldy | x~=oldx
  fprintf(1,'Making coord entries.\n');
  xorg=repmat(-(x/2-0.5):1:x/2-0.5,[y 1]);
  yorg=repmat((-(y/2-0.5):1:y/2-0.5)',[1 x]);
  orgCoords=[xorg(:)';yorg(:)'; ones(1,x*y)];
end

for i=1:imgCount
    newCoords=xfrms(:,:,i)*orgCoords;
    xnew=reshape(newCoords(1,:),y,x);
    ynew=reshape(newCoords(2,:),y,x);
    adjSer(:,:,i)=interp2(xorg,yorg,ser(:,:,i),xnew,ynew);
end
  
adjSer(isnan(adjSer))=0;
  
oldy=y;
oldx=x;
  