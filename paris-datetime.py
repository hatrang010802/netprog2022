from http.server import BaseHTTPRequestHandler, HTTPServer
from datetime import datetime
import pytz

hostName = "localhost"
serverPort = 8888

class MyServer(BaseHTTPRequestHandler):
    def do_GET(self):
        self.send_response(200)
        self.send_header("Content-type", "text/html")
        self.end_headers()
        self.wfile.write(bytes("<html><head><title> Welcome to Paris </title></head>", "utf-8"))
        self.wfile.write(bytes("<p>Display the date and time now in Paris: </p>", "utf-8"))
        self.wfile.write(bytes("<body>", "utf-8"))
        Paris = pytz.timezone('Europe/Paris')
        datetime_paris = datetime.now(Paris)
        string = datetime_paris.strftime('%d/%m/%Y at %H:%M:%S %Z %z')
        self.wfile.write(bytes("<p>Now is: %s </p>" %string , "utf-8"))
        self.wfile.write(bytes("</body></html>", "utf-8"))
        

if __name__ == "__main__":        
    webServer = HTTPServer((hostName, serverPort), MyServer)
    print("Server started http://%s:%s/date/paris" % (hostName, serverPort))

    try:
        webServer.serve_forever()
    except KeyboardInterrupt:
        pass

    webServer.server_close()
    print("Server stopped.")