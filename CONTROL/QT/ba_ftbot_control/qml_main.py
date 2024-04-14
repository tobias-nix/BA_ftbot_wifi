import sys
from PyQt6.QtWidgets import QApplication, QWidget
from PyQt6.QtGui import QPainter, QColor, QPolygon
from PyQt6.QtCore import QPoint, QTimer
import math

class TriangleWidget(QWidget):
    def __init__(self, parent=None):
        super().__init__(parent)
        self.angle = 0
        self.timer = QTimer(self)
        self.timer.timeout.connect(self.updateAngle)
        self.timer.start(30)  # Ändere die Zeit in Millisekunden für die Animationsgeschwindigkeit

    def paintEvent(self, event):
        try:
            painter = QPainter(self)
            painter.setRenderHint(QPainter.RenderHint.Antialiasing)
            painter.setBrush(QColor(0, 0, 255))  # Blaue Farbe
            painter.setPen(QColor(0, 0, 255))

            # Definiere die Punkte des Dreiecks
            p1 = QPoint(int(self.width() / 2), 10)
            p2 = QPoint(int(self.width() - 10), int(self.height() - 10))
            p3 = QPoint(10, int(self.height() - 10))

            # Rotiere die Punkte
            p1 = self.rotatePoint(p1)
            p2 = self.rotatePoint(p2)
            p3 = self.rotatePoint(p3)

            # Erstelle ein QPolygon-Objekt mit den Dreieckspunkten
            triangle = QPolygon([p1, p2, p3])

            # Zeichne das Dreieck
            painter.drawPolygon(triangle)
        except Exception as e:
            print("Error:", e)

    def updateAngle(self):
        self.angle += 1
        if self.angle >= 360:
            self.angle = 0
        self.update()

    def rotatePoint(self, point):
        # Rotiere den Punkt um den Ursprung (Mittelpunkt des Widgets)
        cx = self.width() / 2
        cy = self.height() / 2
        x = point.x() - cx
        y = point.y() - cy

        # Winkel in Radiant umwandeln
        rad = math.radians(self.angle)

        # Rotation um den Ursprung
        nx = x * math.cos(rad) - y * math.sin(rad)
        ny = x * math.sin(rad) + y * math.cos(rad)

        # Verschiebe den Punkt zurück
        return QPoint(int(nx + cx), int(ny + cy))

class MainWindow(QWidget):
    def __init__(self):
        super().__init__()
        self.initUI()

    def initUI(self):
        self.setGeometry(100, 100, 400, 400)
        self.setWindowTitle('Dreieck Beispiel')

        self.triangleWidget = TriangleWidget(self)
        self.triangleWidget.setGeometry(50, 50, 300, 300)

if __name__ == '__main__':
    app = QApplication(sys.argv)
    mainWindow = MainWindow()
    mainWindow.show()
    sys.exit(app.exec())
