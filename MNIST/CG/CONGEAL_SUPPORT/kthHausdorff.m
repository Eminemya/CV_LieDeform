function res = kthHausdorff(mask, dt, k)
% kthHausdorff  returns the kth partial hausdorff distance between mask and dt image.
%
% res = kthHausdorff(mask, dt, k)
% mask and dt must be the same size, with mask binary and dt a distance transformed image
% mask and dt may have multiple channel, however.
% k should be a fraction between 0 and 1
% given to binary images a and b, the kth partial hausdorff distance is 
%   KH(a,b) = kth{a}(min{b}(|a-b|))


  d = dt(mask);
  % this is not efficient if length(d) is big... use hist instead...
  dsort = sort(d);
  res = dsort(round(k*length(dsort)));
  
  
  
