addpath('data_mean/')
load ../mnist_all

tt=0;
for i=1:10

tmp=[];
for j=1:10
eval(['load(''data_edge_mean/ind_' num2str(i-1) '_' num2str(j-1) '.mat'')']);
tmp=[tmp;ind(1,:)];
end

[aaa,bbb]=min(tmp);
bad=find(bbb-i~=0);
disp([i,bad])
%{
figure
cc=0;
for k=bad
subplot(length(bad),6,cc*6+1)
eval(['imagesc(reshape(test' num2str(i-1)  '(k,:),28,28)'')'])
title(['test:  ' num2str(i-1)])
[dd,ee]=sort(tmp(:,k),'ascend');
for l=1:5
subplot(length(bad),6,cc*6+l+1)
id=ceil(ee(l));
eval(['imagesc(reshape(mean(train' num2str(id-1)  '),28,28)'')'])
title(['train:  ' num2str(id-1) '  ' num2str(dd(l))])
end
cc=cc+1;
end
%}
tt=tt+length(bad);
end
