function B = aff_basis(imsiz)
% Affine deformation basis
%
%   B = aff_basis(imsiz)
%
%       Returns a Lie algebraic basis for simple affine transforms
%       (dim = 3, x-translation, y-translation, and rotation)
%

assert(is_realmat(imsiz, [1 2]));

h = imsiz(1);
w = imsiz(2);

B.K = 3;
B.siz = imsiz;

N = h * w;
Bx = zeros(N, 3);
By = zeros(N, 3);

% x-translation

Bx(:, 1) = 1;
By(:, 1) = 0;

% y-translation

Bx(:, 2) = 0;
By(:, 2) = 1;

% rotation (close-wise on image frame)

cx = (1+w) / 2;
cy = (1+h) / 2;
[X, Y] = meshgrid((1:w) - cx, (1:h) - cy);

Bx(:, 3) = -Y(:);
By(:, 3) = X(:);

B.Bx = Bx;
B.By = By;




