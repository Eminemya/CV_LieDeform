clear
load mnist_all

nn={'train','test'};
for jj=1:2
for kk=0:9
len=eval(['size(' nn{jj} num2str(kk) ',1);'])
eval(['b' nn{jj} num2str(kk) '=zeros(len*2,784);'])
for i=1:len
%binarize
tmp=eval(['reshape(' nn{jj} num2str(kk) '(i,:),28,28);']);

%{
%connected component
[L, num] = bwlabel(tmp);
if(num~=1)
[aa,bb]=max(histc(L(:),1:num));
L(L~=bb)=0;
end
%}
eval(['mm=mean(tmp(tmp(:)~=0));'])
tmp(tmp<mm)=0;
%tmp(tmp<150)=0;
tmp(tmp~=0)=1;
%tmp(L==0)=0;

%skeleton
%eval(['b' nn{jj} num2str(kk) '(i,:)=reshape(bwmorph(L,''skel'',inf),1,784);'])
eval(['b' nn{jj} num2str(kk) '(i,:)=tmp(:);'])
end

end
end

clear num aa bb L i jj kk len mm nn tmp
save mnist_skel2.mat
