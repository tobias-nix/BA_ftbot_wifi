import logging
from controllers.control import Controller
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from controllers.transmit_thread import TransmitThread


def transmit_thread(controller):
    wifi_connection = WifiConnection(controller.model)
    thread_manager = ThreadManager()
    transmit_thread_call = TransmitThread(wifi_connection, thread_manager)
    transmit_thread_call.start()


def main():
    logging.basicConfig(level=logging.ERROR, format='%(funcName)s() - %(levelname)s: %(message)s')

    c = Controller()
    transmit_thread(c)


if __name__ == "__main__":
    main()
