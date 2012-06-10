function [a] = readpgm(name)
%READPGM
% reads a pgm in to a matrix
%WARNING the pgm can not contain comment lines
% the pgm has to be in pgm raw form, and not ascii. use an editor
% to remove the comment lines
% for matlab, use x=readpgm('') where image.pgm is the image
% then k=mat2gray(x), then imshow(k) to display the image.


fn = fopen(name,'r');
[head] = fscanf(fn,'%c%d%d%d%d',5);
[a,count] = fread(fn,[head(3),head(4)],'uchar');

fclose(fn);
a=a';
