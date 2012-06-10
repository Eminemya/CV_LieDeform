addpath(pwd)
load mnist_all
load km_land
tt=0;
for j=1:10

tmp2=[];
idx=[];

num=1;

for i=1:10
%{
eval(['load(''data_m_D1/1ind_' num2str(i-1) '_' num2str(j-1) '.mat'')']);
[aa,bb]=sort(ind,'ascend');
%}

eval(['load(''data_m2_D1/1dis_' num2str(i-1) '_' num2str(j-1) '.mat'')']);

[aa,bb]=sort(tmp','ascend');
tmp2=[tmp2;aa(1:num,:)];
%idx=[idx;ind(4:6,:)];

end

[pp,bad]=acc(tmp2,j,num);

disp([j,bad])

%{
figure
cc=0;
for k=bad
subplot(length(bad),6,cc*6+1)
eval(['imagesc(reshape(test' num2str(i-1)  '(k,:),28,28)'')'])
title(['test:  ' num2str(i-1)])
[dd,ee]=sort(tmp2(:,k),'ascend');
for l=1:5
subplot(length(bad),6,cc*6+l+1)
id=ceil(ee(l)/num);
eval(['imagesc(reshape(train' num2str(id-1)  '(' num2str(idx(ee(l),k))  ',:),28,28)'')'])
title(['train:  ' num2str(id-1) '  ' num2str(dd(l))])
end
cc=cc+1;
end
%}
tt=tt+length(bad);
end
