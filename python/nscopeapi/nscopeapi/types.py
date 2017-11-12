
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
