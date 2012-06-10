function y=cc(b1,b2)
y=zeros(1,length(b1));
for i=1:length(b1)
y(i)=length(intersect(b1{i},b2{i}));
end
end
