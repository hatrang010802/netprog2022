import socket

PORT = 1234
BUFSIZE = 1024

s = socket.socket()
s.bind(('', PORT))
s.listen(0)

while True:
    # Waiting for a connection
    cnx, addr = s.accept()
    print(type(cnx), type(addr))
    while True:
        # reading data from this connection
        msg = cnx.recv(BUFSIZE)
        print("Client: ", msg.decode('utf8'))
        response = input("Enter response: ")
        resp = response.encode('utf8')
        cnx.send(resp)
        if(msg.decode('utf8') == 'exit' or response == 'exit'):
            print("""
            Client is disconnected ...
            Waiting for another client ...
            """)
            break
    
    