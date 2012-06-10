% Return two vectors. The first vector has the row of the nth largest
% element. The second vector has the column of the nth largest.
% Usage: [rowVec,colVec]=maxsort2d.m
function [rowVec,colVec]=maxsort2d(m)

[rows,cols]=size(m);
vm=m(:);
[val,ind]=sort(-vm);

colVec=floor((ind-1)/rows)+1;
rowVec=ind-(colVec-1)*rows;



