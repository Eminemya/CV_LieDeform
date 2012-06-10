function loglike=xfrmLogLike(xfrm,xfrms,kernelVar)

xfrms=xfrms+rand(size(xfrms))*.1-0.5;
n=size(xfrms,3);

like=0;
for i=1:n
  x2=xfrms(1:2,1:2,i);
  xfrminv=xfrm(1:2,1:2)^-1;
  T=xfrminv*x2;
  invdet=1/det(T);
  sqdist=norm(logm(T),'fro')^2;
  like=like+1/kernelVar^2*invdet^2*exp(-sqdist/kernelVar);
end

loglike=log(like);

 
 