addpath('../')


Ks = [3,10,25,50];
PP=zeros(4,4);

for tttt=1:20
for ii = 1:4

    eval(['load f_' num2str(ii)])
    numtest=size(face_t,2);
    numtrain=size(face_train,2);
    oo=randsample(numtrain,Ks(ii));
    
   n_t=face_t;
   n_r=face_train;

   n_t(1:120,:)=[];
   n_t(end-119:end,:)=[];
   n_r(1:120,:)=[];
   n_r(end-119:end,:)=[];

   dis_mat=zeros(Ks(ii),numtest);
   pp_mat=zeros(Ks(ii),numtest);
    xx=1;
    for i = oo'%1 : numtrain
        proj=mtd(n_t,n_r(:,i));
        %{
        proj=mtd(face_t,face_train(:,i));
             dis_mat(i,:) =  sum((proj-face_t).^2,1);
             pp_mat(i,:) = -10*log10(mean((proj-face_t).^2));
             %}
             proj(proj>1)=1;z
             proj(proj<0)=0;
             dis_mat(xx,:) =  sum((proj-n_t).^2,1);
             pp_mat(xx,:) = -10*log10(mean((proj-n_t).^2));
		xx=xx+1;
    end

    PP(3,ii)=PP(3,ii)+mean(max(pp_mat)); %22.9796
    PP(1,ii)=PP(1,ii)+mean(min(dis_mat)); %5.6314


    [dis_l2,index] = min(pdist2(face_train(:,oo)',face_t'));
    PP(2,ii)=PP(2,ii)+mean(dis_l2.^2); %6.2752

    %psnr
    %pp=zeros(numtrain,numtest);
    pp=zeros(Ks(ii),numtest);
    xx=1;
    for j = oo'%1 : numtrain
            pp(xx,:) = -10*log10(mean((bsxfun(@minus,face_t, face_train(:,j)).^2)));
            xx=xx+1;
        end
    PP(4,ii)=PP(4,ii)+mean(max(pp)) ;
end
tttt
end

PP/20

