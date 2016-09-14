/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file

    @brief contains function headers for making requests to nScope
*/

#ifndef NSCOPEAPI_REQUESTS_H__
#define NSCOPEAPI_REQUESTS_H__


#ifdef __cplusplus
extern "C" {
#endif

	NSCOPE_API ErrorType nScope_request_data(ScopeHandle nScope, Request newRequest, int numSamples, int antiAliased);
	NSCOPE_API ErrorType nScope_request_data_stream(ScopeHandle nScope, Request newRequest);
    NSCOPE_API ErrorType nScope_stop_request(ScopeHandle nScope, Request reqHandle);
    NSCOPE_API ErrorType nScope_release_request(ScopeHandle nScope, Request reqHandle);
    NSCOPE_API ErrorType nScope_wait_for_request_finish(ScopeHandle nScope,Request reqHandle);
    NSCOPE_API ErrorType nScope_request_xfer_has_completed(ScopeHandle nScope, Request reqHandle, bool* hasCompleted);
    NSCOPE_API ErrorType nScope_request_xfer_samples_remaining(ScopeHandle nScope, Request reqHandle);
    NSCOPE_API ErrorType nScope_stop_data_stream(ScopeHandle nScope, Request reqHandle);
    NSCOPE_API ErrorType nScope_read_data(ScopeHandle nScope, Request reqHandle, int channel, double* data);
	NSCOPE_API ErrorType nScope_request_has_data(ScopeHandle nScope, Request reqHandle, bool* hasData);

#ifdef __cplusplus
}
#endif


#endif
