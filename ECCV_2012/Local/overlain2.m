function Ic = overlain2(I0, I1)
% overlain two gray images to generate a color one
%
%   Ic = OVERLAIN2(I0, I1);
%
%   I0 and I1 should be of the same size.
%   - I0 ==> red channel
%   - I1 ==> green channel
%

%assert(is_realmat(I0) && is_realmat(I1));
assert(isequal(size(I0), size(I1)));

Ic = zeros([size(I0) 3]);
Ic(:,:,1) = I0;
Ic(:,:,2) = I1;

