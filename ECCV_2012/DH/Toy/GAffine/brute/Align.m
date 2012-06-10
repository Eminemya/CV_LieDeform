function [ww2,y]=Align(arr,target)

y=zeros(size(arr));
ww2=zeros(1,size(arr,1));
sq=sqrt(size(arr,2));
                
                tmp2=reshape(target,sq,sq);
                [aa,bb]=ind2sub(size(tmp2),find(tmp2));   
                cc=[min(aa),max(aa),min(bb),max(bb)];
                lenx=cc(2)-cc(1)+1;
                leny=cc(4)-cc(3)+1;
                tmp2=imresize(tmp2(cc(1):cc(2),cc(3):cc(4)),[28,floor(28*leny/lenx)]);
                target=reshape(tmp2,1,sq*sq);

for i = 1 : size(arr,1)
    tmp=reshape(arr(i,:),sq,sq);
    
    best=IDM7(arr(i,:)',target');
    newarr=tmp;
    
    % 1) area preserving 
    for rot=[-30:10:30]
        tmpp=imrotate(tmp,rot,'crop');
        for shx=-1:0.2:1
            for shy=-1:0.2:1
                if abs(shx*shy)<0.3
                %mat=[cos(rot),-sin(rot),0;sin(rot),cos(rot),0;0,0,1]*[1,shx,0;shy,1+shx*shy,0;0,0,1];
                mat=[1,shx,0;shy,1+shx*shy,0;0,0,1];
                tform = maketform('affine',mat);
                %if max(abs([mat(1,1),mat(2,2)]))<1.2
                tmp2 = imtransform(tmpp,tform);   
                % 2) moving bbox around
                [aa,bb]=ind2sub(size(tmp2),find(tmp2));   
                cc=[min(aa),max(aa),min(bb),max(bb)];
                lenx=cc(2)-cc(1)+1;
                leny=cc(4)-cc(3)+1;
                if lenx<=28 &&leny<=lenx
                %ly=[max(1,floor((sq-leny)/2)-2),min(floor((sq-leny)/2)+2,sq-leny+1),leny-1];
                %lx=[max(1,floor((sq-lenx)/2)-2),min(floor((sq-lenx)/2)+2,sq-lenx+1),lenx-1];
                %ly=[max(1,floor((sq-leny)/2)),min(floor((sq-leny)/2)+2,sq-leny+1),leny-1];
                %lx=[max(1,floor((sq-lenx)/2)),min(floor((sq-lenx)/2)+2,sq-lenx+1),lenx-1];
                tmp2=imresize(tmp2(cc(1):cc(2),cc(3):cc(4)),[28,floor(28*leny/lenx)]);
                
                %scale down will lead to degeneration because of different prototypes...
                %{
                if leny>lenx
                    tmp2=imresize(tmp2(cc(1):cc(2),cc(3):cc(4)),20/leny);
                    lenx=size(tmp2,1);
                    lx=[floor((sq-lenx)/2)-3,floor((sq-lenx)/2)+3,lenx-1];
                    ly=[3,7,19];
                else
                    %rare..
                    tmp2=imresize(tmp2(cc(1):cc(2),cc(3):cc(4)),20/lenx);
                    leny=size(tmp2,2);
                    ly=[floor((sq-leny)/2)-3,floor((sq-leny)/2)+3,leny-1];
                    lx=[3,7,19];
                end
                %}
                l=size(tmp2,2);
                ll=max(1,floor((sq-l)/2));
                new=zeros(sq);
                new(:,ll:l+ll-1)=tmp2;                        
                %new(lx(1):lx(1)+lx(3),ly(1):ly(1)+ly(3))=tmp2;                        
                tmpbest=IDM7(reshape(new,sq*sq,1),target');
                if tmpbest<best
                      best=tmpbest;
                      newarr=new;        
                      pp=[rot,shx,shy]
                 end
                 %small shift will be considered within perturbation
                %{
                 for sx=lx(1):lx(2)
                    for sy=ly(1):ly(2)
                        new=zeros(sq);
                        new(sx:sx+lx(3),sy:sy+ly(3))=tmp2;                        
                        tmpbest=sum((new(:)'-target).^2);
                        if tmpbest<best
                            best=tmpbest;
                            newarr=new;        
                            %pp=[rot,shx,shy];
                        end
                    end
                end
                %}
                
                end
                end
            end
        end 
    end
    y(i,:)=newarr(:);
    ww2(i)=best;    
end


end


