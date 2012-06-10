load mnist_all


[x,y]=size(train1);
sr=zeros(28,28,x);
for i=1:x
sr(:,:,i)=double(reshape(train1(i,:),28,28))/255;
end

save cg1 sr
