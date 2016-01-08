/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

#ifndef NSCOPEAPI_ANALOGINPUTS_H__
#define NSCOPEAPI_ANALOGINPUTS_H__



#ifdef __cplusplus
extern "C" {
#endif


    int NSCOPE_API_EXPORT_CALL nScope_set_channels_on(scopeHandle *nScope, int ch1on, int ch2on, int ch3on, int ch4on);
    int NSCOPE_API_EXPORT_CALL nScope_get_channels_on(scopeHandle *nScope, int* channelsOn);
    int NSCOPE_API_EXPORT_CALL nScope_get_num_channels_on(scopeHandle* nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_ch_on(scopeHandle* nScope, int ch, int channelOn);
    int NSCOPE_API_EXPORT_CALL nScope_get_ch_on(scopeHandle* nScope, int ch);
    int NSCOPE_API_EXPORT_CALL nScope_set_ch1_on(scopeHandle *nScope, int channelOn);
    int NSCOPE_API_EXPORT_CALL nScope_get_ch1_on(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_ch2_on(scopeHandle *nScope, int channelOn);
    int NSCOPE_API_EXPORT_CALL nScope_get_ch2_on(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_ch3_on(scopeHandle *nScope, int channelOn);
    int NSCOPE_API_EXPORT_CALL nScope_get_ch3_on(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_ch4_on(scopeHandle *nScope, int channelOn);
    int NSCOPE_API_EXPORT_CALL nScope_get_ch4_on(scopeHandle *nScope);

    double NSCOPE_API_EXPORT_CALL nScope_get_ch_gain(scopeHandle* nScope, int ch);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch_gain(scopeHandle* nScope, int ch, double channelGain);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch1_gain(scopeHandle *nScope, double channelGain);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch1_gain(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch2_gain(scopeHandle *nScope, double channelGain);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch2_gain(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch3_gain(scopeHandle *nScope, double channelGain);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch3_gain(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch4_gain(scopeHandle *nScope, double channelGain);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch4_gain(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_channel_gains(scopeHandle *nScope, double ch1Gain, double ch2Gain, double ch3Gain, double ch4Gain);
    int NSCOPE_API_EXPORT_CALL nScope_get_channel_gains(scopeHandle *nScope, double* channelGains);

    double NSCOPE_API_EXPORT_CALL nScope_get_ch_level(scopeHandle* nScope, int ch);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch_level(scopeHandle* nScope, int ch, double channelLevel);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch1_level(scopeHandle *nScope, double channelLevel);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch1_level(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch2_level(scopeHandle *nScope, double channelLevel);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch2_level(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch3_level(scopeHandle *nScope, double channelLevel);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch3_level(scopeHandle *nScope);
    double NSCOPE_API_EXPORT_CALL nScope_set_ch4_level(scopeHandle *nScope, double channelLevel);
    double NSCOPE_API_EXPORT_CALL nScope_get_ch4_level(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_set_channel_levels(scopeHandle *nScope, double ch1Level, double ch2Level, double ch3Level, double ch4Level);
    int NSCOPE_API_EXPORT_CALL nScope_get_channel_levels(scopeHandle *nScope, double* channelLevels);

  // double NSCOPE_API_EXPORT_CALL nScope_set_ch1_range(scopeHandle *nScope, double inputMin, double inputMax);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch1_input_min(scopeHandle *nScope);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch1_input_max(scopeHandle *nScope);
  // double NSCOPE_API_EXPORT_CALL nScope_set_ch2_range(scopeHandle *nScope, double inputMin, double inputMax);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch2_input_min(scopeHandle *nScope);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch2_input_max(scopeHandle *nScope);
  // double NSCOPE_API_EXPORT_CALL nScope_set_ch3_range(scopeHandle *nScope, double inputMin, double inputMax);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch3_input_min(scopeHandle *nScope);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch3_input_max(scopeHandle *nScope);
  // double NSCOPE_API_EXPORT_CALL nScope_set_ch4_range(scopeHandle *nScope, double inputMin, double inputMax);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch4_input_min(scopeHandle *nScope);
  // double NSCOPE_API_EXPORT_CALL nScope_get_ch4_input_max(scopeHandle *nScope);


#ifdef __cplusplus
}
#endif

#endif
