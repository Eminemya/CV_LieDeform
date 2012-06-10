load mnist_all
%{
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

%1) layer 1: L2->find nearest 5
num=5;
mm=[];
for kk=0:9
eval(['knn' num2str(kk) '=zeros(' num2str(num*20)  ',size(test' num2str(kk) ',1));'])
for ll=0:9
tmp=eval(['pdist2(double(train' num2str(ll) '),double(test' num2str(kk) '),''euclidean'');']);
[aa,bb]=sort(tmp,'ascend');
eval(['knn' num2str(kk) '(' num2str(num*ll+1) ':' num2str(num*ll+num) ',:)=aa(1:' num2str(num)  ',:);']);
eval(['knn' num2str(kk) '(' num2str(num*ll+1+num*10) ':' num2str(num*ll+num*11) ',:)=bb(1:' num2str(num)  ',:);']);
%{
%}
%eval(['ind=IDM5(stest' num2str(kk) '(1:size(test' num2str(kk) ',1),:)'',stest' num2str(kk) '(size(test' num2str(kk) ',1)+1:end,:)'',strain' num2str(kk) '(1:size(train' num2str(kk) ',1),:)'',strain' num2str(kk) '(size(train' num2str(kk) ',1)+1:end,:)'');']);
%eval(['save ind_' num2str(kk) '_' num2str(ll) ' ind'])
[kk,ll]
end
end


tt=zeros(1,10);
vote=cell(1,10);
for kk=0:9
eval(['[vote{kk+1},bad]=acc(knn' num2str(kk) ',kk+1,num);'])
tt(kk+1)=length(bad);
disp([(kk+1),bad])
end


vote1=cell(1,10);
vote2=cell(1,10);
tt1=zeros(1,10);
tt2=zeros(1,10);
h=fspecial('sobel');
for kk=0:9
%test
%{
len=eval(['size(test' num2str(kk) ',1);'])
eval(['stest' num2str(kk) '=zeros(len*2,900);'])
for i=1:len
tmp=eval(['conv2(reshape(double(test' num2str(kk) '(i,:))/255,28,28),h);']);
eval(['stest' num2str(kk) '(i,:)=tmp(:);'])
tmp=eval(['conv2(reshape(double(test' num2str(kk) '(i,:))/255,28,28),h'');']);
eval(['stest' num2str(kk) '(i+len,:)=tmp(:);'])
end
%}
%train
len=eval(['size(test' num2str(kk)  ',1);']);
dis=zeros(num*10,len);
for jj=0:9
for ii=1:len
eval(['img=train' num2str(jj) '(knn' num2str(kk)  '(' num2str((jj+10)*num+1) ':' num2str((jj+10)*num+num) ',ii),:);'])
%{
for j=1:num
tmp=eval(['tmp=conv2(reshape(double(img(j,:))/255,28,28),h,''valid'');']);
eval(['imgh(' num2str(k*num+j) ',:)=tmp(:);'])
tmp=eval(['tmp=conv2(reshape(double(img(j,:))/255,28,28),h'',''valid'');']);
eval(['imgv(' num2str(k*num+j) ',:)=tmp(:);'])
end
%}
eval(['dis(' num2str(jj*5+1) ':' num2str(jj*5+5) ',ii)=IDM4(double(test' num2str(kk)  '(ii,:))''/255,double(img)''/255)'';'])
end

end
%{
eval(['dis=IDM5(stest' num2str(i-1)  '(' num2str(j)  ',:))''/255,double(img{' num2str(j)  '})''/255);'])
[aa,bb]=sort(dis,'ascend');
vote2(:,j)=bb;
%}

[vote1{kk+1},bad]=acc(dis,kk+1,num);
tt1(kk+1)=length(bad);
disp([(kk+1),bad])
end








%combo:
vote_f=cell(1,10;
tt_f=zeros(1,10);
for kk=0:9
len=size(vote{kk+1},2);
ee=zeros(size(vote{kk+1}));
for jj=1:len
ee(vote{kk+1}(:,jj),jj)=1:10*num;
%ee(vote2{kk+1}(:,jj),jj)=ee(vote2{kk+1}(:,jj),jj)+(1:10*num)';
ee(vote1{kk+1}(:,jj),jj)=ee(vote1{kk+1}(:,jj),jj)+(1:10*num)';
end
[vote_f{kk+1},bad]=acc(ee,kk+1,num);

tt_f(kk+1)=length(bad);
disp([(kk+1),bad])

end

