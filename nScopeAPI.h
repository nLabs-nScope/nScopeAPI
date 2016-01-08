/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

#ifndef NSCOPEAPI_H__
#define NSCOPEAPI_H__


#ifdef _WIN32
      #define NSCOPE_API_EXPORT __declspec(dllexport)
      #define NSCOPE_API_CALL //__declspec(dllimport)
#else
      #define NSCOPE_API_EXPORT /**< API export macro */
      #define NSCOPE_API_CALL /**< API call macro */
#endif

#define NSCOPE_API_EXPORT_CALL NSCOPE_API_EXPORT NSCOPE_API_CALL /**< API export and call macro*/


#ifdef __cplusplus
extern "C" {
#endif

	struct scopeDev_;
	typedef struct scopeDev_ scopeHandle; /* opaque nScope structure */

	struct request_;
	typedef struct request_ request;

	/** @brief Open a connected nScope device.

		@returns
			This function returns a pointer to a #scopeHandle object on
			success or NULL on failure.
	*/
	NSCOPE_API_EXPORT_CALL scopeHandle* nScope_open(int powerOn);
	void NSCOPE_API_EXPORT_CALL nScope_close(scopeHandle** nScope_p);
    void NSCOPE_API_EXPORT_CALL nScope_clean(scopeHandle** nScope_p);
	void NSCOPE_API_EXPORT_CALL nScope_initialize(scopeHandle* nScope);
    double NSCOPE_API_EXPORT_CALL nScope_get_power_usage(scopeHandle* nScope);
    int NSCOPE_API_EXPORT_CALL nScope_get_power_state(scopeHandle* nScope);
    int NSCOPE_API_EXPORT_CALL nScope_find_firmware_loader();
    int NSCOPE_API_EXPORT_CALL nScope_write_to_loader();
    int NSCOPE_API_EXPORT_CALL nScope_load_firmware();

    double NSCOPE_API_EXPORT_CALL nScope_check_API_version();
    double NSCOPE_API_EXPORT_CALL nScope_check_FW_version();

    #include "nScopeAPI_requests.h"
    #include "nScopeAPI_analogInputs.h"
    #include "nScopeAPI_sampleTiming.h"
    #include "nScopeAPI_trigger.h"
    #include "nScopeAPI_analogOutputs.h"
    #include "nScopeAPI_pulseGenerators.h"


#ifdef __cplusplus
}
#endif

#endif
