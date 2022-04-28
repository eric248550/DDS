/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_sharedMemorySignalingSemaphore.h    generated by: makeheader    Thu Feb 28 22:11:23 2019
 *
 *		built from:	sharedMemorySignalingSemaphore.ifc
 */

#ifndef osapi_sharedMemorySignalingSemaphore_h
#define osapi_sharedMemorySignalingSemaphore_h


  #ifndef osapi_sharedMemory_h
    #include "osapi/osapi_sharedMemory.h"
  #endif

#include "osapi/osapi_sharedMemorySemMutex_impl.h"

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIOsapiSharedMemorySignalingSemaphoreHandle;

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySignalingSemaphore_create(
		struct RTIOsapiSharedMemorySignalingSemaphoreHandle *handle, 
		int * statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySignalingSemaphore_attach(
		struct RTIOsapiSharedMemorySignalingSemaphoreHandle *handle, 
		int *statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySignalingSemaphore_createOrAttach(
		struct RTIOsapiSharedMemorySignalingSemaphoreHandle *handle, 
		int * statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySignalingSemaphore_signal(
		struct RTIOsapiSharedMemorySignalingSemaphoreHandle *handle, 
		int* statusOut);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySignalingSemaphore_wait(
    struct RTIOsapiSharedMemorySignalingSemaphoreHandle *handle, int* statusOut);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySignalingSemaphore_detach(
		struct RTIOsapiSharedMemorySignalingSemaphoreHandle *handle);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemorySignalingSemaphore_delete(
		struct RTIOsapiSharedMemorySignalingSemaphoreHandle *handle);



#define RTIOsapiSharedMemorySignalingSemaphoreHandle	\
		RTIOsapiSharedMemorySemMutexHandle

#define RTIOsapiSharedMemorySignalingSemaphore_create(h, s, k) \
	RTIOsapiSharedMemorySemMutex_create(h, s, k, SEMMUTEX_TYPE_BINARYSEM)

#define RTIOsapiSharedMemorySignalingSemaphore_attach(h, s, k) \
	RTIOsapiSharedMemorySemMutex_attach(h, s, k, SEMMUTEX_TYPE_BINARYSEM)

#define RTIOsapiSharedMemorySignalingSemaphore_createOrAttach(h, s, k) \
	RTIOsapiSharedMemorySemMutex_createOrAttach(h, s, k, SEMMUTEX_TYPE_BINARYSEM)

#define RTIOsapiSharedMemorySignalingSemaphore_signal(h, s) \
	RTIOsapiSharedMemorySemMutex_give(h, s, SEMMUTEX_TYPE_BINARYSEM)

#define RTIOsapiSharedMemorySignalingSemaphore_wait(h, s) \
	RTIOsapiSharedMemorySemMutex_take(h, s, SEMMUTEX_TYPE_BINARYSEM)

#define RTIOsapiSharedMemorySignalingSemaphore_detach(h) \
	RTIOsapiSharedMemorySemMutex_detach(h, SEMMUTEX_TYPE_BINARYSEM)

#define RTIOsapiSharedMemorySignalingSemaphore_delete(h) \
	RTIOsapiSharedMemorySemMutex_delete(h, SEMMUTEX_TYPE_BINARYSEM)



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_sharedMemorySignalingSemaphore_h */
