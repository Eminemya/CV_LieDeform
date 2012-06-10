load mnist_all	




%0. preprocessing 
[x,y]=size(train4);
ntrain4=zeros(x,y);
sntrain4=zeros(x,y);

G = fspecial('gaussian',[3 3],2);
for i=1:x
tmp=double(reshape(train4(i,:),28,28))/255;
%biggest connected component
pp=bwconncomp(tmp);
if pp.NumObjects>1
ind=cellfun(@length,pp.PixelIdxList);
[aa,bb]=max(ind);
ind=[1:bb-1,bb+1:pp.NumObjects];
for j=ind
tmp(pp.PixelIdxList{j})=0;
end
end
%feature

%blur
%tmp2 = imfilter(tmp,G,'same');
tmp2 = tmp;
ntrain4(i,:)=tmp2(:);
sntrain4(i,:)=f_bb2(tmp2,28)';
end

save scale0 ntrain4 sntrain4
see2(1:200,'sntrain4','scale0')


%1) Local Perturbation
l2norm=sum(sntrain4.^2,2);

r_thres=0.05;
glabel=2:size(sntrain4,1);
cc=[1];
cindex={};
while(length(glabel)>0)
% imadjust...
ww2=IDM7(sntrain4(glabel,:)',sntrain4(cc(end),:)')';
ratio=ww2./l2norm(glabel);
%ratio=ww2./(sum(ntrain4(cc(end),:))+sum(ntrain4(glabel,:),2));
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
save scale1 cc cindex l2norm


%2) Global Align + peturbation
addpath('brute/')
glabel=cc(2:end);
cc2=[cc(1)];
cindex2={};
tindex2={};
while(length(glabel)>0)
    %[trans,ind]=Align2_bk(ntrain4(cc2(end),:),sntrain4(glabel,:),l2norm(glabel),28,r_thres); 
    [trans,ind]=Align2(ntrain4(cc2(end),:),sntrain4(glabel,:),l2norm(glabel),28,r_thres); 
    cindex2{length(cc2)}=glabel(ind);
    tindex2{length(cc2)}=trans;
    glabel(ind)=[];
    cc2=[cc2,glabel(1)];
    glabel(1)=[];
    [length(cc2),length(glabel)]
end


save scale2 cc2 cindex2 tindex2 sntrain4 ntrain4

%see3(tindex2,cindex2,cc2,'sntrain4','ntrain4','scale2')





%3) learn a template for rotation.

addpath('../template')
[tem1,aligned,trans]=Rotate(ntrain4(cc2,:));

%4) merge cc/cc2/ccindex/ccindex2

srntrain4=zeros(x,y);
%landmarks
srntrain4(cc2,:)=aligned;
%rest
for i=1:length(cindex2)
    rot=trans(i);
    for j=cindex2{i}
        tmp=imrotate(reshape(ntrain4(j,:),28),rot,'crop');
        srntrain4(j,:)=f_bb2(tmp,28)';
        ind=find(cc==j);
        for k=cindex{ind}
            tmp=imrotate(reshape(ntrain4(k,:),28),rot,'crop');
            srntrain4(k,:)=f_bb2(tmp,28)';
        end
    end
end


%5) train dist matrix
dis4=IDM7(sntrain4(glabel,:)',sntrain4(cc(end),:)')'




















