load cc2
a=reshape(ntrain4(cc(83),:),28,28);
subplot(1,2,1)
imagesc(a')

shx=0.8;shy=0.1;
mat=[1,shx,0;shy,1+shx*shy,0;0,0,1];
                tform = maketform('affine',mat);
                                %if max(abs([mat(1,1),mat(2,2)]))<1.2
                                                tmp2 = imtransform(a,tform);  
subplot(1,2,2)
                imagesc(tmp2')







[aa,bb]=Align(ntrain4(cc(2:100),:),ntrain4(cc(1),:));
