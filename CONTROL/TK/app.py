import logging
import sys
from controllers.control import Controller
from controllers.queue_receive import ReceiveQueue
from controllers.receive_thread import ReceiveThread
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from controllers.transmit_thread import TransmitThread


class App:
    def __init__(self):
        self.controller = Controller()
        self.receive_queue = ReceiveQueue()
        self.wifi_connection = WifiConnection(self.controller.model, self.receive_queue)
        self.thread_manager = ThreadManager()

    def main(self):
        logging.basicConfig(filename='app.log', filemode='w', format='%(name)s - %(levelname)s - %(message)s', level=logging.INFO)

        self.receive_thread()
        self.transmit_thread()
        self.controller.run()
        self.thread_manager.stop_threads()

    def receive_thread(self):
        receive_thread_call = ReceiveThread(self.wifi_connection, self.thread_manager, self.receive_queue)
        try:
            receive_thread_call.start()
        except Exception as e:
            logging.error(f"User canceled during connection check!\n Error: {e}")
            sys.exit()

    def transmit_thread(self):
        transmit_thread_call = TransmitThread(self.wifi_connection, self.thread_manager)
        transmit_thread_call.start()


if __name__ == "__main__":
    app = App()
    app.main()
