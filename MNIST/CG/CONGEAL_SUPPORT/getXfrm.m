function xfrm=getXfrm(transVec)

len=length(transVec);

xmat=eye(3);
ymat=eye(3);
rotMat=eye(3);
xScaleMat=eye(3);
yScaleMat=eye(3);
xShearMat=eye(3);
yShearMat=eye(3);

if len>=2
  xmat(1,3)=transVec(1)*1;
  ymat(2,3)=transVec(2)*1;
end

if len>=3
  theta=transVec(3)*1/60;
  rotMat(1:2,1:2)=[cos(theta) -sin(theta); sin(theta) cos(theta)];
end

if len>=7
  xScaleMat(1,1)=exp(0.05*transVec(4));
  yScaleMat(2,2)=exp(0.05*transVec(5));
end

if len>=5
  xShearMat(1,2)=0.05*transVec(4);
  yShearMat(2,1)=0.05*transVec(5);
end

if len<=2
  xfrm=ymat*xmat;
  return;
end

if len<=3
  xfrm=rotMat*ymat*xmat;
  return;
end

if len<=5
   %xfrm=yScaleMat*xScaleMat*rotMat*ymat*xmat;
  xfrm=yShearMat*xShearMat*rotMat*ymat*xmat;
  return;
end

if len<=7
  xfrm=yShearMat*xShearMat*yScaleMat*xScaleMat*rotMat*ymat*xmat;
  return;
end

fprintf(1,'Error in getXfrm: shouldnt have gotten here.\n');
