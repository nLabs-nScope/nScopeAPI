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

    /** @brief set the sample rate

        Sets the scope sample rate in Hz

        Not all sample rates can be acheived, nScope will automatically choose the closest approximation

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [in] sample_hz
            desired sample rate in Hz
    */
    NSCOPE_API ErrorType nScope_set_sample_rate_in_hz(ScopeHandle nScope, double sample_hz);

    /** @brief get the sample rate

        Gets the scope sample rate in Hz, stores it in sample_hz

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [out] sample_hz
            pointer to double to store actual sample rate in Hz
    */
    NSCOPE_API ErrorType nScope_get_sample_rate_in_hz(ScopeHandle nScope, double* sample_hz);

    /** @brief set the time between samples in seconds

        Not all sample rates can be acheived, nScope will automatically choose the closest approximation

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [in] sample_time_seconds
            desired time between samples in seconds
    */
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_seconds(ScopeHandle nScope, double sample_time_seconds);

    /** @brief get the time between samples in seconds

        Gets the time between samples in seconds, stores it in sample_time_seconds

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [out] sample_time_seconds
            pointer to double to store actual time between samples
    */
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_seconds(ScopeHandle nScope, double* sample_time_seconds);

    /** @brief set the time between samples in minutes

        Not all sample rates can be acheived, nScope will automatically choose the closest approximation

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [in] sample_time_minutes
            desired time between samples in minutes
    */
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_minutes(ScopeHandle nScope, double sample_time_minutes);

    /** @brief get the time between samples in minutes

        Gets the time between samples in minutes, stores it in sample_time_minutes

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [out] sample_time_minutes
            pointer to double to store actual time between samples
    */
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_minutes(ScopeHandle nScope, double* sample_time_minutes);

    /** @brief set the time between samples in milliseconds

        Not all sample rates can be acheived, nScope will automatically choose the closest approximation

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [in] sample_time_ms
            desired time between samples in milliseconds
    */
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_ms(ScopeHandle nScope, double sample_time_ms);

    /** @brief get the time between samples in milliseconds

        Gets the time between samples in milliseconds, stores it in sample_time_ms

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [out] sample_time_ms
            pointer to double to store actual time between samples
    */
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_ms(ScopeHandle nScope, double* sample_time_ms);

    /** @brief set the time between samples in microseconds

        Not all sample rates can be acheived, nScope will automatically choose the closest approximation

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [in] sample_time_us
            desired time between samples in microseconds
    */
    NSCOPE_API ErrorType nScope_set_time_between_samples_in_us(ScopeHandle nScope, double sample_time_us);

    /** @brief get the time between samples in microseconds

        Gets the time between samples in microseconds, stores it in sample_time_us

        @returns
            #ErrorType
        @param [in] nScope
            #ScopeHandle object
        @param [out] sample_time_us
            pointer to double to store actual time between samples
    */
    NSCOPE_API ErrorType nScope_get_time_between_samples_in_us(ScopeHandle nScope, double* sample_time_us);

#ifdef __cplusplus
}
#endif

#endif
