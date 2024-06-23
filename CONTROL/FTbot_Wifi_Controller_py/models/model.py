"""
This module defines the Model class which represents the state of the application.
"""

class Model:
    """
    The Model class represents the state of the application.

    Attributes:
        | steering: The steering value of the model.
        | throttle: The throttle value of the model.
        | speed: The speed value of the model.
        | voltage: The voltage value of the model.
        | observers: The list of observers for the model.
    """

    def __init__(self) -> None:
        """
        The constructor for the Model class.
        """
        self.steering = 0
        self.throttle = 0
        self.speed = 0.00
        self.voltage = 0.0
        self.observers = []

    def add_observer(self, observer):
        """
        The method to add an observer to the model.

        Parameters:
            observer: The observer to be added.
        """
        self.observers.append(observer)

    def remove_observer(self, observer):
        """
        The method to remove an observer from the model.

        Parameters:
            observer: The observer to be removed.
        """
        self.observers.remove(observer)

    def notify_observers(self):
        """
        The method to notify all observers of the model.
        """
        for observer in self.observers:
            observer.notify()

    def add_to_steering(self, value: int) -> None:
        """
        The method to add a value to the steering of the model.

        Parameters:
            value: The value to be added to the steering.
        """
        self.steering += value
        if self.steering > 100:
            self.steering = 100
        elif self.steering < -100:
            self.steering = -100
        self.notify_observers()  # View update

    def set_throttle(self, value: int) -> None:
        """
        The method to set the throttle of the model.

        Parameters:
            value: The value to be set as the throttle.
        """
        if -100 <= value <= 100:
            self.throttle = value
            self.notify_observers()

    def set_speed(self, left_speed: float, right_speed: float) -> None:
        """
        The method to set the speed of the model.

        Parameters:
            left_speed: The left speed value.
            right_speed: The right speed value.
        """
        self.speed = round((left_speed + right_speed) / 2, 3)
        self.notify_observers()

    def set_voltage(self, value: float) -> None:
        """
        The method to set the voltage of the model.

        Parameters:
            value: The value to be set as the voltage.
        """
        self.voltage = value
        self.notify_observers()