function y=see_D1(kk,ran)
load mnist_edge_sobel
load mnist_all
if(exist(['D1see' num2str(kk) '.mat'])==0)
%1) find indices
badlist=[];
idx=[];kidx=[];

tmp2=[];
idx2=[];
num=3;
shownum=5;

for j=ran
eval(['load(''data_l2_D1/dis_' num2str(kk) '_' num2str(j) '.mat'')']);
[aa,bb]=sort(tmp,'ascend');
%eval(['load(''bk/tra2te/1ind_' num2str(kk) '_' num2str(j) '.mat'')']);
%[aa,bb]=sort(ind,'ascend');
tmp2=[tmp2;aa(1:num,:)];
idx2=[idx2;bb(1:num,:)];
end

[pp,badlist]=acc(tmp2,find(ran==kk),num,1);

pp=pp(1:shownum,badlist);


[kk,badlist]

idx2=idx2(:,badlist);
dis=sort(tmp2(:,badlist));
dis=dis(1:shownum,:);

[x,y]=size(idx2);
idx=idx2(bsxfun(@plus,pp,(0:x:x*(y-1))));

kidx=ran(ceil(pp/num));
if(size(kidx,1)~=5)
kidx=kidx';
end

eval(['save D1see' num2str(kk) '.mat kidx idx badlist dis'])

else
eval(['load D1see' num2str(kk)])
end

%2) plot them
Res = 'y';
cc=0;
[mx,my]=meshgrid(2:27,2:27);
while (Res=='y'&&cc<length(badlist))

for ii=cc+1:min([cc+10,length(badlist)])

% test errors
subplot(10,6,(ii-cc-1)*6+1)
eval(['gx=reshape(stest' num2str(kk) '(' num2str(badlist(ii))  ',:),26,26)'';'])
eval(['gy=reshape(stest' num2str(kk) '(end/2+' num2str(badlist(ii))  ',:),26,26)'';'])
eval(['aa=reshape(test' num2str(kk) '(' num2str(badlist(ii))  ',:),28,28)'';'])
hold on
imagesc([zeros(28),fliplr(aa')'])
quiver(mx,fliplr(my')',gx,gy)

title(num2str(badlist(ii)))
axis off
% nearest train images

for jj=1:5
subplot(10,6,(ii-cc-1)*6+jj+1)
id=kidx(jj,ii);
pos=idx(jj,ii);
eval(['gx=reshape(strain' num2str(id) '(' num2str(pos)  ',:),26,26)'';'])
eval(['gy=reshape(strain' num2str(id) '(end/2+' num2str(pos)  ',:),26,26)'';'])
eval(['aa=reshape(train' num2str(id) '(' num2str(pos)  ',:),28,28)'';'])
hold on
imagesc([zeros(28),fliplr(aa')'])
quiver(mx,fliplr(my')',gx,gy)
title([num2str(id) '   ' num2str(pos) ' ' num2str(dis(jj,ii))])
axis off
end

end

cc=cc+10;
Res = input('(y/n)  ', 's');


end
end

