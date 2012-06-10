%seep(cc,cindex,'sntrain4','scale')
function y=seep(dd,ind , name,ff)
if(nargin==4)
eval(['load ' ff])
end
load mnist_all
len=length(ind);


Res = 'y';
cc=0;
ll=sqrt(eval(['size(' name ',2)']));
while (Res=='y'&&cc*10<len)

for j=1:100
subplot(10,10,j)
imagesc(zeros(1));
axis off
end

for j=1:min(10,len-cc*10)
subplot(10,10,j*10-9)
eval(['a=reshape(' name '(dd(j+cc*10),:),ll,ll)'';'])
imagesc(a)
axis off
%title(num2str(dd(j)))

for jj=1:min(9,length(ind{j+cc*10}))
subplot(10,10,j*10-9+jj)
eval(['a=reshape(' name '(ind{j+cc*10}(jj),:),ll,ll)'';'])
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
