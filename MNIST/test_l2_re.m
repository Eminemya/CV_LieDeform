function [tt,sss,ttt]=test_l2_re(optt,ran)
load mnist_all

%2) pairwise distance
num=21;
tt=zeros(1,5);
sss=cell(1,10);
ttt=cell(1,10);


for ll=ran
knn=[];
%idx=[];
for kk=ran
eval(['load data_l2_D' num2str(optt)  '/dis_' num2str(kk) '_' num2str(ll)])

if(optt~=5)
[aa,bb]=sort(tmp',1,'ascend');
else
aa=0;
[aa1,bb]=sort(tmp1',1,'ascend');
aa=aa+aa1(1:num,:);
[aa1,bb]=sort(tmp2',1,'ascend');
aa=aa+aa1(1:num,:);
[aa1,bb]=sort(tmp3',1,'ascend');
aa=aa+aa1(1:num,:);
[aa1,bb]=sort(tmp4',1,'ascend');
aa=aa+aa1(1:num,:);
end


knn=[knn;aa(1:num,:)];
%idx=[idx;bb(1:num,:)];
[kk,ll]
end

cc=1;
for take=[1,5,11,15,21]
if(take<=num)
eval(['[tmp,bad]=acc(knn,ll+1,num,take);'])
tt(cc)=tt(cc)+length(bad);

if(take==1)
sss{ll+1}=bad;
ttt{ll+1}=floor((tmp(1:take,bad)-1)/num);
end

end
cc=cc+1;
end


end








%{
[pp,qq]=sort(knn(:,[635,943]))
knn(42+(22:25),[635,943])
%}
