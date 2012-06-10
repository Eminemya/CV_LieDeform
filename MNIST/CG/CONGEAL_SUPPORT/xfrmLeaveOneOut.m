function loglike=xfrmLeaveOneOut(xfrms,kernelVar,invdets,sqdists)

n=size(xfrms,3);

loglike=0;
for i=1:n
  subtot=0;
  for j=1:n
    if i~=j
      subtot=subtot+1/kernelVar^2*invdets(i,j)^2*exp(-sqdists(i,j)/kernelVar);
    end
  end
  loglike=loglike+log(subtot);
end

 
 