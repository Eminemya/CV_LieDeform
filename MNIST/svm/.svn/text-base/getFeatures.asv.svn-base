function [FeatureMat Group] = getFeatures( data )


featureMatrix = [];

% Extracting Features
for i = 1 : length(data)
    
    sample = data(i).img;
    featureVector = [
        
        getHorizontalLineNum( sample ) %1D
        getVerticalLineNum( sample ) %1D
        getEulerNum( sample) %1D
        getXYStatistics(sample) %4D
        getHWRatio(sample) %1D
        getArea(sample) %1D
        getTemplatesResp( sample ) %16D
        
        
        ] ; 
    
    featureMatrix(:,i) = featureVector;
    Group(i) = data(i).label;
end
    
FeatureMat = featureMatrix';
Group = Group';

end

