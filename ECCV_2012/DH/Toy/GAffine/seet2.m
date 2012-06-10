%seet(imgs,ind)
function y=seet(imgs,ind)
len=length(ind);
Res = 'y';
cc=0;
ll=sqrt(size(imgs,3));
while (Res=='y'&&cc*100<len)

for j=1:min(100,len-cc*100)
subplot(10,10,j)
if length(size(imgs))==3
a=reshape(imgs(j+cc*100,ind(j+cc*100),:),ll,ll);
else
a=reshape(imgs(j+cc*100,:),ll,ll);
end

imagesc(a')
axis off
title(num2str(ind(j+cc*100)))
end

cc=cc+1;
Res = input('(y/n)  ', 's');
end
close 
end
