

load train5

for i=1:size(train5,1)
[aa,bb]=ind2sub([28,28],find(train5(i,:)));
lx(i)=max(aa)-min(aa)+1;
ly(i)=max(bb)-min(bb)+1;
end



for i=1:10
    [i,sum(land2{i}==167)]
end


%L2 should not be good

%1.1) special
load data_l2_00/dis_8_6.mat
[tmp(1832,81),tmp(5096,81)] % [3.1666e+03,1.9680e+03]
load test_data_lp9_2/dis_8_6


load ns_dis6
see(strain(1832,:));see(strain(5096,:));

load data_l2_00/dis_8_8.mat
load ns_dis8
[tmp(3365,81),tmp(3973,81)] % [2.6808 , 1.5114]
see(strain(3365,:));see(strain(3973,:));

%if rot align...
%see_D0(8,0:9,1)
[tmp(1832,81),tmp(5096,81)]

%1.2) statistics




%every test
dis=cell(1,10);
for i=0:9
    %every train
    dis{i+1}=[];
    for j=0:9
        eval(['load data_l2_1/dis_' num2str(i) '_' num2str(j)])
        dis{i+1}(j+1,:)=min(tmp);
    end
end
save test_l2_na dis



rr=[];
ww=[];
for i=1:10
rr=[rr,dis{i}(i,:)];
ww=[ww,min(dis{i}([1:i-1,i+1:end],:))];
end


ran=[min(min(rr),min(ww)),max(max(rr),max(ww))];
ran=ceil(ran*10)/10;
[rv,~]=histc(rr,ran(1):0.1:ran(2));
[wv,~]=histc(ww,ran(1):0.1:ran(2));

%pdf
subplot(1,2,1)
hold on
plot(ran(1):0.1:ran(2),rv,'b-')
plot(ran(1):0.1:ran(2),wv,'r-')

%right val/dist
subplot(1,2,2)
hold on
dif=rr-ww;
plot(rr(dif<0),dif(dif<0),'b.')
plot(rr(dif>=0),dif(dif>=0),'r.')
plot(ran,[0,0],'k-','LineWidth',3)
axis equal
title('No Align')





load acc_num
lenn=[1,10,100,500,1000,2000,3000,4000,5000,10000];
cc=['b-';'r-';'bo';'ro'];
figure;
%hold on
for i=1:6
    semilogx(lenn,score(i,:),cc(ceil(i/3),:))
    hold on;
    semilogx(lenn,score(i,:),cc(2+ceil(i/3),:))
    hold on;
end

dd={'k--','g--','k>','g>'};
for i=1:4
    semilogx(lenn,score(i+6,:),dd{ceil(i/2)})
    hold on;
    semilogx(lenn,score(i+6,:),dd{2+ceil(i/2)})
    hold on;
end


