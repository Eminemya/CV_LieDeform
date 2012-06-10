load cc2

sq=sqrt(size(ntrain4,2));
cindex={};                
dd=1;
%scale the bb
sntrain4=zeros(length(cc),size(ntrain4,2));
for i=1:length(cc)
   sntrain4(i,:)=f_bb2(reshape(ntrain4(cc(i),:),sq,sq),sq)';
end
l2norm=sum(sntrain4.^2,2)';
index=1:length(cc)-1;
thres=0.05;

cindex{dd}=[];
in={};
img={};
%ee=1;
tmp=reshape(ntrain4(cc(1),:),sq,sq);
    for rot=[-30:10:30]
        tmpp=imrotate(tmp,rot,'crop');
        for shx=-1:0.2:1
            for shy=-1:0.2:1
                if abs(shx*shy)<0.3
                mat=[1,shx,0;shy,1+shx*shy,0;0,0,1];
                tform = maketform('affine',mat);
                tmp2 = imtransform(tmpp,tform);   
                % 2) moving bbox around
                target=f_bb2(tmp2,sq);
                if length(target)>0
                     tmpbest=IDM7(sntrain4(index,:)',target);
                     rr=find(tmpbest./l2norm(index)<thres);
                    if length(rr)>0
                        cindex{dd}=[cindex{dd},index(rr)];
                        index(rr)=[];
                        %in{ee}=index(rr);
                        %img{ee}=reshape(target,sq,sq);
                        %ee=ee+1;
                     end
                end
                end
            end
        end
    end

%{

in2=in;
for i=1:length(in2)
for ii=1:length(in2{i})
in{i}(ii)=find(cc==in2{i}(ii));
end

end

figure
for i=1:length(in)
        subplot(length(in),10,1+(i-1)*10)
        imagesc(img{i})
    for j=1:length(in{i})
        subplot(length(in),10,1+j+(i-1)*10)
        imagesc(reshape(sntrain4(in{i}(j),:),sq,sq))
    end
end

%}
