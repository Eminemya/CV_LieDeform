function [tem1,imgs,theta]=Rotate(imgs)


addpath('../GAffine')
num_img=size(imgs,1);
sq=sqrt(size(imgs,2));
rot_set=-30:5:30;
len=length(rot_set);
newimgs=zeros([size(imgs),ll]);
mid=(ll+1)/2;
for i=1:num_img
    tmp=reshape(imgs(i,:),sq,sq);
    for j=setdiff(1:ll,mid)
        tmpp=imrotate(tmp,rot_set(j),'crop');
        newimgs(i,:,j)=f_bb2(tmpp,sq)';
    end
    newimgs(i,:,mid)=f_bb2(tmp,sq)';
end

imgs=newimgs(:,:,mid);



%1) Modeling : how to trade-off different likelihood terms (scale)

%1.1) Model 1: 
%known: sig_rot=45,noise=0.1
%unknown: tem,theta_i

%Learning
%initialization
tem1=mean(imgs);
theta1=zeros(1,num_img);
Lik1=zeros(1,num_img);
img1=imgs;
sig_rot=10;
sig_img=0.2;
%until convergence
thres=1e-5;
Lik=0;
for i =1:num_img
Lik1(i)=log(normpdf(theta1(i),0,sig_rot))+sum(log(normpdf(imgs(i,:),tem1,sig_img)));
end

Lik=sum(Lik1);
preLik=0;
iter=1;
while abs(Lik-preLik)<thres
    preLik=Lik;
%given the template, max rotate
for i=1:num_img
    for j=1:length(rot_set)
        tmp=sum(log(normpdf(newimgs(i,:,j),tem1,sig_img)))+log(normpdf(rot_set(j),0,sig_rot));
        if tmp>Lik(i)
            Lik1(i)=tmp;
            theta1(i)=j;
            imgs(i,:)=newimgs(i,:,j);
        end
    end
end
%given rotation,max template

tem1=mean(imgs,3);
Lik=sum(Lik1);
[iter,Lik]
iter=iter+1;

end



end
