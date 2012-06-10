function adjImg=computeXfrmImgNear(img,transVec)

persistent oldx oldy;
persistent xorg yorg orgCoords;

xfrm=getXfrm(transVec);
  
[y,x]=size(img);

if isempty(oldx) | y~=oldy | x~=oldx
  fprintf(1,'Making coord entries.\n');
  xorg=repmat(-(x/2-0.5):1:x/2-0.5,[y 1]);
  yorg=repmat((-(y/2-0.5):1:y/2-0.5)',[1 x]);
  orgCoords=[xorg(:)'; yorg(:)'; ones(1,x*y)];
end

newCoords=xfrm*orgCoords;
xnew=reshape(newCoords(1,:),y,x);
ynew=reshape(newCoords(2,:),y,x);
adjImg=interp2(xorg,yorg,img,xnew,ynew,'nearest');

adjImg(isnan(adjImg))=0;
  
oldy=y;
oldx=x;
