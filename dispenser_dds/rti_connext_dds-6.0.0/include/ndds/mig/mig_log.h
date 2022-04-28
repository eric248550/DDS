/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)mig_log.h    generated by: makeheader    Thu Feb 28 22:12:15 2019
 *
 *		built from:	log.ifc
 */

#ifndef mig_log_h
#define mig_log_h


  #ifndef log_common_h
    #include "log/log_common.h"
  #endif
  #ifndef mig_dll_h
    #include "mig/mig_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif


  #define SUBMODULE_MIG_RTPS             (0x1000)
  #define SUBMODULE_MIG_INTERPRETER      (0x2000)
  #define SUBMODULE_MIG_GENERATOR        (0x3000)


  #define MIG_SUBMODULE_MASK_RTPS             (0x0001)


  #define MIG_SUBMODULE_MASK_INTERPRETER      (0x0002)


  #define MIG_SUBMODULE_MASK_GENERATOR        (0x0004)


  #define MIG_SUBMODULE_MASK_ALL              (0xffff)

extern MIGDllExport
void MIGLog_setVerbosity(RTILogBitmap submoduleMask, int verbosity);

extern MIGDllExport
void MIGLog_setBitmaps(RTILogBitmap submoduleMask,
		       RTILogBitmap instrumentationMask);

extern MIGDllExport
void MIGLog_getBitmaps(RTILogBitmap *submoduleMask,
		       RTILogBitmap *instrumentationMask);

extern MIGDllVariable const struct RTILogMessage MIG_LOG_INTERPRETER_ADD_FAILURE_XXXX;

extern MIGDllVariable const struct RTILogMessage MIG_LOG_ADD_FAILURE_s;

extern MIGDllVariable const struct RTILogMessage MIG_LOG_INTERPRETER_BAD_ALIGNMENT_d;


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* mig_log_h */
