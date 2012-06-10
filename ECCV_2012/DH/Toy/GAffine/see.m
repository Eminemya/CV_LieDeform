function see(img)
if(sum(size(img)==1)>0)
sq=sqrt(length(img))
figure;imagesc(reshape(img,sq,sq))
else
figure;imagesc(img)
end
colormap gray
axis off
axis equal
end
