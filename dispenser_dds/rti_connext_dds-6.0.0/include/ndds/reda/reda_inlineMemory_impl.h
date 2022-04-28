/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)reda_inlineMemory_impl.h    generated by: makeheader    Thu Feb 28 22:11:32 2019
 *
 *		built from:	inlineMemory_impl.ifc
 */

#ifndef reda_inlineMemory_impl_h
#define reda_inlineMemory_impl_h


#ifdef __cplusplus
    extern "C" {
#endif

extern REDADllExport
REDAInlineMemoryBuffer * REDAInlineMemory_reserveBufferI(
        struct REDAInlineMemory ** selfPt, 
        REDAInlineMemorySize bufferSize,
        RTIBool allowManagerRelocation);


#define  REDAInlineMemory_reserveBuffer(selfPt, bufferSize) \
    REDAInlineMemory_reserveBufferI(selfPt, bufferSize, RTI_TRUE)


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* reda_inlineMemory_impl_h */
