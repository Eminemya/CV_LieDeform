function yy=f_bb2(im,x)

[aa,bb]=ind2sub(size(im),find(im));

lx=max(aa)-min(aa)+1;
ly=max(bb)-min(bb)+1;

out=im(min(aa):max(aa),min(bb):max(bb));

y=zeros(x);
sx=1+floor((x-lx)/2);
sy=1+floor((x-ly)/2);
y(sx:sx+lx-1,sy:sy+ly-1)=out;

yy=y(:);
end
