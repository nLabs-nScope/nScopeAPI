#include <node_api.h>
#include "nScopeAPI.h"

napi_value MyFunction(napi_env env, napi_callback_info info) {
    napi_status status;
    size_t argc = 1;
    int number = 0;
    ErrorType ns_status;
    double api,fw;
    napi_value argv[1];

    status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Failed to parse arguments");
    }

    status = napi_get_value_int32(env, argv[0], &number);

    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Invalid number was passed as argument");
    }
    napi_value myNumber;
    ns_status = nScope_check_API_version(&api);
    // ns_status = nScope_check_FW_version(&fw);






    
    if(ns_status == SUCCESS)
    {
        status = napi_create_double(env, api, &myNumber);

        if (status != napi_ok) {
            napi_throw_error(env, NULL, "Unable to create return value");
        }
    }
    else
    {
        status = napi_create_double(env, ns_status, &myNumber);

        if (status != napi_ok) {
            napi_throw_error(env, NULL, "Unable to create return value");
        }
    }

    return myNumber;
}

napi_value Init(napi_env env, napi_value exports) {
    napi_status status;
    napi_value fn;

    status = napi_create_function(env, NULL, 0, MyFunction, NULL, &fn);
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to wrap native function");
    }

    status = napi_set_named_property(env, exports, "my_function", fn);
    
    if (status != napi_ok) {
        napi_throw_error(env, NULL, "Unable to populate exports");
    }

    return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)
