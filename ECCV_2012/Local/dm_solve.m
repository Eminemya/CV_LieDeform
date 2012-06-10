function xr = dm_solve(B, xs, xt, tol)
% Solve the optimal projection of xt on the deformation manifold
%
%   xr = dm_solve(B, xs, xt);
%   xr = dm_solve(B, xs, xt, tol);
%
%       Find xr, which is a transformed version of xs along B, to
%       approximate xt.
%
%       tol: tolerance of changes at convergence (default = 1e-6);
%

%% verify input arguments

assert(is_realmat(xs) && isequal(size(xs), B.siz));
assert(is_realmat(xt) && isequal(size(xt), B.siz));

if nargin < 4
    tol = 1e-6;
end

%% main

xr = xs;
err = norm(xr - xt, 'fro');

ch = inf;

while ch > tol
    
    [gx, gy] = imgrad(xr);    
    coeff = dm_coeffs(B, xr(:), gx(:), gy(:), xt(:));
    
    xr_pre = xr;
    c = 1;
    while c > 1e-5        
        y = deform_img(xr, B, coeff * c);
        
        cur_err = norm(y - xt, 'fro');
        if cur_err < err
            xr = y;
            err = cur_err;
            break;
        else
            c = c * 0.5;
        end        
    end
    
    ch = norm(xr - xr_pre, 'fro');    
end


