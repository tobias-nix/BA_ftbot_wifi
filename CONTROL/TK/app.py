import logging
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
        logging.basicConfig(level=logging.ERROR, format='%(funcName)s() - %(levelname)s: %(message)s')

        self.transmit_thread()
        self.receive_thread()
        self.controller.run()
        self.thread_manager.stop_threads()

    def transmit_thread(self):
        transmit_thread_call = TransmitThread(self.wifi_connection, self.thread_manager)
        transmit_thread_call.start()

    def receive_thread(self):
        receive_thread_call = ReceiveThread(self.wifi_connection, self.thread_manager, self.receive_queue)
        receive_thread_call.start()


if __name__ == "__main__":
    app = App()
    app.main()
