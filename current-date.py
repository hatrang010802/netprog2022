from http.server import BaseHTTPRequestHandler, HTTPServer
from datetime import datetime 
import json

hostName = "localhost"
serverPort = 8888

class MyServer(BaseHTTPRequestHandler):
    
    # def myconverter(self):
    #     if isinstance(self, datetime.datetime):
    #         return self.__str__()
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<html><head><title> Welcome to world </title></head>", "utf-8"))
        self.wfile.write(bytes("<p>Display the current date and time in my browser: </p>", "utf-8"))
        self.wfile.write(bytes("<body>", "utf-8"))
        d = {}
        now = datetime.now()
        d['date and time'] = now.strftime("%d/%m/%Y at %H:%M:%S")    
        self.wfile.write(bytes("<p>Now in json file: %s </p>" %json.dumps(d) , "utf-8"))
        self.wfile.write(bytes("</body></html>", "utf-8"))
    

if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s/api/date" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")