//
// BAPI_PO_CONFIRM1 exception: 0  struct: 3  table: 9  var: 2
//
// abap 2.2.0 at: 2021-04-14 18:31:25
//

// prettier-ignore
const parameters = {

// IMPORT PARAMETERS

PURCHASEORDER    :           "", // CHAR (10) ALPHA=ALPHA Purchasing Document Number SU3=BES
// TESTRUN       :           "", // CHAR (1) Switch to Simulation Mode for Write BAPIs
// HEADER        :           {}, // BAPIMECONFHEADER Header Data Confirmation for BAPI
// HEADERX       :           {}, // BAPIMECONFHEADERX Change Parameter Header Data Confirmation BAPI

// TABLE PARAMETERS

ITEM             :           [], // BAPIMECONFITEM Confirmation Item Data
// CONFIRMATION  :           [], // BAPIMECONFDETAIL MM-PUR: Confirmation Details
// CONFIRMATIONX :           [], // BAPIMECONFDETAILX Table Type for Change Parameter Confirmation Details
// EXTENSIONIN   :           [], // BAPIPAREX Table Type for BAPIPAREX
// EXTENSIONOUT  :           [], // BAPIPAREX Table Type for BAPIPAREX
// HEADER_TEXT   :           [], // BAPIMECONFTEXT Header Text - Confirmation
// ITEM_TEXT     :           [], // BAPIMECONFITEMTEXT Text Data - Confirmation
// ITEMX         :           [], // BAPIMECONFITEMX Table Type for Change Parameter of Item Data
// RETURN        :           [], // BAPIRET2 Return Parameter(s)

// EXPORT PARAMETERS

// EXP_HEADER    :           {}, // BAPIMECONFHEADER Header Data Confirmation for BAPI
};

const result = await client.call("BAPI_PO_CONFIRM1", parameters);

//
// IMPORT PARAMETERS
//

// BAPIMECONFHEADER  Header Data Confirmation for BAPI

// prettier-ignore
const HEADER = {
  DOC_NUMBER                       :   "", // CHAR (10) ALPHA=ALPHA Purchasing Document Number SU3=BES
};

// BAPIMECONFHEADERX  Change Parameter Header Data Confirmation BAPI

// prettier-ignore
const HEADERX = {
  DOC_NUMBER                       :   "", // CHAR (1) Updated information in related user data field
  DOC_TYPE                         :   "", // CHAR (1) Updated information in related user data field
  VENDOR                           :   "", // CHAR (1) Updated information in related user data field
  CURRENCY                         :   "", // CHAR (1) Updated information in related user data field
  CURRENCY_ISO                     :   "", // CHAR (1) Updated information in related user data field
  LANGU                            :   "", // CHAR (1) Updated information in related user data field
  LANGU_ISO                        :   "", // CHAR (1) Updated information in related user data field
};


//
// TABLE PARAMETERS
//

// BAPIMECONFITEM  Confirmation Item Data
const ITEM = [];

// prettier-ignore
const ITEM_line = {
  ITEM_NO                          :   "", // NUMC (5) Item Number of Purchasing Document SU3=BSP
  MATERIAL                         :   "", // CHAR (18) ALPHA=MATN1 Material Number SU3=MAT
  MATERIAL_EXTERNAL                :   "", // CHAR (40) ALPHA=MATNL Long Material Number for MATERIAL Field
  MATERIAL_GUID                    :   "", // CHAR (32) External GUID for MATERIAL Field
  MATERIAL_VERSION                 :   "", // CHAR (10) ALPHA=MATNW Version Number for MATERIAL Field
  EMATERIAL                        :   "", // CHAR (18) ALPHA=MATN1 Material number SU3=MAT
  INT_ARTICLE_NUM                  :   "", // CHAR (18) ALPHA=EAN11 International Article Number (EAN/UPC) SU3=EAN
  VEND_MAT                         :   "", // CHAR (35) Material Number Used by Vendor
  PLANT                            :   "", // CHAR (4) Plant SU3=WRK
  STGE_LOC                         :   "", // CHAR (4) Storage location SU3=LAG
  QUANTITY                         : "0.0", // QUAN (13.3) Purchase Order Quantity
  PO_UNIT                          :   "", // UNIT (3) ALPHA=CUNIT Order unit
  PO_UNIT_ISO                      :   "", // CHAR (3) Order unit in ISO code
  ORDERPR_UN                       :   "", // UNIT (3) ALPHA=CUNIT Order Price Unit (Purchasing)
  ORDERPR_UN_ISO                   :   "", // CHAR (3) ISO code for purchase order price unit
  PRICE_UNIT                       :  "0", // DEC (5) Price unit
  NET_PRICE                        :  "0", // DEC (28.9) Currency amount for BAPIS (with 9 decimal places)
  ACKN_REQD                        :   "", // CHAR (1) Order Acknowledgment Requirement
  ACKNOWL_NO                       :   "", // CHAR (20) Order Acknowledgment Number
  SHIPPING                         :   "", // CHAR (2) Shipping Instructions
  CONFIRMED_AS_ORDERED             :   "", // CHAR (1) Confirmed as Ordered
  CANCELED                         :   "", // CHAR (1) Rejection Indicator
  EMATERIAL_EXTERNAL               :   "", // CHAR (40) ALPHA=MATNL Long Material Number for MATERIAL Field
  EMATERIAL_GUID                   :   "", // CHAR (32) External GUID for MATERIAL Field
  EMATERIAL_VERSION                :   "", // CHAR (10) ALPHA=MATNW Version Number for MATERIAL Field
};

// BAPIMECONFDETAIL  MM-PUR: Confirmation Details
const CONFIRMATION = [];

// prettier-ignore
const CONFIRMATION_line = {
  ITEM_NO                          :   "", // NUMC (5) Item Number of Purchasing Document SU3=BSP
  CONF_SER                         :   "", // NUMC (4) Sequential Number of Vendor Confirmation
  DELETE_IND                       :   "", // CHAR (1) Asset class marked for deletion
  CONF_CATEGORY                    :   "", // CHAR (2) Confirmation Category
  DELIV_DATE_TYP                   :   "", // CHAR (1) Date category of delivery date in vendor confirmation
  DELIV_DATE                       :   "", // DATS (8) Delivery Date of Vendor Confirmation
  DELIV_TIME                       :   "", // TIMS (6) Delivery Date Time-Spot in Vendor Confirmation
  QUANTITY                         : "0.0", // QUAN (13.3) Quantity as Per Vendor Confirmation
  REFERENCE                        :   "", // CHAR (35) Reference Document Number (for Dependencies see Long Text)
  BATCH                            :   "", // CHAR (10) Batch Number SU3=CHA
  CREAT_DATE                       :   "", // DATS (8) Creation Date of Confirmation
  CREAT_TIME                       :   "", // TIMS (6) Time at Which Vendor Confirmation was Created
  MPN                              :   "", // CHAR (18) ALPHA=MATN1 Material number corresponding to manufacturer part number SU3=HTN
  HANDOVERDATE                     :   "", // DATS (8) Handover Date at the Handover Location
  HANDOVERTIME                     :   "", // TIMS (6) Handover time at the handover location
  MPN_EXTERNAL                     :   "", // CHAR (40) ALPHA=MATNL Long Material Number for MATERIAL Field
  MPN_GUID                         :   "", // CHAR (32) External GUID for MATERIAL Field
  MPN_VERSION                      :   "", // CHAR (10) ALPHA=MATNW Version Number for MATERIAL Field
};

// BAPIMECONFDETAILX  Table Type for Change Parameter Confirmation Details
const CONFIRMATIONX = [];

// prettier-ignore
const CONFIRMATIONX_line = {
  ITEM_NO                          :   "", // NUMC (5) Item Number of Purchasing Document SU3=BSP
  CONF_SER                         :   "", // NUMC (4) Sequential Number of Vendor Confirmation
  ITEM_NOX                         :   "", // CHAR (1) Updated information in related user data field
  CONF_SERX                        :   "", // CHAR (1) Updated information in related user data field
  DELETE_IND                       :   "", // CHAR (1) Updated information in related user data field
  CONF_CATEGORY                    :   "", // CHAR (1) Updated information in related user data field
  DELIV_DATE_TYP                   :   "", // CHAR (1) Updated information in related user data field
  DELIV_DATE                       :   "", // CHAR (1) Updated information in related user data field
  DELIV_TIME                       :   "", // CHAR (1) Updated information in related user data field
  QUANTITY                         :   "", // CHAR (1) Updated information in related user data field
  REFERENCE                        :   "", // CHAR (1) Updated information in related user data field
  BATCH                            :   "", // CHAR (1) Updated information in related user data field
  CREAT_DATE                       :   "", // CHAR (1) Updated information in related user data field
  CREAT_TIME                       :   "", // CHAR (1) Updated information in related user data field
  MPN                              :   "", // CHAR (1) Updated information in related user data field
  HANDOVERDATE                     :   "", // CHAR (1) Updated information in related user data field
  HANDOVERTIME                     :   "", // CHAR (1) Updated information in related user data field
  MPN_EXTERNAL                     :   "", // CHAR (1) Updated information in related user data field
  MPN_GUID                         :   "", // CHAR (1) Updated information in related user data field
  MPN_VERSION                      :   "", // CHAR (1) Updated information in related user data field
};

// BAPIPAREX  Table Type for BAPIPAREX
const EXTENSIONIN = [];

// prettier-ignore
const EXTENSIONIN_line = {
  STRUCTURE                        :   "", // CHAR (30) Structure name of  BAPI table extension
  VALUEPART1                       :   "", // CHAR (240) Data part of BAPI extension parameter
  VALUEPART2                       :   "", // CHAR (240) Data part of BAPI extension parameter
  VALUEPART3                       :   "", // CHAR (240) Data part of BAPI extension parameter
  VALUEPART4                       :   "", // CHAR (240) Data part of BAPI extension parameter
};

// BAPIPAREX  Table Type for BAPIPAREX
const EXTENSIONOUT = [];

// prettier-ignore
const EXTENSIONOUT_line = {
  STRUCTURE                        :   "", // CHAR (30) Structure name of  BAPI table extension
  VALUEPART1                       :   "", // CHAR (240) Data part of BAPI extension parameter
  VALUEPART2                       :   "", // CHAR (240) Data part of BAPI extension parameter
  VALUEPART3                       :   "", // CHAR (240) Data part of BAPI extension parameter
  VALUEPART4                       :   "", // CHAR (240) Data part of BAPI extension parameter
};

// BAPIMECONFTEXT  Header Text - Confirmation
const HEADER_TEXT = [];

// prettier-ignore
const HEADER_TEXT_line = {
  TEXT_ID                          :   "", // CHAR (4) Text ID
  DELETE_IND                       :   "", // CHAR (1) Deletion indicator in purchasing document
  TEXT_FORM                        :   "", // CHAR (2) Tag column
  TEXT_LINE                        :   "", // CHAR (132) Text Line
};

// BAPIMECONFITEMTEXT  Text Data - Confirmation
const ITEM_TEXT = [];

// prettier-ignore
const ITEM_TEXT_line = {
  ITEM_NO                          :   "", // NUMC (5) Item Number of Purchasing Document SU3=BSP
  DELETE_IND                       :   "", // CHAR (1) Deletion indicator in purchasing document
  TEXT_ID                          :   "", // CHAR (4) Text ID
  TEXT_FORM                        :   "", // CHAR (2) Tag column
  TEXT_LINE                        :   "", // CHAR (132) Text Line
};

// BAPIMECONFITEMX  Table Type for Change Parameter of Item Data
const ITEMX = [];

// prettier-ignore
const ITEMX_line = {
  ITEM_NO                          :   "", // NUMC (5) Item Number of Purchasing Document SU3=BSP
  ITEM_NOX                         :   "", // CHAR (1) Updated information in related user data field
  MATERIAL                         :   "", // CHAR (1) Updated information in related user data field
  MATERIAL_EXTERNAL                :   "", // CHAR (1) Updated information in related user data field
  MATERIAL_GUID                    :   "", // CHAR (1) Updated information in related user data field
  MATERIAL_VERSION                 :   "", // CHAR (1) Updated information in related user data field
  EMATERIAL                        :   "", // CHAR (1) Updated information in related user data field
  INT_ARTICLE_NUM                  :   "", // CHAR (1) Updated information in related user data field
  VEND_MAT                         :   "", // CHAR (1) Updated information in related user data field
  PLANT                            :   "", // CHAR (1) Updated information in related user data field
  STGE_LOC                         :   "", // CHAR (1) Updated information in related user data field
  QUANTITY                         :   "", // CHAR (1) Updated information in related user data field
  PO_UNIT                          :   "", // CHAR (1) Updated information in related user data field
  PO_UNIT_ISO                      :   "", // CHAR (1) Updated information in related user data field
  ORDERPR_UN                       :   "", // CHAR (1) Updated information in related user data field
  ORDERPR_UN_ISO                   :   "", // CHAR (1) Updated information in related user data field
  PRICE_UNIT                       :   "", // CHAR (1) Updated information in related user data field
  NET_PRICE                        :   "", // CHAR (1) Updated information in related user data field
  ACKN_REQD                        :   "", // CHAR (1) Updated information in related user data field
  ACKNOWL_NO                       :   "", // CHAR (1) Updated information in related user data field
  SHIPPING                         :   "", // CHAR (1) Updated information in related user data field
  CONFIRMED_AS_ORDERED             :   "", // CHAR (1) Updated information in related user data field
  CANCELED                         :   "", // CHAR (1) Updated information in related user data field
  EMATERIAL_EXTERNAL               :   "", // CHAR (1) Updated information in related user data field
  EMATERIAL_GUID                   :   "", // CHAR (1) Updated information in related user data field
  EMATERIAL_VERSION                :   "", // CHAR (1) Updated information in related user data field
};

// BAPIRET2  Return Parameter(s)
const RETURN = [];

// prettier-ignore
const RETURN_line = {
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

// BAPIMECONFHEADER  Header Data Confirmation for BAPI

// prettier-ignore
const EXP_HEADER = {
  DOC_NUMBER                       :   "", // CHAR (10) ALPHA=ALPHA Purchasing Document Number SU3=BES
};
