import sys
import BaseHTTPServer
from os import curdir, sep
from SimpleHTTPServer import SimpleHTTPRequestHandler
import random
import time
from threading import Thread

HandlerClass = SimpleHTTPRequestHandler
ServerClass = BaseHTTPServer.HTTPServer
Protocol = "HTTP/1.0"

speed = 11

if sys.argv[1:]:
	port = int(sys.argv[1])
else:
	port = 8000
server_adress = ('127.0.0.1', port)
going = 1
count = 0
class writer(Thread):
	
	def run(self):
		self.count = 0
		while going:
			self.count += 1
		
			f = open('tester.xml','w')
			f.write("<?xml version='1.0' encoding='UTF-8' ?><Car><speed>" + str(self.count) + "</speed></Car>")
			f.close()
			time.sleep(1)
w = writer()
w.start()

class MyHandler(SimpleHTTPRequestHandler):
	def do_GET(self):
		try:
			if self.path == "/test.xml":
				xmlstr = '<?xml version="1.0" encoding="UTF-8" ?>\n<Car><variables><speed>' + str(speed) + '</speed><force><X>' + str(11+random.random()) + '</X><Y>21</Y><Z>9</Z></force><heading>180</heading></variables></Car>'
				self.send_response(200)
				self.send_header('Content-type', 'text/xml')
				self.end_headers()
				self.wfile.write(xmlstr)
				return
			elif self.path.endswith(".xml"):
				f = open(curdir + sep + self.path)
				self.send_response(200) 
				self.send_header("Content-type", 'text/xml')
				self.end_headers()
				self.wfile.write(f.read())
				f.close()
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
try:
	httpd.serve_forever()
except KeyboardInterrupt:
	going = 0
	t.join()
	quit()