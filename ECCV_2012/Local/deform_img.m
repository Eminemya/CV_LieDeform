function Ir = deform_img(I, B, c)
% Deform an image using a deformation system
%
%   Ir = deform_img(I, B, c);
%
%   It is advisable to prepad an image before using this function
%

%% verify input

K = B.K;
assert(isvector(c) && isreal(c) && numel(c) == K);
[h, w] = size(I); 
assert(isequal([h w], B.siz));

if ~isa(c, 'double')
    c = double(c);
end

if size(c, 2) > 1
    c = c.';
end


%% main

% velocity field

Vx = B.Bx * c;
Vy = B.By * c;
Vx = reshape(Vx, [h w]);
Vy = reshape(Vy, [h w]);

% source positions

X0 = 0:w-1;
X0 = X0(ones(1, h), :);

Y0 = (0:h-1).';
Y0 = Y0(:, ones(1, w));

% generate deformation field

[Xt, Yt, Msk] = exp_map(Vx, Vy, X0, Y0, 1, 0.01);

Xt = reshape(Xt, [h w]);
Yt = reshape(Yt, [h w]);
Msk = reshape(Msk, [h w]);

Dx = Xt - X0;
Dy = Yt - Y0;

Ir = fwd_warp_cimp(I, Dx, Dy, Msk);


