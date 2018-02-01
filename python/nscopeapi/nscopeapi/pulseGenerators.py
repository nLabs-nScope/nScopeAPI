from ctypes import POINTER, c_int, c_bool, c_double
from nscopeapi.nScopeDefs import *

lib.nScope_set_PX_on.restype = c_int
lib.nScope_set_PX_on.argtypes = [POINTER(scopeDev), c_int, c_bool]
lib.nScope_get_PX_on.restype = c_int
lib.nScope_get_PX_on.argtypes = [POINTER(scopeDev), c_int, POINTER(c_bool)]

lib.nScope_set_P1_P2_on.restype = c_int
lib.nScope_set_P1_P2_on.argtypes = [POINTER(scopeDev),c_bool,c_bool]
lib.nScope_get_P1_P2_on.restype = c_int
lib.nScope_get_P1_P2_on.argtypes = [POINTER(scopeDev),POINTER(c_bool*2)]

lib.nScope_set_PX_frequency_in_hz.restype = c_int
lib.nScope_set_PX_frequency_in_hz.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_PX_frequency_in_hz.restype = c_int
lib.nScope_get_PX_frequency_in_hz.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

lib.nScope_set_P1_P2_frequencies_in_hz.restype = c_int
lib.nScope_set_P1_P2_frequencies_in_hz.argtypes = [POINTER(scopeDev),c_double,c_double]
lib.nScope_get_P1_P2_frequencies_in_hz.restype = c_int
lib.nScope_get_P1_P2_frequencies_in_hz.argtypes = [POINTER(scopeDev),POINTER(c_double*2)]

lib.nScope_set_PX_period_in_ms.restype = c_int
lib.nScope_set_PX_period_in_ms.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_PX_period_in_ms.restype = c_int
lib.nScope_get_PX_period_in_ms.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

lib.nScope_set_P1_P2_periods_in_ms.restype = c_int
lib.nScope_set_P1_P2_periods_in_ms.argtypes = [POINTER(scopeDev),c_double,c_double]
lib.nScope_get_P1_P2_periods_in_ms.restype = c_int
lib.nScope_get_P1_P2_periods_in_ms.argtypes = [POINTER(scopeDev),POINTER(c_double*2)]

lib.nScope_set_PX_period_in_us.restype = c_int
lib.nScope_set_PX_period_in_us.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_PX_period_in_us.restype = c_int
lib.nScope_get_PX_period_in_us.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

lib.nScope_set_P1_P2_periods_in_us.restype = c_int
lib.nScope_set_P1_P2_periods_in_us.argtypes = [POINTER(scopeDev),c_double,c_double]
lib.nScope_get_P1_P2_periods_in_us.restype = c_int
lib.nScope_get_P1_P2_periods_in_us.argtypes = [POINTER(scopeDev),POINTER(c_double*2)]

lib.nScope_set_PX_duty_percentage.restype = c_int
lib.nScope_set_PX_duty_percentage.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_PX_duty_percentage.restype = c_int
lib.nScope_get_PX_duty_percentage.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

lib.nScope_set_P1_P2_duty_percentages.restype = c_int
lib.nScope_set_P1_P2_duty_percentages.argtypes = [POINTER(scopeDev),c_double,c_double]
lib.nScope_get_P1_P2_duty_percentages.restype = c_int
lib.nScope_get_P1_P2_duty_percentages.argtypes = [POINTER(scopeDev),POINTER(c_double*2)]

lib.nScope_set_PX_pulse_width_in_ms.restype = c_int
lib.nScope_set_PX_pulse_width_in_ms.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_PX_pulse_width_in_ms.restype = c_int
lib.nScope_get_PX_pulse_width_in_ms.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

lib.nScope_set_P1_P2_pulse_widths_in_ms.restype = c_int
lib.nScope_set_P1_P2_pulse_widths_in_ms.argtypes = [POINTER(scopeDev),c_double,c_double]
lib.nScope_get_P1_P2_pulse_widths_in_ms.restype = c_int
lib.nScope_get_P1_P2_pulse_widths_in_ms.argtypes = [POINTER(scopeDev),POINTER(c_double*2)]

lib.nScope_set_PX_pulse_width_in_us.restype = c_int
lib.nScope_set_PX_pulse_width_in_us.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_get_PX_pulse_width_in_us.restype = c_int
lib.nScope_get_PX_pulse_width_in_us.argtypes = [POINTER(scopeDev), c_int, POINTER(c_double)]

lib.nScope_set_P1_P2_pulse_widths_in_us.restype = c_int
lib.nScope_set_P1_P2_pulse_widths_in_us.argtypes = [POINTER(scopeDev),c_double,c_double]
lib.nScope_get_P1_P2_pulse_widths_in_us.restype = c_int
lib.nScope_get_P1_P2_pulse_widths_in_us.argtypes = [POINTER(scopeDev),POINTER(c_double*2)]

lib.nScope_send_PX_oneshot_pulse.restype = c_int
lib.nScope_send_PX_oneshot_pulse.argtypes = [POINTER(scopeDev), c_int, c_double]
lib.nScope_send_P1_P2_oneshot_pulses.restype = c_int
lib.nScope_send_P1_P2_oneshot_pulses.argtypes = [POINTER(scopeDev),c_double,c_double]

	# 	if rtrn == -111:
	# 		raise ValueError("Requested frequency is too fast")
	# 		return
	# 	if rtrn == -110:
	# 		raise ValueError("Requested frequency is too slow")
	# 		return
	# 	return rtrn
    	# 	if rtrn == -121:
    	# 		raise Warning("Requested pulse width results in always high signal")
    	# 	if rtrn == -120:
    	# 		raise Warning("Requested pulse width results in always low signal")
	# 	if rtrn == -110:
	# 		raise ValueError("Requested period is too short")
	# 		return
	# 	if rtrn == -111:
	# 		raise ValueError("Requested period is too long")
	# 		return
class Implementation:
    def setPXOn(self,px,pxOn):
        pxOn = bool(pxOn)
        lib.nScope_set_PX_on(self.handle,px,pxOn)
        return

    def getPXOn(self,px):
        pxOn = c_bool()
        lib.nScope_get_PX_on(self.handle,px,byref(pxOn))
        return pxOn.value

    def setP1P2On(self,p1on,p2on):
        p1on = bool(p1on)
        p2on = bool(p2on)
        lib.nScope_set_P1_P2_on(self.handle,p1on,p2on)
        return

    def getP1P2On(self):
        pxOn = (c_bool*2)()
        lib.nScope_get_P1_P2_on(self.handle,byref(pxOn))
        return list(pxOn)

    def setPXFrequencyInHz(self,px,pxFrequency):
        lib.nScope_set_PX_frequency_in_hz(self.handle,px,pxFrequency)
        return

    def getPXFrequencyInHz(self,px):
        pxFrequency = c_double()
        lib.nScope_get_PX_frequency_in_hz(self.handle,px,byref(pxFrequency))
        return pxFrequency.value

    def setP1P2FrequenciesInHz(self,p1frequency,p2frequency):
        lib.nScope_set_P1_P2_frequencies_in_hz(self.handle,p1frequency,p2frequency)
        return

    def getP1P2FrequenciesInHz(self):
        pxFrequencies = (c_double*2)()
        lib.nScope_get_P1_P2_frequencies_in_hz(self.handle,byref(pxFrequencies))
        return list(pxFrequencies)

    def setPXPeriodInMs(self,px,pxPeriod):
        lib.nScope_set_PX_period_in_ms(self.handle,px,pxPeriod)
        return

    def getPXPeriodInMs(self,px):
        pxPeriod = c_double()
        lib.nScope_get_PX_period_in_ms(self.handle,px,byref(pxPeriod))
        return pxPeriod.value

    def setP1P2PeriodsInMs(self,p1period,p2period):
        lib.nScope_set_P1_P2_periods_in_ms(self.handle,p1period,p2period)
        return

    def getP1P2PeriodsInMs(self):
        pxPeriods = (c_double*2)()
        lib.nScope_get_P1_P2_periods_in_ms(self.handle,byref(pxPeriods))
        return list(pxPeriods)

    def setPXPeriodInUs(self,px,pxPeriod):
        lib.nScope_set_PX_period_in_us(self.handle,px,pxPeriod)
        return

    def getPXPeriodInUs(self,px):
        pxPeriod = c_double()
        lib.nScope_get_PX_period_in_us(self.handle,px,byref(pxPeriod))
        return pxPeriod.value

    def setP1P2PeriodsInUs(self,p1period,p2period):
        lib.nScope_set_P1_P2_periods_in_us(self.handle,p1period,p2period)
        return

    def getP1P2PeriodsInUs(self):
        pxPeriods = (c_double*2)()
        lib.nScope_get_P1_P2_periods_in_us(self.handle,byref(pxPeriods))
        return list(pxPeriods)

    def setPXDutyPercentage(self,px,pxDuty):
        lib.nScope_set_PX_duty_percentage(self.handle,px,pxDuty)
        return

    def getPXDutyPercentage(self,px):
        pxDuty = c_double()
        lib.nScope_get_PX_duty_percentage(self.handle,px,byref(pxDuty))
        return pxDuty.value

    def setP1P2DutyPercentages(self,p1duty,p2duty):
        lib.nScope_set_P1_P2_duty_percentages(self.handle,p1duty,p2duty)
        return

    def getP1P2DutyPercentages(self):
        pxDuties = (c_double*2)()
        lib.nScope_get_P1_P2_duty_percentages(self.handle,byref(pxDuties))
        return list(pxDuties)

    def setPXPulseWidthInMs(self,px,pxPulseWidth):
        lib.nScope_set_PX_pulse_width_in_ms(self.handle,px,pxPulseWidth)
        return

    def getPXPulseWidthInMs(self,px):
        pxPulseWidth = c_double()
        lib.nScope_get_PX_pulse_width_in_ms(self.handle,px,byref(pxPulseWidth))
        return pxPulseWidth.value

    def setP1P2PulseWidthsInMs(self,p1pulseWidth,p2pulseWidth):
        lib.nScope_set_P1_P2_pulse_widths_in_ms(self.handle,p1pulseWidth,p2pulseWidth)
        return

    def getP1P2PulseWidthsInMs(self):
        pxPulseWidths = (c_double*2)()
        lib.nScope_get_P1_P2_pulse_widths_in_ms(self.handle,byref(pxPulseWidths))
        return list(pxPulseWidths)

    def setPXPulseWidthInUs(self,px,pxPulseWidth):
        lib.nScope_set_PX_pulse_width_in_us(self.handle,px,pxPulseWidth)
        return

    def getPXPulseWidthInUs(self,px):
        pxPulseWidth = c_double()
        lib.nScope_get_PX_pulse_width_in_us(self.handle,px,byref(pxPulseWidth))
        return pxPulseWidth.value

    def setP1P2PulseWidthsInUs(self,p1pulseWidth,p2pulseWidth):
        lib.nScope_set_P1_P2_pulse_widths_in_us(self.handle,p1pulseWidth,p2pulseWidth)
        return

    def getP1P2PulseWidthsInUs(self):
        pxPulseWidths = (c_double*2)()
        lib.nScope_get_P1_P2_pulse_widths_in_us(self.handle,byref(pxPulseWidths))
        return list(pxPulseWidths)

    def sendPXpulse(self,px,pulseWidth):
        lib.nScope_send_PX_oneshot_pulse(self.handle,px,pulseWidth)
        return

    def sendP1P2pulses(self,pulseWidth1,pulseWidth2):
        lib.nScope_send_P1_P2_oneshot_pulses(self.handle,pulseWidth1,pulseWidth2)
        return
