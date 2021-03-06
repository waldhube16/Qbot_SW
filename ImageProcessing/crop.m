A = imread('Left.jpeg');
width = 200;
height = 200;
[rows, columns, numberOfColorChannels] = size(A);
left = columns/2 - width/2;
top = rows/2 - height/2;
croppedImage = imcrop(A, [left, top, width, height]);
imshow(croppedImage)

