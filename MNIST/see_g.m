%see2(1:100,'c','global/km1')
function y=see_g(ind , name,ff)
if(nargin==3)
eval(['load ' ff])
end
load mnist_all
len=length(ind);
ll=ceil(sqrt(len));
for j=1:len
subplot(ll,ll,j)
eval(['a=reshape(' name '(' num2str(ind(j))  ',:),28,28);'])
[aa,bb]=ind2sub([28,28],find(a~=0));
tmp=[aa,bb]/28;
hold on

plot(tmp(:,1),tmp(:,2),'b.')
plot_2dg(mean(tmp)',cov(tmp),1,'r-')
end

