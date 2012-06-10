function B = dm_update_B(nbs, B, Alpha, lambda)
%DM_UPDATE_B Updates the deformation basis
%
%   B = dm_update_B(nbs, B, alpha);
%
%   arguments:
%   - nbs:      the neighbor hood system
%   - B:        the basis struct to be updated
%   - Alpha:    the coefficient vectors for all pairs [K x np]
%   

%% verify input

K = B.K;
N = prod(B.siz);
ns = nbs.ns;

%assert(is_realmat(Alpha) && isequal(size(Alpha), [K np]));

%% main

% group pairs by sources

grps = intgroup(ns, nbs.smap);
ws = nbs.w;

% calculate c_s^{kl}

Cs = zeros(K^2, ns);  % K^2 x ns

for i = 1 : ns
    gi = grps{i};    
    a = Alpha(:, gi);        
    a = bsxfun(@times, a, sqrt(ws(gi)));
    aa = a * a';    
    Cs(:, i) = aa(:);    
end

% calculate product of gradients

Gxx = nbs.Gx .* nbs.Gx;   % N x ns
Gxy = nbs.Gx .* nbs.Gy;   
Gyy = nbs.Gy .* nbs.Gy; 

Hxx = Gxx * Cs';  % N x K^2
Hxy = Gxy * Cs';
Hyx = Hxy;
Hyy = Gyy * Cs';


% construct Q (quadratic term)

u0 = (1:N)';
u1 = u0 + N;

I0 = repmat((0 : (K-1)) * (2*N), K, 1);
J0 = repmat((0 : (K-1))' * (2*N), 1, K);
I0 = reshape(I0, 1, K^2);
J0 = reshape(J0, 1, K^2);

Ixx = bsxfun(@plus, u0, I0);
Jxx = bsxfun(@plus, u0, J0);

Iyx = bsxfun(@plus, u1, I0);
Jyx = bsxfun(@plus, u0, J0);

Ixy = bsxfun(@plus, u0, I0);
Jxy = bsxfun(@plus, u1, J0);

Iyy = bsxfun(@plus, u1, I0);
Jyy = bsxfun(@plus, u1, J0);


qd = 2 * K * N;

I = [Ixx(:); Iyx(:); Ixy(:); Iyy(:); (1:qd)'];
J = [Jxx(:); Jyx(:); Jxy(:); Jyy(:); (1:qd)'];
QV = [Hxx(:); Hyx(:); Hxy(:); Hyy(:); ones(qd,1) * lambda];

Q = sparse(I, J, QV, qd, qd);

% construct f (linear term)

X = nbs.X;
s = nbs.s;
t = nbs.t;
D = X(:, s) - X(:, t);
Dw = bsxfun(@times, D, ws);

hsx = nbs.Gx(:, nbs.smap) .* Dw;    % N x np
hsy = nbs.Gy(:, nbs.smap) .* Dw;    % N x np

Fx = hsx * Alpha';  
Fy = hsy * Alpha';

f = [Fx; Fy];
f = f(:);


% debug
% [Q0, f0] = dm_debugQ(nbs, B, Alpha);
% fprintf('norm(Q - Q0, inf) = %.4g\n', norm(Q - Q0, inf));
% fprintf('norm(f - f0, inf) = %.4g\n', norm(f - f0, inf));


% solve B

Bmat = Q \ f;

Bmat = reshape(Bmat, N, 2 * K);
Bx = Bmat(:, 1:2:end);
By = Bmat(:, 2:2:end);

B.Bx = Bx;
B.By = By;


