function a = dm_coeffs(B, xs, gx, gy, Xt)
%DM_COEFFS Solve the deformation coefficients from source to targets
%
%   a = DM_COEFFS(B, xs, gx, gy, Xt);
%
%   Inputs:
%   - B:        The deformation basis [N x (2K)]
%   - xs:       The source image [N x 1] (N: #pixels/image)
%   - gx:       The x-gradient field of the source image [N x 1]
%   - gy:       The y-gradient field of the source image [N x 1]
%   - Xt:       The target image [N x nt] (nt: # targets)
%   
%   Outputs:
%   - a:        The coefficients [K x nt]
%

%% verify inputs

N = B.siz(1) * B.siz(2);
assert(is_realmat(Xt) && size(Xt, 1) == N);

%% main

V = liealg_act(B, gx, gy);
dX = bsxfun(@minus, Xt, xs);
a = V \ dX;


