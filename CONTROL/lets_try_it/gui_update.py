from tkinter import Tk
from build.gui import create_gui

varSteer = 0

window = create_gui()

window.mainloop()

def set_steering(canvas, image_5):
    canvas.coords(image_5, 450 + varSteer * 10, 355)


    # Update Tkinter window
    window.update()
