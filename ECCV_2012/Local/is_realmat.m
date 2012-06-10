function tf = is_realmat(A, siz)
% Tests whether an input is a real matrix of specific size
%
%   tf = IS_REALMAT(A);
%   tf = IS_REALMAT(A, siz);
%

tf = isfloat(A) && isreal(A) && ndims(A) == 2;

if nargin >= 2
    tf = tf && size(A, 1) == siz(1) && size(A, 2) == siz(2);
end
