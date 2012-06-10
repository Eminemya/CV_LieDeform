load mnist_all	

%0. preprocessing 
digit=0;
[numtrain,lendigit]=eval(['size(train' num2str(digit) ')']);
sq=sqrt(lendigit);

imgs=zeros(numtrain,lendigit);
ntrain=zeros(numtrain,lendigit);
G = fspecial('gaussian',[3 3],2);

for i=1:numtrain
tmp=eval(['double(reshape(train' num2str(digit) '(i,:),sq,sq))/255;']);
%biggest connected component
pp=bwconncomp(tmp);
if pp.NumObjects>1
ind=cellfun(@length,pp.PixelIdxList);

%{
[aa,bb]=max(ind);
ind=[1:bb-1,bb+1:pp.NumObjects];
for j=ind
tmp(pp.PixelIdxList{j})=0;
end
%}
for j=find(ind<15)
tmp(pp.PixelIdxList{j})=0;
end

end
%feature
%blur
%tmp2 = imfilter(tmp,G,'same');
tmp2 = tmp;
imgs(i,:)=f_bb2(tmp2,sq)';
ntrain(i,:)=tmp2(:);

end
l2norm=sum(imgs.^2,2);


%save scale0 ntrain imgs l2norm
%see2(1:200,'simgs','scale0')


%1) Local Perturbation

r_thres=0.07;
glabel=2:numtrain;
cc=[1];
cindex={};
while(length(glabel)>0)
% imadjust...
ww2=IDM7(imgs(glabel,:)',imgs(cc(end),:)')';
ratio=ww2./l2norm(glabel);
%ratio=ww2./(sum(imgs(cc(end),:))+sum(imgs(glabel,:),2));
[aa,bb]=max(ratio);
if(aa<=r_thres)
%done
cindex{length(cc)}=glabel;
glabel=[];
else
cindex{length(cc)}=glabel(find(ratio<=r_thres));
cc=[cc,glabel(bb)];
glabel([bb;find(ratio<=r_thres)])=[];
end
[length(cc),length(glabel)]
end

if length(cc)>length(cindex)
cindex{length(cc)}=[];
end
%save scale1 cc cindex
%seep_bk(cc,cindex,'imgs','scale0')
seep(cc,cindex,imgs)

%2) Global Align + peturbation
addpath('brute/')
rot_set=-50:5:50;
ll=length(rot_set);
lc=length(cc)
newimgs=zeros(length(cc),lendigit,ll);
mid=(ll+1)/2;
nomid=setdiff(1:ll,mid);
for i=1:lc
%all angles
    tmp=reshape(ntrain(cc(i),:),sq,sq);
    for j=nomid
        tmpp=imrotate(tmp,rot_set(j),'crop');
        newimgs(i,:,j)=f_bb2(tmpp,sq)';
    end
end
newimgs(:,:,mid)=imgs(cc,:);


glabel=2:lc;
cc2=[1];
cindex2={};
tindex2={};
while(length(glabel)>0)
    %[trans,ind]=Align2_bk(imgs(cc2(end),:),simgs(glabel,:),l2norm(glabel),sq,r_thres); 
    [trans,ind]=Align2(newimgs(cc2(end),:,mid),newimgs(glabel,:,nomid),sq,r_thres); 
    cindex2{length(cc2)}=glabel(ind);
    tindex2{length(cc2)}=trans;
    glabel(ind)=[];
    cc2=[cc2,glabel(1)];
    glabel(1)=[];
    [length(cc2),length(glabel)]
end
if length(cc2)>length(cindex2)
    cindex2{length(cc2)}=[];
end
%{
for i=1:length(tindex2)
if length(tindex2{i})>0 
    tindex2{i}(tindex2{i}>=mid)=tindex2{i}(tindex2{i}>=mid)+1;
end
end
%}

%save scale2 cc2 cindex2 tindex2 newimgs
see3(tindex2,cindex2,cc2,newimgs)
%IDM7(newimgs(cindex2{1}(8),:,20)',newimgs(cc2(1),:,mid)')'/sum(newimgs(cindex2{1}(8),:,20).^2)
%figure;imagesc(reshape(newimgs(cc2(229),:,11),28,28)')
%3) learn a template for rotation.

%3.0)Navie obj tuning
%{
[trans,ind]=Align2(squeeze(newimgs(1,:,mid)),newimgs(cc2(2:end),:,:),sq,40,rot_set);
seet(newimgs(cc2(2:end),:,:),trans);
%}
%3.1) EM
%{
addpath('../template')
[tem1,aligned,trans]=Rotate(newimgs(cc2,:,:),rot_set);
%}

%3.2) congeal NN
[aligned,trans,order]=Congeal(newimgs(cc2,:,:),rot_set,50);
seet(aligned(order,:,:),order)
%4) merge cc/cc2/ccindex/ccindex2
strain=zeros(numtrain,lendigit);
%landmarks
strain(cc(cc2),:)=aligned;
%rest
%cp=0;
%track=cell(1,length(cindex2));
for i=1:length(cindex2)
    %track{i}=[cc(cc2(i))];
    rot=trans(i);
    for k=cindex{cc2(i)}
        tmp=imrotate(reshape(ntrain(k,:),sq,sq),rot_set(rot),'crop');
        strain(k,:)=f_bb2(tmp,sq)';
        %cp=cp+1;
        %track{i}=[track{i},k];
    end

    for jj=1:length(cindex2{i})
        j=cindex2{i}(jj);        
        strain(cc(j),:)=newimgs(j,:,tindex2{i}(jj)+rot-mid);
        %cp=cp+1;
        %track{i}=[track{i},cc(j)];
        for k=cindex{j}
            tmp=imrotate(reshape(ntrain(k,:),sq,sq),rot_set(rot)+rot_set(tindex2{i}(jj)),'crop');
            strain(k,:)=f_bb2(tmp,sq)';
            %cp=cp+1;
            %track{i}=[track{i},k];
        end
    end
end

%see2(track{1},'strain','haha');

%5) train dist matrix
landmark=cc(cc2);
dis=IDM7(strain(cc(cc2),:)',strain');

eval(['save dis' num2str(digit) '  order dis landmark']);


%6) align test images
timg_a=cell(1,10);
trans_a=cell(1,10);
dist_a=cell(1,10);

for tt=0:9
timg=eval(['test' num2str(tt)]);

newtimgs=zeros([size(timg),ll]);
timg_a{tt+1}=zeros(size(timg));

for i=1:size(timg,1)
    %all angles
    tmp=reshape(timg(i,:),sq,sq);
    for j=nomid
        tmpp=imrotate(tmp,rot_set(j),'crop');
        newtimgs(i,:,j)=f_bb2(tmpp,sq)';
    end
    newtimgs(i,:,mid)=f_bb2(tmp,sq)';
end

[trans,ind,dis]=Align2(aligned,newtimgs,sq,1,[1,1]);
for i=1:size(timg,1)
timg_a{tt+1}(i,:)=newtimgs(i,:,trans(i));
end
trans_a{tt+1}=trans;
dist_a{tt+1}=dis;
end

eval(['save a_test' num2str(tt) '  timg_a trans_a dist_a']);


end

















%{
sq=28;
load scale0
tmpp=reshape(ntrain(1,:),28,28);

shx=0.2;shy=0.2;
mat=[1,shx,0;shy,1+shx*shy,0;0,0,1];
tform = maketform('affine',mat);
tmp2 = imtransform(tmpp,tform);
target=f_bb2(tmp2,sq);

IDM7_b(imgs(1,:)',target)
IDM7(imgs(1,:)',target)



%}
















