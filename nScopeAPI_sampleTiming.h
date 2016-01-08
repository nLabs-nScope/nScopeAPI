/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

#ifndef NSCOPEAPI_SAMPLETIMING_H__
#define NSCOPEAPI_SAMPLETIMING_H__


#ifdef __cplusplus
extern "C" {
#endif

  double NSCOPE_API_EXPORT_CALL nScope_set_sample_rate_in_hz(scopeHandle *nScope, double sample_hz);
  double NSCOPE_API_EXPORT_CALL nScope_get_sample_rate_in_hz(scopeHandle *nScope);
  double NSCOPE_API_EXPORT_CALL nScope_set_time_between_samples_in_seconds(scopeHandle *nScope, double sample_time_seconds);
  double NSCOPE_API_EXPORT_CALL nScope_get_time_between_samples_in_seconds(scopeHandle *nScope);
  double NSCOPE_API_EXPORT_CALL nScope_set_time_between_samples_in_minutes(scopeHandle *nScope, double sample_time_minutes);
  double NSCOPE_API_EXPORT_CALL nScope_get_time_between_samples_in_minutes(scopeHandle *nScope);
  double NSCOPE_API_EXPORT_CALL nScope_set_time_between_samples_in_ms(scopeHandle *nScope, double sample_time_ms);
  double NSCOPE_API_EXPORT_CALL nScope_get_time_between_samples_in_ms(scopeHandle *nScope);
  double NSCOPE_API_EXPORT_CALL nScope_set_time_between_samples_in_us(scopeHandle *nScope, double sample_time_us);
  double NSCOPE_API_EXPORT_CALL nScope_get_time_between_samples_in_us(scopeHandle *nScope);

#ifdef __cplusplus
}
#endif

#endif
