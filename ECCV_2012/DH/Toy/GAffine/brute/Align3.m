function [tt,yy,aa]=Align3(ref,imgs,thres,opt)
if nargin==3
opt=0;
end



if opt==0
    [x,y,z]=size(imgs);
        dis=reshape(IDM8(reshape(imgs,[],z)',ref),x,y);
        [aa,bb]=min(dis');
        yy=find(aa<thres);
        tt=bb(yy);
        aa=findnext(aa,thres);
elseif opt==1
    %for multiple img alignment
    [x,y,z]=size(imgs);
    dis=zeros(x,size(ref,1)*y);
    for rr=1:size(ref,1)
        dis(:,(rr-1)*y+1:rr*y)=reshape(IDM10(reshape(imgs,[],z)',ref(rr,:)'),x,y);
    end
    
    [aa,bb]=min(dis');
    tt=mod(bb,y);
    tt(tt==0)=y;
    yy=ceil(bb/y);
elseif opt==2
    %for multiple ref alignment
    [x,y,z]=size(ref);
    dis=IDM8(imgs',reshape(ref,[],z)');    
    [aa,bb]=min(dis);
    %tt=mod(bb,y)+1;
    tt=ceil(bb/x);
    yy=bb-x*(tt-1);    
        
end




end
