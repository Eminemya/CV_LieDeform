function y=align_p(index)
load cc2	
addpath('./brute/')
s = matlabpool('size');
if s==0
matlabpool
end

% algin...
kk=2+index*48:min(length(cc),index*48+49);
aligned=Align(ntrain4(cc(kk),:),ntrain4(cc(1),:));
eval(['save a' num2str(index) ' aligned kk'])
end



