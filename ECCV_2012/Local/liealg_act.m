function V = liealg_act(B, gx, gy)
%LIEALG_ACT Lie algebraic action
%
%   V = LIEALG_ACT(B, gx, gy);
%
%   Input:
%   - B:        The Lie algebra basis struct
%   - gx:       The x-gradient field [N x nt]
%   - gy:       The y-gradient field [N x nt]
%
%   Output:
%   - V:        The image basis resulted from the action [N x K x nt]
%
%   N is the number of pixels per image, and n is the number of samples
%

%% main

Bx = B.Bx;
By = B.By;
N = size(Bx, 1);

nt = size(gx, 2);

if nt > 1
    gx = reshape(gx, [N 1 nt]);
    gy = reshape(gy, [N 1 nt]);
end

V = - (bsxfun(@times, Bx, gx) + bsxfun(@times, By, gy));

