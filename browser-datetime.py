from http.server import BaseHTTPRequestHandler, HTTPServer
from datetime import datetime 

hostName = "localhost"
serverPort = 8888

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<html><head><title> Welcome to HT world </title></head>", "utf-8"))
        self.wfile.write(bytes("<p>Display the date and time now in my browser: </p>", "utf-8"))
        self.wfile.write(bytes("<body>", "utf-8"))
        now = datetime.now()
        string = now.strftime("%d/%m/%Y at %H:%M:%S")
        self.wfile.write(bytes("<p>Now is: %s </p>" %string , "utf-8"))
        self.wfile.write(bytes("</body></html>", "utf-8"))
        

if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s/date" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")