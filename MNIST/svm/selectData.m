close all;
clear;
clc;

load C:\Users\yichangshih\Desktop\sanskrit\newdata\train.mat;
data = imgs;
save trainingData data;

load C:\Users\yichangshih\Desktop\sanskrit\newdata\test.mat;
data = imgs;
save testingData data;