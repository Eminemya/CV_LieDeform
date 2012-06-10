%{
load mnist_all
h=fspecial('sobel');






for kk=0:9
len=eval(['size(train' num2str(kk) ',1);'])
eval(['strain' num2str(kk) '=zeros(len*2,900);'])
for i=1:len
tmp=eval(['conv2(reshape(double(train' num2str(kk) '(i,:))/255,28,28),h);']);
eval(['strain' num2str(kk) '(i,:)=tmp(:);'])
tmp=eval(['conv2(reshape(double(train' num2str(kk) '(i,:))/255,28,28),h'');']);
eval(['strain' num2str(kk) '(i+len,:)=tmp(:);'])
end

len=eval(['size(test' num2str(kk) ',1);'])
eval(['stest' num2str(kk) '=zeros(len*2,900);'])
for i=1:len
tmp=eval(['conv2(reshape(double(test' num2str(kk) '(i,:))/255,28,28),h);']);
eval(['stest' num2str(kk) '(i,:)=tmp(:);'])
tmp=eval(['conv2(reshape(double(test' num2str(kk) '(i,:))/255,28,28),h'');']);
eval(['stest' num2str(kk) '(i+len,:)=tmp(:);'])
end

end


save hoho
%}

load hoho

mm=[];
for kk=5:9
eval(['knn' num2str(kk) '=zeros(30,size(test' num2str(kk) ',1));'])
for ll=0:9
eval(['knn' num2str(kk) '(' num2str(3*ll+1) ':' num2str(3*ll+3) ',:)=IDM3(stest' num2str(kk) '(1:size(test' num2str(kk) ',1),:)'',stest' num2str(kk) '(size(test' num2str(kk) ',1)+1:end,:)'',strain' num2str(kk) '(1:size(train' num2str(kk) ',1),:)'',strain' num2str(kk) '(size(train' num2str(kk) ',1)+1:end,:)'');']);
%eval(['ind=IDM3(stest' num2str(kk) '(1:size(test' num2str(kk) ',1),:)'',stest' num2str(kk) '(size(test' num2str(kk) ',1)+1:end,:)'',strain' num2str(kk) '(1:size(train' num2str(kk) ',1),:)'',strain' num2str(kk) '(size(train' num2str(kk) ',1)+1:end,:)'');']);
%eval(['save ind_' num2str(kk) '_' num2str(ll) ' ind'])
end
end

save knn



%knn0=zeros(30,size(test0,1));'])
for parfor kk=0:9
parfor ll=0:9
ind=IDM3(stest0(1:size(test0,1),:)',stest0(size(test0,1)+1:end,:)',strain0(1:size(train0,1),:)',strain0(size(train0,1)+1:end,:)');
eval(['save ind_' num2str(ll) ' ind'])
end



%{
%test accuracy
yy=IDM2(ttt(:)',ttt2(:)',strain1(1:2,:)',strain1(len+1:len+2,:)')
y=IDM(ttt,ttt2,reshape(strain1(1:1,:),30,30),reshape(strain1(len+1:len+1,:),30,30))
y=IDM(ttt,ttt2,reshape(strain1(2:2,:),30,30),reshape(strain1(len+2:len+2,:),30,30))


y=IDM(reshape(stest1(1:1,:),30,30),reshape(stest1(len+1:len+1,:),30,30),reshape(strain1(1:1,:),30,30),reshape(strain1(len+1:len+1,:),30,30))
y=IDM(reshape(stest1(1:1,:),30,30),reshape(stest1(len+1:len+1,:),30,30),reshape(strain1(2:2,:),30,30),reshape(strain1(len+2:len+2,:),30,30))

yy=IDM2(reshape(stest1(1:1,:),30,30),reshape(stest1(len+1:len+1,:),30,30),strain1(1:2,:)',strain1(len+1:len+2,:)')




IDM2(stest1(1:1,:),stest1(size(test1,1)+1:size(test1,1)+1,:),strain1(1:10,:)',strain1(size(train1,1)+1:size(train1,1)+10,:)')
IDM2(stest1(2:2,:),stest1(size(test1,1)+2:size(test1,1)+2,:),strain1(1:10,:)',strain1(size(train1,1)+1:size(train1,1)+10,:)')

IDM3(stest1(1:2,:)',stest1(size(test1,1)+1:size(test1,1)+2,:)',strain1(1:10,:)',strain1(size(train1,1)+1:size(train1,1)+10,:)')

dis=zeros(1,100);
for i=1:100
dis(i)=IDM4(double(test1(1,:))'/255,double(train1(i,:))'/255);
end
dd=IDM4(double(test1(1,:))'/255,double(train1(1:100,:))'/255);


%}




