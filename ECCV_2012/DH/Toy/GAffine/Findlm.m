function [cc2,cindex2,tindex2]=Findlm(newimgs,mid,r_thres)
glabel=2:size(newimgs,1);
cc2=[1];
cindex2={};
tindex2={};
while(length(glabel)>0)
    %[trans,ind]=Align2_bk(imgs(cc2(end),:),simgs(glabel,:),l2norm(glabel),sq,r_thres); 
        [trans,ind,next]=Align3(squeeze(newimgs(cc2(end),mid,:)),newimgs(glabel,:,:),r_thres);
        cindex2{length(cc2)}=glabel(ind);
        tindex2{length(cc2)}=trans;
        glabel(ind)=[];
        cc2=[cc2,glabel(next)];
        glabel(next)=[];
        [length(cc2),length(glabel),length(ind)]
end
if length(cc2)>length(cindex2)
   cindex2{length(cc2)}=[];
   tindex2{length(cc2)}=[];
end




end
