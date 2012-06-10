function [trans,ind]=Align2(ref,imgs,l2norm,sq,thres)
ind=[];                
trans=[];
%scale the bb
index=1:length(l2norm);

tmp=reshape(ref,sq,sq);
    for rot=setdiff(-50:10:50,0)
    %for rot=setdiff(-30:5:30,0)
        tmpp=imrotate(tmp,rot,'crop');
        tmpbest=IDM7(imgs(index,:)',f_bb2(tmpp,sq))';
        rr=find(tmpbest./l2norm(index)<thres);
        if length(rr)>0
             ind=[ind,index(rr)];
             index(rr)=[];
             trans=[trans,rot];
        end
    end

end
