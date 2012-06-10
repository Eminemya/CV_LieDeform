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

%{
figure;
imshow(overlain2(reshape(mani.X(:,1),31,31), reshape(mani.X(:,mani.t(1)),31,31)));
hold on;
hss(reshape(mani.X(:,1),31,31),Vx,Vy,1);



figure;imshow(reshape(mani.X(:,1),31,31));hold on;show_dmfield(B,1,2);



src = reshape(mani.X(:,1),31,31);
tar = reshape(mani.X(:,mani.t(4)),31,31);

recon=dm_solve(B,src , tar);
fprintf('src - tar = %.4f\n', norm(src - tar, 'fro'));
fprintf('rec - tar = %.4f\n', norm(recon - tar, 'fro'));

proj=mtd(tar(:),src(:));
proj(proj>1)=1;
proj(proj<0)=0;
sqrt(sum((proj-tar(:)).^2))
%}
