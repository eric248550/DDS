/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)reda_hash.h    generated by: makeheader    Thu Feb 28 22:11:32 2019
 *
 *		built from:	hash.ifc
 */

#ifndef reda_hash_h
#define reda_hash_h


  #ifndef reda_dll_h
    #include "reda/reda_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

typedef int (*REDAHashFunction)(const void *key,
                                        int numberOfBuckets);

struct REDAHashDefinition {
    /*e Hash function. Must reutrn a int between 0 and the numberOfBuckets-1.
     */
    REDAHashFunction hashFunction;		
    /*e number of buckets. Must be larger or equal to 1. */
    int numberOfBuckets;
};

extern REDADllExport
int REDAHash_hashSimpleInt(const void *key, int numBuckets);

extern REDADllExport
int REDAHash_hashSimpleDoubleInt(const void *key, int numBuckets);

extern REDADllExport
int REDAHash_hashSimpleTripleInt(const void *key, int numBuckets);

extern REDADllExport
int REDAHash_hashSimpleQuadInt(const void *key, int numBuckets);

extern REDADllExport
int REDAHash_hashSimpleFiveInt(const void *key, int numBuckets);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

/* performance boosting macros and optimizations */
  #include "reda/reda_hash_impl.h"

#endif /* reda_hash_h */
