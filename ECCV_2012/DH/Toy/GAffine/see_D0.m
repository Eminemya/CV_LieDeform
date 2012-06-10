function y=see_D0(kk,ran,optt)

switch optt
case 0
load mnist_all
load Align_rs
case 1
load mnist_all
load Align_r
case 2
load mnist_all
load data/Align_45r
load data/clus_label
case 3
load mnist_edge_canny
case 4
load mnist_rote0
end

nn={'','','c','e','r'};


if(exist(['D0seep' num2str(kk) '.mat'])==0)
%1) find indices
badlist=[];
idx=[];kidx=[];

tmp2=[];
idx2=[];
num=1;
shownum=5;

for j=ran
%eval(['load(''data_l2/dis_' num2str(j) '_' num2str(kk) '.mat'')']);
%eval(['load(''data_lp9_2/dis_' num2str(j) '_' num2str(kk) '.mat'')']);
%eval(['load(''data_lp9_2/dis_' num2str(kk) '_' num2str(j) '.mat'')']);
eval(['load(''data/data_l2_210/dis_' num2str(kk) '_' num2str(j) '.mat'')']);
%tmp=tmp';
[aa,bb]=sort(tmp,1,'ascend');
tmp2=[tmp2;aa(1:num,:)];
idx2=[idx2;bb(1:num,:)];
end

[pp,badlist]=acc(tmp2,find(ran==kk),num);

pp=pp(1:shownum,badlist);


[kk,length(badlist)]

idx2=idx2(:,badlist);
dis=sort(tmp2(:,badlist));
dis=dis(1:shownum,:);

[x,y]=size(idx2);
idx=idx2(bsxfun(@plus,pp,(0:x:x*(y-1))));

kidx=ran(ceil(pp/num));


eval(['save D0seep' num2str(kk) '.mat kidx idx badlist dis'])

else
eval(['load D0seep' num2str(kk)])
end

%2) plot them
Res = 'y';
cc=0;
while (Res=='y'&&cc<length(badlist))

for ii=cc+1:min([cc+10,length(badlist)])

for jj=1:5
% test errors
subplot(10,11,(ii-cc-1)*11+jj*2-1)
%eval(['aa=reshape(stest' num2str(kk) '(' num2str(badlist(ii))  ',:),21,21)'';'])
id=kidx(jj,ii);
pos=idx(jj,ii);
tid=find(find([clus{id+1,:}]==pos)<=cumsum(cellfun(@length,clus(id+1,:))),1,'first');

eval(['aa=reshape(stest' num2str(id) '{kk+1,tid}(' num2str(badlist(ii)) ',:),21,21)'';'])
%eval(['aa=reshape(' num2str(nn{optt+1}) 'test' num2str(kk) '(' num2str(badlist(ii))  ',:),28,28)'';'])
imagesc(aa)
title(num2str(badlist(ii)))
axis off
% nearest train images

subplot(10,11,(ii-cc-1)*11+jj*2)
eval(['aa=reshape(strain' num2str(id) '(' num2str(pos)  ',:),21,21)'';'])
%eval(['aa=reshape(' num2str(nn{optt+1}) 'train' num2str(id) '(' num2str(pos)  ',:),28,28)'';'])
imagesc(aa)
title([num2str(id) '   ' num2str(pos) ' ' num2str(dis(jj,ii))])
axis off
end



subplot(10,11,(ii-cc-1)*11+11)
eval(['aa=reshape(test' num2str(kk) '(' num2str(badlist(ii))  ',:),28,28)'';'])
imagesc(aa)
title('original')
axis off
% nearest train images

end

cc=cc+10;
Res = input('(y/n)  ', 's');


end
close 
end

