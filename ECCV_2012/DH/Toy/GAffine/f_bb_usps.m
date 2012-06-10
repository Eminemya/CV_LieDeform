function y=f_bb_usps(im,x)
sq=size(im,1);
[aa,bb]=ind2sub(size(im),find(im));

lx=max(aa)-min(aa)+1;
ly=max(bb)-min(bb)+1;

    if lx<=ly 
        out=imresize(im(min(aa):max(aa),min(bb):max(bb)),[floor(lx*x/ly),x],'bilinear');
    else
        out=imresize(im(min(aa):max(aa),min(bb):max(bb)),[x,x],'bilinear');
    end
    out(out<1/510)=0;
    out(out>1)=1;
    out(sum(out,2)==0,:)=[];
    y=zeros(x);
    lx=size(out,1);
    sx=max(1,1+floor((x-lx)/2));
    y(sx:sx+lx-1,:)=out;
    y=reshape(y,x*x,1);
end
