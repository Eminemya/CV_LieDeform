%see2(1:100,'c','global/km1')
function y=see2(ind , name,ff)
if(nargin==3)
eval(['load ' ff])
end
load mnist_all
len=length(ind);


Res = 'y';
cc=0;
ll=sqrt(eval(['size(' name ',2)']));
while (Res=='y'&&cc*100<len)

for j=1:min(100,len-cc*100)
subplot(10,10,j)
eval(['a=reshape(' name '(' num2str(ind(j+cc*100))  ',:),ll,ll);'])
%imagesc(g2b(a',100))
imagesc(a')
end

cc=cc+1;
Res = input('(y/n)  ', 's');
end
