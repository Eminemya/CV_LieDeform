function [tt,sss,ttt,uuu]=test_l2(optt,ran)
load mnist_all

%2) pairwise distance
num=21;
tt=zeros(1,5);
sss=cell(1,10);
ttt=cell(1,10);
uuu=cell(1,10);

for kk=ran
eval(['knn=zeros(' num2str(num*2*length(ran))  ',size(test' num2str(kk) ',1));'])
for ll=ran
%eval(['load data_l2_D' num2str(optt)  '/dis_' num2str(kk) '_' num2str(ll) ' tmp'])
%eval(['load data_l2_D' num2str(optt)  '/dis_' num2str(kk) '_' num2str(ll)])
eval(['load test/' num2str(optt)  'dis_' num2str(kk) '_' num2str(ll)])
tmp=tmp';

if(optt~=5)
[aa,bb]=sort(tmp,1,'ascend');
else
aa=0;
[aa1,bb]=sort(tmp1,1,'ascend');
aa=aa+aa1(1:num,:);
[aa1,bb]=sort(tmp2,1,'ascend');
aa=aa+aa1(1:num,:);
[aa1,bb]=sort(tmp3,1,'ascend');
aa=aa+aa1(1:num,:);
[aa1,bb]=sort(tmp4,1,'ascend');
aa=aa+aa1(1:num,:);
end


eval(['knn(' num2str(num*ll+1) ':' num2str(num*ll+num) ',:)=aa(1:' num2str(num)  ',:);']);
%eval(['knn(' num2str(num*ll+1+num*length(ran)) ':' num2str(num*(ll+1)+num*(length(ran)+1)) ',:)=bb(1:' num2str(num)  ',:);']);
[kk,ll]
end

cc=1;
for take=[1,5,11,15,21]
if(take<=num)
eval(['[tmp,bad]=acc(knn(1:end/2,:),kk+1,num,take);'])
tt(cc)=tt(cc)+length(bad);

if(take==1)
sss{kk+1}=bad;
ttt{kk+1}=floor((tmp(1:take,bad)-1)/num);
end

end
cc=cc+1;
end


end








%{
[pp,qq]=sort(knn(:,[635,943]))
knn(42+(22:25),[635,943])
%total:

ll=0;
for i=0:9
ll=ll+eval(['size(test' num2str(i) ',1)']);
end

%}
