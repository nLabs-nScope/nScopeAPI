from ctypes import byref
from nScopeDefs import *

import analogInputs
import analogOutputs
import pulseGenerators
import requests
import sampleTiming
import trigger

class nScope(
	analogInputs.Implementation,
	analogOutputs.Implementation,
	pulseGenerators.Implementation,
	requests.Implementation,
	sampleTiming.Implementation,
	trigger.Implementation):

	def __init__(self):

		self.handle = scopeHandle()
		self.request = scopeRequest()

		nScopeAPI.nScope_open(True,byref(self.handle))
		if self.handle:
			nScopeAPI.nScope_initialize(self.handle)
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
