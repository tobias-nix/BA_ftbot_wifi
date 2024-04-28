import math
import tkinter as tk
from base.constants import *
from models.model import Model
from views.view import View


class Controller:
    def __init__(self):
        self.root = tk.Tk()
        self.model = Model(self)
        self.model.add_observer(self)
        self.view = View(self.root, self)

    def run(self):
        self.view.viewPanel.game_loop()
        self.root.mainloop()

    def update_view(self):
        x, y = self.get_position_from_steering_angle()
        self.view.viewPanel.update_view(x, y, self.model.voltage, self.model.speed)
        # print(f"throttle: {self.model.throttle:.2f}")

    def get_position_from_steering_angle(self):
        angle = math.radians(self.model.steering * STEERING_ANGLE_FACTOR) - math.pi / 2
        x = CANVAS_CENTER_X + STEERING_RADIUS * math.cos(angle)
        y = CANVAS_CENTER_Y + STEERING_RADIUS * math.sin(angle)
        return x, y

    def increase_throttle(self):
        if self.model.throttle < MAX_THROTTLE:
            self.model.set_throttle(min(self.model.throttle + THROTTLE_INCREASE_RATE, MAX_THROTTLE))

    def decrease_throttle(self):
        if self.model.throttle > MIN_THROTTLE:
            self.model.set_throttle(max(self.model.throttle - THROTTLE_INCREASE_RATE, MIN_THROTTLE))

    def decrease_throttle_to_zero(self):
        if abs(self.model.throttle) < THROTTLE_ZERO_THRESHOLD:
            self.model.set_throttle(0)
        elif self.model.throttle > 0:
            self.decrease_throttle()
        elif self.model.throttle < 0:
            self.increase_throttle()

    def steering_input_left(self):
        self.model.add_to_steering(-STEERING_INCREMENT)

    def steering_input_right(self):
        self.model.add_to_steering(STEERING_INCREMENT)

    def notify(self):
        self.update_view()
