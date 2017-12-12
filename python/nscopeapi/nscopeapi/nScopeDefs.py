from ctypes import CDLL, Structure, POINTER, byref, c_double, c_int, c_bool
import platform,os

system = platform.system()

print __file__
print os.path.abspath(os.path.dirname(__file__))
if system == "Darwin":
	nScopeAPI = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/mac/libnscopeapi.dylib"))
elif system == "Windows":
	nScopeAPI = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/win32/libnscopeapi.dll"))
elif system == "Linux":
	nScopeAPI = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/linux_i386/libnscopeapi.so"))


class scopeDev(Structure):
	pass

class requestObj(Structure):
	pass

scopeHandle = POINTER(scopeDev)
scopeRequest = POINTER(requestObj)

nScopeAPI.nScope_open.restype = c_int
nScopeAPI.nScope_open.argtypes = [c_bool, POINTER(POINTER(scopeDev))]

nScopeAPI.nScope_close.restype = c_int
nScopeAPI.nScope_close.argtypes = [POINTER(POINTER(scopeDev))]

nScopeAPI.nScope_clean.restype = c_int
nScopeAPI.nScope_clean.argtypes = [POINTER(POINTER(scopeDev))]

nScopeAPI.nScope_initialize.restype = c_int
nScopeAPI.nScope_initialize.argtypes = [POINTER(scopeDev)]

nScopeAPI.nScope_get_power_usage.restype = c_int
nScopeAPI.nScope_get_power_usage.argtypes = [POINTER(scopeDev), POINTER(c_double)]

nScopeAPI.nScope_get_power_state.restype = c_int
nScopeAPI.nScope_get_power_state.argtypes = [POINTER(scopeDev), POINTER(c_int)]

nScopeAPI.nScope_find_firmware_loader.restype = c_int
nScopeAPI.nScope_write_to_loader.restype = c_int
nScopeAPI.nScope_load_firmware.restype = c_int

nScopeAPI.nScope_check_API_version.restype = c_int
nScopeAPI.nScope_check_API_version.argtypes = [POINTER(c_double)]

nScopeAPI.nScope_check_FW_version.restype = c_int
nScopeAPI.nScope_check_FW_version.argtypes = [POINTER(c_double)]

nScopeAPI.nScope_check_API_build.restype = c_int
nScopeAPI.nScope_check_API_build.argtypes = [POINTER(c_int)]

def checkAPIver():
	APIver = c_double()
	nScopeAPI.nScope_check_API_version(byref(APIver))
	return APIver.value

def checkAPIbuild():
	APIbuild = c_int()
	nScopeAPI.nScope_check_API_build(byref(APIbuild))
	return APIbuild.value

def checkFWver():
	FWver = c_double()
	nScopeAPI.nScope_check_FW_version(byref(FWver))
	return FWver.value

def findFirmwareLoader():
	nScopeAPI.nScope_find_firmware_loader()

def writeToLoader():
    nScopeAPI.nScope_write_to_loader()

def loadFirmware():
	nScopeAPI.nScope_load_firmware()
