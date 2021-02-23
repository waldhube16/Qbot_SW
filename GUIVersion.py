# This Python file uses the following encoding: utf-8
import sys
import os
import serial
import serial.tools.list_ports
import time
import cv2 as cv
# import cv2 as cv
from PyQt5.QtCore import QElapsedTimer, QTimer
from PyQt5.QtGui import QPixmap
os.system('pyuic5 GUI/QbotMain.ui -o GUI/QbotMain.py')
from GUI.QbotMain import Ui_QbotGUI
from PyQt5.QtWidgets import QLabel, QMainWindow, QApplication, QFrame, QPushButton, QToolButton, QErrorMessage
from PyQt5 import QtSerialPort
from SolverBackend.Cube import Cube as erno
# import SolverBackend.AlgorithmPython.solver as solver
import kociemba
from ImageProcessing import analyzeCubeImages
class QbotGUI(QMainWindow, Ui_QbotGUI):
    
    def __init__(self):
        super(QbotGUI, self).__init__()
        self.setupUi(self)
        #instantiate other components 
        self.cube = erno()
        # self.solver = solver
        self.serial = serial.Serial()
        # self.timer1ms = QTimer()
        # self.timer1ms.timeout.connect(self.solutionProgBarHandler)
        # self.timer1ms.setInterval(1)
        # self.timer1ms.start(1) 
        #link GUI elements to methods to execute
        self.Menu1.triggered.connect(self.cube.print)
        manualChildren = self.scrollAreaManual.children() #get all children in scroll area containing move buttons 
        for btn in manualChildren:
            if type(btn) == QPushButton: #only continue with buttons 
                if len(btn.text()) <= 2: #text on buttons indicates the move
                    btn.clicked.connect(self.performMoveOnCube)

        frameChildren = self.tab_2D.children() #get all children in tab 2D
        for frame in frameChildren:
            btns = frame.children()
            for child in btns:
                if type(child) == QToolButton: #only continue with toolbuttons 
                    if child.objectName()[-1] == "5": 
                        pass
                    else:
                        child.clicked.connect(self.recolorFrame)

        middleButtons = [self.btn_U5, self.btn_R5, self.btn_F5, self.btn_D5, self.btn_L5, self.btn_B5]
        for btn in middleButtons:
            btn.clicked.connect(self.startRecolor)

        stepperButtons = [self.btn_a3, self.btn_A3,self.btn_a4, self.btn_A4,self.btn_a5, self.btn_A5, self.btn_a6, self.btn_A6]
        for btn in stepperButtons:
            btn.clicked.connect(self.sendToHW)
        axisButtons = [self.btn_y0,self.btn_Y0,self.btn_x0,self.btn_X0]
        for btn in axisButtons:
            btn.clicked.connect(self.sendToHW)
        self.btn_Send.clicked.connect(self.sendToHW)
        self.btn_EnDisableServo.clicked.connect(self.sendToHW)
        self.btn_Clean.clicked.connect(self.resetCube)
        patternChildren = self.scrollAreaPatterns.children() #get all children in scroll area containing pattern buttons 
        for btn in patternChildren:
            if type(btn) == QToolButton:
                btn.clicked.connect(self.applyPattern)
        self.btn_GenSolution.clicked.connect(self.generateSolution)
        self.actionGenerate_Random.triggered.connect(self.randomizeCube)
        self.btn_Apply.clicked.connect(self.applyStringToCube)
        self.btn_ScanCube.clicked.connect(self.startScan)
        
        self.colorGlobals = {"enableRecolor": False, "currColor": "U"}
        ComPorts = [comport.device for comport in serial.tools.list_ports.comports()]
        self.combo_COM.addItems(ComPorts)
        self.btn_Connect.clicked.connect(self.openSerial)
        
    
    def sendToHW(self):
        """
        Select which commands to send the hardware.
        """
        sender = self.sender()
        if sender == self.btn_Send:
            sendstring = self.lineEdit_InOut.text()
        elif sender == self.btn_EnDisableServo:
            if sender.text() == "Enable":
                sendstring = "E1"
                sender.setText("Disable")
            else:
                sendstring = "E2"
                sender.setText("Enable")
        else:
            sendstring = sender.text()

        self.sendCommands(sendstring)
        pass

    def startScan(self):
        """
        Scan the cube and generate the cubestring from the images and display the images in the GUI 
        """


        cam = cv.VideoCapture(-1); # open the default cam
        if (~cam.isOpened()):  # check if we succeeded
            return -1
 
        flag = self.sendCommands("X0")
        flag += self.sendCommands("Y1")

        
        time.sleep(1)
        for i in range(5):
            return_value, image = cam.read()
        
        cv.imwrite("ExampleImages/Left.jpeg", image)

        flag += self.sendCommands("y1")
        flag += self.sendCommands("y1")

        time.sleep(1)
        for i in range(5):
            return_value, image = cam.read()
        cv.imwrite("ExampleImages/Right.jpeg", image)

        flag += self.sendCommands("x0")
        flag += self.sendCommands("Y0")
        flag += self.sendCommands("Y1")
        flag += self.sendCommands("y0")
        flag += self.sendCommands("X0")
        flag += self.sendCommands("y1")

        time.sleep(1)
        for i in range(5):
            return_value, image = cam.read()
        cv.imwrite("ExampleImages/Down.jpeg", image)

        flag += self.sendCommands("Y1")
        flag += self.sendCommands("Y1")

        time.sleep(1)
        for i in range(5):
            return_value, image = cam.read()
        cv.imwrite("ExampleImages/Up.jpeg", image)

        flag += self.sendCommands("x0")
        flag += self.sendCommands("Y0")
        flag += self.sendCommands("Y1")
        flag += self.sendCommands("X1")

        time.sleep(1)
        for i in range(5):
            return_value, image = cam.read()
        cv.imwrite("ExampleImages/Front.jpeg", image)

        flag += self.sendCommands("x2")

        time.sleep(1)
        for i in range(5):
            return_value, image = cam.read()
        cv.imwrite("ExampleImages/Back.jpeg", image)

        flag += self.sendCommands("X1")
        flag += self.sendCommands("y0")
        # the cam will be deinitialized automatically in VideoCapture destructor

	
        #analyze the pictures
        scannedstring = analyzeCubeImages(bDebug = 0)
        self.cube.cubestring = scannedstring
        self.stringToCubemap()
        faces = ['Up', 'Right', 'Front', 'Down', 'Left', 'Back']
        for face in faces: 
            pxmap = QPixmap("ExampleImages/"+face+"_computed.jpeg")
            label = self.findChild(QLabel, "lbl_"+face+"Picture")
            label.setPixmap(pxmap)
        pass

    def performMoveOnCube(self):
        """
        This function is linked to the move and rotate buttons and changes the cubestring accordingly
        """
        movestring = self.sender().text() #get string from sender button
        self.cube.scramble(movestring)  #manipulate cubestring according to input
        self.stringToCubemap()
        pass

    def applyStringToCube(self):
        """
        This function applies the currently diplayed string on the 2D cube
        """
        movestring = self.lineEdit_InOut.text() #get string from line edit
        self.cube.scramble(movestring)  #manipulate cubestring according to input
        self.stringToCubemap()
        pass


    def resetCube(self):
        """
        Rest cubestring and 2d Map
        """
        self.cube.__init__()
        self.stringToCubemap()
        pass

    def randomizeCube(self):
        """
        Generate random scramble, apply to cube and display string
        """
        self.cube.__init__() #reinitialize the cube object, effectively resetting the cube
        rand = self.cube.genRandom() #generate a string of 20 random moves 
        self.cube.scramble(rand) #perform the moves on the cube 
        self.stringToCubemap() #update GUI with new cubestring
        #display the generated random string in the GUI
        self.lineEdit_InOut.setText(rand) 
        self.label_CurrentString.setText("Random:")
        pass

    def stringToCubemap(self):
        """
        This function takes the cubestring and colors the 2D Cube representation in the GUI
        """
        faces = ["U","R","F","D","L","B"]
        for faceindex in range(0,6):
            face = faces[faceindex]
            for index in range(0,9):
                #extract the symbol from the string
                stringSymbol = self.cube.cubestring[faceindex*9+index]
                # get the specified color in (R,G,B) tuple
                color = self.cube.colors[stringSymbol]
                # color to string 
                color = str(color)
                #set up stylesheet string eg: "background-color: rgb(85, 85, 100);"
                styleSheet = "background-color: rgb"+color+";"
                #get the correct child
                frame = self.findChildren(QFrame, face+str(index+1))
                #set the stylesheet of this child
                frame[0].setStyleSheet(styleSheet)
        pass

    def openSerial(self):
        """
        Tries to open the serial port with the specified parameters. 
        """
        baud = int(self.combo_Baud.currentText())
        COM = self.combo_COM.currentText()
        try:
            self.serial.baudrate = baud
            self.serial.port = COM
            self.serial.timeout = 0.1
            self.serial.open()
            time.sleep(3)
            self.sendCommands("U")
        except Exception as err:
            print(err)
            error_dialog = QErrorMessage()
            error_dialog.showMessage(err.args[0])
            error_dialog.exec_()
            

        pass
    def sendCommands(self, scramblestring):
        """
        Send a string of instructions to the hardware. 
        """
        validCMDs = {"U": "U1", #standard moves
            "U'": "u1", 
            "U2": "U2", 
            "R": "R1", 
            "R'": "r1", 
            "R2": "R2", 
            "F": "F1", 
            "F'": "f1", 
            "F2": "F2", 
            "D": "D1", 
            "D'": "d1", 
            "D2": "D2", 
            "L": "L1", 
            "L'": "l1", 
            "L2": "L2", 
            "B": "B1", 
            "B'": "b1", 
            "B2": "B2",
            "Y0": "Y0", #axis open/close
            "y0": "y0", 
            "X0": "X0", 
            "x0": "x0", 
            "E1": "E1", #motor en/disable
            "E2": "E2",
            "A1": "A1", #single steps
            "a1": "a1", 
            "A2": "A2", 
            "a2": "a2", 
            "A3": "A3", 
            "a3": "a3",
            "A4": "A4", 
            "a4": "a4", 
            "A5": "A5", 
            "a5": "a5",
            "A6": "A6", 
            "a6": "a6",
            }
        txCMDs = []
        txList = scramblestring.split(" ")
        for CMD in txList:
            CMD = validCMDs.get(CMD, lambda: None)
            txCMDs.append(CMD)

        try:
            for num in txCMDs:
                self.serial.write(bytes(num, 'utf-8'))
                while self.serial.in_waiting == 0:
                    time.sleep(0.05)
                data = self.serial.readline()
                print("Received: " + str(data)) 
                if (data != b'K'):
                    raise ValueError('ACK was not received correctly')  
                
        except Exception as err:
            print(err)
            error_dialog = QErrorMessage()
            error_dialog.showMessage(err.args[0])
            error_dialog.exec_()
            return -1
        return 0 

    def applyPattern(self):
        """
        Applies the selected pattern to the cube. 
        """
        self.cube.__init__()
        identifier = self.sender().text() #get string from sender button
        patterns = {
            "Checkerboard": "U2 D2 F2 B2 L2 R2",
            "Superflip": "U R2 F B R B2 R U2 L B2 R U' D' R2 F R' L B2 U2 F2",
            "Cube2nd": "F L F U' R U F2 L2 U' L' B D' B' L2 U",
            "Cube3rd": "U' L' U' F' R2 B' R F U B2 U B' L U' F U R F'",
            "CrossOne": "U F B' L2 U2 L2 F' B U2 L2 U",
            "CrossTwo": "R2 L' D F2 R' D' R' L U' D R D B2 R' U D2",
            "Python": "F2 R' B' U R' L F' L F' B D' R B L2",
            "GreenMamba": "R D R F R' F' B D R' U' B' U D2",
            "6Centers": "U D' R L' F B' U D'",
            "CEC": "U' R2 L2 F2 B2 U' R L F B' U F2 D2 R2 L2 F2 U2 F2 U' F2",
            "Tetris": "L R F B U' D' L' R'",
            "4H": "L2 R2 U2 L2 R2 U2 y L2 R2 U2 L2 R2 U2 y'",
            "4I": "L2 R2 U2 L2 R2 U2 x L2 R2 U2 L2 R2 U2 x'"
            
        }
        self.cube.scramble(patterns[identifier])  #manipulate cubestring according to input
        self.stringToCubemap()
        self.lineEdit_InOut.setText(patterns[identifier])
        self.label_CurrentString.setText("Pattern:")
        pass

    def generateSolution(self):
        """
        Generate a solution for the current cubestring and display in the GUI
        """  
        timer = QElapsedTimer()
        timer.start()
        solution = "No Solution"
        try:
            solution = kociemba.solve(self.cube.cubestring)
        except Exception as err:
            print(err)
            error_dialog = QErrorMessage()
            error_dialog.showMessage(err.args[0])
            error_dialog.exec_()
            solution = err.args[0]

        self.lineEdit_InOut.setText(solution)
        self.label_CurrentString.setText("Solution:")
        self.plainText_Log.appendPlainText("Solution calculation took: {} ms".format(timer.nsecsElapsed()/1000000))
        
        # self.timer1ms.stop()
        pass

    def solutionProgBarHandler(self):
        """
        Updates the progress bar while a solution is calcuated
        """
        currvalue = self.progBar_Solution.value()
        if currvalue == 1000:
            self.progBar_Solution.setValue(0)
        else:
            self.progBar_Solution.setValue(currvalue+1)

        pass

    def recolorFrame(self):
        """
        This function is called when a toolbutton in a frame is clicked in recoloring mode.
        """
        if self.colorGlobals["enableRecolor"] == True: # global indicator whether recoloring mode is on
            sender = self.sender().objectName() #get name of pressed button, eg "btn_U1"
            faceletID = sender.replace('btn_', '') #remove 'btn_' prefix
            face = faceletID[0]
            index = faceletID[1]
            #determine offset and index in cubestring based on face
            switcher = {
                "U": (0*9)-1,
                "R": (1*9)-1,
                "F": (2*9)-1,
                "D": (3*9)-1,
                "L": (4*9)-1,
                "B": (5*9)-1         
            } 
            stringindex = switcher[face]+int(index)
            # extract cubestring before index to be changed
            strbefore = self.cube.cubestring[:stringindex]
            # extract  cubestring after index to be changed 
            strafter = self.cube.cubestring[stringindex+1:]
            # piece together the new cubestring
            self.cube.cubestring = strbefore + self.colorGlobals["currColor"] + strafter
            self.stringToCubemap() #update GUI
        pass

    def startRecolor(self):
        """
        This function is called when a middle button is clicked to start recoloring the frames manually. 
        """
        middleButtons = [self.btn_U5, self.btn_R5, self.btn_F5, self.btn_D5, self.btn_L5, self.btn_B5]
        if self.colorGlobals["enableRecolor"] == False: #start recoloring mode - first button pressed
            #enable recoloring mode
            self.colorGlobals["enableRecolor"] = True
            #get the sendername and extract the corresponding character that indicated the color
            sendername = self.sender().objectName()
            faceletID = sendername.replace('btn_', '')
            face = faceletID[0]
            #set global recoloring parameter
            self.colorGlobals["currColor"] = face
        else:
            if self.sender().isChecked() == False: #same button as before pressed - second button pressed 
                self.colorGlobals["enableRecolor"] = False
            else: 
                """
                different button than before was pressed -> lift previous button and keep recoloring 
                second button pressed is different button than first
                """
                for btn in middleButtons: #reset all middle buttons to unchecked state  
                    btn.setChecked(False)
                sendername = self.sender().objectName()
                self.sender().setChecked(True)
                faceletID = sendername.replace('btn_', '')
                face = faceletID[0]
                self.colorGlobals["currColor"] = face
                
        pass
if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = QbotGUI()
    widget.show()
    sys.exit(app.exec_())
