//
// BAPI_ALM_NOTIF_POSTPONE var: 6  struct: 0  table: 1  exception: 0
//
// abap 2.2.0 at: 2021-03-29 14:41:07
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

NUMBER          :           "", // CHAR (12) ALPHA=ALPHA Notification No SU3=IQM
// LANGU        :     SY-LANGU, // LANG (1) ALPHA=ISOLA Language Key SU3=SPR
// LANGUISO     :           "", // CHAR (2) Language According to ISO 639
// TESTRUN      :        SPACE, // CHAR (1) Test flag

// TABLE PARAMETERS

// RETURN       :           [], // BAPIRET2 Message Type: S = Success, E = Error, W = Warning, I = Information

// EXPORT PARAMETERS

// SYSTEMSTATUS :           "", // CHAR (40) System Status Notification
// USERSTATUS   :           "", // CHAR (40) User Status Notification
};

const result = await client.call("BAPI_ALM_NOTIF_POSTPONE", parameters);

//
// IMPORT PARAMETERS
//


//
// TABLE PARAMETERS
//

// BAPIRET2  Message Type: S = Success, E = Error, W = Warning, I = Information
const RETURN= [];

// prettier-ignore
const RETURN= {
  TYPE                             :   "", // CHAR (1) Message type: S Success, E Error, W Warning, I Info, A Abort
  ID                               :   "", // CHAR (20) Message Class
  NUMBER                           :   "", // NUMC (3) Message Number
  MESSAGE                          :   "", // CHAR (220) Message Text
  LOG_NO                           :   "", // CHAR (20) Application log: log number
  LOG_MSG_NO                       :   "", // NUMC (6) Application log: Internal message serial number
  MESSAGE_V1                       :   "", // CHAR (50) Message Variable
  MESSAGE_V2                       :   "", // CHAR (50) Message Variable
  MESSAGE_V3                       :   "", // CHAR (50) Message Variable
  MESSAGE_V4                       :   "", // CHAR (50) Message Variable
  PARAMETER                        :   "", // CHAR (32) Parameter Name
  ROW                              :    0, // INT4 (10) Lines in parameter
  FIELD                            :   "", // CHAR (30) Field in parameter
  SYSTEM                           :   "", // CHAR (10) ALPHA=ALPHA Logical system from which message originates
};


//
// EXPORT PARAMETERS
//
