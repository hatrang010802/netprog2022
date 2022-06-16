import socket
#import sys

#print(sys.argv)
host = input("Enter host: ")
PORT = int(input("Enter port: "))
m = input("Enter message: ")

s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) #udp
while True:
    message = m.encode('utf8')
    s.sendto(message, (host, PORT))
    break

