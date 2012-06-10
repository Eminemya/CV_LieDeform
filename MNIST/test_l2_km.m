function [tt,sss,ttt,uuu]=test_l2_km(optt,ran)
load mnist_all

%2) pairwise distance
num=21;
tt=zeros(1,5);
sss=cell(1,10);
ttt=cell(1,10);
uuu=cell(1,10);

if(optt~=5)
load km_land
else
load pland
end
for kk=ran
eval(['knn=zeros(' num2str(num*2*length(ran))  ',size(test' num2str(kk) ',1));'])

for ll=ran
%eval(['load data_l2_D' num2str(optt)  '/dis_' num2str(kk) '_' num2str(ll)])
eval(['load data_l2_D' num2str(optt)  '/dis_' num2str(kk) '_' num2str(ll)])

if(optt~=5)

tmp=tmp(land{ll+1},:);
[aa,bb]=sort(tmp,1,'ascend');

else

aa=0;
for ii=1:4
eval(['tmp' num2str(ii) '=tmp' num2str(ii) '(land{ll+1}(ii,:),:);']);
eval(['[aa1,bb]=sort(tmp' num2str(ii) ',1,''ascend'');']);
aa=aa+aa1(1:num,:);
end

end


eval(['knn(' num2str(num*ll+1) ':' num2str(num*ll+num) ',:)=aa(1:' num2str(num)  ',:);']);
eval(['knn(' num2str(num*ll+1+num*length(ran)) ':' num2str(num*ll+num*(length(ran)+1)) ',:)=bb(1:' num2str(num)  ',:);']);
[kk,ll]
end

cc=1;
for take=[1,5,11,15,21]
eval(['[vote,bad]=acc(knn(1:end/2,:),kk+1,num,take);'])
tt(cc)=tt(cc)+length(bad);

if(take==1)
sss{kk+1}=bad;



pp=knn(end/2+1:end,bad);
[x,y]=size(pp);
uuu{kk+1}=pp(bsxfun(@plus,vote(1:5,bad),(0:x:x*(y-1))));
ttt{kk+1}=ran(1+floor((vote(1:5,bad)-1)/num));

end
cc=cc+1;
end


end








%{
[pp,qq]=sort(knn(:,[635,943]))
knn(42+(22:25),[635,943])
%}
