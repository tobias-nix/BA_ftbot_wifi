import sys
from PyQt6 import QtWidgets
from Control import Ui_Form
from PyQt6 import QtGui

class MainWindow(QtWidgets.QMainWindow, Ui_Form):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.setupUi(self)
        self.pushButton.setCheckable(True)  # Make the button checkable
        self.pushButton.clicked.connect(self.checkButtonState)

        # Erstelle und initialisiere das QLineEdit Widget
        self.lineEdit = QtWidgets.QLineEdit(parent=self)
        self.lineEdit.textChanged.connect(self.updateButtonRotation)

    def checkButtonState(self):
        if self.pushButton.isChecked():
            print("Button is pressed")
        else:
            print("Button is not pressed")

    def updateButtonRotation(self, text):
        try:
            angle = float(text)
        except ValueError:
            return

        # Begrenze den Winkel auf einen vernünftigen Bereich
        angle = max(min(angle, 360), 0)
        self.rotateButton(angle)

    def rotateButton(self, angle):
        transform = QtGui.QTransform().rotate(angle)
        self.pushButton.setTransform(transform)

app = QtWidgets.QApplication(sys.argv)
window = MainWindow()
window.show()
app.exec()
