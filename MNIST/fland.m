
load mnist_edge_sobel

b=cell(1,4);
[aa,bb]=meshgrid(1:17,1:17);b{1}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(1:17,10:26);b{2}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,1:17);b{3}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,10:26);b{4}=sub2ind([26,26],aa(:),bb(:));

land=cell(1,10);

for kk=0:9
land{kk+1}=zeros(4,100);

for jj=1:4
eval(['load kmp/pkm' num2str(kk) '_' num2str(jj)])
for i=1:100
tmp=eval(['pdist2([strain' num2str(kk) '(1:end/2,b{' num2str(jj) '}),strain' num2str(kk) '(end/2+1:end,b{' num2str(jj) '})],c(i,:),''euclidean'');']);
[aa,bb]=min(tmp);

land{kk+1}(jj,i)=bb;
end
[kk,jj]
end

end

save pland land
