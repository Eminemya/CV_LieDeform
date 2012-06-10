



a=reshape(test5(540,:),28,28);
a(a>0)=1;
aa=bwmorph(a,'erode');
imagesc(aa')



aa=bwmorph(a,'shrink');
imagesc(aa')




cd /csail/fisher4/users/donglai/

load mnist_all

ll=0;kk=0;opttt=1;

b=cell(1,4);
[aa,bb]=meshgrid(1:18,1:18);b{1}=sub2ind([28,28],aa(:),bb(:));
[aa,bb]=meshgrid(1:18,11:28);b{2}=sub2ind([28,28],aa(:),bb(:));
[aa,bb]=meshgrid(11:28,1:18);b{3}=sub2ind([28,28],aa(:),bb(:));
[aa,bb]=meshgrid(11:28,11:28);b{4}=sub2ind([28,28],aa(:),bb(:));


IDM10(double(test0(1,b{1}))',double(train0(1,b{1}))' )

