% incrTrans
%
% function transVec=incrTrans(mn,cnt,img,transVec)
%
% This function finds an incremental change to the transformation
% transVec which improves the likelihood of the image img under the
% distribution specified by mn.
%
% IMPORTANT: It is assumed that the image mn CONTAINS a copy of 
% the TRANSFORMED VERSION of img already. That is, it contains a
% copy of the img acted upon by transVec.
% This is why oldImg is subtracted out to create allbutone
% below.
%
% All incoming images (mn and img) should be normalized from 0-1.

function transVec=incrTrans(mn,cnt,img,transVec)

pars=length(transVec);

ent=fastEntLookup(mn);

% The goal of this routine is to see whether transforming an image
% increases its likelihood. But remember that the likelihood also
% depends upon the image. There are two parts to the image
% distribution. The first is a part that does not change, 
% the "allbutone" part. This is the distribution of all of the
% images except the image which may undergo transformation. The
% other part is the image which may undergo transformation. The
% weight of the first part should be (cnt-1)/cnt and the weight of
% the second part should be 1/cnt. By computing and saving
% allbutone ahead of time, we can save on computation.

oldImg=computeXfrmImg(img,transVec);
allbutone=mn-oldImg/cnt;

for i=1:pars
  transVec(i)=transVec(i)+1;
  newImg=computeXfrmImg(img,transVec);
  newMean=allbutone+newImg/cnt;
  newEnt=fastEntLookup(newMean);
  
  if newEnt<ent
    ent=newEnt;
  else
    transVec(i)=transVec(i)-2;
    newImg=computeXfrmImg(img,transVec);
    newMean=allbutone+newImg/cnt;
    newEnt=fastEntLookup(newMean);
    
    if newEnt<ent
      ent=newEnt;
    else
      transVec(i)=transVec(i)+1;
    end
  end
end
