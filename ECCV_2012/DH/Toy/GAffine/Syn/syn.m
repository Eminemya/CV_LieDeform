function y =syn(digit)

eval(['load mani_' num2str(digit) '_1'])
p = 0.9;
tol = 1e-3;
maxiter = 100;
addpath('/home/donglai/Desktop/ECCV/eccv12_codes')
addpath('./')
[B0, evs] = dm_init_basis(mani, p);
[B1, ~] = dm_train(mani, B0, maxiter, tol);


a=randn(9,B1.K);
a=100*a/norm(a);

yy=zeros(9,B1.K);
for i=1:9
    tmp= deform_img(reshape(mani.data(1).seed,28,28), B1, a(i,:));
    yy(i,:) =tmp(:)';
end

eval(['save syn_' num2str(digit)])

end
