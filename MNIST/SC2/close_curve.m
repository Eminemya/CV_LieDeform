function [lm,crv] = close_curve(lm,crv);

wt = 100; % relative weights between gamma0 and gamma;
n = size(lm,2)-1;
dx = 2*pi/n;

n1L = zeros(1,n+1);
n1k = zeros(1,n+1);
n2L = zeros(1,n+1);
n2k = zeros(1,n+1);

x1 = zeros(1,n+1);
x2 = x1;
t1 = x1;
t2 = x1;

len = 0;
theta = 0;
t1(1)=1;
t2(1)=0;

for p = 2:n+1
    ds = exp(lm(p-1))*dx;
    len = len + ds;
    theta = theta+crv(p-1)*ds;
    t1(p) = cos(theta);
    t2(p) = sin(theta);
    x1(p)=x1(p-1)+t1(p)*ds;
    x2(p)=x2(p-1)+t2(p)*ds;
end
n0k = ones(1,n+1);
n0L = crv;
n1k = (x2 - x2(n+1));
n2k = (x1(n+1) - x1);
n1L = (t1 + crv.*n1k);
n2L = (t2 + crv.*n2k);

for q = 1:10000
    gamma0 = theta - 2*pi;
    gamma1=x1(n+1);
    gamma2=x2(n+1);
    len2 = len*len;
    wt1 = wt/len2;
    if sqrt(gamma0*gamma0/wt+gamma1*gamma1/len2+gamma2*gamma2/len2)<0.01
        break
    end
    del_lm = gamma0*n0L+wt1*(gamma1*n1L+gamma2*n2L);
    del_k =  gamma0*n0k+wt1*(gamma1*n2k+gamma2*n2k);
    
    lmax = max(abs(lm));
    delmax = max(abs(del_lm));
    if delmax>0
    lm = lm - (0.0001*lmax/delmax)*del_lm;
    end
    kmax = max(abs(crv));
    delmax = max(abs(del_k));
    if delmax>0
    crv = crv - (0.0001*kmax/delmax)*del_k;
    end
    
    theta = 0;
    t1(1)=1;
    t2(1)=0;
    len = 0;
    for p = 2:n+1
        ds = exp(lm(p-1))*dx;
        len = len + ds;
        theta = theta+crv(p-1)*ds;
        t1(p) = cos(theta);
        t2(p) = sin(theta);
        x1(p)=x1(p-1)+t1(p)*ds;
        x2(p)=x2(p-1)+t2(p)*ds;
    end
    
    n0k = ones(1,n+1);
    n0L = crv;
    n1k = (x2 - x2(n+1));
    n2k = (x1(n+1) - x1);
    n1L = (t1 + crv.*n1k);
    n2L = (t2 + crv.*n2k);
end

