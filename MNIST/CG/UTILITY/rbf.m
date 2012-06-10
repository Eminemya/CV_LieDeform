function mean_likelihood=rbf(trainXfrms,testXfrm)

variance=.1;

numTrain=size(trainXfrms,3);

testXfrm(3,:)=[0 0 1];
invTest=testXfrm^-1;

% Add the row "0 0 1" to the end of every affine matrix so
% that we can multiply it by another affine matrix.
trainXfrms(3,:,:)=repmat([0 0 1],[1,1,numTrain]);

diffTrans=zeros(2,3,numTrain);

adjustMat=[1 .3 10; 1 .3 10; 1 1 1];

for i=1:numTrain
  prod=(trainXfrms(:,:,i)*invTest-eye(3))./adjustMat;
  
  diffTrans(:,:,i)=prod(1:2,1:3);
end

dif=reshape(diffTrans,[6,numTrain]);
vars=dot(dif,dif)/(2*variance);

mean_likelihood=sum(exp(-vars)/sqrt(variance^6))/numTrain;
