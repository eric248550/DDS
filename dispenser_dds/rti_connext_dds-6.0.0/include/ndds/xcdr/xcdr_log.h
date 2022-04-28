/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 (c) Copyright, Real-Time Innovations, 2017-2018.
 All rights reserved.
 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.
=========================================================================*/

#ifndef xcdr_log_h
#define xcdr_log_h

/* This file is only used by Connext DDS Pro */
#include "xcdr/xcdr_dll.h"
#include "log/log_common.h"


#ifdef __cplusplus
    extern "C" {
#endif


/* NOTE: When a new submodule is added to CDR, it must be given
   a number and entered here.  Because of the use of this id
   for logging, there are 16 submodule id's: 0x0000, 0x1000,...
   ..., 0xF000.
   It is suggested we put the modules here in an order that
   respects their dependencies: modules with a lower number
   cannot depend on modules with a higher number.
*/
  #define SUBMODULE_XCDR_INFRASTRUCTURE          (0x0000)
  #define SUBMODULE_XCDR_STREAM                  (0x0001)
  #define SUBMODULE_XCDR_INTERPRETER             (0x0002)
  #define SUBMODULE_XCDR_TYPECODE                (0x0004)
  #define SUBMODULE_XCDR_FLAT_DATA               (0x0008)


  #define RTI_XCDR_SUBMODULE_MASK_ALL            (0xFFFF)

extern RTIXCdrDllVariable RTILogBitmap RTIXCdrLog_g_submoduleMask;

extern RTIXCdrDllVariable RTILogBitmap RTIXCdrLog_g_instrumentationMask;

extern RTIXCdrDllExport
void RTIXCdrLog_setVerbosity(RTILogBitmap submoduleMask, int verbosity);

extern RTIXCdrDllExport void RTIXCdrLog_setBitmaps(
        RTILogBitmap submoduleMask,
        RTILogBitmap instrumentationMask);

extern RTIXCdrDllExport void RTIXCdrLog_getBitmaps(
        RTILogBitmap *submoduleMask,
        RTILogBitmap *instrumentationMask);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* xcdr_log_h */
