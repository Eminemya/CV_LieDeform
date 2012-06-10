function adjImg=computeXfrmImgPerspective(img,transVec)

persistent oldx oldy;
persistent xorg yorg orgCoords;
persistent xorgrow yorgrow
[xfrm,k,l,m]=getPerspectiveParams(transVec);
[x,y]=size(img);
  
if isempty(oldx) | y~=oldy | x~=oldx
  fprintf(1,'Making coord entries.\n');
  xorg=repmat(-(x/2-0.5):1:x/2-0.5,[y 1]);
  yorg=repmat((-(y/2-0.5):1:y/2-0.5)',[1 x]);
  xorgrow=xorg(:)';
  yorgrow=yorg(:)';
  orgCoords=[xorgrow; yorgrow; ones(1,x*y)];
end

newCoords=xfrm*orgCoords;
newCoords(1,:)=newCoords(1,:)./(k+l*xorgrow+m*yorgrow);
newCoords(2,:)=newCoords(2,:)./(k+l*xorgrow+m*yorgrow);

xnew=reshape(newCoords(1,:),x,y);
ynew=reshape(newCoords(2,:),x,y);
adjImg=interp2(xorg,yorg,img,xnew,ynew);

adjImg(isnan(adjImg))=0;
  
oldy=y;
oldx=x;