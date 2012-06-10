function I = test_image(name, dx, dy, r)
% Generate a simple test image
%
%   I = test_image(name, dx, dy, r);
%
%   Input:
%   - name:     The name of the image ('sin')
%   - dx:       translation along x-axis
%   - dy:       translation along y-axis
%   - r:        The rotation radian
%
%   Output:
%   - I:        The output image
%

%% main

w = 128;
h = 128;

cx = (1 + w) / 2;
cy = (1 + h) / 2;
[X, Y] = meshgrid((1:w) - cx, (1:h) - cy);

sX = X - dx;
sY = Y - dy;

if (r ~= 0)
    sX = sX * cos(r) + sY * sin(r);
    sY = sX * sin(-r)  + sY * cos(r);
end


switch lower(name)
    case 'sin'
        I = sin_image(sX, sY);
        
    otherwise
        error('Invalid name for test image: %s', name);
end


%% image genration

function I = sin_image(X, Y)

sig = 2;
I = 0.25 * sin(X / (2 * pi * sig)) + 0.25 * sin(Y / (2 * pi * sig)) + 0.5;

  
