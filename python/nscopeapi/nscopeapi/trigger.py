from ctypes import POINTER, c_int, c_bool, c_double
from nScopeDefs import *

'''
Trigger
'''
nScopeAPI.nScope_set_trigger_on.restype = c_int
nScopeAPI.nScope_set_trigger_on.argtypes = [POINTER(scopeDev), c_bool]
nScopeAPI.nScope_get_trigger_on.restype = c_int
nScopeAPI.nScope_get_trigger_on.argtypes = [POINTER(scopeDev), POINTER(c_bool)]

nScopeAPI.nScope_set_trigger_source.restype = c_int
nScopeAPI.nScope_set_trigger_source.argtypes = [POINTER(scopeDev), c_int]
nScopeAPI.nScope_get_trigger_source.restype = c_int
nScopeAPI.nScope_get_trigger_source.argtypes = [POINTER(scopeDev), POINTER(c_int)]

nScopeAPI.nScope_set_trigger_edge.restype = c_int
nScopeAPI.nScope_set_trigger_edge.argtypes = [POINTER(scopeDev), c_int]
nScopeAPI.nScope_get_trigger_edge.restype = c_int
nScopeAPI.nScope_get_trigger_edge.argtypes = [POINTER(scopeDev), POINTER(c_int)]

nScopeAPI.nScope_set_trigger_level.restype = c_int
nScopeAPI.nScope_set_trigger_level.argtypes = [POINTER(scopeDev), c_double]
nScopeAPI.nScope_get_trigger_level.restype = c_int
nScopeAPI.nScope_get_trigger_level.argtypes = [POINTER(scopeDev), POINTER(c_double)]

# Not yet implemented
# nScopeAPI.nScope_set_trigger_delay_ms.restype = c_int
# nScopeAPI.nScope_set_trigger_delay_ms.argtypes = [POINTER(scopeDev), c_double]
# nScopeAPI.nScope_get_trigger_delay_ms.restype = c_int
# nScopeAPI.nScope_get_trigger_delay_ms.argtypes = [POINTER(scopeDev), POINTER(c_double)]
#
# nScopeAPI.nScope_set_trigger_delay_us.restype = c_int
# nScopeAPI.nScope_set_trigger_delay_us.argtypes = [POINTER(scopeDev), c_double]
# nScopeAPI.nScope_get_trigger_delay_us.restype = c_int
# nScopeAPI.nScope_get_trigger_delay_us.argtypes = [POINTER(scopeDev), POINTER(c_double)]

class Implementation:
    def setTriggerOn(self,triggerOn):
        chOn = bool(chOn)
        nScopeAPI.nScope_set_trigger_on(self.handle,triggerOn)
        return

    def getTriggerOn(self):
        triggerOn = c_bool()
        nScopeAPI.nScope_get_trigger_on(self.handle,byref(triggerOn))
        return chOn.value

    def setTriggerSource(self,triggerSource):
        triggerSource = int(triggerSource)
        nScopeAPI.nScope_set_trigger_source(self.handle,triggerSource)
        return

    def getTriggerSource(self):
        triggerSource = c_int()
        nScopeAPI.nScope_get_trigger_source(self.handle,byref(triggerSource))
        return triggerSource.value

    def setTriggerEdge(self,triggerEdge):
        triggerEdge = int(triggerEdge)
        nScopeAPI.nScope_set_trigger_edge(self.handle,triggerEdge)
        return

    def getTriggerEdge(self):
        triggerEdge = c_int()
        nScopeAPI.nScope_get_trigger_edge(self.handle,byref(triggerEdge))
        return triggerEdge.value

    def setTriggerLevel(self,triggerLevel):
        nScopeAPI.nScope_set_trigger_level(self.handle,triggerLevel)
        return

    def getTriggerLevel(self):
        triggerLevel = c_double()
        nScopeAPI.nScope_get_trigger_level(self.handle,byref(triggerLevel))
        return triggerLevel.value

    # def setTimeBetweenSamplesInMs(self,sampleTime):
    #     nScopeAPI.nScope_set_time_between_samples_in_ms(self.handle,sampleTime)
    #     return
    #
    # def getTimeBetweenSamplesInMs(self):
    #     sampleTime = c_double()
    #     nScopeAPI.nScope_get_time_between_samples_in_ms(self.handle,byref(sampleTime))
    #     return sampleTime.value
    #
    # def setTimeBetweenSamplesInUs(self,sampleTime):
    #     nScopeAPI.nScope_set_time_between_samples_in_us(self.handle,sampleTime)
    #     return
    #
    # def getTimeBetweenSamplesInUs(self):
    #     sampleTime = c_double()
    #     nScopeAPI.nScope_get_time_between_samples_in_us(self.handle,byref(sampleTime))
    #     return sampleTime.value
