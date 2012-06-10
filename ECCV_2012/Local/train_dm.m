function [B, Alpha] = train_dm(nbs, B0, maxiter, tol)
%Train a deformation manifold on given data with neighborhood system
%
%   [B, Alpha] = train_dm(nbs, B0, maxiter, tol);
%
%   nbs:        The neighborhood data struct
%   B0:         The initial basis struct
%   maxiter:    the maximum number of iterations
%   tol:        the change tolerance (Linf-norm) at convergence
%

%% verify

assert(isequal(nbs.siz, B0.siz));

K = B0.K;
np = nbs.np;
ns = nbs.ns;


%% main

% prepare

grps = intgroup(ns, nbs.smap);
Alpha = zeros(K, np);

% main-loop

B = B0;
converged = false;
it = 0;

% objv = nan;

while ~converged && it < maxiter
    it = it + 1;
    
    % solve coefficients
    
    for i = 1 : ns
        gi = grps{i};
        
        si = nbs.seeds(i);
        ti = nbs.t(gi);
                
        xs = nbs.X(:, si);
        gx = nbs.Gx(:, i);
        gy = nbs.Gy(:, i);
        
        Xt = nbs.X(:, ti);
        
        Ai = dm_coeffs(B, xs, gx, gy, Xt);
        Alpha(:, gi) = Ai;        
    end
    
    % update B
    
    Bx_pre = B.Bx;
    By_pre = B.By;
    B = dm_update_B(nbs, B, Alpha, 1e-2);
            
    % normalize B and Alpha
    
    Bnrms = sqrt(sum(B.Bx .^ 2 + B.By .^ 2, 1));
    B.Bx = bsxfun(@times, B.Bx, 1 ./ Bnrms);
    B.By = bsxfun(@times, B.By, 1 ./ Bnrms);
    Alpha = bsxfun(@times, Bnrms', Alpha);
    
    % evaluate objv    
    % objv_pre = objv;
    % objv = dm_evalobjv(nbs, B, Alpha);  
            
    % determine convergence
    
    ch = max( maxdiff(B.Bx, Bx_pre), maxdiff(B.By, By_pre)  );
    converged = ch < tol;
    
    fprintf('Iter %4d:  B.ch = %.4g\n', it, ch);
    
end



function v = maxdiff(x, y)

v = max(abs(x(:) - y(:)));



