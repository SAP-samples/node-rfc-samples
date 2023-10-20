/* @(#) $Id: //bas/753_REL/src/base/api/sapdecf.h#3 $ SAP*/
/*-----------------------------------------------------------------------------
 *
 * (c) Copyright SAP AG, Walldorf
 *
 * sapdecf.h - Global header file for decimal floating-point arithmetic.
 *
 * Maintainer: Ulrich Brink, Klaus Kretzschmar
 * Topic:
 * Main File:
 *
 *----------------------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * This is a global header file for the definition of decimal
 * floating-point types and functions operating on them.
 *
 * "saptype.h" must be included before this file. 
 * If you make changes to this file: Do not assume
 * that anything else has been included before!
 *-------------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * This file offers conversion functions, arithmetic functions and
 * other utility functions.
 * This is an overview of the conversion functions:
 * 
 * Conversions to and from elementary data types:
 * 
 * DecFloat16ToDecFloat34
 * DecFloat34ToDecFloat16
 * 
 * DecFloat16ToString
 * DecFloat34ToString
 * 
 * StringToDecFloat16   (see also ab_ctodecf16)
 * StringToDecFloat34   (see also ab_ctodecf34)
 * 
 * DecFloat16ToSAP_INT
 * DecFloat16ToSAP_LLONG
 * DecFloat34ToSAP_INT
 * DecFloat34ToSAP_LLONG
 * 
 * SAP_INTToDecFloat16
 * SAP_LLONGToDecFloat16
 * SAP_INTToDecFloat34
 * SAP_LLONGToDecFloat34
 * 
 * DecFloat16ToSAP_DOUBLE
 * DecFloat34ToSAP_DOUBLE
 * SAP_DOUBLEToDecFloat16
 * SAP_DOUBLEToDecFloat34
 * 
 * DecFloat16ToBCD
 * DecFloat34ToBCD
 * BCDToDecFloat16
 * BCDToDecFloat34
 * 
 * 
 * Conversion into an SAP-proprietary format that can be sorted by memcpy:
 * 
 * DecFloat16ToDecFloat16Raw, DecFloat16ToDecFloat16RawDB
 * DecFloat34ToDecFloat34Raw, DecFloat34ToDecFloat34RawDB
 * NormDecFloat16ToDecFloat16Raw
 * NormDecFloat34ToDecFloat34Raw
 * 
 * Conversion from the SAP-proprietary sortable format into IEEE 754r Decfloats:
 * 
 * DecFloat16RawToDecFloat16, DecFloat16RawToDecFloat16DB
 * DecFloat34RawToDecFloat34, DecFloat34RawToDecFloat34DB
 * DecFloat16RawToNormDecFloat16
 * DecFloat34RawToNormDecFloat34
 *
 * Other functions
 *
 * DecFloat34StrDiv
 * 
 *-------------------------------------------------------------------*/


/*-HISTORY---------------------------------------------------------------------
  * 06.09.2005 kkr  first implementation
  * 24.07.2009 tmd  Implementation for unsigned int and long int added
 *----------------------------------------------------------------------------*/
/**
 @file sapdecf.h
 */


#ifndef SAPDECF_H
#define SAPDECF_H

/* @type SAP_API |
 * The token SAP_API contains plattform dependent keywords,
 * which are necessary to allow dynamic linking of these function
 * from various environments. On Windows for example SAP_API is
 * __extern __loadds __pascal __far.
 */

#if !defined(SAP_FAR)|| !defined(SAP_PASCAL)|| !defined(SAP_EXPORT)|| !defined(SAP_LOADDS) || !defined(SAP_STDCALL)
#   undef SAP_FAR
#   undef SAP_PASCAL
#   undef SAP_EXPORT
#   undef SAP_LOADDS
#   undef SAP_STDCALL
#   if defined(SAPonWINDOWS)
#       define SAP_FAR __far
#       define SAP_PASCAL __pascal
#       define SAP_EXPORT __export
#       define SAP_LOADDS __loadds
#       define SAP_STDCALL
#   elif defined(SAPonNT)
#       define SAP_FAR
#       define SAP_PASCAL
#       define SAP_EXPORT
#       define SAP_LOADDS
#       define SAP_STDCALL _stdcall
#   else
#       define SAP_FAR
#       define SAP_PASCAL
#       define SAP_EXPORT
#       define SAP_LOADDS
#       define SAP_STDCALL
#   endif
#endif

#if !defined(SAP_API)
#   if defined(OS2)
#       define _SYSTEM _System
#       define SAP_API _SYSTEM
#   else
#       define _SYSTEM
#       define SAP_API SAP_FAR SAP_LOADDS SAP_PASCAL SAP_STDCALL
#   endif
#endif /* SAP_API */

#ifndef DECL_EXP
#   if defined(SAPonLIN) && defined(__GNUC__) && defined(GCC_HIDDEN_VISIBILITY)
#     define DECL_EXP __attribute__((visibility("default")))
#   else
#     define DECL_EXP
#   endif
#endif


/**
 *brief  Error return codes.
 * (The return codes are set to the value decNumber has.)
 *
 * A note on error handling:
 * Often, DECF_INEXACT and DECF_UNDERFLOW can be handled in the same way as DECF_OK.
 * If DECF_NO_MEMORY occurs, the caller should abort.
*/
typedef enum {
  /** decNumber shared library could not be loaded; not relevant for SAP Kernel. */
  DECF_NOT_SUPPORTED = -2,

  /** decNumber shared library has wrong version; not relevant for SAP Kernel. */
  DECF_WRONG_VERSION = -1,

  /** no exception occurred */
  DECF_OK = 0,

  /** an inexact exception occurred (number was rounded) */
  DECF_INEXACT ,

  /** an underflow exception occurred (number was rounded such that the result is zero) */
  DECF_UNDERFLOW ,

  /** an overflow exception occurred (number was out of range, e.g., exponent too big) */
  DECF_OVERFLOW ,

  /** a conversion syntax exception occurred */
  DECF_CONV_SYNTAX ,

  /** a division by zero exception occurred */
  DECF_DIV_ZERO ,

  /** an invalid operation exception occurred */
  DECF_INVALID_OP ,

  /** a memory allocation error occurred */
  DECF_NO_MEMORY

} DECF_RETURN;



/**
 * \brief Rounding modes (IEEE 854 compliant).
 * Please compare with libDecimal.h before edit
*/
typedef enum {
	/** round towards +infinity */
	DECF_ROUND_CEILING   = 0,
	/** round away from 0 */
	DECF_ROUND_UP        = 1,
	/** 0.5 rounds up */
	DECF_ROUND_HALF_UP   = 2,
	/** 0.5 rounds to nearest even */
	DECF_ROUND_HALF_EVEN = 3,
	/** 0.5 rounds down */
	DECF_ROUND_HALF_DOWN = 4,
	/** round towards 0 (truncate) */
	DECF_ROUND_DOWN      = 5,
	/** round towards -infinity */
	DECF_ROUND_FLOOR     = 6,
	/** enum must be less than this */
	DECF_ROUND_MAX       = 7
} DecFRounding;

#ifdef SAPwithINT_LITTLEENDIAN
/** Minimum (in the sense of total ordering) IEEE 754r value = -Infinity */
static const DecFloat16 DecFloat16NegInf = {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8}};
/** Minimum (in the sense of total ordering) IEEE 754r value = -Infinity */
static const DecFloat34 DecFloat34NegInf = {{0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0xf8}};
/** 0E+0 */
static const DecFloat16 DecFloat16ZeroVal = 
  {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0x22}};
static const DecFloat34 DecFloat34ZeroVal = 
  {{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x22}};
#else
static const DecFloat16 DecFloat16NegInf = {{0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
static const DecFloat34 DecFloat34NegInf = {{0xf8, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00,0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
/** 0E+0 */
static const DecFloat16 DecFloat16ZeroVal = 
  {{0x22, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
static const DecFloat34 DecFloat34ZeroVal = 
  {{0x22, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
#endif /* SAPwithINT_LITTLEENDIAN */

/** \brief Number of significant digits in the mantissa */
static const int DecFloat16_NoOfDigits = 16;
static const int DecFloat34_NoOfDigits = 34;

BEGIN_externC
/* mutex lock and unlock */
void decf_mutex_lock(void);
void decf_mutex_unlock(void);

/* library initialization */

/**
 * \brief DecFloatDBmode: See DecFloat_InitializeDBmode()
 */
typedef enum {
  DECF_DBmode_initial     = 0,  /**< Initial */
  DECF_DBmode_roundForDEC = 1,  /**< Rounding necessary for DF16_DEC, DF34_DEC */
  DECF_DBmode_native      = 2   /**< The DB supports decimal floating-point types. */
} DecFloatDBmode;


/**
 * \brief  Initialize a flag that indicates whether the database supports
 * decimal floating-point types or just the SAP-proprietary types
 * DF16_DEC, DF34_DEC (fixed-point on the DB, rounding necessary), and
 * DF16_RAW, DF34_RAW (binary sortable raw fields on the DB).
 * The flag is evaluated in very few special functions only.
 *
 * @param  decfDBmode    Cf. enum DecFloatDBmode
 */
DECL_EXP void SAP_API DecFloat_InitializeDBmode(DecFloatDBmode decfDBmode);


/**
* \brief Decimal Floating Point Shared Library Initialization
*
* This function loads the decNumber shared library libicudecnumber$(SHLIB_EXT)
* and initializes the global decimal floating point environment. 
* This function does nothing if the static library sapdecflib is used.
*
* @return DECF_OK             --  Fine
* @return DECF_NOT_SUPPORTED  --  Shared library could not be loaded
* @return DECF_WRONG_VERSION  --  Shared library has wrong version (check dev-traces)
*/
DECL_EXP DECF_RETURN SAP_API InitDecFloatLib(void);


/* DecFloat <-> String conversions */
/**
 * \brief Convert DecFloat16 to String.
 *
 * This function converts a DecFloat16 number into a string of type SAP_UC*.
 * The caller is responsible for the memory handling.
 *
 * @param  numstr   A pointer to a SAP_UC buffer of type DecFloat16Buff.
 * @param  dfp16    A 64-bit IEEE 754r variable
 * @return: Always DECF_OK
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToString(DecFloat16  dfp16, DecFloat16Buff* numstr);

/**
 * \brief Convert DecFloat34 to String.
 *
 * This function converts a DecFloat34 number into a string of type SAP_UC*.
 * The caller is responsible for the memory handling.
 *
 * @param  numstr   A pointer to a SAP_UC buffer of type DecFloat34Buff.
 * @param  dfp34    A 128-bit IEEE 754r variable
 * @return: Always DECF_OK
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToString(DecFloat34  dfp34, DecFloat34Buff* numstr);

/**
 * \brief Convert (numeric) String to Decfloat16.
 *
 * This function converts a numeric string of type SAP_UC* into a Decfloat16 number.
 * (In the ABAP runtime, use ab_ctodecf16().)
 *
 * @param  numstr   A pointer to an array of SAP_UC* containing the numeric string.
 * @param  dfp16    A pointer to a 64-bit IEEE 754r variable
 * @return DECF_OK              -- Fine
 * @return DECF_INEXACT, DECF_UNDERFLOW -- Almost fine
 * @return DECF_OVERFLOW        -- Number is out of range, e.g., exponent too big
 * @return DECF_CONV_SYNTAX     -- String contains invalid characters
 * @return DECF_NO_MEMORY       -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API StringToDecFloat16(const SAP_UC* numstr, DecFloat16*  dfp16);

/**
 * \brief Convert (numeric) String to Decfloat34.
 *
 * This function converts a numeric string of type SAP_UC* into a Decfloat34 number.
 * (In the ABAP runtime, use ab_ctodecf34().)
 *
 * @param  numstr   A pointer to an array of SAP_UC* containing the numeric string.
 * @param  dfp34    A pointer to a 128-bit IEEE 754r variable
 * @return DECF_OK              -- Fine
 * @return DECF_INEXACT, DECF_UNDERFLOW -- Almost fine
 * @return DECF_OVERFLOW        -- Number is out of range, e.g., exponent too big
 * @return DECF_CONV_SYNTAX     -- String contains invalid characters
 * @return DECF_NO_MEMORY       -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API StringToDecFloat34(const SAP_UC* numstr, DecFloat34*  dfp34);


/* DecFloat <-> DecFloat conversion */
/**
 * \brief   Convert DecFloat16 to DecFloat34
 * @return: Always DECF_OK if the static library sapdecflib is used.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToDecFloat34(DecFloat34*  dfp34_res, DecFloat16  dfp16);

/**
 * \brief  Convert DecFloat34 to DecFloat16
 *
 * (In the ABAP runtime, use ab_decf34ToDecf16().)
 * @return DECF_OK              -- Fine
 * @return DECF_INEXACT, DECF_UNDERFLOW -- Almost fine
 * @return DECF_OVERFLOW        -- Number is out of range, e.g., exponent too big
 * @return DECF_NO_MEMORY       -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToDecFloat16(DecFloat16*  dfp16_res, DecFloat34  dfp34);


/* DecFloat <-> binary sortable DecFloat conversion */
/**
 * \brief Convert 64-bit IEEE 754r decimal floating point variable to 8-byte binary sortable format and store scale information.
 *
 * This function converts a DecFloat16 into an SAP-proprietary format that can be sorted by memcpy.
 * For this purpose, this function has to normalize the DecFloat16 (e.g., 1.50 -> 1.5).
 * The scale information is stored in a separate variable. 
 * (In the ABAP runtime, use ab_DecFloat16ToDecFloat16Raw().)
 *
 * @param dfp16raw_res A pointer to an array of 8 bytes.
 * @param scale        A pointer to a SAP_SHORT variable (provided by the caller).
 * @param dfp16        A 64-bit IEEE 754r decimal floating point variable
 * @return DECF_OK         -- Fine
 * @return DECF_NO_MEMORY  -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToDecFloat16Raw(DecFloat16Raw* dfp16raw_res, SAP_SHORT* scale, DecFloat16  dfp16);

/**
 * \brief Convert 8-byte binary sortable format into 64-bit IEEE 754r decimal floating point variable.
 *
 * In order set the scale of the IEEE 754r variable, this function needs
 * additional information about the scale. 
 * In ABAP, this functionality is available as CL_ABAP_DECFLOAT_RAW=>DECFR16_TO_DECF16.
 *
 * @param dfp16_res    A pointer to a 64-bit IEEE 754r variable
 * @param dfp16raw     A 8-byte sortable decimal floating point variable.
 * @param scale        The desired scale. If scale == -32768, the result will be
 *                     normalized, e.g. 1.5 rather than 1.50. Invalid values for 
 *                     scale will be treated graciously.
 *
 * @return: Always DECF_OK
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16RawToDecFloat16(DecFloat16*  dfp16_res, DecFloat16Raw dfp16raw, SAP_SHORT scale);

/**
 * \brief Convert 128-bit IEEE 754r decimal floating point variable to 16-byte binary sortable format and store scale information.
 *
 * This function converts a DecFloat34 into an SAP-proprietary format that can be sorted by memcpy.
 * For this purpose, this function has to normalize the DecFloat34 (e.g., 1.50 -> 1.5).
 * The scale information is stored in a separate variable. 
 * (In the ABAP runtime, use ab_DecFloat34ToDecFloat34Raw().)
 *
 * @param dfp34raw_res A pointer to an array of 16 bytes.
 * @param scale        A pointer to a SAP_SHORT variable  (provided by the caller).
 * @param dfp34        A 128-bit IEEE 754r decimal floating point variable
 * @return DECF_OK          -- Fine
 * @return DECF_NO_MEMORY   -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToDecFloat34Raw(DecFloat34Raw* dfp34raw_res, SAP_SHORT* scale, DecFloat34  dfp34);

/**
 * \brief Convert 16-byte binary sortable format into 128-bit IEEE 754r decimal floating point variable.
 *
 * In order set the scale information of the IEEE 754r variable, this function needs
 * additional information about the scale. 
 * In ABAP, this functionality is available as CL_ABAP_DECFLOAT_RAW=>DECFR34_TO_DECF34.
 *
 * @param dfp34_res    A pointer to a 128-bit IEEE 754r variable
 * @param dfp34raw     A 16-byte sortable decimal floating point variable.
 * @param scale        The desired scale. If scale == -32768, the result will be
 *                     normalized, e.g. 1.5 rather than 1.50. Invalid values for 
 *                     scale will be treated graciously.
 *
 * @return: Always DECF_OK
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34RawToDecFloat34(DecFloat34*  dfp34_res, DecFloat34Raw dfp34raw, SAP_SHORT scale);


/**
 * \brief  Same as DecFloat16ToDecFloat16Raw
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToDecFloat16RawDB(DecFloat16Raw* dfp16raw_res, SAP_SHORT* scale, DecFloat16  dfp16);

/**
 * \brief  Same as DecFloat16RawToDecFloat16
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16RawToDecFloat16DB(DecFloat16*  dfp16_res, DecFloat16Raw dfp16raw, SAP_SHORT scale);

/**
 * \brief  Same as DecFloat34ToDecFloat34Raw
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToDecFloat34RawDB(DecFloat34Raw* dfp34raw_res, SAP_SHORT* scale, DecFloat34  dfp34);

/**
 * \brief  Same as DecFloat34RawToDecFloat34
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34RawToDecFloat34DB(DecFloat34*  dfp34_res, DecFloat34Raw dfp34raw, SAP_SHORT scale);

/**
 * \brief Convert 64-bit IEEE 754r decimal floating point variable to 8-byte binary sortable format without scale information.
 *
 * This function converts a DecFloat16 into an SAP-proprietary format that can be sorted by memcpy.
 * For this purpose, this function has to normalize the DecFloat16 (e.g., 1.50 -> 1.5).
 * (In the ABAP runtime, you may use ab_NormDecFloat16ToDecFloat16Raw().)
 *
 * @param dfp16raw_res A pointer to an array of 8 bytes.
 * @param dfp16        A 64-bit IEEE 754r decimal floating point variable
 * @return DECF_OK         -- Fine
 * @return DECF_NO_MEMORY  -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API NormDecFloat16ToDecFloat16Raw(DecFloat16Raw* dfp16raw_res, DecFloat16  dfp16);

/**
 * \brief Convert 8-byte binary sortable format into 64-bit IEEE 754r decimal floating point variable.
 *
 * The result will be normalized, e.g., 1.5 rather than 1.50.
 *
 * @param dfp16_res    A pointer to a 64-bit IEEE 754r variable
 * @param dfp16raw     An 8-byte sortable decimal floating point variable
 *
 * @return: Always DECF_OK
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16RawToNormDecFloat16(DecFloat16*  dfp16_res, DecFloat16Raw dfp16raw);

/**
 * \brief Convert 128-bit IEEE 754r decimal floating point variable to 16-byte binary sortable format without scale information.
 *
 * This function converts a DecFloat34 into an SAP-proprietary format that can be sorted by memcpy.
 * For this purpose, this function has to normalize the DecFloat34 (e.g., 1.50 -> 1.5).
 * (In the ABAP runtime, you may use ab_NormDecFloat34ToDecFloat34Raw().)
 *
 * @param dfp34raw_res A pointer to an array of 16 bytes.
 * @param dfp34        A 128-bit IEEE 754r decimal floating point variable
 * @return DECF_OK         -- Fine
 * @return DECF_NO_MEMORY  -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API NormDecFloat34ToDecFloat34Raw(DecFloat34Raw* dfp34raw_res, DecFloat34  dfp34);

/**
 * \brief Convert 16-byte binary sortable format into 128-bit IEEE 754r decimal floating point variable.
 *
 * The result will be normalized, e.g., 1.5 rather than 1.50.
 *
 * @param dfp34_res    A pointer to a 128-bit IEEE 754r variable
 * @param dfp34raw     An 16-byte sortable decimal floating point variable
 *
 * @return: Always DECF_OK
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34RawToNormDecFloat34(DecFloat34*  dfp34_res, DecFloat34Raw dfp34raw);


/* DecFloat <-> Integer conversion */
/**
 * \brief    Convert DecFloat16 to 4-byte or 8-byte integer.
 * (In the ABAP runtime, use ab_decf16ToI() or ab_decf16ToI8().)
 * @return:  DECF_OK, DECF_INEXACT, DECF_UNDERFLOW
 *           DECF_OVERFLOW        -- Number is out of range, e.g., exponent too big
 *           DECF_INVALID_OP      -- DecFloat is a NaN or Infinity
 *           DECF_NO_MEMORY       -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToSAP_INT(SAP_INT* i, DecFloat16  dfp16);
DECL_EXP DECF_RETURN SAP_API DecFloat16ToSAP_LLONG(SAP_LLONG* l, DecFloat16  dfp16);  

/**
 * \brief    Convert 4-byte integer to DecFloat16.
 * (In the ABAP runtime, use ab_iToDecf16().)
 * @return:  DECF_OK              
 *           DECF_NO_MEMORY       
 */
DECL_EXP DECF_RETURN SAP_API SAP_INTToDecFloat16(DecFloat16*  dfp16_res, SAP_INT i);

/**
 * \brief    Convert 8-byte integer to DecFloat16.
 * (In the ABAP runtime, use ab_i8ToDecf16().)
 * @return:  DECF_OK
 *           DECF_INEXACT
 *           DECF_NO_MEMORY 
 */
DECL_EXP DECF_RETURN SAP_API SAP_LLONGToDecFloat16(DecFloat16*  dfp16_res, SAP_LLONG l); 

/**
 * \brief    Convert DecFloat34 to 4-byte or 8-byte integer.
 * (In the ABAP runtime, use ab_decf34ToI() or ab_decf34ToI8().)
 * @return:  DECF_OK, DECF_INEXACT, DECF_UNDERFLOW
 *           DECF_OVERFLOW        -- Number is out of range, e.g., exponent too big
 *           DECF_INVALID_OP      -- DecFloat is a NaN or Infinity
 *           DECF_NO_MEMORY       -- A memoy allocation error occurred
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToSAP_INT(SAP_INT* i, DecFloat34  dfp34);
DECL_EXP DECF_RETURN SAP_API DecFloat34ToSAP_LLONG(SAP_LLONG* l, DecFloat34  dfp34);  

/**
 * \brief    Convert 4-byte or 8-byte integer to DecFloat34.
 * (In the ABAP runtime, use ab_iToDecf34() or ab_i8ToDecf34().)
 * @return:  DECF_OK              
 *           DECF_NO_MEMORY       
 */
DECL_EXP DECF_RETURN SAP_API SAP_INTToDecFloat34(DecFloat34*  dfp34_res, SAP_INT i);
DECL_EXP DECF_RETURN SAP_API SAP_LLONGToDecFloat34(DecFloat34*  dfp34_res, SAP_LLONG l);  


/* DecFloat <-> Double conversion */
/**
 * \brief    Convert DecFloat to 8-byte binary float.
 * The rounding behavior is platform dependent.
 * (In the ABAP runtime, consider using ab_decf16ToF() or ab_decf34ToF().)
 * @return:  DECF_OK              -- As an exception from the normal meaning of DECF_OK:
 *                                   The number may have been rounded and may be a NaN or Infinity.
 *           DECF_OVERFLOW        -- Number is out of range, e.g., exponent too big.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToSAP_DOUBLE(SAP_DOUBLE* d, DecFloat16  dfp16);
DECL_EXP DECF_RETURN SAP_API DecFloat34ToSAP_DOUBLE(SAP_DOUBLE* d, DecFloat34  dfp34);

/**
 * \brief    Convert 8-byte binary float to DecFloat.
 * The rounding behavior is platform dependent.
 * ATTENTION: The behavior for NaNs and Infinities is platform dependent.
 * (In the ABAP runtime, consider using ab_fToDecf16() or ab_fToDecf34().)
 * @return:  DECF_INEXACT      -- The number may have been rounded or may be exact!
 *           DECF_NO_MEMORY       
 */
DECL_EXP DECF_RETURN SAP_API SAP_DOUBLEToDecFloat16(DecFloat16*  dfp16_res, SAP_DOUBLE i);
DECL_EXP DECF_RETURN SAP_API SAP_DOUBLEToDecFloat34(DecFloat34*  dfp34_res, SAP_DOUBLE i);


/* DecFloat <-> BCD conversion */
/**
 * \brief Convert to ABAP type P (BCD).
 *
 * Convert a 64-bit IEEE 754r decimal floating point variable into the
 * ABAP type P.
 *
 * INPUT:
 * @param  dfp16        Decfloat value
 * @param  length       Length of BCD buffer in bytes
 * @param  decPlaces    Number of decimal places (Nachkommastellen) of the
 *                      BCD number
 * OUTPUT:
 * @param  bcd          Unaligned BCD number
 *
 * @return DECF_OK
 * @return DECF_INEXACT
 * @return DECF_UNDERFLOW
 * @return DECF_OVERFLOW    Overflow. A higher level should raise a catchable
 *                          exception.
 * @return DECF_NO_MEMORY   The caller should abort.
 * @return DECF_INVALID_OP  Input is a NaN or Infinity or garbage. The caller should raise an exception.
 */
DECL_EXP DECF_RETURN  SAP_API DecFloat16ToBCD(SAP_RAW* bcd_res, DecFloat16 dfp16, intR length, intR decPlaces);

/**
 * \brief Round IEEE value such that it fits into ABAP type P (BCD).
 *
 * If decFloatDBmode == DECF_DBmode_roundForDEC:
 * Round a 64-bit IEEE 754r decimal floating point value according to
 * decPlaces and check that it fits into the BCD type specified.
 * When returning from this function, dfp16 has at most decPlaces
 * decimal places, but it may have less.
 *
 * INPUT:
 * @param  length       Length of BCD buffer in bytes
 * @param  decPlaces    Number of decimal places (Nachkommastellen) of the
 *                      BCD number
 * CHANGE:
 * @param  dfp16        Decfloat value
 *
 * @return DECF_OK
 * @return DECF_INEXACT
 * @return DECF_UNDERFLOW
 * @return DECF_OVERFLOW    Overflow. A higher level should raise a catchable
 *                          exception.
 * @return DECF_NO_MEMORY   The caller should abort.
 * @return DECF_INVALID_OP  Garbage input. The caller should raise an exception.
 */
DECL_EXP DECF_RETURN  SAP_API DecFloat16RoundForDEC(DecFloat16* dfp16, intR length, intR decPlaces);

/**
 * \brief Compare an IEEE value with a DF16_DEC value.
 *
 * If decFloatDBmode == DECF_DBmode_roundForDEC:
 * This function rounds an IEEE value according the specified number of
 * decimal places (Nachkommastellen) and compares the result with
 * another DecFloat value. (The latter is assumed to be a DF16_DEC
 * value which has already been rounded.)
 * If decFloatDBmode == DECF_DBmode_native, both values are not rounded,
 * but just compared.
 *
 * INPUT:
 * @param  unroundedDf  IEEE decimal floating point value, will be rounded if
 *                      decFloatDBmode == DECF_DBmode_roundForDEC.
 * @param  dbValue      DF16_DEC value in IEEE decimal floating point format
 * @param  decPlaces    Number of decimal places (Nachkommastellen) of the
 *                      DF16_DEC type
 * OUTPUT:
 * @param  p_rc         DECF_OK, DECF_INEXACT, DECF_UNDERFLOW: No special
 *                      action necessary;
 *                      DECF_NO_MEMORY: The caller should abort;
 *                      DECF_INVALID_OP: Garbage input, the caller should raise an exception.
 *
 * @return              -1 if (rounded) IEEE value <  dbValue
 *                      0  if (rounded) IEEE value numerically equal to dbValue
 *                      1  if (rounded) IEEE value >  dbValue.
 *                      If p_rc is DECF_INVALID_OP,
 *                      the return value is guaranteed to be non-zero.
 */
DECL_EXP SAP_INT SAP_API DecFloat16CompareForDEC(DecFloat16 unroundedDf,
                                DecFloat16 dbValue,
                                intR decPlaces,
                                DECF_RETURN* p_rc);

/**
 * \brief Convert from ABAP type P (BCD) to 64-bit IEEE 754r
 *
 * Convert a BCD number (ABAP type P) into a 64-bit IEEE 754r decimal
 * floating point variable.
 *
 * INPUT:
 * @param  bcd          Unaligned BCD number
 * @param  length       Length of BCD number in bytes
 * @param  decPlaces    Number of decimal places of the BCD number
 *
 * OUTPUT:
 * @param  dfp16_res    Decfloat value
 *
 * @return DECF_OK
 * @return DECF_INEXACT
 * @return DECF_NO_MEMORY   The caller should abort.
 * @return DECF_INVALID_OP  Garbage input. The caller should raise an exception.
 */
DECL_EXP DECF_RETURN  SAP_API BCDToDecFloat16(DecFloat16* dfp16_res, SAP_RAW*  bcd, intR length, intR decPlaces );


/**
 * \brief Convert to ABAP type P (BCD).
 *
 * Convert a 128-bit IEEE 754r decimal floating point variable into the
 * ABAP type P.
 *
 * INPUT:
 * @param  dfp34        Decfloat value
 * @param  length       Length of BCD buffer in bytes
 * @param  decPlaces    Number of decimal places (Nachkommastellen) of the
 *                      BCD number
 * OUTPUT:
 * @param  bcd          Unaligned BCD number
 *
 * @return DECF_OK
 * @return DECF_INEXACT
 * @return DECF_UNDERFLOW
 * @return DECF_OVERFLOW    Overflow. A higher level should raise a catchable
 *                          exception.
 * @return DECF_NO_MEMORY   The caller should abort.
 * @return DECF_INVALID_OP  Input is a NaN or Infinity or garbage. The caller should raise an exception.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToBCD(SAP_RAW* bcd_res, DecFloat34 dfp34, intR length, intR decPlaces);

/**
 * \brief Round IEEE value such that it fits into ABAP type P (BCD).
 *
 * If decFloatDBmode == DECF_DBmode_roundForDEC:
 * Round a 128-bit IEEE 754r decimal floating point value according to
 * decPlaces and check that it fits into the BCD type specified.
 *
 * INPUT:
 * @param  length       Length of BCD buffer in bytes
 * @param  decPlaces    Number of decimal places (Nachkommastellen) of the
 *                      BCD number
 * CHANGE:
 * @param  dfp34        Decfloat value
 *
 * @return DECF_OK
 * @return DECF_INEXACT
 * @return DECF_UNDERFLOW
 * @return DECF_OVERFLOW    Overflow. A higher level should raise a catchable
 *                          exception.
 * @return DECF_NO_MEMORY   The caller should abort.
 * @return DECF_INVALID_OP  Garbage input. The caller should raise an exception.
 */
DECL_EXP DECF_RETURN  SAP_API DecFloat34RoundForDEC(DecFloat34* dfp34, intR length, intR decPlaces);

/**
 * \brief Compare an IEEE value with a DF34_DEC value.
 *
 * If decFloatDBmode == DECF_DBmode_roundForDEC:
 * This function rounds an IEEE value according the specified number of
 * decimal places (Nachkommastellen) and compares the result with
 * another DecFloat value. (The latter is assumed to be a DF34_DEC
 * value which has already been rounded.)
 * If decFloatDBmode == DECF_DBmode_native, both values are not rounded,
 * but just compared.
 *
 * INPUT:
 * @param  unroundedDf  IEEE decimal floating point value, will be rounded if
 *                      decFloatDBmode == DECF_DBmode_roundForDEC.
 * @param  dbValue      DF34_DEC value in IEEE decimal floating point format
 * @param  decPlaces    Number of decimal places (Nachkommastellen) of the
 *                      DF34_DEC type
 * OUTPUT:
 * @param  p_rc         DECF_OK, DECF_INEXACT, DECF_UNDERFLOW: No special
 *                      action necessary;
 *                      DECF_NO_MEMORY: The caller should abort;
 *                      DECF_INVALID_OP: Garbage input; the caller should raise an exception.
 *
 * @return              -1 if (rounded) IEEE value <  dbValue
 *                      0  if (rounded) IEEE value numerically equal to dbValue
 *                      1  if (rounded) IEEE value >  dbValue.
 *                      If p_rc is DECF_OVERFLOW or DECF_INVALID_OP,
 *                      the return value is guaranteed to be non-zero.
 */
DECL_EXP SAP_INT SAP_API DecFloat34CompareForDEC(DecFloat34 unroundedDf,
                                DecFloat34 dbValue,
                                intR decPlaces,
                                DECF_RETURN* p_rc);

/**
 * \brief Convert from ABAP type P (BCD) to 128-bit IEEE 754r
 *
 * Convert a BCD number (ABAP type P) into a 128-bit IEEE 754r decimal
 * floating point variable.
 *
 * INPUT:
 * @param  bcd          Unaligned BCD number
 * @param  length       Length of BCD number in bytes
 * @param  decPlaces    Number of decimal places of the BCD number
 *
 * OUTPUT:
 * @param  dfp34_res    Decfloat value
 *
 * @return DECF_OK
 * @return DECF_NO_MEMORY   The caller should abort.
 * @return DECF_INVALID_OP  Garbage input. The caller should raise an exception.
 */
DECL_EXP DECF_RETURN SAP_API BCDToDecFloat34(DecFloat34* dfp34_res, SAP_RAW* bcd, intR length, intR decPlaces );




/* Decfloat arithmetic operations */
/**
 * \brief Computes the sum of two DecFloat16 numbers.
 *
 * The number *dfp16_res is set to dfp16_lhs + dfp16_rhs.
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16_lhs  Left-hand side operand.
 * @param dfp16_rhs  Right-hand side operand.
 *
 * @return            DECF_OK 
 * @return            DECF_INEXACT
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Add(DecFloat16* dfp16_res, DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs );

/**
 * \brief Computes the sum of two DecFloat34 numbers.
 *
 * The number *dfp34_res is set to dfp34_lhs + dfp34_rhs.
 * @param dfp34_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp34_lhs  Left-hand side operand.
 * @param dfp34_rhs  Right-hand side operand.
 *
 * @return            DECF_OK
 * @return            DECF_INEXACT
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Add(DecFloat34* dfp34_res, DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs );

/**
 * \brief Computes the difference of two DecFloat16 numbers.
 *
 * The number *dfp16_res is set to dfp16_lhs - dfp16_rhs.
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16_lhs  Left-hand side operand.
 * @param dfp16_rhs  Right-hand side operand.
 *
 * @return            DECF_OK
 * @return            DECF_INEXACT
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Sub(DecFloat16* dfp16_res, DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs );

/**
 * \brief Computes the difference of two DecFloat34 numbers.
 *
 * The number *dfp34_res is set to dfp34_lhs - dfp34_rhs.
 * @param dfp34_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp34_lhs  Left-hand side operand.
 * @param dfp34_rhs  Right-hand side operand.
 *
 * @return            DECF_OK 
 * @return            DECF_INEXACT
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Sub(DecFloat34* dfp34_res, DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs );

/**
 * \brief Computes the multiplication of two DecFloat16 numbers.
 *
 * The number *dfp16_res is set to dfp16_lhs * dfp16_rhs.
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16_lhs  Left-hand side operand.
 * @param dfp16_rhs  Right-hand side operand.
 *
 * @return            DECF_OK, DECF_INEXACT, DECF_UNDERFLOW
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Mult(DecFloat16* dfp16_res, DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs );

/**
 * \brief Computes the multiplication of two DecFloat34 numbers.
 *
 * The number *dfp34_res is set to dfp34_lhs / dfp34_rhs.
 * @param dfp34_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp34_lhs  Left-hand side operand.
 * @param dfp34_rhs  Right-hand side operand.
 *
 * @return            DECF_OK, DECF_INEXACT, DECF_UNDERFLOW
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Mult(DecFloat34* dfp34_res, DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs );

/**
 * \brief Computes the division of two DecFloat16 numbers.
 *
 * The number *dfp16_res is set to dfp16_lhs / dfp16_rhs.
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16_lhs  Left-hand side operand.
 * @param dfp16_rhs  Right-hand side operand.
 *
 * @return            DECF_OK, DECF_INEXACT, DECF_UNDERFLOW
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_DIV_ZERO -- Division by zero.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers or division is not defined (f.g. 0/0).
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Div(DecFloat16* dfp16_res, DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs );

/**
 * \brief Computes the division of two DecFloat34 numbers.
 *
 * The number *dfp34_res is set to dfp34_lhs / dfp34_rhs.
 * @param dfp34_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp34_lhs  Left-hand side operand.
 * @param dfp34_rhs  Right-hand side operand.
 *
 * @return            DECF_OK, DECF_INEXACT, DECF_UNDERFLOW
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_DIV_ZERO -- Division by zero.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers or division is not defined (f.g. 0/0).
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Div(DecFloat34* dfp34_res, DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs );

/**
 * \brief Computes the DIV operator.
 * Note: In ABAP, DIV is defined differently, see ab_Decf34Div().
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_DIV(DecFloat16* dfp16_res, DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs );
DECL_EXP DECF_RETURN SAP_API DecFloat34_DIV(DecFloat34* dfp34_res, DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs );

/**
 * \brief Computes the MOD operator.
 * Note: In ABAP, MOD is defined differently, see ab_Decf34Mod().
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_MOD(DecFloat16* dfp16_res, DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs );
DECL_EXP DECF_RETURN SAP_API DecFloat34_MOD(DecFloat34* dfp34_res, DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs );


/* Relational and logical operations */
/* Op ==  */
/**
 * \brief Equality operation for DecFloat16 numbers.
 *
 * This function checks whether two DecFloat16 numbers
 * are numerically equal, i.e. it is independent of the
 * scale of the numbers.
 * (In the ABAP runtime, consider using ab_decf16Eq().)
 *
 * @param  dfp16_lhs  Left-hand side operand.
 * @param  dfp16_rhs  Right-hand side operand.
 * @param  prc        Return code. Possible values: DECF_OK -- Fine, DECF_NO_MEMORY -- A memory allocation error occurred,DECF_INVALID_OP -- Arguments are no-numbers .
 *
 * @return  TRUE,FALSE
 */
DECL_EXP SAP_BOOL SAP_API DecFloat16_EQ(DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs, DECF_RETURN* prc );

/**
 * \brief Equality operation for DecFloat34 numbers.
 *
 * This function checks whether two DecFloat34 numbers
 * are numerically equal, i.e. it is independent of the
 * scale of the numbers.
 * (In the ABAP runtime, consider using ab_decf34Eq().)
 *
 * @param  dfp34_lhs  Left-hand side operand.
 * @param  dfp34_rhs  Right-hand side operand.
 * @param  prc        Return code. Possible values: DECF_OK -- Fine, DECF_NO_MEMORY -- A memory allocation error occurred,DECF_INVALID_OP -- Arguments are no-numbers .
 *
 * @return  TRUE,FALSE
 */
DECL_EXP SAP_BOOL SAP_API DecFloat34_EQ(DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs, DECF_RETURN* prc  );

/* Op >  */
/**
 * \brief Relational ">" operation for DecFloat16 numbers.
 *
 * This function checks whether a DecFloat16 number
 * is numerically greater than another,  independent of the
 * scale of the numbers.
 *
 * @param  dfp16_lhs  Left-hand side operand.
 * @param  dfp16_rhs  Right-hand side operand.
 * @param  prc        Return code. Possible values: DECF_OK -- Fine, DECF_NO_MEMORY -- A memory allocation error occurred,DECF_INVALID_OP -- Arguments are no-numbers .
 *
 * @return  TRUE,FALSE
 */
DECL_EXP SAP_BOOL SAP_API DecFloat16_GT(DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs, DECF_RETURN* prc );

/**
 * \brief Relational ">" operation for DecFloat34 numbers.
 *
 * This function checks whether a DecFloat34 number
 * is numerically greater than another,  independent of the
 * scale of the numbers.
 *
 * @param  dfp34_lhs  Left-hand side operand.
 * @param  dfp34_rhs  Right-hand side operand.
 * @param  prc        Return code. Possible values: DECF_OK -- Fine, DECF_NO_MEMORY -- A memory allocation error occurred,DECF_INVALID_OP -- Arguments are no-numbers .
 *
 * @return  TRUE,FALSE
 */
DECL_EXP SAP_BOOL SAP_API DecFloat34_GT(DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs, DECF_RETURN* prc );

/* Op <  */
/**
 * \brief Relational "<" operation for DecFloat16 numbers.
 *
 * This function checks whether a DecFloat16 number
 * is numerically less than another,  independent of the
 * scale of the numbers.
 *
 * @param  dfp16_lhs  Left-hand side operand.
 * @param  dfp16_rhs  Right-hand side operand.
 * @param  prc        Return code. Possible values: DECF_OK -- Fine, DECF_NO_MEMORY -- A memory allocation error occurred,DECF_INVALID_OP -- Arguments are no-numbers .
 *
 * @return  TRUE,FALSE
 */
DECL_EXP SAP_BOOL SAP_API DecFloat16_LT(DecFloat16  dfp16_lhs, DecFloat16  dfp16_rhs, DECF_RETURN* prc );

/**
 * \brief Relational "<" operation for DecFloat34 numbers.
 *
 * This function checks whether a DecFloat34 number
 * is numerically less than another,  independent of the
 * scale of the numbers.
 *
 * @param  dfp34_lhs  Left-hand side operand.
 * @param  dfp34_rhs  Right-hand side operand.
 * @param  prc        Return code. Possible values: DECF_OK -- Fine, DECF_NO_MEMORY -- A memory allocation error occurred,DECF_INVALID_OP -- Arguments are no-numbers .
 *
 * @return  TRUE,FALSE
 */
DECL_EXP SAP_BOOL SAP_API DecFloat34_LT(DecFloat34  dfp34_lhs, DecFloat34  dfp34_rhs, DECF_RETURN* prc );

/**
 * \brief This function compares two DecFloat16 numbers numerically.
 *
 * If dfp16_lhs  < dfp16_rhs then the function returns -1.
 * If dfp16_lhs == dfp16_rhs then the function returns  0.
 * If dfp16_lhs  > dfp16_rhs then the function returns  1.
 *
 * @param  dfp16_lhs  Left-hand side operand.
 * @param  dfp16_rhs  Right-hand side operand.
 *
 * @return -1,0,1
 */
DECL_EXP SAP_INT SAP_API DecFloat16Compare(DecFloat16 dfp16_lhs, DecFloat16 dfp16_rhs, DECF_RETURN* p_rc);

/**
 * \brief This function compares two DecFloat34 numbers numerically.
 *
 * If dfp34_lhs  < dfp34_rhs then the function returns -1.
 * If dfp34_lhs == dfp34_rhs then the function returns  0.
 * If dfp34_lhs  > dfp34_rhs then the function returns  1.
 *
 * @param  dfp34_lhs  Left-hand side operand.
 * @param  dfp34_rhs  Right-hand side operand.
 *
 * @return -1,0,1
 */
DECL_EXP SAP_INT SAP_API DecFloat34Compare(DecFloat34 dfp34_lhs, DecFloat34 dfp34_rhs, DECF_RETURN* p_rc);

/* Rounding */
DECL_EXP DECF_RETURN SAP_API DecFloat16RoundDec(DecFloat16* dfp16, SAP_INT dec, DecFRounding decFRound);
DECL_EXP DECF_RETURN SAP_API DecFloat16RoundPrec(DecFloat16* dfp16, SAP_INT prec, DecFRounding decFRound);

DECL_EXP DECF_RETURN SAP_API DecFloat34RoundDec(DecFloat34* dfp34, SAP_INT dec, DecFRounding decFRound);
DECL_EXP DECF_RETURN SAP_API DecFloat34RoundPrec(DecFloat34* dfp34, SAP_INT prec, DecFRounding decFRound);

/* Rescaling */
DECL_EXP DECF_RETURN SAP_API DecFloat16RescaleDec(DecFloat16* dfp16, SAP_INT dec, DecFRounding decFRound);
DECL_EXP DECF_RETURN SAP_API DecFloat16RescalePrec(DecFloat16* dfp16, SAP_INT prec, DecFRounding decFRound);

DECL_EXP DECF_RETURN SAP_API DecFloat34RescaleDec(DecFloat34* dfp34, SAP_INT dec, DecFRounding decFRound);
DECL_EXP DECF_RETURN SAP_API DecFloat34RescalePrec(DecFloat34* dfp34, SAP_INT prec, DecFRounding decFRound);

/* Utility Functions */
DECL_EXP SAP_BOOL SAP_API DecFloat16IsInfinite(DecFloat16 dfp16);
DECL_EXP SAP_BOOL SAP_API DecFloat34IsInfinite(DecFloat34 dfp34);

DECL_EXP SAP_BOOL SAP_API DecFloat16IsFinite(DecFloat16 dfp16);
DECL_EXP SAP_BOOL SAP_API DecFloat34IsFinite(DecFloat34 dfp34);

DECL_EXP SAP_BOOL SAP_API DecFloat16IsNaN(DecFloat16 dfp16);
DECL_EXP SAP_BOOL SAP_API DecFloat34IsNaN(DecFloat34 dfp34);

DECL_EXP DecFloat16* SAP_API DecFloat16Zero(DecFloat16* dfp16);
DECL_EXP DecFloat34* SAP_API DecFloat34Zero(DecFloat34* dfp34);

DECL_EXP DecFloat16 SAP_API DecFloat16Ceil(DecFloat16 dfp16, DECF_RETURN* p_rc);
DECL_EXP DecFloat34 SAP_API DecFloat34Ceil(DecFloat34 dfp34, DECF_RETURN* p_rc);

DECL_EXP DecFloat16 SAP_API DecFloat16Floor(DecFloat16 dfp16, DECF_RETURN* p_rc);
DECL_EXP DecFloat34 SAP_API DecFloat34Floor(DecFloat34 dfp34, DECF_RETURN* p_rc);

/** /brief Minimum IEEE 754r value = -Infinity */
DECL_EXP DecFloat16 SAP_API GetMinDecFloat16(void);
/** /brief Minimum IEEE 754r value = -Infinity */
DECL_EXP DecFloat34 SAP_API GetMinDecFloat34(void);


/**
 * \brief  Get the exponent of a Decfloat number.
 *
 * These functions deliver the exponent that occurs if the number is written as
 *     <integer> * 10 ^ <exponent>.
 * Example: 1234.50 has the exponent -2 (since the representation is 123450E-2).
 * For NaNs and Infinities, the result is undefined.
 * 
 * Note: CL_ABAP_MATH=>GET_SCALE returns the exponent with reversed sign.
 *
 * @return  Always DECF_OK.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16GetExponent(SAP_INT* exponent, DecFloat16 dfp16);
DECL_EXP DECF_RETURN SAP_API DecFloat34GetExponent(SAP_INT* exponent, DecFloat34 dfp34);


DECL_EXP DECF_RETURN SAP_API DecFloat16GetNumOfDigits(SAP_INT* digits, DecFloat16 dfp16);
DECL_EXP DECF_RETURN SAP_API DecFloat34GetNumOfDigits(SAP_INT* digits, DecFloat34 dfp34);



/**
 * \brief Converts a DecFloat16 number into its preferred network byte order.
 *
 * The preferred neutral network byte order is Big-Endian.
 *
 * @param   dfp16_neutral A pointer to a DecFloat16 number where the result is written to.
 * @param   dfp16         The DecFloat16 number to be converted.
 *
 * @return  Always DECF_OK.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToDecFloat16Neutral(DecFloat16* dfp16_neutral, DecFloat16 dfp16);

/**
 * \brief Converts a neutral DecFloat16 number into its machine-dependent encoding (big- or little-endian).
 *
 * The preferred neutral network byte order is Big-Endian.
 *
 * @param   dfp16                A pointer to a DecFloat16 number where the result is written to.
 * @param   dfp16_neutal         The neutral DecFloat16 number to be converted.
 *
 * @return  Always DECF_OK.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16NeutralToDecFloat16(DecFloat16* dfp16, DecFloat16 dfp16_neutral);

/**
 * \brief Converts a DecFloat34 number into its preferred network byte order.
 *
 * The preferred neutral network byte order is Big-Endian.
 *
 * @param   dfp34_neutral A pointer to a DecFloat34 number where the result is written to.
 * @param   dfp34         The DecFloat34 number to be converted.
 *
 * @return  Always DECF_OK.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToDecFloat34Neutral(DecFloat34* dfp34_neutral, DecFloat34 dfp34);

/**
 * \brief Converts a neutral DecFloat34 number into its machine-dependent encoding (big- or little-endian).
 *
 * The preferred neutral network byte order is Big-Endian.
 *
 * @param   dfp34                A pointer to a DecFloat34 number where the result is written to.
 * @param   dfp34_neutal         The neutral DecFloat34 number to be converted.
 *
 * @return  Always DECF_OK.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34NeutralToDecFloat34(DecFloat34* dfp34, DecFloat34 dfp34_neutral);


/* Normalization functions */

/**
 * \brief In-place normalization of a DecFloat16 number.
 *
 * Cf. DecFloat16ToNormDecFloat16().
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16Normalize(DecFloat16* dfp16);

/**
 * \brief In-place normalization of a DecFloat34 number.
 *
 * Cf. DecFloat34ToNormDecFloat34().
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34Normalize(DecFloat34* dfp34);

/**
 * \brief Converts a DecFloat16 number to a normalized DecFloat16 number.
 *
 * The result is stored in norm_dfp16.
 * Trailing zeros are removed (without changing the numerical value). 
 * If the number is zero, the sign is removed.
 *
 * @param   norm_dfp16 A pointer to a DecFloat16 number where the result is written to.
 * @param   dfp16      The DecFloat16 number to be normalized.
 *
 * @return  DECF_OK -- Fine.
 * @return  DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return  DECF_INVALID_OP -- Arguments are no-numbers .
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16ToNormDecFloat16(DecFloat16* norm_dfp16, DecFloat16 dfp16);

/**
 * \brief Converts a DecFloat34 number to a normalized DecFloat34 number.
 *
 * The result is stored in norm_dfp34.
 * Trailing zeros are removed (without changing the numerical value). 
 * If the number is zero, the sign is removed.
 *
 * @param   norm_dfp34 A pointer to a DecFloat34 number where the result is written to.
 * @param   dfp34      The DecFloat34 number to be normalized.
 *
 * @return  DECF_OK -- Fine. (Argument may be an Infinity or quiet NaN.)
 * @return  DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return  DECF_INVALID_OP -- Argument is a signaling NaN.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34ToNormDecFloat34(DecFloat34* norm_dfp34, DecFloat34 dfp34);


/**
 * \brief Returns the result of raising the base to the power of the exponent.
 *
 * The exponent can be a fractional number.
 *
 * @param dfp34_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param base       Base of the power operation.
 * @param exponent   Exponent of the power operation
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Arguments are no-numbers or exponent contains fractional digits.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_fPow(DecFloat34* dfp34_res, DecFloat34 base, DecFloat34 exponent);


/**
 * \brief Returns the square root of a DecFloat16.
 *
 * The number *dfp16_res is set to the square root of dfp16, rounded if necessary, to
 * 16 digits using the DECF_ROUND_HALF_EVEN rounding mode.
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Sqrt(DecFloat16* dfp16_res, DecFloat16 dfp16);

/**
 * \brief Returns the square root of a DecFloat34.
 *
 * The number *dfp34_res is set to the square root of dfp34, rounded if necessary, to
 * 34 digits using the DECF_ROUND_HALF_EVEN rounding mode.
 * @param dfp16_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Sqrt(DecFloat34* dfp34_res, DecFloat34 dfp34);

/**
 * \brief Exponential function for DecFloat16 numbers.
 *
 * The number is set to e raised to the power of rhs, rounded if necessary using
 * the round–half–even rounding algorithm.
 *
 * Finite results will always be full precision and inexact, except when rhs is a zero or
 * –Infinity (giving 1 or 0 respectively). Inexact results will almost always be correctly
 * rounded, but may be up to 1 ulp (unit in last place) in error in rare cases.
 *
 * This is a mathematical function; the 10**6 restrictions on precision and range apply as
 * described above.
 *
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Exp(DecFloat16* dfp16_res, DecFloat16 dfp16);

/**
 * \brief Exponential function for DecFloat34 numbers.
 *
 * The number is set to e raised to the power of rhs, rounded if necessary using
 * the round–half–even rounding algorithm.
 *
 * Finite results will always be full precision and inexact, except when rhs is a zero or
 * –Infinity (giving 1 or 0 respectively). Inexact results will almost always be correctly
 * rounded, but may be up to 1 ulp (unit in last place) in error in rare cases.
 *
 * This is a mathematical function; the 10**6 restrictions on precision and range apply as
 * described above.
 *
 * @param dfp16_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Exp(DecFloat34* dfp34_res, DecFloat34 dfp34);

/**
 * \brief Natural logarithm function for DecFloat16 numbers.
 *
 * The number is set to the natural logarithm (in base e) of rhs, rounded if necessary using
 * the round–half–even rounding algorithm.
 *
 * Finite results will always be full precision and inexact, except when rhs is a zero or
 * –Infinity (giving 1 or 0 respectively). Inexact results will almost always be correctly
 * rounded, but may be up to 1 ulp (unit in last place) in error in rare cases.
 *
 * This is a mathematical function; the 10**6 restrictions on precision and range apply as
 * described above.
 *
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Ln(DecFloat16* dfp16_res, DecFloat16 dfp16);

/**
 * \brief Natural logarithm function for DecFloat34 numbers.
 *
 * The number is set to the natural logarithm (in base e) of rhs, rounded if necessary using
 * the round–half–even rounding algorithm.
 *
 * Finite results will always be full precision and inexact, except when rhs is a zero or
 * –Infinity (giving 1 or 0 respectively). Inexact results will almost always be correctly
 * rounded, but may be up to 1 ulp (unit in last place) in error in rare cases.
 *
 * This is a mathematical function; the 10**6 restrictions on precision and range apply as
 * described above.
 *
 * @param dfp16_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Ln(DecFloat34* dfp34_res, DecFloat34 dfp16);


/**
 * \brief Logarithm in base 10 function for DecFloat16 numbers.
 *
 * The number is set to the logarithm in base 10 of rhs, rounded if necessary using
 * the round–half–even rounding algorithm.
 *
 * Finite results will always be full precision and inexact, except when rhs is a zero or
 * –Infinity (giving 1 or 0 respectively). Inexact results will almost always be correctly
 * rounded, but may be up to 1 ulp (unit in last place) in error in rare cases.
 *
 * This is a mathematical function; the 10**6 restrictions on precision and range apply as
 * described above.
 *
 * @param dfp16_res  Pointer to the IEEE 754r 64-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16_Log10(DecFloat16* dfp16_res, DecFloat16 dfp16);

/**
 * \brief Logarithm in base 10 function for DecFloat34 numbers.
 *
 * The number is set to the logarithm in base 10 of rhs, rounded if necessary using
 * the round–half–even rounding algorithm.
 *
 * Finite results will always be full precision and inexact, except when rhs is a zero or
 * –Infinity (giving 1 or 0 respectively). Inexact results will almost always be correctly
 * rounded, but may be up to 1 ulp (unit in last place) in error in rare cases.
 *
 * This is a mathematical function; the 10**6 restrictions on precision and range apply as
 * described above.
 *
 * @param dfp16_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return            DECF_OK -- Fine
 * @return            DECF_OVERFLOW -- Exponent of result too big.
 * @return            DECF_NO_MEMORY -- A memory allocation error occurred.
 * @return            DECF_INVALID_OP -- Argument is no-number or negative.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34_Log10(DecFloat34* dfp34_res, DecFloat34 dfp16);


/**
 * \brief Returns the "next" DecFloat16 number to dfp16 in the direction of -Infinity
 *
 *  Returns the "next" DecFloat16 number to dfp16 in the direction of -Infinity according
 *  to the IEEE 754r rules for "nextDown".
 *
 *
 * @param dfp16_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return           DECF_OK -- Fine.
 * @return           DECF_INVALID_OP -- -- Argument is sNaN.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16NextMinus(DecFloat16* dfp16_res,DecFloat16 dfp16);


/**
 * \brief Returns the "next" DecFloat16 number to dfp16 in the direction of Infinity
 *
 *  Returns the "next" DecFloat16 number to dfp16 in the direction of -Infinity according
 *  to the IEEE 754r rules for "nextDown".
 *
 *
 * @param dfp16_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp16      Argument value.
 *
 * @return           DECF_OK -- Fine.
 * @return           DECF_INVALID_OP -- -- Argument is sNaN.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat16NextPlus(DecFloat16* dfp16_res,DecFloat16 dfp16);


/**
 * \brief Returns the "next" DecFloat34 number to dfp34 in the direction of -Infinity
 *
 *  Returns the "next" DecFloat34 number to dfp34 in the direction of -Infinity according
 *  to the IEEE 754r rules for "nextDown".
 *
 *
 * @param dfp34_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp34      Argument value.
 *
 * @return           DECF_OK -- Fine.
 * @return           DECF_INVALID_OP -- -- Argument is sNaN.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34NextMinus(DecFloat34* dfp34_res,DecFloat34 dfp34);


/**
 * \brief Returns the "next" DecFloat34 number to dfp34 in the direction of Infinity
 *
 *  Returns the "next" DecFloat34 number to dfp34 in the direction of -Infinity according
 *  to the IEEE 754r rules for "nextDown".
 *
 *
 * @param dfp34_res  Pointer to the IEEE 754r 128-bit variable where the result is stored.
 * @param dfp34      Argument value.
 *
 * @return           DECF_OK -- Fine.
 * @return           DECF_INVALID_OP -- -- Argument is sNaN.
 */
DECL_EXP DECF_RETURN SAP_API DecFloat34NextPlus(DecFloat34* dfp34_res,DecFloat34 dfp34);

typedef void * (*Decfl34AllocateCallBack)(SAP_ULLONG);

/**
 * \brief Converts divident and divisor to an arbitrary precision decNumber format and
 * performs a division to a decfloat34. Note that divident and divisor are not transformed
 * to a decfloat34 _before_ the division (and thus loosing precision or generating exceptions
 * because of too large numbers) but _during_ the divison.
 *
 * NOTE: This function is not available in the RFC SDK.
 *
 * @param divident   Divident (as ASCII encoded string)
 * @param divisor    Divisor (as ASCII encoded string)
 * @param allocateFn Callback to allocate memory for temporary values, caller frees memory
 * @param result     Result as Decfloat
 *
 * @return           DECF_OK -- Fine.
 * @return           All other -- Error!
 */
DECF_RETURN DecFloat34StrDiv(
  const SAP_UTF8 * divident,
  const SAP_UTF8 * divisor,
  Decfl34AllocateCallBack allocateFn,
  DecFloat34 * result);

END_externC
#endif /* DECFARITHM_H */
