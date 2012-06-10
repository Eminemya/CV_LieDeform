function im=g2b(im,thres)
im(im<thres)=0;
im(im~=0)=1;
end
