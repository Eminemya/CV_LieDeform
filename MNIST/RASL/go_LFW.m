% Yigang Peng, Arvind Ganesh, November 2009. 
% Questions? abalasu2@illinois.edu
%
% Copyright: Perception and Decision Laboratory, University of Illinois, Urbana-Champaign
%            Microsoft Research Asia, Beijing
%
% Reference: RASL: Robust Alignment by Sparse and Low-rank Decomposition for Linearly Correlated Images  
%            Yigang Peng, Arvind Ganesh, John Wright, Wenli Xu, and Yi Ma. Proc. of CVPR, 2010.
%

% robust batch image alignment example

% clear
clc ;
clear all;
close all ;

% addpath
addpath RASL_toolbox ;
addpath data ;
addpath results ;

%% define images' path

currentPath = cd;

% input path
imagePath = fullfile(currentPath,'data','LFW') ;
pointPath = fullfile(currentPath,'data','LFW') ; % path to files containing initial feature(eye) coordinates
userName = 'Ariel_Sharon' ;
% one of 
% 'Gloria_Macapagal_Arroyo', 'Jennifer_Capriati', 'Laura_Bush',  
% 'Serena_Williams', 'Barack_Obama', 'Ariel_Sharon', 
% 'Arnold_Schwarzenegger', 'Colin_Powell', 'Donald_Rumsfeld',
% 'George_W_Bush', 'Gerhard_Schroeder', 'Hugo_Chavez',
% 'Jacques_Chirac', 'Jean_Chretien', 'John_Ashcroft',
% 'Junichiro_Koizumi', 'Lleyton_Hewitt', 'Luiz_Inacio_Lula_da_Silva', 
% 'Tony_Blair', 'Vladimir_Putin'

% output path
destRoot = fullfile(currentPath,'results') ;
destDir = fullfile(destRoot,userName) ;
if ~exist(destDir,'dir')
    mkdir(destRoot,userName) ;
end

%% define parameters

% dispaly flag
raslpara.DISPLAY = 1 ;

% save flag
raslpara.saveStart = 1 ;
raslpara.saveEnd = 1 ;
raslpara.saveIntermedia = 0 ;


% for face images
raslpara.canonicalImageSize = [ 80 60  ];
raslpara.canonicalEyeCoords = [ 5  55 ; ...
                                32 32  ];
                            
% parametric tranformation model
raslpara.transformType = 'AFFINE'; 
% one of 'TRANSLATION', 'SIMILARITY', 'AFFINE','HOMOGRAPHY'

raslpara.numScales = 1 ; % if numScales > 1, we use multiscales

% main loop
raslpara.stoppingDelta = .01; % stopping condition of main loop
raslpara.maxIter = 25; % maximum iteration number of main loops

% inner loop
raslpara.inner_tol = 1e-6 ;
raslpara.inner_maxIter = 1000 ;
raslpara.continuationFlag = 1 ;
raslpara.mu = 1e-3 ;
raslpara.lambdac = 1 ; % lambda = lambdac/sqrt(m)


%% Get training images

% get initial transformation
transformationInit = 'SIMILARITY';
[fileNames, transformations, numImages] = get_training_images( imagePath, pointPath, userName, raslpara.canonicalEyeCoords, transformationInit) ;


%% RASL main loop: do robust batch image alignment

[D, Do, A, E, xi, numIterOuter, numIterInner ] = rasl_main(fileNames, transformations, numImages, raslpara, destDir);

%% plot the results

layout.xI = 5 ;
layout.yI = 7 ;
layout.gap = 2 ;
layout.gap2 = 1 ;
rasl_plot(destDir, numImages, raslpara.canonicalImageSize, layout)
