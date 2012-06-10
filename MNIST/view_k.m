function y=view_k(id,optt,part)


nn={'','s','c','e','r'};
switch optt
case 0
load mnist_all
eval(['load kmg/km' num2str(id)])
case 1
load mnist_edge_sobel
eval(['load kmp/pkm' num2str(id) '_' num2str(part)])
len=17;
b=cell(1,4);
[aa,bb]=meshgrid(1:17,1:17);b{1}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(1:17,10:26);b{2}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,1:17);b{3}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,10:26);b{4}=sub2ind([26,26],aa(:),bb(:));
[mx,my]=meshgrid(1:len,1:len);
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


cc=0;
Res = 'y';
while(Res=='y'&&cc<10)
for i=1:10

%1: computed centroid
subplot(10,10,(i-1)*10+1)
if(optt~=1)
imagesc(reshape(eval([nn{optt+1} 'train' num2str(id) '(land{id+1}(i+cc*10),:)']),28,28)')
else
im=c(i+cc*10,1:end/2);
im2=c(i+cc*10,end/2+1:end);
quiver(mx,fliplr(my')',reshape(im,len,len),reshape(im2,len,len))
axis off
end

%2: nearest examplar
subplot(10,10,(i-1)*10+2)
if(optt~=1)
imagesc(reshape(eval([nn{optt+1} 'train' num2str(id) '(land{id+1}(i+cc*10),:)']),28,28)')
else
im=eval([nn{optt+1} 'train' num2str(id) '(land{id+1}(part,i+cc*10),:);']);
im2=eval([nn{optt+1} 'train' num2str(id) '(land{id+1}(part,i+cc*10)+end/2,:);']);

quiver(mx,fliplr(my')',reshape(im(b{part}),len,len),reshape(im2(b{part}),len,len))
axis off
end
ind=randsample(find(idx==i+cc*10),10);


for j=3:10
subplot(10,10,(i-1)*10+j)
if(optt~=1)
imagesc(eval(['reshape(' nn{optt+1} 'train' num2str(id) '(ind(j),:),28,28)''']))
else
im=eval([nn{optt+1} 'train' num2str(id) '(ind(j),:);']);
im2=eval([nn{optt+1} 'train' num2str(id) '(ind(j)+end/2,:);']);
quiver(mx,fliplr(my')',reshape(im(b{part}),len,len),reshape(im2(b{part}),len,len))
axis off
end

end

end

Res = input('(y/n)  ', 's');
cc=cc+1;
end
close
end

