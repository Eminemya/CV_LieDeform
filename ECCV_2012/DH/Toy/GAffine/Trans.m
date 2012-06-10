function y=Trans(img,tran)


sq=sqrt(length(img));

tmp=reshape(img,sq,sq);


rot=tran(1);shx=tran(2);shy=tran(3);

if rot~=0
    tmp=imrotate(tmp,rot,'crop');
end

if shx~=0 || shy~=0
    mat=[1,shx,0;shy,1+shx*shy,0;0,0,1];
    tform = maketform('affine',mat);
    tmp = imtransform(tmp,tform,'XYScale',1);
end


y=f_bb3(tmp,21,0.6)';
end
