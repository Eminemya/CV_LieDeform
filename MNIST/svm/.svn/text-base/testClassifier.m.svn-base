clear;
close all;
clc;


load C:\Users\yichangshih\Desktop\sanskrit\newdata\test.mat;
data = imgs;
load C:\Users\yichangshih\Desktop\sanskrit\newdata\group.mat;
[aa,bb]=sort(group(:,1),'ascend');
group = group(bb,: );

load C:\Users\yichangshih\Desktop\sanskrit\newdata\knnlabel.mat;
load C:\Users\yichangshih\Desktop\sanskrit\newdata\ham_label.mat;

[Testing Group_gnd] = getFeatures(data);

%-----------------------------------------------------
%   Learning and Learning Parameters
c = 1000;
lambda = 1e-7;
kerneloption= 2;
kernel='poly';
verbose = 0;
nbclass = 5 ; 

%--------------------------------------------------
coarseLabel = knnlabel;
coarseLabel = ham_label;
%coarseLabel = Group_gnd;

correct = 0 ; 



load classifiers;
for i = 1 : length(data)
    
    xsup = classifiers(coarseLabel(i)).xsup;
    w = classifiers(coarseLabel(i)).w;
    b = classifiers(coarseLabel(i)).b;
    nbsv = classifiers(coarseLabel(i)).nbsv;
    
    [fineLabel , maxi] = svmmultivaloneagainstone(Testing(i,:) ,xsup,w,b,nbsv, kernel ,kerneloption);
    fineLabelOrig = group(coarseLabel(i), fineLabel );
    if( fineLabelOrig == Group_gnd(i))
        correct = correct + 1 ; 
    end
    i
end

correct/length(data)
