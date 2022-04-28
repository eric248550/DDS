/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_sharedMemoryMutex.h    generated by: makeheader    Thu Feb 28 22:11:23 2019
 *
 *		built from:	sharedMemoryMutex.ifc
 */

#ifndef osapi_sharedMemoryMutex_h
#define osapi_sharedMemoryMutex_h


  #ifndef osapi_sharedMemory_h
    #include "osapi/osapi_sharedMemory.h"
  #endif

#include "osapi/osapi_sharedMemorySemMutex_impl.h"

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIOsapiSharedMemoryMutexHandle;

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemoryMutex_create(
		struct RTIOsapiSharedMemoryMutexHandle *handle, 
		int * statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemoryMutex_attach(
		struct RTIOsapiSharedMemoryMutexHandle *handle, 
		int *statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemoryMutex_createOrAttach(
		struct RTIOsapiSharedMemoryMutexHandle *handle, 
		int * statusOut,
		int key);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemoryMutex_unlock(
		struct RTIOsapiSharedMemoryMutexHandle *handle, 
		int* statusOut);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemoryMutex_lock(
		struct RTIOsapiSharedMemoryMutexHandle *handle,
		int* statusOut);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemoryMutex_detach(
		struct RTIOsapiSharedMemoryMutexHandle *handle);

extern RTIOsapiDllExport
RTIBool RTIOsapiSharedMemoryMutex_delete(
		struct RTIOsapiSharedMemoryMutexHandle *handle);



#define RTIOsapiSharedMemoryMutexHandle	\
		RTIOsapiSharedMemorySemMutexHandle

#define RTIOsapiSharedMemoryMutex_create(h, s, k) \
	RTIOsapiSharedMemorySemMutex_create(h, s, k, SEMMUTEX_TYPE_MUTEX)

#define RTIOsapiSharedMemoryMutex_attach(h, s, k) \
	RTIOsapiSharedMemorySemMutex_attach(h, s, k, SEMMUTEX_TYPE_MUTEX)

#define RTIOsapiSharedMemoryMutex_createOrAttach(h, s, k) \
	RTIOsapiSharedMemorySemMutex_createOrAttach(h, s, k, SEMMUTEX_TYPE_MUTEX)

#define RTIOsapiSharedMemoryMutex_unlock(h, s) \
	RTIOsapiSharedMemorySemMutex_give(h, s, SEMMUTEX_TYPE_MUTEX)

#define RTIOsapiSharedMemoryMutex_lock(h, s) \
	RTIOsapiSharedMemorySemMutex_take(h, s, SEMMUTEX_TYPE_MUTEX)

#define RTIOsapiSharedMemoryMutex_detach(h) \
	RTIOsapiSharedMemorySemMutex_detach(h, SEMMUTEX_TYPE_MUTEX)

#define RTIOsapiSharedMemoryMutex_delete(h) \
	RTIOsapiSharedMemorySemMutex_delete(h, SEMMUTEX_TYPE_MUTEX)



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_sharedMemoryMutex_h */
