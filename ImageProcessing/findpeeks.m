%
% Based on: 
% URL: https://viewer.mathworks.com/?viewer=plain_code&url=https%3A%2F%2Fde.mathworks.com%2Fmatlabcentral%2Fmlc-downloads%2Fdownloads%2Fsubmissions%2F49434%2Fversions%2F4%2Fcontents%2FArduinoRubiksCubeSolver%2Fthistlethwaite45%2Ffindpeeks.m&embed=web
% Mirror: https://de.mathworks.com/matlabcentral/fileexchange/49434-rubik-s-cube-solver-using-an-arduino-and-matlab
% Copyright 2015 The MathWorks, Inc.
% Modified by: Simon Waldhuber
% Available: https://github.com/waldhube16/Qbot_SW/blob/master/ImageProcessing/findpeeks.m
%

function peeks = findpeeks(x)
%
% Finds peeks in a spectrum. Is used during webcam-capture to determine
% position of the cube.
%

n = numel(x);

locmax = 0;
pos = 0;
count = 1;

for i=1:n
    test = max(locmax(count),x(i));
    if i-pos(count) < n/10 && test>locmax(count)
        locmax(count) = test;
        pos(count) = i;
    elseif i-pos(count) >= n/10
        count = count+1;
        locmax(count) = x(i);
        pos(count) = i; 
    end
end
    
peeks = [locmax;pos];
end