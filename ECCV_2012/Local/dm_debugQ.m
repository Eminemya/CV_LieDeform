function [Q, f] = dm_debugQ(nbs, B, Alpha)
% Construct Q-matrix in a slow but safe way
%
%   [Q, f] = dm_debugQ(nbs, B, Alpha);
%

np = nbs.np;
s = nbs.s;
t = nbs.t;

N = prod(nbs.siz);
K = B.K;

Q = zeros(2*N*K, 2*N*K);
f = zeros(2*N*K, 1);

smap = nbs.smap;
ws = nbs.w;

for i = 1 : np
    
    a = Alpha(:, i);    
    gx = nbs.Gx(:, smap(i));
    gy = nbs.Gy(:, smap(i));
    dx = nbs.X(:, s(i)) - nbs.X(:, t(i));
            
    Cst = cell(1, 2*K);
    
    for k = 1 : K
        Cst{2*k-1} = diag(gx) * a(k);
        Cst{2*k} = diag(gy) * a(k);
    end
    
    Cst = [Cst{:}];
    
    Q = Q + ws(i) * (Cst' * Cst);    
    f = f + ws(i) * (Cst' * dx);
end
