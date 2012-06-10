function [g_ind,g_tran]=Congeal5(imgs,r_thres)


[x,y,ll]=size(imgs);
mid=(1+y)/2;
g_ind={};
g_tran={};
g_curr=0;


numcluster=100;
% 1 approimately assign digit to its nearest neighbour
while numcluster>=10
   r_thres= r_thres+0.01;
   [cc2,cindex2,tindex2]=Findlm(imgs,mid,r_thres) 
    len=cellfun(@length,cindex2);
    numcluster=ceil(x/max(len));
end


[aa,bb]=sort(len,'descend');
big=bb(1:numcluster);

% 2 clean up each big group
% 3 assign noisy stuff
reassign=setdiff(1:x,unique([g_ind{big}]));
g_ind=g_ind(big);
g_tran=g_tran(big);
hh=zeros(1,length(big));
for i =1 :length(big)
    hh(i)=g_ind{i}(1);
end
    [tt,yy]=Align3(squeeze(imgs(hh,mid,:)),imgs(reassign,:,:),2);
    for i=1:max(yy)
        ind=find(yy==i);
        g_tran{i}=[g_tran{i},tt(ind)];    
        g_ind{i}=[g_ind{i},reassign(ind)];    
    end

%{
    [tt,yy]=Align3(imgs(hh,:,:),squeeze(imgs(reassign,mid,:)),2,2);
    for i=1:max(yy)
        ind=find(yy==i);
        g_tran{i}=[g_tran{i},1+length(trans_s)-tt(ind)];    
        g_ind{i}=[g_ind{i},reassign(ind)];    
    end
%}  
%ii=1;seet2(imgs(g_ind{ii},:,:),g_tran{ii})
end

