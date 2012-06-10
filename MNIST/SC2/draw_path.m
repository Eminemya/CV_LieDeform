function [] = draw_path(lm,crv);
n = size(lm,2)-1;
T = size(lm,1)-1;
dt = 2*pi/n;
x = zeros(1,n+1);
y = zeros(1,n+1);
for t = 1:T+1
    theta = 0;
    for p = 2:n+1
        ds = exp(lm(t,p-1))*dt;
        theta = theta+crv(t,p-1)*ds;
        t1 = cos(theta);
        t2 = sin(theta);
        x(p)=x(p-1)+t1*ds;
        y(p)=y(p-1)+t2*ds;
    end
    plot(x,y); axis equal; pause(0.1);
end
