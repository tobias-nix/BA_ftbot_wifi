from PyQt6.QtGui import QGuiApplication
from PyQt6.QtQml import QQmlApplicationEngine
from PyQt6.QtCore import QUrl
import sys

def handle_qml_warnings(warnings):
    for warning in warnings:
        print("QML Warning:", warning.toString())

if __name__ == "__main__":
    app = QGuiApplication(sys.argv)

    engine = QQmlApplicationEngine()
    engine.warnings.connect(handle_qml_warnings)  # Connect to the warnings signal

    engine.load(QUrl.fromLocalFile("content/Screen01.ui.qml"))  # Load QML file using QUrl.fromLocalFile

    if not engine.rootObjects():
        sys.exit(-1)

    sys.exit(app.exec())
