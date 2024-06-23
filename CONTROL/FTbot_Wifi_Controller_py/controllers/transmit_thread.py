import time
import logging
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from views.message_window import MessageWindow

class TransmitThread:
    """
    The TransmitThread class is responsible for transmitting data to the Wi-Fi connection.

    Attributes:
        wifi_connection: The Wi-Fi connection to which data is transmitted.
        thread_manager: The thread manager that manages the thread.
        logger: The logger for logging information.
    """

    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager):
        """
        The constructor for the TransmitThread class.

        Parameters:
            wifi_connection: The Wi-Fi connection to which data is transmitted.
            thread_manager: The thread manager that manages the thread.
        """
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager
        self.logger = logging.getLogger(__name__)

    def run(self):
        """
        The method to run the thread for transmitting data.
        """
        self.logger.info("Running TransmitThread")
        while not self.thread_manager.stop_event.is_set():
            try:
                # Fetch the steering and throttle values from the model
                steering = self.wifi_connection.model.steering
                throttle = self.wifi_connection.model.throttle

                # Call the send_data method with the fetched values
                self.wifi_connection.send_data(steering, throttle)
                time.sleep(0.1)
            except Exception as e:
                MessageWindow.show_error(f"Error in transmit thread!\n Error:  {e}")

    def start(self):
        """
        The method to start the thread for transmitting data.
        """
        self.logger.info("Starting TransmitThread")
        self.thread_manager.start_threads(self.run, ())