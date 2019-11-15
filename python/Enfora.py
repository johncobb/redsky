from MessageBase import Message
from MessageBase import DeviceType
from MessageBase import MessageFormat
from MessageBase import EventCode
from MessageBase import EventCategory
from MessageBase import GpsStatus

import binascii
import struct


"""
    * Message Format = 1052814 (0x10108E)
    * 
    *	Variable	Length	Start	Stop
    *  --------------------------------
    *	header		4		0		3
    *	parm1		11		4		14
    *	mdmid		22		15		36
    *	iocfg/iogpa	6		37		42
    *	event cat	3		43		45
    *	gprmc		80		46		125 
"""

"""
?: boolean
h: short
l: long
i: int
f: float
q: long long int
"""



# bin_msg_timed = b'\x00\x05\x02\x00\x00\x00\x00\xff 0PT1MU5'
#bin_msg_full = b'\x00\x05\x02\x00\x00\x00\x00\x1f 0PT1MU5p\x10\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x01\x01\x00\x00\x00'

bin_msg_timed = b'\x00\x05\x02\x00\x00\x00\x00241000517\x13\x0b\x0f\x17\x08\x0b'
bin_msg_full = b'\x00\x05\x02\x00\x00\x00\x00\x1f41000517p\x14\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x13\x0b\x0f\x16)\x00'

# bin_timed = struct.pack('hhl', )

class Enfora(Message):

    def __init__(self):
        pass
    
    def __init__(self, data):
        self.data = data
        print("data: ", self.data)

    def get_header(self, packet):
        print(int.from_bytes(packet[:4], byteorder='big', signed=False))

    def get_parm1(self, packet):
        print(int.from_bytes(packet[4:8], byteorder='big', signed=False))

    def get_mdm_id(self, packet):
        print(packet[8:16])

    def get_iocfg(self, packet):
        print(packet[16:17])

    def get_iogpa(self, packet):
        print(packet[17:18])

    def isBinary(self):
        return True


if __name__ == "__main__":

    """ Instantiate base class """
    m = Message("xyz")
    print(m.get_data())

    """ Instantiate derrived class """
    e = Enfora("Enfora")
    print(e.get_data())

    for dt in DeviceType:
        print(dt)

    print(bin_msg_timed)

    msg = bin_msg_full
    print("len: ", len(msg))
    # x = bytearray(bin_msg_timed)

    e.get_header(msg)
    e.get_parm1(msg)
    e.get_mdm_id(msg)

    if (len(msg) > 22):
        e.get_iocfg(msg)
        e.get_iogpa(msg)
