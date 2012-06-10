

IDM5(strain0(5617:5617,:)',strain0(end/2+5617:end/2+5617,:)',stest0(1:1,:)',stest0(end/2+1:end/2+1,:)')


h=fspecial('sobel');
IDM5(reshape(conv2(double(reshape(train0(4569:4569,:),28,28))/255,h),900,1),reshape(conv2(double(reshape(train0(4569:4569,:),28,28))/255,h'),900,1),reshape(conv2(double(reshape(test0(1:1,:),28,28))/255,h),900,1),reshape(conv2(double(reshape(test0(1:1,:),28,28))/255,h'),900,1))

IDM5(reshape(conv2(double(reshape(test0(1:1,:),28,28))/255,h),900,1),reshape(conv2(double(reshape(test0(1:1,:),28,28))/255,h'),900,1),reshape(conv2(double(reshape(train0(4569:4569,:),28,28))/255,h),900,1),reshape(conv2(double(reshape(train0(4569:4569,:),28,28))/255,h'),900,1))




IDM5(stest0(1:1,:)',stest0(end/2+1:end/2+1,:)',strain0(5617:5617,:)',strain0(end/2+5617:end/2+5617,:)')


IDM5(stest1(1:1,:)',stest1(end/2+1:end/2+1,:)',strain1(4569:4569,:)',strain1(end/2+4569:end/2+4569,:)')



IDM8(stest1(1:1,:)',stest1(end/2+1:end/2+1,:)',strain1(1:1,:)',strain1(end/2+1:end/2+1,:)')


IDM(stest1(1:1,:)',stest1(end/2+1:end/2+1,:)',strain1(1:1,:)',strain1(end/2+1:end/2+1,:)')

[aa,bb]=meshgrid(1:12,1:12);
b=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(1:12,1:12);
b=sub2ind([26,26],aa(:),bb(:));

IDM(stest1(1:1,b)',stest1(end/2+1:end/2+1,b)',strain1(1:1,:)',strain1(end/2+1:end/2+1,:)')


[aa,bb]=meshgrid(1:12,13:26);
b=sub2ind([26,26],aa(:),bb(:));
IDM(stest1(1:1,b)',stest1(end/2+1:end/2+1,b)',strain1(1:1,:)',strain1(end/2+1:end/2+1,:)')
[aa,bb]=meshgrid(13:26,1:12);
b=sub2ind([26,26],aa(:),bb(:));
IDM(stest1(1:1,b)',stest1(end/2+1:end/2+1,b)',strain1(1:1,:)',strain1(end/2+1:end/2+1,:)')
[aa,bb]=meshgrid(13:26,13:26);
b=sub2ind([26,26],aa(:),bb(:));
IDM(stest1(1:1,b)',stest1(end/2+1:end/2+1,b)',strain1(1:1,:)',strain1(end/2+1:end/2+1,:)')


eval(['tmp1=IDM8(srtest' num2str(kk) '(1:end/2,b)'',srtest' num2str(kk) '(end/2+1:end,b)'',srtrain' num2str(ll) '(1:end/2,b)'',srtrain' num2str(ll) '(end/2+1:end,b)'');']);

