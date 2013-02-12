import sys
import BaseHTTPServer
from os import curdir, sep
from SimpleHTTPServer import SimpleHTTPRequestHandler

HandlerClass = SimpleHTTPRequestHandler
ServerClass = BaseHTTPServer.HTTPServer
Protocol = "HTTP/1.0"

speed = 11

if sys.argv[1:]:
	port = int(sys.argv[1])
else:
	port = 8000
server_adress = ('127.0.0.1', port)

class MyHandler(SimpleHTTPRequestHandler):
	def do_GET(self):
		try:
			if self.path == "/test.xml":
				self.send_response(200)
				self.send_header('Content-type', 'text/xml')
				self.end_headers()
				self.wfile.write(("<Car><speed>" + str(speed) + "</speed><force>23</force><heading>32</heading></Car>"))
				return
			elif self.path.endswith(".html"):
				f = open(curdir + sep + self.path)
				self.send_response(200) 
				self.send_header("Content-type", 'text/html')
				self.end_headers()
				self.wfile.write(f.read())
				f.close()
				return
			return
		except IOError:
			self.send_error(404,'File Not Found: %s' % self.path)
	def do_POST(self):
		global rootnode


HandlerClass.protocol_version = Protocol
httpd = ServerClass(server_adress, MyHandler)

sa = httpd.socket.getsockname()
print "Serving HTTP on ", sa[0], ":", sa[1], "..."
httpd.serve_forever()