








import time

import socket

#UDP_ADDRESS = "ec2-user@ec2-3-84-199-221.compute-1.amazonaws.com"
UDP_ADDRESS = "3.84.199.221"
#UDP_ADDRESS = "172.31.90.117"
#UDP_PORT = 8080
UDP_PORT = 1721
Message = "Ground Control to Major Tom"

client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

while True:
    client.sendto(Message, (UDP_ADDRESS, UDP_PORT))
    time.sleep(1)
