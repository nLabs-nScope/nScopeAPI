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




	# def readCh1(self,numsamples,samplerate):
	# 	numsamples = int(numsamples)
	# 	self.setChannelsOn(1,0,0,0)
	# 	self.setSampleRateInHz(samplerate)
	# 	self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
	# 	if not self.request:
	# 		print 'Invalid Request'
	# 		return
	# 	data = []
	# 	while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
	# 		data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),1))
	# 	nScopeAPI.nScope_release_request(self.handle,byref(self.request))
	# 	self.request = None
	# 	return data
	# def readCh2(self,numsamples,samplerate):
	# 	numsamples = int(numsamples)
	# 	self.setChannelsOn(0,1,0,0)
	# 	self.setSampleRateInHz(samplerate)
	# 	self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
	# 	if not self.request:
	# 		print 'Invalid Request'
	# 		return
	# 	data = []
	# 	while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
	# 		data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),2))
	# 	nScopeAPI.nScope_release_request(self.handle,byref(self.request))
	# 	self.request = None
	# 	return data
	# def readCh3(self,numsamples,samplerate):
	# 	numsamples = int(numsamples)
	# 	self.setChannelsOn(0,0,1,0)
	# 	self.setSampleRateInHz(samplerate)
	# 	self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
	# 	if not self.request:
	# 		print 'Invalid Request'
	# 		return
	# 	data = []
	# 	while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
	# 		data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),3))
	# 	nScopeAPI.nScope_release_request(self.handle,byref(self.request))
	# 	self.request = None
	# 	return data
	# def readCh4(self,numsamples,samplerate):
	# 	numsamples = int(numsamples)
	# 	self.setChannelsOn(0,0,0,1)
	# 	self.setSampleRateInHz(samplerate)
	# 	self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
	# 	if not self.request:
	# 		print 'Invalid Request'
	# 		return
	# 	data = []
	# 	while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
	# 		data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),4))
	# 	nScopeAPI.nScope_release_request(self.handle,byref(self.request))
	# 	self.request = None
	# 	return data
