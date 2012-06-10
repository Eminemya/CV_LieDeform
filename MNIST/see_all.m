function y=see_all(kk,ran)
%{
load mnist_corner
load mnist_edge_sobel
load mnist_edge_canny
load km_land

%1) find indices
badlist=[];
idx=[];kidx=[];
x=0;y=0;

for optt=[1,0,2,3]

tmp2=[];
idx2=[];
tmp2km=[];
idx2km=[];

for j=ran
eval(['load(''data_m2_D' num2str(optt) '/'  num2str(optt) 'dis_' num2str(kk) '_' num2str(j) '.mat'')']);
[aa,bb]=sort(tmp,'ascend');
tmp2=[tmp2;aa(1:5,:)];
idx2=[idx2;bb(1:5,:)];
[aa,bb]=sort(tmp(land{j+1},:),'ascend');
tmp2km=[tmp2km;aa(1:5,:)];
idx2km=[idx2km;bb(1:5,:)];
end


[aa,bb]=sort(tmp2km,'ascend');
pp=ceil(bb(1:5,:)/5);

if(optt==1)
%km badlist
badlist=find(pp(1,:)~=find(ran==kk));
idx=zeros(10,4*length(badlist));
kidx=zeros(10,4*length(badlist));
x=length(ran)*5;y=length(badlist);
end


idx(1:5,(optt+1):4:end)=idx2km(bsxfun(@plus,bb(1:5,badlist),(0:x:x*(y-1))));
kidx(1:5,(optt+1):4:end)=ran(pp(:,badlist));


[aa,bb]=sort(tmp2,'ascend');
pp=ceil(bb(1:5,:)/5);
idx(6:10,(optt+1):4:end)=idx2(bsxfun(@plus,bb(1:5,badlist),(0:x:x*(y-1))));
kidx(6:10,(optt+1):4:end)=ran(pp(:,badlist));

end
%}
load hoho
nn={'','s','c','e'};

%2) plot them
Res = input('(y/n)  ', 's');
cc=0;
[mx,my]=meshgrid(2:27,2:27);
while (Res=='y'&&cc<length(badlist))

for ii=cc+1:min([cc+2,length(badlist)])

% test errors
subplot(11,8,(ii-cc-1)*4+2)
eval(['gx=reshape(stest' num2str(kk) '(' num2str(badlist(ii))  ',:),26,26)'';'])
eval(['gy=reshape(stest' num2str(kk) '(end/2+' num2str(badlist(ii))  ',:),26,26)'';'])
quiver(mx,fliplr(my')',gx,gy)
axis off
subplot(11,8,(ii-cc-1)*4+1)
eval(['aa=reshape(test' num2str(kk) '(' num2str(badlist(ii))  ',:),28,28)'';'])
imagesc(aa)
title(num2str(badlist(ii)))
axis off
subplot(11,8,(ii-cc-1)*4+3)
eval(['aa=reshape(ctest' num2str(kk) '(' num2str(badlist(ii))  ',:),28,28)'';'])
imagesc(imadjust(aa))
axis off
subplot(11,8,(ii-cc-1)*4+4)
eval(['aa=reshape(etest' num2str(kk) '(' num2str(badlist(ii))  ',:),28,28)'';'])
imagesc(aa)
axis off
% nearest train images

for jj=1:5
%km
subplot(11,8,(ii-cc-1)*4+jj*8+2)
id=kidx(jj,(ii-1)*4+2);
pos=idx(jj,(ii-1)*4+2);
eval(['gx=reshape(strain' num2str(id) '(' num2str(land{1+id}(pos))  ',:),26,26)'';'])
eval(['gy=reshape(strain' num2str(id) '(end/2+' num2str(land{1+id}(pos))  ',:),26,26)'';'])
quiver(mx,fliplr(my')',gx,gy)
title([num2str(id) '   ' num2str(pos) ])
axis off
%all
subplot(11,8,(ii-cc-1)*4+(jj+5)*8+2)
id=kidx(jj+5,(ii-1)*4+2);
pos=idx(jj+5,(ii-1)*4+2);
eval(['gx=reshape(strain' num2str(id) '(' num2str(pos)  ',:),26,26)'';'])
eval(['gy=reshape(strain' num2str(id) '(end/2+' num2str(pos)  ',:),26,26)'';'])
quiver(mx,fliplr(my')',gx,gy)
title([num2str(id) '   ' num2str(pos) ])
axis off

for ll=[1,3,4]
subplot(11,8,(ii-cc-1)*4+jj*8+ll)
id=kidx(jj,(ii-1)*4+ll);
pos=idx(jj,(ii-1)*4+ll);
eval(['aa=reshape(' num2str(nn{ll}) 'train' num2str(id) '(' num2str(land{1+id}(pos))  ',:),28,28)'';'])
imagesc(aa);
title([num2str(id) '   ' num2str(pos) ])
axis off
subplot(11,8,(ii-cc-1)*4+(jj+5)*8+ll)
id=kidx(jj+5,(ii-1)*4+ll);
pos=idx(jj+5,(ii-1)*4+ll);
eval(['aa=reshape(' num2str(nn{ll}) 'train' num2str(id) '(' num2str(pos)  ',:),28,28)'';'])

imagesc(imadjust(aa));

title([num2str(id) '   ' num2str(pos) ])
axis off
end


end
end



cc=cc+2;
Res = input('(y/n)  ', 's');
end
end

