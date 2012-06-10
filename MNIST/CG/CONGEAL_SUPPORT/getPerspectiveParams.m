function [xfrm,k,l,m]=getPerspectiveParams(transVec)

len=length(transVec);

xmat=eye(3);
ymat=eye(3);
rotMat=eye(3);
xScaleMat=eye(3);
yScaleMat=eye(3);
xShearMat=eye(3);
yShearMat=eye(3);

xmat(1,3)=transVec(1)*1;
ymat(2,3)=transVec(2)*1;

theta=transVec(3)*1/60;
rotMat(1:2,1:2)=[cos(theta) -sin(theta); sin(theta) cos(theta)];

xScaleMat(1,1)=exp(0.05*transVec(4));
yScaleMat(2,2)=exp(0.05*transVec(5));

xShearMat(1,2)=0.05*transVec(6);
yShearMat(2,1)=0.05*transVec(7);

xfrm=yShearMat*xShearMat*yScaleMat*xScaleMat*rotMat*ymat*xmat;

k=1;
l=transVec(8)/1000;
m=transVec(9)/1000;
