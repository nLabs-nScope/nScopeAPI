from ctypes import CDLL, Structure, POINTER, c_int, c_double, c_bool, cast, byref
from .types import defineTypes

import platform,os

system = platform.system()

if system == "Darwin":
	nScopeAPI = CDLL(os.path.join(os.path.dirname(__file__), "lib/mac/libnscopeapi.dylib"))
elif system == "Windows":
	nScopeAPI = CDLL(os.path.join(os.path.dirname(__file__), "lib/win32/libnscopeapi.dll"))
elif system == "Linux":
	nScopeAPI = CDLL(os.path.join(os.path.dirname(__file__), "lib/linux_i386/libnscopeapi.so"))

nScopeAPI.nScope_check_API_version.restype = c_double
nScopeAPI.nScope_check_FW_version.restype = c_double


def checkAPIver():
	return nScopeAPI.nScope_check_API_version()

def checkFWver():
	return nScopeAPI.nScope_check_FW_version()

def findFirmwareLoader():
	nScopeAPI.nScope_find_firmware_loader()

def writeToLoader():
    nScopeAPI.nScope_write_to_loader()

def loadFirmware():
	return nScopeAPI.nScope_load_firmware()

class scopeHandle(Structure):
	pass

class request(Structure):
	pass

class nScopeObj(object):

	def __init__(self):

		defineTypes()
		self.handle = nScopeAPI.nScope_open(1)
		self.request = None
		if not self.handle:
			print "Unable to connect to nScope"

	def requestData(self,numsamples):
		if self.request:
			nScopeAPI.nScope_release_request(self.handle,byref(self.request))
		self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
		if not self.request:
			raise ValueError("Invalid request")
			return
	def readData(self,channel):
		rtrn = nScopeAPI.nScope_read_data(self.handle,byref(self.request),channel)
		if rtrn == -106:
			raise ValueError("Invalid request")
			return
		if rtrn == -112:
			raise ValueError("nScope channel does not exist")
			return
		if rtrn == -104:
			raise RuntimeWarning("No more data available")
			return
		if rtrn == -102:
			raise RuntimeWarning("nScope channel was not on during request")
			return
		return rtrn
	def requestHasData(self):
		if not self.request:
			return False
		rtrn = nScopeAPI.nScope_request_has_data(self.handle,self.request)
		if rtrn == -106:
			raise RuntimeError("Invalid request")
			return
		rtrn = bool(rtrn)
		if rtrn:
			return rtrn
		else:
			nScopeAPI.nScope_release_request(self.handle,byref(self.request))
			self.request = None
			return rtrn

	def readCh1(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(1,0,0,0)
		self.setSampleRateInHz(samplerate)
		self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
		if not self.request:
			print 'Invalid Request'
			return
		data = []
		while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
			data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),1))
		nScopeAPI.nScope_release_request(self.handle,byref(self.request))
		self.request = None
		return data
	def readCh2(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(0,1,0,0)
		self.setSampleRateInHz(samplerate)
		self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
		if not self.request:
			print 'Invalid Request'
			return
		data = []
		while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
			data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),2))
		nScopeAPI.nScope_release_request(self.handle,byref(self.request))
		self.request = None
		return data
	def readCh3(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(0,0,1,0)
		self.setSampleRateInHz(samplerate)
		self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
		if not self.request:
			print 'Invalid Request'
			return
		data = []
		while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
			data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),3))
		nScopeAPI.nScope_release_request(self.handle,byref(self.request))
		self.request = None
		return data
	def readCh4(self,numsamples,samplerate):
		numsamples = int(numsamples)
		self.setChannelsOn(0,0,0,1)
		self.setSampleRateInHz(samplerate)
		self.request = nScopeAPI.nScope_request_data(self.handle,numsamples,0)
		if not self.request:
			print 'Invalid Request'
			return
		data = []
		while(nScopeAPI.nScope_request_has_data(self.handle,self.request)):
			data.append(nScopeAPI.nScope_read_data(self.handle,byref(self.request),4))
		nScopeAPI.nScope_release_request(self.handle,byref(self.request))
		self.request = None
		return data

	'''
	*******************
	Analog Inputs
	*******************
	'''
	def setChannelsOn(self,ch1on,ch2on,ch3on,ch4on):
		rtrn = nScopeAPI.nScope_set_channels_on(self.handle,ch1on,ch2on,ch3on,ch4on)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
	def getChannelsOn(self):
		rtrnlist = (c_int*4)()
		rtrn = nScopeAPI.nScope_get_channels_on(self.handle,cast(rtrnlist, POINTER(c_int)))
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return list(rtrnlist)
	def getNumChannelsOn(self):
		rtrn = nScopeAPI.nScope_get_num_channels_on(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setChannelOn(self,ch,chOn):
		chOn = int(bool(chOn))
		rtrn = nScopeAPI.nScope_set_ch_on(self.handle,ch,chOn)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		if rtrn == -112:
			raise ValueError("nScope channel does not exist")
			return
		return bool(rtrn)
	def getChannelOn(self,ch):
		rtrn = nScopeAPI.nScope_get_ch_on(self.handle,ch)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		if rtrn == -112:
			raise ValueError("nScope channel does not exist")
			return
		return bool(rtrn)
	def setCh1on(self, chOn):
		chOn = bool(int(chOn))
		return self.setChannelOn(1,chOn)
	def getCh1on(self):
		return self.getChannelOn(1)
	def setCh2on(self, chOn):
		chOn = bool(int(chOn))
		return self.setChannelOn(2,chOn)
	def getCh2on(self):
		return self.getChannelOn(2)
	def setCh3on(self, chOn):
		chOn = bool(int(chOn))
		return self.setChannelOn(3,chOn)
	def getCh3on(self):
		return self.getChannelOn(3)
	def setCh4on(self, chOn):
		chOn = bool(int(chOn))
		return self.setChannelOn(4,chOn)
	def getCh4on(self):
		return self.getChannelOn(4)
	def setChannelGains(self,ch1gain,ch2gain,ch3gain,ch4gain):
		rtrn = nScopeAPI.nScope_set_channel_gains(self.handle,ch1gain,ch2gain,ch3gain,ch4gain)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		if rtrn == -110:
			raise ValueError("requested gain is too low")
			return
		if rtrn == -111:
			raise ValueError("requested gain is too high")
			return
		return
	def getChannelGains(self):
		rtrnlist = (c_double*4)()
		rtrn = nScopeAPI.nScope_get_channel_gains(self.handle,cast(rtrnlist, POINTER(c_double)))
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return list(rtrnlist)
	def setChannelGain(self,ch,chGain):
		rtrn = nScopeAPI.nScope_set_ch_gain(self.handle,ch,chGain)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		if rtrn == -110:
			raise ValueError("requested gain is too low")
			return
		if rtrn == -111:
			raise ValueError("requested gain is too high")
			return
		if rtrn == -112:
			raise ValueError("nScope channel does not exist")
			return
		return rtrn
	def getChannelGain(self,ch):
		rtrn = nScopeAPI.nScope_get_ch_gain(self.handle,ch)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		if rtrn == -112:
			raise ValueError("nScope channel does not exist")
			return
		return rtrn
	def setCh1gain(self,chGain):
		return self.setChannelGain(1,chGain)
	def getCh1gain(self):
		return self.getChannelGain(1)
	def setCh2gain(self,chGain):
		return self.setChannelGain(2,chGain)
	def getCh2gain(self):
		return self.getChannelGain(2)
	def setCh3gain(self,chGain):
		return self.setChannelGain(3,chGain)
	def getCh3gain(self):
		return self.getChannelGain(3)
	def setCh4gain(self,chGain):
		return self.setChannelGain(4,chGain)
	def getCh4gain(self):
		return self.getChannelGain(4)

	def setChannelLevels(self,ch1level,ch2level,ch3level,ch4level):
		rtrn = nScopeAPI.nScope_set_channel_levels(self.handle,ch1level,ch2level,ch3level,ch4level)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
	def getChannelLevels(self):
		rtrnlist = (c_double*4)()
		rtrn = nScopeAPI.nScope_get_channel_levels(self.handle,cast(rtrnlist, POINTER(c_double)))
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return list(rtrnlist)
	def setChannelLevel(self,ch,chLevel):
		rtrn = nScopeAPI.nScope_set_ch_level(self.handle,ch,chLevel)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		if rtrn == -112:
			raise ValueError("nScope channel does not exist")
			return
		return rtrn
	def getChannelLevel(self,ch):
		rtrn = nScopeAPI.nScope_get_ch_level(self.handle,ch)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		if rtrn == -112:
			raise ValueError("nScope channel does not exist")
			return
		return rtrn
	def setCh1level(self,chLevel):
		return self.setChannelLevel(1,chLevel)
	def getCh1level(self):
		return self.getChannelLevel(1)
	def setCh2level(self,chLevel):
		return self.setChannelLevel(2,chLevel)
	def getCh2level(self):
		return self.getChannelLevel(2)
	def setCh3level(self,chLevel):
		return self.setChannelLevel(3,chLevel)
	def getCh3level(self):
		return self.getChannelLevel(3)
	def setCh4level(self,chLevel):
		return self.setChannelLevel(4,chLevel)
	def getCh4level(self):
		return self.getChannelLevel(4)


	'''
	*******************
	Sample Timing
	*******************
	'''
	def setSampleRateInHz(self,samplerate):
		rtrn = nScopeAPI.nScope_set_sample_rate_in_hz(self.handle,samplerate)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -111:
			raise ValueError("Requested sample rate is too fast")
			return
		if rtrn == -110:
			raise ValueError("Requested sample rate is too slow")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getSampleRateInHz(self):
		rtrn = nScopeAPI.nScope_get_sample_rate_in_hz(self.handle)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setTimeBetweenSamplesInSeconds(self,sampletime):
		rtrn = nScopeAPI.nScope_set_time_between_samples_in_seconds(self.handle,sampletime)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -111:
			raise ValueError("Requested sample rate is too slow")
			return
		if rtrn == -110:
			raise ValueError("Requested sample rate is too fast")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getTimeBetweenSamplesInSeconds(self):
		rtrn = nScopeAPI.nScope_get_time_between_samples_in_seconds(self.handle)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setTimeBetweenSamplesInMinutes(self,sampletime):
		rtrn = nScopeAPI.nScope_set_time_between_samples_in_minutes(self.handle,sampletime)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -111:
			raise ValueError("Requested sample rate is too slow")
			return
		if rtrn == -110:
			raise ValueError("Requested sample rate is too fast")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getTimeBetweenSamplesInMinutes(self):
		rtrn = nScopeAPI.nScope_get_time_between_samples_in_minutes(self.handle)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setTimeBetweenSamplesInMs(self,sampletime):
		rtrn = nScopeAPI.nScope_set_time_between_samples_in_ms(self.handle,sampletime)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -111:
			raise ValueError("Requested sample rate is too slow")
			return
		if rtrn == -110:
			raise ValueError("Requested sample rate is too fast")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getTimeBetweenSamplesInMs(self):
		rtrn = nScopeAPI.nScope_get_time_between_samples_in_ms(self.handle)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setTimeBetweenSamplesInUs(self,sampletime):
		rtrn = nScopeAPI.nScope_set_time_between_samples_in_us(self.handle,sampletime)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -111:
			raise ValueError("Requested sample rate is too slow")
			return
		if rtrn == -110:
			raise ValueError("Requested sample rate is too fast")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getTimeBetweenSamplesInUs(self):
		rtrn = nScopeAPI.nScope_get_time_between_samples_in_us(self.handle)
		if rtrn == -102:
			raise RuntimeError("No scope channels are on")
			return
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn

	'''
	*******************
	Pulse Generators
	*******************
	'''
	def setP1frequencyInHz(self,frequency):
		rtrn = nScopeAPI.nScope_set_P1_frequency_in_hz(self.handle,frequency)
		if rtrn == -111:
			raise ValueError("Requested frequency is too fast")
			return
		if rtrn == -110:
			raise ValueError("Requested frequency is too slow")
			return
		return rtrn
	def getP1frequencyInHz(self):
		rtrn = nScopeAPI.nScope_get_P1_frequency_in_hz(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setP2frequencyInHz(self,frequency):
		rtrn = nScopeAPI.nScope_set_P2_frequency_in_hz(self.handle,frequency)
		if rtrn == -111:
			raise ValueError("Requested frequency is too fast")
			return
		if rtrn == -110:
			raise ValueError("Requested frequency is too slow")
			return
		return rtrn
	def getP2frequencyInHz(self):
		rtrn = nScopeAPI.nScope_get_P2_frequency_in_hz(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setPulseFrequenciesInHz(self,P1freq,P2freq):
		rtrn = nScopeAPI.nScope_set_pulse_frequencies_in_hz(self.handle,P1freq,P2freq)
		if rtrn == -111:
			raise ValueError("Requested frequency is too fast")
			return
		if rtrn == -110:
			raise ValueError("Requested frequency is too slow")
			return
		return rtrn
	def getPulseFrequenciesInHz(self,P1freq,P2freq):
		rtrnlist = (c_double*4)()
		rtrn = nScopeAPI.nScope_get_pulse_frequencies_in_hz(self.handle,cast(rtrnlist, POINTER(c_double)))
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return list(rtrnlist)
	def setP1periodInMs(self,period):
		rtrn = nScopeAPI.nScope_set_P1_period_in_ms(self.handle,period)
		if rtrn == -110:
			raise ValueError("Requested period is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested period is too long")
			return
		return rtrn
	def getP1periodInMs(self):
		rtrn = nScopeAPI.nScope_get_P1_period_in_ms(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setP2periodInMs(self,period):
		rtrn = nScopeAPI.nScope_set_P2_period_in_ms(self.handle,period)
		if rtrn == -110:
			raise ValueError("Requested period is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested period is too long")
			return
		return rtrn
	def getP2periodInMs(self):
		rtrn = nScopeAPI.nScope_get_P2_period_in_ms(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setPulsePeriodsInMs(self,period1,period2):
		rtrn = nScopeAPI.nScope_set_pulse_periods_in_ms(self.handle,period1,period2)
		if rtrn == -110:
			raise ValueError("Requested period is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested period is too long")
			return
		return rtrn

	def setP1periodInUs(self,period):
		rtrn = nScopeAPI.nScope_set_P1_period_in_us(self.handle,period)
		if rtrn == -110:
			raise ValueError("Requested period is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested period is too long")
			return
		return rtrn
	def getP1periodInUs(self):
		rtrn = nScopeAPI.nScope_get_P1_period_in_us(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setP2periodInUs(self,period):
		rtrn = nScopeAPI.nScope_set_P2_period_in_us(self.handle,period)
		if rtrn == -110:
			raise ValueError("Requested period is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested period is too long")
			return
		return rtrn
	def getP2periodInUs(self):
		rtrn = nScopeAPI.nScope_get_P2_period_in_us(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setPulsePeriodsInUs(self,period1,period2):
		rtrn = nScopeAPI.nScope_set_pulse_periods_in_us(self.handle,period1,period2)
		if rtrn == -110:
			raise ValueError("Requested period is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested period is too long")
			return
		return rtrn

	def setP1dutyPercentage(self,duty):
		rtrn = nScopeAPI.nScope_set_P1_duty_percentage(self.handle,duty)
		if rtrn == -121:
			raise Warning("Requested duty results in always high signal")
		if rtrn == -120:
			raise Warning("Requested duty results in always low signal")
		return rtrn
	def getP1dutyPercentage(self):
		rtrn = nScopeAPI.nScope_get_P1_duty_percentage(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setP2dutyPercentage(self,duty):
		rtrn = nScopeAPI.nScope_set_P2_duty_percentage(self.handle,duty)
		if rtrn == -121:
			raise Warning("Requested duty results in always high signal")
		if rtrn == -120:
			raise Warning("Requested duty results in always low signal")
		return rtrn
	def getP2dutyPercentage(self):
		rtrn = nScopeAPI.nScope_get_P2_duty_percentage(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setPulseDutyPercentages(self,duty1,duty2):
		rtrn = nScopeAPI.nScope_set_pulse_duty_percentages(self.handle,duty1,duty2)
		if rtrn == -121:
			raise Warning("Requested duty results in always high signal")
		if rtrn == -120:
			raise Warning("Requested duty results in always low signal")
		return rtrn

	def setP1pulseWidthInMs(self,pulseWidth):
		rtrn = nScopeAPI.nScope_set_P1_pulse_width_in_ms(self.handle,pulseWidth)
		if rtrn == -121:
			raise Warning("Requested duty results in always high signal")
		if rtrn == -120:
			raise Warning("Requested duty results in always low signal")
		return rtrn
	def getP1pulseWidthInMs(self):
		rtrn = nScopeAPI.nScope_get_P1_pulse_width_in_ms(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setP2pulseWidthInMs(self,pulseWidth):
		rtrn = nScopeAPI.nScope_set_P2_pulse_width_in_ms(self.handle,pulseWidth)
		if rtrn == -121:
			raise Warning("Requested pulse width results in always high signal")
		if rtrn == -120:
			raise Warning("Requested pulse width results in always low signal")
		return rtrn
	def getP2pulseWidthInMs(self):
		rtrn = nScopeAPI.nScope_get_P2_pulse_width_in_ms(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setPulseWidthsInMs(self,pulseWidth1,pulseWidth2):
		rtrn = nScopeAPI.nScope_set_pulse_widths_in_ms(self.handle,pulseWidth1,pulseWidth2)
		if rtrn == -121:
			raise Warning("Requested pulse width results in always high signal")
		if rtrn == -120:
			raise Warning("Requested pulse width results in always low signal")
		return rtrn

	def setP1pulseWidthInUs(self,pulseWidth):
		rtrn = nScopeAPI.nScope_set_P1_pulse_width_in_us(self.handle,pulseWidth)
		if rtrn == -121:
			raise Warning("Requested pulse width results in always high signal")
		if rtrn == -120:
			raise Warning("Requested pulse width results in always low signal")
		return rtrn
	def getP1pulseWidthInUs(self):
		rtrn = nScopeAPI.nScope_get_P1_pulse_width_in_us(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setP2pulseWidthInUs(self,pulseWidth):
		rtrn = nScopeAPI.nScope_set_P2_pulse_width_in_us(self.handle,pulseWidth)
		if rtrn == -121:
			raise Warning("Requested pulse width results in always high signal")
		if rtrn == -120:
			raise Warning("Requested pulse width results in always low signal")
		return rtrn
	def getP2pulseWidthInUs(self):
		rtrn = nScopeAPI.nScope_get_P2_pulse_width_in_us(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setPulseWidthsInUs(self,pulseWidth1,pulseWidth2):
		rtrn = nScopeAPI.nScope_set_pulse_widths_in_us(self.handle,pulseWidth1,pulseWidth2)
		if rtrn == -121:
			raise Warning("Requested pulse width results in always high signal")
		if rtrn == -120:
			raise Warning("Requested pulse width results in always low signal")
		return rtrn

	def setP1on(self,P1on):
		P1on = int(bool(P1on))
		rtrn = nScopeAPI.nScope_set_P1_on(self.handle,P1on)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def getP1on(self):
		rtrn = nScopeAPI.nScope_get_P1_on(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def setP2on(self,P2on):
		P2on = int(bool(P2on))
		rtrn = nScopeAPI.nScope_set_P2_on(self.handle,P2on)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def getP2on(self):
		rtrn = nScopeAPI.nScope_get_P2_on(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def setPulseGeneratorsOn(self,P1on,P2on):
		P1on = int(bool(P1on))
		P2on = int(bool(P2on))
		rtrn = nScopeAPI.nScope_set_pulse_generators_on(self.handle,P1on,P2on)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getPulseGeneratorsOn(self):
		rtrnlist = (c_int * 2)()
		rtrn = nScopeAPI.nScope_get_pulse_generators_on(self.handle,cast(rtrnlist,POINTER(c_int)))
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return list(rtrnlist)

	def sendP1pulse(self,pulseWidth):
		rtrn = nScopeAPI.nScope_send_P1_pulse(self.handle,pulseWidth)
		if rtrn == -110:
			raise ValueError("Requested pulse is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested pulse is too long")
			return
		return rtrn
	def sendP2pulse(self,pulseWidth):
		rtrn = nScopeAPI.nScope_send_P2_pulse(self.handle,pulseWidth)
		if rtrn == -110:
			raise ValueError("Requested pulse is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested pulse is too long")
			return
		return rtrn
	def sendPulses(self,pulseWidth0,pulseWidth1):
		rtrn = nScopeAPI.nScope_send_pulses(self.handle,pulseWidth0,pulseWidth1)
		if rtrn == -110:
			raise ValueError("Requested pulse is too short")
			return
		if rtrn == -111:
			raise ValueError("Requested pulse is too long")
			return
		return rtrn

	'''
	*******************
	Analog Outputs
	*******************
	'''
	def setA1frequencyInHz(self,frequency):
		rtrn = nScopeAPI.nScope_set_A1_frequency_in_hz(self.handle,frequency)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getA1frequencyInHz(self):
		rtrn = nScopeAPI.nScope_get_A1_frequency_in_hz(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setA2frequencyInHz(self,frequency):
		rtrn = nScopeAPI.nScope_set_A2_frequency_in_hz(self.handle,frequency)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getA2frequencyInHz(self):
		rtrn = nScopeAPI.nScope_get_A2_frequency_in_hz(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setA1waveType(self,wave):
		wave = str(wave)
		if wave.lower() == 'sine' or wave.lower() == 'sin':
			rtrn = nScopeAPI.nScope_set_A1_wave_type(self.handle,0)
		elif wave.lower() == 'triangle' or wave.lower() == 'tri':
			rtrn = nScopeAPI.nScope_set_A1_wave_type(self.handle,1)
		else:
			raise ValueError("Unknown wave type: "+wave)
			return
		if rtrn is 0:
			return 'Sine'
		elif rtrn is 1:
			return 'Triangle'
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return
	def getA2waveType(self):
		rtrn = nScopeAPI.nScope_get_A2_wave_type(self.handle)
		if rtrn is 0:
			return 'Sine'
		elif rtrn is 1:
			return 'Triangle'
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return
	def setA2waveType(self,wave):
		wave = str(wave)
		if wave.lower() == 'sine' or wave.lower() == 'sin':
			rtrn = nScopeAPI.nScope_set_A2_wave_type(self.handle,0)
		elif wave.lower() == 'triangle' or wave.lower() == 'tri':
			rtrn = nScopeAPI.nScope_set_A2_wave_type(self.handle,1)
		else:
			raise ValueError("Unknown wave type: "+wave)
			return
		if rtrn is 0:
			return 'Sine'
		elif rtrn is 1:
			return 'Triangle'
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return
	def getA1waveType(self):
		rtrn = nScopeAPI.nScope_get_A1_wave_type(self.handle)
		if rtrn is 0:
			return 'Sine'
		elif rtrn is 1:
			return 'Triangle'
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return
	def setA1on(self,aoOn):
		aoOn = int(bool(aoOn))
		rtrn = nScopeAPI.nScope_set_A1_on(self.handle,aoOn)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def getA1on(self):
		rtrn = nScopeAPI.nScope_get_A1_on(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def setA2on(self,aoOn):
		aoOn = int(bool(aoOn))
		rtrn = nScopeAPI.nScope_set_A2_on(self.handle,aoOn)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def getA2on(self):
		rtrn = nScopeAPI.nScope_get_A2_on(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def setA1unipolar(self,unipolar):
		unipolar = int(bool(unipolar))
		rtrn = nScopeAPI.nScope_set_A1_unipolar(self.handle,unipolar)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def getA1unipolar(self):
		rtrn = nScopeAPI.nScope_get_A1_unipolar(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def setA2unipolar(self,unipolar):
		unipolar = int(bool(unipolar))
		rtrn = nScopeAPI.nScope_set_A2_unipolar(self.handle,unipolar)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def getA2unipolar(self):
		rtrn = nScopeAPI.nScope_get_A2_unipolar(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return bool(rtrn)
	def setA1amplitude(self,amplitude):
		rtrn = nScopeAPI.nScope_set_A1_amplitude(self.handle,amplitude)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getA1amplitude(self):
		rtrn = nScopeAPI.nScope_get_A1_amplitude(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def setA2amplitude(self,amplitude):
		rtrn = nScopeAPI.nScope_set_A2_amplitude(self.handle,amplitude)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn
	def getA2amplitude(self):
		rtrn = nScopeAPI.nScope_get_A2_amplitude(self.handle)
		if rtrn == -101:
			raise RuntimeError("nScope is not connected")
			return
		return rtrn

def defineTypes():
	nScopeAPI.nScope_open.restype = POINTER(scopeHandle)
	nScopeAPI.nScope_close.argtypes = [POINTER(POINTER(scopeHandle))]

	nScopeAPI.nScope_request_data.restype = POINTER(request)
	nScopeAPI.nScope_request_data.argtypes = [POINTER(scopeHandle),c_int,c_int]
	# nScopeAPI.nScope_request_data_stream.restypes
	# nScopeAPI.nScope_request_data_stream.argtypes
	nScopeAPI.nScope_release_request.argtpyes = [POINTER(scopeHandle),POINTER(POINTER(request))]

	nScopeAPI.nScope_wait_for_request_finish.argtypes = [POINTER(scopeHandle),POINTER(request)]
	nScopeAPI.nScope_request_xfer_has_completed.restype = c_int
	nScopeAPI.nScope_request_xfer_has_completed.argtypes = [POINTER(scopeHandle),POINTER(request)]
	# nScopeAPI.nScope_request_xfer_samples_remaining.restype = c_int
	# nScopeAPI.nScope_request_xfer_samples_remaining.argtypes = [POINTER(request)]
	# nScopeAPI.nScope_request_stop_data_stream.restype = c_int
	# nScopeAPI.nScope_request_stop_data_stream.argtypes = [POINTER(request)]

	nScopeAPI.nScope_read_data.restype = c_double
	nScopeAPI.nScope_read_data.argtypes = [POINTER(scopeHandle),POINTER(POINTER(request)),c_int]
	nScopeAPI.nScope_request_has_data.restype = c_int
	nScopeAPI.nScope_request_has_data.argtypes = [POINTER(scopeHandle),POINTER(POINTER(request))]


	'''
	Analog Inputs
	'''
	nScopeAPI.nScope_set_channels_on.argtypes = [POINTER(scopeHandle),c_int,c_int,c_int,c_int]
	nScopeAPI.nScope_get_channels_on.argtypes = [POINTER(scopeHandle),POINTER(c_int)]
	nScopeAPI.nScope_get_num_channels_on.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_ch_on.argtypes = [POINTER(scopeHandle), c_int, c_int]
	nScopeAPI.nScope_get_ch_on.argtypes = [POINTER(scopeHandle), c_int]

	nScopeAPI.nScope_set_ch_gain.restype = c_double
	nScopeAPI.nScope_set_ch_gain.argtypes = [POINTER(scopeHandle), c_int, c_double]
	nScopeAPI.nScope_get_ch_gain.restype = c_double
	nScopeAPI.nScope_get_ch_gain.argtypes = [POINTER(scopeHandle), c_int]
	nScopeAPI.nScope_set_channel_gains.argtypes = [POINTER(scopeHandle),c_double,c_double,c_double,c_double]
	nScopeAPI.nScope_get_channel_gains.argtypes = [POINTER(scopeHandle),POINTER(c_double)]

	nScopeAPI.nScope_set_ch_level.restype = c_double
	nScopeAPI.nScope_set_ch_level.argtypes = [POINTER(scopeHandle), c_int, c_double]
	nScopeAPI.nScope_get_ch_level.restype = c_double
	nScopeAPI.nScope_get_ch_level.argtypes = [POINTER(scopeHandle), c_int]
	nScopeAPI.nScope_set_channel_levels.argtypes = [POINTER(scopeHandle),c_double,c_double,c_double,c_double]
	nScopeAPI.nScope_get_channel_levels.argtypes = [POINTER(scopeHandle),POINTER(c_double)]

	'''
	Sample Timing
	'''
	nScopeAPI.nScope_set_sample_rate_in_hz.restype = c_double
	nScopeAPI.nScope_set_sample_rate_in_hz.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_sample_rate_in_hz.restype = c_double
	nScopeAPI.nScope_get_sample_rate_in_hz.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_time_between_samples_in_seconds.restype = c_double
	nScopeAPI.nScope_set_time_between_samples_in_seconds.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_time_between_samples_in_seconds.restype = c_double
	nScopeAPI.nScope_get_time_between_samples_in_seconds.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_time_between_samples_in_minutes.restype = c_double
	nScopeAPI.nScope_set_time_between_samples_in_minutes.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_time_between_samples_in_minutes.restype = c_double
	nScopeAPI.nScope_get_time_between_samples_in_minutes.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_time_between_samples_in_ms.restype = c_double
	nScopeAPI.nScope_set_time_between_samples_in_ms.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_time_between_samples_in_ms.restype = c_double
	nScopeAPI.nScope_get_time_between_samples_in_ms.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_time_between_samples_in_us.restype = c_double
	nScopeAPI.nScope_set_time_between_samples_in_us.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_time_between_samples_in_us.restype = c_double
	nScopeAPI.nScope_get_time_between_samples_in_us.argtypes = [POINTER(scopeHandle)]


	'''
	Trigger
	'''
	# nScopeAPI.nScope_set_trigger_on.argtypes = [POINTER(scopeHandle), c_int]
	# nScopeAPI.nScope_get_trigger_on.argtypes = [POINTER(scopeHandle)]

	# nScopeAPI.nScope_set_trigger_source.argtypes = [POINTER(scopeHandle), c_int]
	# nScopeAPI.nScope_get_trigger_source.argtypes = [POINTER(scopeHandle)]

	# nScopeAPI.nScope_set_trigger_edge.argtypes = [POINTER(scopeHandle), c_int]
	# nScopeAPI.nScope_get_trigger_edge.argtypes = [POINTER(scopeHandle)]

	# nScopeAPI.nScope_set_trigger_level.restype = c_double
	# nScopeAPI.nScope_set_trigger_level.argtypes = [POINTER(scopeHandle),c_double]
	# nScopeAPI.nScope_get_trigger_level.restype = c_double
	# nScopeAPI.nScope_get_trigger_level.argtypes = [POINTER(scopeHandle)]


	'''
	Pulse Generators
	'''
	nScopeAPI.nScope_set_P1_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_set_P1_frequency_in_hz.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P1_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_get_P1_frequency_in_hz.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_P2_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_set_P2_frequency_in_hz.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P2_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_get_P2_frequency_in_hz.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_pulse_frequencies_in_hz.restype = c_double
	nScopeAPI.nScope_set_pulse_frequencies_in_hz.argtypes = [POINTER(scopeHandle),c_double,c_double]
	nScopeAPI.nScope_get_pulse_frequencies_in_hz.argtypes = [POINTER(scopeHandle),POINTER(c_double)]

	nScopeAPI.nScope_set_P1_period_in_ms.restype = c_double
	nScopeAPI.nScope_set_P1_period_in_ms.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P1_period_in_ms.restype = c_double
	nScopeAPI.nScope_get_P1_period_in_ms.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_P2_period_in_ms.restype = c_double
	nScopeAPI.nScope_set_P2_period_in_ms.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P2_period_in_ms.restype = c_double
	nScopeAPI.nScope_get_P2_period_in_ms.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_pulse_periods_in_ms.restype = c_double
	nScopeAPI.nScope_set_pulse_periods_in_ms.argtypes = [POINTER(scopeHandle),c_double,c_double]
	nScopeAPI.nScope_get_pulse_periods_in_ms.argtypes = [POINTER(scopeHandle),POINTER(c_double)]

	nScopeAPI.nScope_set_P1_period_in_us.restype = c_double
	nScopeAPI.nScope_set_P1_period_in_us.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P1_period_in_us.restype = c_double
	nScopeAPI.nScope_get_P1_period_in_us.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_P2_period_in_us.restype = c_double
	nScopeAPI.nScope_set_P2_period_in_us.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P2_period_in_us.restype = c_double
	nScopeAPI.nScope_get_P2_period_in_us.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_pulse_periods_in_us.restype = c_double
	nScopeAPI.nScope_set_pulse_periods_in_us.argtypes = [POINTER(scopeHandle),c_double,c_double]
	nScopeAPI.nScope_get_pulse_periods_in_us.argtypes = [POINTER(scopeHandle),POINTER(c_double)]

	nScopeAPI.nScope_set_P1_duty_percentage.restype = c_double
	nScopeAPI.nScope_set_P1_duty_percentage.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P1_duty_percentage.restype = c_double
	nScopeAPI.nScope_get_P1_duty_percentage.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_P2_duty_percentage.restype = c_double
	nScopeAPI.nScope_set_P2_duty_percentage.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P2_duty_percentage.restype = c_double
	nScopeAPI.nScope_get_P2_duty_percentage.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_pulse_duty_percentages.restype = c_double
	nScopeAPI.nScope_set_pulse_duty_percentages.argtypes = [POINTER(scopeHandle),c_double,c_double]
	nScopeAPI.nScope_get_pulse_duty_percentages.argtypes = [POINTER(scopeHandle),POINTER(c_double)]

	nScopeAPI.nScope_set_P1_pulse_width_in_ms.restype = c_double
	nScopeAPI.nScope_set_P1_pulse_width_in_ms.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P1_pulse_width_in_ms.restype = c_double
	nScopeAPI.nScope_get_P1_pulse_width_in_ms.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_P2_pulse_width_in_ms.restype = c_double
	nScopeAPI.nScope_set_P2_pulse_width_in_ms.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P2_pulse_width_in_ms.restype = c_double
	nScopeAPI.nScope_get_P2_pulse_width_in_ms.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_pulse_widths_in_ms.restype = c_double
	nScopeAPI.nScope_set_pulse_widths_in_ms.argtypes = [POINTER(scopeHandle),c_double,c_double]
	nScopeAPI.nScope_get_pulse_widths_in_ms.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_P1_pulse_width_in_us.restype = c_double
	nScopeAPI.nScope_set_P1_pulse_width_in_us.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P1_pulse_width_in_us.restype = c_double
	nScopeAPI.nScope_get_P1_pulse_width_in_us.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_P2_pulse_width_in_us.restype = c_double
	nScopeAPI.nScope_set_P2_pulse_width_in_us.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_P2_pulse_width_in_us.restype = c_double
	nScopeAPI.nScope_get_P2_pulse_width_in_us.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_pulse_widths_in_us.restype = c_double
	nScopeAPI.nScope_set_pulse_widths_in_us.argtypes = [POINTER(scopeHandle),c_double,c_double]
	nScopeAPI.nScope_get_pulse_widths_in_us.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_P1_on.restype = c_int
	nScopeAPI.nScope_set_P1_on.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_P1_on.restype = c_int
	nScopeAPI.nScope_get_P1_on.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_P2_on.restype = c_int
	nScopeAPI.nScope_set_P2_on.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_P2_on.restype = c_int
	nScopeAPI.nScope_get_P2_on.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_pulse_generators_on.restype = c_int
	nScopeAPI.nScope_set_pulse_generators_on.argtypes = [POINTER(scopeHandle),c_int,c_int]
	nScopeAPI.nScope_get_pulse_generators_on.argtypes = [POINTER(scopeHandle),POINTER(c_int)]

	nScopeAPI.nScope_send_P1_pulse.restype = c_double
	nScopeAPI.nScope_send_P1_pulse.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_send_P2_pulse.restype = c_double
	nScopeAPI.nScope_send_P2_pulse.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_send_pulses.restype = c_double
	nScopeAPI.nScope_send_pulses.argtypes = [POINTER(scopeHandle),c_double,c_double]


	'''
	Analog Outputs
	'''
	nScopeAPI.nScope_set_A1_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_set_A1_frequency_in_hz.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_A1_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_get_A1_frequency_in_hz.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_A2_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_set_A2_frequency_in_hz.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_A2_frequency_in_hz.restype = c_double
	nScopeAPI.nScope_get_A2_frequency_in_hz.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_A1_wave_type.restype = c_int
	nScopeAPI.nScope_set_A1_wave_type.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_A1_wave_type.restype = c_int
	nScopeAPI.nScope_get_A1_wave_type.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_A2_wave_type.restype = c_int
	nScopeAPI.nScope_set_A2_wave_type.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_A2_wave_type.restype = c_int
	nScopeAPI.nScope_get_A2_wave_type.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_A1_on.restype = c_int
	nScopeAPI.nScope_set_A1_on.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_A1_on.restype = c_int
	nScopeAPI.nScope_get_A1_on.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_A2_on.restype = c_int
	nScopeAPI.nScope_set_A2_on.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_A2_on.restype = c_int
	nScopeAPI.nScope_get_A2_on.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_A1_unipolar.restype = c_int
	nScopeAPI.nScope_set_A1_unipolar.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_A1_unipolar.restype = c_int
	nScopeAPI.nScope_get_A1_unipolar.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_A2_unipolar.restype = c_int
	nScopeAPI.nScope_set_A2_unipolar.argtypes = [POINTER(scopeHandle),c_int]
	nScopeAPI.nScope_get_A2_unipolar.restype = c_int
	nScopeAPI.nScope_get_A2_unipolar.argtypes = [POINTER(scopeHandle)]

	nScopeAPI.nScope_set_A1_amplitude.restype = c_double
	nScopeAPI.nScope_set_A1_amplitude.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_A1_amplitude.restype = c_double
	nScopeAPI.nScope_get_A1_amplitude.argtypes = [POINTER(scopeHandle)]
	nScopeAPI.nScope_set_A2_amplitude.restype = c_double
	nScopeAPI.nScope_set_A2_amplitude.argtypes = [POINTER(scopeHandle),c_double]
	nScopeAPI.nScope_get_A2_amplitude.restype = c_double
	nScopeAPI.nScope_get_A2_amplitude.argtypes = [POINTER(scopeHandle)]
