function seea(optt,fn,row)
% seea(optt,fn,row)
switch optt
case 0
load mnist_all
case 1
load mnist_edge_sobel
case 2
load mnist_corner
case 3
load mnist_edge_canny
case 4
load mnist_rote0
case 5
load c1
end




im=eval([fn '(row,:);']);
len=sqrt(length(im));

if(optt~=1)
imagesc(reshape(im,len,len)')
else
im2=eval([fn '(row+end/2,:);']);
[mx,my]=meshgrid(1:len,1:len);
quiver(mx,fliplr(my')',reshape(im,len,len),reshape(im2,len,len))
axis off

end
end
