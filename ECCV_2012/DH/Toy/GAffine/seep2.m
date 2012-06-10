%see3(tindex2,cindex2,cc2,'sntrain4','ntrain4','scale2')
function y=seep2(tt,dd,ind , name,trans_ind)



len=length(ind);
Res = 'y';
cc=0;
ll=sqrt(size( name ,3));
mid=(1+size( name ,2))/2;

while (Res=='y'&&cc*10<len)

%clear out
for j=1:100
subplot(10,10,j)
imagesc(zeros(1));
axis off
end
%comparision
for j=1:min(10,len-cc*10)
subplot(10,10,j*10-9)
a=reshape( name (ind(j+cc*10),mid,:),ll,ll)';
imagesc(a)
axis off
%title(num2str(dd(j)))

for jj=1:min(9,length(dd{j+cc*10}))
subplot(10,10,j*10-9+jj)
%[j+cc*10,length(dd),length(tt)]
%[dd{j+cc*10}(jj),tt{j+cc*10}(jj)]
a=reshape( name (dd{j+cc*10}(jj),tt{j+cc*10}(jj),:),ll,ll)';
%{
if sum(tt{j+cc*10}(jj,2:3)~=0)>0
    shx=-tt{j+cc*10}(jj,2);
    shy=-tt{j+cc*10}(jj,3);
    mat=[1+shx*shy,shx,0;shy,1,0;0,0,1];
    tform = maketform('affine',mat);
    a  = imtransform(a,tform);                                
end
if tt{j+cc*10}(jj,1)~=0
a=imrotate(a,-tt{j+cc*10}(jj,1),'crop');
end
%}
%imagesc(reshape(f_bb3(a,ll,0.6),ll,ll))
imagesc(reshape(a,ll,ll))
title(['affine ' num2str(trans_ind(:,tt{j+cc*10}(jj))')])
axis off
%title(num2str(ind{j+cc*10}(jj)))
end

end

cc=cc+1;
Res = input('(y/n)  ', 's');
end
close 
end
