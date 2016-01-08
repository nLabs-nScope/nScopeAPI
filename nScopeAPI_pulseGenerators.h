/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

#ifndef NSCOPEAPI_PULSEGNERATORS_H__
#define NSCOPEAPI_PULSEGNERATORS_H__



#ifdef __cplusplus
extern "C" {
#endif

    double NSCOPE_API_EXPORT_CALL nScope_set_P1_frequency_in_hz(scopeHandle *nScope, double frequency);
    double NSCOPE_API_EXPORT_CALL nScope_get_P1_frequency_in_hz(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_P2_frequency_in_hz(scopeHandle *nScope, double frequency);
    double NSCOPE_API_EXPORT_CALL nScope_get_P2_frequency_in_hz(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_pulse_frequencies_in_hz(scopeHandle *nScope, double frequency0, double frequency1);
    int NSCOPE_API_EXPORT_CALL nScope_get_pulse_frequencies_in_hz(scopeHandle *nScope, double* pulseFrequencies);

    double NSCOPE_API_EXPORT_CALL nScope_set_P1_period_in_ms(scopeHandle *nScope, double period);
    double NSCOPE_API_EXPORT_CALL nScope_get_P1_period_in_ms(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_P2_period_in_ms(scopeHandle *nScope, double period);
    double NSCOPE_API_EXPORT_CALL nScope_get_P2_period_in_ms(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_pulse_periods_in_ms(scopeHandle *nScope, double period0, double period1);
    int NSCOPE_API_EXPORT_CALL nScope_get_pulse_periods_in_ms(scopeHandle *nScope, double* pulsePeriods);

    double NSCOPE_API_EXPORT_CALL nScope_set_P1_period_in_us(scopeHandle *nScope, double period);
    double NSCOPE_API_EXPORT_CALL nScope_get_P1_period_in_us(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_P2_period_in_us(scopeHandle *nScope, double period);
    double NSCOPE_API_EXPORT_CALL nScope_get_P2_period_in_us(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_pulse_periods_in_us(scopeHandle *nScope, double period0, double period1);
    int NSCOPE_API_EXPORT_CALL nScope_get_pulse_periods_in_us(scopeHandle *nScope, double* pulsePeriods);

    double NSCOPE_API_EXPORT_CALL nScope_set_P1_duty_percentage(scopeHandle *nScope, double dutyPercentage);
    double NSCOPE_API_EXPORT_CALL nScope_get_P1_duty_percentage(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_P2_duty_percentage(scopeHandle *nScope, double dutyPercentage);
    double NSCOPE_API_EXPORT_CALL nScope_get_P2_duty_percentage(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_pulse_duty_percentages(scopeHandle *nScope, double duty0, double duty1);
    int NSCOPE_API_EXPORT_CALL nScope_get_pulse_duty_percentages(scopeHandle *nScope, double* dutyPercentages);

    double NSCOPE_API_EXPORT_CALL nScope_set_P1_pulse_width_in_ms(scopeHandle *nScope, double pulseWidth);
    double NSCOPE_API_EXPORT_CALL nScope_get_P1_pulse_width_in_ms(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_P2_pulse_width_in_ms(scopeHandle *nScope, double pulseWidth);
    double NSCOPE_API_EXPORT_CALL nScope_get_P2_pulse_width_in_ms(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_pulse_widths_in_ms(scopeHandle *nScope, double pulseWidth0, double pulseWidth1);
    int NSCOPE_API_EXPORT_CALL nScope_get_pulse_widths_in_ms(scopeHandle *nScope, double* pulseWidths);

    double NSCOPE_API_EXPORT_CALL nScope_set_P1_pulse_width_in_us(scopeHandle *nScope, double pulseWidth);
    double NSCOPE_API_EXPORT_CALL nScope_get_P1_pulse_width_in_us(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_P2_pulse_width_in_us(scopeHandle *nScope, double pulseWidth);
    double NSCOPE_API_EXPORT_CALL nScope_get_P2_pulse_width_in_us(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_pulse_widths_in_us(scopeHandle *nScope, double pulseWidth0, double pulseWidth1);
    int NSCOPE_API_EXPORT_CALL nScope_get_pulse_widths_in_us(scopeHandle *nScope, double* pulseWidths);

    int NSCOPE_API_EXPORT_CALL nScope_set_P1_on(scopeHandle *nScope, int P1on);
    int NSCOPE_API_EXPORT_CALL nScope_get_P1_on(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_P2_on(scopeHandle *nScope, int P2on);
    int NSCOPE_API_EXPORT_CALL nScope_get_P2_on(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_pulse_generators_on(scopeHandle *nScope, int P1on, int P2on);
    int NSCOPE_API_EXPORT_CALL nScope_get_pulse_generators_on(scopeHandle *nScope, int* pulseGensOn);

    double NSCOPE_API_EXPORT_CALL nScope_send_P1_pulse(scopeHandle *nScope, double pulseWidth);
    double NSCOPE_API_EXPORT_CALL nScope_send_P2_pulse(scopeHandle *nScope, double pulseWidth);
    double NSCOPE_API_EXPORT_CALL nScope_send_pulses(scopeHandle *nScope, double pulseWidth0, double pulseWidth1);



#ifdef __cplusplus
}
#endif

#endif
