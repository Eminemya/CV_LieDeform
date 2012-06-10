clear
load mnist_all
sq=28;
coarse=21;
avg=0.6;
nn={'train','test'};
for jj=1:2
for kk=0:9
len=eval(['size(' nn{jj} num2str(kk) ',1);'])
eval(['e' nn{jj} num2str(kk) '=zeros(len,441);'])
for i=1:len
tmp=eval(['double(reshape(' nn{jj} num2str(kk) '(i,:),sq,sq))/255;']);
eval(['e' nn{jj} num2str(kk) '(i,:)=f_bb3(tmp,coarse,avg)'';'])
end

end
end

clear num aa bb L i jj kk len mm nn tmp
save l2_0_nn.mat

%pw distance

for kk=0:9
for ll=0:9
tmp=eval(['pdist2(double(etrain' num2str(ll) '),double(etest' num2str(kk) '),''euclidean'');']);
eval(['save data_l2_00/dis_' num2str(kk) '_' num2str(ll) ' tmp'])
[kk,ll]
end
end

%{
%part
b=cell(1,4);
[aa,bb]=meshgrid(1:17,1:17);b{1}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(1:17,10:26);b{2}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,1:17);b{3}=sub2ind([26,26],aa(:),bb(:));
[aa,bb]=meshgrid(10:26,10:26);b{4}=sub2ind([26,26],aa(:),bb(:));


for kk=0:4
for ll=0:9
%tmp=eval(['pdist2(double(strain' num2str(ll) '),double(stest' num2str(kk) '),''euclidean'');']);
tmp=0;
for mm=1:4
eval(['tmp' num2str(mm) '=pdist2(double(strain' num2str(ll) '(1:end/2,b{mm})),double(stest' num2str(kk) '(1:end/2,b{mm})),''euclidean'')+pdist2(double(strain' num2str(ll) '(end/2+1:end,b{mm})),double(stest' num2str(kk) '(end/2+1:end,b{mm})),''euclidean'');']);
end
eval(['save data_l2_D5/dis_' num2str(kk) '_' num2str(ll) ' tmp1 tmp2 tmp3 tmp4'])
%eval(['save data_l2_D5/dis_' num2str(kk) '_' num2str(ll) ' tmp'])
[kk,ll]
end
end


clear
load badlist
for ll=0:9
    eval(['train' num2str(ll) '(bbadd{ll+1},:)=[];'])
end

for kk=0:9
for ll=0:9
tmp=eval(['pdist2(double(train' num2str(ll) '),double(test' num2str(kk) '),''euclidean'');']);
eval(['save data_l2_00/dis_' num2str(kk) '_' num2str(ll) ' tmp'])
[kk,ll]
end
end

%}
