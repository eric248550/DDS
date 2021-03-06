/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)commend_readerService_impl.h    generated by: makeheader    Thu Feb 28 22:12:19 2019
 *
 *		built from:	readerService_impl.ifc
 */

#ifndef commend_readerService_impl_h
#define commend_readerService_impl_h


  #ifndef osapi_bufferUtils_h
    #include "osapi/osapi_bufferUtils.h"
  #endif
  #ifndef mig_interpreter_h
    #include "mig/mig_interpreter.h"
  #endif
#ifdef __cplusplus
    extern "C" {
#endif



#define COMMENDReaderServiceProperty_copy(to, from) \
    RTIOsapiMemory_copy(to, from, sizeof(struct COMMENDReaderServiceProperty))

#define COMMENDReaderServiceData_set(me, context, sn, vSn, setFirstSn, batchSnOffset, statusInfo, \
                                     userData, parameter, batchSampleInfo, var, serializedData) \
  (me)->writer.prefix.hostId   = (context)->sourceHostId;                 \
  (me)->writer.prefix.appId    = (context)->sourceAppId;                  \
  (me)->writer.prefix.instanceId    = (context)->sourceInstanceId;        \
  (me)->writer.objectId = (context)->writerObjectId;                      \
  (me)->reader.prefix.hostId   = (context)->destinationHostId;            \
  (me)->reader.prefix.appId    = (context)->destinationAppId;             \
  (me)->reader.prefix.instanceId    = (context)->destinationInstanceId;   \
  (me)->reader.objectId = (context)->readerObjectId;                      \
  MIGGeneratorSample_set(&((me)->sample), (sn), (setFirstSn), vSn , batchSnOffset, (var), \
        ((context)->haveTimestamp ? &((context)->timestamp) : NULL),      \
        NULL, (context)->submessageFlags, (context)->dataExtraFlags,   \
        (statusInfo), (userData), (parameter), NULL, NULL, batchSampleInfo, (serializedData));



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* commend_readerService_impl_h */
