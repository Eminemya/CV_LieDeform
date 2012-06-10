function tt=compress2(numland)
load mnist_all
%1) choose landmark
land=cell(1,10);
for kk=0:9
%1.1) hard choice
ind=[];
%{
tmp=eval(['pdist2(double(train' num2str(kk) '),mean(double(train' num2str(kk) ')),''euclidean'');']);
[aa,bb]=min(tmp);
ind=[ind,bb];
%}
%{
for jj=1:numland-1
tmp=tmp+eval(['pdist2(double(train' num2str(kk) '),double(train' num2str(kk) '('  num2str(ind(end)) ',:)),''euclidean'');']);
[aa,bb]=max(tmp);
ind=[ind,bb];
end
%}


%1.2) random choice
%ind=randsample(eval(['size(train' num2str(kk)  ',1)']),numland)';

%1.3) kmeans
%eval(['[idx, c] = kmeans(double(train' num2str(kk)  '), numland);'])

%{
eval(['load global/km' num2str(kk)])
ind=[];
for i=1:numland
tmp=eval(['pdist2(double(train' num2str(kk) '),c(i,:),''euclidean'');']);
[aa,bb]=min(tmp);
ind=[ind,bb];
end
[kk]
%}
%{
%1.4 hieraracical
eval(['L=linkage(double(train' num2str(kk)  '));'])
idx = cluster(L,'maxclust',numland);
C=zeros(numland,size(train0,2));
for jj=1:numland
C(jj,:)=eval(['mean(double(train' num2str(kk) '(idx==jj,:)));']);
end
%}
%{
ind=[];
for jj=1:numland
tmp=eval(['pdist2(double(train' num2str(kk) '),C(jj,:) ')),''euclidean'');']);
[aa,bb]=min(tmp);
ind=[ind,bb];
end
%}

land{kk+1}=ind;
end

load km_land land


%{
%sanity check for numland=1

ttrain=zeros(10,784);
tt=0;
for kk=0:9
ttrain(kk+1,:)=eval(['train' num2str(kk) '(' num2str(land{kk+1}) ',:);']);
end
for kk=0:9
tmp=eval(['pdist2(double(ttrain),double(test' num2str(kk) '),''euclidean'');']);
[aa,bb]=min(tmp);
tt=tt+sum(bb~=kk+1);
end


%}






%2) pairwise distance

choose=[1,5,11,15,21]
if(numland>21)
num=numland;
else
num=choose(find(choose<=numland,1,'last'));
end


for kk=0:9
eval(['knn' num2str(kk) '=zeros(' num2str(num*20)  ',size(test' num2str(kk) ',1));'])
for ll=0:9
eval(['load data_l2_D0/dis_' num2str(kk) '_' num2str(ll) ' tmp'])
tmp=tmp(land{ll+1},:);
%{
eval(['load data_edge_mean/ind_' num2str(kk) '_' num2str(ll)])
tmp=ind(1,:);
%}

[aa,bb]=sort(tmp,1,'ascend');
eval(['knn' num2str(kk) '(' num2str(num*ll+1) ':' num2str(num*ll+num) ',:)=aa(1:' num2str(num)  ',:);']);
eval(['knn' num2str(kk) '(' num2str(num*ll+1+num*10) ':' num2str(num*ll+num*11) ',:)=bb(1:' num2str(num)  ',:);']);
[kk,ll]
end
end

tt=zeros(1,5);
cc=1;
for take=[1,5,11,15,21]
if(take<=num)
for kk=0:9
eval(['[tmp,bad]=acc(knn' num2str(kk) ',kk+1,num,take);'])
tt(cc)=tt(cc)+length(bad);
end
cc=cc+1;
end
end

%{
within range

ran=3;
tt=zeros(1,10);
for kk=0:9
eval(['[tmp,tmp2]=sort(knn' num2str(kk) '(1:10,:),''ascend'');'])

tt(kk+1)=tt(kk+1)+sum(sum(tmp2(1:ran,:)==kk+1)==0);
end

%}

end



