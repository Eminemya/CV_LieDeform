% 1 check warping local flow
alpha = 0.05;
ratio = 0.5;
minWidth = 7;
nOuterFPIterations = 10;
nInnerFPIterations = 3;
nSORIterations = 30;
para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];

src=double(reshape(train5(1,:),28,28)/255);
tar=double(reshape(train5(100,:),28,28)/255);

tmp = Coarse2FineTwoFrames(tar,src,para);
figure;subplot(1,3,1);imagesc(src');subplot(1,3,2);imagesc(tmp');subplot(1,3,3);imagesc(tar');




load mnist
for i=0:9
eval(['load km' num2str(i)])
eval(['load km' num2str(i)])
 center=zeros(1,100);
	for j=1:100
[~, center(j)] = min( sum((bsxfun(@minus,train,c(j,:)).^2),2))
	end
end


