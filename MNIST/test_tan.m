function y=test_tan(opt)
load mnist_all
option=zeros(1,9);
option(opt)=1;
%option=ones(1,9);

im=double(reshape(train1(1,:),28,28));

switch opt
case 1
im2=[im(:,4:end),im(:,1:3)];
case 2
im2=[im(4:end,:);im(1:3,:)];
case 5
im2=zeros(28);
im2(5:24,5:24)=imresize(im,[20,20]);
case 6
im2=imrotate(im,30,'crop');
case 7
im2=double(bwmorph(im,'thin',2));
im(find(im2~=0));
im2(find(im2~=0))=im(find(im2~=0));
end





%im2=double(reshape(train2(1,:),28,28));

%im1=mtd(im2(:),double(train1(1,:))',option);
im1=mtd(im2(:),im(:)');

%im1=get_td(im2(:),double(train1(1,:))',option);



subplot(1,3,1)
%imagesc(reshape(g2b(im2,100),28,28))
imagesc(reshape(im2,28,28))
subplot(1,3,2)
%imagesc(reshape(g2b(train1(1,:),100),28,28))
imagesc(reshape(train1(1,:),28,28))
title([num2str(b_dist(im2,im)) '   ' num2str(IDM7(g2b(im2(:),100),g2b(im(:),100)))])
subplot(1,3,3)
%imagesc(reshape(g2b(im1,100),28,28))
im1(im1>255)=255;
im1(im1<0)=0;

imagesc(reshape(im1,28,28))
title([num2str(b_dist(im1,im2)) '   ' num2str(IDM7(g2b(im2(:),100),g2b(im1(:),100)))])



end


%{

im=double(reshape(train1(1,:),28,28));

im1=zeros(5,784);

tmp=[im(:,4:end),im(:,1:3)];
im1(1,:)=tmp(:);

tmp=[im(4:end,:);im(1:3,:)];
im1(2,:)=tmp(:);

tmp=zeros(28);
tmp(5:24,5:24)=imresize(im,[20,20]);
im1(3,:)=tmp(:);

tmp=imrotate(im,30,'crop');
im1(4,:)=tmp(:);

tmp=double(bwmorph(im,'thin',2));
im(find(tmp~=0));
tmp(find(tmp~=0))=im(find(tmp~=0));
im1(5,:)=tmp(:);


im2=mtd(im1',im)';

for i=1:5
subplot(5,2,i*2-1)
imagesc(reshape(im1(i,:),28,28))
subplot(5,2,i*2)
imagesc(reshape(im2(i,:),28,28))
end







im=double(reshape(train5(1,:),28,28));
tangents=get_td(im(:));
step=[1,1,1,1,1,1,0.01,1,1]
figure;
for i=1:size(tangents,2)
for j=[-4:1:5]
subplot(size(tangents,2),10,(i-1)*10+j+5)
imagesc(imadjust(im+step(i)/5*j*reshape(tangents(:,i),28,28)))
end
end

im2=[im(4:end,:);im(1:3,:)];


im=double(reshape(ntrain1(4297,:),28,28));
tangents=get_td(im(:));
im2=double(reshape(ntrain1(5800,:),28,28));
pp=inv(tangents'*tangents)*tangents'*(im2(:)-im(:))
%figure;
subplot(1,3,1)
imagesc(g2b(reshape(im,28,28),100))
%imagesc(reshape(im,28,28))
subplot(1,3,2)
%imagesc(reshape(im(:)+tangents*pp,28,28))
imagesc(g2b(reshape(im(:)+tangents*pp,28,28),100))
subplot(1,3,3)
%imagesc(reshape(im2,28,28))
imagesc(g2b(reshape(im2,28,28),100))

im3=im(:)+tangents*pp;

IDM7(g2b(im2(:),100),g2b(im3,100));

x = lsqlin(tangents,im2,[],[],[],[],-step,step)


%}
