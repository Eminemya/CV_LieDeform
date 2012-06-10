load mnist_all


%training
for i=0:9

    dlmwrite([num2str(i) '.dat'], ['Training binary classifier for ' num2str(i)])
    %positive
    dd=eval(['train' num2str(i) ';']);

    for ii=1:size(dd,1)
        ind=find(dd(ii,:));
        [ind]
        dlmwrite([num2str(i) '.dat'], ['Training binary classifier for ' num2str(i)], '-append')
    end
    
    dlmwrite(filename, M, '-append')





end
