import socket
#import sys

#print(sys.argv)
BUFSIZE = 1024
PORT = int(input("Enter port: "))
print("Started server on UDP/{}".format(PORT))
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #udp
s.bind(("", PORT)) #port
data, addr = s.recvfrom(BUFSIZE) #bufsize
print("client {} sent '{}'".format(addr[0], data.decode('utf8')))

