/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

#ifndef NSCOPEAPI_REQUESTS_H__
#define NSCOPEAPI_REQUESTS_H__


#ifdef __cplusplus
extern "C" {
#endif

	NSCOPE_API_EXPORT_CALL request* nScope_request_data(scopeHandle *nScope, int numSamples, int antiAliased);
	NSCOPE_API_EXPORT_CALL request* nScope_request_data_stream(scopeHandle *nScope);
    int NSCOPE_API_EXPORT_CALL nScope_stop_request(scopeHandle* nScope, request* reqHandle);
    int NSCOPE_API_EXPORT_CALL nScope_release_request(scopeHandle* nScope, request** reqHandle_p);
    int NSCOPE_API_EXPORT_CALL nScope_wait_for_request_finish(scopeHandle* nScope,request *reqHandle);
    int NSCOPE_API_EXPORT_CALL nScope_request_xfer_has_completed(scopeHandle* nScope,request* reqHandle);
    int NSCOPE_API_EXPORT_CALL nScope_request_xfer_samples_remaining(scopeHandle* nScope,request * reqHandle);
    int NSCOPE_API_EXPORT_CALL nScope_stop_data_stream(scopeHandle* nScope,request* reqHandle);
    double NSCOPE_API_EXPORT_CALL nScope_read_data(scopeHandle* nScope,request** reqHandle, int channel);
    int NSCOPE_API_EXPORT_CALL nScope_request_has_data(scopeHandle* nScope,request** reqHandle_p);

#ifdef __cplusplus
}
#endif


#endif
