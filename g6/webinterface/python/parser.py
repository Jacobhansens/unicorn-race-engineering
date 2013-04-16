import threading
import time
import serial
import Queue
import struct


'''
The objective for this class is to run a Thread which handles the serial communication.
This object should parse the different types of data and write these to a mysql database.
The communication should be robust to lost packages, by attempting to find start sequences 
in the datastring, if it is incomplete.

255, 123, 10, datatype,
datalength defined in datatype definition

'''



class parser(threading.Thread):
	def __init__(self,connectionname = None,speed=None):
		threading.Thread.__init__(self)
		if(speed == None):
			speed = 115200
		if connectionname == None:
			connectionname = "/dev/tty.usbserial-A700eCo8"
		self.running = 0
		self.conn = serial.Serial(connectionname,speed,timeout=1)
		
	def close(self):
		self.conn.close()
		self.running = 0
		
	def run(self):
		dataType = 0
		while self.conn.isOpen():
			
			if self.conn.inWaiting() > 0:
				tmp = self.conn.read()
				if tmp == 255:
					tmp = self.conn.read()
					if tmp == 123:
						tmp = self.conn.read()
						if tmp == 10:
							dataType = self.conn.read()
							length = getDataLength(dataType)
							data = []
							for i in range(length):
								data.append(self.conn.read())
							parse(dataType,data)

			time.sleep(0.001)
	
	def parse(self,dataType,data):
		
	
	def getDataLength(self,data):
		return 2
		

if __name__ == '__main__':
	print "Starting thread"
	t = parser()
	t.start()
	time.sleep(2)
	t.running=0;
	