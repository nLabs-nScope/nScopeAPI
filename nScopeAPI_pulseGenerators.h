/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file

    @brief contains function headers for controlling the nScope pulse outputs
*/

#ifndef NSCOPEAPI_PULSEGNERATORS_H__
#define NSCOPEAPI_PULSEGNERATORS_H__



#ifdef __cplusplus
extern "C" {
#endif

    NSCOPE_API ErrorType nScope_set_PX_on(ScopeHandle nScope, int pChannel, bool PXon);
    NSCOPE_API ErrorType nScope_get_PX_on(ScopeHandle nScope, int pChannel, bool* PXon);
    NSCOPE_API ErrorType nScope_set_P1_P2_on(ScopeHandle nScope, bool P1on, bool P2on);
    NSCOPE_API ErrorType nScope_get_P1_P2_on(ScopeHandle nScope, bool* pulseGensOn);

    NSCOPE_API ErrorType nScope_set_PX_frequency_in_hz(ScopeHandle nScope, int pChannel, double frequency);
    NSCOPE_API ErrorType nScope_get_PX_frequency_in_hz(ScopeHandle nScope, int pChannel, double* frequency);
    NSCOPE_API ErrorType nScope_set_P1_P2_frequencies_in_hz(ScopeHandle nScope, double frequency0, double frequency1);
    NSCOPE_API ErrorType nScope_get_P1_P2_frequencies_in_hz(ScopeHandle nScope, double* pulseFrequencies);

    NSCOPE_API ErrorType nScope_set_PX_period_in_ms(ScopeHandle nScope, int pChannel, double period);
    NSCOPE_API ErrorType nScope_get_PX_period_in_ms(ScopeHandle nScope, int pChannel, double* period);
    NSCOPE_API ErrorType nScope_set_P1_P2_periods_in_ms(ScopeHandle nScope, double period0, double period1);
    NSCOPE_API ErrorType nScope_get_P1_P2_periods_in_ms(ScopeHandle nScope, double* pulsePeriods);

    NSCOPE_API ErrorType nScope_set_PX_period_in_us(ScopeHandle nScope, int pChannel, double period);
    NSCOPE_API ErrorType nScope_get_PX_period_in_us(ScopeHandle nScope, int pChannel, double* period);
    NSCOPE_API ErrorType nScope_set_P1_P2_periods_in_us(ScopeHandle nScope, double period0, double period1);
    NSCOPE_API ErrorType nScope_get_P1_P2_periods_in_us(ScopeHandle nScope, double* pulsePeriods);

    NSCOPE_API ErrorType nScope_set_PX_duty_percentage(ScopeHandle nScope, int pChannel, double duty);
    NSCOPE_API ErrorType nScope_get_PX_duty_percentage(ScopeHandle nScope, int pChannel, double* duty);
    NSCOPE_API ErrorType nScope_set_P1_P2_duty_percentages(ScopeHandle nScope, double duty0, double duty1);
    NSCOPE_API ErrorType nScope_get_P1_P2_duty_percentages(ScopeHandle nScope, double* dutyPercentages);

    NSCOPE_API ErrorType nScope_set_PX_pulse_width_in_ms(ScopeHandle nScope, int pChannel, double pulseWidth);
    NSCOPE_API ErrorType nScope_get_PX_pulse_width_in_ms(ScopeHandle nScope, int pChannel, double* pulseWidth);
    NSCOPE_API ErrorType nScope_set_P1_P2_pulse_widths_in_ms(ScopeHandle nScope, double pulseWidth0, double pulseWidth1);
    NSCOPE_API ErrorType nScope_get_P1_P2_pulse_widths_in_ms(ScopeHandle nScope, double* pulseWidths);

    NSCOPE_API ErrorType nScope_set_PX_pulse_width_in_us(ScopeHandle nScope, int pChannel, double pulseWidth);
    NSCOPE_API ErrorType nScope_get_PX_pulse_width_in_us(ScopeHandle nScope, int pChannel, double* pulseWidth);
    NSCOPE_API ErrorType nScope_set_P1_P2_pulse_widths_in_us(ScopeHandle nScope, double pulseWidth0, double pulseWidth1);
    NSCOPE_API ErrorType nScope_get_P1_P2_pulse_widths_in_us(ScopeHandle nScope, double* pulseWidths);

    NSCOPE_API ErrorType nScope_send_PX_oneshot_pulse(ScopeHandle nScope, int pChannel, double pulseWidth);
    NSCOPE_API ErrorType nScope_send_P1_P2_oneshot_pulses(ScopeHandle nScope, double pulseWidth1, double pulseWidth2);



#ifdef __cplusplus
}
#endif

#endif
