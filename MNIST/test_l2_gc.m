%{
ran=[0.1:0.1:1,2:1:10];
parfor i=1:19
cc=test_l2_gc(i);
eval(['save w' num2str(i*10) ' cc'])
end

dd=zeros(19,5);
for i=1:19
eval(['load w' num2str(i*10)])
dd(i,:)=cc;
end

%}
function tt=test_l2_gc(weight)
%{
for i=0:9
for kk=0:1
tmp2=[];
for j=0:9
eval(['load(''data_l2_D' num2str(kk) '/dis_' num2str(i) '_' num2str(j) '.mat'')']);
tmp2=[tmp2;tmp];
end
[aa,vote]=sort(tmp2,1,'ascend');
[i,kk]
eval(['save data_l2_D' num2str(kk) '/vote_' num2str(i) '.mat vote']);
end
end
%}

load data_l2_D1/vote_0

%combo
load mnist_all
labels=zeros(1,size(vote,1));
tt=1;
for i=0:9
tt2=eval(['size(train' num2str(i) ',1)'])+tt-1;
labels(tt:tt2)=i;
tt=tt2+1;
end

choose=[1,5,11,15,21];
tt=zeros(1,5);
clear vote
for i=0:9
eval(['v0=load(''data_l2_D0/vote_' num2str(i) ''');']);
eval(['v1=load(''data_l2_D1/vote_' num2str(i) ''');']);
[x,y]=size(v0.vote);
vote_f=zeros(x,y);
ee=zeros(x,y);
%{
for j=1:y
ee=zeros(x,1);
ee(v0.vote(:,j))=1:x;
ee(v1.vote(:,j))=ee(v1.vote(:,j))+weight*(1:x)';
[aa,vote_f(:,j)]=sort(ee);
end
%}

ee(v0.vote+ones(x,1)*(0:x:x*(y-1)))=repmat((1:x)',1,y);
[aa,vote_f]=sort(ee);
[i]
for k=1:5
bad=acc2(vote_f,labels,i+1,choose(k));
tt(k)=tt(k)+length(bad);
end

end

%{
img=cell(1,size(idx,2));
for j=1:size(idx,2)
img{j}=zeros(30,784);
for k=1:10
eval(['img{j}(k*3-2:k*3,:)=train' num2str(k-1) '(1+idx(k*3-2:k*3,j),:);'])
end
end
vote2=zeros(size(tmp));
for j=bad
eval(['dis=IDM4(double(test' num2str(i-1)  '(' num2str(j)  ',:))''/255,double(img{' num2str(j)  '})''/255);'])
[aa,bb]=sort(dis,'ascend');
vote2(:,j)=bb;
end
vote_f=zeros(size(tmp));
for j=bad
ee=zeros(30,1);
ee(vote(:,j))=1:30;
ee(vote2(:,j))=ee(vote2(:,j))+(1:30)';
[aa,bb]=sort(ee);
vote_f(:,j)=bb;
end
[cc,dd]=max(histc(floor((vote_f(1:3,bad)-1)/3),0:9));
disp([i,bad(find(dd~=i))])
%}
%{
figure
cc=0;
%bad=bad(find(dd~=i));
for k=bad
subplot(length(bad),6,cc*6+1)
eval(['imagesc(reshape(test' num2str(i-1)  '(k,:),28,28)'')'])
title(['test:  ' num2str(i-1)])
[dd,ee]=sort(tmp(:,k),'ascend');
for l=1:5
subplot(length(bad),6,cc*6+l+1)
id=ceil(ee(l)/3);
eval(['imagesc(reshape(train' num2str(id-1)  '(' num2str(idx(ee(l),k))  ',:),28,28)'')'])
title(['train:  ' num2str(id-1) '  ' num2str(dd(l))])
end
cc=cc+1;
end
%}
%tt2=tt2+length(find(dd~=i));
end
