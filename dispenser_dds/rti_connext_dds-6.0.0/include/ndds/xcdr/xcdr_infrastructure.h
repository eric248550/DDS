/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
(c) Copyright, Real-Time Innovations, 2018-2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
============================================================================= */

#ifndef xcdr_infrastructure_h
#define xcdr_infrastructure_h

#include <stdio.h>
#include "xcdr/xcdr_dll.h"

/******************************************************************************
 * Including infrastructure_psm must be the done before any other declaration.
 ******************************************************************************/
#include "xcdr/xcdr_infrastructure_psm.h"


#ifdef __cplusplus
    extern "C" {
#endif


/* ------------------------------------------------------------------------- */
/* ---- Constants and Types ------------------------------------------------ */
/* ------------------------------------------------------------------------- */
#define RTI_XCDR_ONE_BYTE_SIZE 1
#define RTI_XCDR_TWO_BYTE_SIZE 2
#define RTI_XCDR_FOUR_BYTE_SIZE 4
#define RTI_XCDR_EIGHT_BYTE_SIZE 8
#define RTI_XCDR_SIXTEEN_BYTE_SIZE 16

#define RTI_XCDR_CHAR_SIZE RTI_XCDR_ONE_BYTE_SIZE
#define RTI_XCDR_OCTET_SIZE RTI_XCDR_ONE_BYTE_SIZE
#define RTI_XCDR_LEGACY_WCHAR_SIZE RTI_XCDR_FOUR_BYTE_SIZE
#define RTI_XCDR_WCHAR_SIZE RTI_XCDR_TWO_BYTE_SIZE
#define RTI_XCDR_SHORT_SIZE RTI_XCDR_TWO_BYTE_SIZE
#define RTI_XCDR_UNSIGNED_SHORT_SIZE RTI_XCDR_TWO_BYTE_SIZE
#define RTI_XCDR_LONG_SIZE RTI_XCDR_FOUR_BYTE_SIZE
#define RTI_XCDR_UNSIGNED_LONG_SIZE RTI_XCDR_FOUR_BYTE_SIZE
#define RTI_XCDR_LONG_LONG_SIZE RTI_XCDR_EIGHT_BYTE_SIZE
#define RTI_XCDR_UNSIGNED_LONG_LONG_SIZE RTI_XCDR_EIGHT_BYTE_SIZE
#define RTI_XCDR_FLOAT_SIZE RTI_XCDR_FOUR_BYTE_SIZE
#define RTI_XCDR_DOUBLE_SIZE RTI_XCDR_EIGHT_BYTE_SIZE
#define RTI_XCDR_LONG_DOUBLE_SIZE RTI_XCDR_SIXTEEN_BYTE_SIZE
#define RTI_XCDR_BOOLEAN_SIZE RTI_XCDR_ONE_BYTE_SIZE
#define RTI_XCDR_ENUM_SIZE RTI_XCDR_FOUR_BYTE_SIZE

#define RTI_XCDR_TRUE ((RTIXCdrBoolean)1)
#define RTI_XCDR_FALSE ((RTIXCdrBoolean)0)
#define RTI_XCDR_MAYBE ((RTIXCdrBoolean)2)

#define RTIXCdrChar_MAX 127
#define RTIXCdrChar_MIN (-RTIXCdrChar_MIN-1)

#define RTIXCdrOctet_MAX 255
#define RTIXCdrOctet_MIN 0

#define RTIXCdrShort_MAX 32767
#define RTIXCdrShort_MIN (-RTIXCdrShort_MAX-1)

#define RTIXCdrUnsignedShort_MAX 65535
#define RTIXCdrUnsignedShort_MIN 0

#define RTIXCdrWchar_MAX RTIXCdrUnsignedShort_MAX
#define RTIXCdrWchar_MIN RTIXCdrUnsignedShort_MIN

/* This is not defined as -2147483648 because that value is processed in
   two stages. From https://msdn.microsoft.com/en-us/library/4kh09110.aspx
   1. The number 2147483648 is evaluated. Because it is greater than the                                                                                         .
      maximum integer value of 2147483647, the type of 2147483648 is not int,                                                                                    .
      but unsigned int                                                                                                                                           .
   2. Unary minus is applied to the value, with an unsigned result, which also                                                                                                                                                                                        .
      happens to be 2147483648.                                                                                                                                                              .
*/
#define RTIXCdrLong_MAX 2147483647
#define RTIXCdrLong_MIN (-RTIXCdrLong_MAX - 1)

#define RTIXCdrUnsignedLong_MAX 4294967295U
#define RTIXCdrUnsignedLong_MIN 0

#define RTIXCdrLongLong_MAX 9223372036854775807LL
#define RTIXCdrLongLong_MIN (-RTIXCdrLongLong_MAX - 1LL)

#define RTIXCdrUnsignedLongLong_MAX 18446744073709551615ULL
#define RTIXCdrUnsignedLongLong_MIN 0ULL

#define RTIXCdrFloat_MAX 3.4E38F
#define RTIXCdrFloat_MIN (-RTIXCdrFloat_MAX)

#define RTIXCdrDouble_MAX +1.7E+308
#define RTIXCdrDouble_MIN (-RTIXCdrDouble_MAX)

typedef RTIXCdrLong RTIXCdrAlignment;


struct RTIXCdrInlineListNode {
    struct RTIXCdrInlineListNode *next;
    struct RTIXCdrInlineListNode *prev;
};


/* ------------------------------------------------------------------------- */
/* ---- Function declarations ---------------------------------------------- */
/* ------------------------------------------------------------------------- */

extern RTIXCdrDllExport
void * RTIXCdrHeap_allocate(RTIXCdrUnsignedLong size);

extern RTIXCdrDllExport
void RTIXCdrHeap_free(void *ptr);

#define TYPE RTIXCdrUnsignedLong

extern RTIXCdrDllExport
void RTIXCdrHeap_allocateStruct(
        TYPE **structStoragePointer,
        TYPE);

extern RTIXCdrDllExport
void RTIXCdrHeap_freeStruct(
        TYPE *structStorage);

#undef TYPE

extern RTIXCdrDllExport
RTIXCdrUnsignedLong RTIXCdrWString_getLength(const RTIXCdrWchar * str);

extern RTIXCdrDllExport
void RTIXCdrMemory_copy(void *dest, const void *src, RTIXCdrUnsignedLong size);

extern RTIXCdrDllExport
RTIXCdrUnsignedLong RTIXCdrAlignment_alignSizeUp(
        RTIXCdrUnsignedLong size,
        RTIXCdrAlignment alignment);

extern RTIXCdrDllExport
RTIXCdrUnsignedLongLong RTIXCdrUtility_pointerToULongLong(
        const void *pointer);

#ifdef __cplusplus
    }
#endif


/******************************************************************************
 * Including infrastructure_impl must be the last thing we do in this file.
 ******************************************************************************/
#include "xcdr/xcdr_infrastructure_impl.h"

#endif /* xcdr_infrastructure_h */
