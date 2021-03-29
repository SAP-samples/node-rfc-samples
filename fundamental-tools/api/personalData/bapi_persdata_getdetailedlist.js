//
// BAPI_PERSDATA_GETDETAILEDLIST exception: 0  struct: 1  table: 1  var: 3
//
// abap 2.2.0 at: 2021-03-29 15:40:08
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

EMPLOYEENUMBER      :           "", // NUMC (8) Personnel Number SU3=PER
// TIMEINTERVALHIGH :   '99991231', // DATS (8) Valid To Date
// TIMEINTERVALLOW  :   '18000101', // DATS (8) Validity start date

// TABLE PARAMETERS

PERSONALDATA        :           [], // BAPIP0002L Key for HR Master Data

// EXPORT PARAMETERS

// RETURN           :           {}, // BAPIRETURN1 Structure for Return Code
};

const result = await client.call("BAPI_PERSDATA_GETDETAILEDLIST", parameters);

//
// IMPORT PARAMETERS
//


//
// TABLE PARAMETERS
//

// BAPIP0002L  Key for HR Master Data
const PERSONALDATA= [];

// prettier-ignore
const PERSONALDATA= {
  EMPLOYEENO                       :   "", // NUMC (8) Personnel Number SU3=PER
  SUBTYPE                          :   "", // CHAR (4) Subtype SU3=SUB
  OBJECTID                         :   "", // CHAR (2) Object Identification SU3=OPS
  LOCKINDIC                        :   "", // CHAR (1) Lock Indicator for HR Master Data Record
  VALIDEND                         :   "", // DATS (8) End Date
  VALIDBEGIN                       :   "", // DATS (8) Start Date
  RECORDNR                         :   "", // NUMC (3) Number of Infotype Record With Same Key
};


//
// EXPORT PARAMETERS
//

// BAPIRETURN1  Structure for Return Code

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
};
