function [trans,ind]=Align2(ref,imgs,l2norm,sq,thres)
ind=[];                
trans=[];                
%scale the bb
index=1:length(l2norm);

tmp=reshape(ref,sq,sq);
    for rot=[-30:10:-10,10:10:30]
        tmpp=imrotate(tmp,rot,'crop');
        for shx=-0.2:0.2:0.2%-1:0.2:1
            for shy=-0.2:0.2:0.2%-1:0.2:1
                %if abs(shx*shy)<0.3
                mat=[1,shx,0;shy,1+shx*shy,0;0,0,1];
                tform = maketform('affine',mat);
                tmp2 = imtransform(tmpp,tform);   
                % 2) moving bbox around
                target=f_bb2(tmp2,sq);
                if length(target)>0
                     tmpbest=IDM7(imgs(index,:)',target)';
                     rr=find(tmpbest./l2norm(index)<thres);
                    if length(rr)>0
                        ind=[ind,index(rr)];
                        trans=[trans;[rot,shx,shy]];
                        index(rr)=[];
                     end
                end
                %end
            end
        end
    end

end
