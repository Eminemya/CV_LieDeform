function [aligned,trans,pp]=Congeal(imgs,rot_set,sig)

l2norm=squeeze(sum(imgs.^2,2));
[x,y]=size(l2norm);
aligned=zeros(x,size(imgs,2));
mid=(1+y)/2;

curr=1;
trans(curr)=mid;
aligned(curr,:)=imgs(curr,:,trans(curr));
index=2:x;

pp=[1];
prior=-ones(x,1)*log(normpdf(rot_set,0,sig));
while length(index)>0 
    dis=zeros(length(index),y);
    for rot=1:y
        dis(:,rot)=IDM7(imgs(index,:,rot)',aligned(curr,:)');
        %dis(:,rot)=IDM7(aligned(curr,:)',imgs(index,:,rot)')';
        %dis(:,rot)=pdist2(aligned(curr,:),imgs(index,:,rot))';
    end
    

    [aa,bb]=min((prior(1:length(index),:)+dis)');
    [cc,curr]=min(aa);
    tmp=index(curr);
    index(curr)=[];
    trans(tmp)=bb(curr);
    curr=tmp;
    aligned(curr,:)=imgs(curr,:,trans(curr));
    %length(index)
    pp=[pp,curr];
end

%seet(imgs(pp,:,:),trans(pp))

end
    
