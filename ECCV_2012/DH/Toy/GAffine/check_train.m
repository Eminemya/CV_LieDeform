
digit=0;

eval(['load ns_dis' num2str(digit)])



i=1
%Level 1: K-medoid Center(pt1)
see2(1:length(land1),strain)

%Level 2: Center Landmark(pt1)+its cluster Landmarks(pt2)
see2([i,land2{i}],strain)

%Level 3: pt1/pt2 +its aligned its aligned rotation/shear + shift/scale(preserve aspect of ratio) manifold(pt3)
ii=1
%each row: first is the Landmark, rest are the aligned
seep(land1,land3,strain)
seep(land2{ii},land3(land2{ii}),strain)

%IDM8(strain{2}(24,:)',[strain{1}(1,:);strain{2}(1,:)]')
%IDM8(squeeze(newimgs(1,mid,:)),squeeze(newimgs(2,:,:))')
