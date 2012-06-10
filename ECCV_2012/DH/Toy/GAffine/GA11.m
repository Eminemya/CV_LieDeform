function y=GA9(digit)
load mnist_all	

%0. preprocessing 
[numtrain,lendigit]=eval(['size(train' num2str(digit) ')']);
sq=sqrt(lendigit);

ntrain=zeros(numtrain,lendigit);
direction=zeros(numtrain,1);
G = fspecial('gaussian',[3 3],2);
bad=[];
coarse=21;
coarse2=coarse*coarse;
avg=0.6;
imgs=zeros(numtrain,coarse^2);
for i=1:numtrain
tmp=eval(['double(reshape(train' num2str(digit) '(i,:),sq,sq))/255;']);
%biggest connected component
pp=bwconncomp(tmp);
%throw it away since many bad situations that can't be told apart
if pp.NumObjects>1
bad=[bad,i];
else
%feature
%blur
%tmp2 = imfilter(tmp,G,'same');
%pca
%{
[aa,bb]=ind2sub([sq,sq],find(tmp>=0.1));%less noisy
pc= princomp([aa,bb]);
%keep both version...
    %y axis
    tmp2=imrotate(tmp,sign(pc(1)*pc(2))*180*acos(abs(pc(2)))/pi,'crop');
    %}
    tmp2=tmp;
imgs(i,:)=f_bb3(tmp2,coarse,avg)';
ntrain(i,:)=tmp(:);
end

end

imgs(bad,:)=[];
ntrain(bad,:)=[];
numtrain=numtrain-length(bad);


%save scale0 ntrain imgs l2norm
%see2(1:200,imgs)


%1) Reduction I: Local Perturbation

%guruantee the number in the first round to preserve variablity instead of using one same threshold
%ratio proportional to intensity?variance?
%upper bound
r_thres=0.07;
lc=100;
wrong=0;
while lc<300     
    r_thres=r_thres-0.01;    
    glabel=2:numtrain;
cc=[1];
cindex={};
while(length(glabel)>0)
    % imadjust...
    ratio=IDM8(imgs(glabel,:)',imgs(cc(end),:)')';
    %[aa,bb]=max(ratio);
    next=findnext(ratio,r_thres);
    if(max(ratio)<=r_thres)
        %done
        cindex{length(cc)}=glabel;
        glabel=[];
    else
        ind2=find(ratio<=r_thres);
        cindex{length(cc)}=glabel(ind2);
        cc=[cc,glabel(next)];
        glabel([next;ind2])=[];
    end
    [length(cc),length(glabel),length(ind2)]
end

if length(cc)>length(cindex)
    cindex{length(cc)}=[];
end

lc=length(cc)

end




%save scale1 cc cindex
%seep_bk(cc,cindex,'imgs','scale0')
%seep(cc,cindex,imgs)
%see2(1:length(cc),imgs(cc,:))
%see2(1:length(cindex{6}),imgs(cindex{6},:))


%2) Reduction II: Affine + peturbation
addpath('brute/')
rot_set=-60:5:60;
shear_set=0;%-0.5:0.5:0.5;
lr=length(rot_set);
lss=length(shear_set);
ll=lr*lss*lss;
trans_ind=[reshape(ones(lss*lss,1)*rot_set,1,ll);repmat(reshape(ones(lss,1)*shear_set,1,lss*lss),1,lr);repmat(shear_set,1,lss*lr)];
trans_s=trans_ind(1,:)+trans_ind(2,:)+4*trans_ind(3,:);

%for later 2d conversion
newimgs=zeros(lc,lr*lss*lss,coarse*coarse);

mid=(ll+1)/2;
nomid=setdiff(1:ll,mid);
for i=1:lc
%all angles
    tmp=reshape(ntrain(cc(i),:),sq,sq);
    for j=1:lr
        tmpp=imrotate(tmp,rot_set(j),'crop');
        %{
        for k=1:lss
            for kk=1:lss
                mat=[1,shear_set(k),0;shear_set(kk),1+shear_set(k)*shear_set(kk),0;0,0,1];
                tform = maketform('affine',mat);
                tmp2 = imtransform(tmpp,tform);  
                newimgs(i,(j-1)*lss*lss+(k-1)*lss+kk,:)=f_bb3(tmp2,coarse,avg)';
            end
        end
        %}
        newimgs(i,j,:)=f_bb3(tmpp,coarse,avg)';
    end
end


[cc2,cindex2,tindex2]=Findlm(newimgs,mid,r_thres);

lc2=length(cc2);
%IDM8(squeeze(newimgs(cc2(2),mid,:)),squeeze(newimgs(cc2(4),mid,:)))
%seep2(tindex2,cindex2,cc2,newimgs,trans_ind)
%seet2(newimgs(cc2,:,:),ones(1,lc2)*mid)
%see2(1:lc2,squeeze(newimgs(cc2,mid,:)))
%see2(1:ll,squeeze(newimgs(cc2(126),:,:)))


%save b_con3.mat
%3.2) clustering
%aligned a little bit
%[Aligned,g_tran,g_ind]=Congeal2(newimgs(cc2,:,:));
dis=zeros(lc2);
pos=ones(lc2)*mid;

for i=1:lc2
    noind=[1:i-1,i+1:lc2];
    tmp=reshape(IDM8(reshape(newimgs(cc2(noind),:,:),[],coarse2)',squeeze(newimgs(cc2(i),mid,:))),lc2-1,ll);
    [aa,tt]=min(tmp');
    dis(i,noind)=aa;
    pos(i,noind)=tt;
    i
end
%row major, not symmetric
lg=10;
[label, center] = kmedoids(dis, lg);
%i=1;ind=find(label==i);seet2(newimgs(cc2(ind),:,:),pos(center(i),ind))
%see2(1:lg,squeeze(newimgs(cc2(center),mid,:)))

%need to align 10 centers, do 1-medoid
%[label2, center2] = kmedoids(dis(center,center), 1);


%4) merge cc/cc2/ccindex/ccindex2
strain=zeros(numtrain,coarse2);
land1=1:lg;
land2=cell(1,lg);
land3=cell(1,lc2);
curr2=lg+1;
curr3=lc2+1;
aligned=squeeze(newimgs(cc2(center),mid,:));
for ii=1:lg

    lan=[center(ii),setdiff(find(label==ii),center(ii))];
    tran=pos(center(ii),lan);
    land2{ii}=curr2:(curr2+length(lan)-2);
    
    for i=1:length(lan)
        if i==1
            id=ii;
        else
            id=curr2;
            curr2=curr2+1;
        end
        strain(id,:)=squeeze(newimgs(cc2(lan(i)),tran(i),:));
        land3{id}=curr3;

        % direct pt3 
        kk=cc(cc2(lan(i)));
        for k=cindex{cc2(lan(i))}
            strain(curr3,:)=Trans(ntrain(k,:),trans_ind(:,tran(i)));
            curr3=curr3+1;
        end

        for jj=1:length(cindex2{lan(i)})
            j=cindex2{lan(i)}(jj);        
            t=tindex2{lan(i)}(jj);
          % can't concatenate ... should apply in sequence  
            strain(curr3,:)=Trans2(ntrain(cc(j),:),ntrain(kk,:),trans_ind(:,[t,tran(i)]));            
            curr3=curr3+1;
            for k=cindex{j}
                strain(curr3,:)=Trans2(ntrain(cc(j),:),ntrain(kk,:),trans_ind(:,[t,tran(i)]));            
                curr3=curr3+1;
            end
        end
        land3{id}=land3{id}:(curr3-1);
    end
end

dis_train=IDM8(strain(1:lc2,:)',strain');
%sum(cellfun(@length,land3))
%sum(sum(strain,2)~=0)
%find(sum(strain{ii},2)==0)
%see2(track{1},'strain','haha');

%5) train dist matrix
%load Align_l2.mat;IDM9(stest4{1}(110,:)',strain4(167,:)')

eval(['save ns_dis' num2str(digit) '  dis_train strain land1 land2 land3']);
eval(['save ns_alltrain' num2str(digit)])


%6) align test images
timg_a=cell(1,10);
trans_a=cell(1,10);
dist_a=cell(1,10);

for tt=0:9
eval(['load data/c_test' num2str(tt)]);

[trans,ind,dis]=Align3(aligned,newtimgs,2,1);
for i=1:size(newtimgs,1)
    timg_a{tt+1}(i,:)=squeeze(newtimgs(i,trans(i),:));
end

trans_a{tt+1}=trans;
dist_a{tt+1}=dis;

end

eval(['save ns_test_2train' num2str(digit) '  timg_a trans_a dist_a']);


end

