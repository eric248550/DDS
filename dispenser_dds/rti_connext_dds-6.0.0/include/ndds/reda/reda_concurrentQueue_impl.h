/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)reda_concurrentQueue_impl.h    generated by: makeheader    Thu Feb 28 22:11:31 2019
 *
 *		built from:	concurrentQueue_impl.ifc
 */

#ifndef reda_concurrentQueue_impl_h
#define reda_concurrentQueue_impl_h


  #include <stddef.h>
  #ifndef reda_memory_h
/*    #include "reda/reda_memory.h"*/
  #endif

#ifdef __cplusplus
    extern "C" {
#endif


struct REDAConcurrentQueueMsgInfo {
    int          _size;
    unsigned int _cookie;
};

struct REDAConcurrentQueueHandle {
    /* Copy of the Parameters used to configure the queue
     * when it was created. Should be considered constant and read-only
     */
    struct REDAConcurrentQueueDesc _desc;

    /* If a byte swap is required since writing to a different endian 
     * representation. 
     */
    int _adjustForEndianness;
    
    /* Points to the shared state of the queue */
    struct REDAConcurrentQueueState *_state;

    /* Points to a backup of the state. Uset to restore the state if
     a process crashes while modifying the state
    */
    struct REDAConcurrentQueueState *_backup;

    struct REDAConcurrentQueueMsgInfo *_msgInfos; 
                    /* Together with the bufferReadIndex defines the array
		       of messages. Must be able to hold messageCountMax+1
		       elements. */

    char *_buffer; /* The buffer containing the messages.
		      Contains space for bufferSize bytes
                      Note that always: bufferSize > (maxDataBytes + messageSizeMax)
		      in fact currently we set
                            bufferSize =  
                                   (maxDataBytes + messageSizeMax)
                                    + (REDA_CONCURRENT_QUEUE_ALIGN_BYTES -1)*messageSizeMax */
    unsigned int _bufferSize; /* The number of bytes available for using 
                                  starting at buffer */ 
};


#define swap4ByteUIntArg(x) ( ((x)<<24) | (((x)&0xff00)<<8) | (((x)&0xff0000)>>8) | ((x)>>24) )
#define swap4Bytes(x) swap4ByteUIntArg( ((unsigned int)(x)) )


#define REDAConcurrentQueue_finishWrite(q, finishedHandle, msgSize) \
    (q)->_msgInfos[finishedHandle]._size = \
             ((q)->_adjustForEndianness?swap4Bytes(msgSize):msgSize); \
    (q)->_msgInfos[finishedHandle]._cookie = \
             REDA_CONCURRENT_QUEUE_COOKIE_INVALID

#define REDAConcurrentQueue_getQueueDesc(q, descOut) *(descOut) = (q)->_desc


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* reda_concurrentQueue_impl_h */
