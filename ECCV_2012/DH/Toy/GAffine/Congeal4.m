function [g_ind,g_tran]=Congeal4(imgs,r_thres,g_thres)


[x,y,ll]=size(imgs);
mid=(1+y)/2;
g_ind={};
g_tran={};
g_curr=0;


index=1:x;
% 1 find small groups
while length(index)>=g_thres
    g_curr=g_curr+1;
    curr=index(1);
    noind=[1:(curr-1),(curr+1):x];

    [tt,yy]=Align3(squeeze(imgs(curr,mid,:)),imgs(noind,:,:),r_thres);
    
    tmp=noind(yy);
    noind(yy)=[];
    yy=tmp;
    g_ind{g_curr}=[curr,yy];
    g_tran{g_curr}=[mid,tt];
    index=setdiff(index,g_ind{g_curr});
    %[g_curr,length(index),length(g_ind{g_curr})]
    %include previous center?
    
end
if  length(index)>0
    g_curr=g_curr+1;
    g_ind{g_curr}=index;
    g_tran{g_curr}=[mid];
end
len=cellfun(@length,g_ind);

% 2 assign noisy stuff

numcluster=max([5,ceil(x/max(len)),sum(len>=g_thres)]);

[aa,bb]=sort(len,'descend');
big=bb(1:numcluster);

reassign=setdiff(1:x,unique([g_ind{big}]));
g_ind=g_ind(big);
g_tran=g_tran(big);

hh=zeros(1,length(big));
for i =1 :length(big)
    hh(i)=g_ind{i}(1);
end
    [tt,yy]=Align3(squeeze(imgs(hh,mid,:)),imgs(reassign,:,:),2,1);
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

