

load mnist_all	


%6,000 1

%1. preprocessing
[x,y]=size(train1);
ntrain1=zeros(x,400);
%{
%1.1 binarize
train1(train1<200)=0;
train1(train1>0)=1;
blabel=[];
for i=1:x
tmp=reshape(train1(i,:),28,28);
% 1 piece only
pp=bwconncomp(tmp);
if(pp.NumObjects==1)
[aa,bb]=ind2sub([28,28],find(tmp));
pc= princomp([aa,bb]);
if(pc(2)>pc(4))
b=imrotate(tmp,180*acos(-pc(1))/pi-90,'crop');
else
b=imrotate(tmp,-180*asin(-pc(3))/pi,'crop');
end
ntrain1(:,:,i)=f_bb(b,20);
else
blabel=[blabel,i];
end

end

%}

blabel=[];
for i=1:x
tmp=reshape(train1(i,:),28,28);
% 1 piece only
pp=bwconncomp(tmp);
if(pp.NumObjects==1)
[aa,bb]=ind2sub([28,28],find(tmp));
pc= princomp([aa,bb]);

%{
if(abs(pc(2))>abs(pc(4)))
b1=imrotate(double(tmp),180*acos(-pc(1))/pi-90,'crop');
else
b2=imrotate(double(tmp),-180*asin(-pc(3))/pi,'crop');
end
%}
%for 1, princi be vertical

b=imrotate(double(tmp),sign(pc(1)*pc(2))*180*acos(abs(pc(2)))/pi,'crop');
ntrain1(i,:)=f_bb(b,20);
else
blabel=[blabel,i];
end
end



%percentage

%{
glabel=setdiff(1:x,blabel);
sss=sum(ntrain1,2);
ww=IDM7(ntrain1(glabel,:)',ntrain1(1,:)');

bb=glabel(find(ww./sss(glabel)'>1))
cc=glabel(find(ww./sss(glabel)'<=0.1))

see2(bb,'ntrain1','ntrain')

%}





glabel=setdiff(1:x,blabel);
cc=[glabel(1)];
glabel(1)=[];
sss=sum(g2b(ntrain1(glabel,:),100),2)';




proj=mtd(ntrain1(glabel,:)',ntrain1(cc(end),:)');
ww2=IDM7_p(g2b(ntrain1(glabel,:),100)',g2b(proj,100));
ratio=ww2./sss;
[aa,bb]=max(ratio);
if(aa<=0.05)
%done
sss=[];
else
cc=[cc,glabel(bb)];
reduce=[bb,find(ratio<=0.05)];
sss(reduce)=[];
glabel(reduce)=[];
end






figure;hold on;plot(ww);plot(ww2,'r-')




%{
% not necessay...
dis_l2=pdist2(ntrain1(1,:),ntrain1(glabel,:));
c1=glabel(find(dis_l2./sss'<=0.05));

ww=IDM7(g2b(ntrain1(glabel,:),100)',g2b(ntrain1(cc(end),:),100)');
cc=glabel(find(ww./sss<=0.05))
%}








