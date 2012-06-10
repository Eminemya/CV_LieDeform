
%{


matlabpool
pp=cell(1,4);
parfor i=1:4
pp{i}=knn2(i-1,0:9);
end

%common error

ww=cell(1,10);

tt=0;
for j=1:10
ww{j}=zeros(1,2000);
for i=[1,2]
ww{j}(pp{i}{j})=ww{j}(pp{i}{j})+1;
end
disp([j,find(ww{j}==2)])
tt=tt+sum(ww{j}==2);
end
tt


for j=1:10
ind=find(ww{j}==4);
if(~isempty(ind))
figure;
see2(ind,['test' num2str(j-1)])
end
end

%}

%function [tt,sss,ttt,uuu]=knn2(optt,ran)
function [sss]=knn2(optt,ran)
addpath(pwd)
load mnist_all
load km_land
tt=zeros(1,10);
sss=cell(1,10);
ttt=cell(1,10);
uuu=cell(1,10);
num=3;
for i=ran
tmpp=[];
idx=[];

for j=ran

%{
eval(['load(''data_m_D1/1ind_' num2str(i) '_' num2str(j) '.mat'')']);
[aa,bb]=sort(ind,'ascend');
%}

%{
eval(['load(''data_m2_D' num2str(optt) '/'  num2str(optt) 'dis_' num2str(i) '_' num2str(j) '.mat'')']);
%tmp=tmp(land{j+1},:);
[aa,bb]=sort(tmp,'ascend');
%}


%eval(['load(''data_m3_D' num2str(optt) '/tra2te/'  num2str(optt) '_pdis_' num2str(i) '_' num2str(j) '.mat'')']);
eval(['load(''data_m3_D' num2str(optt) '/te2tra/'  num2str(optt) '_pdis_r' num2str(i) '_' num2str(j) '.mat'')']);

%{
[aa,bb]=sort((tmp1+tmp2+tmp3+tmp4),'ascend');
tmpp=[tmpp;aa(1:num,:)];
idx=[idx;bb(1:num,:)];
%}

tmppp=0;
for kkk=1:4
tmppp=tmppp+eval(['sort(tmp' num2str(kkk) ',''ascend'');']);
end
[aa,bb]=sort(tmppp,'ascend');
%{%}


tmpp=[tmpp;aa(1:num,:)];
idx=[idx;bb(1:num,:)];



end

[pp,bad]=acc(tmpp,find(ran==i),num);
tt(i+1)=length(bad);
sss{i+1}=bad;
idx=idx(:,bad);
[x,y]=size(idx);
uuu{i+1}=idx(bsxfun(@plus,pp(1:num,bad),(0:x:x*(y-1))));
ttt{i+1}=ran(1+floor((pp(1:num,bad)-1)/num));
disp([i,bad])

%{
figure
cc=0;
for k=bad
subplot(length(bad),6,cc*6+1)
eval(['imagesc(reshape(test' num2str(i)  '(k,:),28,28)'')'])
title(['test:  ' num2str(i)])
[dd,ee]=sort(tmpp(:,k),'ascend');
for l=1:5
subplot(length(bad),6,cc*6+l+1)
id=ceil(ee(l)/num);
eval(['imagesc(reshape(train' num2str(id-1)  '(' num2str(idx(ee(l),k))  ',:),28,28)'')'])
title(['train:  ' num2str(id-1) '  ' num2str(dd(l))])
end
cc=cc+1;
end
%}

end



%{
   1

     2   252   486

     3   270   273

     4

     5   124   232   844

     6   324   411   540   872

     7    88

     8    74   397   915

     9    86   824

    10    47   288   399   635
%}
