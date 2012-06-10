% Return the position and value of the minimum of the matrix a.
% Usage: [rc,val]=min2d(a)
function [rc,val]=min2d(a)

[vals,inds]=min(a);
[val,c]=min(vals);
[val,r]=min(a(:,c));
rc(1)=r;
rc(2)=c;

