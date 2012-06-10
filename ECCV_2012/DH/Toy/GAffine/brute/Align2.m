function [trans,ind,aa]=Align2(ref,imgs,sq,thres,opt)
if nargin==4
opt=0;
end

%scale the bb
l2norm=squeeze(sum(imgs.^2,2));
[x,y]=size(l2norm);
mid=y/2+1;
dis=zeros(x,y);    
    
    if length(opt)==2       
       %for align test 
        for rot=1:y
            tmp=IDM7(imgs(:,:,rot)',ref');
            dis(:,rot)=min(tmp);
        end

    else
        for rot=1:y
            dis(:,rot)=IDM7(imgs(:,:,rot)',ref');
        end
    
    end
    dis=dis./l2norm;
    

    if length(opt)>2
        %for global alignment
        dis=(dis*5).^0.3-ones(x,1)*log(normpdf(opt,0,thres));
    end
    
    [aa,bb]=min(dis');
    if length(opt)>2
        trans=bb;
        ind=[];        
    else

        rr=find(aa<thres);
        if length(rr)>0
            ind=rr;
            trans=bb(rr);
            if length(opt)==1
            trans(trans>=mid)=trans(trans>=mid)+1;
            end
        else
            ind=[];                
            trans=[];
        end 

    end
end
