/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)netio_sender_impl.h    generated by: makeheader    Thu Feb 28 22:12:05 2019
 *
 *		built from:	sender_impl.ifc
 */

#ifndef netio_sender_impl_h
#define netio_sender_impl_h


  #ifndef reda_inlineList_h
    #include "reda/reda_inlineList.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

extern RTINetioDllExport RTIBool RTINetioSender_send(
    struct RTINetioSender *me,
    const struct RTINetioSenderDestinationGroup *group,
    const struct REDAWeakReference *toArray, int toArraySize,
    const struct REDABuffer *buffer, int bufferCount,
    int transportPriority, struct REDAWorker *worker);

extern RTINetioDllExport RTIBool RTINetioSender_queryLeastCommonCapability(
    struct RTINetioSender *me,
    int *messageSizeMaxOut, int *gatherBufferCountMaxOut,
    const struct RTINetioSenderDestinationGroup *group,
    const struct REDAWeakReference *toArray, int toArraySize,
    struct REDAWorker *worker);

struct RTINetioSenderDestinationGroup {
    struct RTINetioSender *_sender;
    struct REDAInlineList _list;
};


/* --------------------------------------------------------------- */
#define RTINetioSenderDestinationGroup_sendFast(me, buffer, bufferCount, \
                                                priority, worker)        \
    RTINetioSender_send(me->_sender, me, NULL, 0, buffer, bufferCount,   \
                        priority, worker)

/* --------------------------------------------------------------- */
#define RTINetioSender_sendFast(me, toArray, toArraySize,       \
                                buffer, bufferCount, priority, worker)    \
    RTINetioSender_send(me, NULL, toArray, toArraySize, buffer, \
			bufferCount, priority, worker)


/* --------------------------------------------------------------- */
#define RTINetioSenderDestinationGroup_queryCapability(                 \
    me, messageSizeMaxOut, gatherBufferCountMaxOut, worker)             \
    RTINetioSender_queryLeastCommonCapability(me->_sender,              \
                            messageSizeMaxOut, gatherBufferCountMaxOut, \
                            me, NULL, 0, worker)

/* --------------------------------------------------------------- */
#define RTINetioSender_queryCapability(me, messageSizeMaxOut,               \
                                       gatherBufferCountMaxOut,             \
                                       toArray, toArraySize, worker)        \
    RTINetioSender_queryLeastCommonCapability(me, messageSizeMaxOut, \
                                              gatherBufferCountMaxOut, \
                                              NULL, toArray, toArraySize, \
                                              worker)


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* netio_sender_impl_h */
