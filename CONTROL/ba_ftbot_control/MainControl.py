import sys
from PyQt6 import QtWidgets
from Control import Ui_Form

class MainWindow(QtWidgets.QMainWindow, Ui_Form):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.setupUi(self)

app = QtWidgets.QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()