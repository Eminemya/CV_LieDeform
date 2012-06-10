function [Affine2by2, GX, Angles]=GetAffine2D(Pts1, Pts2, qq);
%%%%%% Pts1, Pts2 are 2-by-n1 and 2-by-n2 matrices.
%%%%%% Pts2= Affine2by2 x Pts1
if size(Pts1, 1) ~= 2
    Pts1=Pts1';
    if size(Pts1, 1) ~= 2
        disp(['Incorrect Input .. GetAffine2D Pause ... ']);
        pause;
    end
end
if size(Pts2, 1) ~= 2
    Pts2=Pts2';
    if size(Pts2, 1) ~= 2
        disp(['Incorrect Input .. GetAffine2D Pause ... ']);
        pause;
    end
end

N1=size(Pts1, 2);   N2=size(Pts2, 2);
mm1=mean(Pts1, 2);  PP1=Pts1-repmat(mm1, 1, N1);
mm2=mean(Pts2, 2);  PP2=Pts2-repmat(mm2, 1, N2);

[S1, S2]=Reduction(PP1, PP2);
X1=PP1(1, :);   Y1=PP1(2, :);
X2=PP2(1, :);   Y2=PP2(2, :);
%%% cubic moments
M1_3=[sum(X1.^3);sum(X1.^2.*Y1);sum(Y1.^2.*X1);sum(Y1.^3)]/N1;
M2_3=[sum(X2.^3);sum(X2.^2.*Y2);sum(Y2.^2.*X2);sum(Y2.^3)]/N2;
%% sample rotation angles 
theta=(0:qq:360)/180*pi;  n_angles=length(theta);
Angles=theta;
theta=[theta theta];
AA=cos(theta); BB=-sin(theta); CC=-BB; DD=AA;
CC(n_angles:end)=-CC(n_angles:end); DD(n_angles:end)=-DD(n_angles:end);
W2=inv(S2); W1=S1;
A=AA*W2(1)*W1(1)+BB*W2(1)*W1(2)+CC*W2(2)*W1(1)+DD*W2(2)*W1(2);
B=AA*W2(1)*W1(3)+BB*W2(1)*W1(4)+CC*W2(2)*W1(3)+DD*W2(2)*W1(4);
C=AA*W2(3)*W1(1)+BB*W2(3)*W1(2)+CC*W2(4)*W1(1)+DD*W2(4)*W1(2);
D=AA*W2(3)*W1(3)+BB*W2(3)*W1(4)+CC*W2(4)*W1(3)+DD*W2(4)*W1(4);

MM=[A.^3*M1_3(1)+3*A.^2.*B*M1_3(2)+3*A.*B.^2*M1_3(3)+B.^3*M1_3(4);
    A.^2.*C*M1_3(1)+(2*A.*B.*C + A.^2.*D)*M1_3(2)+(2*A.*B.*D+B.^2.*C)*M1_3(3)+B.^2.*D*M1_3(4);
    C.^2.*A*M1_3(1)+(2*C.*D.*A + C.^2.*B)*M1_3(2)+(2*C.*D.*B+D.^2.*A)*M1_3(3)+D.^2.*B*M1_3(4);    
    C.^3*M1_3(1)+3*C.^2.*D*M1_3(2)+3*C.*D.^2*M1_3(3)+D.^3*M1_3(4)];
KX=MM-repmat(M2_3, 1, size(MM, 2));
WW=1./(abs(M2_3)+0.0001);  WW=repmat(WW, 1, length(theta)); %%% Weights
GX=sum(abs(WW.*(KX)).^2, 1);
%GX=sum((KX).^2, 1);
[mm, id]=min(GX);       th=theta(id);

IDS=GetLocalMin(GX, mm);
%IDS=setdiff(IDS, id);
disp(['Number of Local Mins Checked ... ' num2str(length(IDS))]);

%RR=[cos(th) -sin(th); sin(th) cos(th)];
%if id > n_angles
%    RR=[cos(th) -sin(th); -sin(th) -cos(th)];
%end
Affine2by2=eye(2); %%inv(S2)*RR*S1;
Value=CheckQuality(Affine2by2, PP1(:, 1:10:end), PP2(:, 1:10:end));
    
flag=0;

for kk=1:length(IDS)
    th=theta(IDS(kk));
    RR=[cos(th) -sin(th); sin(th) cos(th)];
    if IDS(kk) > n_angles
        RR=[cos(th) -sin(th); -sin(th) -cos(th)];
    end
    AA=inv(S2)*RR*S1;
    vv=CheckQuality(AA, PP1(:, 1:10:end), PP2(:, 1:10:end));
    if vv < Value;
        Value=vv;
        Affine2by2=AA;
            if IDS(kk) > n_angles
                flag=1;
            end
    end
end
if flag==1
    disp(['Negative Determinant ... ']);
else
    disp(['Positive Determinant ... ']);
end

function [S1, S2]=Reduction(Pts1, Pts2)
%%%% P1 and P2 are normalized points.
%%%% S1 and S2 are the normalizing transforms
dd=sum(Pts1(1, :).*Pts1(2, :)) ;
C1=[sum(Pts1(1, :).*Pts1(1, :)) dd;dd sum(Pts1(2, :).*Pts1(2, :))];
dd=sum(Pts2(1, :).*Pts2(2, :));
C2=[sum(Pts2(1, :).*Pts2(1, :)) dd;dd sum(Pts2(2, :).*Pts2(2, :))];

[EV1, ev1]=eig(C1);  e1=diag(ev1); e1=1./sqrt(e1);
[EV2, ev2]=eig(C2);  e2=diag(ev2); e2=1./sqrt(e2);
S1=EV1*diag(e1)*EV1';
S2=EV2*diag(e2)*EV2';

function id=GetLocalMin(VV, mm);

n=length(VV);
WW=[VV(end) VV(1:n-1)];
UU=[VV(2:end) VV(1)];
id1=find(WW-VV > 0);
id2=find(UU-VV > 0);
id=intersect(id1, id2);

WW=VV(id);
[mm, ids]=sort(WW, 'ascend');
id=id(ids);
if length(id) > 3;
    id=id(1:3);
end


function Value=CheckQuality(AA, BB, CC);

BB=AA*BB;
b=sum(BB.^2, 1);
c=sum(CC.^2, 1);
hh=repmat(b, length(c), 1)+repmat(c', 1, length(b))-2*CC'*BB;
[mm, ids]=sort(hh, 'ascend');
[nn, xds]=sort(hh', 'ascend');
Value=mean(sqrt(mm(1, :)))+mean(sqrt(nn(2, :)));




