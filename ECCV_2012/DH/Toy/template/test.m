

%0) generate the data
% real template
tem=zeros(10);
tem(2:9,4:7)=1;


% distribution of the angles
num_img=100;
noise=0.1;
sig_rot=45;
theta=sig_rot*randn(1,num_img);

imgs=zeros(10,10,num_img);
%%%%%keep it smallllllllllllllllllll:binary, but a little artificial to truncate
%temptation of continuos gray image without loss of information

%generative: sgn(rot(tem+Normal Perturbation) - 0.5)
for i=1:num_img
    tmp=imrotate(tem,theta(i),'crop')+randn(10)*noise;
    %binarize->proba: match/mismatch
    tmp(tmp>=0.5)=1;
    tmp(tmp~=1)=0;
    %gray->distance:boltzmann
    imgs(:,:,i)=uint8(tmp);
end

save data_rot



%1) Modeling : how to trade-off different likelihood terms (scale)

%1.1) Model 1: 
%known: sig_rot=45,noise=0.1
%sig_rot1=sig_rot;
sig_rot1=1;
noise1=noise;
%unknown: tem,theta_i
rot_set=-90:10:90;

%Learning
%initialization
tem1=mean(imgs,3);
tem1(tem1>=0.5)=1;
tem1(tem1~=1)=0;
theta1=zeros(1,num_img);
Lik1=zeros(1,num_img);
img1=imgs;
%until convergence
thres=1e-5;
Lik=0;
for i =1:num_img
Lik1(i)=loglik(tem1,img1(:,:,i),noise1,1)+log(normpdf(theta1(i),0,sig_rot1));
end

while(abs(Lik-sum(Lik1))>thres)
Lik=sum(Lik1);
Lik
%given the template, max rotate
for i=1:num_img
    for j=rot_set
        tmpim=imrotate(imgs(:,:,i),j,'crop');
        tmp=loglik(tem1,tmpim,noise1,1)+log(normpdf(j,0,sig_rot1));
        if tmp>Lik1(i)
            Lik1(i)=tmp;
            theta1(i)=j;
            img1(:,:,i)=tmpim;
        end
    end
end
%given rotation,max template

tem1=mean(img1,3);
tem1(tem1>=0.5)=1;
tem1(tem1~=1)=0;

for i =1:num_img
    Lik1(i)=loglik(tem1,img1(:,:,i),noise,1)+log(normpdf(theta1(i),0,sig_rot));
end

end









