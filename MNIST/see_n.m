%see2(1:100,'c','global/km1')
function y=see_n(ntrain)


%len=size(ntrain,3);
len=size(ntrain,1);
Res = 'y';
cc=0;
[mx,my]=meshgrid(2:27,2:27);
while (Res=='y'&&cc*100<len)


for j=1:min(100,len-cc*100)
subplot(10,10,j)
%imagesc(ntrain(:,:,cc*100+j)')
imagesc(reshape(ntrain(cc*100+j,:),20,20)')

end

cc=cc+1;
Res = input('(y/n)  ', 's');
end


end
