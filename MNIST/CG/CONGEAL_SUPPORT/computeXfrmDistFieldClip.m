function xfrmDF=computeXfrmDistFieldClip(df,transVec,cutout)

persistent oldx oldy;
persistent xorg yorg orgCoords;

xfrm=getXfrm(transVec);
  
[y,x,z]=size(df);

if isempty(oldx) | y~=oldy | x~=oldx
  fprintf(1,'Making coord entries.\n');
  xorg=repmat(-(x/2-0.5):1:x/2-0.5,[y 1]);
  yorg=repmat((-(y/2-0.5):1:y/2-0.5)',[1 x]);
  orgCoords=[xorg(:)'; yorg(:)'; ones(1,x*y)];
end

newCoords=xfrm*orgCoords;
xnew=reshape(newCoords(1,:),y,x);
ynew=reshape(newCoords(2,:),y,x);

rows=y;
cols=x;
rowst=floor((.5-cutout/2)*rows)+1;
rowend=ceil((.5+cutout/2)*rows);
colst=floor((.5-cutout/2)*cols)+1;
colend=ceil((.5+cutout/2)*cols);

for i=1:z
  xfrmDF(:,:,i)=interp2(xorg,yorg,df(:,:,i),xnew(rowst:rowend,colst:colend),ynew(rowst:rowend,colst:colend),'nearest');
end
xfrmDF(isnan(xfrmDF))=rand;
  
oldy=y;
oldx=x;
