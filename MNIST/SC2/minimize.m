function [path1_lm,path1_crv] = minimize(path0_lm,path0_crv,N,wt);

% wt = weight of the stretching term

A = wt*wt;

epsilon = 0.0001;
gcLmax = 0;
gckmax = 0;
flag = 0;
path1_lm = path0_lm;
path1_crv = path0_crv;
for k = 1:N
    [gcL,gck,condn,energy] = calc_curvature(path1_lm,path1_crv,A);
    if condn>10^6
        break
    else
        xL = max(max(abs(gcL)));
        xk = max(max(abs(gck)));
        if flag==0
%             flag=1;
            gcLmax = xL;
            gckmax = xk;
        else
            if (xL>gcLmax)|(xk>gckmax)
                epsilon = 0.1*epsilon;
            end
            gcLmax = xL;
            gckmax = xk;
        end
    end

    format short g;
    format compact;
    if mod(k,100)==0
    [k,epsilon,energy,gcLmax,gckmax,condn]
    end
    path1_lm = path1_lm + epsilon*gcL;
    path1_crv = path1_crv + epsilon*gck;
    [path1_lm,path1_crv] = close_path(path1_lm,path1_crv);
end
