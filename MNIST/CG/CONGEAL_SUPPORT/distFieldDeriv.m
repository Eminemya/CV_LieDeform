% function deltaEnt=distFieldDeriv(df,dfNew,N)
% 
% Return a number proportional to H(df)-H(df+dfNew)
% 
% df is a distribution field.
% dfNew is a distribution field that is a candidate for
%       combination with df.
% N is an integer that says how many distribution fields have been
%       average to make df.
%
% The idea of this routine is to return a number that is positive if
% combining the dfNew with df would reduce the overall entropy of 
% the distribution field, and negative if it would increase the entropy.
%
% For example, adding the distribution of a low 
% variance 0-mean Gaussian to a high variance
% 0-mean Gaussian would result in a distribution that
% had lower entropy than the high variance Gaussian.
% If df and dfNew contained just these single distributions, then
% the value returned would be positive, indicating that dfNew had a
% reducing effect on the entropy.

function deltaEnt=distFieldDeriv(df,dfNew,N)

SMALL_VAL=0.000001;
BIG_VAL=0.999999;

MAX_INDEX=100;

persistent xlogxTable;
persistent oldp;
persistent newp;
persistent p;

persistent maskv;
% The table indices will range from 1:MAX_INDEX.
%
% The first value in the table will represent f(0).
% The last value will represent f(1).
%
% Hence, for a given value d, its index is given by
% ind=floor(d*(MAX_INDEX-.000001))+1
%

if size(xlogxTable)==0 
  fprintf(1,'Computing xlogx lookup table...');
  p=linspace(SMALL_VAL,BIG_VAL,MAX_INDEX);
  [oldp,newp]=meshgrid(p,p);

  % NOTE: The following line computes H(old)-H(new), not the opposite!

  % ALSO: oldp varies from left to right
  %       newp varies from top to bottom
  tempTable= newp.*log(newp)-oldp.*log(oldp);
  xlogxTable=tempTable(:);
  fprintf(1,'done.\n');
  masklayer=fspecial('gaussian',[size(df,1) size(df,2)],size(df,1)/2]);
  mask=repmat(masklayer,[1 1 size(df,3)]);
  maskv=mask(:);
end

% oldp is just df
% newp is df*(N-1)/N+dfNew/N

oldpvals=floor(df(:)*(MAX_INDEX-.000001));
newpvals=floor((df(:)*(N-1)+dfNew(:))/N*(MAX_INDEX-.000001));



% Unfortunately, the two-dimensional index must be turned into a 
% one-dimensional index. So we must form a new index:
% jnt_index=index1*MAX_INDEX+index;

% Here, we must preserve the fact that
%     : oldp varies from left to right
%     : newp varies from top to bottom
dtmp=xlogxTable(oldpvals*MAX_INDEX+newpvals+1);
deltaEnt=sum(dtmp.*maskv);

%deltaEnt=sum(xlogxTable(oldpvals*MAX_INDEX+newpvals+1));

