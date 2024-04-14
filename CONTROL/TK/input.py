import pyglet
from pyglet.window import key

varSteer = 0

window = pyglet.window.Window()

@window.event
def on_key_press(symbol, modifiers):
    global varSteer
    if symbol == key.A:
        varSteer -= 1
    elif symbol == key.D:
        varSteer += 1
    elif symbol == key.ESCAPE:
        pyglet.app.exit()

pyglet.app.run()