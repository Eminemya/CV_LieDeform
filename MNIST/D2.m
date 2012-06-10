%load mnist_all
%load mnist_edge_sobel
h=fspecial('sobel');
[a,b]=meshgrid(1:28)
[gx, gy, gxx,gyy] = deri(reshape(test1(86,:),28,28), 'x', 'y', 'xx','yy');
%figure;
subplot(2,4,1)
imagesc(reshape(test1(86,:),28,28))

subplot(2,4,2)
%quiver(a,b,reshape(stest1(86,:),26,26),reshape(stest1(end/2+86,:),26,26))
quiver(a,b,gx,gy)
subplot(2,4,3)
%quiver(a(1:24,1:24),b(1:24,1:24),conv2(reshape(stest1(86,:),26,26),h,'valid'),conv2(reshape(stest1(end/2+86,:),26,26),h','valid'))
quiver(a,b,gxx,gyy)
subplot(2,4,4)
imagesc(cornermetric(reshape(test1(86,:),28,28)))

[gx, gy, gxx,gyy] = deri(reshape(train0(2525,:),28,28), 'x', 'y', 'xx','yy');
%figure;
subplot(2,4,5)
imagesc(reshape(train0(2525,:),28,28))
subplot(2,4,6)
quiver(a,b,gx,gy)
subplot(2,4,7)
quiver(a,b,gxx,gyy)
subplot(2,4,8)
imagesc(cornermetric(reshape(train0(2525,:),28,28)))


