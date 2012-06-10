function y=Trans2(img,ref,tran)


sq=sqrt(length(img));

tmp=reshape(img,sq,sq);

for i=1:size(tran,2)
rot=tran(1,i);shx=tran(2,i);shy=tran(3,i);

if rot~=0
    tmp=imrotate(tmp,rot,'crop');
end

if shx~=0 || shy~=0
    mat=[1,shx,0;shy,1+shx*shy,0;0,0,1];
    tform = maketform('affine',mat);
    tmp = imtransform(tmp,tform,'XYScale',1);
end

if i==1
%align to bb of ref
    tmp=f_bb({tmp,reshape(ref,sq,sq)});    
end

end


y=f_bb3(tmp,21,0.6)';
end
