clear
load mnist_all
h=fspecial('sobel');
nn={'train','test'};

for jj=1:2
for kk=0:9
len=eval(['size(' nn{jj} num2str(kk) ',1);'])
eval(['r' nn{jj} num2str(kk) '=zeros(len,784);'])
eval(['sr' nn{jj} num2str(kk) '=zeros(len*2,784);'])
for i=1:len

%rotate
tmp=eval(['reshape(' nn{jj} num2str(kk) '(i,:),28,28);']);
[aa,bb]=ind2sub([9,28],find(tmp(:,20:end)~=0));
pc= princomp([aa,bb]);

if(pc(2)>pc(4))
b=imrotate(double(tmp),180*acos(-pc(1))/pi-90,'crop');
else
b=imrotate(double(tmp),-180*asin(-pc(3))/pi,'crop');
end

eval(['r' nn{jj} num2str(kk) '(i,:)=b(:);'])

%sobel edge

tmp=conv2(b/255,h,'same');
eval(['sr' nn{jj} num2str(kk) '(i,:)=tmp(:);'])
tmp=conv2(b/255,h','same');
eval(['sr' nn{jj} num2str(kk) '(i+len,:)=tmp(:);'])

end
end
end

save mnist_rote0 rtest1 rtest2 rtest3 rtest4 rtest5 rtest6 rtest7 rtest8 rtest9 rtest0 rtrain1 rtrain2 rtrain3 rtrain4 rtrain5 rtrain6 rtrain7 rtrain8 rtrain9 rtrain0

save mnist_rote1 srtest1 srtest2 srtest3 srtest4 srtest5 srtest6 srtest7 srtest8 srtest9 srtest0 srtrain1 srtrain2 srtrain3 srtrain4 srtrain5 srtrain6 srtrain7 srtrain8 srtrain9 srtrain0


%pw distance

for kk=0:9
for ll=0:9
tmp=eval(['pdist2(double(rrtrain' num2str(ll) '),double(rrtest' num2str(kk) '),''euclidean'');']);

%{
len1=size(eval(['srtrain' num2str(ll)]),1)/2;
len2=size(eval(['srtest' num2str(kk)]),1)/2;
tmp=eval(['pdist2(double(srtrain' num2str(ll) '(1:len1,:)),double(srtest' num2str(kk) '(1:len2,:)),''euclidean'')+pdist2(double(srtrain' num2str(ll) '(len1+1:end,:)),double(srtest' num2str(kk) '(len2+1:end,:)),''euclidean'');']);

%}
eval(['save data_l2_D4/dis_' num2str(kk) '_' num2str(ll) ' tmp'])
[kk,ll]
end
end





load mnist_all
im=double(rtrain9(1,:));
pp=zeros(1,10);
qq=zeros(1,10);
for i=1:10
tmp=imrotate(reshape(im,28,28),i,'crop');
pp(i)=IDM7(im',tmp(:));
qq(i)=sum((im'-tmp(:)).^2);
end


IDM7(double(rtrain9(1,:))',double(rtrain9(2,:)'))




for i=1:10
tmp=imrotate(reshape(im,28,28),i,'crop');
imwrite(uint8(tmp),['ha' num2str(i) '.pgm'],'PGM');
end


for i=0:9
eval(['sum(sum(rtrain' num2str(i) '>=150))/size(rtrain' num2str(i) ',1)'])
end


%tmp=eval(['reshape(' nn{jj} num2str(kk) '(i,:),28,28);']);
tmp=reshape(rtrain9(69,:),28,28);
[aa,bb]=ind2sub([28,28],find(tmp~=0));
pc= princomp([aa,bb]);
b=imrotate(double(tmp),180*acos(-pc(1))/pi,'crop');
eval(['r' nn{jj} num2str(kk) '(i,:)=b(:);'])

