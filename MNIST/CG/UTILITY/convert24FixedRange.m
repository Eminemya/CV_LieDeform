function im24=convert24FixedRange(im,mp,mn,mx)

im=im-mn;
im=im/(mx-mn);

[rows,cols]=size(im);
im24=zeros(rows,cols,3);

for i=1:rows
  for j=1:cols
    ind=floor(im(i,j)*63.9999999999)+1;
    ind=min(ind,64);
    im24(i,j,:)=mp(ind,:);
  end
end

