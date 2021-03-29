//
// /COE/RBP_PAM_SERV_ORD_CREAT_N var: 3  struct: 0  table: 1  exception: 0
//
// abap 2.2.0 at: 2021-03-29 14:41:07
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

IV_NOTIFNO       :           "", // CHAR (12) ALPHA=ALPHA no text (en) SU3=IQM
IV_ORDER_TYPE    :           "", // CHAR (4) no text (en) SU3=AAT

// EXPORT PARAMETERS

// EV_ORDERID    :           "", // CHAR (12) ALPHA=ALPHA no text (en) SU3=ANR
// ET_RETURN     :           [], // BAPIRETTAB no text (en)
};

const result = await client.call("/COE/RBP_PAM_SERV_ORD_CREAT_N", parameters);

//
// IMPORT PARAMETERS
//


//
// EXPORT PARAMETERS
//

// BAPIRETTAB  
const ET_RETURN= [];

// prettier-ignore
const ET_RETURN= {
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
