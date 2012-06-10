function im24=convert24fixed(im,mp,minval,maxval)

im=im-minval;
im=im/(maxval-minval);
[rows,cols]=size(im);
im24=zeros(rows,cols,3);

for i=1:rows
  for j=1:cols
    ind=floor(im(i,j)*63.9999999999)+1;
    im24(i,j,:)=mp(ind,:);
  end
end

