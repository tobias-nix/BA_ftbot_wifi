import time
import logging
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from views.message_window import MessageWindow


class TransmitThread:
    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager):
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager
        self.logger = logging.getLogger(__name__)

    def run(self):
        self.logger.info("Running TransmitThread")
        while not self.thread_manager.stop_event.is_set():
            try:
                # Fetch the steering and throttle values from the model
                steering = self.wifi_connection.model.steering
                throttle = self.wifi_connection.model.throttle

                # Call the send_data method with the fetched values
                self.wifi_connection.send_data(steering, throttle)
                time.sleep(0.5)
            except Exception as e:
                MessageWindow.show_error(f"Error in transmit thread!\n Error:  {e}")

    def start(self):
        self.logger.info("Starting TransmitThread")
        self.thread_manager.start_threads(self.run, ())
