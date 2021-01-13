# This Python file uses the following encoding: utf-8
import sys
import os
os.system('pyuic5 GUI/QbotMain.ui -o GUI/QbotMain.py')
from GUI.QbotMain import Ui_QbotGUI
from PyQt5.QtWidgets import QMainWindow, QApplication, QFrame, QPushButton

from SolverBackend.Cube import Cube as erno


class QbotGUI(QMainWindow, Ui_QbotGUI):
    
    def __init__(self):
        super(QbotGUI, self).__init__()
        self.setupUi(self)
        self.cube = erno()
        self.Menu1.triggered.connect(self.cube.print)
        manualChildren = self.scrollAreaManual.children() #get all children in scroll area containing move buttons 
        for btn in manualChildren:
            if type(btn) == QPushButton: #only continue with buttons 
                if len(btn.text()) <= 2: #text on buttons indicates the move
                    btn.clicked.connect(self.performMoveOnCube)



    def performMoveOnCube(self):
        """
        This function is linked to the move and rotate buttons and changes the cubestring accordingly
        """
        movestring = self.sender().text() #get string from sender button
        self.cube.scramble(movestring)  #manipulate cubestring according to input
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
    def cubemapToString(self):
        """
        This function takes the 2D cube representation and creates the corresponding cubestring
        """
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
