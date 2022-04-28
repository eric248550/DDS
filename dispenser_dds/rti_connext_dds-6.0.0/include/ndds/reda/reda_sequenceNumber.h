/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)reda_sequenceNumber.h    generated by: makeheader    Thu Feb 28 22:11:32 2019
 *
 *		built from:	sequenceNumber.ifc
 */

#ifndef reda_sequenceNumber_h
#define reda_sequenceNumber_h


  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif
  #ifndef osapi_ntptime_h
    #include "osapi/osapi_ntptime.h"
  #endif
  #ifndef reda_dll_h
    #include "reda/reda_dll.h"
  #endif
  #ifndef reda_fastBuffer_h
    #include "reda/reda_fastBuffer.h"
  #endif
  #ifndef reda_inlineList_h
    #include "reda/reda_inlineList.h"
  #endif
  #ifndef reda_skiplist_h
    #include "reda/reda_skiplist.h"
  #endif
  #ifndef reda_buffer_h
    #include "reda/reda_buffer.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct REDABuffer; /* forward declare to appease compiler */

struct REDASequenceNumber {
    /*e The most significant part of the sequence number */
    RTI_INT32 high;
    /*e The least significant part of the sequence number */
    RTI_UINT32 low;
};


  #define REDA_SEQUENCE_NUMBER_HIGH_MAX ((RTI_INT32)0x7fffffff)


  #define REDA_SEQUENCE_NUMBER_LOW_MAX ((RTI_UINT32)0xffffffff)


  #define REDA_SEQUENCE_NUMBER_MAX {REDA_SEQUENCE_NUMBER_HIGH_MAX, \
                                    REDA_SEQUENCE_NUMBER_LOW_MAX}


  #define REDA_SEQUENCE_NUMBER_ZERO {0, 0}


  #define REDA_SEQUENCE_NUMBER_HIGH_UNKNOWN ((RTI_INT32)0xffffffff)


  #define REDA_SEQUENCE_NUMBER_HIGH_AUTO ((RTI_INT32)0xffffffff)


  #define REDA_SEQUENCE_NUMBER_LOW_UNKNOWN ((RTI_UINT32)0xffffffff)


  #define REDA_SEQUENCE_NUMBER_LOW_AUTO ((RTI_UINT32)0xffffffff)


  #define REDA_SEQUENCE_NUMBER_UNKNOWN \
    {REDA_SEQUENCE_NUMBER_HIGH_UNKNOWN, REDA_SEQUENCE_NUMBER_LOW_UNKNOWN}


  #define REDA_SEQUENCE_NUMBER_AUTO {REDA_SEQUENCE_NUMBER_HIGH_AUTO, \
                                     REDA_SEQUENCE_NUMBER_LOW_AUTO}

extern REDADllExport
void REDASequenceNumber_print(const void *data, const char *desc, int indent);

extern REDADllExport
void REDASequenceNumber_setZero(struct REDASequenceNumber *me);

extern REDADllExport
RTIBool REDASequenceNumber_isZero(const struct REDASequenceNumber *me);

extern REDADllExport
void REDASequenceNumber_setUnknown(struct REDASequenceNumber *me);

extern REDADllExport
RTIBool REDASequenceNumber_isUnknown(const struct REDASequenceNumber *me);

extern REDADllExport
RTIBool REDASequenceNumber_isAuto(const struct REDASequenceNumber *me);

extern REDADllExport
RTIBool REDASequenceNumber_isMaximum(const struct REDASequenceNumber *me);

extern REDADllExport 
void REDASequenceNumber_setMaximum(struct REDASequenceNumber *me);

extern REDADllExport 
int REDASequenceNumber_compare(const struct REDASequenceNumber *me,
			       const struct REDASequenceNumber *sn);

extern REDADllExport 
void REDASequenceNumber_add(struct REDASequenceNumber *answer,
			    const struct REDASequenceNumber *sn1,
			    const struct REDASequenceNumber *sn2);

extern REDADllExport 
void REDASequenceNumber_subtract(struct REDASequenceNumber *answer,
				 const struct REDASequenceNumber *sn1,
				 const struct REDASequenceNumber *sn2);

extern REDADllExport 
void REDASequenceNumber_plusplus(struct REDASequenceNumber *me);

extern REDADllExport
void REDASequenceNumber_minusminus(struct REDASequenceNumber *me);

extern REDADllExport void
REDASequenceNumber_increment(struct REDASequenceNumber *me,
			     const struct REDASequenceNumber *sn);

extern REDADllExport void
REDASequenceNumber_decrement(struct REDASequenceNumber *me,
			     const struct REDASequenceNumber *sn);

extern REDADllExport void REDASequenceNumber_max(
    struct REDASequenceNumber *answer,
    const struct REDASequenceNumber *sn1,
    const struct REDASequenceNumber *sn2);

extern REDADllExport void REDASequenceNumber_min(
    struct REDASequenceNumber *answer,
    const struct REDASequenceNumber *sn1,
    const struct REDASequenceNumber *sn2);

extern REDADllExport double REDASequenceNumber_toDouble(
    struct REDASequenceNumber *sn);

struct REDASequenceNumberInterval {
    struct REDAInlineListNode _node;

    const struct REDASkiplistNode * _skiplistNode;

    struct REDASequenceNumber firstSn;
    struct REDASequenceNumber lastSn;

    struct REDABuffer userData;
    RTIBool validUserData;
    struct RTINtpTime userDataExpirationTime;
};

typedef int REDASequenceNumberIntervalListAssertMode;


#define REDA_SEQUENCE_NUMBER_INTERVAL_LIST_EXPLICIT_ASSERT (0)


#define REDA_SEQUENCE_NUMBER_INTERVAL_LIST_ORDERED_ASSERT (1)


#define REDA_SEQUENCE_NUMBER_INTERVAL_LIST_MAGIC_NUMBER 0x7344L


struct REDASequenceNumberIntervalList {
    struct REDASkiplist list;
    int _list_init;

    struct REDAInlineList _expirationList;

    struct REDAFastBufferPool *intervalPool;
    struct REDAFastBufferPool *userDataPool;
    const struct REDASkiplistNode *iterNode;
    REDASequenceNumberIntervalListAssertMode _assertMode;
};

extern REDADllExport 
struct REDASequenceNumberIntervalList *
REDASequenceNumberIntervalList_new(
    const struct REDASkiplistDescription *listDes,
    struct REDAFastBufferPool *intervalPool,
    struct REDAFastBufferPool *userDataPool,
    REDASequenceNumberIntervalListAssertMode assertMode);

extern REDADllExport 
void
REDASequenceNumberIntervalList_delete(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_initialize(
    struct REDASequenceNumberIntervalList * self,
    const struct REDASkiplistDescription *listDes,
    struct REDAFastBufferPool *intervalPool,
    struct REDAFastBufferPool *userDataPool,
    REDASequenceNumberIntervalListAssertMode assertMode);

extern REDADllExport
void REDASequenceNumberIntervalList_finalize(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport RTIBool
REDASequenceNumberIntervalList_containsSequenceNumber(
    struct REDASequenceNumberIntervalList *self,
    const struct REDASequenceNumber *sn);

extern REDADllExport struct REDASequenceNumberInterval *  
REDASequenceNumberIntervalList_assertExplicitSequenceNumberWithUserData(
    struct REDASequenceNumberIntervalList *self,
    RTIBool * alreadyExists, 
    const struct REDASequenceNumber *sn,
    const struct REDABuffer * userData,
    const struct RTINtpTime * userDataExpirationTime);

extern REDADllExport struct REDASequenceNumberInterval *  
REDASequenceNumberIntervalList_assertOrderedSequenceNumberWithUserData(
    struct REDASequenceNumberIntervalList *self,
    RTIBool * alreadyExists, 
    const struct REDASequenceNumber *sn,
    const struct REDABuffer * userData,
    const struct RTINtpTime * userDataExpirationTime);



#define REDASequenceNumberIntervalList_assertSequenceNumber(self,sn) \
    REDASequenceNumberIntervalList_assertSequenceNumberWithUserData( \
        self,NULL,sn,NULL,NULL)


#define REDASequenceNumberIntervalList_assertSequenceNumberWithUserDataMacro(    \
            self,alreadyExists,sn,data,expiration)                               \
    ((self)->_assertMode == REDA_SEQUENCE_NUMBER_INTERVAL_LIST_EXPLICIT_ASSERT ? \
        REDASequenceNumberIntervalList_assertExplicitSequenceNumberWithUserData( \
            self,alreadyExists,sn,data,expiration) :                             \
        REDASequenceNumberIntervalList_assertOrderedSequenceNumberWithUserData(  \
            self,alreadyExists,sn,data,expiration))

#ifndef RTI_PRECONDITION_TEST
  #define REDASequenceNumberIntervalList_assertSequenceNumberWithUserData \
    REDASequenceNumberIntervalList_assertSequenceNumberWithUserDataMacro
#else 

extern REDADllExport struct REDASequenceNumberInterval *
REDASequenceNumberIntervalList_assertSequenceNumberWithUserData(
    struct REDASequenceNumberIntervalList *self,
    RTIBool * alreadyExists,
    const struct REDASequenceNumber *sn,
    const struct REDABuffer * userData,
    const struct RTINtpTime * userDataExpirationTime);


#endif


extern REDADllExport
RTIBool REDASequenceNumberIntervalList_assertInterval(
    struct REDASequenceNumberIntervalList *self,
    RTIBool * modified, 
    const struct REDASequenceNumber * firstSn,
    const struct REDASequenceNumber * lastSn,
    const struct REDABuffer * userData,
    const struct RTINtpTime * userDataExpirationTime);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_mergeWithUserData(
    struct REDASequenceNumberIntervalList * self,
    RTIBool * modified, 
    const struct REDASequenceNumberIntervalList * srcLst,
    const struct REDABuffer * userData,
    const struct RTINtpTime * userDataExpirationTime);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_merge(
    struct REDASequenceNumberIntervalList * self,
    RTIBool * modified, 
    const struct REDASequenceNumberIntervalList * srcLst);

extern REDADllExport 
int
REDASequenceNumberIntervalList_getIntervalCount(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport 
RTI_UINT64
REDASequenceNumberIntervalList_getSampleCount(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport 
RTI_UINT64
REDASequenceNumberInterval_getSampleCount(
    struct REDASequenceNumberInterval *self);

extern REDADllExport 
const struct REDASequenceNumberInterval *
REDASequenceNumberIntervalList_getFirstInterval(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport
const struct REDASequenceNumberInterval *
REDASequenceNumberIntervalList_getLastInterval(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport 
const struct REDASequenceNumberInterval *
REDASequenceNumberIntervalList_getNextInterval(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport
void REDASequenceNumberIntervalList_invalidateExpiredUserData(
    struct REDASequenceNumberIntervalList *self,
    const struct RTINtpTime * now);

extern REDADllExport
void REDASequenceNumberIntervalList_clear(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport
void REDASequenceNumberIntervalList_findHighestContiguousNumber(
    const struct REDASequenceNumberIntervalList * self,
    struct REDASequenceNumber * result);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_toBuffer(
    const struct REDASequenceNumberIntervalList * self,
    struct REDABuffer * buffer, int maxLength, RTIBool compact,
    RTIBool ignoreError);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_fromBuffer(
    struct REDASequenceNumberIntervalList * self,
    const struct REDABuffer * buffer);

extern REDADllExport
void REDASequenceNumberIntervalList_print(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_isInitialized(
    struct REDASequenceNumberIntervalList *self);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_intersect(
    struct REDASequenceNumberIntervalList * out,
    const struct REDASequenceNumberIntervalList * il1,
    const struct REDASequenceNumberIntervalList * il2);

/*e \ingroup REDASequenceNumberClass
 
  Returns the substraction of two interval lists
 */
extern REDADllExport
RTIBool REDASequenceNumberIntervalList_substract(
    struct REDASequenceNumberIntervalList * out,
    const struct REDASequenceNumberIntervalList * il1,
    const struct REDASequenceNumberIntervalList * il2);

extern REDADllExport
RTIBool REDASequenceNumberIntervalList_deleteSequenceNumber(
    struct REDASequenceNumberIntervalList * self,
    const struct REDASequenceNumber * sn);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

/* pick up hidden performance boosting macros and optimizations */
  #include "reda/reda_sequenceNumber_impl.h"

#endif /* reda_sequenceNumber_h */
