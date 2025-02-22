addpath(pwd)
addpath('../')
load ../mnist_all

tt=0;
num=3;
ww=cell(1,10);
for i=1:10

tmp=[];
idx=[];
for j=1:10

eval(['load(''tra2te/1ind_' num2str(i-1) '_' num2str(j-1) '.mat'')']);
%eval(['load(''te2tra/1ind_' num2str(i-1) '_' num2str(j-1) '.mat'')']);
[aa,bb]=sort(ind,'ascend');

%{
[aa,bb]=sort(ind(1:10,:),'ascend');
%}
tmp=[tmp;aa(1:num,:)];
idx=[idx;bb(1:num,:)];
%{%}
end

%{
for kkk=1:num
[pp,bad]=acc(tmp,i,num,kkk);
disp([i,bad])
end
%}
[pp,bad]=acc(tmp,i,num,kkk);
disp([i,bad])

ww{i}=bad;

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
id=ceil(ee(l)/3);
eval(['imagesc(reshape(train' num2str(id-1)  '(' num2str(idx(ee(l),k))  ',:),28,28)'')'])
title(['train:  ' num2str(id-1) '  ' num2str(dd(l))])
end
cc=cc+1;
end
%}
tt=tt+length(bad);
end



%{
%enhancement

for i=1:10
bad=ww{i};
figure
cc=0;
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
end

wo=reshape(test1(252,:),28,28)';
for i=1:6
subplot(2,3,i)
wo2=bwmorph(wo,'thicken',i);
%wo2=double(wo2).*double(wo);
imagesc(wo2)
end



h=fspecial('sobel');
for i=1:10
for j=ww{i}

tmp=zeros(42,676);
im=eval(['double(reshape(test' num2str(i-1) '(j,:),28,28))']);
for ii=-10:1:10
im2=imrotate(im,ii*5)/255;
ppp=conv2(im2,h,'valid');
tmp(ii+11,:)=ppp(:);
ppp=conv2(im2,h','valid');
tmp(ii+11+end/2,:)=ppp(:);

%{
tmp(3*(ii+10)+1,:)=conv2(im2/255,h,'valid');
tmp(3*(ii+10)+1+end/2,:)=conv2(im2/255,h','valid');
for jj=1:2
wo=double(bwmorph(im2,'thicken',i)).*double(im2)/255;
ppp=conv2(wo,h,'valid');
tmp(3*(ii+10)+jj+1,:)=ppp(:);
ppp=conv2(wo,h','valid');
tmp(3*(ii+10)+jj+1+end/2,:)=ppp(:);
end
%}
end

for jj=1:10
hh=IDM5(tmp(1:end/2,:)',tmp(end/2+1:end,:)',eval(['strain' num2str(jj-1) '(1:end/2,:)'''],eval(['strain' num2str(jj-1) '(1+end/2:end,:)''']));
end


end
end









%}
