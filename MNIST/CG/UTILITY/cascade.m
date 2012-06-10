function bigIm=cascade(ser,percentOff,colmap,minval,maxval)

[y,x,cnt]=size(ser);

xskip=floor(percentOff*x);
yskip=floor(percentOff*y);

bigSizeX=x+(cnt-1)*xskip;
bigSizeY=y+(cnt-1)*yskip;

bigIm=zeros(y,x,3);

xst=1;
yst=1;


for i=1:cnt
  colim=convert24fixed(ser(:,:,i),colmap,minval,maxval);
  colim=add_border_24(colim,[1 1 1]');
  colim=add_box_24(colim,[0 0 0]',[15 20 70 75]);
  colim=add_box_24(colim,[1 1 1]',[13 22 68 77]);
  bigIm(yst:yst+y-1,xst:xst+x-1,:)=colim;
  xst=xst+xskip;
  yst=yst+yskip;
end
