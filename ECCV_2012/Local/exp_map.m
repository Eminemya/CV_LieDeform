function [xt, yt, M] = exp_map(Vx, Vy, xs, ys, ts, stepsize)
% Perform velocity-field based exp-mapping
%
%   [xt, yt, M] = exp_map(Vx, Vy, xs, ys, ts, stepsize);
%
%   M indicates whether xt and yt are in field.
%

%% verify input

assert(is_realmat(Vx) && is_realmat(Vy) && isequal(size(Vx), size(Vy)));
assert(is_realmat(xs) && is_realmat(ys) && numel(xs) == numel(ys));

if isscalar(ts)
    ts = ts * ones(size(xs));
end

%% main

[xt, yt, M] = exp_map_cimp(Vx, Vy, xs, ys, ts, stepsize);


