from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional

DESCRIPTOR: _descriptor.FileDescriptor

class SetSpeedSteering(_message.Message):
    __slots__ = ("speed", "steering")
    SPEED_FIELD_NUMBER: _ClassVar[int]
    STEERING_FIELD_NUMBER: _ClassVar[int]
    speed: float
    steering: float
    def __init__(self, speed: _Optional[float] = ..., steering: _Optional[float] = ...) -> None: ...

class RobotStatus(_message.Message):
    __slots__ = ("true_left_speed", "true_right_speed", "voltage")
    TRUE_LEFT_SPEED_FIELD_NUMBER: _ClassVar[int]
    TRUE_RIGHT_SPEED_FIELD_NUMBER: _ClassVar[int]
    VOLTAGE_FIELD_NUMBER: _ClassVar[int]
    true_left_speed: float
    true_right_speed: float
    voltage: float
    def __init__(self, true_left_speed: _Optional[float] = ..., true_right_speed: _Optional[float] = ..., voltage: _Optional[float] = ...) -> None: ...
