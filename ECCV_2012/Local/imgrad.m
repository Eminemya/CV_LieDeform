function [Gx, Gy] = imgrad(I)
% Evaluate image gradient
%
%   [Gx, Gy] = imgrad(I);
%

Kx = (1/8) * [-1 0 1; -2 0 2; -1 0 1];
Ky = Kx.';

Gx = imfilter(I, Kx, 'replicate');
Gy = imfilter(I, Ky, 'replicate');

