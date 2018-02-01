from ctypes import POINTER, c_int, c_double
from nscopeapi.nScopeDefs import *

'''
Sample Timing
'''
lib.nScope_set_sample_rate_in_hz.restype = c_int
lib.nScope_set_sample_rate_in_hz.argtypes = [POINTER(scopeDev), c_double]
lib.nScope_get_sample_rate_in_hz.restype = c_int
lib.nScope_get_sample_rate_in_hz.argtypes = [POINTER(scopeDev), POINTER(c_double)]

lib.nScope_set_time_between_samples_in_seconds.restype = c_int
lib.nScope_set_time_between_samples_in_seconds.argtypes = [POINTER(scopeDev), c_double]
lib.nScope_get_time_between_samples_in_seconds.restype = c_int
lib.nScope_get_time_between_samples_in_seconds.argtypes = [POINTER(scopeDev), POINTER(c_double)]

lib.nScope_set_time_between_samples_in_minutes.restype = c_int
lib.nScope_set_time_between_samples_in_minutes.argtypes = [POINTER(scopeDev), c_double]
lib.nScope_get_time_between_samples_in_minutes.restype = c_int
lib.nScope_get_time_between_samples_in_minutes.argtypes = [POINTER(scopeDev), POINTER(c_double)]

lib.nScope_set_time_between_samples_in_ms.restype = c_int
lib.nScope_set_time_between_samples_in_ms.argtypes = [POINTER(scopeDev), c_double]
lib.nScope_get_time_between_samples_in_ms.restype = c_int
lib.nScope_get_time_between_samples_in_ms.argtypes = [POINTER(scopeDev), POINTER(c_double)]

lib.nScope_set_time_between_samples_in_us.restype = c_int
lib.nScope_set_time_between_samples_in_us.argtypes = [POINTER(scopeDev), c_double]
lib.nScope_get_time_between_samples_in_us.restype = c_int
lib.nScope_get_time_between_samples_in_us.argtypes = [POINTER(scopeDev), POINTER(c_double)]

# 	if rtrn == -102:
# 		raise RuntimeError("No scope channels are on")
# 		return
# 	if rtrn == -111:
# 		raise ValueError("Requested sample rate is too fast")
# 		return
# 	if rtrn == -110:
# 		raise ValueError("Requested sample rate is too slow")
# 		return
# 	if rtrn == -101:
# 		raise RuntimeError("nScope is not connected")
# 		return

class Implementation:
    def setSampleRateInHz(self,sampleRate):
        lib.nScope_set_sample_rate_in_hz(self.handle,sampleRate)
        return

    def getSampleRateInHz(self):
        sampleRate = c_double()
        lib.nScope_get_sample_rate_in_hz(self.handle,byref(sampleRate))
        return sampleRate.value

    def setTimeBetweenSamplesInSeconds(self,sampleTime):
        lib.nScope_set_time_between_samples_in_seconds(self.handle,sampleTime)
        return

    def getTimeBetweenSamplesInSeconds(self):
        sampleTime = c_double()
        lib.nScope_get_time_between_samples_in_seconds(self.handle,byref(sampleTime))
        return sampleTime.value

    def setTimeBetweenSamplesInMinutes(self,sampleTime):
        lib.nScope_set_time_between_samples_in_minutes(self.handle,sampleTime)
        return

    def getTimeBetweenSamplesInMinutes(self):
        sampleTime = c_double()
        lib.nScope_get_time_between_samples_in_minutes(self.handle,byref(sampleTime))
        return sampleTime.value

    def setTimeBetweenSamplesInMs(self,sampleTime):
        lib.nScope_set_time_between_samples_in_ms(self.handle,sampleTime)
        return

    def getTimeBetweenSamplesInMs(self):
        sampleTime = c_double()
        lib.nScope_get_time_between_samples_in_ms(self.handle,byref(sampleTime))
        return sampleTime.value

    def setTimeBetweenSamplesInUs(self,sampleTime):
        lib.nScope_set_time_between_samples_in_us(self.handle,sampleTime)
        return

    def getTimeBetweenSamplesInUs(self):
        sampleTime = c_double()
        lib.nScope_get_time_between_samples_in_us(self.handle,byref(sampleTime))
        return sampleTime.value
