import socket
import logging
import sys
import subprocess
import netifaces

from base import ftbot_pb2
from controllers.queue_receive import ReceiveQueue
from views.message_window import MessageWindow


class WifiConnection:
    def __init__(self, model, receive_queue: ReceiveQueue):
        self.model = model
        self.receive_queue = receive_queue
        self.interface = self.get_interface_by_ssid("ESP_01_NIX") # TODO: Change this to the actual SSID and ip
        self.sockety = socket.gethostbyname(socket.gethostname())
        self.source_ip = socket.gethostbyname(self.interface)
        self.source_port = 55719
        source_ip_parts = self.source_ip.split('.')
        target_ip_parts = ['192', '168', source_ip_parts[2], '1']
        self.target_ip = '.'.join(target_ip_parts)
        self.target_port = 58361
        self.logger = logging.getLogger(__name__)
        self.sock = self.create_socket()

    def get_interface_by_ssid(self, ssid):
        for interface in netifaces.interfaces():
            try:
                output = subprocess.check_output(['netsh', 'wlan', 'show', 'interfaces']).decode('utf-8', errors='ignore')
                if ssid in output:
                    return interface
            except subprocess.CalledProcessError:
                pass
        return None

    def create_socket(self):
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.sock.bind((self.source_ip, self.source_port))
            self.sock.settimeout(5)
            return self.sock
        except socket.error as e:
            MessageWindow.show_error(f"Failed to create socket!\n Error: {e}")
            return False

    def check_connection(self):
        return True # Remove this line for full implementation !!!

        try:
            data, addr = self.sock.recvfrom(11)
            message = data.decode()

            if message == "ftbot_ready":
                response = f"ip:{self.source_ip}_port:{self.source_port}"
                self.sock.sendto(response.encode(), addr)
                return True
        except socket.timeout:
            retry = MessageWindow.show_question("Connection check timed out! Trying again...")
            if not retry:
                raise Exception("Cancelled by user!")
            else:
                self.check_connection()
        except Exception as e:
            MessageWindow.show_error(f"Error during connection check!\n Error: {e}")
        return True


    def send_data(self, steering, throttle):
        try:
            # Create an instance of the SetSpeedSteering message
            message = ftbot_pb2.SetSpeedSteering()

            # Set the left_speed and steering attributes
            message.speed = throttle
            message.steering = steering

            # Serialize the message to a string
            serialized_message = message.SerializeToString()

            # Create a new message instance for deserialization
            deserialized_message = ftbot_pb2.SetSpeedSteering()
            deserialized_message.ParseFromString(serialized_message)

            self.logger.info("Sending data: %s, Deserialized: %s", serialized_message, deserialized_message)

            # Send the serialized message over the socket
            # self.sock.sendto(serialized_message, (self.target_ip, self.target_port))
        except Exception as e:
            MessageWindow.show_error(f"Error during transmission!\n Error: {e}")

