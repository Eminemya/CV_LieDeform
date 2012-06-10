% Note: this function removes certain constant factors for
% efficiency, so it does not compute an estimate of the entropy,
% but a function that it linear in the entropy.

function h=colorVasicek(v)

len=size(v,3);
m=floor(sqrt(len));

vals=sort(v,3);

intvals=vals(:,:,m+1:len)-vals(:,:,1:len-m);
hvec=log(intvals);
h=sum(hvec(:));
