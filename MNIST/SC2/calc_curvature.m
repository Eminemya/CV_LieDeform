function [gcL,gck,condn,path_energy] = calc_curvature(lm,crv,A);

% A = weight of stretching term

T = size(lm,1)-1;
n = size(lm,2)-1;
dt = 1/T;
dx = 2*pi/n;

path_energy = 0;

gcL = zeros(T+1,n+1);
gck = gcL;

n0L = zeros(1,n+1);
n1L = zeros(1,n+1);
n1k = zeros(1,n+1);
n2L = zeros(1,n+1);
n2k = zeros(1,n+1);

lmt = zeros(1,n+1);
lmtt = lmt;
kt = lmt;
ktt = lmt;
gcL_tmp = lmt;
gck_tmp = lmt;

x1 = zeros(1,n+1);
x2 = x1;
t1 = x1;
t2 = x1;

gamma = zeros(3,1);
gcn = gamma;
J = zeros(3,3);
maxcondn = 0;

len = zeros(T+1,1);
for t = 1:T+1
    for p = 2:n+1
        len(t) = len(t)+exp(lm(t,p-1))*dx;
    end
end
       

for t = 2:T
    theta = 0;
    t1(1)=1;
    t2(1)=0;
    for p = 2:n+1
        tmp = exp(lm(t,p-1))*dx;
        ds(p-1) = tmp;
        theta = theta+crv(t,p-1)*tmp;
        t1(p) = cos(theta);
        t2(p) = sin(theta);
        x1(p)=x1(p-1)+t1(p)*tmp;
        x2(p)=x2(p-1)+t2(p)*tmp;
    end

    lt = (len(t+1)-len(t-1))/(2*dt);
    lmt = (lm(t+1,:)-lm(t-1,:))/(2*dt);
    lmtt = (lm(t-1,:)-2*lm(t,:)+lm(t+1,:))/(dt*dt);
    kt = (crv(t+1,:)-crv(t-1,:))/(2*dt);
    ktt = (crv(t-1,:)-2*crv(t,:)+crv(t+1,:))/(dt*dt);
    
    path_energy = path_energy + G(lmt,kt,lmt,kt,ds,len(t),A);
    
    lmt2_ave = dotproduct(lmt,lmt,ds)/len(t);
    kt2_ave = dotproduct(kt,kt,ds)/len(t);
    
    gcL_tmp = lmtt + 0.5*(lmt.*lmt+lmt2_ave) - (lt/len(t))*lmt; 
    gcL_tmp = gcL_tmp - (0.5*len(t)*len(t)/A)*(kt.*kt+kt2_ave);
    gck_tmp = ktt + kt.*lmt+(lt/len(t))*kt;;
    
    n0L = len(t)*crv(t,:)/A;
    n0k = ones(1,n+1)/len(t); 
    n1k = (x2 - x2(n+1))/len(t);
    n2k = (x1(n+1) - x1)/len(t);
    n1L = len(t)*(t1 + len(t)*crv(t,:).*n1k)/A;
    n2L = len(t)*(t2 + len(t)*crv(t,:).*n2k)/A;
    
    J(1,1) = G(n0L,n0k,n0L,n0k,ds,len(t),A);
    J(1,2) = G(n0L,n0k,n1L,n1k,ds,len(t),A);
    J(1,3) = G(n0L,n0k,n2L,n2k,ds,len(t),A);
    J(2,1) = J(1,2);
    J(2,2) = G(n1L,n1k,n1L,n1k,ds,len(t),A);
    J(2,3) = G(n1L,n1k,n2L,n2k,ds,len(t),A);
    J(3,1) = J(1,3);
    J(3,2) = J(2,3);
    J(3,3) = G(n2L,n2k,n2L,n2k,ds,len(t),A);
    condn = cond(J);
    if condn>maxcondn
        maxcondn = condn;
    end
    if  condn>10^6
        condn 
        break;
    end
    J = inv(J); %inverse of the jacobian
    
    gamma(1) = G(gcL_tmp,gck_tmp,n0L,n0k,ds,len(t),A);
    gamma(2) = G(gcL_tmp,gck_tmp,n1L,n1k,ds,len(t),A);
    gamma(3) = G(gcL_tmp,gck_tmp,n2L,n2k,ds,len(t),A);
    gcn = J*gamma;
    gcL(t,:) = gcL_tmp - (gcn(1)*n0L+gcn(2)*n1L+gcn(3)*n2L);
    gck(t,:) = gck_tmp - (gcn(1)*n0k+gcn(2)*n1k+gcn(3)*n2k);

end



function[value] = G(aL,ak,bL,bk,ds,len,A);
n = size(aL,2)-1;
value = 0;
for p = 1:n
    value = value + (0.5*A/len)*(aL(p)*bL(p)+aL(p+1)*bL(p+1))*ds(p);
    value = value + (0.5*len)*(ak(p)*bk(p)+ak(p+1)*bk(p+1))*ds(p);
end

function[value] = dotproduct(a,b,ds);
n = size(a,2)-1;
value = 0;
for p = 1:n
    value = value + 0.5*(a(p)*b(p)+a(p+1)*b(p+1))*ds(p);
end


    
    
    