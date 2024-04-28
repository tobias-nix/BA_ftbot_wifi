import socket
from base import ftbot_pb2


class WifiConnection:
    def __init__(self, model):
        self.model = model
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.source_ip = socket.gethostbyname('0.0.0.0')
        self.source_port = 55719
        self.target_ip = '192.168.10.1'
        self.target_port = 58361
        # self.sock.bind((self.source_ip, self.source_port))

    def check_connection(self):
        # TODO: check if the connection is established
        return True

    def send_data(self, steering, throttle):
        # Create an instance of the SetSpeedSteering message
        message = ftbot_pb2.SetSpeedSteering()

        # Set the speed and steering attributes
        message.speed = throttle
        message.steering = steering

        # Serialize the message to a string
        serialized_message = message.SerializeToString()

        # Create a new message instance for deserialization
        deserialized_message = ftbot_pb2.SetSpeedSteering()
        deserialized_message.ParseFromString(serialized_message)

        print("Sending data: ", serialized_message, "Deserialized: ", deserialized_message)

        # Send the serialized message over the socket
        # self.sock.sendto(serialized_message, (self.target_ip, self.target_port))
