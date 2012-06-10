addpath('../')

ns = [10,100,500,1000];
Ks = [3,10,25,50];
PP=zeros(4,4);

for ii = 1:4
    eval(['load f_' num2str(ii)])
    numtest=size(face_t,2);
    numtrain=size(face_train,2);

    oo=randsample(numtrain,Ks(ii));
    
    num_nb= floor(ns(ii)/Ks(ii));
	
 
   dis_mat=zeros(Ks(ii),numtest);
   pp_mat=zeros(Ks(ii),numtest);
    for jj=1:Ks(ii)
    % find nb:
    [aa,bb]=sort(sum((bsxfun(@minus,face_train,face_train(:,oo(jj))).^2)),'ascend');    
    [pc,score,latent] = princomp(face_train(:,bb(1:num_nb+1))');
    mm=mean(face_train(:,bb(1:num_nb+1)),2);
    test = bsxfun(@plus,(bsxfun(@minus,face_t,mm)'*pc(:,1:num_nb))*pc(:,1:num_nb)',mm')';
      dis_mat(jj,:) =  sum((test-face_t).^2,1);
      pp_mat(jj,:) = -10*log10(mean((test-face_t).^2));
     end
   PP(3,ii)=PP(3,ii)+mean(max(pp_mat)); %22.9796
   PP(1,ii)=PP(1,ii)+mean(min(dis_mat)); %5.6314


end
