
dset.ns = 16;
dset.siz = [72 64];
dset.siz = [32 32];
numpix = prod(dset.siz);
dset.data = struct([]);

h=fspecial('gaussian',dset.siz/2,3);

for j = 1 : 16
    if j<10
        nn=['00' num2str(j)];
    else
        nn=['0' num2str(j)];
    end
    a = dir(['FaceH/' nn '*.jpg']);
    
    dset.data(j).n = length(a)-1;
    dset.data(j).nbs = zeros(numpix,length(a));
    for k = 1 : length(a)
        bb = imread(['FaceH/' a(k).name]);
        cc = double(rgb2gray(imresize(bb,dset.siz)))/255;
        %{
        %}
        %dset.data(j).nbs(:,k) = reshape(cc-mean(cc(:))+0.5,numpix,1);
        %{
        dset.data(j).nbs(:,k) = .05/range(cc(:)) * (cc(:)-min(cc(:)));
        dset.data(j).nbs(:,k) = dset.data(j).nbs(:,k) - mean(dset.data(j).nbs(:,k))+0.5;
        %}

        %dset.data(j).nbs(:,k)=reshape(cc./imfilter(cc,h),numpix,1);
        dset.data(j).nbs(:,k) = cc(:);
        dset.data(j).nbs(:,k) = 0.5+0.1*(dset.data(j).nbs(:,k)-mean(dset.data(j).nbs(:,k)))/std(dset.data(j).nbs(:,k),1);
        
    end
end
ind = cellfun(@isempty,{dset.data.nbs});
dset.ns = 16 - sum(ind);
dset.data(ind==1)=[];




dismat=zeros(dset.ns);
labelmat=zeros(dset.ns,dset.ns,2);
for j = 1 : dset.ns
    for k = j+1 : dset.ns
        tmp = pdist2(dset.data(j).nbs',dset.data(k).nbs');
        [aa,bb] = min(tmp);
        [cc,dd] = min(aa);
        dismat(j,k)=cc;
        labelmat(j,k,1) = dd;%col
        labelmat(j,k,2) = bb(dd);%row
        labelmat(k,j,1) = bb(dd);%col
        labelmat(k,j,2) = dd;%row
    end
end


%if neg pixel?
%{
for j = 1 : 16
[j,min(dset.data(j).nbs(:))]
end
%}


% 7 center. 3 test
%minimax
src = 4; 
tar = 5;
sp=labelmat(tar,src,1);
tp=labelmat(tar,src,2);
testimg = dset.data(tar).nbs(:,tp);
%{
figure;
colormap gray
subplot(1,2,1)
imagesc(reshape(testimg,dset.siz))
subplot(1,2,2)
imagesc(reshape(dset.data(src).nbs(:,sp),dset.siz))
%}


%10 medoid
D = pdist2(dset.data(src).nbs',dset.data(src).nbs');
precenter=[sp,1,4,8,11,16,15];
K = length(precenter);
%see2(precenter,dset.data(src).nbs')
[label, center] = kmedoids(D,K,precenter);
%see2(center,dset.data(src).nbs')


SIFTflowpara.alpha=1*1;
SIFTflowpara.d=40*1;
SIFTflowpara.gamma=0.005*1;
SIFTflowpara.nlevels=4;
SIFTflowpara.wsize=2;
SIFTflowpara.topwsize=10;
SIFTflowpara.nTopIterations = 60;
SIFTflowpara.nIterations= 30;


tic;[vx,vy,energylist]=SIFTflowc2f(sift1,sift2,SIFTflowpara);toc

warpI2=warpImage(im2,vx,vy);


dset.data(src)=dset2.data;
rest = setdiff(1:dset.ns,src)
for j= 1:length(rest)
    [~, pos] = min( sum(bsxfun(@minus,dset.data(j).nbs,testimg).^2));

    dset.data(j).seed = dset.data(j).nbs(:,sp);
    dset.data(j).nbs(:,pos) = [];
    dset.data(j).n=size(dset.data(j).nbs,2);
    dset.data(j).w=ones(1,dset.data(j).n);
    for k = 1 : dset.data.n
        [vx ,vy] = Coarse2FineTwoFrames( reshape(dset.data(j).nbs(:,k),dset2.siz), reshape(dset.data(j).seed,dset2.siz),para);
        dset.data(j).Vx(:,k) = vx(:);
        dset.data(j).Vy(:,k) = vy(:);
end
[B0, evs] = dm_init_basis(dset, p);
[B2, A2] = dm_train(dset, B0, maxiter, tol);


tmps2=zeros([dset.siz,tp]);
for i = 2 : 10
 %tmps2(:,:,i) = deform_img(reshape(testimg,dset.siz), B2,A2{1}(:,center(i)))';
 % coordinate 1st order linear combine
 tmps2(:,:,i) = dm_solve(B2, reshape(testimg,dset.siz),  reshape(dset.data(src).nbs(:,center(i)),dset.siz),1e-5);
 tmp = tmps2(:,:,i);
 [i, max(abs(vx(:))),sum((tmp(:)-dset.data(src).nbs(:,center(i))).^2),sum((tmp(:)-testimg).^2)]
end


for i = 1 : K
subplot(10,4,4*i-3)
imagesc(reshape(dset.data(src).nbs(:,center(i)),dset.siz))
subplot(10,4,4*i-2)
imagesc(tmps(:,:,i))
subplot(10,4,4*i-1)
imagesc(tmps2(:,:,i))
subplot(10,4,4*i)
imagesc(reshape(testimg,dset.siz))
end
colormap gray







alpha = 0.035;
ratio = 0.5;
minWidth = 8;
nOuterFPIterations = 20;
nInnerFPIterations = 5;
nSORIterations = 30;
para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];

tmps0=zeros([dset.siz,tp]);
for i = 2 : K
 [vx ,vy] = Coarse2FineTwoFrames( reshape(dset.data(src).nbs(:,center(i)),dset.siz), reshape(dset.data(src).nbs(:,sp),dset.siz),para);
 tmps0(:,:,i) = Coarse2FineTwoFrames( reshape(dset.data(src).nbs(:,center(i)),dset.siz), reshape(dset.data(src).nbs(:,sp),dset.siz),para);
 tmp = tmps0(:,:,i);
 [i, max(abs(vx(:))),sum((tmp(:)-dset.data(src).nbs(:,center(i))).^2),sum((tmp(:)-dset.data(src).nbs(:,sp)).^2)]
end
for i = 1 : K
subplot(10,3,3*i-2)
imagesc(reshape(dset.data(src).nbs(:,center(i)),dset.siz))
subplot(10,3,3*i-1)
imagesc(tmps0(:,:,i))
subplot(10,3,3*i)
imagesc(reshape(dset.data(src).nbs(:,sp),dset.siz))
end


%{

% 1) direct matching
tmps=zeros([dset.siz,tp]);
for i = 2 : K
 [vx ,vy] = Coarse2FineTwoFrames( reshape(dset.data(src).nbs(:,center(i)),dset.siz), reshape(testimg,dset.siz),para);
 tmps(:,:,i) = Coarse2FineTwoFrames( reshape(dset.data(src).nbs(:,center(i)),dset.siz), reshape(testimg,dset.siz),para);
 tmp = tmps(:,:,i);
 [i, max(abs(vx(:))),sum((tmp(:)-dset.data(src).nbs(:,center(i))).^2),sum((tmp(:)-testimg).^2)]
end

for i = 1 : K
subplot(10,3,3*i-2)
imagesc(reshape(dset.data(src).nbs(:,center(i)),dset.siz))
subplot(10,3,3*i-1)
imagesc(tmps(:,:,i))
subplot(10,3,3*i)
imagesc(reshape(testimg,dset.siz))
end


addpath('/home/donglai/Desktop/ECCV/eccv12_codes')
%2) tangent space alone
p = 0.95;
maxiter = 100;
tol = 1e-3;
dset2 = dset;
dset2.ns = 1;
dset2.data([1:src-1,src+1:end])=[];
dset2.data(1).seed = dset2.data(1).nbs(:,sp);
dset2.data(1).nbs(:,sp) = [];
dset2.data(1).n=size(dset2.data(1).nbs,2);
dset2.data(1).w=ones(1,dset2.data(1).n);
for k = 1 : dset2.data.n
    [vx ,vy] = Coarse2FineTwoFrames( reshape(dset2.data(1).nbs(:,k),dset2.siz), reshape(dset2.data(1).seed,dset2.siz),para);
    dset2.data(1).Vx(:,k) = vx(:);
    dset2.data(1).Vy(:,k) = vy(:);
end
[B0, evs] = dm_init_basis(dset2, p);
[B2, A2] = dm_train(dset2, B0, maxiter, tol);


tmps2=zeros([dset.siz,K]);
for i = 2 : K
 %tmps2(:,:,i) = deform_img(reshape(testimg,dset.siz), B2,A2{1}(:,center(i)))';
 % coordinate 1st order linear combine

 tmps2(:,:,i) = dm_solve(B2, reshape(testimg,dset.siz),  reshape(dset.data(src).nbs(:,center(i)),dset.siz),1e-4);
 tmp = tmps2(:,:,i);
 [i, max(abs(vx(:))),sum((tmp(:)-dset.data(src).nbs(:,center(i))).^2),sum((tmp(:)-testimg).^2)]
end
figure
for i = 1 : K
subplot(10,4,4*i-3)
imagesc(reshape(dset.data(src).nbs(:,center(i)),dset.siz))
subplot(10,4,4*i-2)
imagesc(tmps(:,:,i))
subplot(10,4,4*i-1)
imagesc(tmps2(:,:,i))
subplot(10,4,4*i)
imagesc(reshape(testimg,dset.siz))
end


%3) shared tangent spaces

