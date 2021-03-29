//
// CTS_API_CREATE_CHANGE_REQUEST exception: 0  struct: 0  table: 0  var: 7
//
// abap 2.2.0 at: 2021-03-29 15:40:08
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

CATEGORY       :           "", // CHAR (1) no text (undefined)
CLIENT         :           "", // CHAR (3) no text (undefined)
DESCRIPTION    :           "", // CHAR (60) Description
OWNER          :           "", // CHAR (12) no text (undefined)

// EXPORT PARAMETERS

// MESSAGE     :           "", // CHAR (80) Error Message
// REQUEST     :           "", // CHAR (20) Change Request
// RETCODE     :           "", // CHAR (3) Return code
};

const result = await client.call("CTS_API_CREATE_CHANGE_REQUEST", parameters);

//
// IMPORT PARAMETERS
//


//
// EXPORT PARAMETERS
//
