
%b,d known
% kk specify
len=length(b{kk});
[mx,my]=meshgrid(2:27,30:55);
%{
load mnist_corner
load mnist_edge_sobel
load mnist_edge_canny
load km_land
%}
for j=1:len
subplot(len,6,(j-1)*6+1)
hold on
eval(['aa=reshape(test' num2str(kk-1) '(' num2str(b{kk}(j))  ',:),28,28)'';'])
eval(['bb=reshape(ctest' num2str(kk-1) '(' num2str(b{kk}(j))  ',:),28,28)'';'])
eval(['gx=reshape(stest' num2str(kk-1) '(' num2str(b{kk}(j))  ',:),26,26)'';'])
eval(['gy=reshape(stest' num2str(kk-1) '(end/2+' num2str(b{kk}(j))  ',:),26,26)'';'])
eval(['cc=reshape(etest' num2str(kk-1) '(' num2str(b{kk}(j))  ',:),28,28)'';'])
imagesc([aa;zeros(28);imadjust(bb)*255;cc*255])
axis off
quiver(mx,my,gx,gy)


if(km==0)
for i=1:10
land{i}=1:eval(['size(train' num2str(i-1) ',1)']);
end
end

for jj=2:6
subplot(len,6,(j-1)*6+jj)
hold on
eval(['aa=reshape(train' num2str(c{kk}(jj-1,j)) '(' num2str(land{1+c{kk}(jj-1,j)}(d{kk}(jj-1,j)))  ',:),28,28)'';'])
eval(['bb=reshape(ctrain' num2str(c{kk}(jj-1,j)) '(' num2str(land{1+c{kk}(jj-1,j)}(d{kk}(jj-1,j)))  ',:),28,28)'';'])
eval(['gx=reshape(strain' num2str(c{kk}(jj-1,j)) '(' num2str(land{1+c{kk}(jj-1,j)}(d{kk}(jj-1,j)))  ',:),26,26)'';'])
eval(['gy=reshape(strain' num2str(c{kk}(jj-1,j)) '(end/2+' num2str(land{1+c{kk}(jj-1,j)}(d{kk}(jj-1,j)))  ',:),26,26)'';'])
eval(['cc=reshape(etrain' num2str(c{kk}(jj-1,j)) '(' num2str(land{1+c{kk}(jj-1,j)}(d{kk}(jj-1,j)))  ',:),28,28)'';'])
imagesc([aa;zeros(28);imadjust(bb)*255;cc*255])
quiver(mx,my,gx,gy)
axis off
end




end

