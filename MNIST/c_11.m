

load mnist_all	
%6,000 1

%1. preprocessing 

%1.1) PCA align
[x,y]=size(train1);
ntrain1=zeros(x,784);

blabel=[];
for i=1:x
tmp=reshape(train1(i,:),28,28);
% 1 piece only
pp=bwconncomp(tmp);
if(pp.NumObjects==1)
[aa,bb]=ind2sub([28,28],find(tmp));
pc= princomp([aa,bb]);

%first princi be vertical
b=imrotate(double(tmp),sign(pc(1)*pc(2))*180*acos(abs(pc(2)))/pi,'crop');
ntrain1(i,:)=f_bb2(b,28);
else
blabel=[blabel,i];
end
end

ntrain1(blabel,:)=[];

save c1 ntrain1 blabel
%see2(1:size(ntrain1,1) ,'ntrain1','c1')


%1.2) TD+SP
glabel=2:size(ntrain1,1);
cc=[1];
cindex={};
while(length(glabel)>0)
proj=mtd(ntrain1(glabel,:)',ntrain1(cc(end),:)');
% imadjust...
proj(proj<0)=0;
proj=g2b(bsxfun(@times,proj,255./max(proj)),100);
ww2=IDM7_p(g2b(ntrain1(glabel,:),100)',proj);
ratio=ww2./sum(proj);
[aa,bb]=max(ratio);
if(aa<=0.05)
%done
cindex{length(cc)}=glabel;
glabel=[];
else
cindex{length(cc)}=glabel(find(ratio<=0.05));
cc=[cc,glabel(bb)];
glabel([bb,find(ratio<=0.05)])=[];
end
[length(cc),length(glabel)]
end

%see2(cc,'ntrain1','c1')
save c2 cc cindex
%2) Global Align: Congeal
addpath('/home/donglai/Desktop/Sans/MNIS/CG')
addpath('/home/donglai/Desktop/Sans/MNIS/CG/IO')
addpath('/home/donglai/Desktop/Sans/MNIS/CG/UTILITY')
addpath('/home/donglai/Desktop/Sans/MNIS/CG/CONGEAL_SUPPORT')


%sr=sr(1:end-6,:,:);

sr=zeros(28,28,length(cc));
for i=1:length(cc)
sr(:,:,i)=reshape(ntrain1(cc(i),:),28,28)/255;
end


[adjSer,meanIms,transVecs]=binaryCongeal(sr,20,7);
showSer(meanIms,1);


nntrain1=zeros(length(cc),784);
for i=1:length(cc)
nntrain1(i,:)=255*reshape(adjSer(:,:,i),1,784);
end
save haha nntrain1
see2(1:length(cc),'nntrain1','haha')

glabel=2:size(nntrain1,1);
cc2=[1];
cindex2={};
while(length(glabel)>0)
proj=mtd(nntrain1(glabel,:)',nntrain1(cc2(end),:)');
% imadjust...
proj(proj<0)=0;
proj=g2b(bsxfun(@times,proj,255./max(proj)),100);
ww2=IDM7_p(g2b(nntrain1(glabel,:),100)',proj);
ratio=ww2./sum(proj);
[aa,bb]=max(ratio);
if(aa<=0.05)
%done
cindex2{length(cc2)}=glabel;
glabel=[];
else
cindex{length(cc2)}=glabel(find(ratio<=0.05));
cc2=[cc2,glabel(bb)];
glabel([bb,find(ratio<=0.05)])=[];
end
[length(cc2),length(glabel)]
end
see2(cc2,'nntrain1','haha')

save c3 nntrain1 cc2

%3) Local Align:
%proto-star shape...mixture of too many
%3.1) SC
addpath('/home/donglai/Desktop/Sans/MNIS/SC')
nnntrain1=nntrain1(cc2,:);
nnntrain1(nnntrain1<100)=0;
[aa,bb]=max(pdist2(nnntrain1(1,:),nnntrain1(2:end,:)));

V1=reshape(nnntrain1(1,:),28,28);
V1=imresize(V1,sf,'bil');
V2=reshape(nnntrain1(1+bb,:),28,28);
V2=imresize(V2,sf,'bil');



glabel=1:length(cc2);

%3.2) TD
proj=nnntrain1(1,:)';
for i=1:100
subplot(10,10,i)
proj=mtd(nnntrain1(1+bb,:)',proj);
imagesc(reshape(proj,28,28))
end
%3.3) Geo on shape...

%3.4) part!!!

%3.5) low entrophy congeal




% imadjust...
proj(proj<0)=0;
proj=g2b(bsxfun(@times,proj,255./max(proj)),100);
ww2=IDM7_p(g2b(nnntrain1(glabel,:),100)',proj);
ratio=ww2./sum(proj);
[aa,bb]=max(ratio);
cc2=[cc2,glabel(bb)];
glabel([bb,find(ratio<=0.05)])=[];









