function [aligned,g_tran,g_ind]=Congeal2(imgs)

[x,y,z]=size(imgs);
aligned=zeros(x,z);
mid=(1+y)/2;
g_ind=[1,zeros(1,x-1)];
g_tran=[mid,zeros(1,x-1)];
aligned(1,:)=squeeze(imgs(1,mid,:));
index=2:x;

for g_curr=1:x-1
    dis=reshape(IDM8(reshape(imgs(index,:,:),[],z)',squeeze(imgs(g_ind(g_curr),g_tran(g_curr),:))),x-g_curr,y);
    [aa,tt]=min(dis');
    [~,ind]=min(aa);
    g_ind(g_curr+1)=index(ind);
    g_tran(g_curr+1)=tt(ind);
    aligned(g_curr+1,:)=squeeze(imgs(index(ind),tt(ind),:));
    index(ind)=[];
    g_curr
end


end


