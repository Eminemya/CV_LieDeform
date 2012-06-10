function y=f_bb3(im,x,avg)
    im(im<1/510)=0;
    im(im>1)=1;
sq=size(im,1);
[aa,bb]=ind2sub(size(im),find(im));

lx=max(aa)-min(aa)+1;
ly=max(bb)-min(bb)+1;

    if lx<=ly 
        out=imresize(im(min(aa):max(aa),min(bb):max(bb)),[floor(lx*x/ly),x],'bilinear');
    else
        out=imresize(im(min(aa):max(aa),min(bb):max(bb)),[x,x],'bilinear');
    end
        %try to compensate for the color hist
    %out=out*(x*x/(sq*sq))*(sum(im(:))/sum(out(:)));
    %keep the avg
    %out=out*sum(im(:))/sum(out(:));
    out=out*avg*sum(out(:)>0)/sum(out(:));
    %out=out*sum(im(:)*sum(out(:)>0))/(sum(im(:)>0)*sum(out(:)));
    %out=out*sum(im(im(:)>0.1))*sum(out(:)>0.1)/(sum(im(:)>0.1)*sum(out(out(:)>0.1)));
    %out=out*0.5*sum(out(:)>0)/(sum(out(:)));
            
    out(out<1/510)=0;
    out(out>1)=1;
    out(sum(out,2)==0,:)=[];
    y=zeros(x);
    lx=size(out,1);
    sx=max(1,1+floor((x-lx)/2));
    y(sx:sx+lx-1,:)=out;
    y=reshape(y,x*x,1);


end
