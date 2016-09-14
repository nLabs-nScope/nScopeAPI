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

    NSCOPE_API ErrorType nScope_set_AX_on(ScopeHandle nScope, int aChannel, bool aOn);
    NSCOPE_API ErrorType nScope_get_AX_on(ScopeHandle nScope, int aChannel, bool* aOn);

    NSCOPE_API ErrorType nScope_set_AX_frequency_in_hz(ScopeHandle nScope, int aChannel, double frequency);
    NSCOPE_API ErrorType nScope_get_AX_frequency_in_hz(ScopeHandle nScope, int aChannel, double* frequency);

    NSCOPE_API ErrorType nScope_set_AX_wave_type(ScopeHandle nScope, int aChannel, WaveType wave);
    NSCOPE_API ErrorType nScope_get_AX_wave_type(ScopeHandle nScope, int aChannel, WaveType* wave);

    NSCOPE_API ErrorType nScope_set_AX_unipolar(ScopeHandle nScope, int aChannel, bool isUnipolar);
    NSCOPE_API ErrorType nScope_get_AX_unipolar(ScopeHandle nScope, int aChannel, bool* isUnipolar);

    NSCOPE_API ErrorType nScope_set_AX_amplitude(ScopeHandle nScope, int aChannel, double amplitude);
    NSCOPE_API ErrorType nScope_get_AX_amplitude(ScopeHandle nScope, int aChannel, double* amplitude);

#ifdef __cplusplus
}
#endif

#endif
