/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_sharedMemory_impl.h    generated by: makeheader    Thu Feb 28 22:11:22 2019
 *
 *		built from:	sharedMemory_impl.ifc
 */

#ifndef osapi_sharedMemory_impl_h
#define osapi_sharedMemory_impl_h



/* Win32 ------------------------------------------------------------------ */
#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
#include <windows.h>
    #define RTIOsapiSharedMemoryNativeHandle_Segment 	HANDLE
    #define RTIOsapiSharedMemoryNativeHandle_SemMutex	HANDLE
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEGMENT  (NULL)
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEMMUTEX (NULL)

/* Posix ------------------------------------------------------------------ */
#elif defined(RTI_QNX) || defined(RTI_LYNXOS_SE)
#include "semaphore.h"
    #define RTIOsapiSharedMemoryNativeHandle_Segment 	int
    #define RTIOsapiSharedMemoryNativeHandle_SemMutex 	sem_t *
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEGMENT  (-1)
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEMMUTEX (SEM_FAILED)

/* Integrity -------------------------------------------------------------- */
#elif defined(RTI_INTY)
#include "INTEGRITY.h"
    #define RTIOsapiSharedMemoryNativeHandle_Segment 	int
    #define RTIOsapiSharedMemoryNativeHandle_SemMutex 	Object
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEGMENT  (-1)
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEMMUTEX ((Object)-1)

/* VxWorks 6.x ------------------------------------------------------------ */
#elif defined(RTI_VXWORKS) && (defined(__RTP__) || defined(_WRS_KERNEL))
#include "vxWorks.h"
    #define RTIOsapiSharedMemoryNativeHandle_Segment 	SD_ID
    #define RTIOsapiSharedMemoryNativeHandle_SemMutex 	SEM_ID
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEGMENT  ((SD_ID)NULL)
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEMMUTEX ((SEM_ID)NULL)

/* System V --------------------------------------------------------------- */
#else
    #define RTIOsapiSharedMemoryNativeHandle_Segment 	int
    #define RTIOsapiSharedMemoryNativeHandle_SemMutex	int
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEGMENT  (-1)
    #define RTI_OSAPI_SHARED_MEMORY_NATIVE_HANDLE_INVALID_SEMMUTEX (-1)

#endif /* defined(RTI_WIN32) || defined(RTI_WINCE) */

#ifdef __cplusplus
    extern "C" {
#endif


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_sharedMemory_impl_h */
