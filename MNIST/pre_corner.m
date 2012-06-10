clear
load mnist_all

nn={'train','test'};
for jj=1:2
for kk=0:9
len=eval(['size(' nn{jj} num2str(kk) ',1);'])
eval(['c' nn{jj} num2str(kk) '=zeros(len,784);'])

for i=1:len
%binarize
tmp=eval(['cornermetric(reshape(' nn{jj} num2str(kk) '(i,:),28,28));']);
%skeleton
%eval(['b' nn{jj} num2str(kk) '(i,:)=reshape(bwmorph(L,''skel'',inf),1,784);'])
eval(['c' nn{jj} num2str(kk) '(i,:)=tmp(:);'])
end

end
end

clear num aa bb L i jj kk len mm nn tmp
save mnist_corner.mat

for kk=0:9
for ll=0:9
tmp=eval(['pdist2(double(ctrain' num2str(ll) '),double(ctest' num2str(kk) '),''euclidean'');']);
eval(['save dis_' num2str(kk) '_' num2str(ll) ' tmp'])
[kk,ll]
end
end

