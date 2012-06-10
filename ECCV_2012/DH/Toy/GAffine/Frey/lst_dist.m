function y = lst_dist(index)
addpath('/home/donglai/Desktop/ECCV/eccv12_codes')
addpath('../t_data')
as = 0.01:0.01:0.5;
Ks=[3,10,25,50];
kk = floor(index/100);
ll = index-kk*100;
mm = floor(ll/50);
K = Ks(1+kk);
alpha = as(1+ll-mm*50);

eval(['load ../../Data/Frey/f_' num2str(kk+1)])
thres = mean(ddd(:))-mm*0.3;
ratio = 0.5;
minWidth = 7;
nOuterFPIterations = 10;
nInnerFPIterations = 3;
nSORIterations = 50;
para = [alpha,ratio,minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations];

Bs = cell(1,K);
Alpha = cell(1,K);
p = 0.9;
tol = 1e-3;
maxiter = 100;
x=30;y=38;
[xorg,yorg]=meshgrid(0.5:1:y-0.5,0.5:1:x-0.5);
for i = 1 : K
    seed = [i, setdiff(find(ddd(i,:)<thres),i) ];
    dset.ns = length(seed);
    dset.siz = [30 38];
    dset.data = struct([]);
    bad = [];
    for j = 1 : dset.ns
        ind = setdiff(find(IDX==seed(j)),ctrs(seed(j)));
        if ~isempty(ind)
        dset.data(j).n = length(ind);
        if j ==1
            tmp1 = reshape(face_train(:,ctrs(i)),dset.siz);
        else
            [vx,vy] = Coarse2FineTwoFrames( reshape(face_train(:,ctrs(seed(j))),30,38), reshape(face_train(:,ctrs(seed(1))),30,38),para);
            norgx = xorg - vx;
            norgy = yorg - vy;
            tmp1 = interp2(xorg,yorg,reshape(face_train(:,ctrs(seed(j))),30,38),norgx,norgy);
            tmp1(isnan(tmp1))=0;
        end
        dset.data(j).seed = tmp1(:);
        dset.data(j).nbs = zeros(1140,length(ind));
        dset.data(j).Vx = zeros(1140,length(ind));
        dset.data(j).Vy = zeros(1140,length(ind));
        dset.data(j).w = ones(1,length(ind));        
        for k = 1 : length(ind)
            if j==1
                [tmp2]= Coarse2FineTwoFrames( reshape(face_train(:,ind(k)),30,38), reshape(face_train(:,ctrs(i)),30,38),para);
            else
                %proprogation
                tmp2 = interp2(xorg,yorg,reshape(face_train(:,ind(k)),30,38),norgx,norgy);
                tmp2(isnan(tmp2))=0;
            end
            dset.data(j).nbs(:,k) = tmp2(:);
            [vx,vy] = Coarse2FineTwoFrames( tmp2, tmp1,para);
            dset.data(j).Vx(:,k) = vx(:);
            dset.data(j).Vy(:,k) = vy(:);
        end
    else
        bad=[bad,j];
    end
    end
    dset.ns=dset.ns-length(bad);
    dset.data(bad)=[];

    [B0, evs] = dm_init_basis(dset, p);
    [Bs{i}, Alpha{i}] = dm_train(dset, B0, maxiter, tol);
end
numtest = size(face_t,2);
numtrain = size(face_r,2);
dis_lt = zeros(1,numtest);
dis_mat= zeros(K,numtest);
pp_mat= zeros(K,numtest);
for i = 1 : numtest
    for j = 1 : K
        warp=dm_solve2(Bs{j},reshape(face_train(:,ctrs(j)),30,38),reshape(face_t(:,i),30,38));    
        dis_mat(j,i) =  sum((warp(:)-face_t(:,i)).^2,1);
        pp_mat(j,i) =  -10*log10(mean((warp(:)-face_t(:,i)).^2));
    end
    i
end

mean( min(dis_mat))
mean( max(pp_mat))

eval(['save ../../Data/Frey/lst' num2str(K) '/BB_' num2str(ll)])
end

