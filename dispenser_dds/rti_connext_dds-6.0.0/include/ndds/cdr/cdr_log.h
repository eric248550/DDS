/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)cdr_log.h    generated by: makeheader    Thu Feb 28 22:11:48 2019
 *
 *		built from:	log.ifc
 */

#ifndef cdr_log_h
#define cdr_log_h


  #ifndef cdr_dll_h
    #include "cdr/cdr_dll.h"
  #endif
  #ifndef log_common_h
    #include "log/log_common.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif


/*e \ingroup RTICdrLog
  Submodule ID for error code */
  #define SUBMODULE_CDR_STREAM                  (0x0000)
  #define SUBMODULE_CDR_TYPE_CODE               (0x0001)
  #define SUBMODULE_CDR_TYPE_OBJECT             (0x0002)


/*e \ingroup RTICdrLog
  Stream submodule mask for logging.
*/
  #define RTI_CDR_SUBMODULE_MASK_STREAM         (0x0001)
/*e \ingroup RTICdrLog
  Type code submodule mask for logging.
*/
  #define RTI_CDR_SUBMODULE_MASK_TYPE_CODE      (0x0002)  

/*e \ingroup RTICdrLog
  TypeObject submodule mask for logging.
*/
  #define RTI_CDR_SUBMODULE_MASK_TYPE_OBJECT      (0x0004)  

/*e \ingroup RTICdrLog
  Mask for turning on logging for all submodules.
*/
  #define RTI_CDR_SUBMODULE_MASK_ALL            (0xFFFF)

extern RTICdrDllVariable RTILogBitmap RTICdrLog_g_submoduleMask;

extern RTICdrDllVariable RTILogBitmap RTICdrLog_g_instrumentationMask;

extern RTICdrDllExport
void RTICdrLog_setVerbosity(RTILogBitmap submoduleMask, int verbosity);

extern RTICdrDllExport void
RTICdrLog_setBitmaps(RTILogBitmap submoduleMask,
		     RTILogBitmap instrumentationMask);

extern RTICdrDllExport void RTICdrLog_getBitmaps(
    RTILogBitmap *submoduleMask, RTILogBitmap *instrumentationMask);

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_SERIALIZE_FAILURE_s;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_DESERIALIZE_FAILURE_s;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_SKIP_FAILURE_s;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_INVALID_ENCAPSULATION_ID_d;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_EXCEED_SEQ_MAX_LENGTH_dd;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_SERIALIZE_INVALID_ENUMERATOR_ds;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_DESERIALIZE_INVALID_ENUMERATOR_ds;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_UNASSIGNABLE_SAMPLE_OF_TYPE_s;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_XTYPES_DESERIALIZE_UNKNOWN_ENUM_ORDINAL_sssdd;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_XTYPES_DESERIALIZE_UNKNOWN_UNION_DISCRIMINATOR_s;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_XTYPES_DESERIALIZE_UNKNOWN_UNION_DISCRIMINATOR_sss;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_NOT_ASSIGNABLE_sss;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_NOT_ASSIGNABLE_ss;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_MEMBER_NOT_ASSIGNABLE_ssd;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_COLLECTION_BOUNDS_NOT_ASSIGNABLE_dd;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_UNION_LABEL_NOT_ASSIGNABLE_dss;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_NOT_ASSIGNABLE_s;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_ERROR_ds;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_NOT_EQUIVALENT_ss;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_NOT_EQUAL_ss;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_MEMBER_NOT_EQUAL_ssd;

extern RTICdrDllVariable const struct RTILogMessage RTI_CDR_LOG_TYPE_OBJECT_NOT_EQUAL_s;


#define RTICdrLog_exception \
    if ((RTILog_setLogLevel != NULL) \
        && (RTICdrLog_g_instrumentationMask & RTI_LOG_BIT_EXCEPTION) \
        && (RTICdrLog_g_submoduleMask & RTI_CDR_CURRENT_SUBMODULE)){ \
            RTILog_setLogLevel(RTI_LOG_BIT_EXCEPTION); \
    } \
    if ((RTICdrLog_g_instrumentationMask & RTI_LOG_BIT_EXCEPTION) \
        && (RTICdrLog_g_submoduleMask & RTI_CDR_CURRENT_SUBMODULE)) \
            RTILog_printContextAndMsg

#define RTICdrLog_warn \
    if ((RTILog_setLogLevel != NULL) \
        && (RTICdrLog_g_instrumentationMask & RTI_LOG_BIT_WARN) \
        && (RTICdrLog_g_submoduleMask & RTI_CDR_CURRENT_SUBMODULE)){ \
            RTILog_setLogLevel(RTI_LOG_BIT_WARN); \
    } \
    if ((RTICdrLog_g_instrumentationMask & RTI_LOG_BIT_WARN) \
        && (RTICdrLog_g_submoduleMask & RTI_CDR_CURRENT_SUBMODULE)) \
            RTILog_printContextAndMsg


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* cdr_log_h */
