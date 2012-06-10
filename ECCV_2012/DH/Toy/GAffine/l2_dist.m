function l2_dist(index)
kk=floor(index/10);
ll=index-kk*10;
eval(['load ns_test_2train' num2str(kk)])
eval(['load ns_dis' num2str(kk)])
clear tmp
tmp=eval(['pdist2(strain,timg_a{' num2str(ll+1) '});']);

eval(['save data_l2_rot/dis_' num2str(kk) '_' num2str(ll) ' tmp'])

end

