function newim=add_border_24(im,val);
newim=im;
%val=reshape(v,[1 1 3]);
[y,x,foo]=size(im);

for i=1:x
  newim(1,i,:)=val;
  newim(2,i,:)=val;
  newim(y,i,:)=val;
  newim(y-1,i,:)=val;
end

for i=1:y
  newim(i,1,:)=val;
  newim(i,2,:)=val;
  newim(i,x-1,:)=val;
  newim(i,x,:)=val;
end
