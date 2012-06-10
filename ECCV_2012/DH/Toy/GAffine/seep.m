%seep(cc,cindex,sntrain4)
function y=seep(dd,ind ,name)
len=length(ind);


Res = 'y';
cc=0;
ll=sqrt(size(name,2));
while (Res=='y'&&cc*10<len)

for j=1:100
subplot(10,10,j)
imagesc(zeros(1));
axis off
end

for j=1:min(10,len-cc*10)
subplot(10,10,j*10-9)
a=reshape( name (dd(j+cc*10),:),ll,ll)';
imagesc(a)
axis off
%title(num2str(dd(j)))

for jj=1:min(9,length(ind{j+cc*10}))
subplot(10,10,j*10-9+jj)
a=reshape( name(ind{j+cc*10}(jj),:),ll,ll)';
imagesc(a)
axis off
%title(num2str(ind{j+cc*10}(jj)))
end

end

cc=cc+1;
Res = input('(y/n)  ', 's');
end
close 
end
