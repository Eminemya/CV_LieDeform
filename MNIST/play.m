
load mnist_all



num=2
figure
for i=1:num
subplot(3,num,i)
eval(['a=reshape(train' num2str(i-1) '(1,:),28,28);'])
b=a;
b(b<mean(b(b~=0)))=0;
b(b~=0)=1;

c=bwmorph(b,'skel')
imagesc(c')


c=bwboundaries(b)
imagesc(a)
subplot(3,num,i+num)
%d=curve(c{1}(:,1),c{1}(:,2));
c{1}=[c{1};c{1}(1,:)]
jump=3;
d= LineCurvature2D(c{1}(1:jump:length(c{1})-jump+1-mod(length(c{1}),jump),:))
plot(d)
subplot(3,num,i+2*num)
plot(c{1}(1:jump:length(c{1})-jump+1-mod(length(c{1}),jump),1),c{1}(1:jump:length(c{1})-jump+1-mod(length(c{1}),jump),2))
end







figure;
subplot(2,1,1)
imagesc(reshape(train4(3234,:),28,28)')
subplot(2,1,2)
imagesc(reshape(test9(307,:),28,28)')




cellfun(@(x) sum(cellfun(@length,x)), pp)


