load mnist_all



pp=cell(1,10);
for i=1:10
pp{i}=zeros(1,eval(['size(test' num2str(i-1) ',1)']));
for j=1:eval(['size(test' num2str(i-1) ',1)'])
a=reshape(eval(['test' num2str(i-1) '(j,:)'])test0(1,:),28,28);
[aa,bb]=ind2sub([28,28],find(a~=0));
tmp=[aa,bb];
pp{i}(j)=cov(diag(tmp/cov(tmp)*tmp'));
end
end



