function showSer(ser,figNum,maxnum)

if exist('maxnum')==1
  numFigs=ceil(size(ser,3)/maxnum);
  for j=1:numFigs
    figN=j+figNum-1;
    row=ceil(sqrt(maxnum)-.000001);
    if j==numFigs
      s=size(ser,3)-(j-1)*maxnum;
    else
      s=maxnum;
    end
    
    figure(figN);
    clf;
    for i=1:s
      subplot(row,row,i);
      imagesc(ser(:,:,i+maxnum*(j-1)));
      colormap('gray');
    end
  end
else
  figure(figNum);
  clf;

  row=ceil(sqrt(size(ser,3))-.000001);
  for i=1:size(ser,3)
    subplot(row,row,i);
    imagesc(ser(:,:,i));
    colormap('gray');
  end
end

drawnow;
