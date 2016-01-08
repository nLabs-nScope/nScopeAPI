
#include "mex.h"
#include "nScopeAPI.h"
#include "nScope.h"
#include <string.h>



static scopeHandle* nScope;
static request* currentRequest;

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{

    char cmd[64];
    if (nrhs < 1 || mxGetString(prhs[0], cmd, sizeof(cmd)))
    mexErrMsgTxt("first input should be a command string less than 64 characters long.");

    // Open connection to nScope
    if (!strcmp("open", cmd)) {
        if(nlhs!=0){
            mexErrMsgTxt(strcat(cmd,": no output required"));
        }
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            mexErrMsgTxt(strcat(cmd,": nScope already open"));
        } else {
            double APIver = nScope_check_API_version();
            double FWver = nScope_check_FW_version();
            int fwTryCount = 0;
            if((APIver != FWver && FWver > 0.0)){
                mexEvalString("disp('incorrect firmware detected, attempting to find firmware loader...')");
                while(nScope_find_firmware_loader()<0){
                    fwTryCount++;
                    if(fwTryCount == 5){
                        mexEvalString("disp('having trouble finding firmware loader. please unplug nScope and re-plug while holding button')");
                    }
                    if(fwTryCount == 30){
                        mexErrMsgTxt(strcat(cmd,": could not connect to firmware loader"));
                    }
                }
                mexEvalString("disp('connected to loader. Writing firmware to nScope, do NOT unplug')");
                fwTryCount = 0;
                while(nScope_write_to_loader() < 0){
                    fwTryCount++;
                    if(fwTryCount == 30){
                        mexErrMsgTxt(strcat(cmd,": could not load firmware"));
                    }
                }
                mexEvalString("disp('firmware update completed. please unplug and re-plug nScope')");
                nScope = nScope_open(mxGetScalar(prhs[1]));
                fwTryCount++;
                while(!nScope){
                    mexEvalString("pause(0.5);");
                    nScope = nScope_open(mxGetScalar(prhs[1]));
                    fwTryCount++;
                    if(fwTryCount == 30){
                        mexErrMsgTxt(strcat(cmd,": unable to connect to nScope"));
                    }
                }
                mexLock();
            } else {
                nScope = nScope_open(mxGetScalar(prhs[1]));
                if(!nScope){
                    mexErrMsgTxt(strcat(cmd,": unable to connect to nScope"));
                }
                mexLock();
            }
        }
        return;
    }

    // Close connection to nScope;
    if (!strcmp("close", cmd)) {
        if(nlhs!=0){
            mexErrMsgTxt(strcat(cmd,": no output required"));
        }
        if (nScope){
            nScope_close(&nScope);
            nScope = NULL;
            mexUnlock();
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    // check API Version
    if (!strcmp("checkAPIver", cmd)) {
        if(nrhs>1){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
        double* output = (double*)mxGetPr(plhs[0]);
        *output = nScope_check_API_version();
        return;
    }

    if (!strcmp("checkFWver", cmd)) {
        if(nrhs>1){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
        double* output = (double*)mxGetPr(plhs[0]);
        *output = nScope_check_FW_version();
        if(*output == -101){
            mexErrMsgTxt(strcat(cmd,": cannot connect to an nScope"));
        }
        return;
    }

    // Request Data from nScope
    if (!strcmp("requestData", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            if(currentRequest != NULL){
                nScope_release_request(nScope,&currentRequest);
                currentRequest = NULL;
            }
            currentRequest = nScope_request_data(nScope,mxGetScalar(prhs[1]),0);               
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    // Read Data from the request
    if (!strcmp("readData", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            if(currentRequest == NULL){
                mexWarnMsgTxt(strcat(cmd,": no request found"));
                *output = 0;
            } else {
                *output = nScope_read_data(nScope,&currentRequest,mxGetScalar(prhs[1]));
                if (*output == -102){
                    mexWarnMsgTxt("nScopeAPI:readData: nScope channel is off");
                }
                if (*output == -104){
                    mexWarnMsgTxt("nScopeAPI:readData: no more data is available");
                }
                if (*output == -112){
                    mexErrMsgTxt(strcat(cmd,": nScope channel does not exist"));
                }
                if (*output == -106){
                    mexErrMsgTxt(strcat(cmd,": invalid request"));
                }
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    // Check if request has data
    if (!strcmp("requestHasData", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            if(currentRequest == NULL){
                *output = 0;
                mexWarnMsgTxt(strcat(cmd,": no request found"));
            } else {
                *output = nScope_request_has_data(nScope,&currentRequest);
                if (*output == -106){
                    mexErrMsgTxt(strcat(cmd,": invalid request"));
                }
                if(*output == 0){
                    nScope_release_request(nScope,&currentRequest);
                    currentRequest = NULL;
                }
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }


/**********************
Analog Inputs
***********************/
{{{
    if (!strcmp("setChannelsOn", cmd)) {
        if(nrhs!=5){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            nScope_set_channels_on(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]),mxGetScalar(prhs[3]),mxGetScalar(prhs[4]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getChannelsOn", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,4,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            nScope_get_channels_on(nScope,output);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getNumChannelsOn", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_num_channels_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setChannelOn", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            int rtrn = nScope_set_ch_on(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if (rtrn == -112){
                mexErrMsgTxt(strcat(cmd,": nScope channel does not exist"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getChannelOn", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_ch_on(nScope,mxGetScalar(prhs[1]));
            if (*output == -112){
                mexErrMsgTxt(strcat(cmd,": nScope channel does not exist"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setCh1on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_ch1_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh1on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_ch1_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh2on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_ch2_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh2on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_ch2_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh3on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_ch3_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh3on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_ch3_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh4on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_ch4_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh4on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_ch4_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setChannelGains", cmd)) {
        if(nrhs!=5){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            int rtrn = nScope_set_channel_gains(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]),mxGetScalar(prhs[3]),mxGetScalar(prhs[4]));
            if(rtrn == -110){
                mexErrMsgTxt(strcat(cmd,": requested gain is too low"));
            }
            if(rtrn == -111){
                mexErrMsgTxt(strcat(cmd,": requested gain is too high"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getChannelGains", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,4,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            nScope_get_channel_gains(nScope,output);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setChannelGain", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            int rtrn = nScope_set_ch_gain(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if (rtrn == -112){
                mexErrMsgTxt(strcat(cmd,": nScope channel does not exist"));
            }
            if(rtrn == -110){
                mexErrMsgTxt(strcat(cmd,": requested gain is too low"));
            }
            if(rtrn == -111){
                mexErrMsgTxt(strcat(cmd,": requested gain is too high"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getChannelGain", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch_gain(nScope,mxGetScalar(prhs[1]));
            if (*output == -112){
                mexErrMsgTxt(strcat(cmd,": nScope channel does not exist"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setCh1gain", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch1_gain(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested gain is too low"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested gain is too high"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh1gain", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch1_gain(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh2gain", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch2_gain(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested gain is too low"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested gain is too high"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh2gain", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch2_gain(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh3gain", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch3_gain(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested gain is too low"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested gain is too high"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh3gain", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch3_gain(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh4gain", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch4_gain(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested gain is too low"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested gain is too high"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh4gain", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch4_gain(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setChannelLevels", cmd)) {
        if(nrhs!=5){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            int rtrn = nScope_set_channel_levels(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]),mxGetScalar(prhs[3]),mxGetScalar(prhs[4]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getChannelLevels", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,4,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            nScope_get_channel_levels(nScope,output);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setChannelLevel", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            int rtrn = nScope_set_ch_level(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if (rtrn == -112){
                mexErrMsgTxt(strcat(cmd,": nScope channel does not exist"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getChannelLevel", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": too many arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch_level(nScope,mxGetScalar(prhs[1]));
            if (*output == -112){
                mexErrMsgTxt(strcat(cmd,": nScope channel does not exist"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setCh1level", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch1_level(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh1level", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch1_level(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh2level", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch2_level(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh2level", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch2_level(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh3level", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch3_level(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh3level", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch3_level(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setCh4level", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>0){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_ch4_level(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getCh4level", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_ch4_level(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }


}}}


/**********************
Sample Timing
***********************/
{{{
    if (!strcmp("setSampleRateInHz", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_sample_rate_in_hz(nScope,mxGetScalar(prhs[1]));
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too fast"));
            }
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getSampleRateInHz", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_sample_rate_in_hz(nScope);
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setTimeBetweenSamplesInSeconds", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_time_between_samples_in_seconds(nScope,mxGetScalar(prhs[1]));
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too fast"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getTimeBetweenSamplesInSeconds", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_time_between_samples_in_seconds(nScope);
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setTimeBetweenSamplesInMinutes", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_time_between_samples_in_minutes(nScope,mxGetScalar(prhs[1]));
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too fast"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getTimeBetweenSamplesInMinutes", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_time_between_samples_in_minutes(nScope);
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setTimeBetweenSamplesInMs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_time_between_samples_in_ms(nScope,mxGetScalar(prhs[1]));
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too fast"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getTimeBetweenSamplesInMs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_time_between_samples_in_ms(nScope);
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setTimeBetweenSamplesInUs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_time_between_samples_in_us(nScope,mxGetScalar(prhs[1]));
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too fast"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested sample rate is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getTimeBetweenSamplesInUs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_time_between_samples_in_us(nScope);
            if(*output == -102){
                mexErrMsgTxt(strcat(cmd,": no scope channels are on"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

}}}


/**********************
 Pulse Generators
 **********************/
{{{

    if (!strcmp("setP1frequencyInHz", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P1_frequency_in_hz(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested frequency is too fast"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested frequecny is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP1frequencyInHz", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P1_frequency_in_hz(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setP2frequencyInHz", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P2_frequency_in_hz(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested frequency is too fast"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested frequecny is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP2frequencyInHz", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P2_frequency_in_hz(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setPulseFrequenciesInHz", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_pulse_frequencies_in_hz(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested frequency is too fast"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested frequecny is too slow"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setP1periodInMs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P1_period_in_ms(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested period is too short"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested period is too long"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP1periodInMs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P1_period_in_ms(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setP2periodInMs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P2_period_in_ms(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested period is too short"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested period is too long"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP2periodInMs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P2_period_in_ms(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setPulsePeriodsInMs", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_pulse_periods_in_ms(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested period is too short"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested period is too long"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setP1periodInUs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P1_period_in_us(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested period is too short"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested period is too long"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP1periodInUs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P1_period_in_us(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setP2periodInUs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P2_period_in_us(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested period is too short"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested period is too long"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP2periodInUs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P2_period_in_us(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setPulsePeriodsInUs", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_pulse_periods_in_us(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if(*output == -110){
                mexErrMsgTxt(strcat(cmd,": requested period is too short"));
            }
            if(*output == -111){
                mexErrMsgTxt(strcat(cmd,": requested period is too long"));
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setP1dutyPercentage", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P1_duty_percentage(nScope,mxGetScalar(prhs[1]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setP1dutyPercentage: requested duty results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setP1dutyPercentage: requested duty results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP1dutyPercentage", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P1_duty_percentage(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setP2dutyPercentage", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P2_duty_percentage(nScope,mxGetScalar(prhs[1]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setP2dutyPercentage: requested duty results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setP2dutyPercentage: requested duty results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP2dutyPercentage", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P2_duty_percentage(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setPulseDutyPercentages", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_pulse_duty_percentages(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setPulseDutyPercentages: requested duty results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setPulseDutyPercentages: requested duty results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setP1pulseWidthInMs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P1_pulse_width_in_ms(nScope,mxGetScalar(prhs[1]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setP1pulseWidthInMs: requested pulse width results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setP1pulseWidthInMs: requested pulse width results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP1pulseWidthInMs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P1_pulse_width_in_ms(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setP2pulseWidthInMs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P2_pulse_width_in_ms(nScope,mxGetScalar(prhs[1]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setP2pulseWidthInMs: requested pulse width results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setP2pulseWidthInMs: requested pulse width results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP2pulseWidthInMs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P2_pulse_width_in_ms(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setPulseWidthsInMs", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_pulse_widths_in_ms(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setPulseWidthsInMs: requested pulse width results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setPulseWidthsInMs: requested pulse width results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setP1pulseWidthInUs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P1_pulse_width_in_us(nScope,mxGetScalar(prhs[1]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setP1pulseWidthInUs: requested pulse width results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setP1pulseWidthInUs: requested pulse width results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP1pulseWidthInUs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P1_pulse_width_in_us(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setP2pulseWidthInUs", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_P2_pulse_width_in_us(nScope,mxGetScalar(prhs[1]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setP2pulseWidthInUs: requested pulse width results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setP2pulseWidthInUs: requested pulse width results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP2pulseWidthInUs", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_P2_pulse_width_in_us(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setPulseWidthsInUs", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_pulse_widths_in_us(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if(*output == -121){
                mexWarnMsgTxt("nScopeAPI:setPulseWidthsInUs: requested pulse width results in always high signal");
            }
            if(*output == -120){
                mexWarnMsgTxt("nScopeAPI:setPulseWidthsInUs: requested pulse width results in always low signal");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("sendP1pulse", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_send_P1_pulse(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexWarnMsgTxt("nScopeAPI:sendP1pulse: requested pulse is too short");
            }
            if(*output == -111){
                mexWarnMsgTxt("nScopeAPI:sendP1pulse: requested pulse is too long");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("sendP2pulse", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_send_P2_pulse(nScope,mxGetScalar(prhs[1]));
            if(*output == -110){
                mexWarnMsgTxt("nScopeAPI:sendP2pulse: requested pulse is too short");
            }
            if(*output == -111){
                mexWarnMsgTxt("nScopeAPI:sendP2pulse: requested pulse is too long");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("sendPulses", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateDoubleMatrix(1,1,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_send_pulses(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
            if(*output == -110){
                mexWarnMsgTxt("nScopeAPI:sendPulses: requested pulse is too short");
            }
            if(*output == -111){
                mexWarnMsgTxt("nScopeAPI:sendPulses: requested pulse is too long");
            }
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setP1on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_P1_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP1on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_P1_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setP2on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_P2_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getP2on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_P2_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("setPulseGeneratorsOn", cmd)) {
        if(nrhs!=3){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_pulse_generators_on(nScope,mxGetScalar(prhs[1]),mxGetScalar(prhs[2]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getPulseGeneratorsOn", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,2,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            nScope_get_pulse_generators_on(nScope,output);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
}}}

/**********************
 Analog Outputs
 **********************/

    if (!strcmp("setA1frequencyInHz", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_A1_frequency_in_hz(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA1frequencyInHz", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_A1_frequency_in_hz(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setA2frequencyInHz", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_A2_frequency_in_hz(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA2frequencyInHz", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_A2_frequency_in_hz(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setA1amplitude", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_A1_amplitude(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA1amplitude", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_A1_amplitude(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setA2amplitude", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_set_A2_amplitude(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA2amplitude", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxDOUBLE_CLASS,mxREAL);
            double* output = (double*)mxGetPr(plhs[0]);
            *output = nScope_get_A2_amplitude(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setA1on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_A1_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA1on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_A1_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setA2on", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_A2_on(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA2on", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_A2_on(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setA1unipolar", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_A1_unipolar(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA1unipolar", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_A1_unipolar(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    if (!strcmp("setA2unipolar", cmd)) {
        if(nrhs!=2){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_set_A2_unipolar(nScope,mxGetScalar(prhs[1]));
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }
    if (!strcmp("getA2unipolar", cmd)) {
        if(nrhs!=1){
            mexErrMsgTxt(strcat(cmd,": incorrect number of arguments"));
        }
        if(nlhs>1){
            mexErrMsgTxt(strcat(cmd,": too many outputs"));
        }
        if (nScope){
            plhs[0] = mxCreateNumericMatrix(1,1,mxINT32_CLASS,mxREAL);
            int* output = (int*)mxGetPr(plhs[0]);
            *output = nScope_get_A2_unipolar(nScope);
        } else {
            mexErrMsgTxt(strcat(cmd,": nScope is not connected"));
        }
        return;
    }

    // Got here, so command not recognized
    mexErrMsgTxt(strcat(cmd,": command not recognized."));
}
