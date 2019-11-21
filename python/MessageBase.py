from enum import Enum
from enum import IntEnum


class DeviceType(IntEnum):
    Enfora = 1
    Nordic = 2

class MessageFormat(Enum):
    ASCII = 0
    Binary = 1

class GpsStatus(Enum):
    Valid = 'A'
    Invalid = 'V'
    Unknown = '?'

class EventCode(IntEnum):
    Timed = 1
    Distance = 2
    IgnitionOn = 3
    IgnitionOff = 4
    Idle = 5
    Invisible = 6
    TimedReportAck = 11
    DistanceReportAck = 22
    Powerup = 50
    Timeclock = 99
    CellInfo = 900
    FirmwareInfo = 901
    Unknown = 999

class EventCategory(IntEnum):
    Ignition = 7
    Powerup = 8
    Timer2 = 13
    Timer3 = 14
    GpsDistance = 16
    Idle = 30
    Timeclock = 99
    Unknown = 999

class Message(object):
    def __init__(self, data):
        self.data = data

    def get_data(self):
        return self.data

class Enfora(Message):

    def isBinary(self):
        return True


if __name__ == "__main__":

    """ IntEnum and Enum work differently """
    print(EventCode.Timed == 1)
    print(EventCode.Distance == 2)
    print('A' == GpsStatus.Valid.value)

    """ Create a message object """
    m = Message("xyz")
    print(m.get_data())

    e = Enfora("enfora")
    print(e.get_data())
    print(e.isBinary())
