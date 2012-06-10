%gen img from patch
load scale0
tmpp=reshape(ntrain4(1,:),28,28);
ss=3;
step=2;
num=100;
tmp=cell(1,num);
for k=1:num
new=zeros(size(tmpp));
for i=1:floor(28/ss)
for j=1:floor(28/ss)
    indx=i*(ss-1)+1:i*ss;
    indy=j*(ss-1)+1:j*ss;
    rr=0;
    while rr==0
        ii=ceil(rand(1,2)*2*step-1);

        if indx(1)+ii(1)-step-1>=1 && indy(1)+ii(2)-step-1>=1 && indx(end)+ii(1)-step-1<=28 && indy(end)+ii(2)-step-1<=28        
        rr=1;
        end
    end
   %indx+ii(1)-5
   %indy+ii(2)-5
    patch = tmpp(indx+ii(1)-step-1,indy+ii(2)-step-1);
    new(indx,indy) = patch;
end
end
tmp{k}=new;
end
figure;
for k=1:num
subplot(10,10,k)
imagesc(tmp{k})
axis off
end


