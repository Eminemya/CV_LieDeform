function [vote,bad]=acc(dis,label,num,take)
if(nargin==3)
take=num;
end

[aa,vote]=sort(dis,1,'ascend');


[cc,dd]=max(histc(floor((vote(1:take,:)-1)/num),0:9,1));
bad=find(dd~=label);
%{
bad=find(sum(floor((vote(1:take,:)-1)/num)==label-1)==0);
%}

end
