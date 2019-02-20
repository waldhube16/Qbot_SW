%
% Based on: Function readCubeFaces(servo_front, servo_back)
% URL: https://viewer.mathworks.com/?viewer=plain_code&url=https%3A%2F%2Fde.mathworks.com%2Fmatlabcentral%2Fmlc-downloads%2Fdownloads%2Fsubmissions%2F49434%2Fversions%2F4%2Fcontents%2FArduinoRubiksCubeSolver%2Fadapter%2FreadCubeFaces.m&embed=web
% Mirror: https://de.mathworks.com/matlabcentral/fileexchange/49434-rubik-s-cube-solver-using-an-arduino-and-matlab
% Copyright 2015 The MathWorks, Inc.
% Modified by: Simon Waldhuber
% Available: https://github.com/waldhube16/Qbot_SW/blob/master/ImageProcessing/Bildverarbeitung.m
%

function cubestring = Bildverarbeitung()
    % The function is used to read in the initial configuration of the cube.
    % Webcam support package is required to turn on the webcam and capture
    % snapshots of the six cube faces. Each of the faces is then processed to
    % extract individual facelet colors. The configuration is then saved.
    
    %vid = webcam;
    vid.Resolution = '640x480';
    vid.Sharpness = 80;
    vid.Saturation = 45; %52
    q = 0.5;
    success = false;
    col = zeros(6,3);
    R = cell(1,6);
    figure;
    % Once the cube is placed into the holder in the expected position, read in
    % the facelets for each face.
    for side = 1:6

        % Until success is true, keep taking pictures of the face and attempt
        % to identify the facelets in the face.
        while ~success
            % Capture picture from the webcam
            %img = snapshot(vid);

            if ( side == 1 )
                img = imread ('Up.jpeg'); %Up - White
                %imwrite(img, 'Side1.jpeg');
            elseif (side == 2)
                img = imread ('Right.jpeg'); %Right - Red
                %imwrite(img, 'Side2.jpeg');
            elseif (side == 3)
                img = imread ('Front.jpeg'); %Front - Green
                %imwrite(img, 'Side3.jpeg');
            elseif (side == 4)
                img = imread ('Down.jpeg'); %Down - Yellow
                %imwrite(img, 'Side4.jpeg');
            elseif (side == 5)
                img = imread ('Left.jpeg'); %Left - Orange
                %imwrite(img, 'Side5.jpeg');
            elseif (side == 6)
                img = imread ('Back.jpeg'); %Back - Blue
                %imwrite(img, 'Side6.jpeg');
            end

            %imshow(img);

            %match the pictures with Cube Map
            if ( side == 1 )
                img = imrotate(img, 90);
            elseif (side == 2)
                %img = imrotate(img, -90);
            elseif (side == 3)
                img = imrotate(img, -90);
            elseif (side == 4)
                img = imrotate(img, -90);
            elseif (side == 5)
                img = imrotate(img, -180);
            elseif (side == 6)
                img = imrotate(img, -90);
            end



            % Find Cube in picture by f cal edges in 'ed'
            try
                ed = edge(rgb2gray(img), 'canny');

                x = zeros(size(ed,1),1);
                for i=1:numel(x)
                    x(i) = nnz(ed(i,:));
                end
                y = zeros(size(ed,2),1);
                for i=1:numel(y)
                    y(i) = nnz(ed(:,i));
                end

                xpeeks = findpeeks(x);
                ypeeks = findpeeks(y);
                highx  = sort(xpeeks(1,:),'descend');
                highy  = sort(ypeeks(1,:),'descend');
                highx  = highx(1:4);
                highy  = highy(1:4);
                for i=1:4
                    posx(i) = xpeeks(2,find(xpeeks(1,:)== highx(i),1));
                    posy(i) = ypeeks(2,find(ypeeks(1,:)== highy(i),1));
                    xpeeks(:,xpeeks(1,:)== highx(i)) = [];
                    ypeeks(:,ypeeks(1,:)== highy(i)) = [];
                end
                posx = sort(posx);
                posy = sort(posy);

                img = img(posx(1):posx(4),posy(1):posy(4),:);
                s = size(img);

                %center the cube image in a square
                if s(1)~=s(2)
                    dif = abs(s(1)-s(2));
                    cut = ceil(dif/2);
                    if s(2)<s(1)
                        img = img(cut:end-cut,:,:);
                    else
                        img = img(:,cut:end-cut,:);
                    end
                    s = size(img);
                    img = img(1:min(s(1:2)),1:min(s(1:2)),:);
                end

                % Present the original orientation image to the user
                image(img);


                axis off square
                cont = false;
                while ~cont
                    ui = questdlg('Is this correct?','Confirm','Yes','No','Yes');
                    cont = true;
                    switch ui
                        case 'Yes'
                            if ( side == 1 )
                                imwrite(img, 'Side1_cropped.jpeg');
                            elseif (side == 2)
                                imwrite(img, 'Side2_cropped.jpeg');
                            elseif (side == 3)
                                imwrite(img, 'Side3_cropped.jpeg');
                            elseif (side == 4)
                                imwrite(img, 'Side4_cropped.jpeg');
                            elseif (side == 5)
                                imwrite(img, 'Side5_cropped.jpeg');
                            elseif (side == 6)
                                imwrite(img, 'Side6_cropped.jpeg');
                            end
                            success = true;
                        case 'No'
                            success = false;
                    end
                end
            catch
                message = 'Failed cropping cube image, please try again';
                pause(1)
            end
        end
        R{side} = img;
        success = false;
    end
    for side = 1:6
        % Find the number of columns in the image
        s = size(R{side},1);
         % Find the 3 partitions which would be at 1/3 and 2/3 the number of
        % columns
        x = round(1:(s-1)/3:s);
        % Pick the immovable middle facelet
        R0 = R{side}(x(2):x(3),x(2):x(3),:);
        % Find the number of rows in R0
        l = size(R0,1);
        % Find the center of the facelet
        a = round(l/2*(1-sqrt(q)));
        % Convert the pixel values to double and divide by 255 to normalize the value
        R0 = R0(a:end-a,a:end-a,:);
        R1 = double(R0(:,:,1))/255;
        R2 = double(R0(:,:,2))/255;
        R3 = double(R0(:,:,3))/255;
        % identify the color by finding the median of all colors in this
        % section
        col(side,:) = median([R1(:) R2(:) R3(:)]);
    end
    r = cell(6,1);
    for side = 1:6
        s = size(R{side},1);
        x = round(1:(s-1)/3:s);
        for i=1:3
            for j=1:3
                R0 = R{side}(x(i):x(i+1),x(j):x(j+1),:);
                l = size(R0,1);
                a = round(l/2*(1-sqrt(q)));
                R0 = R0(a:end-a,a:end-a,:);
                R1 = double(R0(:,:,1))/255;
                R2 = double(R0(:,:,2))/255;
                R3 = double(R0(:,:,3))/255;
                for k=1:6
                    temp = [abs(R1(:)-col(k,1)),...
                        abs(R2(:)-col(k,2)),...
                        abs(R3(:)-col(k,3))];
                    D(k) = mode(sqrt(sum(temp.^2,2)));
                end
                r{side}(i,j) = find(D==min(D));
            end
        end
        r{side}(2,2) = side;
    end
    R = cat(3,r{1},r{2},r{3},r{4},r{5},r{6});
    done = false;

    for side = 1:6
        r_t{side} = reshape(r{side}.',[1 9]);
    end
    %cubestring = reshape (R(:,:,:), [1, 54]);

    cubestring = cat(2,r_t{1},r_t{2},r_t{3},r_t{4},r_t{5},r_t{6});
    for index = 1:54
       switch cubestring(index)
           case 1
               cubestring(index) = 'U';
           case 2
               cubestring(index) = 'R';
           case 3
               cubestring(index) = 'F';
           case 4
               cubestring(index) = 'D';
           case 5 
               cubestring(index) = 'L';
           case 6
               cubestring(index) = 'B';
           otherwise
               cubestring(index) = 'X';
       end
    end
    cubestring_char = char(cubestring);
    dlmwrite('cubestring.txt', cubestring_char,'');
end

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