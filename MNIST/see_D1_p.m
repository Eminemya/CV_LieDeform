function y=see_D1_p(kk,ran)
load mnist_edge_sobel
load mnist_all


b=cell(1,4);
[aa,bb]=meshgrid(1:17,1:17);b{1}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(1:17,10:26);b{2}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,1:17);b{3}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,10:26);b{4}=sub2ind([26,26],aa(:),bb(:));

if(exist(['pD1see' num2str(kk) '.mat'])==0)
%1) find indices
badlist=[];
idx=[];kidx=[];

tmpp=[];
idx1=[];
idx2=[];
idx3=[];
idx4=[];
num=3;
shownum=5;

for j=ran
eval(['load(''data_l2_D5/dis_' num2str(kk) '_' num2str(j) '.mat'')']);
tmp=0;
for k=1:4
[aa,bb]=eval(['sort(tmp' num2str(k) ',''ascend'');']);
eval(['idx' num2str(k) '=[idx' num2str(k) ';bb(1:num,:)];']);
tmp=tmp+aa(1:num,:);
end

tmpp=[tmpp;tmp];

end

[pp,badlist]=acc(tmpp,find(ran==kk),num,1);

%badlist=[12          35          50          74          91         218         266         273         338         347         353         363         376         398         484         486         500         516         691         783         799         847         899         988        1007        1020];

pp=pp(1:shownum,badlist);


[kk,badlist]

dis=sort(tmpp(:,badlist));
dis=dis(1:shownum,:);

for k=1:4
eval(['idx' num2str(k) '=idx' num2str(k) '(:,badlist);'])
[x,y]=eval(['size(idx' num2str(k) ');']);
eval(['idx' num2str(k) '=idx' num2str(k) '(bsxfun(@plus,pp,(0:x:x*(y-1))));'])
end

kidx=ran(ceil(pp/num));
if(size(kidx,1)~=5)
kidx=kidx';
end

eval(['save pD1see' num2str(kk) '.mat kidx idx1 idx2 idx3 idx4 badlist dis'])

else
eval(['load pD1see' num2str(kk)])
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
quiver(mx,fliplr(my)',gx,gy)

title(num2str(badlist(ii)))
axis off
% nearest train images

for jj=1:5
subplot(10,6,(ii-cc-1)*6+jj+1)
id=kidx(jj,ii);

gx=zeros(26);
for k=1:4
pos=eval(['idx' num2str(k) '(jj,ii);']);
eval(['gx(b{' num2str(k) '})=gx(b{' num2str(k) '})+strain' num2str(id) '(' num2str(pos)  ',b{' num2str(k) '})'';'])
end

gy=zeros(26);
aa=zeros(28);
for k=1:4
pos=eval(['idx' num2str(k) '(jj,ii);']);
eval(['gy(b{' num2str(k) '})=gy(b{' num2str(k) '})+strain' num2str(id) '(end/2+' num2str(pos)  ',b{' num2str(k) '})'';'])
eval(['aa(b{' num2str(k) '})=aa(b{' num2str(k) '})+double(train' num2str(id) '(' num2str(pos)  ',b{' num2str(k) '}))'';'])
end


hold on
imagesc([zeros(28),imadjust(fliplr(aa)')])
quiver(mx,fliplr(my')',gx,gy)
title([num2str(id) '   ' num2str(pos) ' ' num2str(dis(jj,ii))])
axis off
end

end

cc=cc+10;
Res = input('(y/n)  ', 's');


end

close
end

