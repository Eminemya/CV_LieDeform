
y=zeros(2227,784);

for i=0:1:46
eval(['load a' num2str(i) '.mat'])
y(kk,:)=aligned;
end

save align y
see2(1:100,'y','alig')

load cc2
y(1,:)=ntrain4(cc(1),:);

ww2=IDM7(y(2:end,:)',ntrain4(cc(1),:)')';
%tmp=bsxfun(@minus,y(2:end,:),y(1,:));
%rr=sum(tmp.^2,2)./sum(y(2:end,:).^2,2);
rr=ww2./sum(y(2:end,:).^2,2);
find(rr<0.05)



