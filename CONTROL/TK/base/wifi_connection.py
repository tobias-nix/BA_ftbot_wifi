import socket
from base import ftbot_pb2


class WifiConnection:
    def __init__(self, model):
        self.model = model
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # Create a UDP socket
        self.source_ip = '192.168.10.2'
        self.source_port = 55719
        self.target_ip = '192.168.10.1'
        self.target_port = 58361
        self.sock.bind((self.source_ip, self.source_port))

    def send_data(self):
        message = ftbot_pb2.SetSpeedSteering()
        message.speed = self.model.throttle
        message.steering = self.model.varSteer
        serialized_message = message.SerializeToString()

        # Send the serialized message over the UDP connection
        self.sock.sendto(serialized_message, (self.target_ip, self.target_port))
