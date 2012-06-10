function xfrm=getXfrmForeshorten(transVec)

len=length(transVec);

xmat=eye(3);
ymat=eye(3);
rotMatx=eye(3);
rotMaty=eye(3);
rotMatz=eye(3);

xmat(1,3)=transVec(1)*1;
ymat(2,3)=transVec(2)*1;

transVec(3)=transVec(3)/60;
transVec(4)=transVec(3)/60;
transVec(5)=transVec(3)/60;

rotMatx(2,2)=cos(transVec(3));
rotMatx(3,3)=cos(transVec(3));
rotMatx(2,3)=-sin(transVec(3));
rotMatx(3,2)=sin(transVec(3));

rotMaty(1,1)=cos(transVec(4));
rotMaty(3,3)=cos(transVec(4));
rotMaty(1,3)=-sin(transVec(4));
rotMaty(3,1)=sin(transVec(4));

rotMatz(1,1)=cos(transVec(5));
rotMatz(2,2)=cos(transVec(5));
rotMatz(1,2)=-sin(transVec(5));
rotMatz(2,1)=sin(transVec(5));

totalRot=rotMatz*rotMaty*rotMatx;
xy=[1 0; 0 1; 0 0];

rotatedPatch=totalRot*xy;
forwardMapping=rotatedPatch(1:2,1:2);
backwardMapping=forwardMapping^(-1);

backwardMapping(1,3)=transVec(1)*1;
backwardMapping(2,3)=transVec(2)*1;
backwardMapping(3,:)=[0 0 1];

xfrm=backwardMapping;