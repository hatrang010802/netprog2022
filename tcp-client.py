import socket

PORT = 1234
BUFSIZE = 1024

s = socket.socket()
s.connect(('', PORT))
# Sending a string
while True:
    m = input("Enter message: ")
    message = m.encode('utf8')
    s.send(message)
    # Receiving a string:
    resp = s.recv(BUFSIZE)
    print("Server: ",resp.decode('utf8'))
    if(m == 'exit' or resp.decode('utf8') == 'exit'):
        print(""" 
        Server is disconnected ... 
        """)
        break
# Closing the connection
s.close()