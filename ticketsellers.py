import socket
import socketserver
import sys
import time

TICKETNUM = 1024

class MyTCPSocketHandler(socketserver.BaseRequestHandler):
    def handle(self):
        ticketcount = 0
        while True:
            self.data = self.request.recv(TICKETNUM).strip()
            print(f"{self.client_address[0]} wrote: \n {self.data}")
            waittime = 1
            print(f"{self.client_address[0]} waiting for {waittime} seconds")
            time.sleep(waittime)

            ticknum = "You bought ticket number {ticketcount}".encode('utf8')
            self.request.sendall(ticknum)
            ticketcount = ticketcount + 1
            

if __name__ == "__main__":
    # if len(sys.argv) != 2:
    #     print("Usage: tcp-server port")
    #     exit(1)
    port = int(sys.argv[1])
    server = socketserver. ForkingTCPServer( ("", port), MyTCPSocketHandler)
    #server = socketserver. ThreadingTCPServer( ("", port), MyTCPSocketHandler)
    server.serve_forever()