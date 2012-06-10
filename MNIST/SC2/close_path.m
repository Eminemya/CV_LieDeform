function[lm,crv] = close_path(lm,crv);
T = size(lm,1);
for t=1:T
    [lm(t,:),crv(t,:)] = close_curve(lm(t,:),crv(t,:));
end
