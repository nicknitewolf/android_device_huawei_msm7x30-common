/*
 * Copyright (C) 2006,2011 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifdef RIL_VERSION_MIN
#undef RIL_VERSION_MIN
#define RIL_VERSION_MIN 4
#endif

typedef struct {
    char *aidPtr;   /* AID value, See ETSI 102.221 8.1 and 101.220 4, NULL if no value. */
    int command;    /* one of the commands listed for TS 27.007 +CRSM*/
    int fileid;     /* EF id */
    char *path;     /* "pathid" from TS 27.007 +CRSM command.
                       Path is in hex asciii format eg "7f205f70"
                       Path must always be provided.
                     */
    int p1;
    int p2;
    int p3;
    char *data;     /* May be NULL*/
    char *pin2;     /* May be NULL*/
} RIL_SIM_IO_v4;

typedef struct {
    RIL_PersoSubstate depersonalizationType;
    char             *depersonalizationCode;
} RIL_Depersonalization_v4;

typedef struct
{
  RIL_CardState card_state;
  RIL_PinState  universal_pin_state;             /* applicable to USIM and CSIM: RIL_PINSTATE_xxx */
  int           num_current_3gpp_indexes;
  int           subscription_3gpp_app_index[RIL_CARD_MAX_APPS]; /* value < RIL_CARD_MAX_APPS */
  int           num_current_3gpp2_indexes;
  int           subscription_3gpp2_app_index[RIL_CARD_MAX_APPS]; /* value < RIL_CARD_MAX_APPS */
  int           num_applications;                /* value <= RIL_CARD_MAX_APPS */
  RIL_AppStatus applications[RIL_CARD_MAX_APPS];
} RIL_CardStatus_v4;

typedef struct {
    RIL_SimRefreshResult result;
    char *               aid;   /* is AID(application ID) of the card application */
                                /* See ETSI 102.221 8.1 and 101.220 4 */
                                /*     For SIM_FILE_UPDATE result it can be set to AID of */
                                /*         application in which updated EF resides or it can be */
                                /*         NULL if EF is outside of an application. */
                                /*     For SIM_INIT result this field is set to AID of */
                                /*         application that caused REFRESH */
                                /*     For SIM_RESET result it is NULL. */
    int                  ef_id; /* is the EFID of the updated file if the result is */
                                /* SIM_FILE_UPDATE or 0 for any other result. */
} RIL_SimRefreshResponse_v4;


typedef struct {
    int             cid;        /* Context ID, uniquely identifies this call */
    int             active;     /* 0=inactive, 1=active/physical link down, 2=active/physical link up */
    char *          type;       /* One of the PDP_type values in TS 27.007 section 10.1.1.
                                   For example, "IP", "IPV6", "IPV4V6", or "PPP". */
    char *          apn;        /* ignored */
    char *          address;    /* An address, e.g., "192.0.1.3" or "2001:db8::1". */
    RIL_RadioTechnology     radioTech;     /* Radio Technology, this data call was setup on */
    int             inactiveReason; /* if the data call went inactive(0),
                                       then the reason for being inactive.
                                       defined in RIL_DataCallDropCause */
} RIL_Data_Call_Response_v4_;


typedef struct {
    char *          cid;        /* Context ID */
    char *          ifname;
    char *          addresses;  /* A space-delimited list of addresses, e.g., "192.0.1.3" or
                                   "192.0.1.11 2001:db8::1". */
} RIL_Setup_Data_Call_v4;

/**
 * RIL_REQUEST_VOICE_RADIO_TECH
 *
 * Query the radio technology type (3GPP/3GPP2) used for voice. Query is valid only
 * when radio state is RADIO_STATE_ON
 *
 * "data" is NULL
 * "response" is int *
 * ((int *) response)[0] is of type const RIL_RadioTechnologyFamily
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_VOICE_RADIO_TECH_V4 105

/**
 * RIL_REQUEST_IMS_REGISTRATION_STATE
 *
 * Request current IMS registration state
 *
 * "data" is NULL
 *
 * "response" is int *
 * ((int *)response)[0] is == 0 for IMS not registered
 * ((int *)response)[0] is == 1 for IMS registered
 *
 * If ((int*)response)[0] is = 1, then ((int *) response)[1]
 * must follow with IMS SMS encoding:
 *
 * ((int *) response)[1] is of type const RIL_RadioTechnologyFamily
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_IMS_REGISTRATION_STATE_V4 106

/**
 * RIL_REQUEST_IMS_SEND_SMS
 *
 * Send a SMS message over IMS
 *
 * "data" is const RIL_IMS_SMS_Message *
 *
 * "response" is a const RIL_SMS_Response *
 *
 * Based on the return error, caller decides to resend if sending sms
 * fails.
 * SUCCESS is error class 0 (no error)
 * SMS_SEND_FAIL_RETRY will cause re-send using RIL_REQUEST_CDMA_SEND_SMS
 *   or RIL_REQUEST_SEND_SMS based on Voice Technology available.
 * and GENERIC_FAILURE means no retry.
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  SMS_SEND_FAIL_RETRY
 *  FDN_CHECK_FAILURE
 *  GENERIC_FAILURE
 *
 */

#define RIL_REQUEST_IMS_SEND_SMS_V4 107

/**
 * RIL_REQUEST_GET_DATA_CALL_PROFILE
 *
 * Get the Data Call Profile for a particular app type
 *
 * "data" is const int*
 * (const int*)data[0] - App type. Value is specified the RUIM spec C.S0023-D
 *
 *
 * "response" is a const char * containing the count and the array of profiles
 * ((const int *)response)[0] Number RIL_DataCallProfileInfo structs(count)
 * ((const char *)response)[1] is the buffer that contains 'count' number of
 *                              RIL_DataCallProfileInfo structs.
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 *  RIL_E_DATA_CALL_PROFILE_ERROR
 *  RIL_E_DATA_CALL_PROFILE_NOT_AVAILABLE
 *
 */
#define RIL_REQUEST_GET_DATA_CALL_PROFILE 108

/**
 * RIL_REQUEST_SET_UICC_SUBSCRIPTION
 *
 * Selects/deselects a particular application/subscription to use on a particular SIM card
 * "data" is const  RIL_SelectUiccSub*
 *
 * "response" is NULL
 *
 *  Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE (radio resetting)
 *  GENERIC_FAILURE
 *  SUBSCRIPTION_NOT_AVAILABLE
 *  SUBSCRIPTION_NOT_SUPPORTED
 *
 */
#define RIL_REQUEST_SET_UICC_SUBSCRIPTION_V4 109

/**
 *  RIL_REQUEST_SET_DATA_SUBSCRIPTION
 *
 *  Selects a subscription for data call setup
 * "data" is NULL
 *
 * "response" is NULL
 *
 *  Valid errors:
 *
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE (radio resetting)
 *  GENERIC_FAILURE
 *  SUBSCRIPTION_NOT_AVAILABLE
 *
 */
#define RIL_REQUEST_SET_DATA_SUBSCRIPTION 110

/**
 * RIL_UNSOL_VOICE_RADIO_TECH_CHANGED
 *
 * Indicates that voice technology has changed.
 * Callee will invoke the following requests on main thread: RIL_REQUEST_VOICE_RADIO_TECH
 *
 */
#define RIL_UNSOL_VOICE_RADIO_TECH_CHANGED_V4 1034

/**
 * RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED
 *
 * Called when data network states has changed
 *
 * Callee will invoke the following requests on main thread:
 *
 * RIL_REQUEST_IMS_REGISTRATION_STATE
  *
 * "data" is NULL
 *
 */
#define RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED_V4 1035

/**
 * RIL_UNSOL_RESPONSE_TETHERED_MODE_STATE_CHANGED
 *
 * Called when tethered mode is enabled or disabled
 *
 *
 * "data" is an int 0 - tethered mode off, 1 - tethered mode on
 *
 */
#define RIL_UNSOL_RESPONSE_TETHERED_MODE_STATE_CHANGED 1036

/**
 * RIL_UNSOL_RESPONSE_DATA_NETWORK_STATE_CHANGED
 *
 * Called when data network states has changed
  *
 * Callee will invoke the following requests on main thread:
 *
 * RIL_REQUEST_DATA_REGISTRATION_STATE
  *
 * "data" is NULL
 *
 */
#define RIL_UNSOL_RESPONSE_DATA_NETWORK_STATE_CHANGED 1037

/**
 * RIL_UNSOL_RIL_CONNECTED
 *
 * Called the ril connects and returns the version
 *
 * "data" is int *
 * ((int *)data)[0] is RIL_VERSION
 */
/* Virtual code to match latest stack. */
#define RIL_UNSOL_RIL_CONNECTED_V4 1038
