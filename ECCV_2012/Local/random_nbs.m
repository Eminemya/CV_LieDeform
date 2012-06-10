function nbs = random_nbs()
% Generate a random nbs system for debugging
%
%   nbs = random_nbs();
%

%% main

n = 20;
ns = 3;
siz = [5 5];
N = prod(siz);

deg = 4;

% seeds and neighbors

seeds = randpick(n, ns).';

s = cell(1, ns);
t = cell(1, ns);
nb = cell(1, ns);
smap = cell(1, ns);

for i = 1 : ns    
    cc = 1:n;
    cc(seeds(i)) = [];    
    nb{i} = cc(randpick(numel(cc), deg));    
    
    smap{i} = ones(1, deg) * i;
    s{i} = ones(1, deg) * seeds(i);
    t{i} = nb{i};
end

s = [s{:}];
t = [t{:}];
smap = [smap{:}];

X = randn(N, n);
Gx = randn(N, ns);
Gy = randn(N, ns);

nbs.ns = ns;
nbs.np = numel(s);
nbs.siz = siz;
nbs.seeds = seeds;
nbs.smap = smap;
nbs.nbs = nb;
nbs.s = s;
nbs.t = t;
nbs.w = rand(1, numel(s));
nbs.X = X;
nbs.Gx = Gx;
nbs.Gy = Gy;

