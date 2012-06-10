function yy=f_bb(im,x)

[aa,bb]=ind2sub(size(im),find(im));

lx=max(aa)-min(aa)+1;
ly=max(bb)-min(bb)+1;

len=min([lx,ly]);
out=im(min(aa):max(aa),min(bb):max(bb));

if(x~=max([lx,ly]))
%need to scale 
if(lx>ly)
out=imresize(out,[x,ceil(ly*x/lx)]);
len=ceil(ly*x/lx);
else
out=imresize(out,[ceil(lx*x/ly),x]);
len=ceil(lx*x/ly);
end

end

%{
out(out<100)=0;
out(out>0)=1;
%}

y=zeros(x);
sy=1+floor((x-len)/2);
if(lx>ly)
%center y
y(:,sy:sy+len-1)=out;
else
%center x
y(sy:sy+len-1,:)=out;
end

yy=y(:);
end
