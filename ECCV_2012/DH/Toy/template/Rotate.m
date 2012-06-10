function [tem1,imgs,theta]=Rotate(newimgs,rot_set)

[num_img,y,ll]=size(newimgs);
sq=sqrt(y);

ll=length(rot_set);
imgs=zeros(num_img,y);
mid=(ll+1)/2;
imgs=squeeze(newimgs(:,:,mid));



%1) Modeling : how to trade-off different likelihood terms (scale)

%1.1) Model 1: 
%known: sig_rot=45,noise=0.1
%unknown: tem,theta_i

%Learning
%initialization
tem1=mean(imgs);
theta1=mid*ones(num_img,1);
Lik1=zeros(1,num_img);
img1=imgs;
sig_rot=50;
%sig_img=0.5;
%until convergence
thres=1e-5;
Lik=0;
lnorm2=squeeze(sum(newimgs.^2,2));
for i =1:num_img
%Lik1(i)=log(normpdf(theta1(i),0,sig_rot))+sum(log(normpdf(imgs(i,:),tem1,sig_img)));
Lik1(i)=log(normpdf(theta1(i),0,sig_rot))+IDM7(imgs(i,:)',tem1')/lnorm2(i,mid);
end

Lik=sum(Lik1);
preLik=0;
iter=1;
while abs(Lik-preLik)>thres
    preLik=Lik;
%given the template, max rotate
for i=1:num_img
    Lik1(i)=IDM7(newimgs(i,:,1)',tem1')/lnorm2(i,1)+log(normpdf(rot_set(1),0,sig_rot));
    for j=2:ll
        tmp=IDM7(newimgs(i,:,j)',tem1')/lnorm2(i,j)+log(normpdf(rot_set(j),0,sig_rot));
        if tmp>Lik1(i)
            Lik1(i)=tmp;
            theta1(i)=j;
            imgs(i,:)=newimgs(i,:,j);
        end
    end
end
%given rotation,max template

%tem1=mean(imgs);

best=sum(Lik1);
%gradient descend
nn=lnorm2( (0:1:(num_img-1))*ll+theta1');
rr=sum(log(normpdf(rot_set(theta1),0,sig_rot)));
step=0.1;
for i=1:y    
       tem1(i)=tem1(i)-step;
        if tem1(i)>=0
            tmp=sum(IDM7(imgs',tem1')./nn)+rr;
        else
            tmp=best-1;
        end

       if tmp<best
           tem1(i)=tem1(i)+2*step;
           if tem1(i)<=1
           tmp=sum(IDM7(imgs',tem1')./nn)+rr;
           else
               tmp=best-1;
           end
           if tmp<best
            tem1(i)=tem1(i)-step;
            else
            best=tmp;
            end
      else
          best=tmp;
       end
end

Lik=best;
[num2str(iter) ':  ' num2str(Lik)]
iter=iter+1;

end
std(theta1)
save align imgs
see2(1:size(imgs,1) , 'imgs','align')
figure;imagesc(reshape(tem1,sq,sq)')
end


%{
tmpimg=squeeze(newimgs(42,:,:))';
save rot tmpimg
see2(1:ll , 'tmpimg','rot')
%}

