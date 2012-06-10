function plot_2dg(mu, C, r, color)
% Plot an ellipse that characterize a Gaussian model 
% the ellipse is at r * std.dev

% Solve linear transform T, s.t. T * T' = C

% We can assume T = [a 0; b c], as it is the Cholesky decomposition of C, 
% then
%
% a^2 = C(1,1)
% a * b = C(1,2) = C(2,1)
% b^2 + c^2 = C(2,2)
%

a = sqrt(C(1,1));
b = C(1,2) / a;
c = sqrt(C(2,2) - b^2);

T = [a 0; b c];

% Generate a standard circle

theta = linspace(0, 2 * pi, 300);  % 300 is the number of points on the ellipse
X = [cos(theta); sin(theta)];

% Transform it to the desired eclipse

X = T * X;
X = bsxfun(@plus, r * X, mu);

% Plot

plot(X(1,:), X(2,:), color, 'LineWidth', 2);



