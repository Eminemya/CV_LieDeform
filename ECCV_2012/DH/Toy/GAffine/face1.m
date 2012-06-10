
addpath('/home/donglai/Desktop/ECCV/eccv12_codes')

cc=1;
for alpha = 0.001: 0.0005: 0.01;
%alpha = 0.002
subplot(4,6,cc)
ratio = 0.5;
minWidth = 8;
nOuterFPIterations = 10;
nInnerFPIterations = 3;
nSORIterations = 30;
para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];

 tmp = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,k),dset.siz), reshape(dset.data(j).seed,dset.siz),para);
 [vx,vy] = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,k),dset.siz), reshape(dset.data(j).seed,dset.siz),para);
%sum((tmp1(:)-face_r(:,ctrs(seed(j)))).^2)

 cc=cc+1;
imagesc(tmp)
colormap gray
[cc, max(abs(vx(:))),sum((tmp(:)-dset.data(j).nbs(:,k)).^2),sum((tmp(:)-dset.data(j).seed).^2)]
 end
%{
%}
 p=0.9;

dset.ns = 16;
dset.siz = [72 64];
dset.siz = [32 32];
numpix = prod(dset.siz);
dset.data = struct([]);

for j = 2:2%1 : 16
    if j<10
        nn=['00' num2str(j)];
    else
        nn=['0' num2str(j)];
    end
    a = dir(['FaceH2/' nn '*.jpg']);
    
    dset.data(j).n = length(a)-1;
    dset.data(j).nbs = zeros(numpix,length(a));
    dset.data(j).Vx = zeros(numpix,length(a)-1);
    dset.data(j).Vy = zeros(numpix,length(a)-1);
    dset.data(j).w = ones(1,length(a)-1);        
    for k = 1 : length(a)
        bb = imread(['FaceH2/' a(k).name]);
        cc = double(rgb2gray(imresize(bb,dset.siz)))/255;
        dset.data(j).nbs(:,k) = reshape(cc/(100*std(cc(:),1)),numpix,1);
        dset.data(j).nbs(:,k) = dset.data(j).nbs(:,k) - mean(dset.data(j).nbs(:,k))+0.5;
    end

    % find center
    [~, pos] = min( sum(bsxfun(@minus,dset.data(j).nbs,mean(dset.data(j).nbs,2)).^2));
    dset.data(j).seed = dset.data(j).nbs(:,pos);
    dset.data(j).nbs(:,pos)=[];

    % data selection
    % vector field
    for k = 1 : length(a)-1
        [vx ,vy] = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,k),dset.siz), reshape(dset.data(j).seed,dset.siz),para);
        dset.data(j).Vx(:,k) = vx(:);
        dset.data(j).Vy(:,k) = vy(:);
    end
[B0, evs] = dm_init_basis(dset, p);
[Bs{i}, Alpha{i}] = dm_train(dset, B0, maxiter, tol);

end


%%
%L2 test
end

%1) check one on one warping
figure
kk=10;
colormap gray
subplot(1,3,1)
imagesc(reshape(dset.data(j).seed,dset.siz))
subplot(1,3,2)
 tmp = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,kk),dset.siz), reshape(dset.data(j).seed,dset.siz),para);
 [vx,vy] = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,kk),dset.siz), reshape(dset.data(j).seed,dset.siz),para);
imagesc(tmp)
subplot(1,3,3)
imagesc(reshape(dset.data(j).nbs(:,kk),dset.siz))

%2) check one on one direct transfer
bb = imread('FaceH2/001_00001.jpg');
cc = double(imresize(rgb2gray(bb),dset.siz))/255;
testimg = reshape(cc/(100*std(cc(:),1)),numpix,1);
testimg = testimg-mean(testimg)+0.5;
figure
kk=10;
colormap gray
subplot(1,3,1)
imagesc( reshape(testimg,dset.siz))
subplot(1,3,2)
 tmp = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,kk),dset.siz), reshape(testimg,dset.siz),para);
 [vx,vy] = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,kk),dset.siz), reshape(testimg,dset.siz),para);
imagesc(tmp)
subplot(1,3,3)
imagesc(reshape(dset.data(j).nbs(:,kk),dset.siz))


%3) Basis transfer independently

% find nearest
[~, pos] = min( sum(bsxfun(@minus,dset.data(j).nbs,testimg).^2));

x=dset.siz(1);y=dset.siz(2);
[xorg,yorg]=meshgrid(0.5:1:y-0.5,0.5:1:x-0.5);
 [vx ,vy] = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,kk),), reshape(dset.data(j).nbs(:,pos),dset.siz),para);
 tmp = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,k),), reshape(dset.data(j).seed,dset.siz),para);
%max(abs(vx(:)))
 vx = reshape(dset.data(1).Vx(:,20),);
 vy = reshape(dset.data(1).Vy(:,20),);

 norgx = xorg - vx;
 norgy = yorg - vy;
 tmp1 = interp2(xorg,yorg,reshape(dset.data(j).nbs(:,20),),norgx,norgy);
 tmp1(isnan(tmp1))=0;

warp=dm_solve(Bs{1},reshape(dset.data(j).nbs(:,k),), reshape(dset.data(j).seed,dset.siz),1e-5);

 y = deform_img(reshape(dset.data(j).seed,), Bs{1}, Alpha{i}(:,20));

for i =1:9
subplot(3,3,i)
imagesc(tmp{i})
colormap gray
[i,mean(tmp{i}(:)),std(tmp{i}(:),1),max(tmp{i}(:)),min(tmp{i}(:))]
end

