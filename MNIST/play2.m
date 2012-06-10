%{
%}
for j=1:9
subplot(3,3,j)
eval(['a=reshape(train' num2str(i-1) '(' num2str(j)  ',:),28,28);'])
b=a;
b(b<mean(b(b~=0)))=0;
b(b~=0)=1;

c=bwmorph(b,'skel')
imagesc(c')
end


%{
for j=1:10
subplot(3,4,j)
eval(['a=reshape(mean(train' num2str(j-1) '),28,28);'])
%{
b=a;
b(b<mean(b(b~=0)))=0;
b(b~=0)=1;

c=bwmorph(b,'skel')
%}
c=a;
imagesc(c')
end
%}

