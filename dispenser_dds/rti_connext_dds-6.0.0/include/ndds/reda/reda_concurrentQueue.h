/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)reda_concurrentQueue.h    generated by: makeheader    Thu Feb 28 22:11:32 2019
 *
 *		built from:	concurrentQueue.ifc
 */

#ifndef reda_concurrentQueue_h
#define reda_concurrentQueue_h


  #include <stdio.h> /* for FILE */
  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif
  #ifndef reda_dll_h
    #include "reda/reda_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif


  #define REDA_CONCURRENT_QUEUE_MSG_ALIGN_BYTES (8)


  #define REDA_CONCURRENT_QUEUE_COOKIE_INVALID (0)

struct REDAConcurrentQueueHandle;


#define REDAConcurrentQueueDesc_SIZEOF_64_BIT_POINTER 8

struct REDAConcurrentQueueDesc {
    /*e Maximum number of bytes of all messages in the buffer */
    int _maxDataBytes;
    /*e Maximum number of bytes on a single write/read */
    int _messageSizeMax;
    /*e Maximum number of individual messages the buffer can hold */
    int _messageCountMax;
#if defined(RTI_SOL2) && defined(RTI_ENDIAN_BIG) /* SparcSol */
    /* In Sparc Solaris we cannot use a pointer because
     * the ConcurentQueue header containing a reference
     * to this structure may be aligned to 4 bytes.
     */ 
    char _memAddress[REDAConcurrentQueueDesc_SIZEOF_64_BIT_POINTER];
#else
    /*e The memory address passed to the create or attach call */
    const char *_memAddress;
#endif
};

struct REDAConcurrentQueueStateInfo {
    /*e Total number of bytes ever written to the queue since it was
        created */
    unsigned int _bytesWrittenCounter;   
    /*e Total number of bytes ever read from the queue since it was
       created */
    unsigned int _bytesFullyReadCounter;
    /*e Boolean flag indicating whether the next message in the queue
       is ready to be read. In other words, whether the next call
       to REDAConcurrentQueue_startReadEA will return a message
       */
    RTIBool      _nextToBeReadMsgIsReadyToRead;
    /*e Boolean flag indicating whether the next message in the queue
       is still being written. In other words, whether a writer has
       called REDAConcurrentQueue_startWriteEA but has not yet
       called REDAConcurrentQueue_finishWriteEA
       */
    RTIBool      _nextToBeReadMsgIsBeingWritten;
    /*e Size of the message that will be returned by the next call to
       REDAConcurrentQueue_startReadEA, assuming it is known.
       */
    int          _nextToBeReadMsgSize;
    /*e In the event that _nextToBeeadMsgIsBeingWritten==RTI_TRUE, this
       field contains the value of the finishedHandle that the writer
       writing that message should be used as a parameter to 
       REDAConcurrentQueue_finishWriteEA
       */  
    int          _nextToBeReadMsgWriteFinishHandle;
    /*e In the event that _nextToBeeadMsgIsBeingWritten==RTI_TRUE, this
       field contains the value of the cookie that the writer
       writing that message used in the call to  
       REDAConcurrentQueue_startWriteEA
       */  
    unsigned int _nextToBeReadMsgWriterCookie;
    /*e Boolean flag indicating whether there is one (or more) messages
       in the process of being read.
     */
    RTIBool      _haveMsgBeingRead;    
    /*e In the event that _haveMsgBeingRead==RTI_TRUE this field contains
       the size of the 'first' message that is still being read. "First"
       detemined by the order in which REDAConcurrentQueue_startReadEA was
       called.
       */
    int          _nextBeingReadMsgSize;
    /*e In the event that _haveMsgBeingRead==RTI_TRUE this field contains
       the finishHandle of the 'first' message that is still being read.
       That is the finishHandle that should be passed to the 
       REDAConcurrentQueue_finishReadEA to indicate the message has been
       completely read
       */
    int          _nextBeingReadMsgReadFinishHandle;
    /*e In the event that _haveMsgBeingRead==RTI_TRUE this field contains
       the value of the cookie that the reader
       reading that message used in the call to REDAConcurrentQueue_startReadEA 
       */
    unsigned int _nextBeingReadMsgReaderCookie;
};

extern REDADllExport RTIBool
REDAConcurrentQueue_create(struct REDAConcurrentQueueHandle *q,
			   int messageCountMax, int messageSizeMax,
			   char *memAddress, int memAddressNumBytes);

extern REDADllExport RTIBool
REDAConcurrentQueue_unlink(struct REDAConcurrentQueueHandle *q);

extern REDADllExport RTIBool
REDAConcurrentQueue_attach(struct REDAConcurrentQueueHandle *q, char *memAddress);

extern REDADllExport RTIBool
REDAConcurrentQueue_detach(struct REDAConcurrentQueueHandle *q);

extern REDADllExport
int REDAConcurrentQueue_getSizeRequired(int messageSizeMax,
					int messageCountMax,
					int maxBytesBuffered);

extern REDADllExport
void REDAConcurrentQueue_print(const struct REDAConcurrentQueueHandle *q, 
			       FILE *file);

extern REDADllExport
RTIBool REDAConcurrentQueue_startWriteEA(struct REDAConcurrentQueueHandle *q,
					 int *finishedHandle, char **whereTo,
					 int msgSize, unsigned int cookie);

extern REDADllExport
void REDAConcurrentQueue_finishWrite(struct REDAConcurrentQueueHandle *q,
				     int finishedHandle, int msgSize);

extern REDADllExport
int REDAConcurrentQueue_startReadEA(struct REDAConcurrentQueueHandle *q,
			       int *finishedHandle, char **whereFrom,
                               unsigned int readerCookie);

extern REDADllExport
void REDAConcurrentQueue_finishReadEA(struct REDAConcurrentQueueHandle *q,
				      int finishedHandle);

extern REDADllExport
void REDAConcurrentQueue_getQueueDesc(
    struct REDAConcurrentQueueHandle *q,
    struct REDAConcurrentQueueDesc *descOut);

extern REDADllExport
void REDAConcurrentQueue_getQueueStateInfoReadEA(
    struct REDAConcurrentQueueHandle *q,
    struct REDAConcurrentQueueStateInfo *infoOut);

extern REDADllExport
RTIBool REDAConcurrentQueue_isWriterPotentiallyStuck(
    struct REDAConcurrentQueueHandle *q,
    struct REDAConcurrentQueueStateInfo *previousInfo,
    struct REDAConcurrentQueueStateInfo *currentInfo );

extern REDADllExport
RTIBool REDAConcurrentQueue_isReaderPotentiallyStuck(
    struct REDAConcurrentQueueHandle *q,
    struct REDAConcurrentQueueStateInfo *previousInfo,
    struct REDAConcurrentQueueStateInfo *currentInfo );

extern REDADllExport
void REDAConcurrentQueue_flushReadEA(struct REDAConcurrentQueueHandle *q,
                                     int readCookie); 

#ifdef __cplusplus
    }	/* extern "C" */
#endif

/* pick up hidden performance boosting macros and optimizations */
  #include "reda/reda_concurrentQueue_impl.h"

#endif /* reda_concurrentQueue_h */
