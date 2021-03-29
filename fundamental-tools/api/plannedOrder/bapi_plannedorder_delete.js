//
// BAPI_PLANNEDORDER_DELETE exception: 0  struct: 1  table: 0  var: 3
//
// abap 2.2.0 at: 2021-03-29 15:40:08
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

PLANNEDORDER       :           "", // CHAR (10) ALPHA=ALPHA Planned order number SU3=PAF
// LAST_ORDER      :          ' ', // CHAR (1) BAPI: Indicator - Last Planned Order for Collective Update
// USE_COLL_UPDATE :          ' ', // CHAR (1) BAPI: Collective Update of Planning File Entries

// EXPORT PARAMETERS

// RETURN          :           {}, // BAPIRETURN1 Confirmations
};

const result = await client.call("BAPI_PLANNEDORDER_DELETE", parameters);

//
// IMPORT PARAMETERS
//


//
// EXPORT PARAMETERS
//

// BAPIRETURN1  Confirmations

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
