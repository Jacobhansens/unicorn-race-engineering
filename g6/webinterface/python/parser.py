import threading
import time
import serial

'''
The objective for this class is to run a Thread which handles the serial communication.
This object should parse the different types of data and write these to a mysql database.
The communication should be robust to lost packages, by attempting to find start sequences 
in the datastring, if it is incomplete.
'''



class parser(threading.Thread):
	def __init__(self,connectionname = None,speed=None):
		threading.Thread.__init__(self)
		if(speed == None):
			speed = 115200
		if connectionname == None:
			connectionname = "/dev/tty.usbserial-A700eCo8"
		self.running = 0
		self.conn = serial.Serial(connectionname,speed)
		
	def close(self):
		self.conn.close()
		self.running = 0
		
	def run(self):
		while self.conn.isOpen():
			print i
			i = i+1
	
	def parse(data):

print "Starting thread"
t = parser()
t.start()
time.sleep(2)
t.running=0;
	