/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
(c) Copyright, Real-Time Innovations, 2018-2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
============================================================================= */

#ifndef xcdr_infrastructure_psm_h
#define xcdr_infrastructure_psm_h


#include "osapi/osapi_type.h"


#ifdef __cplusplus
    extern "C" {
#endif


/* ------------------------------------------------------------------------- */
/* ---- Constants and Types ------------------------------------------------ */
/* ------------------------------------------------------------------------- */
typedef char RTIXCdrChar;
typedef RTI_UINT32 RTIXCdrLegacyWchar;
typedef RTI_UINT16 RTIXCdrWchar;
typedef RTI_UINT8 RTIXCdrOctet;
typedef RTI_INT16 RTIXCdrShort;
typedef RTI_UINT16 RTIXCdrUnsignedShort;
typedef RTI_INT32 RTIXCdrLong;
typedef RTI_UINT32 RTIXCdrUnsignedLong;
typedef RTI_INT64 RTIXCdrLongLong;
typedef RTI_UINT64 RTIXCdrUnsignedLongLong;
typedef RTI_FLOAT32 RTIXCdrFloat;
typedef RTI_DOUBLE64 RTIXCdrDouble;
typedef RTI_UINT8 RTIXCdrBoolean;
typedef RTI_UINT8 RTIXCdrExtendedBoolean;
typedef RTI_INT32 RTIXCdrEnum;
typedef RTI_DOUBLE128 RTIXCdrLongDouble;

typedef RTIXCdrOctet RTIXCdr1Byte;
typedef RTIXCdrUnsignedShort RTIXCdr2Byte;
typedef RTIXCdrUnsignedLong RTIXCdr4Byte;
typedef RTIXCdrUnsignedLongLong RTIXCdr8Byte;
typedef RTIXCdrLongDouble RTIXCdr16Byte;

#define RTI_XCDR_ONE_BYTE_SIZE 1
#define RTI_XCDR_TWO_BYTE_SIZE 2
#define RTI_XCDR_FOUR_BYTE_SIZE 4
#define RTI_XCDR_EIGHT_BYTE_SIZE 8
#define RTI_XCDR_SIXTEEN_BYTE_SIZE 16


#ifdef __cplusplus
    }   /* extern "C" */
#endif

#endif /* xcdr_infrastructure_psm_h */
