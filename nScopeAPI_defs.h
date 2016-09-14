/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 9/10/2016

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file nScopeAPI_defs.h

    @brief header file for common definitions
*/

#ifndef NSCOPEAPI_DEFS_H__
#define NSCOPEAPI_DEFS_H__

    #ifdef _WIN32
       #define NSCOPE_API_EXPORT __declspec(dllexport)
       #define NSCOPE_API_CALL //__declspec(dllimport)
    #else
       #define NSCOPE_API_EXPORT /**< API export macro */
       #define NSCOPE_API_CALL /**< API call macro */
    #endif

    #define NSCOPE_API NSCOPE_API_EXPORT NSCOPE_API_CALL /**< API export and call macro*/

    /** nScope error types

        return type for all nScopeAPI functions

     */
    typedef enum
    {
        /** No error was encountered */
        SUCCESS =                  0,
        /** An unknown error occurred */
        UNKNOWN_ERROR =             -100,
        /** nScope is not open, or has been disconnected unexpectedly */
        NSCOPE_NOT_OPEN =           -101,
        /** the desired channel is currently off */
        NSCOPE_CHANNEL_OFF =        -102,
        /** nScope power is off */
        NSCOPE_POWER_OFF =          -103,
        /** There is no data available */
        NO_DATA_AVAILABLE =         -104,
        /** The trigger settings are invalid */
        INVALID_TRIGGER =           -105,
        /** The request is invalid */
        INVALID_REQUEST =           -106,
        /** A communication error has occurred */
        COMM_ERROR =                -107,
        /** TODO: no clue */
        INTERRUPT_STOPPED =         -108,
        /** Firmware and API are incompatible */
        FW_API_INCOMPATIBLE =       -109,
        /** Value error: a parameter is too small */
        VALUE_ERROR_TOO_SMALL =     -110,
        /** Value error: a parameter is too large */
        VALUE_ERROR_TOO_LARGE =     -111,
        /** Value error: a parameter is out of range */
        VALUE_ERROR_OUT_OF_RANGE =  -112,
        /** Value warning: a parameter is very small */
        VALUE_WARNING_TOO_SMALL =   -120,
        /** Value warning: a parameter is very large */
        VALUE_WARNING_TOO_LARGE =   -121,
    } ErrorType;

    /** Trigger edges of nScope */
    typedef enum
    {
        FALLING_EDGE =    1,  /**< trigger on the falling edge */
        RISING_EDGE =     2,  /**< trigger on the rising edge */
    } TriggerEdge;

    /** Power state of nScope */
    typedef enum
    {
        POWER_OFF =     0,  /**< power is off */
        POWER_ON =      1,  /**< power is on */
        SHORTED =       2,  /**< a short has been detected */
        OVERCURRENT =   3   /**< an overcurrent has been detected */
    } PowerState;

    /** Wave Types of nScope */
    typedef enum
    {
        SINE_WAVE =     0, /**< analog output is a sine wave */
        TRIANGLE_WAVE = 1, /**< analog output is a triangle wave */
    } WaveType;

#endif
