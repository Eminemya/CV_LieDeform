function y=f_bb(ims)
%second is the reference
lx=zeros(2);
ly=zeros(2);

for i=1:2
[aa,bb]=ind2sub(size(ims{i}),find(ims{i}));
lx(i,:)=[min(aa),max(aa)];
ly(i,:)=[min(bb),max(bb)];
end


out=imresize(ims{1}(lx(1,1):lx(1,2),ly(1,1):ly(1,2)),[lx(2,2)-lx(2,1)+1,ly(2,2)-ly(2,1)+1],'bilinear');
y=zeros(size(ims{2}));
y(lx(2,1):lx(2,2),ly(2,1):ly(2,2))=out;

end
