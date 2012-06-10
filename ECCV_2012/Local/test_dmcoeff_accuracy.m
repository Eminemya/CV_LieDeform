function test_dmcoeff_accuracy()
% A small program to test the accuracy of dm-coefficient inference
%

%% prepare

x0 = test_image('sin', 0, 0, 0);
[gx, gy] = imgrad(x0);
gx = gx(:);
gy = gy(:);

B = aff_basis(size(x0));

%% translation

dx0 = 0.1 : 0.1 : 20;
dx1 = zeros(size(dx0));
cc_dx = zeros(size(dx0));

for i = 1 : numel(dx0)
    c0 = [dx0(i), 0, 0]';
    x1 = test_image('sin', dx0(i), 0, 0);
    
    c = dm_coeffs(B, x0(:), gx, gy, x1(:));
    dx1(i) = c(1);
    cc_dx(i) = (c0' * c) / (norm(c0) * norm(c));    
end


%% rotation

r0 = 2e-3 : 2e-3 : 0.5;
r1 = zeros(size(r0));
cc_rot = zeros(size(r0));

for i = 1 : numel(r0)
    c0 = [0, 0, r0(i)]';
    x1 = test_image('sin', 0, 0, r0(i));
    
    c = dm_coeffs(B, x0(:), gx, gy, x1(:));
    r1(i) = c(3);            
    cc_rot(i) = (c0' * c) / (norm(c0) * norm(c));
end


%% figures

figure;
subplot(221);
plot(dx0, dx0, dx0, dx1);

subplot(222);
plot(dx0, cc_dx);
set(gca, 'YLim', [0 1.2]);

subplot(223);
deg0 = rad2deg(r0);
deg1 = rad2deg(r1);
plot(deg0, deg0, deg0, deg1);

subplot(224);
plot(deg0, cc_rot);
set(gca, 'YLim', [0 1.2]);

