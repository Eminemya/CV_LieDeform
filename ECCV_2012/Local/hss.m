function hss(src, Vx, Vy, i)
% show optical flow

vx = Vx(:,i);
vy = Vy(:,i);

[h w] = size(src);
vx = reshape(vx, [h w]);
vy = reshape(vy, [h w]);

x = 1 : 2: w;
y = (1 : 2: h)';

hold on;
quiver(x, y, vx(y, x), vy(y, x));
end
% hss(reshape(mani.X(:,1),31,31),Vx,Vy,1)
