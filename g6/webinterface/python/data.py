from new import classobj

class data(object):
	def __init__(self):#,name,ID,active,rounddec,datalength,max,min):
		self.name = "Empty"
		self.ID = 0
		self.active = 0
		self.rounddec = 0
		self.datalength = 0
		self.max = 9999
		self.min = 0
	
	def conv(self,x):
		return x;
		
class FuelPress(data):
	def __init__(self):
		self.name = "Fuel Press"
		self.ID = 1
		self.active = 0
		self.rounddec = 2
		self.datalength = 16
	def conv(self,x):
		return x*2
		
class StatusLapCount(data):
	def __init__(self):
		self.name = "StatusLapCount"
		self.ID = 2
		self.active = 0
		self.rounddec = 2
		self.datalength=16
	
	def conv(self,x):
		return x*self.ID
		
class StatusInJSum(data):
	def __init__(self):
		self.name = "StatusInJSum"
		self.ID = 3
		self.active = 0
		self.rounddec = 2
		self.datalength=16
	
	def conv(self,x):
		return x*self.ID
		
class lastGearShift(data):
	def __init__(self):
		self.name = "lastGearShift"
		self.ID = 4
		self.active = 0
		self.rounddec = 2
		self.datalength=16
	
	def conv(self,x):
		return x
			
class motorOilTemp(data):
	def __init__(self):
		self.name = "motorOilTemp"
		self.ID = 5
		self.active = 0
		self.rounddec = 2
		self.datalength=16
	
	def conv(self,x):
		return x
		
class oilPressure(data):
	def __init__(self):
		self.name = "oilPressure"
		self.ID = 6
		self.active = 0
		self.rounddec = 2
		self.datalength=16
	
	def conv(self,x):
		return x
		
class statusTime(data):
	def __init__(self):
		self.name = "statusTime"
		self.ID = 7
		self.active = 0
		self.rounddec = 2
		self.datalength=16
	
	def conv(self,x):
		return x
		
		
		
	
def class_with_method(conv):
	class klass: pass
	setattr(klass, conv.__name__, conv)
	print conv.__name__
	print "made it"
	return klass
	
	
#Foo = class_with_method('say_foo': lambda print 'foo')
#Foo = class_with_method({"sho": {lambda self, x: x*2}})
modes = dict()
foo ={'func': lambda x: x*2}

	
class Fuelpress(data):
	def __init__(self):
		self.name = "Fuel Press"
		self.ID = 1
		self.active = 0
		self.rounddec = 2
	def conv(self,x):
		return x*2
		
class datatype(object):

	def __init__(self,key):
		
		if(key == 0):
			pass
		elif(key == 1):
			self.__class__ = Fuelpress
		elif(key == 2):
			self.__class__ = StatusLapCount
		elif(key == 3):
			self.__class__ = StatusInJSum
		
		if(key is not 0):
			self.__init__()
	
		
kl = datatype(3)
#m = Foo()
if __name__ == "__main__":
	print "lol"
	m = foo['func']
	print m(2)