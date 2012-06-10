% This function, given a set of affine transforms, tries to find the
% bandwidth parameter which maximizes the likelihood under the
% invariant kernel of Miller and Chefd'hotel (see CVPR paper).
%
% A small amount of noise is added because the xfrms are likely to
% contain transforms that are exactly the same, due to the
% discretization of the parameter space. This noise keeps the
% bandwidth parameter from shrinking to zero.
%
% 
function kernelVar=bestKernelVar(xfrms)

n=size(xfrms,3);
xfrms=xfrms+rand(size(xfrms))*.1-.05;

kernelVar=1;

x2=xfrms(1:2,1:2,:);
for i=1:n
  x2inv(:,:,i)=x2(:,:,i)^-1;
  for j=1:n
    T=x2inv(:,:,i)*x2(:,:,j);
    invdets(i,j)=1/det(T);
    sqdists(i,j)=norm(logm(T),'fro')^2;
  end
end

ll=xfrmLeaveOneOut(xfrms,kernelVar,invdets,sqdists);

for iter=1:100
  ll_bigger=xfrmLeaveOneOut(xfrms,kernelVar*1.2,invdets,sqdists);
  ll_smaller=xfrmLeaveOneOut(xfrms,kernelVar*0.8,invdets,sqdists);
  if ll_bigger>ll
    kernelVar=kernelVar*1.2;
    ll=ll_bigger;
  else 
    if ll_smaller>ll
      kernelVar=kernelVar*0.8;
      ll=ll_smaller;
    else 
      break;
    end
  end
end

kernelVar
