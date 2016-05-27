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
#define RIL_REQUEST_IMS_REGISTRATION_STATE_V6 109

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
 * SMS_SEND_FAIL_RETRY will cause re-send with data encoded
 *   based on Voice Technology available.
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
#define RIL_REQUEST_IMS_SEND_SMS_V6 110

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
#define RIL_REQUEST_GET_DATA_CALL_PROFILE 111

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
#define RIL_REQUEST_SET_UICC_SUBSCRIPTION_V6 112

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
#define RIL_REQUEST_SET_DATA_SUBSCRIPTION  113

/**
 * RIL_REQUEST_GET_UICC_SUBSCRIPTION
 *
 * Request to query the UICC subscription info
 * that is currently set.
 *
 * "data" is NULL
 *
 * "response" is const RIL_SelectUiccSub *
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 *  SUBSCRIPTION_NOT_AVAILABLE
 *
 */
#define RIL_REQUEST_GET_UICC_SUBSCRIPTION 114

/**
 * RIL_REQUEST_GET_DATA_SUBSCRIPTION
 *
 * Request to query the Data subscription info
 * that is currently set.
 *
 * "data" is NULL
 *
 * "response" is int *
 * ((int *)data)[0] is == 0  Indicates data is active on subscription 0
 * ((int *)data)[0] is == 1  Indicates data is active on subscription 1
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 *  SUBSCRIPTION_NOT_AVAILABLE
 *
 */
#define RIL_REQUEST_GET_DATA_SUBSCRIPTION 115

/**
 *  RIL_REQUEST_SET_SUBSCRIPTION_MODE
 *
 *  Sets the SUBSCRIPTION_MODE to DualStandBy/SingleStandBy
 * "data" is const int *
 * ((const int *)data) [0]    1 indicates SingleStandBy Mode
                              2 indicates DualStandBy Mode
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
#define RIL_REQUEST_SET_SUBSCRIPTION_MODE 116

/**
 * RIL_REQUEST_SET_TRANSMIT_POWER
 *
 * Request to set the transmit power that is allowed
 *
 * "data" is const int *
 * ((int *)data)[0] is == 0 restore default transmit power
 * ((int *)data)[0] is == 1 reduce transmit power as per FCC regulations
 *                          (CFR47 2.1093) for WiFi hotspot
 *
 * "response" is NULL
 *
 * Valid errors:
 *  SUCCESS
 *  RADIO_NOT_AVAILABLE
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SET_TRANSMIT_POWER 117

/**
 * RIL_REQUEST_SETUP_QOS
 *
 * The QoS Parameters contain the following:
 * - Call ID
 * - QoS Specs (There can be multiple QoS Specs with a mimimum of ONE)
 *
 * A QoS Spec is a pair of QoS Flow spec and QoS Filter Spec.  QoS Flow/Filter
 * spec is a comma seperated list of key value pairs of the form 'KEY=VALUE'
 * where the 'KEY' is from the enum RIL_QosSpecKeys and the 'VALUE' is the
 * numerical value. Each QoS Spec is identified by a unique index.
 *
 *
 * For example, the following set of strings is one QoS Spec, first string has
 * Flow/Filter spec for TX and second for RX.
 *
 * "RIL_QOS_SPEC_INDEX=0,RIL_QOS_FLOW_DIRECTION=0,\
 *              RIL_QOS_FLOW_DATA_RATE_MIN=64000,\
 *              RIL_QOS_FILTER_TCP_SOURCE_PORT=4000"
 * "RIL_QOS_SPEC_INDEX=0,RIL_QOS_FLOW_DIRECTION=1,\
 *              RIL_QOS_FLOW_DATA_RATE_MIN=64000,\
 *              RIL_QOS_FILTER_TCP_SOURCE_PORT=4000"
 *
 * A QoS spec must have at least ONE pair of flow/filter spec (either RX or
 * TX). There can be any combination of (the optional) flow and filter
 * parameters included in the QoS spec.
 *
 *
 * "data" is the Call ID followed by an array of QoS Specs
 * ((char **)data)[0] - Call ID
 * ((char **)data)[1] - Flow/Filter Spec (for TX or RX)
 * ((char **)data)[2] - Flow/Filter Spec (optional: for the other direction)
 *
 * "response" is a char ** representing a return code followed by a QoS ID.
 *
 * ((char **)response)[0] - return code. 0 - success, non-0 - failure
 * ((char **)response)[1] - QoS ID
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SETUP_QOS 118

/**
 * RIL_REQUEST_RELEASE_QOS
 *
 * Request to release the QoS for a particular call
 * "data" is char **
 * ((char **)data)[0] is QoS ID
 *
 * "response" is char ** representing a return code
 * ((char **)response)[0] - return code. 0 - success, non-0 - failure
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_RELEASE_QOS 119

/**
 * RIL_REQUEST_GET_QOS_STATUS
 *
 * Request to get the QoS status and its parameters for a given QoS ID
 *
 * "data" is char *
 * ((char *)data) - QoS ID
 *
 * "response" is an const char ** representing a return code followed by an
 * array of Flow/Filter Specs
 * ((char **)response)[0] - return code. 0 - success, non-0 - failure
 * ((char **)response)[1] - Value from RIL_QosStatus
 * ((char **)response)[2] - Flow/Filter Spec   (may be followed by more specs)
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_GET_QOS_STATUS 120

/**
 * RIL_REQUEST_MODIFY_QOS
 *
 * Request to modify QoS for a particular call by specifying the QoS
 * parameters. The QoS parameters are similar to RIL_REQUEST_SETUP_QOS and
 * specifies QoS Flow/Filter Spec's with updated values
 *
 * "data" is char **
 * ((char **)data)[0] - QoS ID
 * ((char **)data)[1] - Modified Flow/Filter Spec   (For TX or RX. Mandatory.)
 * ((char **)data)[2] - Modified Flow/Filter Spec   (For the other direction. Optional)
 *
 * "response" is char ** representing a return code
 * ((char **)response)[0] - return code. 0 - success, non-0 - failure
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_MODIFY_QOS 121

/**
 * RIL_REQUEST_SUSPEND_QOS
 *
 * Request to suspend the QoS for a particular call. All the traffic will be
 * sent using the default/best effort QoS link.
 * "data" is char **
 * ((char **)data[0] is QoS ID
 *
 * "response" is char ** representing a return code
 * ((char **)response)[0] - return code. 0 - success, non-0 - failure
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_SUSPEND_QOS 122

/**
 * RIL_REQUEST_RESUME_QOS
 *
 * Request to resume the QoS for a particular call.
 * "data" is char **
 * ((char **)data)[0] is QoS ID
 *
 * "response" is char ** representing a return code
 * ((char **)response)[0] - return code. 0 - success, non-0 - failure
 *
 * Valid errors:
 *  SUCCESS
 *  GENERIC_FAILURE
 */
#define RIL_REQUEST_RESUME_QOS 123

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
#define RIL_UNSOL_RESPONSE_IMS_NETWORK_STATE_CHANGED_V6 1036

/**
 * RIL_UNSOL_RESPONSE_TETHERED_MODE_STATE_CHANGED
 *
 * Called when tethered mode is enabled or disabled
 *
 *
 * "data" is an int 0 - tethered mode off, 1 - tethered mode on
 *
 */
#define RIL_UNSOL_RESPONSE_TETHERED_MODE_STATE_CHANGED 1037

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
#define RIL_UNSOL_RESPONSE_DATA_NETWORK_STATE_CHANGED 1038

/**
 * RIL_UNSOL_ON_SS
 *
 * Called when SS response is received when DIAL/USSD/SS is changed to SS by
 * call control.
 *
 * "data" is const RIL_StkCcUnsolSsResponse *
 *
 */
#define RIL_UNSOL_ON_SS_V6 1039

/**
 * RIL_UNSOL_STK_CC_ALPHA_NOTIFY
 *
 * Called when there is an ALPHA from UICC during Call Control.
 *
 * "data" is const char * containing ALPHA string from UICC in UTF-8 format.
 *
 */
#define RIL_UNSOL_STK_CC_ALPHA_NOTIFY_V6 1040

/**
 * RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED
 *
 * Called when there is a change in subscription status.
 * This event will be sent in the following scenarios
 *  - subscription readiness at modem, which was selected by telephony layer
 *  - when subscription is deactivated by modem due to UICC card removal
 *
 * "data" is const int *
 * ((const int *)data)[0] == 0 for Subscription Deactivated
 * ((const int *)data)[0] == 1 for Subscription Activated
 *
 */
#define RIL_UNSOL_UICC_SUBSCRIPTION_STATUS_CHANGED_V6 1041

/**
 * RIL_UNSOL_QOS_STATE_CHANGED_IND
 *
 * Indication for any change in the QoS state of a particular QoS flow
 *
 * "data" is an char **
 * ((char **)data)[0] - QoS ID
 * ((char **)data)[1] - Status from RIL_QosIndStates
 *
 */
#define RIL_UNSOL_QOS_STATE_CHANGED_IND 1042
