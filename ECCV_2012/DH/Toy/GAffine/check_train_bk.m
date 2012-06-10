
digit=0;

eval(['load dis' num2str(digit)])



i=1
%Level 1: Clustered Landmarks(pt1)
see2(1:length(land1{i}),strain{i})
%Level 2: Landmark(pt1)+its aligned rotation/shear manifold(pt2)
seep(land1{i},land2{i},strain{i})
%Level 3: pt1+its aligned shift/scale(preserve aspect of ratio) manifold(pt3)
ii=1
see2([land1{i}(ii),land3{i}{land1{i}(ii)}],strain{i})
seep(land1{i},land3{i},strain{i})
%Level 3: pt2+its aligned shift/scale(preserve aspect of ratio) manifold(pt3)
ii=1
seep(land2{i}{ii},land3{i}{ii},strain{i})
see2([land2{i}{ii}(1),land3{i}{land2{i}{ii}(1)}],strain{i})

%IDM8(strain{2}(24,:)',[strain{1}(1,:);strain{2}(1,:)]')
%IDM8(squeeze(newimgs(1,mid,:)),squeeze(newimgs(2,:,:))')
