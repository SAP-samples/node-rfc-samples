//
// BAPI_PERSDATA_DELETE exception: 0  struct: 1  table: 0  var: 8
//
// abap 2.2.0 at: 2021-03-29 15:40:08
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

EMPLOYEENUMBER    :           "", // NUMC (8) Personnel number SU3=PER
LOCKINDICATOR     :           "", // CHAR (1) Lock indicator for HR master record
OBJECTID          :           "", // CHAR (2) Object identification SU3=OPS
RECORDNUMBER      :           "", // NUMC (3) Number of Infotype Record
SUBTYPE           :           "", // CHAR (4) Subtype SU3=SUB
VALIDITYBEGIN     :           "", // DATS (8) Valid from date
VALIDITYEND       :           "", // DATS (8) Valid To Date
// NOCOMMIT       :           "", // CHAR (1) COMMIT control at BAPI interface

// EXPORT PARAMETERS

// RETURN         :           {}, // BAPIRETURN1 Structure for return code
};

const result = await client.call("BAPI_PERSDATA_DELETE", parameters);

//
// IMPORT PARAMETERS
//


//
// EXPORT PARAMETERS
//

// BAPIRETURN1  Structure for return code

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
