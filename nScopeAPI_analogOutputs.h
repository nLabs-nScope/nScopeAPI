/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope.

 David Meyer

 10/23/2014

 Copyright 2015 nLabs, All Rights Reserved.

********************************************************/

#ifndef NSCOPEAPI_ANALOGOUTPUTS_H__
#define NSCOPEAPI_ANALOGOUTPUTS_H__


#define SINE_WAVE       0
#define TRIANGLE_WAVE   1

#ifdef __cplusplus
extern "C" {
#endif

  double NSCOPE_API_EXPORT_CALL nScope_set_A1_frequency_in_hz(scopeHandle *nScope, double frequency);
  double NSCOPE_API_EXPORT_CALL nScope_get_A1_frequency_in_hz(scopeHandle *nScope);
  double NSCOPE_API_EXPORT_CALL nScope_set_A2_frequency_in_hz(scopeHandle *nScope, double frequency);
  double NSCOPE_API_EXPORT_CALL nScope_get_A2_frequency_in_hz(scopeHandle *nScope);

  int NSCOPE_API_EXPORT_CALL nScope_set_A1_wave_type(scopeHandle *nScope, int wave);
  int NSCOPE_API_EXPORT_CALL nScope_get_A1_wave_type(scopeHandle *nScope);
  int NSCOPE_API_EXPORT_CALL nScope_set_A2_wave_type(scopeHandle *nScope, int wave);
  int NSCOPE_API_EXPORT_CALL nScope_get_A2_wave_type(scopeHandle *nScope);

  int NSCOPE_API_EXPORT_CALL nScope_set_A1_on(scopeHandle *nScope, int aoOn);
  int NSCOPE_API_EXPORT_CALL nScope_get_A1_on(scopeHandle *nScope);
  int NSCOPE_API_EXPORT_CALL nScope_set_A2_on(scopeHandle *nScope, int aoOn);
  int NSCOPE_API_EXPORT_CALL nScope_get_A2_on(scopeHandle *nScope);

  int NSCOPE_API_EXPORT_CALL nScope_set_A1_unipolar(scopeHandle *nScope, int unipolar);
  int NSCOPE_API_EXPORT_CALL nScope_get_A1_unipolar(scopeHandle *nScope);
  int NSCOPE_API_EXPORT_CALL nScope_set_A2_unipolar(scopeHandle *nScope, int unipolar);
  int NSCOPE_API_EXPORT_CALL nScope_get_A2_unipolar(scopeHandle *nScope);

  double NSCOPE_API_EXPORT_CALL nScope_set_A1_amplitude(scopeHandle *nScope, double amplitude);
  double NSCOPE_API_EXPORT_CALL nScope_get_A1_amplitude(scopeHandle *nScope);
  double NSCOPE_API_EXPORT_CALL nScope_set_A2_amplitude(scopeHandle *nScope, double amplitude);
  double NSCOPE_API_EXPORT_CALL nScope_get_A2_amplitude(scopeHandle *nScope);

#ifdef __cplusplus
}
#endif

#endif
