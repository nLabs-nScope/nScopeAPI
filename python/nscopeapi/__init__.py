from ctypes import byref
from nscopeapi.nScopeDefs import *

import nscopeapi.analogInputs
import nscopeapi.analogOutputs
import nscopeapi.pulseGenerators
import nscopeapi.requests
import nscopeapi.sampleTiming
import nscopeapi.trigger

def ERR(error):
	if error == 0:
		return
	if error == -100:
		raise RuntimeError("Unkown error")
	if error == -101:
		raise RuntimeError("nScope is not available")
	if error == -102:
		raise RuntimeError("")
	if error == -109:
		raise RuntimeError("Firmware and API are incompatible")



class nScope(
	nscopeapi.analogInputs.Implementation,
	nscopeapi.analogOutputs.Implementation,
	nscopeapi.pulseGenerators.Implementation,
	nscopeapi.requests.Implementation,
	nscopeapi.sampleTiming.Implementation,
	nscopeapi.trigger.Implementation):

	def __init__(self):

		self.handle = scopeHandle()
		self.request = scopeRequest()

		lib.nScope_open(True,byref(self.handle))
		if self.handle:
			lib.nScope_initialize(self.handle)
		else:
			raise RuntimeError("Cannot connect to nScope")

	def readCh1(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(True,False,False,False)
		self.setSampleRateInHz(samplerate)
		self.requestData(numsamples)

		data = []
		while self.requestHasData():
			data.append(self.readData(1))
		return data

	def readCh2(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(False,True,False,False)
		self.setSampleRateInHz(samplerate)
		self.requestData(numsamples)

		data = []
		while self.requestHasData():
			data.append(self.readData(2))
		return data

	def readCh3(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(False,False,True,False)
		self.setSampleRateInHz(samplerate)
		self.requestData(numsamples)

		data = []
		while self.requestHasData():
			data.append(self.readData(3))
		return data

	def readCh4(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(False,False,False,True)
		self.setSampleRateInHz(samplerate)
		self.requestData(numsamples)

		data = []
		while self.requestHasData():
			data.append(self.readData(4))
		return data
