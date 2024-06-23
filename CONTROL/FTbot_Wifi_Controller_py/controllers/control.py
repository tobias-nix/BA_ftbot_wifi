import math
import tkinter as tk
from base.constants import *
from models.model import Model
from views.view import View

class Controller:
    """
    The Controller class is responsible for managing the application's control flow.

    Attributes:
        root: The root window for the Tkinter application.
        model: The model of the application.
        view: The view of the application.
    """

    def __init__(self):
        """
        The constructor for the Controller class.
        """
        self.root = tk.Tk()
        self.model = Model()
        self.model.add_observer(self)
        self.view = View(self.root, self)

    def run(self):
        """
        The method to start the application's main loop.
        """
        self.view.viewPanel.game_loop()
        self.root.mainloop()

    def update_view(self):
        """
        The method to update the view of the application.
        """
        x, y = self.get_position_from_steering_angle()
        self.view.viewPanel.update_view(x, y, self.model.voltage, self.model.speed)

    def get_position_from_steering_angle(self):
        """
        The method to get the position from the steering angle.

        Returns:
            The x and y coordinates.
        """
        angle = math.radians(self.model.steering * STEERING_ANGLE_FACTOR) - math.pi / 2
        x = CANVAS_CENTER_X + STEERING_RADIUS * math.cos(angle)
        y = CANVAS_CENTER_Y + STEERING_RADIUS * math.sin(angle)
        return x, y

    def increase_throttle(self):
        """
        The method to increase the throttle.
        """
        if self.model.throttle < MAX_THROTTLE:
            self.model.set_throttle(min(self.model.throttle + THROTTLE_INCREASE_RATE, MAX_THROTTLE))

    def decrease_throttle(self):
        """
        The method to decrease the throttle.
        """
        if self.model.throttle > MIN_THROTTLE:
            self.model.set_throttle(max(self.model.throttle - THROTTLE_INCREASE_RATE, MIN_THROTTLE))

    def decrease_throttle_to_zero(self):
        """
        The method to decrease the throttle to zero.
        """
        if abs(self.model.throttle) < THROTTLE_ZERO_THRESHOLD:
            self.model.set_throttle(0)
        elif self.model.throttle > 0:
            self.decrease_throttle()
        elif self.model.throttle < 0:
            self.increase_throttle()

    def steering_input_left(self):
        """
        The method to steer left.
        """
        self.model.add_to_steering(-STEERING_INCREMENT)

    def steering_input_right(self):
        """
        The method to steer right.
        """
        self.model.add_to_steering(STEERING_INCREMENT)

    def notify(self):
        """
        The method to notify the controller to update the view.
        """
        self.update_view()