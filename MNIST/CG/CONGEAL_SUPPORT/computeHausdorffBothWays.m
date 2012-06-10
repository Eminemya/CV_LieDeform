function [lh, rh] = computeHausdorffBothWays(a,b,dta,dtb,k)
% computeHausdorffBothWays  compute the kth partial Housdorff distance between a and b
%
%  [lh, rh] = computeHausdorffBothWays(a,b,k)
%  a and b must be binary images of the same size
%  k is a fraction between 0 and 1 (may be a 2 element vector if you want to use different
%     k for lh an rh)
%  lh is a to b and rh is b to a
%  
  lh = kthHausdorff(a, dtb, k(1));
  rh = kthHausdorff(b, dta, k(end));
