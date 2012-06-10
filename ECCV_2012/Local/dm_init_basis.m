function [B, evs] = dm_init_basis(nbs, Vx, Vy, p)
%TRAIN the basis of velocity fields
%
%   [B, evs] = DM_INIT_BASIS(nbs, Vx, Vy, ws, p);
%
%       Initializes the v-field basis using a PCA-variant.
%
%       - nbs:      The neighborhood system
%       - Vx:       The x- optical flow fields [N x np]
%       - Vy:       The y- optical flow fields [N x np]
%       - p:        The fraction of energy preserved in the principal
%                   subspace
%
%       Outputs:
%       - B:        The trained basis
%       - evs:      The eigenvalues
%

%% verify inputs

N = prod(nbs.siz);
np = nbs.np;

assert(is_realmat(Vx, [N np]));
assert(is_realmat(Vy, [N np]));
assert(p > 0 && p < 1);

%% main

V = [Vx; Vy];

w = nbs.w;
sw = sum(w);

C = (bsxfun(@times, V, w) * V') * (1/sw);
C = 0.5 * (C + C');

[B, D] = eig(C);
evs = diag(D);
[evs, si] = sort(evs, 1, 'descend');

K = find(cumsum(evs) >= p * sum(evs), 1);

evs = evs(1:K);
B = B(:, si(1:K));

Bx = B(1:N, :);
By = B((N+1):(2*N), :);
B = [];
B.K = K;
B.siz = nbs.siz;
B.Bx = Bx;
B.By = By;


