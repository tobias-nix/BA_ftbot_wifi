import logging
import socket

from views.message_window import MessageWindow
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from controllers.queue_receive import ReceiveQueue

class ReceiveDataThread:
    """
    The ReceiveDataThread class is responsible for receiving data from the Wi-Fi connection.

    Attributes:
        wifi_connection: The Wi-Fi connection from which data is received.
        thread_manager: The thread manager that manages the thread.
        receive_queue: The queue for storing received data.
        logger: The logger for logging information.
    """

    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager, receive_queue: ReceiveQueue):
        """
        The constructor for the ReceiveDataThread class.

        Parameters:
            wifi_connection: The Wi-Fi connection from which data is received.
            thread_manager: The thread manager that manages the thread.
            receive_queue: The queue for storing received data.
        """
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager
        self.receive_queue = receive_queue
        self.logger = logging.getLogger(__name__)

    def run(self):
        """
        The method to run the thread for receiving data.
        """
        self.logger.info("Running ReceiveDataThread")
        while not self.thread_manager.stop_event.is_set():
            try:
                data = self.wifi_connection.sock.recv(512)

                self.receive_queue.put(data)
            except socket.timeout:
                self.logger.warning("Receive timeout, no data received for 5 seconds")
                continue
            except Exception as e:
                MessageWindow.show_error(f"Error during reception!\n Error: {e}")
                break

    def start(self):
        """
        The method to start the thread for receiving data.
        """
        self.logger.info("Starting ReceiveDataThread")
        self.thread_manager.start_threads(self.run, ())