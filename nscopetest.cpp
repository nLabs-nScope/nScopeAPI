/*******************************************************
 nScopeAPI - Multi-Platform library for
 communication with nScope devices.

 David Meyer

 10/23/2014

 Copyright 2014, All Rights Reserved.

********************************************************/

#include "nscopeapi.h"
#include <cstdio>
#include <stdlib.h>

// Headers needed for sleeping.
#ifdef _WIN32
	#include <windows.h>
#else
	#include <unistd.h>
#endif


int main(int argc, char* argv[])
{
//	scopeHandle* handle = NULL;


#ifdef WIN32
	UNREFERENCED_PARAMETER(argc);
	UNREFERENCED_PARAMETER(argv);
#endif

	printf("API Version: %2.1f\n",nScope_check_API_version());
	nScope_load_firmware();
	// printf("FW Version: %2.1f\n",nScope_check_FW_version());




	// handle = nScope_open(1);
	// if(!handle){
	// 	printf("failed to connect\n");
	// } else {
	// 	//printf("success\n");
	//
	// 	nScope_set_A1_frequency_in_hz(handle,0.2);
	// 	nScope_set_A1_wave_type(handle,0);
	// 	nScope_set_A1_unipolar(handle,1);
	// 	nScope_set_A1_amplitude(handle,4);
	// 	nScope_set_A1_on(handle,1);
	//
	//
	// 	nScope_set_A2_frequency_in_hz(handle,1);
	// 	nScope_set_A2_wave_type(handle,1);
	// 	nScope_set_A2_unipolar(handle,0);
	// 	nScope_set_A2_amplitude(handle,1);
	// 	nScope_set_A2_on(handle,1);
	//
	//
	//
	// 	nScope_set_P1_frequency_in_hz(handle,2);
	// 	nScope_set_P1_duty_percentage(handle,3);
	// 	nScope_set_P2_frequency_in_hz(handle,1.5);
	// 	nScope_set_P2_duty_percentage(handle,50);
	//
	// 	nScope_set_P1_on(handle,1);
	// 	nScope_set_P2_on(handle,1);
	//
	// 	nScope_set_ch1_on(handle,1);
	// 	nScope_set_sample_rate_in_hz(handle,1);
	// 	request* req = nScope_request_data(handle,10,0);
	// 	while(nScope_request_has_data(handle, req)){
	// 		printf("Check: %d\n",nScope_request_has_data(handle, req));
	// 		printf("Ch: %2.2f\n",nScope_read_data(handle,req,1));
	// 		printf("Ch: %2.2f\n",nScope_read_data(handle,req,2));
	// 		printf("Ch: %2.2f\n",nScope_read_data(handle,req,3));
	// 		printf("Ch: %2.2f\n",nScope_read_data(handle,req,4));
	// 	}
	// 	printf("First Check: %d\n",nScope_request_has_data(handle, req));
	// 	printf("Second Check: %d\n",nScope_request_has_data(handle, req));
	// 	nScope_release_request(handle,req);
	// 	printf("Third Check: %d\n",nScope_request_has_data(handle, req));
	//
	//
	// 	nScope_close(handle);
	// }


#ifdef WIN32
	system("pause");
#endif

	return 0;
}
