%
% Based on: Function readCubeFaces(servo_front, servo_back)
% URL: https://viewer.mathworks.com/?viewer=plain_code&url=https%3A%2F%2Fde.mathworks.com%2Fmatlabcentral%2Fmlc-downloads%2Fdownloads%2Fsubmissions%2F49434%2Fversions%2F4%2Fcontents%2FArduinoRubiksCubeSolver%2Fadapter%2FreadCubeFaces.m&embed=web
% Mirror: https://de.mathworks.com/matlabcentral/fileexchange/49434-rubik-s-cube-solver-using-an-arduino-and-matlab
% Copyright 2015 The MathWorks, Inc.
% Modified by: Simon Waldhuber
% Available: https://github.com/waldhube16/Qbot_SW/blob/master/ImageProcessing/Bildverarbeitung.m
%

function cubestring = Bildverarbeitung(Up, Right, Front, Down, Left, Back)
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
    
    % Once the cube is placed into the holder in the expected position, read in
    % the facelets for each face.
    for side = 1:6
        % Until success is true, keep taking pictures of the face and attempt
        % to identify the facelets in the face.

        % Capture picture from the webcam
        %img = snapshot(vid);

        if ( side == 1 )
            img = imread (Up); %Up - White
            img = imrotate(img, 45);
            %imwrite(img, 'Side1.jpeg');
        elseif (side == 2)
            img = imread (Right); %Right - Red
            img = imrotate(img, 45);
            %imwrite(img, 'Side2.jpeg');
        elseif (side == 3)
            img = imread (Front); %Front - Green
            img = imrotate(img, 45);
            %imwrite(img, 'Side3.jpeg');
        elseif (side == 4)
            img = imread (Down); %Down - Yellow
            img = imrotate(img, 45);
            %imwrite(img, 'Side4.jpeg');
        elseif (side == 5)
            img = imread (Left); %Left - Orange
            img = imrotate(img, 45);
            %imwrite(img, 'Side5.jpeg');
        elseif (side == 6)
            img = imread (Back); %Back - Blue
            img = imrotate(img, 45);
            %imwrite(img, 'Side6.jpeg');
        end

        %img = img(posx(1):posx(4),posy(1):posy(4),:);
        img = img(282:451,305:473,:);
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

            if ( side == 1 )
                img = imrotate(img, -90);
                imwrite(img, 'Side1_cropped.jpeg');
            elseif (side == 2)
                img = imrotate(img, 180);
                imwrite(img, 'Side2_cropped.jpeg');
            elseif (side == 3)
                img = imrotate(img, -90);
                imwrite(img, 'Side3_cropped.jpeg');
            elseif (side == 4)
                img = imrotate(img, 90);
                imwrite(img, 'Side4_cropped.jpeg');
            elseif (side == 5)
                img = imrotate(img, 0);
                imwrite(img, 'Side5_cropped.jpeg');
            elseif (side == 6)
                img = imrotate(img, 90);
                imwrite(img, 'Side6_cropped.jpeg');
            end
            
        R{side} = img;
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
