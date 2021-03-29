//
// BAPI_INSPPOINT_CREATEFROMDATA exception: 0  struct: 2  table: 0  var: 3
//
// abap 2.2.0 at: 2021-03-29 15:40:08
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

DATA         :           {}, // BAPI2045L4 Data for inspection point

// EXPORT PARAMETERS

// INSPLOT   :           "", // NUMC (12) Inspection lot number SU3=QLS
// INSPOPER  :           "", // CHAR (4) ALPHA=NUMCV Inspection lot operation number
// INSPPOINT :           "", // NUMC (6) Inspection point
// RETURN    :           {}, // BAPIRETURN1 Return value
};

const result = await client.call("BAPI_INSPPOINT_CREATEFROMDATA", parameters);

//
// IMPORT PARAMETERS
//

// BAPI2045L4  Data for inspection point

// prettier-ignore
const DATA= {
  INSPPOINT                        :   "", // NUMC (6) Inspection Point Number
  INSPLOT                          :   "", // NUMC (12) Inspection Lot Number SU3=QLS
  INSPOPER                         :   "", // CHAR (4) ALPHA=NUMCV Inspection Lot Operation Number
};


//
// EXPORT PARAMETERS
//

// BAPIRETURN1  Return value

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
