function R = fwd_warp(I, Vx, Vy, Msk)
% Forward-warpping an image using a displacement field
%
%   R = FWD_WARP(I, Vx, Vy);
%   R = FWD_WARP(I, Vx, Vy, Msk);
%

%% verify input

assert(is_realmat(I));
assert(is_realmat(Vx) && is_realmat(Vy));
assert(isequal(size(I), size(Vx), size(Vy)));

if nargin < 4
    Msk = true(size(I));
else
    assert(islogical(Msk) && isequal(size(Msk), size(I)));
end

Iclass = class(I);
if ~isa(Vx, Iclass)
    Vx = cast(Vx, Iclass);
end
if ~isa(Vy, Iclass)
    Vy = cast(Vy, Iclass);
end

%% main

R = fwd_warp_cimp(I, Vx, Vy, Msk);

