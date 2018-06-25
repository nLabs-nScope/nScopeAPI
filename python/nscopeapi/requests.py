from ctypes import POINTER, c_int, c_bool, c_double
from nscopeapi.nScopeDefs import *
'''
Requests
'''

lib.nScope_request_data.restype = c_int
lib.nScope_request_data.argtypes = [POINTER(scopeDev), POINTER(POINTER(requestObj)), c_int, c_bool]

# Not yet implemented
# lib.nScope_request_data_stream.restypes = c_int
# lib.nScope_request_data_stream.argtypes = [POINTER(scopeDev), POINTER(POINTER(requestObj))]

lib.nScope_stop_request.restype = c_int
lib.nScope_stop_request.argtypes = [POINTER(scopeDev), POINTER(requestObj)]

lib.nScope_release_request.restype = c_int
lib.nScope_release_request.argtpyes = [POINTER(scopeDev), POINTER(POINTER(requestObj))]

lib.nScope_wait_for_request_finish.restype = c_int
lib.nScope_wait_for_request_finish.argtypes = [POINTER(scopeDev), POINTER(requestObj)]

lib.nScope_request_xfer_has_completed.restype = c_int
lib.nScope_request_xfer_has_completed.argtypes = [POINTER(scopeDev), POINTER(requestObj), POINTER(c_bool)]

# Not yet implemented
# lib.nScope_request_xfer_samples_remaining.restype = c_int
# lib.nScope_request_xfer_samples_remaining.argtypes = [POINTER(scopeDev), POINTER(requestObj)]

# Not yet implemented
# lib.nScope_request_stop_data_stream.restype = c_int
# lib.nScope_request_stop_data_stream.argtypes = [POINTER(scopeDev), POINTER(requestObj)]

lib.nScope_read_data.restype = c_int
lib.nScope_read_data.argtypes = [POINTER(scopeDev), POINTER(requestObj), c_int, POINTER(c_double)]

lib.nScope_request_has_data.restype = c_int
lib.nScope_request_has_data.argtypes = [POINTER(scopeDev), POINTER(requestObj), POINTER(c_bool)]

	# 	if self.request:
	# 		lib.nScope_release_request(self.handle,byref(self.request))
	# 	self.request = lib.nScope_request_data(self.handle,numsamples,0)
	# 	if not self.request:
	# 		raise ValueError("Invalid request")
	# 		return

	# 	if rtrn == -106:
	# 		raise ValueError("Invalid request")
	# 		return
	# 	if rtrn == -112:
	# 		raise ValueError("nScope channel does not exist")
	# 		return
	# 	if rtrn == -104:
	# 		raise RuntimeWarning("No more data available")
	# 		return
	# 	if rtrn == -102:
	# 		raise RuntimeWarning("nScope channel was not on during request")
	# 		return
	# 	return rtrn


class Implementation:
    def requestData(self,numSamples):
        lib.nScope_request_data(self.handle,byref(self.request),numSamples,False)
        return

    def stopRequest(self):
        lib.nScope_stop_request(self.handle,self.request)
        return

    def releaseRequest(self):
        lib.nScope_release_request(self.handle,byref(self.request))
        return

    def waitForRequestFinish(self):
        lib.nScope_wait_for_request_finish(self.handle,self.request)
        return

    def requestTransferHasCompleted(self):
        hasCompleted = c_bool()
        lib.nScope_request_xfer_has_completed(self.handle,self.request,byref(hasCompleted))
        return hasCompleted.value

    def readData(self,channel):
        channel = int(channel)
        data = c_double()
        lib.nScope_read_data(self.handle,self.request,channel,byref(data))
        return data.value

    def requestHasData(self):
        hasData = c_bool()
        lib.nScope_request_has_data(self.handle,self.request,byref(hasData))
        return hasData.value
