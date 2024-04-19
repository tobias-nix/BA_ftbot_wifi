import unittest
from base import ftbot_pb2
from base.wifi_connection import WifiConnection


# Create a Model class for testing purposes
class Model:
    def __init__(self, throttle, varSteer):
        self.throttle = throttle
        self.varSteer = varSteer


class TestWifiConnection(unittest.TestCase):
    def test_send_data(self):
        # Instantiate the Model class and set the throttle and varSteer values
        model = Model(0.5, 0.3)

        # Instantiate the WifiConnection class with the Model instance
        wifi_connection = WifiConnection(model)

        # Call the send_data method
        serialized_message = wifi_connection.send_data()

        # Deserialize the serialized message
        message = ftbot_pb2.SetSpeedSteering()
        message.ParseFromString(serialized_message)

        # Check if the speed and steering fields are equal to the throttle and varSteer values
        self.assertEqual(message.speed, model.throttle)
        self.assertEqual(message.steering, model.varSteer)


if __name__ == '__main__':
    unittest.main()
