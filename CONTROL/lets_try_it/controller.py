from tkinter import IntVar, Tk
from model import Model
from view import View

class Controller:
    def __init__(self):
        self.root = Tk()  # Create the root window
        self.varSteer = IntVar(self.root, value=0)  # Pass the root window to IntVar
        self.view = View(self.root)  # Pass the root window to View
        self.view.window.bind('<Key>', self.on_key_press)

        self.image_5 = self.view.canvas.create_oval(450, 590, 460, 600, fill='red')

    def on_key_press(self, event):
        if event.keysym == 'a' and self.varSteer.get() > -100:
            self.varSteer.set(self.varSteer.get() - 2)
        elif event.keysym == 'd' and self.varSteer.get() < 100:
            self.varSteer.set(self.varSteer.get() + 2)
        self.move_steering()

    def move_steering(self):
        x, y = self.model.move_steering()
        self.view.canvas.coords(self.image_5, x, y)