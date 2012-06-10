function [adjSer]=getCorrectedSerGlobal(b,transVec,ser)

bias=ones(size(b,1),size(b,2));
for i=2:length(transVec)
  bias=bias+transVec(i)*b(:,:,i);
end

repBias=repmat(bias,[1 1 size(ser,3)]);
adjSer=repBias.*ser;

adjSer=adjSer/std(adjSer(:));

