function [g_ind,g_tran]=Congeal3(imgs,r_thres,g_thres,n_thres)


[x,y,ll]=size(imgs);
aligned=zeros(x,ll);
mid=(1+y)/2;
g_ind={};
g_tran={};
g_curr=0;


index=1:x;
% 1 find small groups
while length(index)>1
    g_curr=g_curr+1;
    curr=index(1);
    %[yy,tt]=Conn(imgs(curr,:,trans(curr)),imgs(index,:,:),l2norm(index,:),r_thres);
    noind=[1:(curr-1),(curr+1):x];
    [yy,tt]=Conn(squeeze(imgs(curr,mid,:)),imgs(noind,:,:),r_thres);
    tmp=noind(yy);
    noind(yy)=[];
    yy=tmp;
    
    len=length(yy);
    %just one step down the tree
    %{
    for i= 1:len
        %[i,length(noind)];
        if(~isempty(noind))
            [newyy,newtt]=Conn(squeeze(imgs(yy(i),tt(i),:)),imgs(noind,:,:),r_thres);
            yy=[yy,noind(newyy)];
            tt=[tt,newtt];
            noind(newyy)=[];
        else
            break
        end
    end
    %}
    % seet2(imgs([curr,yy],:,:),[mid,tt])
    g_ind{g_curr}=[curr,yy];
    g_tran{g_curr}=[mid,tt];
    index=setdiff(index,g_ind{g_curr});
    [g_curr,length(index),length(g_ind{g_curr})]
    %include previous center?
    
end
if  length(index)==1
    g_curr=g_curr+1;
    g_ind{g_curr}=index;
    g_tran{g_curr}=[mid];
end
len=cellfun(@length,g_ind);

hh=zeros(1,g_curr);
for i =1 :g_curr
    hh(i)=g_ind{i}(1);
end

%seet2(imgs(g_ind{1},:,:),g_tran{1})
%seet2(imgs(hh,:,:),ones(1,length(hh))*mid)

% 2 assign noisy stuff
small=find(len<g_thres);
big=setdiff(1:g_curr,small);

g_curr=g_curr+1;
g_ind{g_curr}=[];
g_tran{g_curr}=[];

for i=small
    curr=g_ind{i}(1);
    %m1: where is the nearest data? could be repetitive
    %{
    noind=[1:(curr-1),(curr+1):x];
    [yy,tt]=Conn(squeeze(imgs(curr,g_tran{i}(1),:)),imgs(noind,:,:),n_thres,1);
    g_ind{i}=[];    
    i
    if isempty(yy)
        g_ind{g_curr}=[g_ind{g_curr},curr];
        g_tran{g_curr}=[g_tran{g_curr},mid];
    else
        %stupid find algo instead of fancy cell manipulation
        yy=noind(yy);
        for j=find(cellfun(@length,g_ind))
            if sum(g_ind{j}==yy)>0
                g_ind{j}=[g_ind{j},yy];
                g_tran{j}=[g_tran{j},tt];
                break;
            end
        end        
    end
    %}
    %m1: where is the nearest center? 
    %well, consume the noise even though they may be junk
    [yy,tt]=Conn(squeeze(imgs(curr,g_tran{i}(1),:)),imgs(big,:,:),1,1);
    
    if isempty(yy)
        disp(['I should not appear.....:0 '])
        g_ind{g_curr}=[g_ind{g_curr},curr];
        g_tran{g_curr}=[g_tran{g_curr},mid];
    else
        [tmp,ind]=intersect(g_ind{i},g_ind{big(yy)});
        g_ind{i}(ind)=[];
        g_tran{i}(ind)=[];
        g_ind{big(yy)}=[g_ind{big(yy)},g_ind{i}];
        g_tran{big(yy)}=[g_tran{big(yy)},g_tran{i}];    
    end    
        g_ind{i}=[];    
end
ind=find(cellfun(@length,g_ind));
g_ind=g_ind(ind);
g_tran=g_tran(ind);
end

function [yy,tt]=Conn(ref,imgs,thres,opt)

if nargin==3
    opt=0;
end
[x,y,z]=size(imgs);

dis=reshape(IDM8(reshape(imgs,[],z)',ref),x,y);

[aa,bb]=min(dis');
if(opt==0)
    yy=find(aa<thres);
    tt=bb(yy);
else
    [ss,yy]=min(aa);
    tt=bb(yy);
    if ss>thres
        yy=[];
    end
end

end








