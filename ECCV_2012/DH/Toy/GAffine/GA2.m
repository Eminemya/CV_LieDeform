load mnist_all	

%0. preprocessing 

[x,y]=size(train4);
ntrain4=zeros(x,y);
G = fspecial('gaussian',[3 3],2);
for i=1:x
tmp=double(reshape(train4(i,:),28,28))/255';
%feature

%blur
%tmp2 = imfilter(tmp,G,'same');
tmp2 = tmp;
ntrain4(i,:)=tmp2(:);
end

save cc1 ntrain4 
%see2(1:size(ntrain4,1) ,'ntrain4','c1')



%1) Local Perturbation
r_thres=0.05;
glabel=2:size(ntrain4,1);
cc=[1];
cindex={};
while(length(glabel)>0)
% imadjust...
ww2=IDM7(ntrain4(glabel,:)',ntrain4(cc(end),:)')';
ratio=ww2./sum(ntrain4(glabel,:).^2,2);
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


%see2(cc,'ntrain4','c1')
save cc2 cc cindex ntrain4

%2) Global Align + peturbation
%addpath('../grad/')
addpath('../brute/')
%{
sr=zeros(28,28,length(cc));
for i=1:size(sr,3)
      sr(:,:,i)=reshape(ntrain4(i,:),28,28);
end
%}

glabel=cc(2:end);
cc=[1];
cindex={};
while(length(glabel)>0)

% algin...
[ww2,aligned]=Align(ntrain4(glabel,:),ntrain4(cc(end),:));
%{
[adjSer,meanIms,transVecs]=binaryCongeal(sr(:,:,2:end),1,7,sr(:,:,1));
showSer(adjSer,2);
ww2=IDM7(ntrain4(glabel,:)',ntrain4(cc(end),:)')';
%}
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
if length(cc)>length(cindex)
cindex{length(cc)}=[];
end

%see2(cc,'ntrain4','c1')
save cc3 cc cindex




