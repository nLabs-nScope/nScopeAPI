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

	/** @brief Request data from nScope

		Creates a request for data from nScope.
		Anti-aliasing algorithm is used for nScope GUI, not recommended for data acquisition


		@returns
			#ErrorType
		@param [in] nScope
			#ScopeHandle object
		@param [out] newRequest_p
			pointer to a #Request object to store the request handle
		@param [in] numSamples
			number of data samples (per channel) to request
		@param [in] antiAliased
			true: turn on anti-aliasing, false: turn it off.
	*/
	NSCOPE_API ErrorType nScope_request_data(ScopeHandle nScope, Request* newRequest_p, int numSamples, bool antiAliased);

	/** @brief Request an infinite stream of data from nScope

		@warning not yet implemented

	*/
	NSCOPE_API ErrorType nScope_request_data_stream(ScopeHandle nScope, Request* newRequest_p);

	/** @brief stop a request that is in progress

		interrupts a current request from completing

		@returns
			#ErrorType
		@param [in] nScope
			#ScopeHandle object
		@param [in] reqHandle
			#Request object to stop
	*/
    NSCOPE_API ErrorType nScope_stop_request(ScopeHandle nScope, Request reqHandle);

	/** @brief release a request that is finished or stopped

		Frees the memory for the request.

		To prevent memory leaks, the developer must call this function after
		the request has finished an all data has been read.

		On success, the #Request handle will be a null pointer

		@returns
			#ErrorType
		@param [in] nScope
			#ScopeHandle object
		@param [out] reqHandle_p
			pointer to #Request object to release
	*/
    NSCOPE_API ErrorType nScope_release_request(ScopeHandle nScope, Request* reqHandle_p);

	/** @brief wait for a request to finish

		Blocks program execution until a request has finished transferring data from nScope

		@returns
			#ErrorType
		@param [in] nScope
			#ScopeHandle object
		@param [in] reqHandle
			#Request object to wait for
	*/
    NSCOPE_API ErrorType nScope_wait_for_request_finish(ScopeHandle nScope,Request reqHandle);

	/** @brief determine if a request has completed the transfer

		Queries a request to see if the data has finished transferring, stores the result in
		hasCompleted

		@returns
			#ErrorType
		@param [in] nScope
			#ScopeHandle object
		@param [in] reqHandle
			#Request object to query
		@param [out] hasCompleted
			pointer to bool to store the result of the query
	*/
    NSCOPE_API ErrorType nScope_request_xfer_has_completed(ScopeHandle nScope, Request reqHandle, bool* hasCompleted);

	/** @brief query the number of samples remaining in the request transfer

		@warning not yet implemented

	*/
    NSCOPE_API ErrorType nScope_request_xfer_samples_remaining(ScopeHandle nScope, Request reqHandle);

	/** @brief Stop an infinite stream of data from nScope

		@warning not yet implemented

	*/
    NSCOPE_API ErrorType nScope_stop_data_stream(ScopeHandle nScope, Request reqHandle);

	/** @brief Read data from the request

		reads data from a specific channel on a request, and stores the result in data

		@returns
			#ErrorType
		@param [in] nScope
			#ScopeHandle object
		@param [in] reqHandle
			#Request object to query
		@param [in] channel
			channel to read
		@param [out] data
			pointer to double to store the read value on the request
	*/
    NSCOPE_API ErrorType nScope_read_data(ScopeHandle nScope, Request reqHandle, int channel, double* data);

	/** @brief determine if a request has unread data still stored in it

		Queries a request to see if there is still data to be read, stores the result in
		hasData

		@returns
			#ErrorType
		@param [in] nScope
			#ScopeHandle object
		@param [in] reqHandle
			#Request object to query
		@param [out] hasData
			pointer to bool to store the result of the query
	*/
	NSCOPE_API ErrorType nScope_request_has_data(ScopeHandle nScope, Request reqHandle, bool* hasData);

#ifdef __cplusplus
}
#endif


#endif
