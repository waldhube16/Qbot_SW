# This Python file uses the following encoding: utf-8
import sys
import os

from GUI.QbotMain import Ui_QbotGUI
from PyQt5.QtWidgets import QMainWindow, QApplication

from SolverBackend.Cube import Cube as erno
#os.system('pyuic5 GUI/QbotMain.ui -o GUI/QbotMain.py')

cube = erno()

class QbotGUI(QMainWindow, Ui_QbotGUI):
    def __init__(self):
        super(QbotGUI, self).__init__()
        self.setupUi(self)
        self.Menu1.triggered.connect(cube.print)




if __name__ == "__main__":
    app = QApplication(sys.argv)
    widget = QbotGUI()
    widget.show()
    sys.exit(app.exec_())
