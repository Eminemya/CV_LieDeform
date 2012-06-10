function show_dmfield(B, c, intv)
% Visualize the deformation field upon current image
%
%   show_dmfield(B, i, intv):     shows a particular base field
%   show_dmfield(B, c, intv):     shows a combined field with coefficients c
%
%   Inputs:
%   - B:        The deformation basis
%   - i:        an index scalar
%   - c:        coefficient vector of size K x 1
%   - intv:     interval in displaying
%

%% main

K = B.K;
Bx = B.Bx;
By = B.By;

if isscalar(c)
    vx = Bx(:, c);
    vy = By(:, c);
else
    assert(isequal(size(c), [K, 1]));
    vx = Bx * c;
    vy = By * c;
end

h = B.siz(1);
w = B.siz(2);

Vx = reshape(vx, [h w]);
Vy = reshape(vy, [h w]);

x = intv / 2 : intv : w;
y = (intv / 2 : intv : h).';

Vx = interp2(Vx, x, y);
Vy = interp2(Vy, x, y);

hold on;
quiver(x, y, Vx, Vy);


