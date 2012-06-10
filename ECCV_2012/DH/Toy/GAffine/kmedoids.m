function [label, center] = kmedoids(D,k,precenter)
% cost: n x n distance matrix
% k: number of cluster

%1 kmeans++ initialization

n = size(D,1);
if nargin==3
center=precenter;
else
center=[randsample(n,1),zeros(1,k-1)];
ss=D(center(1),:);
rest=[1:center(1)-1,center(1)+1:n];

for i=2:k
    center(i) = randsample(rest,1,true,ss(rest));
    ss=D(center(i),:);
    rest(rest==center(i))=[];
end

end
%2 kmedoid iteration

last=zeros(1,n);
label=ones(1,n);
cc=1;
while any(label ~= last)
    last = label;

    % for non centers
    [~, label] = min(D(center,:));

    % for centers
    for i = 1: k
        ind=find(label==i);
        [~,tmp] = min(sum(D(ind,ind),2));
        center(i)=ind(tmp);
    end



    disp(['Iteration ' num2str(cc)])
    cc=cc+1;
end

%histc(label,1:10)

end
