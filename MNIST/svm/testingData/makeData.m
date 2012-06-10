close all;
clc; 
clear;


prefix = 'C:\Users\yichangshih\Desktop\sanskrit\data\test\';
prefix = 'C:\Users\yichangshih\Desktop\sanskrit\data\train\letter\bkk\0924\';
prefix = 'C:\Users\yichangshih\Desktop\sanskrit\data\train\letter\bkk\092E\';
prefix = 'C:\Users\yichangshih\Desktop\sanskrit\data\train\letter\bkk\092F\';

prefix001 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\1\';
prefix011 = 'C:\Users\yichangshih\Desktop\sanskrit\data\train_svm\11\';

data = struct( 'img', {} , 'label',{});

head = 1 ; 

imList001 = dir([prefix001 '*.png']);
for i = head : head + length(imList001)-1
    img{i} = imread([prefix001 imList001(i).name]);
    label{i} = 1;
end;
head = length(imList001);

imList011 = dir([prefix011 '*.png']);
for i = 1 :  length(imList011)
    img{i + head} = imread([prefix011 imList011(i).name]);
    label{i + head } = 11;
end;
head = length(imList011);

data = struct( 'img', img , 'label',label);
save data data