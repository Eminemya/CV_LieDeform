function A_test(digit)
eval(['load 60_300/ns_dis' num2str(digit)])
addpath('brute/')

%6) align test images
timg_a=cell(10,10);
dist_a=cell(10,10);

for tt=0:9
eval(['load data/c_test' num2str(tt)]);

for ttt=1:10
[trans,ind,dis]=Align3(strain(ttt,:),newtimgs,2,1);
for i=1:size(newtimgs,1)
    timg_a{tt+1,ttt}(i,:)=squeeze(newtimgs(i,trans(i),:));
end
dist_a{tt+1,ttt}=dis;
end



end

eval(['save ns_10test_2train' num2str(digit) '  timg_a dist_a']);


end

