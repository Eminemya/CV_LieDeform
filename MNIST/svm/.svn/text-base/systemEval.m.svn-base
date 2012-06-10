clear;
clc;
close all;


%% Training 
load 'trainingData.mat';
[Training Group] = getFeatures(data);

%-----------------------------------------------------
%   Learning and Learning Parameters
c = 1000;
lambda = 1e-7;
kerneloption= 2;
kernel='poly';
verbose = 0;

%---------------------One Against All algorithms----------------
nbclass=max(Group(:));

%[xsup,w,b,nbsv]=svmmulticlassoneagainstall(Training, Group,nbclass,c,lambda,kernel,kerneloption,verbose);

[xsup,w,b,nbsv,classifier,pos]=svmmulticlassoneagainstone(Training,Group,nbclass,c,lambda,kernel,kerneloption,verbose);
save classifier xsup w b nbsv classifier pos

%% Testing
load classifier
load 'testingData.mat';
[Testing Group_gnd] = getFeatures(data);



%[Group_test,maxi] = svmmultival(Testing,xsup,w,b,nbsv,kernel,kerneloption);
[Group_test,maxi] = svmmultivaloneagainstone(Testing,xsup,w,b,nbsv, kernel ,kerneloption);

%% Results 
sum( Group_test==Group_gnd)/length(Group_test)