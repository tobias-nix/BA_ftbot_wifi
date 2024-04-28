class Model:
    def __init__(self, controller) -> None:
        self.controller = controller
        self.steering = 0
        self.throttle = 0
        self.speed = 0
        self.voltage = 0.0
        self.observers = []

    def add_observer(self, observer):
        self.observers.append(observer)

    def remove_observer(self, observer):
        self.observers.remove(observer)

    def notify_observers(self):
        for observer in self.observers:
            observer.notify()

    def add_to_steering(self, value: int) -> None:
        self.steering += value
        if self.steering > 100:
            self.steering = 100
        elif self.steering < -100:
            self.steering = -100
        self.notify_observers()  # View update

    def set_speed(self, value: int) -> None:
        self.speed = value
        self.notify_observers()
    
    def set_voltage(self, value: int) -> None:
        self.voltage = value
        self.notify_observers()

    def set_throttle(self, value: int) -> None:
        if -100 <= value <= 100:
            self.throttle = value
            self.notify_observers()
