function newim=add_box_24(im,val,coords);
newim=im;
%val=reshape(v,[1 1 3]);
[y,x,foo]=size(im);

for i=coords(3):coords(4)
  newim(coords(1),i,:)=val;
  newim(coords(1)+1,i,:)=val;
  newim(coords(2),i,:)=val;
  newim(coords(2)-1,i,:)=val;
end

for i=coords(1):coords(2)
  newim(i,coords(3),:)=val;
  newim(i,coords(3)+1,:)=val;
  newim(i,coords(4)-1,:)=val;
  newim(i,coords(4),:)=val;
end
