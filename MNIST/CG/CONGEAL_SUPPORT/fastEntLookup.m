% This function takes the mean of a set of binary images 
% and returns the summed pixelwise entropies. It uses a lookup
% table to get the entropy.

function ent=fastEntLookup(meanImg)

persistent entTable;
if size(entTable)==0
  fprintf(1,'Computing entropy lookup table...');
  p=0.00000001:1/10000:0.9999999999;
  entTable= -(p.*log2(p)+(1-p).*log2(1-p));
  fprintf(1,'done.\n');
end

% This function works by indexing into a table of 10,000
% entries in which entry i holds the entropy for the binary
% value between [upper,lower) with lower=(i-1)/10,000 and 
% upper=i/10,000.

ent= sum(sum(entTable(floor(meanImg*9999.999999+1))));
ent=ent/prod(size(meanImg));   % Return mean pixel entropy.
