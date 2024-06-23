import socket
import logging
import configparser

from base import ftbot_pb2
from controllers.queue_receive import ReceiveQueue
from views.message_window import MessageWindow

# HTerm settings: AT+CIPSTART="UDP","192.168.10.2",55719,58361,0

class WifiConnection:
    """
    The WifiConnection class is responsible for managing the Wi-Fi connection of the robot.

    Attributes:
        model: The model of the robot.
        receive_queue: The queue for receiving data.
        source_ip: The source IP address.
        source_port: The source port number.
        target_ip: The target IP address.
        target_port: The target port number.
        logger: The logger for logging information.
        sock: The socket for the connection.
    """

    def __init__(self, model, receive_queue: ReceiveQueue):
        """
        The constructor for the WifiConnection class.

        Parameters:
            model: The model of the robot.
            receive_queue: The queue for receiving data.
        """
        self.model = model
        self.receive_queue = receive_queue

        try:
            config = configparser.ConfigParser()
            config.read('config.ini')

            mode = config.get('NETWORK', 'Mode')
            if mode == 'Auto':
                self.source_ip = socket.gethostbyname(socket.gethostname())
            elif mode == 'Manual':
                self.source_ip = config.get('NETWORK', 'IP')
            else:
                raise ValueError('Invalid mode in config file')
        except Exception as e:
                MessageWindow.show_error(f"Error in socket config file!\n Error: {e}")

        self.source_port = 55719
        source_ip_parts = self.source_ip.split('.')
        target_ip_parts = ['192', '168', source_ip_parts[2], '1']
        self.target_ip = '.'.join(target_ip_parts)
        self.target_port = 58361
        self.logger = logging.getLogger(__name__)
        self.sock = self.create_socket()

    def create_socket(self):
        """
        The method to create a socket for the connection.

        Returns:
            The created socket.
        """
        try:
            self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.sock.bind((self.source_ip, self.source_port))
            self.sock.settimeout(5)
            return self.sock
        except socket.error as e:
            MessageWindow.show_error(f"Failed to create socket!\n Error: {e}")
            return False

    def send_data(self, steering: int, throttle: int):
        """
        The method to send data over the socket.

        Parameters:
            steering: The steering value.
            throttle: The throttle value.
        """
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
            self.sock.sendto(serialized_message, (self.target_ip, self.target_port))
        except Exception as e:
            MessageWindow.show_error(f"Error during transmission!\n Error: {e}")