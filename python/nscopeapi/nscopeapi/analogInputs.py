from ctypes import POINTER, byref, c_int, c_bool, c_double
from nscopeapi.nScopeDefs import *

lib.nScope_set_channels_on.restype = c_int
lib.nScope_set_channels_on.argtypes = [POINTER(scopeDev),c_bool,c_bool,c_bool,c_bool]
lib.nScope_get_channels_on.restype = c_int
lib.nScope_get_channels_on.argtypes = [POINTER(scopeDev),POINTER(c_bool*4)]

lib.nScope_get_num_channels_on.restype = c_int
lib.nScope_get_num_channels_on.argtypes = [POINTER(scopeDev),POINTER(c_int)]

lib.nScope_set_ChX_on.restype = c_int
lib.nScope_set_ChX_on.argtypes = [POINTER(scopeDev), c_int, c_bool]
lib.nScope_get_ChX_on.restype = c_int
lib.nScope_get_ChX_on.argtypes = [POINTER(scopeDev), c_int, POINTER(c_bool)]

lib.nScope_set_channel_gains.restype = c_int
lib.nScope_set_channel_gains.argtypes = [POINTER(scopeDev),c_double,c_double,c_double,c_double]
lib.nScope_get_channel_gains.restype = c_int
lib.nScope_get_channel_gains.argtypes = [POINTER(scopeDev),POINTER(c_double*4)]

lib.nScope_set_ChX_gain.restype = c_int
lib.nScope_set_ChX_gain.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_ChX_gain.restype = c_int
lib.nScope_get_ChX_gain.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

lib.nScope_set_channel_levels.restype = c_int
lib.nScope_set_channel_levels.argtypes = [POINTER(scopeDev),c_double,c_double,c_double,c_double]
lib.nScope_get_channel_levels.restype = c_int
lib.nScope_get_channel_levels.argtypes = [POINTER(scopeDev),POINTER(c_double*4)]

lib.nScope_set_ChX_level.restype = c_int
lib.nScope_set_ChX_level.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_ChX_level.restype = c_int
lib.nScope_get_ChX_level.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

# if rtrn == -101:
# 	raise RuntimeError("nScope is not connected")
# 	return

# 	if rtrn == -112:
# 		raise ValueError("nScope channel does not exist")
# 		return

# 	if rtrn == -110:
# 		raise ValueError("requested gain is too low")
# 		return
# 	if rtrn == -111:
# 		raise ValueError("requested gain is too high")
# 		return

class Implementation:
    def setChannelsOn(self,ch1on,ch2on,ch3on,ch4on):
        lib.nScope_set_channels_on(self.handle,ch1on,ch2on,ch3on,ch4on)
        return

    def getChannelsOn(self):
        channelsOn = (c_bool*4)()
        lib.nScope_get_channels_on(self.handle,byref(channelsOn))
        return list(channelsOn)

    def getNumChannelsOn(self):
        numChannelsOn = c_int()
        lib.nScope_get_num_channels_on(self.handle,byref(numChannelsOn))
        return numChannelsOn.value

    def setChannelOn(self,ch,chOn):
        chOn = bool(chOn)
        lib.nScope_set_ChX_on(self.handle,ch,chOn)
        return

    def getChannelOn(self,ch):
        chOn = c_bool()
        lib.nScope_get_ChX_on(self.handle,ch,byref(chOn))
        return chOn.value

    def setChannelGains(self,ch1gain,ch2gain,ch3gain,ch4gain):
        lib.nScope_set_channel_gains(self.handle,ch1gain,ch2gain,ch3gain,ch4gain)
        return

    def getChannelGains(self):
        channelGains = (c_double*4)()
        lib.nScope_get_channel_gains(self.handle,byref(channelGains))
        return list(channelGains)

    def setChannelGain(self,ch,chGain):
        lib.nScope_set_ChX_gain(self.handle,ch,chGain)
        return

    def getChannelGain(self,ch):
        chGain = c_double()
        lib.nScope_get_ChX_gain(self.handle,ch,byref(chGain))
        return chGain.value

    def setChannelLevels(self,ch1level,ch2level,ch3level,ch4level):
        lib.nScope_set_channel_levels(self.handle,ch1level,ch2level,ch3level,ch4level)
        return

    def getChannelLevels(self):
        channelLevels = (c_double*4)()
        lib.nScope_get_channel_levels(self.handle,byref(channelLevels))
        return list(channelLevels)

    def setChannelLevel(self,ch,chLevel):
        lib.nScope_set_ChX_level(self.handle,ch,chLevel)
        return

    def getChannelLevel(self,ch):
        chLevel = c_double()
        lib.nScope_get_ChX_level(self.handle,ch,byref(chLevel))
        return chLevel.value
