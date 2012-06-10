function y=pca_l2(n1,n2,optt)
load mnist_all


len=eval(['size(train' num2str(n1) ',1)']);
if(optt==0)
[pc,score,latent] = princomp(eval(['[double(train' num2str(n1) ');double(train' num2str(n2) ')]']));
elseif(optt==1)
load mnist_edge_sobel
[pc,score,latent] = princomp(eval(['[[strain' num2str(n1) '(1:end/2,:),strain' num2str(n1) '(end/2+1:end,:)];[strain' num2str(n2) '(1:end/2,:),strain' num2str(n2) '(end/2+1:end,:)]]']));
elseif(optt==2)
load mnist_corner
[pc,score,latent] = princomp(eval(['[ctrain' num2str(n1) ';ctrain' num2str(n2) ']']));

elseif(optt==3)
load mnist_edge_canny
[pc,score,latent] = princomp(eval(['[etrain' num2str(n1) ';etrain' num2str(n2) ']']));

end


cumsum(latent(1:10))./sum(latent)
figure
hold on
plot3(score(1:len,1),score(1:len,2),score(1:len,3),'b.')
plot3(score(len+1:end,1),score(len+1:end,2),score(len+1:end,3),'r.')

%{
figure
hold on
plot3(score(1:len,1),score(1:len,2),score(1:len,3),'b.')
plot3(score(len+1:end,1),score(len+1:end,2),score(len+1:end,3),'r.')

plot(score(1:len,1),score(1:len,2),'b.')
plot(score(len+1:end,1),score(len+1:end,2),'r.')

%}
%{
hold on
num=2;
biplot(pc(:,1:num),'Scores',score(1:len,1:num),'Color','b')
biplot(pc(:,1:num),'Scores',score(len+1:end,1:num),'Color','r')
%}






tt=double(train5)/255;
new=double(test1)/255;
t2=bsxfun(@minus,double(tt),mean(tt,1));
C=(t2'*t2)/(size(tt,1)-1);
D=(tt'*tt)/(size(tt,1)-1);
[aa,bb]=eig(C);
[a,b]=eig(D);

[pc,score,latent] = princomp(tt);

num=700;
addpath('/home/donglai/Desktop/Sans/DH/Toy/GAffine')

bb=mean(tt,1)'+pc(:,1:num)*((new(1,:)-mean(tt,1))*pc(:,1:num))';
cc=pc(:,1:num)*(new(1,:)*pc(:,1:num))';

see(new(1,:))
see(bb)
see(cc)

find(cumsum(latent) >= 0.9 * sum(latent), 1)

%90 percent -> #K







end

