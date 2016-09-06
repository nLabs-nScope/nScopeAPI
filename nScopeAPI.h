/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file


 */

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
	typedef struct scopeDev_ scopeHandle; /**< nScope structure handle */

	struct request_;
	typedef struct request_ request;


     /**< Power state of nScope */
    typedef enum PowerState
    {
        power_off =     0,  /**< power is off */
        power_on =      1,  /**< power is on */
        shorted =       2,  /**< a short has been detected */
        overcurrent =   3   /**< an overcurrent has been detected */
    } PowerState;


	/** @brief Open a connected nScope device and initialize it.

        Looks for a nScope device, connects to it, then runs nScope_initialize()

		@returns
			a pointer to a #scopeHandle object on success or NULL on failure.
        @param powerOn
            if powerOn is non-zero, nScope will turn on when this function successfully returns
	*/
	scopeHandle* NSCOPE_API_EXPORT_CALL nScope_open(int powerOn);

    /** @brief Close and clean a connected nScope device.

        @param nScope_p
            pointer to a pointer to #scopeHandle object to close
    */
	void NSCOPE_API_EXPORT_CALL nScope_close(scopeHandle** nScope_p);

    /** @brief Clean up an nScope device.

        This function cleans the memory that was used for an nScope object. This function
        is called by nScope_close(), so it is only needed when nScope is disconnected for an
        unknown reason.

        @param nScope_p
            pointer to a pointer to #scopeHandle object to clean
    */
    void NSCOPE_API_EXPORT_CALL nScope_clean(scopeHandle** nScope_p);

    /** @brief Initialize an nScope with the default configuration.

        This function is called by nScope_open(), so it's only needed to reset
        the configuration if it ever reaches an unknown state.

        The default configuration is:


        @param nScope
        pointer to #scopeHandle object to initialize
    */
	void NSCOPE_API_EXPORT_CALL nScope_initialize(scopeHandle* nScope);

    /** @brief Read how much power is being used by nScope

        @returns
        the power (in watts) used by nScope at the time the function is called

        @param nScope
        pointer to #scopeHandle object
    */
    double NSCOPE_API_EXPORT_CALL nScope_get_power_usage(scopeHandle* nScope);

    /** @brief Read how much power is being used by nScope

        @returns
        the #PowerState of the nScope

        @param nScope
        pointer to #scopeHandle object
    */
    PowerState NSCOPE_API_EXPORT_CALL nScope_get_power_state(scopeHandle* nScope);

    /** @brief find the firmware loader

        @returns
        1 for success, -1 for failure
    */
    int NSCOPE_API_EXPORT_CALL nScope_find_firmware_loader();

    /** @brief write the firmware to the loader

        @returns
        1 for success, -1 for failure
    */
    int NSCOPE_API_EXPORT_CALL nScope_write_to_loader();

    /** @brief load the nScope with current firmware

        calls both nScope_find_firmware_loader() and nScope_write_to_loader()

        @returns
        1 for success, -1 for failure
    */
    int NSCOPE_API_EXPORT_CALL nScope_load_firmware();

    /** @brief check the version of this API

        @returns
        the version of nScopeAPI
    */
    double NSCOPE_API_EXPORT_CALL nScope_check_API_version();

    /** @brief check the version of the connected firmware

        @returns
        the version of the firmware on the connected nScope
    */
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
