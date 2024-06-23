"""
Constants for the application

Constants:
    | STEERING_RADIUS: The radius of the steering circle.
    | STEERING_ANGLE_FACTOR: The factor to convert steering angle to steering value.
    | CANVAS_CENTER_X: The x-coordinate of the center of the canvas.
    | CANVAS_CENTER_Y: The y-coordinate of the center of the canvas.
    | STEERING_INCREMENT: The increment value for steering.
    | MAX_THROTTLE: The maximum throttle value.
    | MIN_THROTTLE: The minimum throttle value.
    | THROTTLE_INCREASE_RATE: The rate at which the throttle increases.
    | THROTTLE_DECREASE_RATE: The rate at which the throttle decreases.
    | THROTTLE_ZERO_THRESHOLD: The threshold below which the throttle is considered zero.
    | GAME_LOOP_DELAY: The delay for the game loop in milliseconds.
"""

STEERING_RADIUS = 235
STEERING_ANGLE_FACTOR = 0.84
CANVAS_CENTER_X = 450
CANVAS_CENTER_Y = 590
STEERING_INCREMENT = 8
MAX_THROTTLE = 100
MIN_THROTTLE = -100
THROTTLE_INCREASE_RATE = 3
THROTTLE_DECREASE_RATE = 10
THROTTLE_ZERO_THRESHOLD = 10
GAME_LOOP_DELAY = 100