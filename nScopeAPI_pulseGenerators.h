/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file

    @brief contains function headers for controlling the nScope pulse outputs

    nScope has two pulse generators, P1 and P2, that output pulse signals from 0 to 5V. These signals
    are good for use with digital logic or for driving the logic of H-bridge controllers.

    These functions provide control over the timing characteristics of the two pulse outputs.
*/

#ifndef NSCOPEAPI_PULSEGNERATORS_H__
#define NSCOPEAPI_PULSEGNERATORS_H__



#ifdef __cplusplus
extern "C" {
#endif

    /** @brief Set a pulse channel (on/off)

        A true state means the pulse channel is on and outputing voltage
        A false state means the pulse channel is held at ground

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to turn on or off
        @param [in] PXon
            true: turn the channel on, false: turn it off
    */
    NSCOPE_API ErrorType nScope_set_PX_on(ScopeHandle nScope, int pChannel, bool PXon);

    /** @brief Get a pulse channel (on/off)

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to query
        @param [in] PXon
            pointer to boolean to store the on/off state of the queried channel
    */
    NSCOPE_API ErrorType nScope_get_PX_on(ScopeHandle nScope, int pChannel, bool* PXon);

    /** @brief Set the pulse channels (on/off)

        A true state means the pulse channel is on and outputing voltage
        A false state means the pulse channel is held at ground

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] P1on
            true: turn P1 on, false: turn it off
        @param [out] P2on
            true: turn P2 on, false: turn it off
    */
    NSCOPE_API ErrorType nScope_set_P1_P2_on(ScopeHandle nScope, bool P1on, bool P2on);

    /** @brief Get the pulse channels (on/off)

        A true state means the pulse channel is on and outputing voltage
        A false state means the pulse channel is held at ground

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] pulseGensOn
            pointer to boolean array to store the on/off states of the pulse channels
    */
    NSCOPE_API ErrorType nScope_get_P1_P2_on(ScopeHandle nScope, bool* pulseGensOn);

    /** @brief Set a pulse channel frequency in hz

        Not all frequency values can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to set
        @param [in] frequency
            the desired pulse frequency of the channel
    */
    NSCOPE_API ErrorType nScope_set_PX_frequency_in_hz(ScopeHandle nScope, int pChannel, double frequency);

    /** @brief Get a pulse channel frequency in hz

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to query
        @param [out] frequency
            pointer to the actual pulse frequency of the channel
    */
    NSCOPE_API ErrorType nScope_get_PX_frequency_in_hz(ScopeHandle nScope, int pChannel, double* frequency);

    /** @brief Set the pulse channel frequencies in hz

        Not all frequency values can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] frequency1
            the desired frequency of P1
        @param [in] frequency2
            the desired frequency of P2
    */
    NSCOPE_API ErrorType nScope_set_P1_P2_frequencies_in_hz(ScopeHandle nScope, double frequency1, double frequency2);

    /** @brief Get the pulse channel frequencies in hz

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] pulseFrequencies
            pointer to an array of doubles to store the actual pulse frequencies
    */
    NSCOPE_API ErrorType nScope_get_P1_P2_frequencies_in_hz(ScopeHandle nScope, double* pulseFrequencies);

    /** @brief Set a pulse channel period in milliseconds

        The pulse period is the time between pulses on the output channel

        Not all pulse periods can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to set
        @param [in] period
            the desired pulse period (ms) of the channel
    */
    NSCOPE_API ErrorType nScope_set_PX_period_in_ms(ScopeHandle nScope, int pChannel, double period);

    /** @brief Get a pulse channel period in milliseconds

        The pulse period is the time between pulses on the output channel

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to query
        @param [out] period
            pointer to the actual pulse period (ms) of the channel
    */
    NSCOPE_API ErrorType nScope_get_PX_period_in_ms(ScopeHandle nScope, int pChannel, double* period);

    /** @brief Set a pulse channel periods in milliseconds

        The pulse period is the time between pulses on the output channel

        Not all pulse periods can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] period1
            the desired pulse period (ms) on P1
        @param [in] period2
            the desired pulse period (ms) on P2
    */
    NSCOPE_API ErrorType nScope_set_P1_P2_periods_in_ms(ScopeHandle nScope, double period1, double period2);

    /** @brief Get a pulse channel periods in milliseconds

        The pulse period is the time between pulses on the output channel

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] pulsePeriods
            pointer to an array of doubles to store the actual pulse periods (ms)
    */
    NSCOPE_API ErrorType nScope_get_P1_P2_periods_in_ms(ScopeHandle nScope, double* pulsePeriods);

    /** @brief Set a pulse channel period in microseconds

        The pulse period is the time between pulses on the output channel

        Not all pulse periods can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to set
        @param [in] period
            the desired pulse period (µs) of the channel
    */
    NSCOPE_API ErrorType nScope_set_PX_period_in_us(ScopeHandle nScope, int pChannel, double period);

    /** @brief Get a pulse channel period in microseconds

        The pulse period is the time between pulses on the output channel

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to query
        @param [out] period
            pointer to the actual pulse period (µs) of the channel
    */
    NSCOPE_API ErrorType nScope_get_PX_period_in_us(ScopeHandle nScope, int pChannel, double* period);

    /** @brief Set a pulse channel periods in microseconds

        The pulse period is the time between pulses on the output channel

        Not all pulse periods can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] period1
            the desired pulse period (µs) on P1
        @param [in] period2
            the desired pulse period (µs) on P2
    */
    NSCOPE_API ErrorType nScope_set_P1_P2_periods_in_us(ScopeHandle nScope, double period1, double period2);

    /** @brief Get a pulse channel periods in microseconds

        The pulse period is the time between pulses on the output channel

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] pulsePeriods
            pointer to an array of doubles to store the actual pulse periods (µs)
    */
    NSCOPE_API ErrorType nScope_get_P1_P2_periods_in_us(ScopeHandle nScope, double* pulsePeriods);

    /** @brief Set a pulse channel duty percentage

        The duty percentage is the ratio of the time the output is high to the total period of the pulse.
        A duty of 100% means the signal is always 5V, and a signal of 0V means the signal is always 0V.

        Not all duty percentages can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to set
        @param [in] duty
            the desired pulse duty percentage (0.0-100.0)
    */
    NSCOPE_API ErrorType nScope_set_PX_duty_percentage(ScopeHandle nScope, int pChannel, double duty);

    /** @brief Get a pulse channel duty percentage

        The duty percentage is the ratio of the time the output is high to the total period of the pulse.
        A duty of 100% means the signal is always 5V, and a signal of 0V means the signal is always 0V.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to query
        @param [out] duty
            pointer to the actual pulse duty percentage (0.0-100.0)
    */
    NSCOPE_API ErrorType nScope_get_PX_duty_percentage(ScopeHandle nScope, int pChannel, double* duty);

    /** @brief Set the pulse channel duty percentages

        The duty percentage is the ratio of the time the output is high to the total period of the pulse.
        A duty of 100% means the signal is always 5V, and a signal of 0V means the signal is always 0V.

        Not all duty percentages can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] duty1
            the desired pulse duty percentage (0.0-100.0) on P1
        @param [in] duty2
            the desired pulse duty percentage (0.0-100.0) on P2
    */
    NSCOPE_API ErrorType nScope_set_P1_P2_duty_percentages(ScopeHandle nScope, double duty1, double duty2);

    /** @brief Get the pulse channel duty percentages

        The duty percentage is the ratio of the time the output is high to the total period of the pulse.
        A duty of 100% means the signal is always 5V, and a signal of 0V means the signal is always 0V.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] dutyPercentages
            pointer to an array of doubles to store the actual pulse duty percentages (0.0-100.0)
    */
    NSCOPE_API ErrorType nScope_get_P1_P2_duty_percentages(ScopeHandle nScope, double* dutyPercentages);

    /** @brief Set a pulse width in milliseconds on a pulse channel

        The pulse width is the amount of time the signal is high (5V) during each cycle

        Not all pulse widths can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to set
        @param [in] pulseWidth
            the desired pulse width (ms)
    */
    NSCOPE_API ErrorType nScope_set_PX_pulse_width_in_ms(ScopeHandle nScope, int pChannel, double pulseWidth);

    /** @brief Get a pulse width in milliseconds on a pulse channel

        The pulse width is the amount of time the signal is high (5V) during each cycle

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to query
        @param [out] pulseWidth
            pointer to the actual pulse width (ms)
    */
    NSCOPE_API ErrorType nScope_get_PX_pulse_width_in_ms(ScopeHandle nScope, int pChannel, double* pulseWidth);

    /** @brief Set the pulse widths in milliseconds on the pulse channels

        The pulse width is the amount of time the signal is high (5V) during each cycle

        Not all pulse widths can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pulseWidth1
            the desired pulse width (ms) on P1
        @param [in] pulseWidth2
            the desired pulse width (ms) on P2
    */
    NSCOPE_API ErrorType nScope_set_P1_P2_pulse_widths_in_ms(ScopeHandle nScope, double pulseWidth1, double pulseWidth2);

    /** @brief Get the pulse widths in milliseconds on the pulse channels

        The pulse width is the amount of time the signal is high (5V) during each cycle

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] pulseWidths
            pointer to an array of doubles to store the actual pulse widths (ms)
    */
    NSCOPE_API ErrorType nScope_get_P1_P2_pulse_widths_in_ms(ScopeHandle nScope, double* pulseWidths);

    /** @brief Set a pulse width in microseconds on a pulse channel

        The pulse width is the amount of time the signal is high (5V) during each cycle

        Not all pulse widths can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to set
        @param [in] pulseWidth
            the desired pulse width (µs)
    */
    NSCOPE_API ErrorType nScope_set_PX_pulse_width_in_us(ScopeHandle nScope, int pChannel, double pulseWidth);

    /** @brief Get a pulse width in microseconds on a pulse channel

        The pulse width is the amount of time the signal is high (5V) during each cycle

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to query
        @param [out] pulseWidth
            pointer to the actual pulse width (µs)
    */
    NSCOPE_API ErrorType nScope_get_PX_pulse_width_in_us(ScopeHandle nScope, int pChannel, double* pulseWidth);

    /** @brief Set the pulse widths in microseconds on the pulse channels

        The pulse width is the amount of time the signal is high (5V) during each cycle

        Not all pulse widths can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pulseWidth1
            the desired pulse width (µs) on P1
        @param [in] pulseWidth2
            the desired pulse width (µs) on P2
    */
    NSCOPE_API ErrorType nScope_set_P1_P2_pulse_widths_in_us(ScopeHandle nScope, double pulseWidth1, double pulseWidth2);

    /** @brief Get the pulse widths in microseconds on the pulse channels

        The pulse width is the amount of time the signal is high (5V) during each cycle

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] pulseWidths
            pointer to an array of doubles to store the actual pulse widths (µs)
    */
    NSCOPE_API ErrorType nScope_get_P1_P2_pulse_widths_in_us(ScopeHandle nScope, double* pulseWidths);

    /** @brief Send a single pulse out on a pulse channel

        The pulse width is the amount of time (ms) the signal is high (5V)

        Not all pulse widths can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pChannel
            the channel (1 or 2) to use
        @param [in] pulseWidth
            the desired pulse width (ms)
    */
    NSCOPE_API ErrorType nScope_send_PX_oneshot_pulse(ScopeHandle nScope, int pChannel, double pulseWidth);

    /** @brief Send a single pulse out on both pulse channels

        The pulse width is the amount of time (ms) the signal is high (5V)

        Not all pulse widths can be acheived, nScope will automatically choose the closest approximation.

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] pulseWidth1
            the desired pulse width (ms) on P1
        @param [in] pulseWidth2
            the desired pulse width (ms) on P2
    */
    NSCOPE_API ErrorType nScope_send_P1_P2_oneshot_pulses(ScopeHandle nScope, double pulseWidth1, double pulseWidth2);



#ifdef __cplusplus
}
#endif

#endif
