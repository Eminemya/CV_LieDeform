load mnist_all	
%6,000 1

%1. preprocessing 

%1.1) PCA tilt may be harmful...
[x,y]=size(train4);
ntrain4=zeros(x,441);

for i=1:x
tmp=reshape(train4(i,:),28,28)';
tmp(tmp<100)=0;
tmp(tmp>0)=1;
ntrain4(i,:)=f_bb2(tmp,21);
end

save c1 ntrain4 
%see2(1:size(ntrain4,1) ,'ntrain4','c1')

%1.2) Local Perturbation

r_thres=0.1;
glabel=2:size(ntrain4,1);
cc=[1];
cindex={};
while(length(glabel)>0)
% imadjust...
ww2=IDM7(ntrain4(glabel,:)',ntrain4(cc(end),:)')';
ratio=ww2./sum(ntrain4(glabel,:),2);
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

see2(cc,'ntrain4','c1')
save c2 cc cindex

%2) Global Align + peturbation
r_thres=0.1;
glabel=2:size(ntrain4,1);
cc=[1];
cindex={};
while(length(glabel)>0)

% algin...
aligned=Align(ntrain4(glabel,:),ntrain4(cc(end),:));

ww2=IDM7(ntrain4(glabel,:)',ntrain4(cc(end),:)')';
ratio=ww2./sum(ntrain4(glabel,:),2);
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

see2(cc,'ntrain4','c1')
save c2 cc cindex




