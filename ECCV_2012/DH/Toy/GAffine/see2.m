%see2(1:100,'c','global/km1')
function y=see2(ind , name)
len=length(ind);


Res = 'y';
cc=0;
ll=sqrt(size(name,2));
while (Res=='y'&&cc*100<len)

for j=1:min(100,len-cc*100)
subplot(10,10,j)
a=reshape(name (ind(j+cc*100) ,:),ll,ll);
%a=reshape(name (:,ind(j+cc*100) ),30,38);
%a=reshape(name (:,ind(j+cc*100) ),20,28);
%imagesc(g2b(a',100))
imagesc(a)
colormap gray
end

cc=cc+1;
Res = input('(y/n)  ', 's');
end
close 
end
