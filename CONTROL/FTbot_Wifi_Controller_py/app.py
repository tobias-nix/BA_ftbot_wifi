import logging
import sys
from controllers.control import Controller
from controllers.queue_receive import ReceiveQueue
from controllers.receive_process_thread import ReceiveProcessThread
from controllers.receive_data_thread import ReceiveDataThread
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from controllers.transmit_thread import TransmitThread

"""
This module is the main application module. It creates an instance of the App class and starts the main application loop.
"""

class App:
    """
    The main application class. It manages the threads and controllers.
    """
    def __init__(self):
        """
        Initializes the App with a Controller, ReceiveQueue, WifiConnection, and ThreadManager.
        """
        self.controller = Controller()
        self.receive_queue = ReceiveQueue()
        self.wifi_connection = WifiConnection(self.controller.model, self.receive_queue)
        self.thread_manager = ThreadManager()

    def main(self):
        """
        Initializes the App with a Controller, ReceiveQueue, WifiConnection, and ThreadManager.
        """
        logging.basicConfig(filename='app.log', filemode='w', format='%(name)s - %(levelname)s - %(message)s', level=logging.INFO)

        self.receive_process_thread()
        self.receive_data_thread()
        self.transmit_thread()
        self.controller.run()
        self.thread_manager.stop_threads()

    def receive_process_thread(self):
        """
        Starts the ReceiveProcessThread. If there's an error during the start, it logs the error and exits the program.
        """
        receive_thread_call = ReceiveProcessThread(self.wifi_connection, self.thread_manager, self.receive_queue)
        try:
            receive_thread_call.start()
        except Exception as e:
            logging.error(f"User canceled during connection check!\n Error: {e}")
            sys.exit()

    def receive_data_thread(self):
        """
        Starts the ReceiveDataThread. If there's an error during the start, it logs the error and exits the program.
        """
        receive_thread_call = ReceiveDataThread(self.wifi_connection, self.thread_manager, self.receive_queue)
        try:
            receive_thread_call.start()
        except Exception as e:
            logging.error(f"User canceled during connection check!\n Error: {e}")
            sys.exit()

    def transmit_thread(self):
        """
        Starts the TransmitThread.
        """
        transmit_thread_call = TransmitThread(self.wifi_connection, self.thread_manager)
        transmit_thread_call.start()


if __name__ == "__main__":
    """
    If this script is run directly, it creates an instance of App and starts the main application loop.
    """
    app = App()
    app.main()
