/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

/** @file

    @brief contains function headers for controlling the nScope trigger function
*/

#ifndef NSCOPEAPI_TRIGGER_H__
#define NSCOPEAPI_TRIGGER_H__

#ifdef __cplusplus
extern "C" {
#endif


    /** @brief Set the trigger on/off state

        A true state means the triggering on and will trigger on the current
        source, level, and edge state.

        @returns
			nScope ::ErrorType
        @param [in] nScope
            nScope handle
        @param [in] triggerOn
            true: set the trigger on, false: turn it off
    */
    NSCOPE_API ErrorType nScope_set_trigger_on(ScopeHandle nScope, bool triggerOn);

    /** @brief Get the trigger on/off state

        A true state means the triggering on and will trigger on the current
        source, level, and edge state.

        @returns
			nScope ::ErrorType
        @param [in] nScope
            nScope handle
        @param [out] triggerOn
            pointer to variable to store the state of the trigger
    */
    NSCOPE_API ErrorType nScope_get_trigger_on(ScopeHandle nScope, bool* triggerOn);

    /** @brief Set the trigger source channel

        The trigger source is the channel that is used to trigger a sweep.

        @returns
			nScope ::ErrorType
        @param [in] nScope
            nScope handle
        @param [in] triggerSource
            number 1-4 specifying the trigger channel
    */
    NSCOPE_API ErrorType nScope_set_trigger_source(ScopeHandle nScope, int triggerSource);

    /** @brief Get the trigger source channel

        The trigger source is the channel that is used to trigger a sweep.

        @returns
			nScope ::ErrorType
        @param [in] nScope
            nScope handle
    */
    NSCOPE_API ErrorType nScope_get_trigger_source(ScopeHandle nScope, int* triggerSource);

    /** @brief Set the trigger edge condition

        The trigger edge condition specifies which edge (rising or falling) will
        trigger a sweep.

        @returns
			nScope ::ErrorType
        @param [in] nScope
            nScope handle
        @param triggerSource
            number 1-4 specifying the trigger channel
    */
    NSCOPE_API ErrorType nScope_set_trigger_edge(ScopeHandle nScope, TriggerEdge triggerEdge);

    /** @brief Get the trigger edge condition

        The trigger edge condition specifies which edge (rising or falling) will
        trigger a sweep.

        @returns
			nScope ::ErrorType
        @param [in] nScope
            nScope handle
    */
    NSCOPE_API ErrorType nScope_get_trigger_edge(ScopeHandle nScope, TriggerEdge* triggerEdge);

    NSCOPE_API ErrorType nScope_set_trigger_level(ScopeHandle nScope, double triggerLevel);
    NSCOPE_API ErrorType nScope_get_trigger_level(ScopeHandle nScope, double* triggerLevel);

    NSCOPE_API ErrorType nScope_set_trigger_delay_ms(ScopeHandle nScope, double triggerDelay);
    NSCOPE_API ErrorType nScope_get_trigger_delay_ms(ScopeHandle nScope, double* triggerDelay);

    NSCOPE_API ErrorType nScope_set_trigger_delay_us(ScopeHandle nScope, double triggerDelay);
    NSCOPE_API ErrorType nScope_get_trigger_delay_us(ScopeHandle nScope, double* triggerDelay);

#ifdef __cplusplus
}
#endif

#endif
