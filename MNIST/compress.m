
load mnist_all
num=101;
for kk=0:9
eval(['knn' num2str(kk) '=zeros(' num2str(num*20)  ',size(test' num2str(kk) ',1));'])
for ll=0:9
%tmp=eval(['pdist2(double(train' num2str(ll) '),double(test' num2str(kk) '),''euclidean'');']);
%eval(['save dis_' num2str(kk) '_' num2str(ll) ' tmp'])
eval(['load dis_' num2str(kk) '_' num2str(ll)])
[aa,bb]=sort(tmp,'ascend');
eval(['knn' num2str(kk) '(' num2str(num*ll+1) ':' num2str(num*ll+num) ',:)=aa(1:' num2str(num)  ',:);']);
eval(['knn' num2str(kk) '(' num2str(num*ll+1+num*10) ':' num2str(num*ll+num*11) ',:)=bb(1:' num2str(num)  ',:);']);
[kk,ll]
end
end


tt=zeros(1,11);
cc=1;
for take=1:10:101%[1,5,11,15,21]
for kk=0:9
eval(['[tmp,bad]=acc(knn' num2str(kk) ',kk+1,num,take);'])
tt(cc)=tt(cc)+length(bad);
end
cc=cc+1;
end

%{
pp=cell(1,5);
pp{2}=[3323];
pp{2}=[ 3784      6970        7357 ];
pp{3}=[ 3839      6086        6628        6603        6431];
pp{4}=[ 3739      6227        6487        6561        6599];
pp{5}=[ 309   312   332   367   370];
%}

