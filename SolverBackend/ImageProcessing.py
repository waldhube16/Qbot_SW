import cv2 as cv
import numpy as np
import sys
import math
from PyQt5.QtCore import QElapsedTimer

def get_identifier(current_color, centers):
    #adapted from: https://answers.opencv.org/question/186712/find-an-image-by-nearest-color/
    # set the distance to be a reallly big number
    # initialise closest_colour to empty
    shortest_distance = sys.maxsize
    identifier = 'X' #return invalid element by default
    H = current_color[0]
    S = current_color[1]
    V = current_color[2]
    # iterate through all the colours
    # for each colour in the list, find the Euclidean distance to the one selected by the user
    for center_name in centers.keys():
        color = centers[center_name]
        hx = color[0]
        sx = color[1]
        vx = color[2]
        # since your colours are in 3D space, perform the calculation in each respective space
        current_distance = (pow(hx - H, 2) + 4*pow(sx - S, 2) + 2*pow(vx - V, 2)) #works for the example images but weighting may need to be done kind of dynamically


        # update the distance along with the corresponding colour
        if current_distance < shortest_distance:
            shortest_distance = current_distance
            identifier = center_name[0]

    return identifier

def rotateImage(img,rotation):
    h, w = img.shape[0], img.shape[1]
    (cX, cY) = (w//2, h//2)
    # original image center
    M = cv.getRotationMatrix2D((cX, cY),rotation , 1.0)
    # 2 by 3 rotation matrix
    cos = np.abs(M[0, 0])
    sin = np.abs(M[0, 1])
    # compute the dimensions of the rotated imagen
    nW = int((h * sin) + (w * cos))
    nH = int((h * cos) + (w * sin))
    # 285,270,        # 485,270,        # 285,460,        
    # # adjust the rotation matrix to take into account translation of the new centre
    M[0, 2] += (nW / 2) - cX
    M[1, 2] += (nH / 2) - cY
    img = cv.warpAffine(img, M, (nW, nH))
    return img

def analyzeCubeImages(bDebug):
    faces = ['Up', 'Right', 'Front', 'Down', 'Left', 'Back']
    rotation = {'Up': -90, 'Right': 180, 'Front': -90, 'Down': 90, 'Left': 0, 'Back': 90} #set how the images must be rotated in order to be correct in the 2D representation
    avg_colors = dict()
    for face in faces: 
        img = cv.imread("ExampleImages/"+face+".jpeg")
        img = rotateImage(img, 45)
        img = img[260:470,283:493]
        img = rotateImage(img, rotation[face])
        

        gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY) 
        
        kernelsize = 7
        blur = cv.GaussianBlur(gray, (kernelsize,kernelsize),0)
        
        canny = cv.Canny(blur, 50,150)
        
        kernel = np.ones((3,3), np.uint8)
        dilated = cv.dilate(canny, kernel, iterations=2)
        
        contours, hierarchy = cv.findContours(dilated, cv.RETR_TREE, cv.CHAIN_APPROX_SIMPLE)
        #################################################################################
        #source: https://programmer.help/blogs/rubik-cube-recognition-using-opencv-edge-and-position-recognition.html
        candidates = []
        centers = []
        hierarchy = hierarchy[0]

        index = 0
        pre_cX = 0
        pre_cY = 0
        center = []
        for component in zip(contours, hierarchy):
            contour = component[0]
            peri = cv.arcLength(contour, True)
            approx = cv.approxPolyDP(contour, 0.1 * peri, True)
            area = cv.contourArea(contour)
            corners = len(approx)

            # compute the center of the contour
            M = cv.moments(contour)

            if M["m00"]:
                cX = int(M["m10"] / M["m00"])
                cY = int(M["m01"] / M["m00"])
            else:
                cX = None
                cY = None

            if 1500 < area < 2500 and cX is not None:
                tmp = {'index': index, 'cx': cX, 'cy': cY, 'contour': contour}
                center.append(tmp)
                index += 1

        center.sort(key=lambda k: (k.get('cy', 0)))
        row1 = center[0:3]
        row1.sort(key=lambda k: (k.get('cx', 0)))
        row2 = center[3:6]
        row2.sort(key=lambda k: (k.get('cx', 0)))
        row3 = center[6:9]
        row3.sort(key=lambda k: (k.get('cx', 0)))

        center.clear()
        center = row1 + row2 + row3

        for component in center:
            candidates.append(component.get('contour'))
            centers.append((component.get('cx')-20,component.get('cy')-5))
    ##############################################################################################
        mask = np.zeros(dilated.shape,np.uint8)
        extracted = np.zeros(img.shape, np.uint8)
        hsv_img = cv.cvtColor(img, cv.COLOR_BGR2HSV)
        meancol = [] #mean colors of the contours of this face
        #calucate the average colors inside the contours
        for i in range(0, len(candidates)):
            mask[...]=0
            cv.drawContours(mask,candidates,i,255,-1)
            meancol.append(cv.mean(hsv_img, mask)) # get the average hsv color for later differentiation
            col = cv.mean(img, mask) #get the average bgr color to use in the new picture
            cv.drawContours(extracted,candidates ,i,col,-1)
            cv.putText(extracted,"{},{},{}".format(int(meancol[i][0]),int(meancol[i][1]),int(meancol[i][2])),centers[i],cv.FONT_HERSHEY_SIMPLEX, 0.3,(115,100,100),1)

        avg_colors[face] = meancol # put the mean color of the current face in the global dictionary
        #show the new image
        cv.imwrite("ExampleImages/"+face+"_computed.jpeg", extracted)
        cv.drawContours(extracted, candidates, -1, (0, 0, 255), 3)

        if bDebug:
            cv.imshow("Rotated",img)
            cv.imshow("Gray",gray)
            cv.imshow("Blurred", blur)
            cv.imshow("Canny", canny)
            cv.imshow("Dilated", dilated)
            cv.imshow("image", extracted)
            cv.waitKey(0)


    #get the center colors 
    # center_colors = dict()
    center_colors = dict()
    for face in faces:
        center_colors[face] = avg_colors[face][4]

    cubestring = ''
    for face in faces:
        for i in range(0,len(avg_colors[face])):
            current_color = avg_colors[face][i]
            if i == 4:
                identifier = face[0]
            else:
                identifier = get_identifier(current_color, center_colors)

            cubestring += identifier
    # for 




    #compare averages to center color


    return  cubestring


#when executed directly as means to benchmark
if __name__ == "__main__": 
    f = open("imageBenchmark.txt", "w")
    overall = 0
    for i in range(0,1000):
        timer = QElapsedTimer()
        timer.start()
        cubestring = analyzeCubeImages(bDebug = 0)
        end = timer.nsecsElapsed()
        f.write("{}\n".format(end))
        print(end)
        overall += end
    f.close()
        # print("; "+cubestring)
    # print(overall//20)

