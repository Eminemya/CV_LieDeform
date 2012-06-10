addpath(pwd)
load mnist_all

tt=zeros(1,10);
tt2=0;
vote1=cell(1,10);
for i=pp:pp

tmp=[];
idx=[];
for j=1:10
eval(['load(''data_edge_all/ind_' num2str(i-1) '_' num2str(j-1) '.mat'')']);
tmp=[tmp;ind(1:3,:)];
idx=[idx;ind(4:6,:)];
end


[vote1{i},bad]=acc(tmp,i,3);

disp([i,bad])
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
%{%}
tt(i)=length(bad);
%tt2=tt2+length(find(dd~=i));
end
