#ifndef SAPNWRFC_H
#define SAPNWRFC_H

#include <stdlib.h>
#include <stdio.h>
#ifndef SAPTYPE_H
#include "sapucrfc.h"
#endif /* SAPTYPE_H */

#ifndef DECL_EXP
#   if defined(SAPonLIN) && defined(GCC_HIDDEN_VISIBILITY)
#     define DECL_EXP __attribute__((visibility("default")))
#   elif defined(SAPonDARW) && !defined(CPP_USE_STLPORT)
#     define DECL_EXP __attribute__((visibility("default")))
#   else
#     define DECL_EXP
#   endif
#endif /* DECL_EXP */

#ifndef SAP_API
#ifdef SAPonNT 
#     define SAP_API _stdcall
#else
#     define SAP_API
#endif /* SAPonNT */ 
#endif /* SAP_API */

#ifdef SAPonNT
#pragma warning (disable : 4267)  // disable warning: conversion from 'size_t' to 'const unsigned int'
#endif

#if defined(SAPonOS390) && defined(__XPLINK__) && __CHARSET_LIB == 1
#pragma runopts("FILETAG(AUTOCVT,AUTOTAG)")
#endif  

#if defined SAPwith64_BIT && \
    ! defined SAPonNT && \
    ! defined SAPonOS400 && \
    ! defined SAPccQ

  typedef          long RFC_INT8;   /* this requires the LP64 data model */
#elif defined SAPonHPPA   || \
      defined SAPonRS6000 || \
      defined SAPonSUN    || \
      defined SAPonOS390  || \
      defined SAPonOS400  || \
      defined SAPonDARW   || \
      defined SAPonLIN   

  typedef          long long RFC_INT8;
#elif defined SAPonNT
  typedef          __int64 RFC_INT8;
#endif


/* RFC scalar data type mappings */
typedef SAP_UC         RFC_CHAR;     ///< Characters, RFCTYPE_CHAR
typedef RFC_CHAR       RFC_NUM;      ///< Digits, RFCTYPE_NUM          /*SAPUNICODEOK_CHARTYPE*/
typedef SAP_RAW        RFC_BYTE;     ///< Raw data, RFCTYPE_BYTE
typedef SAP_RAW        RFC_BCD;      ///< Packed numbers, RFCTYPE_BCD  /*SAPUNICODEOK_CHARTYPE*/
typedef SAP_RAW        RFC_INT1;     ///< 1 byte integer, RFCTYPE_INT1
typedef short          RFC_INT2;     ///< 2 byte integer, RFCTYPE_INT2
typedef int			   RFC_INT;		 ///< 4 byte integer, RFCTYPE_INT
typedef double         RFC_FLOAT;    ///< Floating point, double precision, RFCTYPE_FLOAT
typedef RFC_CHAR       RFC_DATE[8];  ///< Date, RFCTYPE_DATE (YYYYMMDD)
typedef RFC_CHAR       RFC_TIME[6];  ///< Time, RFCTYPE_TIME (HHMMSS)
typedef DecFloat16     RFC_DECF16;   ///< IEEE 754r decimal floating point, 8 bytes
typedef DecFloat34     RFC_DECF34;   ///< IEEE 754r decimal floating point, 16 bytes
typedef RFC_INT8       RFC_UTCLONG ;        ///< timestamp/long
typedef RFC_INT8       RFC_UTCSECOND ;      ///< timestamp/second
typedef RFC_INT8       RFC_UTCMINUTE ;      ///< timestamp/minute
typedef int            RFC_DTDAY ;          ///< date/day
typedef int            RFC_DTWEEK   ;       ///< date/week
typedef int            RFC_DTMONTH  ;       ///< date/month
typedef int            RFC_TSECOND  ;       ///< time/second
typedef short          RFC_TMINUTE  ;       ///< time/minute
typedef short          RFC_CDAY     ;       ///< Calandendar day: Day and month

#define RFC_TID_LN 24
#define RFC_UNITID_LN 32
typedef SAP_UC RFC_TID[RFC_TID_LN+1];		///< Used for TIDs in inbound and outbound tRFC/qRFC
typedef SAP_UC RFC_UNITID[RFC_UNITID_LN+1];	///< Used for Unit IDs in inbound and outbound bgRFC


/** \enum _RFCTYPE
 * \ingroup api
 *
 * RFCTYPE is used in field descriptions (#RFC_FIELD_DESC) and parameter descriptions 
 * (#RFC_PARAMETER_DESC) and denotes the ABAP data type of the corresponding field/parameter.
 */
typedef enum _RFCTYPE
{
	RFCTYPE_CHAR   = 0,		///< 1-byte or multibyte character, fixed size, blank padded
	RFCTYPE_DATE   = 1,		///< Date ( YYYYYMMDD )
	RFCTYPE_BCD    = 2,		///< Packed number, any length between 1 and 16 bytes
	RFCTYPE_TIME   = 3,		///< Time (HHMMSS) 
	RFCTYPE_BYTE   = 4,		///< Raw data, binary, fixed length, zero padded.
	RFCTYPE_TABLE   = 5,	///< Internal table
	RFCTYPE_NUM    = 6,		///< Digits, fixed size, leading '0' padded.
	RFCTYPE_FLOAT  = 7,		///< Floating point, double precision
	RFCTYPE_INT    = 8,		///< 4-byte integer
	RFCTYPE_INT2   = 9,		///< 2-byte integer. Obsolete, not directly supported by ABAP/4
	RFCTYPE_INT1   = 10,	///< 1-byte integer, unsigned. Obsolete, not directly supported by ABAP/4
	RFCTYPE_NULL  = 14,		///< Not supported data type.
	RFCTYPE_ABAPOBJECT = 16,///< ABAP object.
	RFCTYPE_STRUCTURE = 17,	///< ABAP structure
	RFCTYPE_DECF16  = 23,	///< IEEE 754r decimal floating point, 8 bytes
	RFCTYPE_DECF34  = 24,	///< IEEE 754r decimal floating point, 16 bytes
	RFCTYPE_XMLDATA = 28,	///< No longer used!
	RFCTYPE_STRING = 29,	///< Variable-length, null-terminated string
	RFCTYPE_XSTRING = 30,	///< Variable-length raw string, length in bytes
	RFCTYPE_INT8,			///< 8-byte integer
	RFCTYPE_UTCLONG ,		///< timestamp/long, 8-byte integer
	RFCTYPE_UTCSECOND ,		///< timestamp/second, 8-byte integer
	RFCTYPE_UTCMINUTE ,		///< timestamp/minute, 8-byte integer
	RFCTYPE_DTDAY ,			///< date/day , 4-byte integer
	RFCTYPE_DTWEEK   ,		///< date/week, 4-byte integer
	RFCTYPE_DTMONTH  ,		///< date/month, 4-byte integer
	RFCTYPE_TSECOND  ,		///< time/second, 4-byte integer
	RFCTYPE_TMINUTE  ,		///< time/minute, 2-byte integer
	RFCTYPE_CDAY  ,			///< calendar day, 2-byte integer
	RFCTYPE_BOX  ,			///< boxed structure, note: not supported by NW RFC lib
	RFCTYPE_GENERIC_BOX,	///< boxed client dependent structure, note: not supported by NW RFC lib
	_RFCTYPE_max_value		///< the max. value of RFCTYPEs
}RFCTYPE;

/** \enum _RFC_RC
 * \ingroup api
 *
 * RFC return codes used by all functions that do not directly return a handle.
 * Also used as error indicator in the structure #RFC_ERROR_INFO::code.
 */
typedef enum _RFC_RC
{
    RFC_OK,						///< Everything O.K. Used by every function
    RFC_COMMUNICATION_FAILURE,	///< Error in Network & Communication layer
    RFC_LOGON_FAILURE,			///< Unable to logon to SAP system. Invalid password, user locked, etc.
    RFC_ABAP_RUNTIME_FAILURE,	///< SAP system runtime error (SYSTEM_FAILURE): Shortdump on the backend side
    RFC_ABAP_MESSAGE,			///< The called function module raised an E-, A- or X-Message
    RFC_ABAP_EXCEPTION,			///< The called function module raised an Exception (RAISE or MESSAGE ... RAISING)
    RFC_CLOSED,					///< Connection closed by the other side
    RFC_CANCELED,				///< No longer used
    RFC_TIMEOUT,				///< Time out
    RFC_MEMORY_INSUFFICIENT,	///< Memory insufficient
    RFC_VERSION_MISMATCH,		///< Version mismatch
    RFC_INVALID_PROTOCOL,		///< The received data has an unsupported format
    RFC_SERIALIZATION_FAILURE,	///< A problem while serializing or deserializing RFM parameters
    RFC_INVALID_HANDLE,			///< An invalid handle was passed to an API call
    RFC_RETRY,					///< RfcListenAndDispatch did not receive an RFC request during the timeout period
    RFC_EXTERNAL_FAILURE,		///< Error in external custom code. (E.g. in the function handlers or tRFC handlers.) Results in SYSTEM_FAILURE
    RFC_EXECUTED,				///< Inbound tRFC Call already executed (needs to be returned from RFC_ON_CHECK_TRANSACTION in case the TID is already known and successfully processed before.)
    RFC_NOT_FOUND,				///< Function or structure definition not found (Metadata API)
    RFC_NOT_SUPPORTED,			///< The operation is not supported on that handle
    RFC_ILLEGAL_STATE,			///< The operation is not supported on that handle at the current point of time (e.g. trying a callback on a server handle, while not in a call)
    RFC_INVALID_PARAMETER,		///< An invalid parameter was passed to an API call, (e.g. invalid name, type or length)
    RFC_CODEPAGE_CONVERSION_FAILURE, ///< Codepage conversion error
    RFC_CONVERSION_FAILURE,		///< Error while converting a parameter to the correct data type
    RFC_BUFFER_TOO_SMALL,		///< The given buffer was to small to hold the entire parameter. Data has been truncated.
    RFC_TABLE_MOVE_BOF,			///< Trying to move the current position before the first row of the table
    RFC_TABLE_MOVE_EOF,			///< Trying to move the current position after the last row of the table
    RFC_START_SAPGUI_FAILURE,   ///< Failed to start and attach SAPGUI to the RFC connection
    RFC_ABAP_CLASS_EXCEPTION,   ///< The called function module raised a class based exception 
	RFC_UNKNOWN_ERROR,			///< "Something" went wrong, but I don't know what...
	RFC_AUTHORIZATION_FAILURE,	///< Authorization check error
    RFC_AUTHENTICATION_FAILURE,	///< The authentication handler (RFC_ON_AUTHENTICATION_CHECK) failed to authenticate the user trying to log on
	RFC_CRYPTOLIB_FAILURE,	    ///< Error when dealing with functions provided by the cryptolibrary
	RFC_IO_FAILURE,				///< Error when dealing with io functions, streams etc
	RFC_LOCKING_FAILURE,	    ///< Requesting or freeing critical sections or mutex failed
	_RFC_RC_max_value			///< Don't use
}RFC_RC;

/** \enum _RFC_ERROR_GROUP
 * \ingroup api
 *
 * Groups several error conditions together, depending on the "layer" to which they belong.
 * Used in the structure #RFC_ERROR_INFO::group.
 */
typedef enum _RFC_ERROR_GROUP
{
    OK,								///< OK
	ABAP_APPLICATION_FAILURE,		///< ABAP Exception raised in ABAP function modules
	ABAP_RUNTIME_FAILURE,			///< ABAP Message raised in ABAP function modules or in ABAP runtime of the backend (e.g Kernel)
    LOGON_FAILURE,					///< Error message raised when logon fails 
	COMMUNICATION_FAILURE,			///< Problems with the network connection (or backend broke down and killed the connection)
	EXTERNAL_RUNTIME_FAILURE,		///< Problems in the RFC runtime of the external program (i.e "this" library)
	EXTERNAL_APPLICATION_FAILURE,	///< Problems in the external program (e.g in the external server implementation)
	EXTERNAL_AUTHORIZATION_FAILURE,	///< Problems raised in the authorization check handler provided by the external server implementation
    EXTERNAL_AUTHENTICATION_FAILURE,///< Problems raised by the authentication handler (RFC_ON_AUTHENTICATION_CHECK)
	CRYPTOLIB_FAILURE,              ///< Problems when dealing with functions provided by the cryptolibrary
	LOCKING_FAILURE	                ///< Requesting or freeing critical sections or mutex failed
}RFC_ERROR_GROUP;




/** \struct _RFC_ERROR_INFO
 * \ingroup api
 *
 * Used in all functions of the NW RFC library to return detailed information about
 * an error that has just occurred. This can be an error that the communication partner
 * sent back to us, an error that occurred in the network layer or operating system,
 * an internal error in the NW RFC library or an error that the application programmer
 * (i.e. you) has committed...
 *
 * Within a server function implementation, the application programmer (you) can return
 * this structure to the RFC library in order to specify the error type & message that
 * you want to send back to the backend.
 */
typedef struct _RFC_ERROR_INFO
{
    RFC_RC code;					///< Error code. Should be the same as the API returns if the API has return type RFC_RC
    RFC_ERROR_GROUP group;          ///< Error group
    SAP_UC key[128];				///< Error key
    SAP_UC message[512];			///< Error message
    SAP_UC abapMsgClass[20+1];		///< ABAP message ID , or class
    SAP_UC abapMsgType[1+1];		///< ABAP message type, e.g. 'E', 'A' or 'X'
    RFC_NUM abapMsgNumber[3 + 1];	///< ABAP message number
    SAP_UC abapMsgV1[50+1];			///< ABAP message details field 1, corresponds to SY-MSGV1 
    SAP_UC abapMsgV2[50+1];			///< ABAP message details field 2, corresponds to SY-MSGV2 
    SAP_UC abapMsgV3[50+1];			///< ABAP message details field 3, corresponds to SY-MSGV3 
    SAP_UC abapMsgV4[50+1];			///< ABAP message details field 4, corresponds to SY-MSGV4 
}RFC_ERROR_INFO;

/** \struct _RFC_ATTRIBUTES
 * \ingroup connection
 *
 * Structure returned by RfcGetConnectionAttributes() giving some
 * information about the partner system on the other side of this RFC connection.
 */
typedef struct _RFC_ATTRIBUTES
{
    SAP_UC dest[64+1];				///< RFC destination
    SAP_UC host[100+1];				///< Own host name
    SAP_UC partnerHost[100+1];		///< Partner host name
    SAP_UC sysNumber[2+1];			///< R/3 system number
    SAP_UC sysId[8+1];				///< R/3 system ID
    SAP_UC client[3+1];				///< Client ("Mandant")
    SAP_UC user[12+1];				///< User
    SAP_UC language[2+1];			///< Language
    SAP_UC trace[1+1];				///< Trace level (0-3)
    SAP_UC isoLanguage[2+1];		///< 2-byte ISO-Language
    SAP_UC codepage[4+1];           ///< Own code page
    SAP_UC partnerCodepage[4+1];	///< Partner code page
    SAP_UC rfcRole[1+1];			///< C/S: RFC Client / RFC Server
    SAP_UC type[1+1];				///< 2/3/E/R: R/2,R/3,Ext,Reg.Ext
    SAP_UC partnerType[1+1];		///< 2/3/E/R: R/2,R/3,Ext,Reg.Ext
    SAP_UC rel[4+1];				///< My system release
    SAP_UC partnerRel[4+1];			///< Partner system release
    SAP_UC kernelRel[4+1];			///< Partner kernel release
    SAP_UC cpicConvId[8 + 1];		///< CPI-C Conversation ID
    SAP_UC progName[128+1];			///< Name of the calling APAB program (report, module pool)
	SAP_UC partnerBytesPerChar[1+1];///< Number of bytes per character in the backend's current codepage. Note this is different from the semantics of the PCS parameter.
    SAP_UC partnerSystemCodepage[4 + 1];  ///<  Partner system code page 
	SAP_UC partnerIP[15 + 1];		///< Partner IP
	SAP_UC partnerIPv6[45 + 1];		///< Partner IPv6
	SAP_UC reserved[17];			///< Reserved for later use
}RFC_ATTRIBUTES, *P_RFC_ATTRIBUTES;

/** \struct _RFC_SECURITY_ATTRIBUTES
 * \ingroup connection
 *
 * Structure passed to the RFC_SERVER_AUTHORIZATION_HANDLER giving some
 * security related information about the calling ABAP partner of an incoming RFC call.
 */
typedef struct _RFC_SECURITY_ATTRIBUTES
{
	SAP_UC *functionName;	///< Name of the called function module
	SAP_UC *sysId;			///< Calling ABAP system ID
	SAP_UC *client;			///< ABAP Client ("Mandant")
	SAP_UC *user;			///< ABAP User
	SAP_UC *progName;		///< Name of the calling APAB program (report, module pool)
	SAP_UC *sncName;		///< SNC name of the calling ABAP system, if SNC is enabled. Use this only for display or logging purposes.
	SAP_UC *ssoTicket;		///< Logon ticket of the ABAP user, if SSO2 or assertion tickets are enabled
	SAP_RAW *sncAclKey;		///< Canonical representation of the SNC name of the calling ABAP system, if SNC is enabled. Use this for comparisons and access checks.
	unsigned sncAclKeyLength; ///< Length of the above SNC AclKey
}RFC_SECURITY_ATTRIBUTES, *P_RFC_SECURITY_ATTRIBUTES;

/** \struct _RFC_UNIT_ATTRIBUTES
 * \ingroup bgrfc
 *
 * If the external program is the sender of the bgRFC unit, this structure is used to set a
 * bunch of special attributes that determine, how a bgRFC Unit will be processed in the backend.
 * The fields user, client, tCode and program are optional. If left empty, the NW RFC lib will
 * fill them with default values. The fields hostname, sendingDate and sendingTime should not be
 * filled, the lib fills them, when the unit is submitted.
 *
 * If the external program is the receiver of the bgRFC unit, you can use RfcGetServerContext()
 * to obtain the values that were sent by the backend.
 */
typedef struct _RFC_UNIT_ATTRIBUTES{
	short kernelTrace;				///< If != 0, the backend will write kernel traces, while executing this unit.
	short satTrace;					///< If != 0, the backend will write statistic records, while executing this unit.
	short unitHistory;				///< If != 0, the backend will keep a "history" for this unit.
	short lock;						///< Used only for type Q: If != 0, the unit will be written to the queue, but not processed. The unit can then be started manually in the ABAP debugger.
	short noCommitCheck;			///< Per default the backend will check during execution of a unit, whether one
                                    ///< of the unit's function modules triggers an explicit or implicit COMMIT WORK.
                                    ///< In this case the unit is aborted with an error, because the transactional
                                    ///< integrity of this unit cannot be guaranteed. By setting "noCommitCheck" to
                                    ///< true (!=0), this behavior can be suppressed, meaning the unit will be executed
                                    ///< anyway, even if one of its function modules "misbehaves" and triggers a COMMIT WORK.
	SAP_UC user[12+1];				///< Sender User (optional). Default is current operating system User.
	SAP_UC client[3+1];				///< Sender Client ("Mandant") (optional). Default is "000".
	SAP_UC tCode[20+1];				///< Sender Transaction Code (optional). Default is "".
	SAP_UC program[40+1];			///< Sender Program (optional). Default is current executable name.
	SAP_UC hostname[40+1];			///< Sender hostname. Used only when the external program is server. In the client case the nwrfclib fills this automatically.
	RFC_DATE sendingDate;			///< Sending date in UTC (GMT-0). Used only when the external program is server. In the client case the nwrfclib fills this automatically.
	RFC_TIME sendingTime;			///< Sending time in UTC (GMT-0). Used only when the external program is server. In the client case the nwrfclib fills this automatically.
}RFC_UNIT_ATTRIBUTES;

/** \struct _RFC_UNIT_IDENTIFIER
 * \ingroup bgrfc
 *
 * For convenience combines a unit's ID and its type.
 */
typedef struct _RFC_UNIT_IDENTIFIER{
	SAP_UC unitType;				///< 'T' for "transactional" behavior (unit is executed synchronously), 'Q' for "queued" behavior (unit is written into a queue and executed asynchronously)
	RFC_UNITID unitID;				///< The 32 digit unit ID of the background unit.
}RFC_UNIT_IDENTIFIER;

/** \enum _RFC_UNIT_STATE
 * \ingroup bgrfc
 *
 * Used in RfcGetUnitState() for inquiring the processing status of a background Unit that 
 * we (or someone else) sent into this backend.
 */
typedef enum _RFC_UNIT_STATE{
	RFC_UNIT_NOT_FOUND,		///< No information for this unit ID and unit type can be found in the target system. If you are sure, that target system, unit ID and unit type are correct, it means that your previous attempt did not even reach the target system. Send the unit again. However, if you get this status after the Confirm step has already been executed, it means that everything is ok. Don't re-execute in this case!
	RFC_UNIT_IN_PROCESS,	///< Backend system is still in the process of persisting (or executing if type 'T') the payload data. Give it some more time and check the state again later. If this takes "too long", an admin should probably have a look at why there is no progress here.
	RFC_UNIT_COMMITTED,		///< Data has been persisted (or executed if type 'T') ok on receiver side. Confirm event may now be triggered.
	RFC_UNIT_ROLLED_BACK,	///< An error of any type has occurred. Unit needs to be resent.
	RFC_UNIT_CONFIRMED		///< Temporary state between the Confirm event and the time, when the status data will be erased for good. Nothing to be done. Just delete the payload and status information on your side.
}RFC_UNIT_STATE;

typedef RFC_CHAR RFC_ABAP_NAME[30+1];			///< Name of ABAP function, function parameter or field in a structure. (null-terminated)
typedef RFC_CHAR RFC_PARAMETER_DEFVALUE[30+1];	///< Default value of a function module parameter. (null-terminated)
typedef RFC_CHAR RFC_PARAMETER_TEXT[79+1];		///< Parameter description for a function module parameter. (null-terminated)


/** \enum _RFC_CALL_TYPE
 * \ingroup connection
 *
 * Used in RfcGetServerContext() for inquiring the type of 
 * an incoming function call from the backend.
 */
typedef enum _RFC_CALL_TYPE{
	RFC_SYNCHRONOUS,		///< It's a standard synchronous RFC call.
	RFC_TRANSACTIONAL,		///< This function call is part of a transactional LUW (tRFC).
	RFC_QUEUED,				///< This function call is part of a queued LUW (qRFC).
	RFC_BACKGROUND_UNIT		///< This function call is part of a background LUW (bgRFC).
}RFC_CALL_TYPE;

/** \struct _RFC_SERVER_CONTEXT
 * \ingroup connection
 *
 * Used in RfcGetServerContext() for obtaining more information about the
 * current incoming function call.
 */
typedef struct _RFC_SERVER_CONTEXT{
	RFC_CALL_TYPE type;						///< Specifies the type of function call. Depending on the value of this field, some of the other fields of this struct may be filled.
	RFC_TID tid;							///< If type is RFC_TRANSACTIONAL or RFC_QUEUED, this field is filled with the 24 digit TID of the tRFC/qRFC unit.
	RFC_UNIT_IDENTIFIER* unitIdentifier;	///< If type is RFC_BACKGROUND_UNIT, this pointer is set to the unit identifier of the LUW. Note: the pointer is valid only during the execution context of your server function.
	RFC_UNIT_ATTRIBUTES* unitAttributes;	///< If type is RFC_BACKGROUND_UNIT, this pointer is set to the unit attributes of the LUW. Note: the pointer is valid only during the execution context of your server function.
	unsigned isStateful;					///< Specifies whether the current server connection is processing stateful RFC requests (assigned permanently to one fixed ABAP user session).
	SAP_UC sessionID[33];					///< Contains a unique zero-terminated session ID, identifying the ABAP or external user session. Can be used in stateful servers to store session context in a hashmap.
}RFC_SERVER_CONTEXT;

/** \enum _RFC_AUTHENTICATION_TYPE
* \ingroup autoserver
*
* Type of authentication method used by the backend authentication handler (RFC_ON_AUTHENTICATION_CHECK).
*/
typedef enum _RFC_AUTHENTICATION_TYPE{
    RFC_AUTH_NONE,                          ///< No authentication data was provided
    RFC_AUTH_BASIC,                         ///< Authentication with user and password
    RFC_AUTH_X509,                          ///< Authentication with x509 certificate
    RFC_AUTH_SSO                            ///< Authentication with assertion ticket
}RFC_AUTHENTICATION_TYPE;

/** \struct _RFC_CERTIFICATE_DATA
* \ingroup autoserver
*
* Compact structure containing relevant information about the x509 certificate provided by the RFC client. Can be accessed by the
* authentication handler (RFC_ON_AUTHENTICATION_CHECK) and used for validating the user trying to log on.
*/

typedef struct _RFC_CERTIFICATE_DATA{
    const SAP_UC* subject;                   ///< Distinguished name of the user of the certificate
    const SAP_UC* issuer;                    ///< Distinguished name of the certificate authority (CA) that issued the certificate
    SAP_ULLONG validTo;                      ///< UTC Expiration date on which the certificate is no longer considered valid
    SAP_ULLONG validFrom;                    ///< UTC Starting date since the certificate is valid
    const SAP_UC* signature;                 ///< Fingerprint of the public key
    struct _RFC_CERTIFICATE_DATA* next;      ///< Pointer to the next certificate in the chain if any
}RFC_CERTIFICATE_DATA;

/** \struct _RFC_TYPE_DESC_HANDLE
 * \ingroup repository
 *
 * Handle to a cached metadata description of a structure or table type.
 */
typedef struct _RFC_TYPE_DESC_HANDLE {void* handle;} *RFC_TYPE_DESC_HANDLE;

/** \struct _RFC_FUNCTION_DESC_HANDLE
 * \ingroup repository
 *
 * Handle to a cached metadata description of a function module.
 */
typedef struct _RFC_FUNCTION_DESC_HANDLE {void* handle;} *RFC_FUNCTION_DESC_HANDLE;

/** \struct _RFC_CLASS_DESC_HANDLE
 * \ingroup repository
 *
 * Handle to a cached metadata description of a class.
 */
typedef struct _RFC_CLASS_DESC_HANDLE {void* handle;} *RFC_CLASS_DESC_HANDLE;


/** \struct RFC_DATA_CONTAINER
 * \ingroup container
 *
 * Handle to a general data container (structure, table or function module).
 */
typedef struct RFC_DATA_CONTAINER {void* handle;} *DATA_CONTAINER_HANDLE;

/** \struct RFC_STRUCTURE_HANDLE
 * \ingroup container
 *
 * Handle to a data container for a structure.
 */
typedef DATA_CONTAINER_HANDLE RFC_STRUCTURE_HANDLE;

/** \struct RFC_FUNCTION_HANDLE
 * \ingroup container
 *
 * Handle to a data container for a function module.
 */
typedef DATA_CONTAINER_HANDLE RFC_FUNCTION_HANDLE;

/** \struct RFC_TABLE_HANDLE
 * \ingroup container
 *
 * Handle to a data container for a table.
 */
typedef DATA_CONTAINER_HANDLE RFC_TABLE_HANDLE;

/** \struct RFC_ABAP_OBJECT_HANDLE
 * \ingroup container
 *
 * Handle to a data container for an ABAP object instance.
 */
typedef DATA_CONTAINER_HANDLE RFC_ABAP_OBJECT_HANDLE;

/** \struct _RFC_THROUGHPUT_HANDLE
* \ingroup throughput
*
* Handle to a throughput object which can monitor performance relevant data of connections and servers.
* Returned by RfcCreateThroughput() or RfcGetThroughput().
*/
typedef struct _RFC_THROUGHPUT_HANDLE {void* handle;} *RFC_THROUGHPUT_HANDLE;

/** \struct _RFC_AUTHENTICATION_HANDLE
* \ingroup autoserver
*
* Handle to an authentication object which gives access to relevant authentication data received from the client.
* This data can be used to authenticate users in the authentication handler (RFC_ON_AUTHENTICATION_CHECK).
* Passed into the authentication handler (RFC_ON_AUTHENTICATION_CHECK) by the NW RFC library
*/
typedef struct _RFC_AUTHENTICATION_HANDLE {void* handle;} *RFC_AUTHENTICATION_HANDLE;

/** \struct _RFC_CONNECTION_HANDLE
 * \ingroup connection
 *
 * Handle to an RFC connection (client connection or server connection).
 * Returned by RfcOpenConnection() or RfcRegisterServer().
 */
typedef struct _RFC_CONNECTION_HANDLE {void* handle;} *RFC_CONNECTION_HANDLE;

/* Definitions for standalone Server */

/** \struct _RFC_SERVER_HANDLE
* \ingroup autoserver
*
* Handle to an automated ("multi-count") RFC Server, which can manage multiple parallel listening server sessions.
* Returned by RfcCreateServer().
*/
typedef struct _RFC_SERVER_HANDLE {void* handle;} *RFC_SERVER_HANDLE;

/** \enum _RFC_PROTOCOL_TYPE
* \ingroup connection
*
* Used in state information in order to indicate the different types of RFC programs, RFC Server types, etc.
*/
typedef enum _RFC_PROTOCOL_TYPE{
	RFC_UNKOWN,				///< Unspecified
	RFC_CLIENT,				///< RFC Client
	RFC_STARTED_SERVER,		///< Started RFC Server
	RFC_REGISTERED_SERVER,	///< Registered RFC Server
	RFC_MULTI_COUNT_REGISTERED_SERVER,///< Multi-count registered RFC Server
	RFC_TCP_SOCKET_CLIENT,	///< TCP Client
	RFC_TCP_SOCKET_SERVER,	///< TCP Server
    RFC_WEBSOCKET_CLIENT,	///< Websocket RFC Client
    RFC_WEBSOCKET_SERVER,	///< Websocket RFC Server
    RFC_PROXY_WEBSOCKET_CLIENT	///< Websocket RFC Client
}RFC_PROTOCOL_TYPE;

/** \enum _RFC_SERVER_STATE
* \ingroup autoserver
*
* Used in state information in order to indicate the current state of an RFC Server.
*/
typedef enum _RFC_SERVER_STATE {
	RFC_SERVER_INITIAL,	///< The server object has been created, but nothing has been done with it yet.
	RFC_SERVER_STARTING,///< The server has been started, but startup is not yet complete and the server is not yet able to receive/serve requests. Should quickly switch to RUNNING or BROKEN.
	RFC_SERVER_RUNNING,	///< Means at least one registration is still able to accept request from the gateway (in case of Registered Server), or that the server port is open and listening (in case of TCP Socket Server).
	RFC_SERVER_BROKEN,	///< Means that all registrations are dead, e.g. because of gateway being down (in case of Registered Server), or that for some reason server port could not be opened (in case of TCP Socket Server).
	RFC_SERVER_STOPPING,///< The server has been stopped via RfcShutdownServer() (with a timeout > 0) and is still busy processing ongoing requests. It is however no longer accepting new requests. Should switch to STOPPED, once the ongoing requests are finished.
	RFC_SERVER_STOPPED	///< The server has been stopped via RfcShutdownServer() and is currently not processing nor accepting any requests. The object, however, is still valid and can be started again anytime with RfcLaunchServer().
} RFC_SERVER_STATE;

/** \struct _RFC_SERVER_ATTRIBUTES
* \ingroup autoserver
*
* Information about an RFC Server returned by RfcGetServerAttributes(). 
*/
typedef struct _RFC_SERVER_ATTRIBUTES{
	SAP_UC* serverName;			///< This server's name as given when creating the server.
	RFC_PROTOCOL_TYPE type;		///< This RFC server's type. Will be one of RFC_MULTI_COUNT_REGISTERED_SERVER or RFC_TCP_SOCKET_SERVER.
	unsigned registrationCount;	///< The current number of active registrations (in case of a Registered Server) or the maximum number of parallel connections the server will accept (in case of a TCP Socket Server).
	RFC_SERVER_STATE state;		///< This server's state.
	unsigned currentBusyCount;	///< The number of requests currently being processed.
	unsigned peakBusyCount;		///< The maximum number of requests the server has been processing in parallel since it has been created.
} RFC_SERVER_ATTRIBUTES;


/** \enum _RFC_SESSION_EVENT
* \ingroup autoserver
*
* Used in a server session change listener to notify the application whenever a new user session on the server gets started or ends.
*/
typedef enum _RFC_SESSION_EVENT{
	RFC_SESSION_CREATED,	///< A new stateful user session has been created on the server. This can be done either by the server itself via RfcSetServerStateful(), or by the backend via function module RFC_SET_REG_SERVER_PROPERTY
	RFC_SESSION_ACTIVATED,	///< A function call came in from the backend and started processing. This event can probably be ignored by 99% of the applications.
	RFC_SESSION_PASSIVATED,	///< A function call completed processing. This event can probably be ignored by 99% of the applications.
	RFC_SESSION_DESTROYED	///< A stateful user session has been destroyed, either by the server itself via RfcSetServerStateful(), or by the backend via function module RFC_SET_REG_SERVER_PROPERTY, or because the connection was closed (e.g. the corresponding ABAP user session ended or explicitly closed the connection), or because the connection was broken by network error/system failure etc. The application should now clean up all memory/resources allocated for the given session ID.
} RFC_SESSION_EVENT;

/** \struct _RFC_SESSION_CHANGE
* \ingroup autoserver
*
* Notifies an RFC Server that a stateful user session has just been created or destroyed.
*/
typedef struct _RFC_SESSION_CHANGE {
	SAP_UC sessionID[30 + 1];	///< Session ID of the user session in question
	RFC_SESSION_EVENT event;	///< What has been done with that session
} RFC_SESSION_CHANGE;

typedef RFC_RC (SAP_API* RFC_SERVER_SESSION_CHANGE_LISTENER)(RFC_SERVER_HANDLE serverHandle, RFC_SESSION_CHANGE* sessionChange);

typedef void (SAP_API* RFC_SERVER_ERROR_LISTENER)(RFC_SERVER_HANDLE serverHandle, RFC_ATTRIBUTES* clientInfo, RFC_ERROR_INFO* errorInfo);

/** \struct _RFC_STATE_CHANGE
* \ingroup autoserver
*
* Notifies the application that an RFC Server changed its state (e.g. got started, got shutdown, lost its connection to the backend etc.).
*/
typedef struct _RFC_STATE_CHANGE {
	RFC_SERVER_STATE oldState;	///< Previous state of the given server
	RFC_SERVER_STATE newState;	///< New state of the given server
} RFC_STATE_CHANGE;

typedef void (SAP_API* RFC_SERVER_STATE_CHANGE_LISTENER)(RFC_SERVER_HANDLE serverHandle, RFC_STATE_CHANGE* stateChange);

/** \struct _RFC_SERVER_MONITOR_DATA
* \ingroup autoserver
*
* Allows to retrieve monitoring information about all busy or idle connections of an automated RFC Server via RfcGetServerConnectionMonitorData().
*/
typedef struct _RFC_SERVER_MONITOR_DATA{
	RFC_ATTRIBUTES* clientInfo;				///< Pointer to an RFC_ATTRIBUTES structure containing information about this particular client connection.
	int isActive;							///< 1, if this connection is currently processing a call, 0, if it is idle.
	int isStateful;							///< If this connection is currently processing a call, this flag indicates, whether it is a stateful or stateless call: 0 = stateless, 1 = stateful.
	SAP_UC functionModuleName[128];			///< Name of the ABAP function module currently being processed over this connection (if the connection is currently active), or empty (if the connection is idle).
	time_t lastActivity;					///< Point of time of the last activity on this connection (if the connection is currently idle), or not used (if the connection is busy).
} RFC_SERVER_MONITOR_DATA;


/** \struct _RFC_TRANSACTION_HANDLE
 * \ingroup transaction
 *
 * Handle to a data container for a tRFC/qRFC LUW.
 * Can be filled with several RFC_FUNCTION_HANDLEs.
 */
typedef struct _RFC_TRANSACTION_HANDLE {void* handle;} *RFC_TRANSACTION_HANDLE;

/** \struct _RFC_UNIT_HANDLE
 * \ingroup bgrfc
 *
 * Handle to a data container for a bgRFC LUW.
 * Can be filled with several RFC_FUNCTION_HANDLEs.
 */
typedef struct _RFC_UNIT_HANDLE {void* handle;} *RFC_UNIT_HANDLE;

/** \struct _RFC_CONNECTION_PARAMETER
 * \ingroup connection
 *
 * Structure used for connecting to a backend system via RfcOpenConnection() or
 * RfcRegisterServer(). For a list of supported parameters see these two functions or the file sapnwrfc.ini, which gives a complete list of all possible connection parameters.
 */
typedef struct _RFC_CONNECTION_PARAMETER
{
    const SAP_UC * name;	///< The name of the connection parameter, like ashost, user, client.
    const SAP_UC * value;	///< The value of the given parameter.
}RFC_CONNECTION_PARAMETER,*P_RFC_CONNECTION_PARAMETER;

/** \struct _RFC_FIELD_DESC
 * \ingroup repository
 *
 * Structure for reading (RfcGetFieldDescByIndex() or RfcGetFieldDescByName())
 * or defining (RfcAddTypeField()) the properties of a field in a structure/table.
 */
typedef struct _RFC_FIELD_DESC
{
	RFC_ABAP_NAME	name;		///< Field name, null-terminated string
	RFCTYPE		type;			///< Field data type
    /*SAPUNICODEOK_MIXEDLEN*/
	unsigned	nucLength;		///< Field length in bytes in a 1-byte-per-SAP_CHAR system
    /*SAPUNICODEOK_MIXEDLEN*/
	unsigned	nucOffset;		///< Field offset in bytes in a 1-byte-per-SAP_CHAR system
    /*SAPUNICODEOK_MIXEDLEN*/
	unsigned	ucLength;		///< Field length in bytes in a 2-byte-per-SAP_CHAR system
    /*SAPUNICODEOK_MIXEDLEN*/
	unsigned	ucOffset;		///< Field offset in bytes in a 2-byte-per-SAP_CHAR system
	unsigned    decimals;		///< If the field is of type "packed number" (BCD), this member gives the number of decimals.
	RFC_TYPE_DESC_HANDLE typeDescHandle; ///< Pointer to an RFC_STRUCTURE_DESC structure for the nested sub-type if the type field is RFCTYPE_STRUCTURE or RFCTYPE_TABLE */
	void* extendedDescription;	///< Not used by the NW RFC library. This parameter can be used by applications that want to store additional information in the repository (like F4 help values, e.g.).
}RFC_FIELD_DESC,*P_RFC_FIELD_DESC;

/** \enum _RFC_DIRECTION
 * \ingroup repository
 *
 * Used in #RFC_PARAMETER_DESC::direction for specifying the direction of a function module parameter.
 */
typedef enum _RFC_DIRECTION
{
	RFC_IMPORT   = 0x01,					///< Import parameter. This corresponds to ABAP IMPORTING parameter.
	RFC_EXPORT   = 0x02,					///< Export parameter. This corresponds to ABAP EXPORTING parameter.
	RFC_CHANGING = RFC_IMPORT | RFC_EXPORT,	///< Import and export parameter. This corresponds to ABAP CHANGING parameter.
	RFC_TABLES    = 0x04 | RFC_CHANGING		///< Table parameter. This corresponds to ABAP TABLES parameter.
}RFC_DIRECTION;

/** \struct _RFC_PARAMETER_DESC
 * \ingroup repository
 *
 * Structure for reading (RfcGetParameterDescByIndex() or RfcGetParameterDescByName())
 * or defining (RfcAddParameter()) the properties of a parameter in a function module.
 */
typedef struct _RFC_PARAMETER_DESC
{
	RFC_ABAP_NAME	name;		///< Parameter name, null-terminated string
	RFCTYPE		type;			///< Parameter data type
	RFC_DIRECTION direction;	///< Specifies whether the parameter is an input, output or bi-directional parameter
	unsigned	nucLength;		///< Parameter length in bytes in a 1-byte-per-SAP_CHAR system
	unsigned	ucLength;		///< Parameter length in bytes in a 2-byte-per-SAP_CHAR system
	unsigned    decimals;		///< Gives the number of decimals in case of a packed number (BCD)
	RFC_TYPE_DESC_HANDLE typeDescHandle;	///< Handle to the structure definition in case this parameter is a structure or table
	RFC_PARAMETER_DEFVALUE defaultValue;	///< Default value as defined in SE37
	RFC_PARAMETER_TEXT parameterText;		///< Description text of the parameter as defined in SE37. Null-terminated string.
	RFC_BYTE     optional;		///< Specifies whether this parameter is defined as optional in SE37. 1 is optional, 0 non-optional
	void* extendedDescription;	///< This field can be used by the application programmer (i.e. you) to store arbitrary extra information.
}RFC_PARAMETER_DESC,*P_RFC_PARAMETER_DESC;

/** \struct _RFC_EXCEPTION_DESC
 * \ingroup repository
 *
 * Structure for reading (RfcGetExceptionDescByIndex() or RfcGetExceptionDescByName())
 * or defining (RfcAddException()) the properties of an exception key in a function module.
 */
typedef struct _RFC_EXCEPTION_DESC
{
    SAP_UC key[128];		///< Exception key
    SAP_UC message[512];	///< Error message (exception text as defined in SE37)
} RFC_EXCEPTION_DESC, *P__RFC_EXCEPTION_DESC;


/** \enum _RFC_CLASS_ATTRIBUTE_TYPE
 * \ingroup repository
 *
 * Determines the type of an ABAP Object attribute.
 */
typedef enum _RFC_CLASS_ATTRIBUTE_TYPE {
	RFC_CLASS_ATTRIBUTE_INSTANCE,	///< Instance attribute (object member)
	RFC_CLASS_ATTRIBUTE_CLASS,		///< Class attribute (global)
	RFC_CLASS_ATTRIBUTE_CONSTANT	///< A constant
} RFC_CLASS_ATTRIBUTE_TYPE;

typedef RFC_CHAR RFC_CLASS_ATTRIBUTE_DEFVALUE[30+1];	///< Default value of a function module parameter. (null-terminated)
typedef RFC_CHAR RFC_CLASS_NAME[30+1];	///< Default value of a function module parameter. (null-terminated)
typedef RFC_CHAR RFC_CLASS_ATTRIBUTE_DESCRIPTION[511+1];	///< Default value of a function module parameter. (null-terminated)

/** \struct _RFC_CLASS_ATTRIBUTE_DESC
 * \ingroup repository
 *
 * Structure for reading (RfcGetParameterDescByIndex() or RfcGetParameterDescByName())
 * or defining (RfcAddParameter()) the properties of a parameter in a function module.
 */
typedef struct _RFC_CLASS_ATTRIBUTE_DESC
{
	RFC_ABAP_NAME	name;		///< Attribute name, null-terminated string
	RFCTYPE		type;			///< Attribute data type
	unsigned	nucLength;		///< Attribute length in bytes in a 1-byte-per-SAP_CHAR system
	unsigned	ucLength;		///< Attribute length in bytes in a 2-byte-per-SAP_CHAR system
	unsigned    decimals;		///< Gives the number of decimals in case this attribute is a packed number (BCD)
	RFC_TYPE_DESC_HANDLE typeDescHandle;	///< Handle to the structure definition in case this attribute is a structure or table
    RFC_CLASS_ATTRIBUTE_DEFVALUE defaultValue;	///< Default value as defined in SE37
	RFC_CLASS_NAME declaringClass; ///< Declaring class
	RFC_CLASS_ATTRIBUTE_DESCRIPTION description; ///< Attribute description, null terminated, may be null
	unsigned isReadOnly; ///< This attribute is read only if isReadOnly != 0
	RFC_CLASS_ATTRIBUTE_TYPE attributeType; ///< The attribute type tells you, whether this attribute is an instance attribute, a class attribute or a constant.
	void* extendedDescription;	///< This field can be used by the application programmer (i.e. you) to store arbitrary extra information.
}RFC_CLASS_ATTRIBUTE_DESC,*P_RFC_CLASS_ATTRIBUTE_DESC;


#ifdef __cplusplus
extern "C"
{
#endif
	typedef RFC_RC (SAP_API* RFC_SERVER_FUNCTION)(RFC_CONNECTION_HANDLE rfcHandle, RFC_FUNCTION_HANDLE funcHandle, RFC_ERROR_INFO* errorInfo);
	typedef RFC_RC (SAP_API* RFC_ON_CHECK_TRANSACTION)(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const *tid);
	typedef RFC_RC (SAP_API* RFC_ON_COMMIT_TRANSACTION)(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const *tid);
	typedef RFC_RC (SAP_API* RFC_ON_ROLLBACK_TRANSACTION)(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const *tid);
	typedef RFC_RC (SAP_API* RFC_ON_CONFIRM_TRANSACTION)(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const *tid);

	typedef RFC_RC (SAP_API* RFC_FUNC_DESC_CALLBACK)(SAP_UC const *functionName, RFC_ATTRIBUTES rfcAttributes, RFC_FUNCTION_DESC_HANDLE *funcDescHandle);
    typedef RFC_RC (SAP_API* RFC_PM_CALLBACK)(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const *functionName, SAP_RAW *eppBuffer, size_t eppBufferSize, size_t *eppLength); 

	typedef RFC_RC (SAP_API* RFC_ON_CHECK_UNIT)(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNIT_IDENTIFIER const *identifier);
	typedef RFC_RC (SAP_API* RFC_ON_COMMIT_UNIT)(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNIT_IDENTIFIER const *identifier);
	typedef RFC_RC (SAP_API* RFC_ON_ROLLBACK_UNIT)(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNIT_IDENTIFIER const *identifier);
	typedef RFC_RC (SAP_API* RFC_ON_CONFIRM_UNIT)(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNIT_IDENTIFIER const *identifier);
	typedef RFC_RC (SAP_API* RFC_ON_GET_UNIT_STATE)(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNIT_IDENTIFIER const *identifier, RFC_UNIT_STATE* unitState);
	typedef RFC_RC (SAP_API* RFC_ON_PASSWORD_CHANGE)(SAP_UC const *sysId, SAP_UC const *user, SAP_UC const *client,
														SAP_UC *password,  unsigned passwordLength,
														SAP_UC *newPassword, unsigned newPasswordLength,
														RFC_ERROR_INFO* cause);
	typedef RFC_RC (SAP_API* RFC_ON_AUTHORIZATION_CHECK)(RFC_CONNECTION_HANDLE rfcHandle, RFC_SECURITY_ATTRIBUTES *secAttributes, RFC_ERROR_INFO* errorInfo);
    typedef RFC_RC (SAP_API* RFC_ON_AUTHENTICATION_CHECK)(RFC_ATTRIBUTES rfcAttributes, RFC_AUTHENTICATION_HANDLE authenticationHandle, RFC_ERROR_INFO* errorInfo); 

    /* ***********************************************************************/
    /*                                                                       */
    /*  General API & Utilities                                              */
    /*                                                                       */
    /* ***********************************************************************/

	/**
	 * \brief  Initialization of internal variables
	 * \ingroup general
	 *
	 * Obsolete.
	 * %RfcInit() no longer needs to be called explicitly. The RFC library does
	 * this automatically on DLL load.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInit(void);

	/**
	 * \brief  Freeing of internal variables
	 * \ingroup general
	 *
	 * Obsolete.
	 * The RFC library does this automatically on DLL unload.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcCleanup(void);

	/**
	 * \brief  Get information about currently loaded sapnwrfc library.
	 * \ingroup general
	 *
	 * Fills the provided unsigneds with the SAP release values, e.g. *majorVersion = 7500,
	 * *minorVersion = 0, *patchLevel = 44.
	 * \out *majorVersion 
	 * \out *minorVersion 
	 * \out *patchLevel 
	 * \return Version information in string format.
	 * \warning Don't free the returned SAP_UC pointer, it's static memory...
	 */
	DECL_EXP const SAP_UC* SAP_API RfcGetVersion(unsigned* majorVersion, unsigned* minorVersion, unsigned* patchLevel);

	/**
	 * \brief This function is intended to be used by SAP Make-factory only. Please DO NOT use it!  
	 * \ingroup general
	 */
	DECL_EXP RFC_RC SAP_API RfcGetVersionInternal(void);

	/**
	 * \brief  Sets the directory in which to search for the sapnwrfc.ini file.
	 * \ingroup general
	 *
	 * By default the sapnwrfc library searches for the sapnwrfc.ini in the current
	 * working directory of the process. If you want to keep it in a different directory,
	 * use this function to tell the sapnwrfc library about the new path.
	 * \note After you have changed the directory, the NW RFC lib automatically loads
	 * the contents of the new sapnwrfc.ini file from that directory.
	 *
	 * \in *pathName The full (absolute) path of the directory, in which the sapnwrfc
	 * library should look for the sapnwrfc.ini file. A path relative to the current
	 * working directory of the process also works.
	 * \out *errorInfo Detail information in case anything goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetIniPath(const SAP_UC* pathName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Reloads the contents of the sapnwrfc.ini file into memory.
	 * \ingroup general
	 *
	 * Searches the directory given by RfcSetIniPath() (or the current working directory)
	 * for the file sapnwrfc.ini and loads its contents into memory. Reloading the sapnwrfc.ini
	 * file is only necessary after the file has been manually edited
	 * If you want to use a sapnwrfc.ini file in a different location, consider using %RfcSetIniPath().
	 * 
	 * Note: If a file with the name sapnwrfc.ini does not exist in the given directory, this is not
	 * considered an error! Default settings are used in this case.
	 *
	 * \out *errorInfo Detail information in case anything goes wrong. 
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcReloadIniFile(RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the current trace level of the specified RFC connection or destination to the new value.
	 * \ingroup general
	 *
	 * \note If both of connection and destination are NULL, this function sets the "global"
	 * trace level. See below.
     * \in connection A handle to a currently open RFC connection (client or server connection).
	 * The new trace level will be effective immediately.
     * \in *destination Null-terminated string specifying a client or server destination as defined
	 * via a DEST=... entry in sapnwrfc.ini. The new trace level will be used for new connections
	 * to that destination opened after the %RfcSetTraceLevel() call. Already existing connections to
	 * that destination will not be effected.
     * \in traceLevel The new trace level. Must be between 0 and 4. The meaning of those four values
	 * is as follows:
	 * - 0: Off. Only severe errors are logged to the dev_rfc.trc file.
	 * - 1: Brief. All API calls (except for the setter and getter functions) and important attributes
	 *      like codepages, RFC headers, logon parameters are traced. Trace is written to a file named
	 *      rfc&lt;pid&gt;.trc or rfc&lt;pid&gt;_&lt;tid&gt;.trc, depending on whether tracing is done
	 *      on a "per-process" basis or a "per-thread" basis. &lt;pid&gt; is the current process ID,
	 *      &lt;tid&gt; the current thread ID.
	 * - 2: Verbose. In addition to 1, the values of the "scalar" RFC parameters as well as the contents
	 *      of the network containers are traced. Scalar parameters are primitive types (CHAR, INT, FLOAT, etc)
	 *      and flat structures.
	 * - 3: Detailed. In addition to 2 the contents of nested structures and tables and hexdumps
	 * - 4: Full. In addition to 3 all API calls of setter and getter functions and table operations
	 *      are traced.
	 * \out *errorInfo Detail information in case the specified connection or destination does not exist.
	 * \return RFC_OK, RFC_INVALID_HANDLE or RFC_INVALID_PARAMETER
	 *
	 * \note In general RFC trace can be activated/deactivated in 6 different ways:
	 * - By setting the parameter RFC_TRACE=[0|1|2|3|4] in the DEFAULT section of the sapnwrfc.ini file.
	 *   This value applies to all destinations, for which no explicit trace level has been set.
	 *   ("Global" trace level.)
	 * - By setting the parameter TRACE=[0|1|2|3|4] in a specific destination section of sapnwrfc.ini.
	 *   it applies to that destination only and overrules the "global" trace level from the DEFAULT section.
	 * - By setting the environment variable RFC_TRACE=[0|1|2|3|4]. This overrules the setting from the
	 *   DEFAULT section of sapnwrfc.ini.
	 * - Via %RfcSetTraceLevel(). If connection and destination are NULL, this function sets the global
	 *   trace level and overrules the value from the DEFAULT section of sapnwrfc.ini as well as the environment
	 *   variable RFC_TRACE. If connection is non-NULL, it sets the trace level for the current connection only,
	 *   and if destination is non-NULL, it sets the trace level for that destination, overruling the value from
	 *   this destination's section in the sapnwrfc.ini file.
	 * - By passing a {name=TRACE, value=[0|1|2|3|4]} pair in the RFC_CONNECTION_PARAMETER array used in
	 *   RfcOpenConnection(), RfcRegisterServer() or RfcStartServer(). If that RFC_CONNECTION_PARAMETER array
	 *   also contains a {name=DEST, value=...} pair, the trace parameter from the array overrules the value
	 *   from this destination's sapnwrfc.ini section.
	 * - In case the program is a server program: by activating the trace flag for the corresponding destination
	 *   in SM59. The trace setting on backend side is then "inherited" by the external side.
	 *
	 * \note For more information on trace settings see the sample sapnwrfc.ini file contained in the demo folder.
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTraceLevel(RFC_CONNECTION_HANDLE connection, SAP_UC* destination, unsigned traceLevel, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Changes the character encoding to be used in trace files.
	 * \ingroup general
	 *
	 * This function has the same effect as the sapnwrfc.ini parameter RFC_TRACE_ENCODING.
	 * See the documentation of that parameter in the sample ini file contained in the
	 * /demo directory of the NW RFC SDK.
	 *
	 * \note This API call affects only new trace files that will be opened after the call.
	 * The character encoding of already existing trace files is not changed in order to
	 * prevent confusion and garbage data...
	 *
	 *
	 * \in *traceEncoding The new encoding. Possible values are "UTF-16", "UTF-8" and
	 * "DEFAULT". On Windows UTF-16 is recommended for faster performance. "DEFAULT" corresponds
	 * to the operating system's default character encoding, which is CP1252 or ISO-8859-1 on
	 * most Windows systems and UTF-8 on most Linux systems.
	 * \out *errorInfo Detail information in case of an invalid traceEncoding input.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTraceEncoding(SAP_UC* traceEncoding, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Changes the directory where the NW RFC lib should write trace files.
	 * \ingroup general
	 *
	 * This function has the same effect as the sapnwrfc.ini parameter RFC_TRACE_DIR.
	 * See the documentation of that parameter in the sample ini file contained in the
	 * /demo directory of the NW RFC SDK.
	 *
	 * \note This API call affects only new trace files that will be opened after the call.
	 * The directory of already existing trace files is not changed in order to
	 * prevent confusion and garbage data...
	 *
	 *
	 * \in *traceDir The new directory. Can be an absolute or relative path name.
	 * The directory needs to exist prior to calling this API. The NW RFC lib will not
	 * attempt to create non-existing directories.
	 * \out *errorInfo Detail information in case of an invalid traceEncoding input.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTraceDir(SAP_UC* traceDir, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Changes the way the NW RFC lib writes trace files.
	 * \ingroup general
	 *
	 * This function has the same effect as the sapnwrfc.ini parameter RFC_TRACE_TYPE.
	 * See the documentation of that parameter in the sample ini file contained in the
	 * /demo directory of the NW RFC SDK.
	 *
	 * \note This API call closes currently open trace files and then changes to
	 * "one file per process" or one "file per thread".
	 * If the NW RFC lib is already using the given trace type, it does nothing.
	 *
	 *
	 * \in *traceType Must be either "PROCESS" or "THREAD".
	 * \out *errorInfo Detail information in case of an invalid traceEncoding input.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTraceType(SAP_UC* traceType, RFC_ERROR_INFO* errorInfo);

	
    /**
     * \brief  Sets the global CPIC trace level used by the underlying CPIC libabry to write CPIC tracing information
     * to the CPIC trace file cpic_<pid>.trc, where pid is the process ID of the current process. The CPIC trace file
     * is located in the same directory where the RFC trace files are located.
     * \ingroup general
	 *
	 * This function has the same effect as the sapnwrfc.ini parameter CPIC_TRACE_LEVEL.
	 * See the documentation of that parameter in the sample ini file contained in the
	 * /demo directory of the NW RFC SDK.
     *
     * \in traceLevel Must be a value between 0 to 3, where 0 turns tracing off.
	 * \out *errorInfo Detail information in case of an error.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetCpicTraceLevel(unsigned traceLevel, RFC_ERROR_INFO* errorInfo);


    /**
     * \brief Activates the CPIC keepalive
     *
     * \in timeout Must be a value between 10 and 3600, where 0 turns the cpic keepalive off.
     * \out *errorInfo Detail information in case of an error.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcSetCpicKeepalive(unsigned timeout, RFC_ERROR_INFO* errorInfo);

    /**
    * \brief  Sets the global Websocket trace level used by the underlying NI libabry to write tracing information
    * to the trace file ws_rfc_<pid>.trc, where pid is the process ID of the current process. The NI trace file
    * is located in the same directory where the RFC trace files are located.
    * \ingroup general
    *
    * This function has the same effect as the sapnwrfc.ini parameter RFC_SOCKET_TRACE.
    * See the documentation of that parameter in the sample ini file contained in the
    * /demo directory of the NW RFC SDK.
    * Nevertheless this API cannot set a trace level below the global socket trace level set by environment variable 
    * or the ini file.
    *
    * \in traceLevel Must be a value between 0 to 3, where 0 turns tracing off.
    * \out *errorInfo Detail information in case of an error.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcSetSocketTraceLevel(unsigned traceLevel, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Sets the absolute path to the sapcrypto library to enable TLS encryption via Websocket Rfc.
    * \ingroup general
    *
    * The parameter pathToLibrary needs also to contain the name of the library.
    * This function has the same effect as the sapnwrfc.ini parameter TLS_SAPCRYPTOLIB.
    * This API cannot reset a new path to the library during runtime. Once set, the path is definitive. 
    *
    * \in *pathToLibrary Absolute path to library (.so or .dll).
    * \out *errorInfo Detail information in case of an error.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcLoadCryptoLibrary(const SAP_UC* const pathToLibrary, RFC_ERROR_INFO* errorInfo);
	/**
	* \brief  Sets the global idle time interval of a Websocket server connection in seconds after which
	* a keep alive Websocket ping packet is sent.
	* \ingroup general
	*
	* This function has the same effect as the sapnwrfc.ini parameter RFC_WEBSOCKET_PING_INTERVAL.
	* The default value is 300; valid values are 0 [off] and a range from 10 [ten seconds] to 86400 [one day].
	*
	* \in pingInterval Interval in seconds.
	* \out *errorInfo Detail information in case of an error.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcSetWebsocketPingInterval(unsigned pingInterval, RFC_ERROR_INFO* errorInfo);

	/**
	* \brief  Sets the global timeout for a WebSocket keep alive ping reply packet in seconds.
	* \ingroup general
	*
	* This function has the same effect as the sapnwrfc.ini parameter RFC_WEBSOCKET_PONG_TIMEOUT.
	* If no such so-called pong packet is received from the communication partner as a reply to a previously sent
	* WebSocket keep alive ping packet within this timeout period, the connection is considered as broken and will be closed.
	* The default value is 60; valid values are 0 [off] and a range from 10 [ten seconds] to 3600 [one hour].
	* The timeout value should be set lower than the ping interval of the server, so only one ping is active at a time.
	*
	* \in pongTimeout Timeout in seconds.
	* \out *errorInfo Detail information in case of an error.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcSetWebsocketPongTimeout(unsigned pongTimeout, RFC_ERROR_INFO* errorInfo);

    /**
    * \brief  Sets the maximum size of the trace file, after which the current file is closed and "rolled over" to a new file.
    * \ingroup general
    *
    * This function has the same effect as the sapnwrfc.ini parameter RFC_TRACE_MAX_FILE_SIZE. By default
    * two files of a maximum of 512 MB are stored.
    * However this function cannot set the size below a minimum value of 20 MB or the value set by RFC_TRACE_MAX_FILE_SIZE 
    * from the sapnwrfc.ini.
    * As unit of measure you can use "M" for Megabytes or "G" for Gigabytes, for example 1024 and M.
    *
    * \in size Size in specified unit
    * \in unit Unit of measurement
    * \out *errorInfo Detail information in case of an error.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcSetMaximumTraceFileSize(unsigned size, SAP_UC unit, RFC_ERROR_INFO* errorInfo);

    /**
    * \brief  Sets the maximum size of stored old trace files, after which the current file is closed and "rolled over" to a new file.
    * \ingroup general
    *
    * This function has the same effect as the sapnwrfc.ini parameter RFC_TRACE_MAX_STORED_FILES.
    * An additional "roll" to a new file after the maximum is reached, triggers a deletion of the oldest file.
    * The old stored files are marked with the opening timestamp in the file name, when a "roll over" is done.
    * By default two files are stored. The current trace file is not yet marked with the time stamp.
    * However this function cannot set the size to zero, (it will result in an error,) or to a value lower than the one set 
    * by RFC_TRACE_MAX_STORED_FILES from the sapnwrfc.ini.
    * By setting this value to -1, the limit is disabled and and an infinite amount of concurrent files can
    * be kept, i.e. no files will be deleted by the NW RFC library.
    * \warning Attention: Lowering the value might delete some old files, if there are currently more stored 
    * files than permitted by the new (lower) value.
    *
    * \in numberOfFiles Maximum size of stored old trace
    * \out *errorInfo Detail information in case of an error.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcSetMaximumStoredTraceFiles(int numberOfFiles, RFC_ERROR_INFO* errorInfo);

	/**
     * \brief  Converts data in UTF-8 format to SAP_UC strings.
     * \ingroup general
     * 
     * \in *utf8 Pointer to UTF-8 data to be converted
     * \in utf8Length Number of bytes to convert
     * \out *sapuc Pre-allocated output buffer, which will receive the result. Output will be null-terminated.
     * \inout *sapucSize Needs to be filled with the size of the given output buffer in SAP_UC characters.
	 * If the given buffer turns out to be too small (return code RFC_BUFFER_TOO_SMALL), it will be filled
	 * with the required buffer size that would be necessary to convert the given input data.
     * \out *resultLength If the output buffer was large enough, resultLength will be filled with the
	 * length of the output string in SAP_UC characters.
     * \out *errorInfo Will be filled with additional error information in case of an error.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcUTF8ToSAPUC(const RFC_BYTE *utf8, unsigned utf8Length,  SAP_UC *sapuc,  unsigned *sapucSize, unsigned *resultLength, RFC_ERROR_INFO *errorInfo);

	/**
	 * \brief  Converts data in SAP_UC format to UTF-8 format
	 * \ingroup general
	 * 
	 * \in *sapuc Pointer to SAP_UC data to be converted
	 * \in sapucLength Number of characters to convert
	 * \out *utf8 Pre-allocated output buffer, which will receive the result. Output will be null-terminated.
	 * \inout *utf8Size Needs to be filled with the size of the given output buffer in bytes.
	 * If the given buffer turns out to be too small (return code RFC_BUFFER_TOO_SMALL), it will be filled
	 * with the required buffer size that would be necessary to convert the given input data.
	 * \out *resultLength If the output buffer was large enough, resultLength will be filled with the
	 * length of the output string in bytes.
	 * \out *errorInfo Will be filled with additional error information in case of an error.
	 * \return RFC_OK or RFC_BUFFER_TOO_SMALL
	 */
	DECL_EXP RFC_RC SAP_API RfcSAPUCToUTF8(const SAP_UC *sapuc,  unsigned sapucLength, RFC_BYTE *utf8, unsigned *utf8Size,  unsigned *resultLength, RFC_ERROR_INFO *errorInfo);

    /**
     * \brief  Converts an RFC_RC return code to a human readable string for logging purposes.
     * \ingroup general
     * 
     * \in rc Return code to covert to string
     * \return String representation of the return code
	 * \warning Don't free the returned SAP_UC pointer -- its's static memory...
     */
    DECL_EXP const SAP_UC* SAP_API RfcGetRcAsString(RFC_RC rc);

    /**
     * \brief  Converts an RFCTYPE data type indicator to a human readable string for logging purposes.
     * \ingroup general
     * 
     * \in type Data type indicator to convert
     * \return String representation of the type
	 * \warning Don't free the returned SAP_UC pointer -- its's static memory...
     */
    DECL_EXP const SAP_UC* SAP_API RfcGetTypeAsString(RFCTYPE type);

    /**
     * \brief  Converts an RFC_DIRECTION direction indicator to a human readable string for logging purposes.
     * \ingroup general
     * 
     * \in direction Direction indicator to convert
     * \return String representation of the direction
	 * \warning Don't free the returned SAP_UC pointer -- its's static memory...
     */
    DECL_EXP const SAP_UC* SAP_API RfcGetDirectionAsString(RFC_DIRECTION direction);

	/**
	* \brief  Converts an RFC_SERVER_STATE state indicator to a human readable string for logging purposes.
	* \ingroup general
	*
	* \in serverState State indicator to convert
	* \return String representation of the state
	* \warning Don't free the returned SAP_UC pointer -- its's static memory...
	*/
	DECL_EXP const SAP_UC* SAP_API RfcGetServerStateAsString(RFC_SERVER_STATE serverState);

	/**
	* \brief  Converts an RFC_SESSION_EVENT to a human readable string for logging purposes.
	* \ingroup general
	*
	* \in sessionEvent Session event to convert
	* \return String representation of the event
	* \warning Don't free the returned SAP_UC pointer -- its's static memory...
	*/
	DECL_EXP const SAP_UC* SAP_API RfcGetSessionEventAsString(RFC_SESSION_EVENT sessionEvent);

	/**
     * \brief  Converts a 2-char SAP language code to the 1-char SAP language code.
     * \ingroup general
     * 
     * \in *laiso Pointer to the 2-char array with SAP LAISO code to convert
     * \out *lang Pointer to the 1 char for SAP SPRAS key
	 * \out *errorInfo Will be filled with additional error information in case of an error.
     * \return RFC_RC RFC_OK or RFC_INVALID_PARAMETER in case of an error
	 * \warning The SAP LAISO code is not 100% ISO639_1 compliant - see also ABAP table T002X columns SPRAS/LAISO for details
	 */
    DECL_EXP RFC_RC SAP_API RfcLanguageIsoToSap (const SAP_UC *laiso, SAP_UC *lang, RFC_ERROR_INFO* errorInfo);
	
	/**
     * \brief  Converts a 1-char SAP language key to the 2-char SAP language code.
     * \ingroup general
     * 
     * \in *lang Pointer to the 1 char with SAP SPRAS key to convert
     * \out *laiso Pointer to the 2-char array for SAP LAISO code
	 * \out *errorInfo Will be filled with additional error information in case of an error.
     * \return RFC_RC RFC_OK or RFC_INVALID_PARAMETER in case of an error
	 * \warning The SAP LAISO code is not 100% ISO639_1 compliant - see also ABAP table T002X columns SPRAS/LAISO for details
	 */
    DECL_EXP RFC_RC SAP_API RfcLanguageSapToIso (const SAP_UC *lang, SAP_UC *laiso, RFC_ERROR_INFO* errorInfo);



    /* ***********************************************************************/
    /*                                                                       */
    /*  Connection related API                                               */
    /*                                                                       */
    /* ***********************************************************************/

	/**
	 * \brief  Returns a list of names of all SAP Systems maintained in SAPLogon (saplogon.ini or SAPUILandscape.xml).
	 * \ingroup connection
	 *
	 * On Windows systems, where SAPLogon is installed, the logon parameters defined in saplogon.ini can be used for opening connections
	 * to those backend systems. This routine retrieves a list of all available SAP systems. Each key in the list can be used as a value
	 * for RFC_CONNECTION_PARAMETER.value, where RFC_CONNECTION_PARAMETER.name = "SAPLOGON_ID".
	 * For more information see the documentation of the SAPLOGON_ID parameter in the sample sapnwrfc.ini file.
	 *
	 * If the API returns successfully, you should call RfcFreeSaplogonEntries() with the same inputs, once you no longer need the
	 * SAPLogon IDs, so that the memory occupied by them can be cleaned up.
	 *
	 * Sample code illustrating how to use the SAPLogon IDs: \code
	 * SAP_UC** logonIDList;
	 * unsigned numEntries;
	 * RfcGetSaplogonEntries(&logonIDList, &numEntries, &errorInfo);
	 *
	 * if (errorInfo.code == RFC_OK){
	 * 	   for (unsigned i=0; i<numEntries; ++i) printfU(cU("%s\n"), logonIDList[i]);
	 * }
	 * RfcFreeSaplogonEntries(&logonIDList, &numEntries, &errorInfo);
	 * \endcode
	 *
	 * \out ***saplogonIDList Receives a pointer to a SAP_UC* array containing the SAPLogon IDs.
	 * \out *numSaplogonIDs Will be filled with the number of SAPLogon IDs in the list.
	 * \out *errorInfo Returns more error details, if the list of saplogon.ini keys could not be retrieved.
	 * \return RFC_MEMORY_INSUFFICIENT, if unable to malloc memory for the ID list; RFC_NOT_FOUND, if saplogon.ini could not be found on that system or is empty.
	 */
	DECL_EXP RFC_RC SAP_API RfcGetSaplogonEntries(SAP_UC*** saplogonIDList, unsigned* numSaplogonIDs, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Frees a list of SAPLogon IDs obtained from RfcGetSaplogonEntries().
	 * \ingroup connection
	 *
	 * When you no longer need the SAPLogon IDs obtained from RfcGetSaplogonEntries(), you should call this function with the same
	 * arguments that got filled by RfcGetSaplogonEntries(). This will free any internal memory occupied by the list of SAPLogon IDs.
	 *
	 * \inout ***saplogonIDList Points to an SAP_UC* array that was previously filled by RfcGetSaplogonEntries(). Will be set to NULL.
	 * \inout *numSaplogonIDs Points to the length of the SAPLogon ID list. Will be set to 0.
	 * \out *errorInfo Returns more error details, if something goes wrong.
	 * \return Nothing that can go wrong here really.
	 */
	DECL_EXP RFC_RC SAP_API RfcFreeSaplogonEntries(SAP_UC*** saplogonIDList, unsigned* numSaplogonIDs, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Retrieves all connection parameters corresponding to the given ID from the saplogon.ini or SAPUILandscape.xml file.
	* \ingroup connection
	*
	* The ID needs to be one of those returned by RfcGetSaplogonEntries(). It is the same as can also be used as connection
	* parameter SAPLOGON_ID.
	*
	* \in *saplogonID A SAPLogon ID uniquely identifying a certain saplogon.ini or SAPUILandscape.xml entry.
	* \out **entryParameters Receives a pointer to a RFC_CONNECTION_PARAMETER array containing the parameters of the given SAPLogon ID.
	* \out *numParameters Will be filled with the number of connection parameters in the array.
	* \out *errorInfo Returns more error details, if something goes wrong, e.g. out of memory or SAPLogon ID cannot be found.
	* \return Nothing that can go wrong here really.
	*/
	DECL_EXP RFC_RC SAP_API RfcGetSaplogonEntry(SAP_UC* saplogonID, RFC_CONNECTION_PARAMETER** entryParameters, unsigned* numParameters, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Frees an array of connection parameters obtained from RfcGetSaplogonEntry().
	* \ingroup connection
	*
	* When you no longer need the connection parameters obtained from RfcGetSaplogonEntries(), you should call this function with the same
	* arguments that got filled by RfcGetSaplogonEntry(). This will free any internal memory occupied by the array of parameters.
	*
	* \inout **entryParameters Points to an RFC_CONNECTION_PARAMETER array that was previously filled by RfcGetSaplogonEntry(). Will be set to NULL.
	* \inout *numParameters Points to the length of the connection parameter array. Will be set to 0.
	* \out *errorInfo Returns more error details, if something goes wrong.
	* \return Nothing that can go wrong here really.
	*/
	DECL_EXP RFC_RC SAP_API RfcFreeSaplogonEntry(RFC_CONNECTION_PARAMETER** entryParameters, unsigned* numParameters, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Opens an RFC client connection for invoking ABAP function modules in an R/3 backend.
	 * \ingroup connection
	 *
	 * Opens a client connection to an SAP System. The connectionParams may contain the following name-value pairs:
	 * - client, user, passwd, lang, trace
	 *
	 * and additionally one of
	 * -# Direct application server logon: ashost, sysnr.
	 * -# Logon with load balancing: mshost, msserv, sysid, group.\n
	 *    msserv is needed only, if the service of the message server is
	 *    not defined as sapms<SYSID> in /etc/services.
	 *
	 * When logging on with SNC, user&passwd are to be replaced by
	 * - snc_qop, snc_myname, snc_partnername and optionally snc_lib.
	 *
	 * (If snc_lib is not specified, the underlying SNC layer uses the "global" GSS library
	 * defined via environment variable SNC_LIB or SNC_LIB_64.)
	 *
	 * When logging on with SSO Ticket, you can use mysapsso2 instead of user&passwd.
	 * The old SSO format (mysapsso) is no longer supported.
	 *
	 *
	 * Alternatively the connection parameters can be defined in the config file
	 * sapnwrfc.ini. In this case you just pass the parameter dest=... and all
	 * parameters that are missing in the sapnwrfc.ini entry into %RfcOpenConnection().
	 *
	 * For a complete list of logon parameters to be used in connectionParams as well as in the
	 * sapnwrfc.ini file, see the sample sapnwrfc.ini file in the SDK's demo folder.
	 *
	 * If the logon was ok, %RfcOpenConnection() returns a client connection handle, which can be used in RfcInvoke().
	 * Otherwise the return value is NULL and errorInfo contains a detailed error description.
	 * errorInfo->code will be one of:
	 * - RFC_INVALID_PARAMETER			One of the connectionParams was invalid
	 * - RFC_COMMUNICATION_FAILURE		Something is wrong with the network or network settings
	 * - RFC_LOGON_FAILURE				Invalid user/password/ticket/certificate
	 * - RFC_ABAP_RUNTIME_FAILURE		Something is wrong with the R/3 backend
	 * - RFC_MEMORY_INSUFFICIENT		A malloc failed when trying to allocate a temporary buffer
	 *
	 * 
	 * \in *connectionParams An array of RFC_CONNECTION_PARAMETERs with the names as described above
	 * and the values as necessary in your landscape.
	 * \in paramCount Number of parameters in the above array.
	 * \out *errorInfo Returns more error details, if the connect attempt fails.
	 * \return A handle to an RFC client connection that can be used for invoking ABAP function modules in the backend.
	 */
	DECL_EXP RFC_CONNECTION_HANDLE SAP_API RfcOpenConnection(RFC_CONNECTION_PARAMETER const * connectionParams, unsigned paramCount, RFC_ERROR_INFO* errorInfo);

	/** \brief  Registers a server connection at an SAP gateway.
	 * \ingroup connection
	 *
	 * The connectionParams may contain the following name-value pairs:
	 * - gwhost, gwserv, program_id, trace, and the parameters for SNC communication as in RfcOpenConnection().
	 *
	 * Program_id corresponds to an RFC destination in SM59 of type "T" in registration mode.
	 *
	 * For a complete list of logon parameters to be used in connectionParams as well as in the
	 * sapnwrfc.ini file, see the sample sapnwrfc.ini file in the SDK's demo folder.
	 *
	 * If the connection registration was ok, %RfcRegisterServer() returns a server connection handle, which can
	 * be used in RfcListenAndDispatch().
	 * Otherwise the return value is NULL and errorInfo contains information similar to the RfcOpenConnection() case.
	 *
	 * 
	 * \in *connectionParams An array of RFC_CONNECTION_PARAMETERs with the names as described above
	 * and the values as necessary in your landscape.
	 * \in paramCount Number of parameters in the above array.
	 * \out *errorInfo Returns more error details, if the connect attempt fails.
	 * \return A handle to an RFC server connection that can be used for listening for function module requests from the backend.
	 */
	DECL_EXP RFC_CONNECTION_HANDLE SAP_API RfcRegisterServer(RFC_CONNECTION_PARAMETER const * connectionParams, unsigned paramCount, RFC_ERROR_INFO* errorInfo);

	/** \brief  Allows a program to be used as an RFC server which is started by the backend on demand.
	 * \ingroup connection
	 *
	 * This API needs to be called, if the server program is to be started by the R/3 application server.
	 * (RFC destination in SM59 of type "T" in startup mode.)
	 * argc and argv are the inputs of the mainU function. The R/3 application server passes the correct command line to
	 * the program, when starting it up, so you only need to forward these two parameters to %RfcStartServer().
	 * connectionParams is optional and is only needed, if you want to add additional logon parameters to the
	 * ones coming from the command line, e.g for activating trace.
	 *
	 * Like RfcRegisterServer(), the function returns a server connection handle that can be used in RfcListenAndDispatch().
	 * The mechanism of this kind of RFC destination thus works as follows:
	 * -# The R/3 application server opens a telnet connection to the host, where your server program is located, and
	 *    starts the program with the necessary logon parameters. (Or creates a child process, if the startup
	 *    method is "Start on application server".)
	 * -# Your server program calls RfcStartServer, which opens an RFC connection back to the R/3 system.
	 * -# The R/3 system then makes the function call over that RFC connection.
	 *
	 * The main differences of "startup mode" compared to the "registration mode" are:
	 * - Advantage: no logon parameters need to be maintained in the server program. (Unless you want to open
	 *   an additional client connection for looking up function module metadata (RFC_FUNCTION_DESC_HANDLEs) in the
	 *   R/3 DDIC.) 
	 * - Disadvantage: every single function call creates a new process and possibly a remote shell connection in addition to
	 *   the actual RFC connection.
	 *
	 * 
	 * \in argc From mainU() (command line supplied by backend)
	 * \in **argv From mainU() (command line supplied by backend)
	 * \in *connectionParams May optionally contain additional logon parameters
	 * \in paramCount Length of the connection parameter array above
	 * \out *errorInfo Returns more error details, if the connect attempt fails.
	 * \return A handle to an RFC server connection that can be used for listening for function module requests from the backend.
	 */
	DECL_EXP RFC_CONNECTION_HANDLE SAP_API RfcStartServer(int argc, SAP_UC **argv, RFC_CONNECTION_PARAMETER const * connectionParams, unsigned paramCount, RFC_ERROR_INFO* errorInfo);

	/** \brief  Closes an RFC connection
	 * \ingroup connection
	 * 
	 * Can be used to close client connections as well as server connections, when they are no longer needed.
	 *
	 *
	 * \in rfcHandle Connection to be closed
	 * \out *errorInfo Error details in case closing the connection fails. (Can usually be ignored...)
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcCloseConnection(RFC_CONNECTION_HANDLE rfcHandle, RFC_ERROR_INFO* errorInfo);

	/** \brief  Checks an RFC connection
	 * \ingroup connection
	 * 
	 * Can be used to check whether a client/server connection has already been closed,
	 * or whether the NW RFC library still "considers" the connection to be open.
	 * Note that this does not guarantee that the connection is indeed still alive:
	 * A firewall may silently have closed the connection without notifying the endpoints.
	 * If you want to find out, whether the connection is still alive, you'll have to
	 * use the more expensive RfcPing().
	 *
	 *
	 * \in rfcHandle Connection to be checked
	 * \out *isValid 1, if the connection is still found in the internal connection management, 0 otherwise.
	 * \out *errorInfo Error details in case the connection is invalid.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcIsConnectionHandleValid(RFC_CONNECTION_HANDLE rfcHandle, int* isValid, RFC_ERROR_INFO *errorInfo);

    /** \brief  Cancels the RFC call which is currently being called over the given RFC connection and closes the connection 
    * \ingroup connection
    *
    * Can be used only on an RFC client connection and needs to be called from a different thread than the one currently executing the RFC call.
    *
    *
    * \in rfcHandle RFC client connection which is currently blocked in RfcInvoke().
    * \out *errorInfo Error details in case canceling fails. (Can usually be ignored...)
    * \return RFC_OK, if cancel was requested; RFC_ILLEGAL_STATE, if the connection is currently not in a call; or RFC_NOT_SUPPORTED, if the handle is a server handle.
    */
    DECL_EXP RFC_RC SAP_API RfcCancel(RFC_CONNECTION_HANDLE rfcHandle, RFC_ERROR_INFO* errorInfo);

	/** \brief  RFC_RC SAP_API RfcResetServerContext
	 * \ingroup connection
	 * 
	 * Resets the SAP server context ("user context / ABAP session context") associated with the given client
	 * connection, but does not close the connection.
	 *
	 * 
	 * \in rfcHandle The client connection, whose server context is to be reset.
	 * \out *errorInfo Error details in case resetting the server context fails. (Better close the connection in that case.)
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcResetServerContext(RFC_CONNECTION_HANDLE rfcHandle, RFC_ERROR_INFO* errorInfo);

	/** \brief  Ping the remote communication partner through the passed connection handle.
	 * \ingroup connection
	 *
	 * Sends a ping to the backend in order to check, whether the connection is still alive.
	 * Can be used on both, client connections as well as server connections.
	 * \warning Do not use inside a server function implementation.
	 *
	 *
	 * \in rfcHandle The connection to check
	 * \out *errorInfo More error details in case the connection is broken.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcPing(RFC_CONNECTION_HANDLE rfcHandle, RFC_ERROR_INFO* errorInfo);

	/** \brief  Returns details about the current client or server connection.
	 * \ingroup connection
         *
         * Consider that in case you are a server and call RfcListenAndDispatch(), the partner fields
         * of the attributes will be cleared. The reason is, although we might be only connected to a 
         * gateway of one application server, the function module can be also called from the other
         * application servers of the system if configured accordingly in the SM59 destination.
         *
         * I.e. expect only valid partner information from within a function module. Outside of the
         * function module, e.g. in the loop where RfcListenAndDispatch is called, you will get
         * cleared partner information in most of the cases except case RFC_OK, which means that you
         * were just called by an application server.
	 *
	 * See documentation of RFC_ATTRIBUTES.
	 *
	 * 
	 * \in rfcHandle RFC connection
	 * \out *attr Information about the current connection and the communication partner on the other side.
	 * \out *errorInfo Additional error information (e.g. connection already closed).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetConnectionAttributes(RFC_CONNECTION_HANDLE rfcHandle, RFC_ATTRIBUTES* attr, RFC_ERROR_INFO* errorInfo);

	/** \brief  Inside a server function, returns details about the current execution context.
	 * \ingroup connection
	 *
	 * See documentation of RFC_SERVER_CONTEXT.
	 *
	 * 
	 * \in rfcHandle RFC server connection
	 * \out *context Information about the current server execution context.
	 * \out *errorInfo Additional error information (e.g. connection is not a server connection).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetServerContext(RFC_CONNECTION_HANDLE rfcHandle, RFC_SERVER_CONTEXT* context, RFC_ERROR_INFO* errorInfo);

    /** \brief  Gets the SAPRouter, if any.
    * \ingroup connection
    *
    *
    * \in rfcHandle RFC connection
    * \out *sapRouter Pre-allocated buffer
    * \inout *length Needs to be filled with the buffer length of sapRouter. The return value will be the string
    * length of the returned sapRouter (if buffer was large enough) or the required buffer size (if RFC_BUFFER_TOO_SMALL).
    * In the first case, the length value will be the string length without the terminating zero, in the second case it will be the
    * required buffer size including the terminating zero.
    * \out *errorInfo More error details in case something goes wrong.
    * \return RFC_BUFFER_TOO_SMALL, if the provided sapRouter buffer was too small. RFC_OK otherwise.
    */
	DECL_EXP RFC_RC SAP_API RfcGetSapRouter(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC *sapRouter, unsigned *length, RFC_ERROR_INFO* errorInfo);

	/** \brief  Gets the external IP address of the communication partner.
	* \ingroup connection
	*
	* In scenarios where NAT (Network Address Translation) is performed between the LAN segment, where the external RFC program is
	* running, and the LAN segment, where the backend system is running, the RFC_ATTRIBUTES (members "partnerHost", "partnerIP" or "partnerIPv6")
	* will always contain the hostname/address returned by the backend system, which is the address as it is known inside the internal LAN segment.
	* However, this address is usually unusable/invalid inside the external LAN segment. External programs that need a valid "external" IP address
	* of the current communication partner, can use this API to obtain it.
	* If no NAT is used in the current scenario, the value returned by this API will be equal to partnerIP/partnerIPv6 from the RFC_ATTRIBUTES.
	*
	*
	* \in rfcHandle RFC connection
	* \out *partnerExternalIP Pre-allocated buffer
	* \inout *length Needs to be filled with the buffer length of partnerExternalIP. The return value will be the string
	* length of the returned external IP (if buffer was large enough) or the required buffer size (if RFC_BUFFER_TOO_SMALL).
	* In the first case, the length value will be the string length without the terminating zero, in the second case it will be the
	* required buffer size including the terminating zero.
	* \out *errorInfo More error details in case something goes wrong.
	* \return RFC_BUFFER_TOO_SMALL, if the provided partnerExternalIP buffer was too small.
	*         RFC_INVALID_HANDLE, if the given rfcHandle is not connected.
	*         RFC_INVALID_PARAMETER, if one of the input values is invalid.
	*         RFC_OK otherwise.
	*/
	DECL_EXP RFC_RC SAP_API RfcGetPartnerExternalIP(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC *partnerExternalIP, unsigned *length, RFC_ERROR_INFO* errorInfo);

	/** \brief  Gets the IP address of the local network interface used by this connection.
	* \ingroup connection
	*
	* On servers with multiple network interfaces, it may be useful to know, via which interface the current connection has been established.
	*
	*
	* \in rfcHandle RFC connection
	* \out *localAddress Pre-allocated buffer. If you use a buffer of length at least 46, it will always be sufficient,
	* even in case of IPv6 addresses.
	* \inout *length Needs to be filled with the buffer length of partnerExternalIP. The return value will be the string
	* length of the returned external IP (if buffer was large enough) or the required buffer size (if RFC_BUFFER_TOO_SMALL).
	* In the first case, the length value will be the string length without the terminating zero, in the second case it will be the
	* required buffer size including the terminating zero.
	* \out *localPort The local port used for the network connection.
	* \out *errorInfo More error details in case something goes wrong.
	* \return RFC_BUFFER_TOO_SMALL, if the provided partnerExternalIP buffer was too small.
	*         RFC_INVALID_HANDLE, if the given rfcHandle is not connected.
	*         RFC_INVALID_PARAMETER, if one of the input values is invalid.
	*         RFC_EXTERNAL_FAILURE, if a network level error occurs.
	*         RFC_OK otherwise.
	*/
	DECL_EXP RFC_RC SAP_API RfcGetLocalAddress(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC* localAddress, unsigned* length, unsigned* localPort, RFC_ERROR_INFO* errorInfo);

	/** \brief  Gets the partner's SSO2 ticket, if any.
	 * \ingroup connection
	 * 
	 * Can be used in two cases: call it inside the implementation of a server function and pass the server connection as rfcHandle,
	 * if you want to obtain the ticket sent from the ABAP side. For this to work, one of the flags "Send Logon Ticket" or "Send
	 * Assertion Ticket" (or similar) needs to be activated in the definition of the corresponding RFC destination in SM59.
	 * Or call it after RfcOpenConnection() and pass the client connection as rfcHandle, to obtain the ticket issued for the currrently
	 * logged in user. For this to work, the connection must be opened with parameter GETSSO2=1 and the profile parameter
	 * login/create_sso2_ticket must be set to a value different from "0" in the backend.
	 *
	 * 
	 * \in rfcHandle RFC server connection
	 * \out *ssoTicket Pre-allocated buffer, which will receive the backend user's SSO2 ticket (signed user information in base64 format)
	 * \inout *length Needs to be filled with the buffer length of ssoTicket. The return value will be the string
	 * length of the returned ticket (if buffer was large enough) or the required buffer size (if RFC_BUFFER_TOO_SMALL).
	 * In the first case, the length value will be the string length without the terminating zero, in the second case it will be the
	 * required buffer size including the terminating zero.
	 * \out *errorInfo More error details in case there is no ticket.
	 * \return RFC_RC
	 * \warning 
	 */
	DECL_EXP RFC_RC SAP_API RfcGetPartnerSSOTicket(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC *ssoTicket, unsigned *length, RFC_ERROR_INFO* errorInfo);

	/** \brief  Gets the partner's SNC name, if any. 
	 * \ingroup connection
	 * 
	 * 
	 * \in rfcHandle RFC server connection. If this function is executed on a client connection, RFC_ILLEGAL_STATE will be returned.
	 * \out *sncName Pre-allocated buffer, which will receive the backend user's SNC name (null-terminated string).
	 * \in length Size of the pre-allocated buffer. This information is coming from the GSS library, therefore
	 * unfortunately the feature of assigning the used/required length to an output parameter is not possible in this case.
	 * The maximum length of an SNC name is 256.
	 * \out *errorInfo More error details in case SNC is not active.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetPartnerSNCName(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC *sncName, unsigned length, RFC_ERROR_INFO* errorInfo);

	/** \brief  Gets partner's SNC key, if any.
	 * \ingroup connection
	 * 
	 * 
	 * \in rfcHandle RFC server connection. If this function is executed on a client connection, RFC_ILLEGAL_STATE will be returned.
	 * \out *sncKey Pre-allocated buffer, which will receive the backend user's SNC key.
	 * \inout *length Needs to be filled with the buffer length of ssoTicket. The return value will be the byte
	 * length of the returned key (if buffer was large enough). Unfortunately in case of RFC_BUFFER_TOO_SMALL
	 * the required size is not returned by the GSS library.
	 * The maximum length of an SNC key is 1024.
	 * \out *errorInfo More error details in case SNC is not active.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetPartnerSNCKey(RFC_CONNECTION_HANDLE rfcHandle, SAP_RAW *sncKey, unsigned *length, RFC_ERROR_INFO* errorInfo);

	/** \brief  Converts SNC name to SNC key.
	 * \ingroup connection
	 * 
	 * 
	 * \in *sncLib Optional: file name of the GSS library to be used for the conversion. If not specified, the
	 * "global" GSS library (environment variable SNC_LIB or SNC_LIB_64) will be used.
	 * \in *sncName Null-terminated SNC name to be converted.
	 * \out *sncKey Pre-allocated buffer, which will receive the corresponding SNC key.
	 * \inout *keyLength Needs to be filled with the buffer length of sncKey. The return value will be byte length
	 * of the SNC key (if buffer was large enough). Unfortunately in case of RFC_BUFFER_TOO_SMALL
	 * the required size is not returned by the GSS library.
	 * The maximum length of an SNC key is 1024.
	 * \out *errorInfo More error details in case something goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSNCNameToKey(SAP_UC const *sncLib, SAP_UC const *sncName, SAP_RAW *sncKey, unsigned *keyLength, RFC_ERROR_INFO* errorInfo);

	/** \brief  Converts SNC key to SNC name.
	 * \ingroup connection
	 * 
	 * 
	 * \in *sncLib Optional: file name of the GSS library to be used for the conversion. If not specified, the
	 * "global" GSS library (environment variable SNC_LIB or SNC_LIB_64) will be used.
	 * \in *sncKey SNC key to be converted.
	 * \in keyLength Byte length of the given SNC key
	 * \out *sncName Pre-allocated buffer, which will receive the corresponding (null-terminated) SNC name.
	 * \in nameLength Size of the given sncName buffer. (The maximum length of an SNC name is 256.)
	 * \out *errorInfo More error details in case something goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSNCKeyToName(SAP_UC const *sncLib, SAP_RAW const *sncKey, unsigned keyLength ,SAP_UC *sncName, unsigned nameLength, RFC_ERROR_INFO* errorInfo);


	/** \brief  Listens on a server connection handle and waits for incoming RFC calls from the R/3 system.
	 * \ingroup connection
	 * 
	 * The mechanism for dispatching incoming function calls works as follows:
	 * First %RfcListenAndDispatch() checks, whether for the current combination of R/3 SystemID and function
	 * module name a callback function has been installed via RfcInstallServerFunction(). If not, it checks,
	 * whether a callback function for SystemID=NULL has been installed via RfcInstallServerFunction().If not,
	 * it checks, whether a global callback function has been installed via RfcInstallGenericServerFunction().
	 *
	 * If a callback function has been found, the RFC call will be dispatched to that function for processing,
	 * and %RfcListenAndDispatch() returns the return code of the callback function.
	 * Otherwise %RfcListenAndDispatch() returns a SYSTEM_FAILURE to the R/3 backend and the return code
	 * RFC_NOT_FOUND to the caller.
	 *
	 * In general the return codes of %RfcListenAndDispatch() have the following meaning:
	 * - RFC_OK\n		A function call was processed successfully.
	 * - RFC_RETRY\n	No function call came in within the specified timeout period. ("timeout" is given in seconds.)
	 * - RFC_ABAP_EXCEPTION\n	A function call was processed and ended with a defined ABAP Exception, which has
	 *					been returned to the backend.
	 *
	 * In the above three cases "rfcHandle" is still open and can be used to listen for the next request.
	 *
	 * - RFC_ABAP_MESSAGE\n	A function call was started to be processed, but was aborted with an ABAP A-, E- or X-Message.
	 *				The message parameters have been returned to the backend (and can be evaluated there via
	 *				the sy-msgid, sy-msgtype, sy-msgno, sy-msgv1, ..., sy-msgv4 parameters).
	 * - RFC_EXTERNAL_FAILURE\n	A function call was started to be processed, but was aborted with a "SYSTEM_FAILURE",
	 *				which has been returned to the backend.
	 * - RFC_COMMUNICATION_FAILURE\n	The connection broke down while processing the function call. No response
	 *				has been sent to the backend.
	 * - RFC_CLOSED\n	The connection has been closed by the backend side (SMGW, SM04). No response
	 *				has been sent to the backend.
	 * - RFC_NOT_FOUND\n	No handler has been found for the current function module name. A SYSTEM_FAILURE has
	 *				been returned to the R/3 backend.
	 *
	 * In these five cases the connection has been closed, so the "rfcHandle" needs to be refreshed via RfcRegisterServer.
	 *
	 * - RFC_INVALID_HANDLE\n	"rfcHandle" is invalid or points to a connection that has already been closed.
	 *
	 * 
	 * \in rfcHandle Server connection on which to listen for incoming requests.
	 * \in timeout Number of seconds to wait for an incoming request.
	 * \out *errorInfo Additional error information.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcListenAndDispatch (RFC_CONNECTION_HANDLE rfcHandle, int timeout, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Executes a function module in the backend system.
	 * \ingroup connection
	 *
	 * The return codes have the following meaning:
	 * - RFC_OK\n		The function call was executed successfully.
	 * - RFC_ABAP_EXCEPTION\n	The function call was executed and ended with a defined ABAP Exception. The key of the
	 *					exception can be obtained from errorInfo->key.
	 *
	 * In the above two cases "rfcHandle" is still open and can be used to execute further function call.
	 *
	 * - RFC_ABAP_MESSAGE\n	The function call was started to be processed, but was aborted with an ABAP Message.
	 *				The message parameters can be obtained from errorInfo->abapMsgClass, errorInfo->abapMsgType,
	 *				errorInfo->abapMsgNumber, errorInfo->abapMsgV1, ..., errorInfo->abapMsgV4.
	 * - RFC_ABAP_RUNTIME_FAILURE\n	The function call was started to be processed, but was aborted with a SYSTEM_FAILURE
	 *				(e.g division by zero, unhandled exception, etc in the backend system).
	 *				Details can be obtained from errorInfo->message.
	 * - RFC_COMMUNICATION_FAILURE\n	The connection broke down while processing the function call.
	 *				Details can be obtained from errorInfo->message.
	 *
	 * In these three cases the connection has been closed, so the "rfcHandle" needs to be refreshed via RfcOpenConnection.
	 *
	 * - RFC_INVALID_HANDLE\n	"rfcHandle" is invalid or points to a connection that has already been closed.
	 *
	 * 
	 * \in rfcHandle Client connection over which to execute the function module.
	 * \inout funcHandle Data container containing the input data for the function module.
	 * %RfcInvoke() will write the FM's output data into this container.
	 * \out *errorInfo Additional error information.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInvoke(RFC_CONNECTION_HANDLE rfcHandle, RFC_FUNCTION_HANDLE funcHandle, RFC_ERROR_INFO* errorInfo);




    /* ***********************************************************************/
    /*                                                                       */
    /*  Automated Server API                                                 */
    /*                                                                       */
    /* ***********************************************************************/


	/** \brief  This function can be used to start "automatic" servers.
	* \ingroup autoserver
	*
	* In contrast to RfcRegisterServer(), which registers one single server connection at a SAP gateway, %RfcCreateServer() can be used
	* to create a server object that manages multiple server connections in parallel, that takes care of automatically
	* re-registering a connection in case it gets broken by network problems, etc. and that takes care of the dispatch-loop
	* internally, so that application programmers no longer need to implement that error-prone task themselves. This means,
	* you no longer need to use RfcListenAndDispatch() and no longer need to worry about creating multiple threads with such a
	* listen- and dispatch-loop, if you want to process multiple parallel requests. All you need to do is starting an RFC_SERVER_HANDLE
	* with RfcLaunchServer(), and it will listen for incoming requests on n parallel threads (as given by the parameter REG_COUNT).
	*
	* In addition, you can start not only a usual registered Server that registers at an RFC gateway, but also a standalone Server
	* that listens for requests on a network port and can be accessed by both, SAP systems and other external C-, Java- or .NET-based
	* RFC client programs. Which kind of server is started, depends on the connection parameters:
	*
	* Registered Server:
	* Here you need to supply the standard parameters you would also use with RfcRegisterServer(). E.g. GWHOST, GWSERV and PROGRAM_ID,
	* followed potentially by parameters for SNC, Trace, SAPRouter, etc. In addition you can supply the parameters REG_COUNT and MAX_REG_COUNT,
	* if you want to process multiple requests in parallel (multiple gateway registrations). MAX_REG_COUNT is needed only for "stateful"
	* RFC servers (see the sample sapnwrfc.ini for details).
	* Alternatively to registering at only one fixed gateway, you can also provide parameters for "group registration". Then the server will
	* register REG_COUNT connections at every gateway of the given logon group. Again see chapter 3 in the sapnwrfc.ini file.
	*
	*
	* For all types of servers you need to specify the parameter SERVER_NAME. This is a freely choosable name used for monitoring purposes.
	*
	* After a server object has been created, it can be started and stopped any number of times via RfcLaunchServer() and RfcShutdownServer().
	* When the server is no longer needed, it must be cleaned up with RfcDestroyServer().
	*
	* \in *connectionParams Array of network parameters needed for starting the server.
	* \out paramCount Number of elements contained in the RFC_CONNECTION_PARAMETER array.
	* \out *errorInfo Additional error information in case the server object could not be created (e.g. invalid parameters or insufficient memory).
	* \return A handle to the created server object.
	*/
	DECL_EXP RFC_SERVER_HANDLE SAP_API RfcCreateServer(RFC_CONNECTION_PARAMETER const* connectionParams, unsigned paramCount, RFC_ERROR_INFO* errorInfo);

	/** \brief  Cleans up and destroys an automatic server object, once you are done with it.
	* \ingroup autoserver
	*
	* Any internal resources of this server object are released. Therefore make sure not to use the RFC_SERVER_HANDLE in any further API calls
	*(RfcLaunchServer(), RfcShutdownServer(), etc), after you have destroyed it.
	*
	*
	* \in serverHandle A handle to the server object.
	* \out *errorInfo Not much that can go wrong here.
	* \return RFC_OK
	*/
	DECL_EXP RFC_RC SAP_API RfcDestroyServer(RFC_SERVER_HANDLE serverHandle, RFC_ERROR_INFO* errorInfo);

	/** \brief  Starts up an automatic server, so that it starts waiting for incoming requests and processes them.
	* \ingroup autoserver
	*
	*
	* \in serverHandle A handle to the server object.
	* \out *errorInfo Additional error information in case starting the server fails.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcLaunchServer(RFC_SERVER_HANDLE serverHandle, RFC_ERROR_INFO* errorInfo);

	/** \brief  Stops an automatic server, so that it no longer accepts incoming requests.
	* \ingroup autoserver
	*
	* If timeout is set to 0, the server stops immediately, aborting any currently ongoing RFC requests. If you want to give any possibly ongoing requests a
	* chance to complete, before stopping the server, provide a timeout > 0. %RfcShutdownServer() will then block until all current requests are completed
	* or the timeout period is over, whichever occurs first. In any case, the server will immediately stop accepting new requests as soon as you call this function.
	*
	* If at a later point you want this server to resume listening for requests, you can start it again by calling RfcLaunchServer(). However, once you have
	* cleaned up the server with RfcDestroyServer(), you must no longer attempt to use it in further RfcLaunchServer() (or other) calls.
	*
	* \in serverHandle A handle to the server object.
	* \in timeout Number of seconds to wait in order to give currently ongoing RFC requests time to complete.
	* \out *errorInfo Not much that can go wrong here.
	* \return RFC_OK
	*/
	DECL_EXP RFC_RC SAP_API RfcShutdownServer(RFC_SERVER_HANDLE serverHandle, unsigned timeout, RFC_ERROR_INFO* errorInfo);



	/* ***********************************************************************/
	/*                                                                       */
	/*  Managing Automated Servers                                           */
	/*                                                                       */
	/* ***********************************************************************/

	/** \brief  Retrieves detailed information about a multi-count Registered Server or a TCP Socket Server.
	* \ingroup autoserver
	*
	* See RFC_SERVER_ATTRIBUTES for more details.
	*
	* \in serverHandle A handle to the server object.
	* \out *serverAttributes Is filled with state information, number of busy connections, etc.
	* \out *errorInfo Not much can go wrong here, except an invalid handle.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetServerAttributes(RFC_SERVER_HANDLE serverHandle, RFC_SERVER_ATTRIBUTES* serverAttributes, RFC_ERROR_INFO* errorInfo);


	/** \brief  Retrieves detailed information about all clients currently connected to a multi-count Registered Server or a TCP Socket Server.
	* \ingroup autoserver
	*
	* For every connected client you get its connection attributes (hostname, SID, user, client) as well as the current function module name,
	* if the connection is busy, or the last activity time, if it is idle.
	* Make sure to release the memory again with RfcDestroyServerConnectionMonitorData(), after you are done with it.
	*
	* \in serverHandle A handle to the server object.
	* \out *numberOfConnections Number of client connections currently connected to this server.
	* \out **connectionData An array of monitor data structs, one for each client connection.
	* \out *errorInfo Not much can go wrong here, except an invalid handle or out of memory.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetServerConnectionMonitorData(RFC_SERVER_HANDLE serverHandle, unsigned* numberOfConnections, RFC_SERVER_MONITOR_DATA** connectionData, RFC_ERROR_INFO* errorInfo);


	/** \brief  Releases all internal memory hold by monitor data object.
	* \ingroup autoserver
	*
	* Use this to free the data obtained from RfcGetServerConnectionMonitorData() once you no longer need it.
	*
	* \in numberOfConnections Number of elements in the connectionData array.
	* \in connectionData Array of connection data objects to be cleaned up.
	* \out *errorInfo Can't go wrong...
	* \return RFC_OK
	*/
	DECL_EXP RFC_RC SAP_API RfcDestroyServerConnectionMonitorData(unsigned numberOfConnections, RFC_SERVER_MONITOR_DATA* connectionData, RFC_ERROR_INFO* errorInfo);


	/** \brief  Adds an error listener to this server.
	* \ingroup autoserver
	*
	* An error listener is a callback function of type RFC_SERVER_ERROR_LISTENER. The server will execute this function, whenever a
	* severe technical error happens outside the processing of function modules, e.g. network problems with the gateway or with the
	* connected clients.
	*
	* \in serverHandle A handle to the server object.
	* \in errorListener Function pointer to a callback function receiving error notifications.
	* \out *errorInfo Additional error information in case adding the error listener fails, e.g. invalid handle.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcAddServerErrorListener(RFC_SERVER_HANDLE serverHandle, RFC_SERVER_ERROR_LISTENER errorListener, RFC_ERROR_INFO* errorInfo);


	/** \brief  Adds a state change listener to this server.
	* \ingroup autoserver
	*
	* A state change listener is a callback function of type RFC_SERVER_STATE_CHANGE_LISTENER. The server will execute this function,
	* whenever the server's state changes, e.g. from STARTED to ALIVE, or from ALIVE to STOPPING.
	*
	* \in serverHandle A handle to the server object.
	* \in stateChangeListener Function pointer to a callback function receiving state change notifications.
	* \out *errorInfo Additional error information in case adding the state change listener fails, e.g. invalid handle.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcAddServerStateChangedListener(RFC_SERVER_HANDLE serverHandle, RFC_SERVER_STATE_CHANGE_LISTENER stateChangeListener, RFC_ERROR_INFO* errorInfo);

	/** \brief  Adds a session change listener to this server.
	* \ingroup autoserver
	*
	* A session change listener is a callback function of type RFC_SESSION_STATE_CHANGE_LISTENER. The server will execute this function,
	* whenever a stateful user session starts or ends. A "stateful user session" is basically a one-to-one binding between a SAP user session
	* on ABAP side and some kind of "user session" in your C program. State information can be kept on C side inbetween separate function
	* calls from ABAP.
	*
	* The server will also execute this function, whenever an ABAP function call begins or ends inside an existing stateful user session.
	* For most applications, this probably does not matter, so this event can be ignored. There may however be cases, where some cleanup
	* or reduction of consumed resources can be done, while a stateful user session is idle.
	* 
	* There are two ways to start a stateful user session:
	* - The ABAP side requests to start a stateful sequence by calling RFM RFC_SET_REG_SERVER_PROPERTY with parameter EXCLUSIV = 'Y'
	* - The C program, while currently processing a request from ABAP, can set the current connection to stateful via RfcSetServerStateful()
	*
	* There are four ways a stateful user session can end:
	* - The ABAP side ends the stateful sequence by calling RFM RFC_SET_REG_SERVER_PROPERTY with parameter EXCLUSIV = 'N'
	* - The C program, while currently processing a request from ABAP, can end the current stateful session via RfcSetServerStateful()
	* - The SAP user session on ABAP side ends.\n
	*   This can be, because the SAP user logs out, or ends the current internal mode by pressing the "yellow arrow" or "red cross" button
	*   or by switching to a new transaction via \\n in the OK-code field.
	* - Either the ABAP session or the C session runs into a severe problem (SYSTEM_FAILURE), upon which both sides get reset and the
	*   connection between the two sides gets closed.
	* - The network connection gets destroyed by network problems, system crash etc.
	*
	* An application that wants to work with stateful sessions, needs to react as follows to the various events:
	* - RFC_SESSION_CREATED\n
	*   Do the necessary initialization of data or resources (like a database connection, etc.).
	* - RFC_SESSION_PASSIVATED\n
	*   Most applications won't need this and can therefore ignore this event. One example, where this may be useful, is:
	*   if the function calls going on in this session are few and far between, but they occupy a lot of memory, it might be a good idea
	*   to flush the session state out to disc here, and load it back into memory, when the session gets activated again.
	* - RFC_SESSION_ACTIVATED\n
	*   This is the counterpart to RFC_SESSION_PASSIVATED. In most cases it can safely be ignored. For an example where it might be
	*   useful to use it, see above.
	* - RFC_SESSION_DESTROYED\n
	*   Do the necessary cleanup of data and other resources that have been used while processing the function calls of this session.
	*
	* \in serverHandle A handle to the server object.
	* \in sessionChangeListener Function pointer to a callback function receiving state change notifications.
	* \out *errorInfo Additional error information in case adding the state change listener fails, e.g. invalid handle.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcAddServerSessionChangedListener(RFC_SERVER_HANDLE serverHandle, RFC_SERVER_SESSION_CHANGE_LISTENER sessionChangeListener, RFC_ERROR_INFO* errorInfo);

	/** \brief  Sets this client's operation mode to statefull or stateless.
	* \ingroup autoserver
	*
	* When a client session operates in stateless mode, which is the default, it does not keep state information inbetween several
	* RFC requests over the same connection. By setting it to stateful, you can change that so that all requests over one connection
	* run inside one single "user session".
	*
	* \note This can be used only for connection handles being managed by an automated (multi-count) server. If you try to use it
	* on an ordinary connection created with RfcRegisterServer() or RfcStartServer(), you will get an RFC_ILLEGAL_STATE error.
	*
	* \in connectionHandle A handle to the current client connection. Use the one that gets passed to you in your RFC_SERVER_FUNCTION implementation.
	* \in isStateful Specifies whether the server should operate in stateful mode ("1") or in stateless mode ("0").
	* \out *errorInfo Additional error information in case changing the state fails, e.g. invalid handle, server is not a multi-count server, etc.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcSetServerStateful(RFC_CONNECTION_HANDLE connectionHandle, unsigned isStateful, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Installs an optional function for performing authentication checks on incoming login attempts.
    * \ingroup installer
    * 
    * After an RFC connection is opened to the RFC library, and before the first RFC call is executed over
    * this connection, the RFC library calls this callback function, if installed.
    * Here you can implement a central authentication check, defining exactly which entity
    * is allowed to execute the function in your RFC server program.
    * The actual function module implementations can then concentrate on their business logic and don't
    * need to pay attention to access and authentication checks.
    * 
    * \in onAuthenticationCheck Pointer to a function of type RFC_ON_AUTHENTICATION_CHECK. The RFC lib calls this function, whenever a new RFC connection to this server is first opened by the client.
    * \out *errorInfo Additional information, in case the handler could not be installed.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcInstallAuthenticationCheckHandler(RFC_ON_AUTHENTICATION_CHECK onAuthenticationCheck, RFC_ERROR_INFO* errorInfo);

    /** \brief  Gets the type of authentication data received from the backend in RFC_ON_AUTHENTICATION_CHECK.
    * \ingroup autoserver
    *
    * If a handler of type RFC_ON_AUTHENTICATION_CHECK is installed, this getter returns the type of authentication data that was received from
    * the backend. The authentication method can be customized in the SM59 destination in the backend. The received authentication data is stored
    * in the authentication handle, which can then by queried by the authentication handler RFC_ON_AUTHENTICATION_CHECK.
    *
    * \in authenticationHandle A handle representing the authentication data passed into RFC_ON_AUTHENTICATION_CHECK.
    * \out *type The type of authentication method used by the backend.
    * \out *errorInfo Additional error information in case changing the state fails, e.g. invalid handle, null pointer, etc.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetAuthenticationType(RFC_AUTHENTICATION_HANDLE authenticationHandle, RFC_AUTHENTICATION_TYPE* type, RFC_ERROR_INFO* errorInfo);
    
    /** \brief  Gets the user to authenticate in RFC_ON_AUTHENTICATION_CHECK if any is received.
    * \ingroup autoserver
    *
    * If a handler of type RFC_ON_AUTHENTICATION_CHECK is installed, this getter returns the user to authenticate set in the destination in the backend.
    * This could also be the alias user.
    * The received authentication data is stored in the authentication handle, which can then by queried by 
    * the authentication handler RFC_ON_AUTHENTICATION_CHECK.
    *
    * \in authenticationHandle A handle representing the authentication data passed into RFC_ON_AUTHENTICATION_CHECK.
    * \out **user User to authenticate.
    * \out *length String length of user.
    * \out *errorInfo Additional error information in case changing the state fails, e.g. invalid handle, null pointer, etc.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetAuthenticationUser(RFC_AUTHENTICATION_HANDLE authenticationHandle, const SAP_UC** user, unsigned* length, RFC_ERROR_INFO* errorInfo);
    
    /** \brief  Gets the password for authentication in RFC_ON_AUTHENTICATION_CHECK if basic authentication method was setup in the backend.
    * \ingroup autoserver
    *
    * If a handler of type RFC_ON_AUTHENTICATION_CHECK is installed, this getter returns the password for authentication set in the destination in the backend, i.e.
    * basic authentication was setup.
    * The received authentication data is stored in the authentication handle, which can then by queried by 
    * the authentication handler RFC_ON_AUTHENTICATION_CHECK.
    *
    * \in authenticationHandle A handle representing the authentication data passed into RFC_ON_AUTHENTICATION_CHECK.
    * \out **password The user's password for basic authentication. NULL if otherwise.
    * \out *length String length of password.
    * \out *errorInfo Additional error information in case changing the state fails, e.g. invalid handle, null pointer, etc.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetAuthenticationPassword(RFC_AUTHENTICATION_HANDLE authenticationHandle, const SAP_UC** password, unsigned* length, RFC_ERROR_INFO* errorInfo);
    
    /** \brief  Gets the assertionTicket for authentication in RFC_ON_AUTHENTICATION_CHECK if SSO based authentication method was setup in the backend.
    * \ingroup autoserver
    *
    * If a handler of type RFC_ON_AUTHENTICATION_CHECK is installed, this getter returns the assertionTicket for authentication set in the destination in the backend, i.e.
    * SSO authentication was setup.
    * The received authentication data is stored in the authentication handle, which can then by queried by 
    * the authentication handler RFC_ON_AUTHENTICATION_CHECK.
    *
    * \in authenticationHandle A handle representing the authentication data passed into RFC_ON_AUTHENTICATION_CHECK.
    * \out **assertionTicket Assertion ticket for SSO authentication. NULL if otherwise.
    * \out *length String length of assertionTicket.
    * \out *errorInfo Additional error information in case changing the state fails, e.g. invalid handle, null pointer, etc.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetAuthenticationAssertionTicket(RFC_AUTHENTICATION_HANDLE authenticationHandle, const SAP_UC** assertionTicket, unsigned* length, RFC_ERROR_INFO* errorInfo);
    
    /** \brief  Gets the certificate chain for authentication in RFC_ON_AUTHENTICATION_CHECK if x509 authentication method was setup in the backend.
    * \ingroup autoserver
    *
    * If a handler of type RFC_ON_AUTHENTICATION_CHECK is installed, this getter returns the certificate chain for authentication set in the destination in the backend, i.e.
    * x509 authentication was setup. The certificate chain is stored as a singly linked list.
    * The received authentication data is stored in the authentication handle, which can then by queried by 
    * the authentication handler RFC_ON_AUTHENTICATION_CHECK.
    *
    * \in authenticationHandle A handle representing the authentication data passed into RFC_ON_AUTHENTICATION_CHECK.
    * \out **certificateData Singly linked list of certificate attributes for x509 authentication. NULL if otherwise.
    * \out *errorInfo Additional error information in case changing the state fails, e.g. invalid handle, null pointer, etc.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetAuthenticationCertificateData(RFC_AUTHENTICATION_HANDLE authenticationHandle, const RFC_CERTIFICATE_DATA** certificateData, RFC_ERROR_INFO* errorInfo);

    /* ***********************************************************************/
    /*                                                                       */
    /*  Transaction (tRFC & qRFC) Client API                                 */
    /*                                                                       */
    /* ***********************************************************************/

	/**
	 * \brief  Retrieves a unique 24-digit transaction ID from the backend.
	 * \ingroup transaction
	 * If you specify NULL as connection handle, the API will attempt to generate a TID locally using the
	 * operating system's UUID algorithms. (Currently not possible on AIX systems.)
	 * 
	 * \in rfcHandle Client connection to a backend or NULL, if you want to create a TID locally.
	 * \out tid Will be filled with the transaction ID.
	 * \out *errorInfo Error information in case there is a problem with the connection.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetTransactionID(RFC_CONNECTION_HANDLE rfcHandle, RFC_TID tid, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Creates a container for executing a (multi-step) transactional call.
	 * \ingroup transaction
	 * 
	 * If queueName is NULL, tRFC will be used, otherwise qRFC. Use RfcInvokeInTransaction() to
	 * add one (or more) function modules to the transactional call. When sending this transactional
	 * call to the backend via RfcSubmitTransaction(), the backend will then treat
	 * all function modules in the RFC_TRANSACTION_HANDLE as one LUW.
	 *
	 * \in rfcHandle Client connection to the backend, into which you want to send this tRFC/qRFC LUW.
	 * \in tid A unique 24 character ID.
	 * \in *queueName For tRFC set this to NULL, for qRFC specify the name of a qRFC inbound queue in the backend.
	 * \out *errorInfo Error information in case there is a problem with the connection.
	 * \return A data container that can be filled with several function modules.
	 */
	DECL_EXP RFC_TRANSACTION_HANDLE SAP_API RfcCreateTransaction(RFC_CONNECTION_HANDLE rfcHandle, RFC_TID tid, SAP_UC const *queueName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Adds a function module call to a transaction. Can be used multiple times on one tHandle.
	 * \ingroup transaction
	 * 
	 * \in tHandle A transaction handle created via RfcCreateTransaction().
	 * \in funcHandle An RFC_FUNCTION_HANDLE, whose IMPORTING, CHANGING and TABLES parameters have been filled.
	 * \note that tRFC/qRFC calls have no return values, so the EXPORTING parameters of this function handle will
	 * not be filled, nor will the changes to the CHANGING/TABLES parameters be returned.
	 * \out *errorInfo Actually there is nothing that can go wrong here except for invalid handles and out of memory.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInvokeInTransaction(RFC_TRANSACTION_HANDLE tHandle, RFC_FUNCTION_HANDLE funcHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Executes the entire LUW in the backend system as an "atomic unit".
	 * \ingroup transaction
	 * 
	 * This step can be repeated until it finally succeeds (RFC_OK). The transaction handling in the backend
	 * system protects against duplicates (until you remove the TID from the backend's status tables using
	 * RfcConfirmTransaction()).
	 * 
	 * 
	 * \in tHandle A transaction handle filled with one or several function modules.
	 * \out *errorInfo Additional error information in case anything goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSubmitTransaction(RFC_TRANSACTION_HANDLE tHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Removes the TID contained in the RFC_TRANSACTION_HANDLE from the backend's ARFCRSTATE table.
	 * \ingroup transaction
	 * 
	 * After RfcSubmitTransaction() has finally succeeded, call %RfcConfirmTransaction() to clean up the
	 * transaction handling table in the backend.
	 * \warning Attention: after this call, the backend is no longer protected against this TID. So another
	 * RfcSubmitTransaction() with the same transaction handle would result in a duplicate.
	 *
	 * 
	 * \in tHandle A transaction handle that has successfully been submitted.
	 * \out *errorInfo Additional error information in case of a network problem.
	 * \warning You may retry the Confirm step, if you get an error here, but do not retry the Submit step!
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcConfirmTransaction(RFC_TRANSACTION_HANDLE tHandle, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Convenience function to remove the TID contained in a previous RFC_TRANSACTION_HANDLE from the backend's ARFCRSTATE table,
	 * without the need of still having the RFC_TRANSACTION_HANDLE at hand.
	 * \ingroup transaction
	 *
	 * After RfcSubmitTransaction() has finally succeeded, call %RfcConfirmTransactionID() to clean up the
	 * transaction handling table in the backend. This function can be called after the RFC_TRANSACTION_HANDLE has
	 * already been deleted.
	 * \warning Attention: after this call, the backend is no longer protected against this TID. So another
	 * RfcSubmitTransaction() with the same transaction handle would result in a duplicate.
	 *
	 *
	 * \in rfcHandle A connection into the same system, into which the corresponding transaction has been sent via RfcSubmitTransaction().
	 * \in tid A unique 24 character ID.
	 * \out *errorInfo Additional error information in case of a network problem.
	 * \warning You may retry the Confirm step, if you get an error here, but do not retry the Submit step!
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcConfirmTransactionID(RFC_CONNECTION_HANDLE rfcHandle, RFC_TID tid, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Releases the memory of the transaction container.
	 * \ingroup transaction
	 *
	 *
	 * \in tHandle A transaction handle that is no longer needed.
	 * \out *errorInfo Not much that can go wrong here...
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyTransaction(RFC_TRANSACTION_HANDLE tHandle, RFC_ERROR_INFO* errorInfo);


	/* ***********************************************************************/
	/*                                                                       */
	/*  Background Communication (bgRFC) Client API                          */
	/*                                                                       */
	/* ***********************************************************************/

	/**
	 * \brief  Create a 32 digit bgRFC unit ID.
	 * \ingroup bgrfc
	 *
	 * This function fills the given RFC_UNITID with a 32 digit hexadecimal GUID and zero-terminates it.
	 * If you want the GUID to be generated by the backend, pass a valid rfcHandle, if you want the
	 * NW RFC library to generate one locally (using the appropriate OS functions), pass NULL as
	 * connection handle. In both cases the GUID is suitable for sending bgRFC units into an SAP system.
	 *
	 *
	 * \in rfcHandle An open RFC connection into the system that is to create the unit ID, or NULL.
	 * \out uid Preallocated buffer that will receive the 32 digits of the unit ID and a terminating zero.
	 * \out *errorInfo Not much that can go wrong here...
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetUnitID(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNITID uid, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Create a bgRFC unit.
	 * \ingroup bgrfc
	 *
	 * Creates a data container that can later be filled with one or more function modules comprising the
	 * bgRFC unit. The backend will execute these function modules as an atomic unit.
	 * The connection handle specifies the target system, to which the unit will later be sent. The unit ID
	 * has been created in the previous step (or is an old one in case of retrying a failed unit).
	 * Via queueNames and queueNameCount you can specify the list of bgRFC queues, into which this unit
	 * shall later be inserted. If no queues are given (queueNameCount == 0), a synchronous unit is created
	 * (type 'T') that will later be executed immediately. Otherwise an asynchronous unit (type 'Q') is created,
	 * which will be inserted into the named queues and executed asynchronously by the bgRFC scheduler.
	 *
	 *
	 * \in rfcHandle An open RFC connection into the system that will later receive the unit.
	 * \in uid A 32 digit unique identifier of the unit.
	 * \in *queueNames[] A list of bgRFC queues in the backend or NULL.
	 * \in queueNameCount The length of the queueNames list.
	 * \in *unitAttr A set of attributes that specify the behaviour of the unit in the backend.
	 * See RFC_UNIT_ATTRIBUTES for more information.
	 * \out *identifier This identifier can be used in later calls to RfcConfirmUnit() and RfcGetUnitState().
	 * It is important that these functions are called with the correct unit type ('T' or 'Q'), otherwise
	 * the backend system won't find the status information corresponding to the uid... Therefore the
	 * NW RFC lib bundles the uid and the correct unit type here for your convenience.
	 * \out *errorInfo More details in case something goes wrong.
	 * \return RFC_OK or RFC_MEMORY_INSUFFICIENT
	 */
	DECL_EXP RFC_UNIT_HANDLE SAP_API RfcCreateUnit(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNITID uid, SAP_UC const *queueNames[], unsigned queueNameCount,
                             	                   const RFC_UNIT_ATTRIBUTES* unitAttr, RFC_UNIT_IDENTIFIER* identifier, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Adds a function module to a bgRFC unit.
	 * \ingroup bgrfc
	 *
	 * Serializes the payload of the function module data container into bgRFC format and inserts
	 * it into the data container for the bgRFC unit. The funcHandle can afterwards be freed
	 * using RfcDestroyFunction(), because the data is copied, not referenced.
	 *
	 * \note Despite the name "invoke", nothing is executed in the backend system, yet!
	 *
	 *
	 * \in unitHandle A valid (unsubmitted) bgRFC unit, to which the given function module shall be added.
	 * \in funcHandle A function module, whose payload (IMPORTING/CHANGING/TABLES) shall be added to the unit.
	 * \out *errorInfo More details in case something goes wrong.
	 * \return RFC_OK, RFC_INVALID_HANDLE or RFC_MEMORY_INSUFFICIENT
	 */
	DECL_EXP RFC_RC SAP_API RfcInvokeInUnit(RFC_UNIT_HANDLE unitHandle, RFC_FUNCTION_HANDLE funcHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Executes a bgRFC unit in the backend.
	 * \ingroup bgrfc
	 *
	 * Sends the bgRFC unit into the backend, where it will be executed synchronously or persisted
	 * in the given inbound queues and executed asynchronously by the bgRFC scheduler, depending on
	 * whether the unit type is 'T' or 'Q'.
	 * If the type is 'T', this function will wait until the unit is completely executed and then
	 * return the success or error information. If the type is 'Q', this function only inserts the
	 * unit into the specified queues and then returns. Processing of the unit in the backend system
	 * happens asynchronously. The return code of this function indicates, whether the unit could
	 * be persisted in the given queues successfully. In order to get information about the processing
	 * status of the unit, use RfcGetUnitState() at a later point.
	 *
	 * \note Despite the name "invoke", nothing is executed in the backend system, yet!
	 *
	 *
	 * \in unitHandle A valid (unsubmitted) bgRFC unit, which shall be sent into the backend system.
	 * \out *errorInfo More details in case something goes wrong.
	 * \return RFC_OK, RFC_INVALID_HANDLE, RFC_MEMORY_INSUFFICIENT, RFC_COMMUNICATION_FAILURE
	 */
	DECL_EXP RFC_RC SAP_API RfcSubmitUnit(RFC_UNIT_HANDLE unitHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Removes the UID from the backend's status management.
	 * \ingroup bgrfc
	 *
	 * After RfcSubmitUnit() returned successfully, you should use this function to cleanup
	 * the status information for this unit on backend side. However, be careful: if you have
	 * a three-tier architecture, don't bundle Submit and Confirm into one single logical step.
	 * Otherwise you run the risk, that the middle tier (the NW RFC lib) successfully executes
	 * both, the Submit and the Confirm, but on the way back to the first tier an error occurs
	 * and the first tier can not be sure that the unit was really executed in the backend and
	 * therefore decides to re-execute it. This will now result in a duplicate execution in the
	 * backend, because the Confirm step in the first try has already deleted the UID in the
	 * backend, and consequently the backend is no longer protected against re-execution of this
	 * UID. In a three-tier architecture, the first tier should trigger both steps separately:
	 * first the Submit, and after it knows that the Submit was successful, the Confirm.
	 * Also in case the Confirm runs into an error, do NOT execute the Submit again, never!
	 * You may try the Confirm again at a later point, but otherwise just ignore the error.
	 * Better a left-over entry in the status information table than a duplicate unit...
	 *
	 * \in rfcHandle A connection into the same system, into which the corresponding bgRFC unit
	 * has been sent via RfcSubmitUnit().
	 * \in *identifier The correct combination of UID and type of the unit. Best use the output
	 * you get from RfcCreateUnit().
	 * \out *errorInfo More details in case something goes wrong.
	 * \return RFC_OK, RFC_INVALID_HANDLE, RFC_COMMUNICATION_FAILURE
	 */
	DECL_EXP RFC_RC SAP_API RfcConfirmUnit(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNIT_IDENTIFIER* identifier, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Releases the memory of the bgRFC unit container.
	 * \ingroup bgrfc
	 * 
	 * 
	 * \in unitHandle A unit handle that is no longer needed.
	 * \out *errorInfo Not much that can go wrong here...
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyUnit(RFC_UNIT_HANDLE unitHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Retrieves the processing status of the given background unit from the backend system's status management.
	 * \ingroup bgrfc
	 * 
	 * 
	 * \in rfcHandle A connection into the same system, into which the corresponding bgRFC unit
	 * has been sent via RfcSubmitUnit().
	 * \in *identifier The correct combination of UID and type of the unit. Best use the output
	 * you get from RfcCreateUnit().
	 * \out *state The state of the unit. See RFC_UNIT_STATE for more details.
	 * \out *errorInfo Not much that can go wrong here...
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetUnitState(RFC_CONNECTION_HANDLE rfcHandle, RFC_UNIT_IDENTIFIER* identifier, RFC_UNIT_STATE* state, RFC_ERROR_INFO* errorInfo);



    /* ***********************************************************************/
    /*                                                                       */
    /*  Installation of Callback Functions for RFC Servers                   */
    /*                                                                       */
    /* ***********************************************************************/

	/**
	 * \brief  Installs a callback function of type RFC_SERVER_FUNCTION, which will be triggered when a request for
	 * the function module corresponding to funcDescHandle comes in from the R/3 system corresponding to sysId.
	 * \ingroup installer
	 *
	 * If you pass NULL as "sysId", the serverFunction will be used for calls from any backend system.
	 * 
	 * The main inputs of RFC_SERVER_FUNCTION are as follows:
	 * - RFC_CONNECTION_HANDLE\n		A connection handle, which can be used to query logon information about
	 *						the current (backend) user or to make callbacks into the backend.
	 * - RFC_FUNCTION_HANDLE\n			A data container that represents the current function call. Read the importing
	 *						parameters, which came from the backend, from this container via the RfcGetX functions and
	 *						write the exporting parameters, which are to be returned to the backend, into this container
	 *						using the RfcSetX functions.\n
	 *						The memory of that container is automatically released by the RFC Runtime after the
	 *						RFC_SERVER_FUNCTION returns.
	 * - RFC_ERROR_INFO*\n			If you want to return an ABAP Exception or ABAP Message to the backend, fill the
	 *						parameters of that container and return RFC_ABAP_EXCEPTION or RFC_ABAP_MESSAGE from
	 *						your RFC_SERVER_FUNCTION implementation.\n
	 *						If you want to return a SYSTEM_FAILURE to the backend, fill the message parameter of
	 *						this container and return RFC_EXTERNAL_FAILURE from your RFC_SERVER_FUNCTION implementation.
	 * If your RFC_SERVER_FUNCTION implementation processed the function call successfully, you should return RFC_OK.
	 *
	 * 
	 * \in *sysId System ID of the R/3 system, for which this function module implementation shall be used.
	 * If you set this to NULL, this server function will be used for calls from all backends, for whose SysID no
	 * explicit server function has been installed.
	 * \in funcDescHandle A function description giving the name of the function module and its parameters.\n
	 * Note that the NW RFC library does not create a copy of this function description. So if you are using
	 * self-defined (hard-coded) function descriptions (see RfcCreateFunctionDesc()), then you need to make
	 * sure, that these function descriptions are not destroyed as long as they are still used in a server
	 * function installation!
	 * \in serverFunction Pointer to a C function of type RFC_SERVER_FUNCTION. If you pass a null-pointer here,
	 * any previously installed server function for the given function module will be uninstalled.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInstallServerFunction(SAP_UC const *sysId, RFC_FUNCTION_DESC_HANDLE funcDescHandle, RFC_SERVER_FUNCTION serverFunction, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Installs a generic callback function of type RFC_SERVER_FUNCTION together with a callback
	 * function of type RFC_FUNC_DESC_CALLBACK for obtaining the metadata description of unknown function modules.
     * \ingroup installer
     * 
	 * The RFC Runtime calls the callback function RFC_SERVER_FUNCTION, if it receives a function call, for whose
	 * function module name no matching callback function has been installed via RfcInstallServerFunction()
	 * (neither for the current system ID nor for SysID=NULL).
	 *
	 * In addition to the handler function you need to provide a second callback function: RFC_FUNC_DESC_CALLBACK.
	 * The RFC runtime calls it to obtain an RFC_FUNCTION_DESC_HANDLE for the current function module from you.
	 * So this function either needs to return hardcoded meta data or needs to be able to perform a DDIC lookup
	 * using a valid client connection and RfcGetFunctionDesc(). If your implementation of RFC_FUNC_DESC_CALLBACK
	 * is not able to provide a function description for the current function module name, it should return RFC_NOT_FOUND.
	 * The RFC runtime will then notify the backend, that this function module cannot be processed by your
	 * RFC server.
	 *
     * 
     * \in serverFunction A pointer to a function that can handle "all" function modules.
     * \in funcDescProvider A pointer to a function that can provide metadata descriptions of "all" function modules.
     * \out *errorInfo Again not much that can go wrong at this point.
     * \return 
     */
    DECL_EXP RFC_RC SAP_API RfcInstallGenericServerFunction(RFC_SERVER_FUNCTION serverFunction, RFC_FUNC_DESC_CALLBACK funcDescProvider, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Installs the necessary callback functions for processing incoming tRFC/qRFC calls.
	 * \ingroup installer
	 * 
	 * These functions need to be implemented by you and will be used by the RFC runtime in the following way:
	 * -# The RFC_ON_CHECK_TRANSACTION function is called when a local transaction is starting. Since a transactional 
	 *    RFC call can be issued many times by the client system, the function is responsible for storing the transaction ID
	 *    in permanent storage. The return value should be one of the following:
	 *    - RFC_OK\n		Transaction ID stored, transaction can be started.
	 *    - RFC_EXECUTED\n	This transaction has already been processed successfully in an earlier attempt. Skip the execution now.
	 *    - RFC_EXTERNAL_FAILURE\n Currently unable to access my permanent storage. Raise an exception in the sending system, so
	 *						that the sending system will try to resend the transaction at a later time.
	 * -# The next step will be the execution of the RFC_SERVER_FUNCTIONs for all function modules contained in the LUW.
	 * -# If one of the RFC_SERVER_FUNCTION implementations returns an error code, RFC_ON_ROLLBACK_TRANSACTION is called.
	 *    Here you should roll back all the work of all the previous RFC_SERVER_FUNCTIONs. (The easiest way is to do
	 *    a database ROLLBACK WORK here.)\n
	 *    If all RFC_SERVER_FUNCTIONs complete successfully, RFC_ON_COMMIT_TRANSACTION is called at the end.
	 *    Persist all the changes here (e.g. do a COMMIT WORK).\n
	 *    Note: Normally you'll only have "one-function-module LUWs", e.g. IDocs. In this case the RFC_SERVER_FUNCTION
	 *    can already commit/rollback its own work, before returning RFC_OK or an error code. So the two functions
	 *    RFC_ON_ROLLBACK_TRANSACTION and RFC_ON_COMMIT_TRANSACTION can be empty in this case.
	 * -# In the end RFC_ON_CONFIRM_TRANSACTION will be called. All information stored about that transaction can now be
	 *    discarded by the server, as it no longer needs to protect itself against duplicates.
	 *    In general this function can be used to delete the transaction ID from permanent storage.
	 *
	 * If you pass NULL as "sysId", the transaction handlers will be used for tRFC calls from any backend system,
	 * for which no explicit handlers have been installed.
	 *
	 * 
	 * \in *sysId System ID of the SAP system for which to use this set of transaction handlers, or NULL.
	 * \in onCheckFunction Pointer to a function of type RFC_ON_CHECK_TRANSACTION.
	 * \in onCommitFunction Pointer to a function of type RFC_ON_COMMIT_TRANSACTION.
	 * \in onRollbackFunction Pointer to a function of type RFC_ON_ROLLBACK_TRANSACTION.
	 * \in onConfirmFunction Pointer to a function of type RFC_ON_CONFIRM_TRANSACTION.
	 * \out *errorInfo Additional information, in case the handlers could not be installed.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInstallTransactionHandlers (SAP_UC const *sysId, RFC_ON_CHECK_TRANSACTION onCheckFunction,
											RFC_ON_COMMIT_TRANSACTION onCommitFunction, RFC_ON_ROLLBACK_TRANSACTION onRollbackFunction,
											RFC_ON_CONFIRM_TRANSACTION onConfirmFunction, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Installs the necessary callback functions for processing incoming bgRFC calls.
	 * \ingroup installer
	 * 
	 * These functions need to be implemented by you and will be used by the RFC runtime in the following way:
	 * -# The RFC_ON_CHECK_UNIT function is called when a local background unit is starting. Since a background 
	 *    RFC call can be issued many times by the client system, the function is responsible for storing the unit ID
	 *    and type in permanent storage. The return value should be one of the following:
	 *    - RFC_OK\n		Unit ID stored, LUW can be started.
	 *    - RFC_EXECUTED\n	This LUW has already been processed successfully in an earlier attempt. Skip the execution now.
	 *    - RFC_EXTERNAL_FAILURE\n Currently unable to access my permanent storage. Raise an exception in the sending system, so
	 *						that the sending system will try to resend the unit at a later time.
	 * -# The next step will be the execution of the RFC_SERVER_FUNCTIONs for all function modules contained in the LUW.
	 * -# If one of the RFC_SERVER_FUNCTION implementations returns an error code, RFC_ON_ROLLBACK_UNIT is called.
	 *    Here you should roll back all the work of all the previous RFC_SERVER_FUNCTIONs. (The easiest way is to do
	 *    a database ROLLBACK WORK here.)\n
	 *    If all RFC_SERVER_FUNCTIONs complete successfully, RFC_ON_COMMIT_UNIT is called at the end.
	 *    Persist all the changes here (e.g. do a COMMIT WORK).\n
	 *    Note: Normally you'll only have "one-function-module LUWs", e.g. IDocs. In this case the RFC_SERVER_FUNCTION
	 *    can already commit/rollback its own work, before returning RFC_OK or an error code. So the two functions
	 *    RFC_ON_ROLLBACK_UNIT and RFC_ON_COMMIT_UNIT can be empty in this case.
	 * -# In the end RFC_ON_CONFIRM_UNIT will be called. All information stored about that LUW can now be
	 *    discarded by the server, as it no longer needs to protect itself against duplicates.
	 *    In general this function can be used to delete the unit ID from permanent storage.
	 * -# At various points in the processing of a background unit, the backend system may or may not inquire
	 *    the status of the currently (or previously) processed unit by calling RFC_ON_GET_UNIT_STATE. Your implementation
	 *    of this function should check your permanent storage for status information about the given unit ID and
	 *    fill the RFC_UNIT_STATE* accordingly.
	 *
	 * If you pass NULL as "sysId", the transaction handlers will be used for bgRFC calls from any backend system,
	 * for which no explicit handlers have been installed.
	 *
	 * 
	 * \in *sysId System ID of the SAP system for which to use this set of transaction handlers, or NULL.
	 * \in onCheckFunction Pointer to a function of type RFC_ON_CHECK_UNIT.
	 * \in onCommitFunction Pointer to a function of type RFC_ON_COMMIT_UNIT.
	 * \in onRollbackFunction Pointer to a function of type RFC_ON_ROLLBACK_UNIT.
	 * \in onConfirmFunction Pointer to a function of type RFC_ON_CONFIRM_UNIT.
	 * \in onGetStateFunction Pointer to a function of type RFC_ON_GET_UNIT_STATE.
	 * \out *errorInfo Additional information, in case the handlers could not be installed.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInstallBgRfcHandlers (SAP_UC const *sysId, RFC_ON_CHECK_UNIT onCheckFunction,
											RFC_ON_COMMIT_UNIT onCommitFunction, RFC_ON_ROLLBACK_UNIT onRollbackFunction,
											RFC_ON_CONFIRM_UNIT onConfirmFunction, RFC_ON_GET_UNIT_STATE onGetStateFunction, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Installs the necessary callback functions for processing Extended Passport (EPP) events.
	 * \ingroup installer
	 * 
	 * Extended Passports is a feature that supersedes Distributed Statistical Records (DSRs).
	 * It allows to track certain performance attributes across system boundaries. These callback functions
	 * allow the application to exchange passports with the backend system. The actual data contained in the
	 * passports, can be processed with the eppslib library.
	 * \note Normal RFC applications should never need to deal with this topic at all...
	 * 
	 * 
	 * \in onClientCallStart Pointer to a function of type RFC_PM_CALLBACK. The RFC lib calls this function, before it sends a client request into the backend. Here you can provide the passport that is to be sent along with the RFC request.
	 * \in onClientCallEnd Pointer to a function of type RFC_PM_CALLBACK. The RFC lib calls this function, after the RFC response was received from the backend. You can read the updated passport information.
	 * \in onServerCallStart Pointer to a function of type RFC_PM_CALLBACK. The RFC lib calls this function, when it received an RFC request from the backend. Here you can read the passport that accompanied the request.
	 * \in onServerCallEnd Pointer to a function of type RFC_PM_CALLBACK. The RFC lib calls this function, before it will send the response to the above request back to the backend. You can update the passport data with information about processing performance of the current call.
	 * \out *errorInfo Additional information, in case the handlers could not be installed.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInstallPassportManager (RFC_PM_CALLBACK onClientCallStart,
											RFC_PM_CALLBACK onClientCallEnd,
											RFC_PM_CALLBACK onServerCallStart, 
											RFC_PM_CALLBACK onServerCallEnd, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Installs an optional callback function for processing password change events.
	 * \ingroup installer
	 * 
	 * Whenever a logon attempt is made with a user, whose password is still initial, the backend system
	 * challenges this user to change his/her password. If this happens during a call to RfcOpenConnection(),
	 * the RFC library calls this callback function (if installed), and allows you to change the user's password.
	 * In your implementation, you can either return RFC_EXTERNAL_FAILURE, if you can't/don't want to change
	 * the password. In that case RfcOpenConnection() will end with RFC_LOGON_FAILURE and any additional text from
	 * errorInfo->message will be returned to the application. Or you can fill the old and new password with correct
	 * values and return RFC_OK, upon which the RFC library will attempt to change the password accordingly.
	 * \note See also the documentation of the logon parameter PASSWORD_CHANGE_ENFORCED in the sample sapnwrfc.ini file,
	 * which specifies, whether the application is allowed to get by without a PasswordChangeHandler and keep using
	 * the initial/expired password for login.
	 *
	 * 
	 * \in onPasswordChange Pointer to a function of type RFC_ON_PASSWORD_CHANGE. The RFC lib calls this function, whenever an initial password is detected during a call to RfcOpenConnection().
	 * \out *errorInfo Additional information, in case the handler could not be installed.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInstallPasswordChangeHandler(RFC_ON_PASSWORD_CHANGE onPasswordChange, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Installs an optional callback function for performing authorization checks on incoming function calls.
	 * \ingroup installer
	 * 
	 * After an RFC call arrives at the RFC library, and before the library executes the corresponding
	 * server implementation for that function module, it calls this callback function, if installed.
	 * Here you can implement a central authorization check, defining exactly which user from which backend
	 * system is allowed to execute what functions in your RFC server program.
	 * The actual function module implementations can then concentrate on their business logic and don't
	 * need to pay attention to access and authorization checks.
	 * 
	 * 
	 * \in onAuthorizationCheck Pointer to a function of type RFC_ON_AUTHORIZATION_CHECK. The RFC lib calls this function, whenever an RFC request arrives from the backend.
	 * \out *errorInfo Additional information, in case the handler could not be installed.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInstallAuthorizationCheckHandler(RFC_ON_AUTHORIZATION_CHECK onAuthorizationCheck, RFC_ERROR_INFO* errorInfo);



    /* ***********************************************************************/
    /*                                                                       */
    /*  Data container API (Function modules, structures & tables)           */
    /*                                                                       */
    /* ***********************************************************************/

    /**
     * \brief  Creates a data container that can be used to execute function calls in the backend via RfcInvoke().
     * \ingroup container
     * 
	 * The importing parameters can be set using the RfcSetX functions. After the RfcInvoke() call returned
	 * successfully, the exporting parameters can be read from this data container via the RfcGetX functions.
	 *
     * 
     * \in funcDescHandle Metadata description ("blueprint") for the data container to be created.
     * \out *errorInfo Error information in case the parameters are incorrect or there's not enough memory.
     * \return A handle to the function module container.
     */
    DECL_EXP RFC_FUNCTION_HANDLE SAP_API RfcCreateFunction(RFC_FUNCTION_DESC_HANDLE funcDescHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Releases all memory used by the data container.
	 * \ingroup container
	 * 
	 * \warning Be careful: if you have obtained a handle to a structure (RFC_STRUCTURE_HANDLE) or
	 * table parameter (RFC_TABLE_HANDLE) from that function module, that handle will be invalid afterwards,
	 * as that memory will be released as well!
	 *
	 * 
	 * \in funcHandle Data container to release.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyFunction(RFC_FUNCTION_HANDLE funcHandle, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Allows to deactivate certain parameters in the function module interface.
     * \ingroup container
     * 
	 * This is particularly useful for BAPIs which have many large tables, in which you are not interested.
	 * Deactivate those and leave only those tables active, in which you are interested. This reduces
	 * network traffic and memory consumption in your application considerably.
	 *
	 * \note This functionality can be used for input and output parameters. If the parameter is an input,
	 * no data for that parameter will be sent to the backend. If it's an output, the backend will be
	 * informed not to return data for that parameter. 
     * 
     * \in funcHandle A function module data container.
     * \in *paramName The name of a parameter of this function module.
     * \in isActive 1 = activate, 0 = deactivate.
     * \out *errorInfo Error information in case something goes wrong (e.g. a parameter of that name does not exist).
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcSetParameterActive(RFC_FUNCTION_HANDLE funcHandle, SAP_UC const* paramName, int isActive, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Query whether a parameter is active.
     * \ingroup container
     * 
     * Useful for example in a server function implementation: Before creating a large table,
	 * you may want to check, whether the client (the backend system), has requested that table at all.
     * 
     * \in funcHandle A function module data container (usually handed to your server function from the RFC library).
     * \in *paramName The name of a parameter of this function module.
     * \out *isActive 1 = is active, 0 = is not active.
     * \out *errorInfo Error information in case something goes wrong (e.g. a parameter of that name does not exist).
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcIsParameterActive(RFC_FUNCTION_HANDLE funcHandle, SAP_UC const* paramName, int *isActive, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Creates a data container for a structure.
	 * \ingroup container
	 * 
	 * 
	 * \in typeDescHandle The metadata description (blueprint) for the structure to be created.
	 * \out *errorInfo Error information in case the parameters are incorrect or there's not enough memory.
	 * \return A handle to the structure.
	 */
	DECL_EXP RFC_STRUCTURE_HANDLE SAP_API RfcCreateStructure(RFC_TYPE_DESC_HANDLE typeDescHandle, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Clones a sructure including the data in it.
     * \ingroup container
     * 
     * 
     * \in srcStructureHandle The structure to clone.
     * \out *errorInfo Not enough memory?
     * \return A handle to the newly created copy of the input structure.
     */
    DECL_EXP RFC_STRUCTURE_HANDLE SAP_API RfcCloneStructure(RFC_STRUCTURE_HANDLE srcStructureHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Releases all memory for a particular structure
	 * \ingroup container
	 * 
	 * \warning Do not call this function on structures, which you have obtained from another data container
	 * (e.g. a function module) via RfcGetStructure(). In that case the memory will be released, when the
	 * parent container will be destroyed. If you destroy a child structure separately, you will get a
	 * segmentation fault, when the parent structure is destroyed!
	 * 
	 * \in structHandle Structure to release.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyStructure(RFC_STRUCTURE_HANDLE structHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Creates a data container for a table.
	 * \ingroup container
	 * 
	 * 
	 * \in typeDescHandle The metadata description (blueprint) for the line type of the table to be created.
	 * \out *errorInfo More details in case there was an invalid parameter or not enough memory.
	 * \return The freshly created table.
	 */
	DECL_EXP RFC_TABLE_HANDLE SAP_API RfcCreateTable(RFC_TYPE_DESC_HANDLE typeDescHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Clones a table including all the data in it. (Use with care...)
	 * \ingroup container
	 * 
	 * 
	 * \in srcTableHandle The table to duplicate.
	 * \out *errorInfo In case there is not enough memory.
	 * \return A handle to the cloned table.
	 */
	DECL_EXP RFC_TABLE_HANDLE SAP_API RfcCloneTable(RFC_TABLE_HANDLE srcTableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Releases the memory of a table and all its lines.
	 * \ingroup container
	 * 
	 * \warning Be careful: if you still have a reference to a certain table line (an RFC_STRUCTURE_HANDLE you got
	 * from RfcGetCurrentRow() / RfcAppendNewRow() / RfcInsertNewRow()), this handle will be invalid after %RfcDestroyTable()!
	 * Using a handle to a table line after the table has been destroyed, will lead to a segmentation fault.
	 * 
	 * \in tableHandle The table to release.
	 * \out *errorInfo Nothing can go wrong here...
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyTable(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the table row, on which the "table cursor" is currently positioned.
	 * \ingroup container
	 * 
	 * \note that the rows are numbered from 0 to n-1, not from 1 to n, as it's done in ABAP.
	 * 
	 * \in tableHandle The table to read data from.
	 * \out *errorInfo If the table cursor is not on a valid position.
	 * \return A handle to the current row.
	 * \warning Do not destroy the returned RFC_STRUCTURE_HANDLE.
	 */
	DECL_EXP RFC_STRUCTURE_HANDLE SAP_API RfcGetCurrentRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Appends a new empty row at the end of the table and moves the table cursor to that row.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle The table to enlarge.
	 * \out *errorInfo More information in case of errors (e.g. not enough memory).
	 * \return A handle to the newly created row.
	 */
	DECL_EXP RFC_STRUCTURE_HANDLE SAP_API RfcAppendNewRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

    /**
    * \brief  Reserves memory without changing the size of a table so that new rows can be appended without new memory allocation.
    * \ingroup container
    * 
    * 
    * \in tableHandle The table to enlarge.
    * \in numRows Number of rows to reserve.
    * \out *errorInfo More information in case of errors (e.g. not enough memory).
    * \return RFC_OK, RFC_INVALID_HANDLE or RFC_MEMORY_INSUFFICIENT.
    */
    DECL_EXP RFC_RC SAP_API RfcReserveCapacity(RFC_TABLE_HANDLE tableHandle, unsigned numRows, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Appends a set of new empty rows at the end of the table and moves the table cursor to the first new row.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle The table to enlarge.
	 * \in numRows Number of rows to add.
	 * \out *errorInfo More information in case of errors (e.g. not enough memory).
	 * \return RFC_OK, RFC_INVALID_HANDLE or RFC_MEMORY_INSUFFICIENT.
	 */
	DECL_EXP RFC_RC SAP_API RfcAppendNewRows(RFC_TABLE_HANDLE tableHandle, unsigned numRows, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Inserts a new empty row at the current position of the table cursor.
	 * \ingroup container
	 *
	 * The row, on which the table cursor is currently positioned, and all following rows are moved
	 * one index "down". E.g. if the table currently has rows nos 0 - n-1 and the cursor points to row i,
	 * then the rows i - n-1 are moved to positions i+1 - n, and the new row is inserted at position i.
	 * 
	 * 
	 * \in tableHandle The table to enlarge.
	 * \out *errorInfo More information in case of errors (e.g. not enough memory).
	 * \return A handle to the newly created row.
	 */
	DECL_EXP RFC_STRUCTURE_HANDLE SAP_API RfcInsertNewRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Appends an existing row to the end of the table and moves the table cursor to that row.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle The table to enlarge.
	 * \in structHandle The row to append to the table.
	 * \out *errorInfo More information in case something goes wrong (e.g. the line types of the table and the structure don't match).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcAppendRow(RFC_TABLE_HANDLE tableHandle, RFC_STRUCTURE_HANDLE structHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Inserts an existing row at the current position of the table cursor.
	 * \ingroup container
	 * 
	 * The row, on which the table cursor is currently positioned, and all following rows are moved
	 * one index "down". E.g. if the table currently has rows nos 0 - n-1 and the cursor points to row i,
	 * then the rows i - n-1 are moved to positions i+1 - n, and the given row is inserted at position i.
	 * 
	 * 
	 * \in tableHandle The table to enlarge.
	 * \in structHandle The row to insert into the table.
	 * \out *errorInfo More information in case something goes wrong (e.g. the line types of the table and the structure don't match).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcInsertRow(RFC_TABLE_HANDLE tableHandle, RFC_STRUCTURE_HANDLE structHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Deletes the row, on which the table cursor is currently positioned.
	 * \ingroup container
	 *
	 * If the row cursor is currently at an index i between 0 - n-2, then row i will be deleted and the
	 * rows i+1 - n-1 will be moved on index "up", e.g. will now be rows i - n-2. The table cursor will
	 * remain fixed at index i.\n
	 * If the cursor is currently on the last row (n-1), then that row will be deleted, all other position
	 * will remain unchanged, and the table cursor will move up to n-2 (the new last row of the table).
	 *
	 * 
	 * \in tableHandle The table from which to delete a row.
	 * \out *errorInfo Error information in case the table cursor is not on a valid position.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDeleteCurrentRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Deletes all rows from the table.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle The table to clear.
	 * \out *errorInfo Not much that can go wrong here (except an invalid table handle).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDeleteAllRows(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Positions the table cursor at the first row (or at index "-1", if the table is empty).
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle A table.
	 * \out *errorInfo Not much that can go wrong here (except an invalid table handle).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcMoveToFirstRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Positions the table cursor at the last row (or at index "-1", if the table is empty).
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle A table.
	 * \out *errorInfo Not much that can go wrong here (except an invalid table handle).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcMoveToLastRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Increments the table cursor by one.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle A table.
	 * \out *errorInfo Not much that can go wrong here (except an invalid table handle).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcMoveToNextRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Decrements the table cursor by one.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle A table.
	 * \out *errorInfo Not much that can go wrong here (except an invalid table handle).
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcMoveToPreviousRow(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the table cursor to a specific index.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle A table.
	 * \in index The index to which to move the cursor.
	 * \out *errorInfo Index out of bounds or invalid table handle.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcMoveTo(RFC_TABLE_HANDLE tableHandle, unsigned index, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the number of rows in a table.
	 * \ingroup container
	 * 
	 * 
	 * \in tableHandle A table.
	 * \out *rowCount The number of rows in the table.
	 * \out *errorInfo Not much that can go wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetRowCount(RFC_TABLE_HANDLE tableHandle, unsigned* rowCount, RFC_ERROR_INFO* errorInfo);

	/**
	* \brief  Returns a type description handle describing the line type (metadata) of this table.
	* \ingroup container
	*
	*
	* \in tableHandle A table.
	* \out *errorInfo Not much that can go wrong.
	* \return A type description handle that provides information about this table's fields (for each field: fieldname, the field's datatype, length, offset, etc.)
	*/
	DECL_EXP RFC_TYPE_DESC_HANDLE SAP_API RfcGetRowType(RFC_TABLE_HANDLE tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Creates an ABAP object handle with the given class description handle.
	 * \ingroup container
	 *
	 * \in classDescHandle   class description handle.
	 * \out *errorInfo  Contains more information, for example if memory runs out (code = RFC_MEMORY_INSUFFICIENT).
	 * \return A handle to the created ABAP object.
	 */
	DECL_EXP RFC_ABAP_OBJECT_HANDLE SAP_API RfcCreateAbapObject(RFC_CLASS_DESC_HANDLE classDescHandle, RFC_ERROR_INFO* errorInfo);

    /**
	 * \brief  Destroys an ABAP object handle.
	 * \ingroup container
	 *
	 * \in objHandle    ABAP object handle to be destroyed.
	 * \out *errorInfo  Should always return successfully.
	 * \return RFC_RC
	 */
    DECL_EXP RFC_RC SAP_API RfcDestroyAbapObject(RFC_ABAP_OBJECT_HANDLE objHandle, RFC_ERROR_INFO* errorInfo);


    /* ****************************************************************************
     *
     *  API for accessing the fields of a data container
     *
	 * API for reading the exporting parameters of an RFC_FUNCTION_HANDLE in the
	 * client case, the importing parameters of an RFC_FUNCTION_HANDLE in the
	 * server case and the fields of an RFC_STRUCTURE_HANDLE or RFC_TABLE_HANDLE.
     * ****************************************************************************/

	/**
	 * \brief  Returns the value of the specified field as char array.
	 * \ingroup container
	 * 
     * The charBuffer will be filled with a string representation of the given field. The remaining
     * places in the buffer will be filled with trailing spaces. In case the buffer is too small,
     * the function will return RFC_BUFFER_TOO_SMALL. The result will not be null-terminated.
	 *
     * The field specified by name needs to be of one of the following data types. If the field
	 * has one of the listed non-char-like data types, the RFC library will convert the field value
	 * to string format. Example:\n
	 * If "name" specifies a field of type INT4 with the value 4711 and charBuffer is an SAP_CHAR[10],
	 * then the buffer will be filled as follows: "4711      ".
	 *
     * \note If the target field has type BYTE or XSTRING, the bytes will be
     * converted to a hex encoded string representation.
	 *
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_NUM
     * - RFCTYPE_DATE
     * - RFCTYPE_TIME
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_UTCLONG
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field.
	 * \out *charBuffer A pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in RFC_CHARs.
	 * \out *errorInfo Field doesn't exist, cannot be converted to char, etc.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetChars(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_CHAR *charBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as char array.
	 * \ingroup container
	 * 
     * This function works exactly like RfcGetChars(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field.
	 * \out *charBuffer A pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in RFC_CHARs.
	 * \out *errorInfo Field doesn't exist, cannot be converted to char, etc.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetCharsByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_CHAR *charBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as num-char array (digits only).
	 * \ingroup container
	 * 
     * The charBuffer will be filled with a string representation of the field (from right to left).
     * The remaining places in the buffer will be filled with leading zero digits. In case
     * the buffer is too small, the function will return RFC_BUFFER_TOO_SMALL. The result is not
	 * null-terminated.
	 *
	 * The field specified by name needs to be of one of the following data types. If the field
	 * has one of the listed non-char-like data types, the RFC library will convert the field value
	 * to string format. Example:\n
	 * If "name" specifies a field of type INT4 with the value 4711 and charBuffer is an SAP_CHAR[10],
	 * then the buffer will be filled as follows: "0000004711".
     *
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_NUM
     * - RFCTYPE_DATE
     * - RFCTYPE_TIME
     * - RFCTYPE_INTx
     * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field.
	 * \out *charBuffer A pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in RFC_CHARs.
	 * \out *errorInfo Field doesn't exist, cannot be converted to numc, etc.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetNum(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_NUM *charBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as num-char array (digits only).
	 * \ingroup container
	 * 
     * This function works exactly like RfcGetNum(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
     * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field.
	 * \out *charBuffer A pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in RFC_CHARs.
	 * \out *errorInfo Field doesn't exist, cannot be converted to numc, etc.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetNumByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_NUM *charBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Reads a DATE field.
	 * \ingroup container
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read. The field must be of type RFCTYPE_DATE.
	 * \out emptyDate An RFC_DATE object, which will receive the field value.
	 * \out *errorInfo More information in case something goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetDate(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_DATE emptyDate, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Reads a DATE field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcGetDate(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read. The field must be of type RFCTYPE_DATE.
	 * \out emptyDate An RFC_DATE object, which will receive the field value.
	 * \out *errorInfo More information in case something goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetDateByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_DATE emptyDate, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Reads a TIME field.
	 * \ingroup container
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read. The field must be of type RFCTYPE_TIME.
	 * \out emptyTime An RFC_TIME object, which will receive the field value.
	 * \out *errorInfo More information in case something goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetTime(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_TIME emptyTime, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Reads a TIME field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcGetTime(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read. The field must be of type RFCTYPE_TIME.
	 * \out emptyTime An RFC_TIME object, which will receive the field value.
	 * \out *errorInfo More information in case something goes wrong.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetTimeByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_TIME emptyTime, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as null-terminated string.
	 * \ingroup container
     *
     * The charBuffer will be filled with a null-terminated string representation of the field value.
     * In case the buffer is too small, e.g. no place for string termination, the function will
     * return RFC_BUFFER_TOO_SMALL. stringLength contains the number of written characters, or the
     * required number of characters in case RFC_BUFFER_TOO_SMALL was thrown.
	 * The result will be null-terminated.
	 *
	 * The field specified by name needs to be of one of the following data types. If the field
	 * has one of the listed non-char-like data types, the RFC library will convert the field value
	 * to string format. Example:\n
	 * If "name" specifies a field of type INT4 with the value 4711 and stringBuffer is an SAP_UC[10],
	 * then the buffer will be filled as follows: "4711\0xxxxx". (x: left unchanged.)
     *
     * \note If the target field has type BYTE or XSTRING, the bytes will be
     * converted to a hex encoded string representation.
	 *
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_NUM
     * - RFCTYPE_DATE
     * - RFCTYPE_TIME
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_UTCLONG
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *stringBuffer Pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in SAP_UC.
	 * \out *stringLength Always returns the string's length, no matter whether the stringBuffer had
	 * been large enough or not. (Note that if you want to try again after an RFC_BUFFER_TOO_SMALL,
	 * you need to make the stringBuffer at least *stringLength + 1 in order to account for the terminating null.)
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetString(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, SAP_UC *stringBuffer, unsigned bufferLength, unsigned* stringLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as null-terminated string.
	 * \ingroup container
     *
     * This function works exactly like RfcGetString(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *stringBuffer Pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in SAP_UC.
	 * \out *stringLength Always returns the string's length, no matter whether the stringBuffer had
	 * been large enough or not. (Note that if you want to try again after an RFC_BUFFER_TOO_SMALL,
	 * you need to make the stringBuffer at least *stringLength + 1 in order to account for the termnating null.)
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetStringByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, SAP_UC *stringBuffer, unsigned bufferLength, unsigned* stringLength, RFC_ERROR_INFO* errorInfo);

    /**
	 * \brief  Returns the value of the specified field as byte array.
	 * \ingroup container
	 *
     * Should mainly be used with fields of type RAW (RFCTYPE_BYTE), but also works with
	 * a number of other data types. In case of numerical data types it simply gives the
	 * binary representation of the value, in case of character data types it gives the
	 * UTF-16 representation (little endian/big endian, depending on the host platform).
     * In case the buffer is too small, the function will return RFC_BUFFER_TOO_SMALL.
     * In case the buffer is longer than the field, it will be filled with 0x00 values.
	 * Example: The field is of type INT4 and contains the value 4711, byteBuffer is an SAP_RAW[10].
	 * Then the buffer will be filled as follows: 67 12 00 00 00 00 00 00 00 00 (little endian system)
	 * or 00 00 12 67 00 00 00 00 00 00 (big endian system).
	 *
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_CHAR
     * - RFCTYPE_NUM
     * - RFCTYPE_DATE
     * - RFCTYPE_TIME
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
     * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *byteBuffer Pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in bytes.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetBytes(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, SAP_RAW *byteBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as byte array.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetBytes(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
     * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *byteBuffer Pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in bytes.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetBytesByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, SAP_RAW *byteBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as byte array.
	 * \ingroup container
     *
     * In case the buffer is too small, the function will return RFC_BUFFER_TOO_SMALL.
     * xstringLength contains the number of written bytes, or the required number of bytes
     * in case of RFC_BUFFER_TOO_SMALL.
     * The remaining buffer won't be changed.
	 * 
	 * Example: The field is of type INT4 and contains the value 4711, byteBuffer is an SAP_RAW[10].
	 * Then the buffer will be filled as follows: 67 12 00 00 x x x x x x (little endian system)
	 * or 00 00 12 67 x x x x x x (big endian system). (x: unchanged) In both cases *xstringLength
	 * will be 4.
	 * 
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_CHAR
     * - RFCTYPE_NUM
     * - RFCTYPE_DATE
     * - RFCTYPE_TIME
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *byteBuffer Pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in bytes.
	 * \out *xstringLength Byte length of the result (in both cases, no matter whether the byteBuffer had
	 * been large enough or not).
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetXString(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, SAP_RAW *byteBuffer, unsigned bufferLength, unsigned* xstringLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as byte array.
	 * \ingroup container
     *
     * This function works exactly like RfcGetXString(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *byteBuffer Pre-allocated buffer, which will receive the (converted) field value.
	 * \in bufferLength Size of the buffer in bytes.
	 * \out *xstringLength Byte length of the result (in both cases, no matter whether the byteBuffer had
	 * been large enough or not).
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetXStringByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, SAP_RAW *byteBuffer, unsigned bufferLength, unsigned* xstringLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as RFC_INT (signed).
	 * \ingroup container
     *
     * If the field is a character type, an "atoi-like" conversion is performed. If the field is of type
	 * RFCTYPE_BYTE/RFCTYPE_XSTRING, this function interprets the bytes in big-endian byte order when
     * converting them to int. Note that in this case the byte length of the field value must not exceed 4!
	 * 
     * The field specified by name needs to be of one of the following data types:
	 * <ul>
	 * <li>RFCTYPE_INT8
     * <li>RFCTYPE_INT
     * <li>RFCTYPE_INT2
     * <li>RFCTYPE_INT1
     * <li>RFCTYPE_BYTE     is interpreted as big endian sequence of an int
     * <li>RFCTYPE_XSTRING  is interpreted as big endian sequence of an int
     * <li>RFCTYPE_CHAR
     * <li>RFCTYPE_NUM
     * <li>RFCTYPE_STRING
	 * </ul>
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *value The (converted) integer value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */

	DECL_EXP RFC_RC SAP_API RfcGetInt(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_INT  *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the specified field as RFC_INT (signed).
	 * \ingroup container
     *
     * This function works exactly like RfcGetInt(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *value The (converted) integer value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetIntByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_INT  *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of a field as an unsigned one byte integer.
	 * \ingroup container
	 *
	 * The current field value must not be bigger than 255, otherwise you'll get an RFC_CONVERSION_ERROR.
	 * If the field is of type RFCTYPE_BYTE/RFCTYPE_XSTRING, the field length must be 1 byte.
	 *
     * The field specified by name needs to be of one of the following data types:
	 * <ul>
	 * <li>RFCTYPE_INT8
     * <li>RFCTYPE_INT
     * <li>RFCTYPE_INT2
     * <li>RFCTYPE_INT1
     * <li>RFCTYPE_BYTE
     * <li>RFCTYPE_XSTRING
	 * </ul>
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *value The (converted) integer value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetInt1(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_INT1 *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of a field as an unsigned one byte integer.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetInt1(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *value The (converted) integer value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetInt1ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_INT1 *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the field value as a signed two byte integer.
	 * \ingroup container
	 *
	 * The current field value must be between -32768 and 32767, otherwise you'll get an RFC_CONVERSION_ERROR.
	 * If the field is of type RFCTYPE_BYTE/RFCTYPE_XSTRING, the field length must be 1 or 2 bytes.
	 *
     * The field specified by name needs to be of one of the following data types:
	 * <ul>
	 * <li>RFCTYPE_INT8
     * <li>RFCTYPE_INT
     * <li>RFCTYPE_INT2
     * <li>RFCTYPE_INT1
     * <li>RFCTYPE_BYTE     is interpreted as big endian sequence of a short
     * <li>RFCTYPE_XSTRING  is interpreted as big endian sequence of a short
	 * </ul>
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *value The (converted) integer value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetInt2(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_INT2 *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the field value as a signed two byte integer.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetInt2(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *value The (converted) integer value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetInt2ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_INT2 *value, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Returns the field value as a signed eight byte integer.
	* \ingroup container
	*
	* If the field is of type RFCTYPE_BYTE/RFCTYPE_XSTRING, the field length must be 1, 2, 4 or 8 bytes.
	*
	* The field specified by name needs to be of one of the following data types:
	* - RFCTYPE_INT8
	* - RFCTYPE_INT
	* - RFCTYPE_INT2
	* - RFCTYPE_INT1
	* - RFCTYPE_BYTE     is interpreted as big endian sequence of a long long
	* - RFCTYPE_XSTRING  is interpreted as big endian sequence of a long long
    * - RFCTYPE_UTCLONG
	*
	*
	* \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	* is a table handle, the function will read the field value of the current row.
	* \in *name The name of the field to read.
	* \out *value The (converted) integer value.
	* \out *errorInfo More information in case the field does not exist or a conversion fails.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetInt8(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_INT8* value, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Returns the field value as a signed eight byte integer.
	* \ingroup container
	*
	* This function works exactly like RfcGetInt8(), the difference being that the field is
	* addressed by its index within the structure/table/function module. The first field has index 0,
	* last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	*
	*
	* \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	* is a table handle, the function will read the field value of the current row.
	* \in index The index of the field to read.
	* \out *value The (converted) integer value.
	* \out *errorInfo More information in case the field does not exist or a conversion fails.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetInt8ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_INT8* value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the given field as an RFC_FLOAT.
	 * \ingroup container
	 * 
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *value The floating point value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetFloat(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_FLOAT *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the value of the given field as an RFC_FLOAT.
	 * \ingroup container
	 * 
     * This function works exactly like RfcGetFloat(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *value The floating point value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetFloatByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_FLOAT *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the field as an 8 byte IEEE 754r decimal floating point.
	 * \ingroup container
	 *
	 * See the header sapdecf.h for how to work with RFC_DECF16 objects. If the field has a binary
	 * data type, its field length needs to be 8 bytes.
	 *
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_DECF16
     * - RFCTYPE_DECF34
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
	 * - RFCTYPE_INT8
     * - RFCTYPE_INT
     * - RFCTYPE_INT2
     * - RFCTYPE_INT1
     * - RFCTYPE_CHAR
     * - RFCTYPE_NUM
     * - RFCTYPE_STRING
     * - RFCTYPE_BYTE     is interpreted as IEEE 754r format
     * - RFCTYPE_XSTRING  is interpreted as IEEE 754r format
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *value The (converted) decimal floating point value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetDecF16(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_DECF16 *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the field as an 8 byte IEEE 754r decimal floating point.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetDecF16(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *value The (converted) decimal floating point value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetDecF16ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_DECF16 *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the field as a 16 byte IEEE 754r decimal floating point.
	 * \ingroup container
	 *
	 * See the header sapdecf.h for how to work with RFC_DECF16 objects. If the field has a binary
	 * data type, its field length needs to be 16 bytes.
	 *
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_DECF16
     * - RFCTYPE_DECF34
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
	 * - RFCTYPE_INT8
     * - RFCTYPE_INT
     * - RFCTYPE_INT2
     * - RFCTYPE_INT1
     * - RFCTYPE_CHAR
     * - RFCTYPE_NUM
     * - RFCTYPE_STRING
     * - RFCTYPE_BYTE     is interpreted as IEEE 754r format
     * - RFCTYPE_XSTRING  is interpreted as IEEE 754r format
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *value The (converted) decimal floating point value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetDecF34(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_DECF34 *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the field as a 16 byte IEEE 754r decimal floating point.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetDecF34(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *value The (converted) decimal floating point value.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetDecF34ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_DECF34 *value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns a handle to a structure.
	 * \ingroup container
	 *
	 * The field specified by name must be of type RFCTYPE_STRUCTURE. If that field has not yet
	 * been accessed/filled previously, a new empty structure is created from the metadata of the
	 * parent data container ("dataHandle") and returned.
	 * \warning The memory of that data container will be released, when the parent container gets
	 * destroyed. So don't destroy the returned structure handle, nor continue to use it, after the
	 * parent has been destroyed!
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *structHandle A handle to the sub-structure.
	 * \out *errorInfo Field does not exist, is of wrong type or out of memory.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetStructure(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_STRUCTURE_HANDLE* structHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns a handle to a structure.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetStructure(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *structHandle A handle to the sub-structure.
	 * \out *errorInfo Field does not exist, is of wrong type or out of memory.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetStructureByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_STRUCTURE_HANDLE* structHandle, RFC_ERROR_INFO* errorInfo);

	/**
	* \brief  Returns the entire structure value as a single char buffer.
	* \ingroup container
	*
	* The charBuffer will be filled with the data of the structure as if it were a single char field.
	*
	* In case the buffer is too small, the function will return RFC_BUFFER_TOO_SMALL. 
	* The result will <b>not</b> be null-terminated.
	*
	* This mimics the way structures have been handled by the classic RFC library librfc32.
	* It can conveniently be used for fetching an RFC structure into a C struct, which has been defined
	* like in the ABAP DDIC.
	* In addition to programming convenience, it should also improve runtime performance compared to fetching
	* each single field one-by-one.
	* 
	* This function can only be applied to structures/tables if they contain char-like fields (CHAR, NUMC, DATE, TIME)
	* The result will be aligned exactly as on ABAP side, including padding bytes.
	*
	* \in dataHandle A data container (structure handle or table handle). If dataHandle
	* is a table handle, the function will read the structure data of the current row.
	* \out *charBuffer Pre-allocated buffer, which will receive the structure value.
	* \in bufferLength Size of the buffer in SAP_UC.
	* \out *errorInfo More information in case the structure cannot be returned as char buffer.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetStructureIntoCharBuffer(DATA_CONTAINER_HANDLE dataHandle, SAP_UC *charBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns a handle to a table.
	 * \ingroup container
	 *
	 * The field specified by name must be of type RFCTYPE_TABLE. If that field has not yet
	 * been accessed/filled previously, a new empty structure is created from the metadata of the
	 * parent data container ("dataHandle") and returned.
	 * \warning The memory of that data container will be released, when the parent container gets
	 * destroyed. So don't destroy the returned table handle, nor continue to use it, after the
	 * parent has been destroyed!
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *tableHandle A handle to the sub-table.
	 * \out *errorInfo Field does not exist, is of wrong type or out of memory.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetTable(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_TABLE_HANDLE* tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns a handle to a table.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetTable(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *tableHandle A handle to the sub-table.
	 * \out *errorInfo Field does not exist, is of wrong type or out of memory.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetTableByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_TABLE_HANDLE* tableHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns a handle to an abap object.
	 * \ingroup container
	 *
	 * The field specified by name must be of type RFCTYPE_ABAPOBJECT. If that field has not yet
	 * been filled previously, NULL is returned.
	 * \warning The memory of that data container will be released, when the parent container gets
	 * destroyed. So don't destroy the returned table handle, nor continue to use it, after the
	 * parent has been destroyed!
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle, table handle or object handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of the field to read.
	 * \out *objHandle A handle to the object.
	 * \out *errorInfo Field does not exist, is of wrong type or out of memory.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetAbapObject(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, RFC_ABAP_OBJECT_HANDLE* objHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns a handle to an abap object.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetAbapObject(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle, table handle or object handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of the field to read.
	 * \out *objHandle A handle to the object.
	 * \out *errorInfo Field does not exist, is of wrong type or out of memory.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetAbapObjectByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, RFC_ABAP_OBJECT_HANDLE* objHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the length of the value of a STRING or XSTRING parameter.
	 * \ingroup container
	 *
	 * The field specified by name must be of type RFCTYPE_STRING or RFCTYPE_XSTRING. If that field is
	 * of type STRING, the returned length is measured in characters, otherwise in bytes.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in *name The name of a STRING or XSTRING field.
	 * \out *stringLength Length of the current field value.
	 * \out *errorInfo Wrong field type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetStringLength(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, unsigned* stringLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the length of the value of a STRING or XSTRING parameter.
	 * \ingroup container
	 *
     * This function works exactly like RfcGetStringLength(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will read the field value of the current row.
	 * \in index The index of a STRING or XSTRING field.
	 * \out *stringLength Length of the current field value.
	 * \out *errorInfo Wrong field type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetStringLengthByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, unsigned* stringLength, RFC_ERROR_INFO* errorInfo);



	/* *****************************************************************************
	 *
	 * API for setting the importing parameters of an RFC_FUNCTION_HANDLE in the
	 * client case, the exporting parameters of an RFC_FUNCTION_HANDLE in the server
	 * case and the subfields of an RFC_STRUCTURE_HANDLE or RFC_TABLE_HANDLE.
	 *
	 *******************************************************************************/

	/**
	 * \brief  Sets the given char value (charValue/valueLength) into the field.
	 * \ingroup container
     *
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_NUM
     * - RFCTYPE_DATE
     * - RFCTYPE_TIME
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_UTCLONG
	 *
     * \note If the target field is a numerical type, the RFC library tries to convert the string
	 * to a number. If the target field has type BYTE or XSTRING, the char value will be interpreted as
     * hex encoded string representation of the bytes. Its length needs to be even in that case.\n
	 * Example: the 8 characters "CAFEBABE" will be converted to 4 bytes 0xCA 0xFE 0xBA 0xBE.
	 *
	 * If the value cannot be converted to the desired target type, RFC_CONVERSION_ERROR will be
	 * returned.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in *charValue The characters to write into the field.
	 * \in valueLength The number of characters to read from charValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetChars(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_CHAR *charValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the given char value (charValue/valueLength) into the field.
	 * \ingroup container
     *
     * This function works exactly like RfcSetChars(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in *charValue The characters to write into the field.
	 * \in valueLength The number of characters to read from charValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetCharsByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_CHAR *charValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of a NUMC field.
	 * \ingroup container
	 * 
	 * The target field needs to be of type RFCTYPE_NUM.
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in *charValue The digits [0..9] to write into the field.
	 * \in valueLength The number of characters to read from charValue.
	 * \out *errorInfo More information in case the field does not exist or the parameter value is invalid.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetNum(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_NUM *charValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of a NUMC field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetNum(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in *charValue The digits [0..9] to write into the field.
	 * \in valueLength The number of characters to read from charValue.
	 * \out *errorInfo More information in case the field does not exist or the parameter value is invalid.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetNumByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_NUM *charValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the given string value (stringValue/valueLength) into the field.
	 * \ingroup container
     *
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_NUM
     * - RFCTYPE_DATE
     * - RFCTYPE_TIME
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_UTCLONG
	 *
     * \note If the target field is a numerical type, the RFC library tries to convert the string
	 * to a number. If the target field has type BYTE or XSTRING, the char value will be interpreted as
     * hex encoded string representation of the bytes. Its length needs to be even in that case.\n
	 * Example: the 8 characters "CAFEBABE" will be converted to 4 bytes 0xCA 0xFE 0xBA 0xBE.
	 *
	 * If the value cannot be converted to the desired target type, RFC_CONVERSION_ERROR will be
	 * returned.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in *stringValue The characters to write into the field.
	 * \in valueLength The number of characters to read from stringValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetString(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const SAP_UC *stringValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the given string value (stringValue/valueLength) into the field.
	 * \ingroup container
     *
     * This function works exactly like RfcSetString(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in *stringValue The characters to write into the field.
	 * \in valueLength The number of characters to read from stringValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetStringByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const SAP_UC *stringValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of a DATE field.
	 * \ingroup container
	 * 
	 * The target field needs to be of type RFCTYPE_DATE.
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in date The date value to write into the field.
	 * \out *errorInfo Is the field not of type DATE?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetDate(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_DATE date, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of a DATE field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetDate(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in date The date value to write into the field.
	 * \out *errorInfo Is the field not of type DATE?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetDateByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_DATE date, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of a TIME field.
	 * \ingroup container
	 * 
	 * The target field needs to be of type RFCTYPE_TIME.
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in time The time value to write into the field.
	 * \out *errorInfo Is the field not of type TIME?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTime(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_TIME time, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of a TIME field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetTime(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in time The time value to write into the field.
	 * \out *errorInfo Is the field not of type TIME?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTimeByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_TIME time, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the given byte value (byteValue/valueLength) into the field.
	 * \ingroup container
     *
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
     * \note: If the target field has type CHAR or STRING, the byte value
     * will be stored as a hex representation of the bytes.\n
     * If the target field has a numerical type, the byte value will be
     * assigned only if the given valueLength matches the field length.
	 * In order to use this feature, you need to know exactly what you are doing...
	 * E.g. when setting 8 bytes into an RFC_FLOAT field, you need to understand the
	 * IEEE floating point format. Better only use this function for setting RAW fields.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in *byteValue The byte value to write into the field.
	 * \in valueLength The number of bytes to use from byteValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetBytes(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const SAP_RAW *byteValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the given byte value (byteValue/valueLength) into the field.
	 * \ingroup container
     *
     * This function works exactly like RfcSetBytes(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in *byteValue The byte value to write into the field.
	 * \in valueLength The number of bytes to use from byteValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetBytesByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const SAP_RAW *byteValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the given byte value (byteValue/valueLength) into the field.
	 * \ingroup container
     *
     * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_BYTE
     * - RFCTYPE_XSTRING
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_INTx
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_DECFxx
     * \note: If the target field has type CHAR or STRING, the byte value
     * will be stored as a hex representation of the bytes.\n
     * If the target field has a numerical type, the byte value will be
     * assigned only if the given valueLength matches the field length.
	 * In order to use this feature, you need to know exactly what you are doing...
	 * E.g. when setting 8 bytes into an RFC_FLOAT field, you need to understand the
	 * IEEE floating point format. Better only use this function for setting RAW fields.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in *byteValue The byte value to write into the field.
	 * \in valueLength The number of bytes to use from byteValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetXString(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const SAP_RAW *byteValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the given byte value (byteValue/valueLength) into the field.
	 * \ingroup container
     *
     * This function works exactly like RfcSetXString(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in *byteValue The byte value to write into the field.
	 * \in valueLength The number of bytes to use from byteValue.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetXStringByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const SAP_RAW *byteValue, unsigned valueLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT4 field.
	 * \ingroup container
	 * 
	 * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_INTx
     * - RFCTYPE_DECFxx
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetInt(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_INT  value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT4 field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetInt(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetIntByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_INT  value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT1 field.
	 * \ingroup container
	 * 
	 * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_INTx
     * - RFCTYPE_DECFxx
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetInt1(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_INT1 value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT1 field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetInt1(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetInt1ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_INT1 value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT2 field.
	 * \ingroup container
	 * 
	 * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_INTx
     * - RFCTYPE_DECFxx
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetInt2(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_INT2 value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT2 field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetInt2(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetInt2ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_INT2 value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT8 field.
	 * \ingroup container
	 *
	 * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_INTx
     * - RFCTYPE_DECFxx
	 * - RFCTYPE_UTCLONG.
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetInt8(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_INT8 value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an INT8 field.
	 * \ingroup container
	 *
	 * This function works exactly like RfcSetInt8(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 *
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The integer value to set.
	 * \out *errorInfo More information in case the field does not exist or a conversion fails.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetInt8ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_INT8 value, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Sets a floating point field.
	 * \ingroup container
	 *
	 * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_CHAR
     * - RFCTYPE_STRING
     * - RFCTYPE_NUM
     * - RFCTYPE_DECF16
     * - RFCTYPE_DECF34
	 * \note If the target field is CHAR or STRING, the value will be converted to a string in
	 * scientific notation. If it is NUMC, it will be truncated to the next integer.
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The double value to set.
	 * \out *errorInfo Field does not exist or is not of a supported type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetFloat(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_FLOAT value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets a floating point field.
	 * \ingroup container
	 *
     * This function works exactly like RfcSetFloat(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The double value to set.
	 * \out *errorInfo Field does not exist or is not of a supported type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetFloatByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_FLOAT value, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Sets the value of an 8 byte decfloat object into a field.
	 * \ingroup container
	 * 
	 * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_DECF16
     * - RFCTYPE_DECF34
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_INT
     * - RFCTYPE_INT2
     * - RFCTYPE_INT1
     * - RFCTYPE_CHAR
     * - RFCTYPE_NUM
     * - RFCTYPE_STRING
     * - RFCTYPE_BYTE     Needs to be 8 byte long.
     * - RFCTYPE_XSTRING
	 * \note If the target field is CHAR or STRING, the value will be converted to a string in
	 * scientific notation. If it is NUMC, it will be truncated to the next integer.
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The decfloat value to set.
	 * \out *errorInfo Field does not exist or is not of a supported type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetDecF16(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_DECF16 value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of an 8 byte decfloat object into a field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetDecF16(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The decfloat value to set.
	 * \out *errorInfo Field does not exist or is not of a supported type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetDecF16ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_DECF16 value, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Sets the value of a 16 byte decfloat object into a field.
	 * \ingroup container
	 * 
	 * The field specified by name needs to be of one of the following data types:
     * - RFCTYPE_DECF16
     * - RFCTYPE_DECF34
     * - RFCTYPE_FLOAT
     * - RFCTYPE_BCD
     * - RFCTYPE_INT
     * - RFCTYPE_INT2
     * - RFCTYPE_INT1
     * - RFCTYPE_CHAR
     * - RFCTYPE_NUM
     * - RFCTYPE_STRING
     * - RFCTYPE_BYTE     Needs to be 8 byte long.
     * - RFCTYPE_XSTRING
	 * \note If the target field is CHAR or STRING, the value will be converted to a string in
	 * scientific notation. If it is NUMC, it will be truncated to the next integer.
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The decfloat value to set.
	 * \out *errorInfo Field does not exist or is not of a supported type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetDecF34(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_DECF34 value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the value of a 16 byte decfloat object into a field.
	 * \ingroup container
	 * 
     * This function works exactly like RfcSetDecF34(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 * 
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The decfloat value to set.
	 * \out *errorInfo Field does not exist or is not of a supported type?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetDecF34ByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_DECF34 value, RFC_ERROR_INFO* errorInfo);


	/**
	 * \brief  Copies the given structure into the target structure of the parent container.
	 * \ingroup container
	 *
	 * The target field needs to be of type RFCTYPE_STRUCTURE.
	 *
	 * \note If you want to avoid the copy operation, use RfcGetStructure() and set the subfields here,
	 * instead of the sequence RfcCreateStructure()/ setting the subfields/ #RfcSetStructure().
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The structure to copy.
	 * \out *errorInfo Out of memory, field does not exist or is not of type RFCTYPE_STRUCTURE?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetStructure(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_STRUCTURE_HANDLE value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Copies the given structure into the target structure of the parent container.
	 * \ingroup container
	 *
     * This function works exactly like RfcSetStructure(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The structure to copy.
	 * \out *errorInfo Out of memory, field does not exist or is not of type RFCTYPE_STRUCTURE?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetStructureByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_STRUCTURE_HANDLE value, RFC_ERROR_INFO* errorInfo);

	/**
	* \brief Set single char value buffer to the entire structure.
	* \ingroup container
	*
	* The structure will be filled with the data of bufferas if it were a single char field.
	*
	* In case the buffer is too small, the function will return RFC_BUFFER_TOO_SMALL.
	* The result will <b>not</b> be null-terminated.
	*
	* This mimics the way structures have been handled by the classic RFC library librfc32.
	* It can conveniently be used for fetching an RFC structure into a C struct, which has been defined
	* like in the ABAP DDIC.
	* In addition to programming convenience, it should also improve runtime performance compared to fetching
	* each single field one-by-one.
	*
	* This function can only be applied to structures/tables if they contain char-like fields (CHAR, NUMC, DATE, TIME)
	* The result will be aligned exactly as on ABAP side, including padding bytes.
	*
	* \out dataHandle A data container (structure handle or table handle). If dataHandle
	* is a table handle, the function will read the structure data of the current row.
	* \in *charBuffer Pre-allocated buffer, which will receive the structure value.
	* \in bufferLength Size of the buffer in SAP_UC.
	* \out *errorInfo More information in case the structure cannot be returned as char buffer.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcSetStructureFromCharBuffer(DATA_CONTAINER_HANDLE dataHandle, SAP_UC *charBuffer, unsigned bufferLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Copies the given table into the target table of the parent container.
	 * \ingroup container
	 *
	 * The target field needs to be of type RFCTYPE_TABLE.
	 *
	 * \note If you want to avoid the copy operation, use RfcGetTable() and set the subfields here,
	 * instead of the sequence RfcCreateTable()/ setting the subfields/ #RfcSetTable().
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The table to copy.
	 * \out *errorInfo Field does not exist or is not of type RFCTYPE_TABLE?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTable(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_TABLE_HANDLE value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Copies the given table into the target table of the parent container.
	 * \ingroup container
	 *
     * This function works exactly like RfcSetTable(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle or table handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The table to copy.
	 * \out *errorInfo Field does not exist or is not of type RFCTYPE_TABLE?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetTableByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_TABLE_HANDLE value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Copies the object into the target object of the parent container.
	 * \ingroup container
	 *
	 * The target field needs to be of type RFCTYPE_ABAPOBJECT.
	 *
	 * \note If you want to avoid the copy operation, use RfcGetAbapObject() and if the instance already exists set the subfields here,
	 * instead of the sequence RfcCreateAbapObject()/ setting the subfields/ #RfcSetAbapObject().
	 *
	 * \in dataHandle A data container (function handle, structure handle, table handle or object handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *name The name of the field to set.
	 * \in value The object to copy.
	 * \out *errorInfo Field does not exist or is not of type RFCTYPE_ABAPOBJECT?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetAbapObject(DATA_CONTAINER_HANDLE dataHandle, SAP_UC const* name, const RFC_ABAP_OBJECT_HANDLE value, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Copies the object into the target object of the parent container.
	 * \ingroup container
	 *
     * This function works exactly like RfcSetAbapObject(), the difference being that the field is
	 * addressed by its index within the structure/table/function module. The first field has index 0,
	 * last field has index n-1, the order of the fields is as defined in the ABAP DDIC.
	 * 
	 *
	 * \in dataHandle A data container (function handle, structure handle, table handle or object handle). If dataHandle
	 * is a table handle, the function will set the field value of the current row.
	 * \in *index The index of the field to set.
	 * \in value The object to copy.
	 * \out *errorInfo Field does not exist or is not of type RFCTYPE_ABAPOBJECT?
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcSetAbapObjectByIndex(DATA_CONTAINER_HANDLE dataHandle, unsigned index, const RFC_ABAP_OBJECT_HANDLE value, RFC_ERROR_INFO* errorInfo);


    /**
	 * \brief  Gets the ABAP exception object handle from the given function handle.
	 * \ingroup container
	 * 
	 * If a call to #RfcInvoke() returned RFC_ABAP_CLASS_EXCEPTION, the RFC client calls this function afterwards with the original function handle
	 * in order to get access to the details of the class exception.
	 * \in funcHandle   Function module data container.
	 * \out *errorInfo  Should always return successfully.
	 * \return A handle to an ABAP class exception object .
	 */
	DECL_EXP RFC_ABAP_OBJECT_HANDLE SAP_API RfcGetAbapClassException(RFC_FUNCTION_HANDLE funcHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Sets the ABAP exception object handle to the given function handle.
	 * \ingroup container
	 *
	 * If an RFC server function wants to throw an ABAP class exception, it calls this function before it returns with RFC_ABAP_CLASS_EXCEPTION.  
	 * \in funcHandle   Function module data container .
	 * \in excpHandle   Object handle to the class exception to be thrown.
	 * \in exceptionText  Exception text.
	 * \out *errorInfo  Should always return successfully.
	 * \return RFC_RC
	 */
    DECL_EXP RFC_RC SAP_API RfcSetAbapClassException(RFC_FUNCTION_HANDLE funcHandle, RFC_ABAP_OBJECT_HANDLE excpHandle, const SAP_UC *exceptionText,  RFC_ERROR_INFO* errorInfo);

	/**
     * \brief  Returns the metadata description for the given function module.
     * \ingroup container
     * 
     * 
     * \in funcHandle A function module.
     * \out *errorInfo Can't possibly go wrong...
     * \return The metadata description that had been used when creating the function module container.
     */
    DECL_EXP RFC_FUNCTION_DESC_HANDLE SAP_API RfcDescribeFunction(RFC_FUNCTION_HANDLE funcHandle, RFC_ERROR_INFO* errorInfo);
    
    /**
     * \brief  Returns the metadata description of the given structure or table (RFC_STRUCTURE_HANDLE or RFC_TABLE_HANDLE).
     * \ingroup container
     * 
     * 
     * \in dataHandle A structure or table.
     * \out *errorInfo Can't possibly go wrong...
     * \return The type description of the given structure (in case dataHandle is a structure), or the
	 * type description of the table line type (in case dataHandle is a table).
     */
    DECL_EXP RFC_TYPE_DESC_HANDLE SAP_API RfcDescribeType(DATA_CONTAINER_HANDLE dataHandle, RFC_ERROR_INFO* errorInfo);


    /* ************************************************************************/
    /*                                                                       */
    /*  Metadata and Repository API                                          */
    /*                                                                       */
    /* ************************************************************************/
	
    /* 1. Repository API */

	/**
	 * \brief  Returns the function description that is valid for the system to which rfcHandle points to.
	 * \ingroup repository
	 * 
     * If the function description is already in the repository cache for that system ID, it will be 
	 * returned immediately (from the cache), otherwise it will be looked up in the system's DDIC using
	 * the rfcHandle. The result from the DDIC lookup will then be placed into the cache for later use.
	 *
	 * The RFC Runtime maintains a cache for every R/3 System ID, as the meta data could be different
	 * from R/3 release to R/3 release.
     * This is the main API that should be used.
	 * 
	 * \in rfcHandle Open client connection to the R/3 System, for which you need the function module description.
	 * \in *funcName Name of the function module to look up.
	 * \out *errorInfo More error details in case something goes wrong.
	 * \return The metadata description of the given function module.
	 */
	DECL_EXP RFC_FUNCTION_DESC_HANDLE SAP_API RfcGetFunctionDesc(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const * funcName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Looks for a cached function description. 
	 * \ingroup repository
	 * 
     * This API should be used with care and is only for special scenarios, for example:
	 * 1. You know for sure, that a function description has already been cached via RfcGetFunctionDesc(),
	 *    and don't want to open an extra rfcHandle that will never be used.
	 *    In this case simply use the SAP System ID as the repositoryID.
	 * 2. You have created a hard-coded repository via RfcAddFunctionDesc(), which contains function modules
	 *    that do not exist in the backend's DDIC.
     * 
     * If repositoryID is NULL, the "default repository" is used.
	 * 
	 * \in *repositoryID System ID of R/3 System, for which this function module description has been cached,
	 * or NULL in case you want to look for it in the default repository.
	 * \in *funcName Name of the function module.
	 * \out *errorInfo Requested function name not in cache?
	 * \return The requested function description.
	 */
	DECL_EXP RFC_FUNCTION_DESC_HANDLE SAP_API RfcGetCachedFunctionDesc(SAP_UC const * repositoryID, SAP_UC const * funcName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Adds a function description to the cache for the specified R/3 System.
	 * \ingroup repository
     * 
     * This API should be used with care and is only for special scenarios, e.g. if you want to
	 * write an RFC server that offers function modules, which do not exist in the R/3 system's DDIC.
     * If repositoryID is NULL, the description is added to the "default repository".
	 * 
	 * 
	 * \in *repositoryID System ID of R/3 System, to whose cache you want to add the function description,
	 * or NULL for the default repository.
	 * \in funcDesc The function description.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcAddFunctionDesc(SAP_UC const * repositoryID, RFC_FUNCTION_DESC_HANDLE funcDesc, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Removes a function description from the cache for the specified R/3 System.
	 * \ingroup repository
     * 
     * This API can be used, e.g. if the signature (imports, exports, etc.) of a function module has
	 * been changed in the backend, while the external RFC program is still running. If the RFC library
	 * continues using the old cached metadata description, garbage values (if fields have been deleted
	 * from the function module) or missing values (if new fields have been added to the function module)
	 * will result.
     * If repositoryID is NULL, the description is removed from the "default repository".
	 * 
	 * 
	 * \in *repositoryID System ID of R/3 System, to whose cache you want to add the function description,
	 * or NULL for the default repository.
	 * \in *functionName The name of the function module, whose description is to be removed from the cache.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcRemoveFunctionDesc(SAP_UC const * repositoryID, SAP_UC const * functionName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the structure description that is valid for the system to which rfcHandle points to.
	 * \ingroup repository
	 * 
     * If the structure description is already in the repository cache for that system ID, it will be 
	 * returned immediately (from the cache), otherwise it will be looked up in the system's DDIC using
	 * the rfcHandle. The result from the DDIC lookup will then be placed into the cache for later use.
	 *
	 * The RFC Runtime maintains a cache for every R/3 System ID, as the meta data could be different
	 * from R/3 release to R/3 release.
	 * \note Normally it should not be necessary to lookup separate structure descriptions. They are
	 * already looked up as part of the function module, in which they are used.
	 * 
	 * \in rfcHandle Open client connection to the R/3 System, for which you need the structure description.
	 * \in *typeName Name of a DDIC structure or table.
	 * \out *errorInfo More error details in case something goes wrong.
	 * \return The metadata description of the given structure/table.
	 */
	DECL_EXP RFC_TYPE_DESC_HANDLE SAP_API RfcGetTypeDesc(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const * typeName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Looks for a cached structure/table description. 
	 * \ingroup repository
	 *
	 * Similar to RfcGetTypeDesc(), but it only looks into the cache. Again it should almost never
	 * be necessary to get a metadata description of a single structure.
	 * 
	 * \in *repositoryID System ID of R/3 System, for which this type description has been cached,
	 * or NULL in case you want to look for it in the default repository.
	 * \in *typeName Name of the DDIC structure/table.
	 * \out *errorInfo Requested type name not in cache?
	 * \return The requested type description.
	 */
	DECL_EXP RFC_TYPE_DESC_HANDLE SAP_API RfcGetCachedTypeDesc(SAP_UC const * repositoryID, SAP_UC const * typeName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Adds a type description to the cache.
	 * \ingroup repository
	 * 
	 * 
	 * \in *repositoryID System ID of R/3 System, to whose cache you want to add the type description,
	 * or NULL for the default repository.
	 * \in typeHandle The type description.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcAddTypeDesc(SAP_UC const * repositoryID, RFC_TYPE_DESC_HANDLE typeHandle, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Removes a type description from the cache.
	 * \ingroup repository
	 * 
	 * 
	 * \in *repositoryID System ID of R/3 System, from whose cache you want to remove the type description,
	 * or NULL for the default repository.
	 * \in *typeName The name of the type, whose description is to be removed from the cache.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcRemoveTypeDesc(SAP_UC const * repositoryID, SAP_UC const * typeName, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Returns the class description that is valid for the system to which rfcHandle points to.
	 * \ingroup repository
	 * 
     * If the class description is already in the repository cache for that system ID, it will be 
	 * returned immediately (from the cache), otherwise it will be looked up in the system's DDIC using
	 * the rfcHandle. The result from the DDIC lookup will then be placed into the cache for later use.
	 *
	 * The RFC Runtime maintains a cache for every R/3 System ID, as the meta data could be different
	 * from R/3 release to R/3 release.
     * This is the main API that should be used.
	 * 
	 * \in rfcHandle Open client connection to the R/3 System, for which you need the class description.
	 * \in *className Name of the class to look up.
	 * \out *errorInfo More error details in case something goes wrong.
	 * \return The metadata description of the given function module.
	 */
	DECL_EXP RFC_CLASS_DESC_HANDLE SAP_API RfcGetClassDesc(RFC_CONNECTION_HANDLE rfcHandle, SAP_UC const * className, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Looks for a cached class description. 
	 * \ingroup repository
	 * 
     * This API should be used with care and is only for special scenarios, for example:
	 * 1. You know for sure, that a class description has already been cached via RfcGetClassDesc(),
	 *    and don't want to open an extra rfcHandle that will never be used.
	 *    In this case simply use the SAP System ID as the repositoryID.
	 * 2. You have created a hard-coded repository via RfcAddClassDesc(), which contains classes
	 *    that do not exist in the backend's DDIC.
     * 
     * If repositoryID is NULL, the "default repository" is used.
	 * 
	 * \in *repositoryID System ID of R/3 System, for which this class description has been cached,
	 * or NULL in case you want to look for it in the default repository.
	 * \in *className Name of the class.
	 * \out *errorInfo Requested class name not in cache?
	 * \return The requested class description.
	 */
	DECL_EXP RFC_CLASS_DESC_HANDLE SAP_API RfcGetCachedClassDesc(SAP_UC const * repositoryID, SAP_UC const * className, RFC_ERROR_INFO* errorInfo);

     /**
     * \brief  Returns the metadata description of the given ABAP object handle.
     * \ingroup container
     * 
     * 
     * \in objectHandle An ABAP object.
     * \out *errorInfo Can't possibly go wrong...
     * \return The class description of the given ABAP object.
     */
    DECL_EXP RFC_CLASS_DESC_HANDLE SAP_API RfcDescribeAbapObject(RFC_ABAP_OBJECT_HANDLE objectHandle, RFC_ERROR_INFO* errorInfo);

    /**
	 * \brief  Adds a class description to the cache for the specified R/3 System.
	 * \ingroup repository
     * 
     * This API should be used with care and is only for special scenarios, e.g. if you want to
	 * write an RFC server that offers/uses classes, which do not exist in the R/3 system's DDIC.
     * If repositoryID is NULL, the description is added to the "default repository".
	 * 
	 * 
	 * \in *repositoryID System ID of R/3 System, to whose cache you want to add the class description,
	 * or NULL for the default repository.
	 * \in classDesc The class description.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcAddClassDesc(SAP_UC const * repositoryID, RFC_CLASS_DESC_HANDLE classDesc, RFC_ERROR_INFO* errorInfo);

    /**
	 * \brief  Removes a class description from the cache for the specified R/3 System.
	 * \ingroup repository
     * 
     * If repositoryID is NULL, the description is removed from the "default repository".
	 * 
	 * 
	 * \in *repositoryID System ID of R/3 System, from whose cache you want to remove the class description,
	 * or NULL for the default repository.
	 * \in *className The name of the ABAP class, whose description you want to remove.
	 * \out *errorInfo Not much that can go wrong here.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcRemoveClassDesc(SAP_UC const * repositoryID, SAP_UC const * className, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Removes all metadata from the repository cache of the specified R/3 System.
	* \ingroup repository
	*
	* If repositoryID is NULL, the "default repository" is cleared.
	*
	*
	* \in *repositoryID System ID of R/3 System, whose cache you want to clear,
	* or NULL for the default repository.
	* \out *errorInfo Not much that can go wrong here.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcClearRepository(SAP_UC const * repositoryID, RFC_ERROR_INFO* errorInfo);

    /**
    * \brief  Stores the currently cached objects of a repository into a JSON formatted text file.
    * \ingroup repository
    *
    * This function will create a JSON formatted text file that contains all currently cached function module descriptions with their parameters,
    * so it can be reloaded at another time (see RfcLoadRepository()) without opening connections to the backend and fetching metadata from the DDIC.
    * This JSON file can also be used by the SAP .NET Connector and SAP Java Connector.
    *
    * \in *repositoryID System ID of R/3 System, whose cache you want to save, or NULL for the default cache.
    * \in *targetStream FILE pointer opened by the user.
    * \out *errorInfo More error details in case something goes wrong.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcSaveRepository(SAP_UC const * repositoryID, FILE* const targetStream, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Retrieves metadata from a JSON formatted text file and creates the according repository to use for function calls.
    * \ingroup repository
    *
    * This function will create a repository with the given ID - or a default repository, if the ID is NULL - and populate it with
	* the function descriptions and parameter descriptions contained in the JSON formatted text file (see RfcSaveRepository()).
    * That way the RFC program does not need to fetch the metadata from the backend DDIC, which is useful, if you want to
	* improve the startup performance of your program or if your program is an RFC server that does not have login parameters
	* for the backend.
    * It is also possible to use JSON files created by SAP .NET Connector and SAP Java Connector.
    *
	* \note Special care needs to be taken to guarantee that the loaded metadata indeed matches the function and structure
	* descriptions defined in the backend system(s) against which it is to be used. Otherwise the risk of data corruption is very high.
	* \note If a repository with the given ID already exists, %RfcLoadRepository() will delete it and replace it with the contents
	* of the JSON file.
	* 
    *
    * \in *repositoryID System ID of R/3 System, for which you want to use the metadata contained in the JSON file, or NULL
	* for the default repository.
    * \in *targetStream FILE pointer opened by the user.
    * \out *errorInfo More error details in case something goes wrong.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcLoadRepository(SAP_UC const * repositoryID, FILE* const targetStream, RFC_ERROR_INFO* errorInfo);

    /* 2. Metadata API */
    /* 2.1. Metadata API for structure descriptions */

    /**
     * \brief  Creates an empty type description with the given name.
     * \ingroup structure
     *
     * API for creating hard-coded metadata descriptions, e.g. for function modules that
     * don't exist in the R/3 backend.
     * Add field descriptions to the type description using RfcAddTypeField() and at the end
	 * set the total byte length of the structure using RfcSetTypeLength().
	 * \warning It is not easy to get the total length right, as you also need to take
	 * alignment bytes into account...
	 *
     * Finished type definitions can then be used for creating data containers (RfcCreateStructure()
	 * or RfcCreateTable()) and for adding field/table descriptions to a function module description
	 * (in RFC_PARAMETER_DESCs in RfcAddParameter()).
	 *
     * After the handle was used for creating a container, any modifications are forbidden.
     * 
     * \in *name An (arbitrary) name for the type.
     * \out *errorInfo Not enough memory?
     * \return The new type description.
     */
    DECL_EXP RFC_TYPE_DESC_HANDLE SAP_API RfcCreateTypeDesc(SAP_UC const* name, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Adds a new field to the type description.
     * \ingroup structure
	 *
     * \note After a type description has been used (e.g. via RfcCreateStructure(), RfcCreateTable() or
	 * RfcAddTypeDesc()), it can no longer be modified!
     * 
     * \in typeHandle 
     * \in *fieldDescr 
     * \out *errorInfo 
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcAddTypeField(RFC_TYPE_DESC_HANDLE typeHandle, const RFC_FIELD_DESC* fieldDescr, RFC_ERROR_INFO* errorInfo);

	/**
     * \brief  Sets the total byte length of the type description.
     * \ingroup structure
     * 
	 * Before a type description can be used, this function needs to be called.
	 * The RFC library does not automatically calculate the correct length based on
	 * the fields that have been added, because this task is non-trivial and possibly
	 * platform dependend. (Especially if the structure contains sub-structures.)\n
	 * For integer and floating point types the correct alignments need to be taken into
	 * account (start address divisible by 4 or 8), fixed sub-structures are inlined,
	 * complex structures are referenced by an 8-byte pointer, etc. In general you will need
	 * to do a bit of trial and error, before you get it right.\n
	 * If you really need more details/tips for the process of hardcoding metadata, see
	 * <A HREF="https://wiki.scn.sap.com/wiki/x/FD67Gg">this article</A>.
	 * 
     * 
     * \in typeHandle The type description.
     * \in nucByteLength Total byte length of the structure in a non-Unicode system (1 byte per CHAR).
     * \in ucByteLength Total byte length of the structure in a Unicode system (2 bytes per CHAR).
     * \out *errorInfo The function returns an error, if the given byte lengths are smaller than
	 * the sum of all field lengths, or if the nucByteLength is smaller than the ucByteLength.
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcSetTypeLength(RFC_TYPE_DESC_HANDLE typeHandle, unsigned nucByteLength, unsigned ucByteLength, RFC_ERROR_INFO* errorInfo);

	/**
     * \brief  Returns the name of the type.
     * \ingroup structure
     * 
     * 
     * \in typeHandle The type description.
     * \out bufferForName Will receive the null-terminated DDIC name of the structure definition.
     * \out *errorInfo Should always return successfully...
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcGetTypeName(RFC_TYPE_DESC_HANDLE typeHandle, RFC_ABAP_NAME bufferForName, RFC_ERROR_INFO* errorInfo);

	/**
     * \brief  Returns the number of fields in a structure definition.
     * \ingroup structure
     * 
     * 
     * \in typeHandle The type description.
     * \out *count The number of (direct) fields of this structure.
     * \out *errorInfo Should always return successfully...
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcGetFieldCount(RFC_TYPE_DESC_HANDLE typeHandle, unsigned* count, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Reads the field description of the structure's ith field.
     * \ingroup structure
     *
	 * Useful mostly when looping over the fields of a structure.
     * 
     * \in typeHandle The type description.
     * \in index The index of the field you are interested in.
     * \out *fieldDescr Will be filled with field's description.
     * \out *errorInfo Index out of bounds?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetFieldDescByIndex(RFC_TYPE_DESC_HANDLE typeHandle, unsigned index, RFC_FIELD_DESC* fieldDescr, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Reads the field description of a field given by name.
     * \ingroup structure
     * 
     * 
     * \in typeHandle The type description.
     * \in *name The name of the field of interest.
     * \out *fieldDescr Will be filled with field's description.
     * \out *errorInfo No such field?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetFieldDescByName(RFC_TYPE_DESC_HANDLE typeHandle, SAP_UC const* name, RFC_FIELD_DESC* fieldDescr, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the total byte length of a structure definition.
     * \ingroup structure
     * 
     * 
     * \in typeHandle The type description.
     * \out nucByteLength Total byte length in a non-Unicode system.
     * \out ucByteLength Total byte length in a Unicode system.
     * \out *errorInfo Should always return successfully.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetTypeLength(RFC_TYPE_DESC_HANDLE typeHandle, unsigned* nucByteLength, unsigned* ucByteLength, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Deletes the type description and releases the allocated resources.
	 * \ingroup structure
     * 
     * Only descriptions, which are not stored in a repository cache and not used by the application, can be deleted.
     * Deleting a cached description will cause an error, and deleting a description that is still in use, will lead
     * to a crash.
	 * 
	 * 
	 * \inout typeHandle The type description to be deleted.
	 * \out *errorInfo 
	 * \return 
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyTypeDesc(RFC_TYPE_DESC_HANDLE typeHandle, RFC_ERROR_INFO *errorInfo);



    /* 2.2. Metadata API for function modules */

    /**
     * \brief  Creates an empty function description with the given name.
     * \ingroup function
	 *
     * Add parameter descriptions and exception descriptions to the new RFC_FUNCTION_DESC_HANDLE
	 * via RfcAddParameter() and RfcAddException().\n
     * 
     * After the handle was used for creating a container, any modifications are forbidden.
     * 
     * \in *name The name of the function module.
     * \out *errorInfo Probably not enough memory left?!
     * \return An empty function description that can be used for constructing hard-coded metadata.
     */
    DECL_EXP RFC_FUNCTION_DESC_HANDLE SAP_API RfcCreateFunctionDesc(SAP_UC const* name, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns a function module's DDIC name.
     * \ingroup function
     * 
     * 
     * \in funcDesc The function module description.
     * \out bufferForName Will receive the function module's DDIC name.
     * \out *errorInfo Should always return successfully.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetFunctionName(RFC_FUNCTION_DESC_HANDLE funcDesc, RFC_ABAP_NAME bufferForName, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Adds a new parameter (IMPORTING, EXPORTING, CHANGING, TABLES) to the function description.
     * \ingroup function
     * 
	 * \note After the function description has been used via RfcCreateFunction() or RfcAddFunctionDesc(),
	 * it can no longer be modified!
     * 
     * \in funcDesc The function module description.
     * \in *paramDescr Metadata description of the new parameter.
     * \out *errorInfo More details in case something goes wrong.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcAddParameter(RFC_FUNCTION_DESC_HANDLE funcDesc, const RFC_PARAMETER_DESC* paramDescr, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the number of parameters in the function module definition.
     * \ingroup function
     * 
     * 
     * \in funcDesc The function module's metadata description.
     * \out *count The number of parameters (IMPORTING, EXPORTING, CHANGING, TABLES).
     * \out *errorInfo Nothing can go wrong here.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetParameterCount(RFC_FUNCTION_DESC_HANDLE funcDesc, unsigned* count, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Reads the metadata description of the function module's ith parameter.
     * \ingroup function
	 *
     * \note Mostly be useful when looping over all parameters of a function module.
     * 
     * \in funcDesc The function module's metadata description.
     * \in index The index of the parameter to describe.
     * \out *paramDesc Metadata description of the specified parameter.
     * \out *errorInfo Index out of bounds?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetParameterDescByIndex(RFC_FUNCTION_DESC_HANDLE funcDesc, unsigned index, RFC_PARAMETER_DESC* paramDesc, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Reads the metadata description of a function module parameter given by name.
     * \ingroup function
     * 
     * 
     * \in funcDesc The function module's metadata description.
     * \in *name The name of the parameter to describe.
     * \out *paramDesc Metadata description of the specified parameter.
     * \out *errorInfo No such parameter?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetParameterDescByName(RFC_FUNCTION_DESC_HANDLE funcDesc, SAP_UC const* name, RFC_PARAMETER_DESC* paramDesc, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Adds a new ABAP Exception to the function description.
     * \ingroup function
     * 
	 * \note After the function description has been used via RfcCreateFunction() or RfcAddFunctionDesc(),
	 * it can no longer be modified!
     * 
     * 
     * \in funcDesc The function module's metadata description.
     * \in *excDesc The description of the exception to add.
     * \out *errorInfo Not much that can go wrong here.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcAddException(RFC_FUNCTION_DESC_HANDLE funcDesc, const RFC_EXCEPTION_DESC* excDesc, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the number of ABAP Exceptions of the function module.
     * \ingroup function
     * 
     * 
     * \in funcDesc The function module's metadata description.
     * \out *count The number of the function module's ABAP Exceptions.
     * \out *errorInfo Not much that can go wrong here.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetExceptionCount(RFC_FUNCTION_DESC_HANDLE funcDesc, unsigned* count, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Reads the metadata description of the function module's ith ABAP Exception.
     * \ingroup function
     * 
     * 
     * \in funcDesc The function module's metadata description.
     * \in index The index of the exception to describe.
     * \out *excDesc The ABAP Exception's metadata description.
     * \out *errorInfo Index out of bounds?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetExceptionDescByIndex(RFC_FUNCTION_DESC_HANDLE funcDesc, unsigned index, RFC_EXCEPTION_DESC* excDesc, RFC_ERROR_INFO* errorInfo);

	/**
     * \brief  Reads the metadata description of a function module's ABAP Exception given by name.
     * \ingroup function
     * 
     * 
     * \in funcDesc The function module's metadata description.
     * \in *name The name of the exception to describe.
     * \out *excDesc The ABAP Exception's metadata description.
     * \out *errorInfo No such ABAP Exception?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetExceptionDescByName(RFC_FUNCTION_DESC_HANDLE funcDesc, SAP_UC const* name, RFC_EXCEPTION_DESC* excDesc, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Enables this function module for the basXML serialization format.
	 * \ingroup function
	 *
	 * R/3 Systems from kernel release 7.10 on support a new serialization format: basXML (binary ABAP serialization).
	 * Calling %RfcEnableBASXML() allows the RFC library to transport this function module's data via the
	 * basXML format, if the target backend supports it and the connection parameter NO_BASXML is either not set or set to "0".
	 * 
	 * \in funcDesc The function module's metadata description.
	 * \out *errorInfo Should always return successfully.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcEnableBASXML(RFC_FUNCTION_DESC_HANDLE funcDesc, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns whether this function module has been enabled for basXML.
     * \ingroup function
	 *
     * See RfcEnableBASXML()
     * 
     * \in funcDesc The function module's metadata description.
     * \out *isEnabled 0 = false, 1 = true.
     * \out *errorInfo Should always return successfully.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcIsBASXMLSupported(RFC_FUNCTION_DESC_HANDLE funcDesc, int* isEnabled, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Deletes the function description and releases the allocated resources.
	 * \ingroup function
     * 
     * Only descriptions, which are not stored in a repository cache and not used by the application, can be deleted.
     * Deleting a cached description will cause an error, and deleting a description that is still in use, will lead
     * to a crash.
	 * 
	 * 
	 * \in funcDesc A function description.
	 * \out *errorInfo Should always return successfully...
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyFunctionDesc(RFC_FUNCTION_DESC_HANDLE funcDesc, RFC_ERROR_INFO *errorInfo);

	/**
	 * \brief  Enables this function handle for ABAP class exception support.
	 * \ingroup function
	 *
	 * R/3 Systems from kernel release 7.11 on support ABAP class exceptions.
	 * Calling %RfcEnableAbapClassException() allows an RFC client to inform the ABAP backend that it can handle ABAP class exceptions
	 * for the current function call using this function handle. If the ABAP backend supports class-based exceptions as well,
	 * it can now safely throw such an exception.\n
	 * Needs to be called before the corresponding RfcInvoke().
	 *
	 * \in funcHandle Function module data container.
	 * \in rfcHandleRepository RFC connection handle to the repository system from where the missing metadata can be 
	 * dynamically retrieved during de-serializing the received ABAP class exceptions. This handle can be NULL but should not be
	 * the same that is used for the RFC call itself. 
	 * \out *errorInfo Should always return successfully.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcEnableAbapClassException(RFC_FUNCTION_HANDLE funcHandle, RFC_CONNECTION_HANDLE rfcHandleRepository, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Checks whether this function handle has been enabled for ABAP class exception support.
	 * \ingroup function
	 *
	 * R/3 Systems from kernel release 7.11 on support ABAP class exception.
	 * Typically, an RFC server can use this function in order to find out, whether the function module currently being processed has
	 * ABAP class exceptions enabled in the ABAP backend. Only if this is the case, can the RFC Server safely throw an ABAP class exception.
	 *
	 * \in funcHandle Function module data container.
	 * \out *isEnabled Flag indicating whether the function handle has been enabled for ABAP class based exception support.
	 * \out *errorInfo Should always return successfully.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcIsAbapClassExceptionEnabled(RFC_FUNCTION_HANDLE funcHandle, int* isEnabled,  RFC_ERROR_INFO* errorInfo);


    /* 2.3. Metadata API for ABAP classes */

    /**
     * \brief  Creates an empty class description with the given name.
     * \ingroup class
	 *
     * Add attribute descriptions to the new RFC_CLASS_DESC_HANDLE via RfcAddAttribute().\n
	 *
     * After the handle was used for creating a container, any modifications are forbidden.
     * 
     * \in *name The name of the ABAP class.
     * \out *errorInfo Probably not enough memory left?!
     * \return An empty function description that can be used for constructing hard-coded metadata.
     */
    DECL_EXP RFC_CLASS_DESC_HANDLE SAP_API RfcCreateClassDesc(SAP_UC const* name, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the class's DDIC name.
     * \ingroup class
     * 
     * 
     * \in classDesc The class description.
     * \out bufferForName Will receive the function module's DDIC name (zero terminated).
     * \out *errorInfo Should always return successfully.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetClassName(RFC_CLASS_DESC_HANDLE classDesc, RFC_ABAP_NAME bufferForName, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Adds a new attribute (field, structure, table, method) to the class description.
     * \ingroup class
     * 
	 * \note After the function description has been used via RfcCreateAbapObject() or RfcAddClassDesc(),
	 * it can no longer be modified!
     * 
     * \in classDesc The class description.
     * \in *attrDesc Metadata description of the new class attribute.
     * \out *errorInfo More details in case something goes wrong.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcAddClassAttribute(RFC_CLASS_DESC_HANDLE classDesc, const RFC_CLASS_ATTRIBUTE_DESC* attrDesc, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the number of parameters in the function module definition.
     * \ingroup class
     * 
     * 
     * \in classDesc The class description.
     * \out *count The number of attributes.
     * \out *errorInfo Nothing can go wrong here.
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetClassAttributesCount(RFC_CLASS_DESC_HANDLE classDesc, unsigned* count, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Reads the metadata description of the class attribute.
     * \ingroup class
	 *
     * \note Is useful mostly when looping over all attributes of a class.
     * 
     * \in classDesc The class metadata description.
     * \in index The index of the attributes to describe.
     * \out *attrDesc Metadata description of the class attribute.
     * \out *errorInfo Index out of bounds?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetClassAttributeDescByIndex(RFC_CLASS_DESC_HANDLE classDesc, unsigned index, RFC_CLASS_ATTRIBUTE_DESC* attrDesc, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Reads the metadata description of a class attribute given by name.
     * \ingroup class
     * 
     * 
     * \in classDesc The class metadata description.
     * \in *name The name of the parameter to describe.
     * \out *attrDesc Metadata description of the class attribute.
     * \out *errorInfo No such parameter?
     * \return RFC_RC
     */
    DECL_EXP RFC_RC SAP_API RfcGetClassAttributeDescByName(RFC_CLASS_DESC_HANDLE classDesc, SAP_UC const* name, RFC_CLASS_ATTRIBUTE_DESC* attrDesc, RFC_ERROR_INFO* errorInfo);


    /**
     * \brief  Returns the parent classes of the given class.
     * \ingroup class
     * 
     * \in classDesc The class metadata description.
     * \in name The parent class name.
     * \in index Index of parent class.
     * \out *errorInfo Current class does not inherit from parent class?
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcGetParentClassByIndex(RFC_CLASS_DESC_HANDLE classDesc, RFC_CLASS_NAME name, unsigned index, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the number of parent classes of the given class.
     * \ingroup class
     * 
     * 
     * \in classDesc The class metadata description.
     * \out *parentClassesCount Number of parent classes in the list.
     * \out *errorInfo Should always be successful.
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcGetParentClassesCount(RFC_CLASS_DESC_HANDLE classDesc, unsigned* parentClassesCount, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Sets the parent classes of the given class.
     * \ingroup class
     * 
     * 
     * \in classDesc The class metadata description.
     * \in name Parent class name to be added.
     * \out *errorInfo No such parameter?
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcAddParentClass(RFC_CLASS_DESC_HANDLE classDesc, const RFC_CLASS_NAME name, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the implemented interfaces of the given class.
     * \ingroup class
     * 
     * 
     * \in classDesc The class metadata description.
     * \in index Index of the implemented interface.
     * \out name Buffer for the implemented interface's name.
     * \out *errorInfo Index out of bounds?
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcGetImplementedInterfaceByIndex(RFC_CLASS_DESC_HANDLE classDesc, unsigned index, RFC_CLASS_NAME name, RFC_ERROR_INFO* errorInfo);

    /**
     * \brief  Returns the number of parent interfaces of the given class.
     * \ingroup class
     * 
     * 
     * \in classDesc The class metadata description.
     * \out *implementedInterfacesCount Number of implemented interfaces.
     * \out *errorInfo Should always be successful.
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcGetImplementedInterfacesCount(RFC_CLASS_DESC_HANDLE classDesc, unsigned* implementedInterfacesCount, RFC_ERROR_INFO* errorInfo);
	
    /**
     * \brief  Adds an interface to the list of implemented interfaces of the given class.
     * \ingroup class
     * 
     * 
     * \in classDesc The class metadata description.
     * \in name Name of implemented interface to be added.
     * \out *errorInfo Not much can go wrong here except out of memory.
     * \return RFC_RC
     */
	DECL_EXP RFC_RC SAP_API RfcAddImplementedInterface(RFC_CLASS_DESC_HANDLE classDesc, const RFC_CLASS_NAME name, RFC_ERROR_INFO* errorInfo);

	/**
	 * \brief  Deletes the class description and releases the allocated resources.
	 * \ingroup class
     * 
     * Only descriptions, which are not stored in a repository cache and not used by the application, can be deleted.
     * Deleting a cached description will cause an error, and deleting a description that is still in use, will lead
     * to a crash.
	 * 
	 * 
	 * \in classHandle The class description to be deleted.
	 * \out *errorInfo More details in case the description can not be destroyed.
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyClassDesc(RFC_CLASS_DESC_HANDLE classHandle, RFC_ERROR_INFO *errorInfo);


	typedef void* RFC_METADATA_QUERY_RESULT_HANDLE; ///< Handle to a metadata query result.

	/** \struct _RFC_METADATA_QUERY_RESULT_ENTRY
	 * \ingroup repository
	 *
	 * Structure containing the error that occurred during the metadata query. 
	 */
	typedef struct _RFC_METADATA_QUERY_RESULT_ENTRY
	{
		RFC_ABAP_NAME name;
		SAP_UC errorMessage[512];
	} RFC_METADATA_QUERY_RESULT_ENTRY;
	
	/** \enum _RFC_METADATA_OBJ_TYPE
	 * \ingroup repository
	 *
	 * An RFC_METADATA_OBJ_TYPE indicates whether in a call to RfcGetMetadataQueryFailedEntry() or RfcGetMetadataQuerySucceededEntry()
	 * you are interested in the error/success message for a function module (_FUNCTION), structure/table (_TYPE) or ABAP Class (_CLASS).
	 * It needs to be passed to the above two functions.
	 */
	typedef enum _RFC_METADATA_OBJ_TYPE {RFC_METADATA_FUNCTION, RFC_METADATA_TYPE, RFC_METADATA_CLASS} RFC_METADATA_OBJ_TYPE;
	
	/**
	 * \brief  Creates the metadata query result
	 * \ingroup repository
	 * 
	 * Metadata query results contain the names of functions, types and classes queried successfully, and the corresponding
	 * errors, if the query failed.
	 * 
	 * \out *errorInfo More details in error case
	 * \return Handle to a metadata query result
	 */
	DECL_EXP RFC_METADATA_QUERY_RESULT_HANDLE SAP_API RfcCreateMetadataQueryResult(RFC_ERROR_INFO *errorInfo);

	/**
	 * \brief  Destroys the metadata query result
	 * \ingroup repository
	 * 
	 * Releases all resources allocated by the metadata query result.
	 * 
	 * \in handle Handle to a metadata query result
	 * \out *errorInfo More details in error case
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDestroyMetadataQueryResult(RFC_METADATA_QUERY_RESULT_HANDLE handle, RFC_ERROR_INFO *errorInfo);

	/**
	 * \brief  Describes the metadata query result
	 * \ingroup repository
	 * 
	 * Returns the number of succeeded and failed entries in the metadata query result. The entries' content can be read with 
	 * RfcGetMetadataQueryFailedEntry() and RfcGetMetadataQuerySucceededEntry().
	 * 
	 * \in handle Handle to a metadata query result
	 * \in type Type of the metadata objects you are interested in
	 * \out *successful Number of metadata objects queried successfully
	 * \out *failed Number of metadata objects that could not be queried
	 * \out *errorInfo More details in error case
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcDescribeMetadataQueryResult(RFC_METADATA_QUERY_RESULT_HANDLE handle, 
		RFC_METADATA_OBJ_TYPE type, unsigned* successful, unsigned *failed, RFC_ERROR_INFO *errorInfo);

	/**
	 * \brief  Returns the error entry from the metadata query result
	 * \ingroup repository
	 * 
	 * Returns the object name and the error text, if an error occurred during the query.
	 * 
	 * \in handle Handle to a metadata query result
	 * \in type Type of the requested object
	 * \in index Index of the requested object. Must be between 0 and "failed - 1", where "failed" is the value
	 * returned from RfcDescribeMetadataQueryResult() for the given RFC_METADATA_OBJ_TYPE.
	 * \inout *entry Pointer to the allocated structure to store the name of the metadata object and the error text
	 * \out *errorInfo More details in error case
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetMetadataQueryFailedEntry(RFC_METADATA_QUERY_RESULT_HANDLE handle, 
		RFC_METADATA_OBJ_TYPE type, unsigned index, RFC_METADATA_QUERY_RESULT_ENTRY* entry, RFC_ERROR_INFO *errorInfo);

	/**
	 * \brief  Returns a succeeded entry from the metadata query result
	 * \ingroup repository
	 * 
	 * Returns the object name of a successfully queried object.
	 * 
	 * \in handle Handle to a metadata query result
	 * \in type Type of the requested object
	 * \in index Index of the requested object. Must be between 0 and "successful - 1", where "successful" is the value
	 * returned from RfcDescribeMetadataQueryResult() for the given RFC_METADATA_OBJ_TYPE.
	 * \inout *succeedObj Pointer to the allocated buffer to store the name of the metadata object
	 * \out *errorInfo More details in error case
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcGetMetadataQuerySucceededEntry(RFC_METADATA_QUERY_RESULT_HANDLE handle, 
		RFC_METADATA_OBJ_TYPE type, unsigned index, RFC_ABAP_NAME succeedObj, RFC_ERROR_INFO *errorInfo);


	/**
	 * \brief  Queries the meta data for function, type and class lists. 
	 * \ingroup repository
	 * 
	 * Queries the meta data for function, type and class lists. All meta data is fetched using one roundtrip, 
	 * the result is cached in the repository cache.
	 * 
	 * \note You can use this feature only, if your backend system supports it. SAP Note 1456826 describes the
	 * required minimum support package level that the backend system must have. If the backend system supports
	 * it, open the RFC_CONNECTION_HANDLE with the additional logon parameter USE_REPOSITORY_ROUNDTRIP_OPTIMIZATION=1,
	 * before you pass it to %RfcMetadataBatchQuery().
	 * 
	 * \in rfcHandle Open client connection to the R/3 System, for which you need the function module, type or class descriptions.
	 * \in *functionNames Names of the function modules to look up
	 * \in functionCount Length of the function name list
	 * \in *typeNames Names of the types (structures and tables) to look up
	 * \in typeCount Length of the type name list
	 * \in *classNames Names of the classes to look up
	 * \in classCount Length of the class name list
	 * \in handle Query result, may be null
	 * \out *errorInfo More error details in case something goes wrong
	 * \return RFC_RC
	 */
	DECL_EXP RFC_RC SAP_API RfcMetadataBatchQuery(RFC_CONNECTION_HANDLE rfcHandle, 
		const SAP_UC** functionNames, unsigned functionCount, const SAP_UC** typeNames, unsigned typeCount, 
		const SAP_UC** classNames, unsigned classCount, RFC_METADATA_QUERY_RESULT_HANDLE handle, RFC_ERROR_INFO *errorInfo);



    /* ***********************************************************************/
    /*                                                                       */
    /*  Throughput API                                              */
    /*                                                                       */
    /* ***********************************************************************/


    /**
    * \brief  Creates a throughput object that can be used to measure performance relevant data of connections and servers.
    * \ingroup throughput
    * 
    * The created throughput object can be attached to a connection (via RfcSetThroughputOnConnection()) or an automated server (via RfcSetThroughputOnServer())
    * and will collect performance relevant data from the outgoing or incoming calls. The throughput object will monitor all relevant data until it is removed from the
    * connection or server or the object it is attached to is destroyed, i.e. the connection is closed. Note that only one throughput per connection (or server)
    * is possible. On the contrary one throughput can be attached to many connections (and/or servers).
    * There are serveral functions that handle the throughput and its lifetime like RfcRemoveThroughputFromConnection() or RfcResetThroughput().
    * Additionally there are RfcGetX functions to obtain the aggregated data from the throughput.
    * 
    * \out *errorInfo Error information in case there's not enough memory.
    * \return A handle to the throughput object.
    */
    DECL_EXP RFC_THROUGHPUT_HANDLE SAP_API RfcCreateThroughput(RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Releases all memory used by the throughput object.
    * \ingroup throughput
    * 
    * \warning Be careful: if you have attached the throughput to a connection (RFC_CONNECTION_HANDLE) or
    * server (RFC_SERVER_HANDLE) you have to remove the throughput from the connection or server before deleting it.
    * Alternatively you can close the connection or shutdown the server before destroying the throughput object.
    * 
    * \in throughput A handle to the throughput object.
    * \out *errorInfo Not much that can go wrong here.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcDestroyThroughput(RFC_THROUGHPUT_HANDLE throughput, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Attaches a throughput object to a connection to be monitored by the throughput object.
    * \ingroup throughput
    * 
    * Once attached to a connection, the throughput object will collect data of the function calls invoked via this connection.
    * If there is already another throughput obejct attached to the connection, the old one will be replaced by the given one.
	* The below chart shows a simplified view how the different time measurements apply for a client call.
	*
	* Client                                            Server (backend)                                       Client
	*      
	*	     API begin   serialization   writing       server time        reading   deserialization   API return
	*      ____________|_______________|_________   _|_____________|_    _________|_________________|____________
    * 
    * \in rfcHandle A handle to a currently open RFC connection (client or server connection).
    * \in throughput A handle to the throughput object.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcSetThroughputOnConnection(RFC_CONNECTION_HANDLE rfcHandle, RFC_THROUGHPUT_HANDLE throughput, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the currently attached throughput object from a connection, if any.
    * \ingroup throughput
    *
    * Returns null if none is attached.
    *  
    * \in rfcHandle A handle to a currently open RFC connection (client or server connection).
    * \out *errorInfo More details in error case.
    * \return A handle to a throughput object.
    */
    DECL_EXP RFC_THROUGHPUT_HANDLE SAP_API RfcGetThroughputFromConnection(RFC_CONNECTION_HANDLE rfcHandle, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Removes the throughput object from a connection. The connection will no longer be monitored.
    * \ingroup throughput
    * 
    * \in rfcHandle A handle to a currently open RFC connection (client or server connection).
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcRemoveThroughputFromConnection(RFC_CONNECTION_HANDLE rfcHandle, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Attaches a throughput object to an automated server.
    * \ingroup throughput
    * 
    * Once attached to a server the throughput object will collect data of the function calls received by this server.
    * As the automated server handles its connections by itself, it will also attach the throughput to all of its connections 
    * and to all connections that might be re-opened.
    * If there is already another throughput attached to the server, the old one will be replaced by the given one.
	* The below chart shows a simplified view how the different time measurements apply for a call received by the server.
	*
	* Client                                            automated Server                                                    Client
	*
	*	    call begin       (accepting)   reading   deserialization   C-application   serialization   writing       call end
	*      ____________|_   _____________|_________|_________________|_______________|_______________|_________   _|___________
	*
    * 
    * \in serverHandle A handle to the server object.
    * \in throughput A handle to the throughput object.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcSetThroughputOnServer(RFC_SERVER_HANDLE serverHandle, RFC_THROUGHPUT_HANDLE throughput, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the currently attached throughput object from a server, if any.
    * \ingroup throughput
    *  
    * Returns null if none is attached.
    *  
    * \in serverHandle A handle to the server object.
    * \out *errorInfo More details in error case.
    * \return A handle to a throughput object.
    */
    DECL_EXP RFC_THROUGHPUT_HANDLE SAP_API RfcGetThroughputFromServer(RFC_SERVER_HANDLE serverHandle, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Removes the throughput from an automated server. The server will no longer be monitored.
    * \ingroup throughput
    * 
    * \in serverHandle A handle to the server from which the throughput shall be detached.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcRemoveThroughputFromServer(RFC_SERVER_HANDLE serverHandle, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Resets the data so far collected and aggregated by the throughput object.
    * \ingroup throughput
    * 
    * \in throughput A handle to the throughput object.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcResetThroughput(RFC_THROUGHPUT_HANDLE throughput, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the cumulated number of calls the throughput object recorded since it was attached or since the last reset.
    * \ingroup throughput
    *
    * If a throughput object is attached to several connections or servers, this is the amount of calls that all these connections
	* and servers have processed up to now.
    * 
    * \in throughput A handle to the throughput object.
    * \out *numberOfCalls Number of all monitored calls.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetNumberOfCalls(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* numberOfCalls, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the cumulated time of call durations the throughput object recorded since it was attached or since the last reset.
    * \ingroup throughput
    *
    * If a throughput object is attached to several connections or servers, this is the total time of all processed calls.
    * This time includes serialization, deserialization, reading from network, writing to network and time consumed in the backend.
	* In case of a server it also includes time accepting a connection.
    * An approximation of the time for transmission and execution in the backend is defined by
    *
    *    totalTime - serializationTime - deserializationTime (- applicationTime) 
    * 
    * 
    * \in throughput A handle to the throughput object.
    * \out *totalTime Cumulated time of all function module calls processed by the corresponding connections or servers. The unit is milliseconds.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetTotalTime(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* totalTime, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the cumulated serializationtime the throughput object recorded since it was attached or since the last reset.
    * \ingroup throughput
    *
    * If a throughput object is attached to several connections or servers, this is the serialization time of all processed calls.
	* Serialization time is defined as the time needed for transforming C/C++ data types into a byte stream that can be sent
    * over the network. This includes time needed for codepage conversions, endianness conversions etc., but not the time consumed
	* by writing to the network.  
    *
    * \in throughput A handle to the throughput object.
    * \out *serializationTime Cumulated time all serialization processes took. The unit is milliseconds.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetSerializationTime(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* serializationTime, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the cumulated deserialization time the throughput object recorded since it was attached or since the last reset.
    * \ingroup throughput
    *
    * If a throughput object is attached to several connections or servers, this is the deserialization time of all processed calls.
	* Deserialization time is defined as the time needed for transforming a byte stream received from the network connection into
	* C/C++ data types that can be used by the application. This includes time needed for codepage conversions, endianness conversions etc.,
    * but not the time consumed by reading from the network.
    * 
    * \in throughput A handle to the throughput object.
    * \out *deserializationTime Cumulated time all deserialization processes took. The unit is milliseconds.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetDeserializationTime(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* deserializationTime, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the cumulated time of the C implementations of ABAP function modules that the throughput object recorded
	* since it was attached or since the last reset.
    * \ingroup throughput
    *
	* This value is collected only in the case of server connections. (In the client case, function modules are of course
	* implemented in ABAP, not in C, and their time is included in the backend time.)
    * If a throughput is attached to several connections or servers, this is the application time of all invoked calls.
    * 
    * \in throughput A handle to the throughput object.
    * \out *applicationTime Cumulated time all C impelementations of ABAP function modules took. The unit is milliseconds.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetApplicationTime(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* applicationTime, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Returns the cumulated execution time of the requests at the server, that the throughput object recorded
	* since it was attached or since the last reset.
	* \ingroup throughput
	*
	* If a throughput object is attached to several connections or servers, this is the server time of all processed calls.
	* This value is measured at the backend by the partner and transmitted in the RFC data payload.
	*
	* \in throughput A handle to the throughput object.
	* \out *serverTime Cumulated time spent at the server side for the requests. The unit is milliseconds.
	* \out *errorInfo More details in error case.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetServerTime(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* serverTime, RFC_ERROR_INFO* errorInfo);

	/**
    * \brief  Returns the cumulated time that is used to write to network during the requests, that the throughput object recorded
    * since it was attached or since the last reset.
    * \ingroup throughput
    *
    * If a throughput object is attached to several connections or servers, this is the time used to write to network of all processed calls.
    * The time measures calls to underlying libraries such an NI functions and operating socket functions. Those times might not correctly represent the time
	* that is needed to send the data, as there are asynchronous IO functions used or the OS is responsible for sending the data.
    *
    * \in throughput A handle to the throughput object.
    * \out *writingTime Cumulated time spent writing to the network. The unit is milliseconds.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
	DECL_EXP RFC_RC SAP_API RfcGetNetworkWritingTime(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* writingTime, RFC_ERROR_INFO* errorInfo);

	/**
	* \brief  Returns the cumulated time that is used to read from the network during the requests, that the throughput object recorded
	* since it was attached or since the last reset.
	* \ingroup throughput
	*
	* If a throughput object is attached to several connections or servers, this is the time used to read from the network of all processed calls.
	* The time measures calls to underlying libraries such an NI functions and operating socket functions. Those times might not correctly represent the time
	* that is needed to receive the data, as there are asynchronous IO functions used or the OS is responsible for receiving the data.
	*
	* \in throughput A handle to the throughput object.
	* \out *readingTime Cumulated time spent reading from the network. The unit is milliseconds.
	* \out *errorInfo More details in error case.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetNetworkReadingTime(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* readingTime, RFC_ERROR_INFO* errorInfo);
    /**
    * \brief  Returns the cumulated amount of sent bytes the throughput object recorded since it was attached or since the last reset.
    * \ingroup throughput
    *
    * If a throughput is attached to several connections or servers, this is the amount of bytes sent by all processed calls.
    * 
    * \in throughput A handle to the throughput object.
    * \out *sentBytes Cumulated amount of bytes sent over the network.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetSentBytes(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* sentBytes, RFC_ERROR_INFO* errorInfo);


    /**
    * \brief  Returns the cumulated amount of received bytes the throughput object recorded since it was attached or since the last reset.
    * \ingroup throughput
    *
    * If a throughput is attached to several connections or servers, this is the amount of bytes received by all processed calls.
    * 
    * \in throughput A handle to the throughput object.
    * \out *receivedBytes Cumulated amount of bytes received from the network.
    * \out *errorInfo More details in error case.
    * \return RFC_RC
    */
    DECL_EXP RFC_RC SAP_API RfcGetReceivedBytes(RFC_THROUGHPUT_HANDLE throughput, SAP_ULLONG* receivedBytes, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Set Timeout for Message Server Response 
	*
	* During Group Logon and during Group Registration (registration of an RFC server at multiple gateways),
	* the NW RFC library sends requests to the message server, asking for the currently "least busy" application
	* server (load balancing) or for a list of all application servers contained in a group.
	* This timeout specifies, how long the NW RFC library will wait for the corresponding responses from the
	* message server, before aborting with a timeout error.
	*
	* \in timeout Timeout in seconds
    * \out *errorInfo More details in error case.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcSetMessageServerResponseTimeout(unsigned timeout, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Sets the maximum number of concurrent CPIC conversations.
	*
	* The API can only be called if there are no current CPIC conversations active. A number smaller than the current maximum
	* will be ignored.
	* The default value is 200.
	* 
	* The number can also be increased by setting MAX_CPIC_CONVERSATIONS in the DEFAULT section of the sapnwrfc.ini file.
	*
	* \in maxCpicConversations Maximum of concurrent CPIC conversations
	* \out *errorInfo More details in error case.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcSetMaximumCpicConversations(unsigned maxCpicConversations, RFC_ERROR_INFO* errorInfo);

	/**
	* \brief  Gets the maximum number of parallel CPIC conversations.
	*
	* The default value is 200.
	*
	* \in *maxCpicConversations Current maximum of parallel CPIC conversations
	* \out *errorInfo More details in error case.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcGetMaximumCpicConversations(unsigned* maxCpicConversations, RFC_ERROR_INFO* errorInfo);


	/**
	* \brief  Sets the global logon timeout in seconds.
	*
	* Sets the timeout for how long the logon in the ABAP backend can take during RfcOpenConnection().
	* The valid range of values is [1,3600].
	* The default value is 60 seconds.
	*
	* The timeout can also be set via RFC_GLOBAL_LOGON_TIMEOUT in the DEFAULT section of the sapnwrfc.ini file.
	*
	* \in logonTimeout gloabl logon timeout in seconds.
	* \out *errorInfo More details in error case.
	* \return RFC_RC
	*/
	DECL_EXP RFC_RC SAP_API RfcSetGlobalLogonTimeout(unsigned logonTimeout, RFC_ERROR_INFO* errorInfo);

#ifdef __cplusplus
}
#endif /*cplusplus*/

#endif
