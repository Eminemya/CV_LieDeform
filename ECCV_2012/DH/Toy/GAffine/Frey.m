addpath('/home/donglai/Desktop/ECCV/eccv12_codes'
load frey_rawface
face=double(ff)/255;

%see(reshape(face(:,1),20,28))


mean(sum(bsxfun(@minus,face,face(:,1)).^2,1))

numtrain=200;%1465;
numtest=50;%500;
K=10;
train=randsample(1965,numtrain);
test= randsample(setdiff(1:1965,train),numtest);


[IDX, C] = kmeans(face(:,train)', K);
[aa,bb] = histc(IDX,1:K);
%i=20;see2(find(IDX==i),face(:,train));
face_r = zeros(1140,numtrain);
for i = 1 : numtrain
    tmp = padarray( reshape(face(:,train(i)),20,28) , [5 5]);    
    face_r(:,i) = tmp(:);
end
face_t = zeros(1140,numtest);
for i = 1 : numtest
    tmp = padarray( reshape(face(:,test(i)),20,28) , [5 5]);    
    face_t(:,i) = tmp(:);
end


ctrs=zeros(1,K);
dd=pdist2(C,C);
thres=2.5;
for i = 1 : K
    ind = find (IDX==i);
    [~ , pos ] = min(sum(bsxfun(@minus,face(:,train(ind)),C(i,:)').^2,1));
    ctrs(i) = ind(pos);
end

seep_f(ctrs,IDX,face_r')
alpha = 0.05;
ratio = 0.5;
minWidth = 7;
nOuterFPIterations = 10;
nInnerFPIterations = 3;
nSORIterations = 50;
para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];

Bs = cell(1,K);
Alpha = cell(1,K);
p = 0.9;
tol = 1e-2;
maxiter = 1000;
x=30;y=38;
[xorg,yorg]=meshgrid(0.5:1:y-0.5,0.5:1:x-0.5);
%sum((tmp1(:)-face_r(:,ctrs(seed(j)))).^2)
%sum((tmp1(:)-face_r(:,ctrs(seed(1)))).^2)
for i = 1 : K
    seed = [i, setdiff(find(dd(i,:)<thres),i) ];
    dset.ns = length(seed);
    dset.siz = [30 38];
    dset.data = struct([]);

    for j = 1 : dset.ns
        ind = setdiff(find(IDX==seed(j)),ctrs(seed(j)));
        dset.data(j).n = length(ind);
        if j ==1
            tmp1 = reshape(face_r(:,ctrs(i)),dset.siz);
        else
            %[vx,vy] = Coarse2FineTwoFrames2( reshape(face_r(:,ctrs(i)),30,38), reshape(face_r(:,ctrs(seed(j))),30,38),para);
            %tmp = Coarse2FineTwoFrames2( reshape(face_r(:,ctrs(i)),30,38), reshape(face_r(:,ctrs(seed(j))),30,38),para);
            [vx,vy] = Coarse2FineTwoFrames( reshape(face_r(:,ctrs(seed(j))),30,38), reshape(face_r(:,ctrs(seed(1))),30,38),para);
            [new] = Coarse2FineTwoFrames( reshape(face_r(:,ctrs(seed(j))),30,38), reshape(face_r(:,ctrs(seed(1))),30,38),para);
            %[vx,vy,new] = Coarse2FineTwoFrames( reshape(face_r(:,ctrs(seed(1))),30,38), reshape(face_r(:,ctrs(seed(j))),30,38),para);
            %[vx,vy,new] = Coarse2FineTwoFrames( reshape(face(:,train(ctrs(seed(j)))),20,28), reshape(face(:,train(ctrs(seed(1)))),20,28),para);

            norgx = xorg - vx;
            norgy = yorg - vy;
            tmp1 = interp2(xorg,yorg,reshape(face_r(:,ctrs(seed(j))),30,38),norgx,norgy);
            tmp1(isnan(tmp1))=0;
        end
        dset.data(j).seed = tmp1(:);
        dset.data(j).nbs = zeros(1140,length(ind));
        dset.data(j).Vx = zeros(1140,length(ind));
        dset.data(j).Vy = zeros(1140,length(ind));
        dset.data(j).w = ones(1,length(ind));        
        for k = 1 : length(ind)
            if j==1
                [~,~,tmp2]= Coarse2FineTwoFrames( reshape(face_r(:,ind(k)),30,38), reshape(face_r(:,ctrs(i)),30,38),para);
            else
                %proprogation
                tmp2 = interp2(xorg,yorg,reshape(face_r(:,ind(k)),30,38),norgx,norgy);
                tmp2(isnan(tmp2))=0;
            end
            dset.data(j).nbs(:,k) = tmp2(:);
            [vx,vy] = Coarse2FineTwoFrames( tmp2, tmp1,para);
            dset.data(j).Vx(:,k) = vx(:);
            dset.data(j).Vy(:,k) = vy(:);
        end
    end
    [B0, evs] = dm_init_basis(dset, p);
    [Bs{i}, Alpha{i}] = dm_train(dset, B0, maxiter, tol);

end


%%
%L2 test


[dis_l2,index] = min(pdist2(face_r',face_t'));
tmp = pdist2(face_r',face_t');
[dis_l2,index] = min(tmp(randsample(1:numtest,10),:));
mean(dis_l2.^2)

%TD:
dis_mat= zeros(numtrain,numtest);
for i = 1 : numtrain
    proj=mtd(face_t,face_r(:,i));    
    %proj=mtd(face(:,test),face(:,train(i)));    
    dis_mat(i,:) =  sum((proj-face_t).^2,1);
end
dis_lt = min(dis_mat);
mean(dis_lt)

%TD learned
for i = 1 : K
    seed = [i];
    dset.ns = 1;
    dset.siz = [30 38];
    dset.data = struct([]);

    for j = 1 : dset.ns
        ind = setdiff(find(IDX==seed(j)),ctrs(seed(j)));
        dset.data(j).n = length(ind);
        tmp1 = reshape(face_r(:,ctrs(i)),dset.siz);
        dset.data(j).seed = tmp1(:);
        dset.data(j).nbs = zeros(1140,length(ind));
        dset.data(j).Vx = zeros(1140,length(ind));
        dset.data(j).Vy = zeros(1140,length(ind));
        dset.data(j).w = ones(1,length(ind));        
        for k = 1 : length(ind)
            if j==1
                [~,~,tmp2]= Coarse2FineTwoFrames( reshape(face_r(:,ind(k)),30,38), reshape(face_r(:,ctrs(i)),30,38),para);
            else
                %proprogation
                tmp2 = interp2(xorg,yorg,reshape(face_r(:,ind(k)),30,38),norgx,norgy);
                tmp2(isnan(tmp2))=0;
            end
            dset.data(j).nbs(:,k) = tmp2(:);
            [vx,vy] = Coarse2FineTwoFrames( tmp2, tmp1,para);

%CM:
dis_lt = zeros(1,numtest);
dis_mat= zeros(K,numtest);
for i = 1 : numtest
    for j = 1 : K
        warp=dm_solve(Bs{j},reshape(face_r(:,j),30,38),reshape(face_t(:,i),30,38));    
        dis_mat(j,i) =  sum((warp(:)-face_t(:,i)).^2,1);
    end
end
dis_lm = min(dis_mat);
mean(dis_lm)






