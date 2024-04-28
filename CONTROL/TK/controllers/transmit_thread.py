import time
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection


class TransmitThread:
    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager):
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager

    def run(self):
        print("Running TransmitThread")  # print statement for debugging
        while not self.thread_manager.stop_event.is_set():
            # Fetch the varSteer and throttle values from the model
            varSteer = self.wifi_connection.model.varSteer
            throttle = self.wifi_connection.model.throttle

            # Call the send_data method with the fetched values
            self.wifi_connection.send_data(varSteer, throttle)
            time.sleep(0.1)

    def start(self):
        print("Starting TransmitThread")  # print statement for debugging
        if self.wifi_connection.check_connection():
            self.thread_manager.start_threads(self.run, ())

    def stop(self):
        self.thread_manager.stop_threads()