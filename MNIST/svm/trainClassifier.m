close all;
clc; 
clear; 

load C:\Users\yichangshih\Desktop\sanskrit\newdata\train.mat;
data = imgs;
load C:\Users\yichangshih\Desktop\sanskrit\newdata\group.mat;
[aa,bb]=sort(group(:,1),'ascend');
group = group(bb,: );


%-----------------------------------------------------
%   Learning and Learning Parameters
c = 1000;
lambda = 1e-7;
kerneloption= 2;
kernel='poly';
verbose = 0;
nbclass = 5 ; 

matlabpool close;
matlabpool(8);

parfor i = 1 : 64
    % making training data for each group
    members = group(i,:);
    group_data_num = 1 ;
    groupData={};
    for m = 1 : 5 
        for d = 1 : length(data)
            if (data(d).label == members(m))
                groupData(group_data_num).img = data(d).img;
                groupData(group_data_num).label = m;
                groupData(group_data_num).originalLabel = members(m);
                group_data_num = group_data_num + 1;
            end
        end
    end
    
    [Training Group] = getFeatures(groupData);
    [xsup,w,b,nbsv,classifier,pos]=svmmulticlassoneagainstone(Training,Group,nbclass,c,lambda,kernel,kerneloption,verbose);
    
    classifiers(i).xsup = xsup;
    classifiers(i).w = w;
    classifiers(i).b = b;
    classifiers(i).nbsv = nbsv;
    classifiers(i).classifier = classifier;
    classifiers(i).pos = pos;
    i
end

save classifiers classifiers;