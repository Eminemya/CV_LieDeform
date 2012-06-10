function bad=acc2(dis,labels,label,take)


[cc,dd]=max(histc(labels(dis(1:take,:)),0:9,1));

bad=find(dd~=label);

end
