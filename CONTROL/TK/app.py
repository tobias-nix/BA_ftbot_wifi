import logging
from controllers.control import Controller
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from controllers.transmit_thread import TransmitThread


class App:
    def __init__(self):
        self.controller = Controller()
        self.wifi_connection = WifiConnection(self.controller.model)
        self.thread_manager = ThreadManager()

    def main(self):
        logging.basicConfig(level=logging.ERROR, format='%(funcName)s() - %(levelname)s: %(message)s')

        self.transmit_thread()
        self.controller.run()
        self.thread_manager.stop_threads()

    def transmit_thread(self):
        transmit_thread_call = TransmitThread(self.wifi_connection, self.thread_manager)
        transmit_thread_call.start()


if __name__ == "__main__":
    app = App()
    app.main()
