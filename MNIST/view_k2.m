function y=view_k2(id,optt,part)


nn={'','s','c','e','r'};
switch optt
case 0
load mnist_all
case 1
load mnist_edge_sobel
b=cell(1,4);
[aa,bb]=meshgrid(1:17,1:17);b{1}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(1:17,10:26);b{2}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,1:17);b{3}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,10:26);b{4}=sub2ind([26,26],aa(:),bb(:));

case 2
load mnist_corner
case 3
load mnist_edge_canny
case 4
load mnist_rote0
end

if(optt~=1)
load km_land
else
load pland
end
figure
for i=1:100
subplot(10,10,i)
if(optt~=1)
imagesc(reshape(eval([nn{optt+1} 'train' num2str(id) '(land{id+1}(i),:)']),28,28)')
else
im=eval([nn{optt+1} 'train' num2str(id) '(land{id+1}(1,i),:);']);
im2=eval([nn{optt+1} 'train' num2str(id) '(land{id+1}(part,i)+end/2,:);']);
len=17;
[mx,my]=meshgrid(1:len,1:len);
quiver(mx,fliplr(my')',reshape(im(b{part}),len,len),reshape(im2(b{part}),len,len))
axis off

end


end

end
