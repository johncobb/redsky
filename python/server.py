import socket
import binascii
from datetime import datetime
# UDP_ADDRESS = "127.0.0.1" # only listens on local interface
UDP_ADDRESS = "0.0.0.0" # listens on all interfaces
#UDP_PORT = 8080
UDP_PORT = 1721


""" sainity check the server connection with netcat
setup litener
server: sudo nc -u -l 1721 # setup listener

setup client
client: nc -zv ec2-3-84-199-221.compute-1.amazonaws.com -u 8080 # send data
"""
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server.bind((UDP_ADDRESS, UDP_PORT))
"""
byte[] HeaderBytes = _next(4);
byte[] Parm1Bytes = _next(4); // Event Code
byte[] MDMIDBytes = _next(8); // Device ID
byte[] IOCFGBytes = _next(1);
byte[] IOGPABytes = _next(1);
byte[] ADC2Bytes = _next(2);
byte[] EventCategoryBytes = _next(1);
byte[] GpsDateBytes = _next(3);
byte[] GpsStatusBytes = _next(1);
byte[] GpsLatitudeBytes = _next(3);
byte[] GpsLongitudeBytes = _next(4);
byte[] GpsVelocityBytes = _next(2);
byte[] GpsHeadingBytes = _next(2);
byte[] GpsTimeBytes = _next(3);
byte[] GpsAltitudeBytes = _next(3);
byte[] GpsSatellitesBytes = _next(1);
byte[] GpsOdometerBytes = _next(4);
byte[] RTCBytes = _next(6);
"""

enfora_hdr = ""
enfora_parm1 = ""
enfora_mdmid = ""

def parse_binary(data):
    enfora_hdr = data[:4]
    enfora_parm1 = data[4:4]
    enfora_mdmid = data[8:8]

    print("parse binary")

if __name__ == "__main__":
    print("udp server running...")

    while True:
        data, addr = server.recvfrom(64)

        # mark timestamp
        now = datetime.now()
        # format timestamp
        ftime = now.strftime("%c")
        # record length of data 
        data_len = len(data)
        
        # current enfora lengh is 52 bytes
        # log out message
        #print("Header:" , data[:4])
        print("Message:", data, len(data), addr, ftime)


