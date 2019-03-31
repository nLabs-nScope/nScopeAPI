from ctypes import CDLL, Structure, POINTER, byref, c_double, c_int, c_bool
import platform,os

system = platform.system()
machine = platform.machine()
architecture = platform.architecture()[0]

intelMachines = ["i386","x86","x86_64"]
armMachines = ["arm","armv7","armv71","armv7","armv8b","armv8l","aarch64","aarch64_be"]

if system == "Darwin":
	lib = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/mac/libnscopeapi.dylib"))

elif system == "Windows":
	if architecture == "32bit":
		lib = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/win32/libnscopeapi.dll"))
	elif architecture == "64bit":
		lib = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/win64/libnscopeapi.dll"))
	else:
		raise(EnvironmentError("Unrecognized architecture: '%s'" % architecture))

elif system == "Linux":
	if machine in intelMachines:
		if architecture == "32bit":
			lib = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/linux_i386/libnscopeapi.so"))
		elif architecture == "64bit":
			lib = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/linux_amd64/libnscopeapi.so"))
		else:
			raise(EnvironmentError("Unrecognized architecture: '%s'" % architecture))
	elif machine in armMachines:
		if architecture == "32bit":
			lib = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/linux_armhf/libnscopeapi.so"))
		elif architecture == "64bit":
			lib = CDLL(os.path.join(os.path.abspath(os.path.dirname(__file__)), "lib/linux_arm64/libnscopeapi.so"))
		else:
			raise(EnvironmentError("Unrecognized architecture: '%s'" % architecture))
	else:
		raise(EnvironmentError("Unrecognized machine type: '%s'" % machine))
else:
	raise(EnvironmentError("Unrecognized system type: '%s'" % system))

class scopeDev(Structure):
	pass

class requestObj(Structure):
	pass

scopeHandle = POINTER(scopeDev)
scopeRequest = POINTER(requestObj)

lib.nScope_open.restype = c_int
lib.nScope_open.argtypes = [c_bool, POINTER(POINTER(scopeDev))]

lib.nScope_close.restype = c_int
lib.nScope_close.argtypes = [POINTER(POINTER(scopeDev))]

lib.nScope_clean.restype = c_int
lib.nScope_clean.argtypes = [POINTER(POINTER(scopeDev))]

lib.nScope_initialize.restype = c_int
lib.nScope_initialize.argtypes = [POINTER(scopeDev)]

lib.nScope_get_power_usage.restype = c_int
lib.nScope_get_power_usage.argtypes = [POINTER(scopeDev), POINTER(c_double)]

lib.nScope_get_power_state.restype = c_int
lib.nScope_get_power_state.argtypes = [POINTER(scopeDev), POINTER(c_int)]

lib.nScope_find_firmware_loader.restype = c_int
lib.nScope_write_to_loader.restype = c_int
lib.nScope_load_firmware.restype = c_int

lib.nScope_check_API_version.restype = c_int
lib.nScope_check_API_version.argtypes = [POINTER(c_double)]

lib.nScope_check_FW_version.restype = c_int
lib.nScope_check_FW_version.argtypes = [POINTER(c_double)]

lib.nScope_check_API_build.restype = c_int
lib.nScope_check_API_build.argtypes = [POINTER(c_int)]

def checkAPIver():
	APIver = c_double()
	lib.nScope_check_API_version(byref(APIver))
	return APIver.value

def checkAPIbuild():
	APIbuild = c_int()
	lib.nScope_check_API_build(byref(APIbuild))
	return APIbuild.value

def checkFWver():
	FWver = c_double()
	lib.nScope_check_FW_version(byref(FWver))
	return FWver.value

def findFirmwareLoader():
	lib.nScope_find_firmware_loader()

def writeToLoader():
    lib.nScope_write_to_loader()

def loadFirmware():
	lib.nScope_load_firmware()
