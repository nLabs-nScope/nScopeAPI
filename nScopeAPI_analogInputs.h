/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file

    @brief contains function headers for controlling the nScope analog inputs
*/

#ifndef NSCOPEAPI_ANALOGINPUTS_H__
#define NSCOPEAPI_ANALOGINPUTS_H__



#ifdef __cplusplus
extern "C" {
#endif

    /** @brief Set the channel states (on/off) for all channels

        A true state means the channel is on and will sample if a request is sent

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [in] ch1on
            true: turn channel 1 on, false: turn it off
        @param [in] ch2on
            true: turn channel 2 on, false: turn it off
        @param [in] ch3on
            true: turn channel 3 on, false: turn it off
        @param [in] ch4on
            true: turn channel 4 on, false: turn it off
    */
    NSCOPE_API ErrorType nScope_set_channels_on(ScopeHandle nScope, bool ch1on, bool ch2on, bool ch3on, bool ch4on);

    /** @brief Get the channel states (on/off) for all channels

        A true state means the channel is on and will sample if a request is sent

        @returns
            nScope #ErrorType
        @param [in] nScope
            pointer to nScope handle
        @param [out] channelsOn
            pointer to an array of booleans for retreiving the on state for each channel
    */
    NSCOPE_API ErrorType nScope_get_channels_on(ScopeHandle nScope, bool* channelsOn);

    /** @brief Get the number of channels currently on

        @returns
            nScope #ErrorType
        @param [in] nScope
            nScope handle
        @param [out] numChannelsOn
            pointer to a variable for retreiving the number of channels on
    */
    NSCOPE_API ErrorType nScope_get_num_channels_on(ScopeHandle nScope, int* numChannelsOn);

    /** @brief Set a channel state on or off

        A true state means the channel is on and will sample if a request is sent

        @returns
            1 on success
        @param nScope
            pointer to nScope handle
        @param ch
            channel number to set on or off
        @param channelOn
            true: turn the channel on, false: turn the channel off
    */
    NSCOPE_API ErrorType nScope_set_ChX_on(ScopeHandle nScope, int ch, bool channelOn);

    /** @brief Get the on/off state of a given channel

        @returns
            1 if the channel is on, 0 if it is not
        @param nScope
            pointer to nScope handle
        @param ch
            channel number to query
    */
    NSCOPE_API ErrorType nScope_get_ChX_on(ScopeHandle nScope, int ch, bool* channelOn);

    /** @brief Set the channel gains for all channels

        A gain of 1 indicates

        @returns
            1 on success
        @param nScope
            pointer to nScope handle
        @param ch1Gain
            channel 1 gain
        @param ch2Gain
            channel 2 gain
        @param ch3Gain
            channel 3 gain
        @param ch4Gain
            channel 4 gain
    */
    NSCOPE_API ErrorType nScope_set_channel_gains(ScopeHandle nScope, double ch1Gain, double ch2Gain, double ch3Gain, double ch4Gain);

    /** @brief Get the channel gains for all channels

        @returns
            1 on success
        @param nScope
            pointer to nScope handle
        @param channelGains
            pointer to an array of doubles for retreiving the gain for each channel
    */
    NSCOPE_API ErrorType nScope_get_channel_gains(ScopeHandle nScope, double* channelGains);

    /** @brief Set a given channel's gain

        @returns
            the actual gain of the channel
        @param nScope
            pointer to nScope handle
        @param ch
            channel number to set on or off
        @param channelGain
            the desired gain of the channel
    */
    NSCOPE_API ErrorType nScope_set_ChX_gain(ScopeHandle nScope, int ch, double channelGain);

    /** @brief Get the gain of a given channel

        @returns
            the current gain of the given channel
        @param nScope
            pointer to nScope handle
        @param ch
            channel number to query
    */
    NSCOPE_API ErrorType nScope_get_ChX_gain(ScopeHandle nScope, int ch, double* channelGain);

    /** @brief Set the channel levels for all channels

        Level means:

        @returns
            1 on success
        @param nScope
            pointer to nScope handle
        @param ch1Gain
            channel 1 level
        @param ch2Gain
            channel 2 level
        @param ch3Gain
            channel 3 level
        @param ch4Gain
            channel 4 level
    */
    NSCOPE_API ErrorType nScope_set_channel_levels(ScopeHandle nScope, double ch1Level, double ch2Level, double ch3Level, double ch4Level);

    /** @brief Get the channel levels for all channels

        @returns
            1 on success
        @param nScope
            pointer to nScope handle
        @param channelGains
            pointer to an array of doubles for retreiving the level for each channel
    */
    NSCOPE_API ErrorType nScope_get_channel_levels(ScopeHandle nScope, double* channelLevels);

    /** @brief Set a given channel's level

        @returns
            the actual level of the channel
        @param nScope
            pointer to nScope handle
        @param ch
            channel number to set on or off
        @param channelLevel
            the desired level of the channel
    */
    NSCOPE_API ErrorType nScope_set_ChX_level(ScopeHandle nScope, int ch, double channelLevel);

    /** @brief Get the level of a given channel

        @returns
            the current level of the given channel
        @param nScope
            pointer to nScope handle
        @param ch
            channel number to query
    */
    NSCOPE_API ErrorType nScope_get_ChX_level(ScopeHandle nScope, int ch, double* channelLevel);

  // NSCOPE_API ErrorType nScope_set_ch1_range(ScopeHandle nScope, double inputMin, double inputMax);
  // NSCOPE_API ErrorType nScope_get_ch1_input_min(ScopeHandle nScope);
  // NSCOPE_API ErrorType nScope_get_ch1_input_max(ScopeHandle nScope);
  // NSCOPE_API ErrorType nScope_set_ch2_range(ScopeHandle nScope, double inputMin, double inputMax);
  // NSCOPE_API ErrorType nScope_get_ch2_input_min(ScopeHandle nScope);
  // NSCOPE_API ErrorType nScope_get_ch2_input_max(ScopeHandle nScope);
  // NSCOPE_API ErrorType nScope_set_ch3_range(ScopeHandle nScope, double inputMin, double inputMax);
  // NSCOPE_API ErrorType nScope_get_ch3_input_min(ScopeHandle nScope);
  // NSCOPE_API ErrorType nScope_get_ch3_input_max(ScopeHandle nScope);
  // NSCOPE_API ErrorType nScope_set_ch4_range(ScopeHandle nScope, double inputMin, double inputMax);
  // NSCOPE_API ErrorType nScope_get_ch4_input_min(ScopeHandle nScope);
  // NSCOPE_API ErrorType nScope_get_ch4_input_max(ScopeHandle nScope);


#ifdef __cplusplus
}
#endif

#endif
