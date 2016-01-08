/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

#ifndef NSCOPEAPI_TRIGGER_H__
#define NSCOPEAPI_TRIGGER_H__

#ifdef __cplusplus
extern "C" {
#endif

#define RISING_EDGE  2
#define FALLING_EDGE 1


  int NSCOPE_API_EXPORT_CALL nScope_set_trigger_on(scopeHandle *nScope, int triggerOn);
  int NSCOPE_API_EXPORT_CALL nScope_get_trigger_on(scopeHandle *nScope);

  int NSCOPE_API_EXPORT_CALL nScope_set_trigger_source(scopeHandle *nScope, int triggerSource);
  int NSCOPE_API_EXPORT_CALL nScope_get_trigger_source(scopeHandle *nScope);

  int NSCOPE_API_EXPORT_CALL nScope_set_trigger_edge(scopeHandle *nScope, int triggerEdge);
  int NSCOPE_API_EXPORT_CALL nScope_get_trigger_edge(scopeHandle *nScope);

  double NSCOPE_API_EXPORT_CALL nScope_set_trigger_level(scopeHandle *nScope, double triggerLevel);
  double NSCOPE_API_EXPORT_CALL nScope_get_trigger_level(scopeHandle *nScope);

  double NSCOPE_API_EXPORT_CALL nScope_set_trigger_delay_ms(scopeHandle *nScope, double triggerDelay);
  double NSCOPE_API_EXPORT_CALL nScope_get_trigger_delay_ms(scopeHandle *nScope);

  double NSCOPE_API_EXPORT_CALL nScope_set_trigger_delay_us(scopeHandle *nScope, double triggerDelay);
  double NSCOPE_API_EXPORT_CALL nScope_get_trigger_delay_us(scopeHandle *nScope);

#ifdef __cplusplus
}
#endif

#endif
