import logging
import socket

from views.message_window import MessageWindow
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from controllers.queue_receive import ReceiveQueue


class ReceiveDataThread:
    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager, receive_queue: ReceiveQueue):
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager
        self.receive_queue = receive_queue
        self.logger = logging.getLogger(__name__)

    def run(self):
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
        self.logger.info("Starting ReceiveDataThread")
        self.thread_manager.start_threads(self.run, ())
