import math

class Model:
    def __init__(self, varSteer):
        self.varSteer = varSteer

    def move_steering(self):
        radius = 235
        angle = math.radians(self.varSteer.get() * 0.84) - math.pi / 2
        x = 450 + radius * math.cos(angle)
        y = 590 + radius * math.sin(angle)
        return x, y