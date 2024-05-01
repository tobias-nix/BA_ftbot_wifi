import time
import subprocess
from base import ftbot_pb2
from controllers.queue_receive import ReceiveQueue
from controllers.thread_manager import ThreadManager
from base.wifi_connection import WifiConnection


class ReceiveThread:
    def __init__(self, wifi_connection: WifiConnection, thread_manager: ThreadManager, receive_queue: ReceiveQueue):
        self.wifi_connection = wifi_connection
        self.thread_manager = thread_manager
        self.receive_queue = receive_queue

    def run(self):
        print("Running ReceiveThread")
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
            except Exception as e:
                print(f"Error in ReceiveThread: {e}")

    def start(self):
        print("Starting ReceiveThread")
        if self.wifi_connection.check_connection():
            self.thread_manager.start_threads(self.run, ())

    def stop(self):
        print("Stopping ReceiveThread")
        self.thread_manager.stop_threads()