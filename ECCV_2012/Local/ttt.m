% to debug whatever

K = 5;

nbs = random_nbs();
N = size(nbs.X, 1);

B.K = K;
B.siz = nbs.siz;
B.Bx = randn(N, K);
B.By = randn(N, K);

Alpha = randn(K, nbs.np);

% Br = dm_update_B(nbs, B, Alpha);

Br = train_dm(nbs, B, 100, 1e-8);
