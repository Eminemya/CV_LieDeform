function see_rot(fn,row,step)
load mnist_all

im=double(eval([fn '(row,:);']));
for j=1:2
for i=1:5
subplot(2,5,i+(j-1)*5)
tmp=imrotate(reshape(im,28,28),step*i*(2*j-3),'crop');
imagesc(fliplr(tmp')')
end
end







