function [objv, errs] = dm_evalobjv(nbs, B, Alpha)
% Evaluate the objective of deformation manifold training
%
%   v = dm_evalobjv(nbs, B, Alpha);
%

%% main

np = nbs.np;
sm = nbs.smap;

X = nbs.X;
Vs = liealg_act(B, nbs.Gx, nbs.Gy);
DX = X(:, nbs.t) - X(:, nbs.s);

errs = zeros(1, np);
for i = 1 : np
    
    V = Vs(:,:,sm(i));
    dx = DX(:, i);
    a = Alpha(:, i);
    
    errs(i) = norm(dx - V * a)^2;
end

objv = sum(errs .* nbs.w);

