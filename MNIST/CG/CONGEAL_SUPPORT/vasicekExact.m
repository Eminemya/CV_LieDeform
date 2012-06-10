% ***********************************************************************
% Copyright (c) Erik G. Learned-Miller, 2004.
% ***********************************************************************
% vasicekExact(v,m)       Estimate entropy of distribution from a sample.
% 
% h=vasicek(v,m)
%
% Inputs:
%   v is a vector of scalars.
%   m is the "spacings" count which must be an integer between 1 and the
%     length of the vector v. This can be thought of as a
%     "smoothing" parameter. Larger values give lower variance but
%     higher bias. A good default should be floor(sqrt(len(v))).
%
% Output:
%   h is an estimate of the entropy of the distribution from which
%     the sample v was taken.
%
% The function returns a somewhat downward biased estimate of
% the entropy IN NATS. It is fast, but is also reasonably
% accurate. Its accuracy could be increased by adding a bias
% adjustment term. It uses the natural log rather than the possibly
% more intuitive log2 because natural log is faster.
% 
% For more information on this estimator, see the following
% publications:
%
%   Beirlant, J., Dudewicz, E. J., Gyorfi, L., and van der Meulen,
%     E. C. "Nonparametric entropy estimation: An overview",
%     International Journal of the Mathematical Statistics
%     Sciences, 6, 17-39, 2001.
% 
%   Vasicek, Oldrich. "A test for normality based on sample entropy."
%     Journal of the Royal Statistical Society, Series
%     B. 38(1):54-59, 1976.
% 
%   Learned-Miller, Erik G. and Fisher, John W. "ICA using spacings
%     estimates of entropy." Journal of Machine Learning Research, 4,
%     1271-1295, 2003.
%
function h=vasicekExact(v,m)

len=length(v);
orderStats=sort(v);

% Note that the intervals overlap for this estimator.
intvals=orderStats(m+1:len)-orderStats(1:len-m);
hvec=log(intvals);
h=sum(hvec);

%h=h/(len-m)+log((len+1)/m);     % Simpler version. See Learned-Miller et al.

h=h/(len-m)+log(len+1)-psi(m);   % With partial bias correction? See Beirlant et al.

  