/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_cpu.h    generated by: makeheader    Thu Feb 28 22:11:23 2019
 *
 *		built from:	cpu.ifc
 */

#ifndef osapi_cpu_h
#define osapi_cpu_h


  #ifndef osapi_dll_h
    #include "osapi/osapi_dll.h"
  #endif
  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif



#if defined(RTI_QNX)
  #define RTI_OSAPI_CPU_BITMAP_MAX_BITS   (32)
#else
  #define RTI_OSAPI_CPU_BITMAP_MAX_BITS   (1024)
#endif
#define RTI_OSAPI_CPU_BITMAP_LENGTH     (RTI_OSAPI_CPU_BITMAP_MAX_BITS/32)

#define RTI_OSAPI_CPU_NO_ROTATION  (0)
#define RTI_OSAPI_CPU_RR_ROTATION  (1)

struct RTIOsapiCpuBitmap {
    RTI_UINT32 mask[RTI_OSAPI_CPU_BITMAP_LENGTH];
    int rotation;
    int _numCpus;
    int _numUses;
};


#if defined(RTI_QNX)
  #define RTI_OSAPI_CPU_BITMAP_DEFAULT { \
      {0}, RTI_OSAPI_CPU_NO_ROTATION, 0, 0}
#else
  #define RTI_OSAPI_CPU_BITMAP_DEFAULT { \
      {0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0, \
       0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0}, \
      RTI_OSAPI_CPU_NO_ROTATION, 0, 0}
#endif

#define RTIOsapiCpuBitmap_test(me, i) ((me)->mask[i>>5] & (1<<(i&0x1F)))
#define RTIOsapiCpuBitmap_set(me, i) do { \
    if (((me)->mask[i>>5] & (1<<(i&0x1F))) == 0) (me)->_numCpus++; \
    (me)->mask[i>>5] |= (1<<(i&0x1F)); \
} while (0)

#define RTIOsapiCpuBitmap_zero(me) RTIOsapiMemory_zero((me), sizeof(*(me)))
#define RTIOsapiCpuBitmap_incrementUseCounter(me) ((me)->_numUses++)
#define RTIOsapiCpuBitmap_copy(to, src) RTIOsapiMemory_copy((to), (src), sizeof(*(src)))


extern RTIOsapiDllExport RTIBool RTIOsapiCpuBitmap_equals(
    const struct RTIOsapiCpuBitmap *me, const struct RTIOsapiCpuBitmap *other);

extern RTIOsapiDllExport void 
RTIOsapiCpuBitmap_toStringI(struct RTIOsapiCpuBitmap *me, char *dst, int max);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_cpu_h */