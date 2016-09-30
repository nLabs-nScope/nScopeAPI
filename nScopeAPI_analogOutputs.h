/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope.

 David Meyer

 10/23/2014

 Copyright 2015 nLabs, All Rights Reserved.

********************************************************/

/** @file

    @brief contains function headers for controlling the nScope analog outputs
*/

#ifndef NSCOPEAPI_ANALOGOUTPUTS_H__
#define NSCOPEAPI_ANALOGOUTPUTS_H__


#ifdef __cplusplus
extern "C" {
#endif

    /** @brief Set the analog channel (on/off)

        A true state means the analog channel is on and outputing voltage
        A false state means the analog channel is held at ground

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to turn on or off
        @param [in] aOn
            true: turn the channel on, false: turn it off
    */
    NSCOPE_API ErrorType nScope_set_AX_on(ScopeHandle nScope, int aChannel, bool aOn);

    /** @brief Get the analog channel (on/off) and store it in aOn

        A true state means the analog channel is on and outputing voltage
        A false state means the analog channel is held at ground

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to query
        @param [out] aOn
            pointer to a boolean to store the state of the analog channel
    */
    NSCOPE_API ErrorType nScope_get_AX_on(ScopeHandle nScope, int aChannel, bool* aOn);

    /** @brief Set the analog channel output frequency

        Not all frequency values can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to set
        @param [in] frequency
            desired signal frequency in hz
    */
    NSCOPE_API ErrorType nScope_set_AX_frequency_in_hz(ScopeHandle nScope, int aChannel, double frequency);

    /** @brief Get the analog channel output frequency and store it in the given variable

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to query
        @param [out] frequency
            pointer to double to store the actual signal frequency in hz
    */
    NSCOPE_API ErrorType nScope_get_AX_frequency_in_hz(ScopeHandle nScope, int aChannel, double* frequency);

    /** @brief Set the analog channel output wave type

        The output waves can be set to any one of the available #WaveType

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to set
        @param [in] wave
            the signal #WaveType
    */
    NSCOPE_API ErrorType nScope_set_AX_wave_type(ScopeHandle nScope, int aChannel, WaveType wave);

    /** @brief Get the analog channel output wave type

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to query
        @param [out] wave
            pointer to #WaveType to store the current wave type
    */
    NSCOPE_API ErrorType nScope_get_AX_wave_type(ScopeHandle nScope, int aChannel, WaveType* wave);

    /** @brief Set the analog channel unipolarity

        Unipolar waves range from 0 to amplitude, bipolar waves range from -amplitude to amplitude

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to set
        @param [in] isUnipolar
            true to set the output to be unipolar only, false to set it bipolar
    */
    NSCOPE_API ErrorType nScope_set_AX_unipolar(ScopeHandle nScope, int aChannel, bool isUnipolar);

    /** @brief Get the analog channel unipolarity

        Unipolar waves range from 0 to amplitude, bipolar waves range from -amplitude to amplitude

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to query
        @param [out] isUnipolar
            true if the wave is unipolar, false if it is not
    */
    NSCOPE_API ErrorType nScope_get_AX_unipolar(ScopeHandle nScope, int aChannel, bool* isUnipolar);

    /** @brief Set the analog channel amplitude

        Unipolar waves range from 0 to amplitude, bipolar waves range from -amplitude to amplitude

        Not all amplitude values can be acheived, nScope will automatically choose the closest approximation

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to set
        @param [in] amplitude
            desired signal amplitude in volts
    */
    NSCOPE_API ErrorType nScope_set_AX_amplitude(ScopeHandle nScope, int aChannel, double amplitude);

    /** @brief Get the analog channel amplitude

        Retreives the actual signal amplitude and puts it into the amplitude variable

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] aChannel
            the channel (1 or 2) to query
        @param [out] amplitude
            actual signal amplitude in volts
    */
    NSCOPE_API ErrorType nScope_get_AX_amplitude(ScopeHandle nScope, int aChannel, double* amplitude);

#ifdef __cplusplus
}
#endif

#endif
