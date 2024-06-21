import time
import logging
from base import ftbot_pb2
from controllers.queue_receive import ReceiveQueue
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection
from views.message_window import MessageWindow


class ReceiveProcessThread:
    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager, receive_queue: ReceiveQueue):
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager
        self.receive_queue = receive_queue
        self.logger = logging.getLogger(__name__)

    def run(self):
        self.logger.info("Running ReceiveProcessThread")
        true_left_speed = true_right_speed = voltage = None
        while not self.thread_manager.stop_event.is_set():
            # Fetch the data from the queue
            if self.receive_queue.is_empty():
                time.sleep(0.1)
                continue

            data = self.receive_queue.get()
            

            try:
                # Deserialize the message
                robot_status = ftbot_pb2.RobotStatus()
                robot_status.ParseFromString(data)

                # Extract the speed and voltage values
                true_left_speed = robot_status.true_left_speed
                true_right_speed = robot_status.true_right_speed
                voltage = robot_status.voltage

                # Update the model's speed and voltage with the received values
                self.wifi_connection.model.set_speed(true_left_speed, true_right_speed)
                self.wifi_connection.model.set_voltage(voltage)
                self.logger.info(
                    f"Data: True Left Speed: {true_left_speed}, True Right Speed: {true_right_speed}, Voltage: {voltage}")
            except Exception as e:
                self.logger.error(f"Error in process receive thread!\n Error: {e}")
                self.logger.error(f"Data: True Left Speed: {true_left_speed}, True Right Speed: {true_right_speed}, Voltage: {voltage}")
                # MessageWindow.show_error(f"Error in process receive thread!\n Error: {e}")

    def start(self):
        self.logger.info("Starting ReceiveProcessThread")

        if self.wifi_connection.check_connection():
            self.thread_manager.start_threads(self.run, ())
