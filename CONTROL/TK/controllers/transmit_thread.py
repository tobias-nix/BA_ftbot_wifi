import time
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection


class TransmitThread:
    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager):
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager

    def run(self):
        print("Running TransmitThread\n")  # print statement for debugging
        while not self.thread_manager.stop_event.is_set():
            # Fetch the steering and throttle values from the model
            steering = self.wifi_connection.model.steering
            throttle = self.wifi_connection.model.throttle

            # Call the send_data method with the fetched values
            self.wifi_connection.send_data(steering, throttle)
            time.sleep(0.1)

    def start(self):
        print("Starting TransmitThread\n")  # print statement for debugging
        if self.wifi_connection.check_connection():
            self.thread_manager.start_threads(self.run, ())

    def stop(self):
        print("Stopping TransmitThread\n")  # print statement for debugging
        self.thread_manager.stop_threads()
