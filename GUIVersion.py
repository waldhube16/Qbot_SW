# This Python file uses the following encoding: utf-8
import sys
import os
os.system('pyuic5 GUI/QbotMain.ui -o GUI/QbotMain.py')
from GUI.QbotMain import Ui_QbotGUI
from PyQt5.QtWidgets import QMainWindow, QApplication, QFrame, QPushButton, QToolButton

from SolverBackend.Cube import Cube as erno
import SolverBackend.AlgorithmPython.solver as solver


class QbotGUI(QMainWindow, Ui_QbotGUI):
    
    def __init__(self):
        super(QbotGUI, self).__init__()
        self.setupUi(self)
        self.cube = erno()
        self.solver = solver
        self.Menu1.triggered.connect(self.cube.print)
        manualChildren = self.scrollAreaManual.children() #get all children in scroll area containing move buttons 
        for btn in manualChildren:
            if type(btn) == QPushButton: #only continue with buttons 
                if len(btn.text()) <= 2: #text on buttons indicates the move
                    btn.clicked.connect(self.performMoveOnCube)
        self.btn_Clean.clicked.connect(self.resetCube)
        patternChildren = self.scrollAreaPatterns.children() #get all children in scroll area containing pattern buttons 
        for btn in patternChildren:
            if type(btn) == QToolButton:
                btn.clicked.connect(self.applyPattern)
        self.btn_GenSolution.clicked.connect(self.generateSolution)
        
    def performMoveOnCube(self):
        """
        This function is linked to the move and rotate buttons and changes the cubestring accordingly
        """
        movestring = self.sender().text() #get string from sender button
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
                #set up stylesheet string "background-color: rgb(85, 85, 100);"
                styleSheet = "background-color: rgb"+color+";"
                #get the correct child
                frame = self.findChildren(QFrame, face+str(index+1))
                #set the stylesheet of this child
                frame[0].setStyleSheet(styleSheet)
        pass

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
        timeout = self.spinBox_Timeout.value()
        nmoves = self.spinBox_NMoves.value()
        solution, movecount = self.solver.solve(self.cube.cubestring, nmoves, timeout)
        self.lineEdit_InOut.setText(solution)
        self.label_CurrentString.setText("Solution:")
        pass
    def cubemapToString(self):
        """
        This function takes the 2D cube representation and creates the corresponding cubestring #TODO
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
                #set up stylesheet string "background-color: rgb(85, 85, 100);"
                styleSheet = "background-color: rgb"+color+";"
                #get the correct child
                frame = self.findChildren(QFrame, face+str(index+1))
                #set the stylesheet of this child
                frame[0].setStyleSheet(styleSheet)
        allFrames = self.gridLayout.children()

        switcher = {
            "U": (0*9)-1,
            "R": (1*9)-1,
            "F": (2*9)-1,
            "D": (3*9)-1,
            "L": (4*9)-1,
            "B": (5*9)-1         
        } 
        pass

if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = QbotGUI()
    widget.show()
    sys.exit(app.exec_())
