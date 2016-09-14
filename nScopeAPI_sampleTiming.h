/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file

    @brief contains function headers for controlling the nScope sample timing
*/

#ifndef NSCOPEAPI_SAMPLETIMING_H__
#define NSCOPEAPI_SAMPLETIMING_H__


#ifdef __cplusplus
extern "C" {
#endif

    NSCOPE_API ErrorType nScope_set_sample_rate_in_hz(ScopeHandle nScope, double sample_hz);
    NSCOPE_API ErrorType nScope_get_sample_rate_in_hz(ScopeHandle nScope, double* sample_hz);
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_seconds(ScopeHandle nScope, double sample_time_seconds);
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_seconds(ScopeHandle nScope, double* sample_time_seconds);
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_minutes(ScopeHandle nScope, double sample_time_minutes);
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_minutes(ScopeHandle nScope, double* sample_time_minutes);
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_ms(ScopeHandle nScope, double sample_time_ms);
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_ms(ScopeHandle nScope, double* sample_time_ms);
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_us(ScopeHandle nScope, double sample_time_us);
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_us(ScopeHandle nScope, double* sample_time_us);

#ifdef __cplusplus
}
#endif

#endif
