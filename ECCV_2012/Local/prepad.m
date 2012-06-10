function I = prepad(I)
% Pre-padding an image before doing the transform estimation
%

%% main

e = ceil(0.2 * size(I,1));

I = padarray(I, [e e]);



