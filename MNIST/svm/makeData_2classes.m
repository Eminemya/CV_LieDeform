close all;
clc; 
clear;


prefix001 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\1\';
prefix011 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\11\';
prefix012 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\12\';
prefix013 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\13\';
prefix027 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\27\';
prefix033 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\33\';
prefix052 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\52\';

% so sorry for the confusing
prefix001 = prefix011;
prefix002 = prefix012;

imList001 = dir([prefix001 '*.png']);
imList002 = dir([prefix002 '*.png']);


k = 0.2;

%% Training data
img = {};
label = {};
data = struct( 'img', {} , 'label',{});
head = 0 ; 
% class1
for i = 1 : round( length(imList001)*k)
    img{i + head} = imread([prefix001 imList001(i).name]);
    label{i + head } = 1;
end;
head = round( length(imList001)*k);

% class2
for i = 1 :  round( length(imList002)*k)
    img{i + head} = imread([prefix002 imList002(i).name]);
    label{i + head } = -1;
end;
head = round( length(imList002)*k);


data = struct( 'img', img , 'label',label);
save trainingData data

%% Testing Data

img = {};
label = {};
data = struct( 'img', {} , 'label',{});
head = 0 ; 
% 001
for i = 1 : length(imList001)
    img{i + head} = imread([prefix001 imList001(i).name]);
    label{i + head } = 1;
end;
head = length(imList001);

% 011
for i = 1 :  length(imList002)
    img{i + head} = imread([prefix002 imList002(i).name]);
    label{i + head } = -1;
end;
head = length(imList002);


data = struct( 'img', img , 'label',label);
save testingData data