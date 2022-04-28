/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
(c) Copyright, Real-Time Innovations, 2018-2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
============================================================================= */

#ifndef xcdr_infrastructure_psm_impl_h
#define xcdr_infrastructure_psm_impl_h


#include "xcdr/xcdr_dll.h"


#ifdef __cplusplus
    extern "C" {
#endif


/* ------------------------------------------------------------------------- */
/* ---- Macro implementations ---------------------------------------------- */
/* ------------------------------------------------------------------------- */
#define RTIXCdrMemory_copy(dest, src, size) (memcpy((dest), (src), (size_t)(size)))

#define RTIXCdrUtility_pointerToULongLong RTIOsapiUtility_pointerToUInt64

#define RTIXCdrHeap_allocateStruct(structStoragePointer, Type) \
    RTIOsapiHeap_allocateStructure(structStoragePointer, Type)

#define RTIXCdrHeap_freeStruct(structStorage) \
    RTIOsapiHeap_freeStructure(structStorage)

#ifdef __cplusplus
    }   /* extern "C" */
#endif

#endif /* xcdr_infrastructure_psm_impl_h */
