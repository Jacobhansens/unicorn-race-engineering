import sys
import BaseHTTPServer
from os import curdir, sep
from SimpleHTTPServer import SimpleHTTPRequestHandler
import random
import time
from threading import Thread
import parser
import data
import Queue

q = Queue.Queue()

HandlerClass = SimpleHTTPRequestHandler
ServerClass = BaseHTTPServer.HTTPServer
Protocol = "HTTP/1.0"

speed = 11

if sys.argv[1:]:
	port = int(sys.argv[1])
else:
	port = 9999
server_adress = ('127.0.0.1', port)
going = 1
count = 0

class MyHandler(SimpleHTTPRequestHandler):
	def do_GET(self):
		print "getting!"
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

print "Starting..."
p = parser.parser()
HandlerClass.protocol_version = Protocol
httpd = ServerClass(server_adress, MyHandler)
sa = httpd.socket.getsockname()

try:
	print "Serving HTTP on", sa[0], ":", sa[1], "..."
	p = parser.parser()
	print "Created parser"
	p.daemon = True
	print "made parser into daemon"
	print("what!")
	p.start()
	while True:
		print q.get()
		httpd.handle()
		time.sleep(0.01)	

except (KeyboardInterrupt,SystemExit):
	going = 0
	
httpd.socket.close()
p.close()
print "Quitting"
quit()