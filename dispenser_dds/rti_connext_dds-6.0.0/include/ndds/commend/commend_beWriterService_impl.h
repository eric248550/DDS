/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)commend_beWriterService_impl.h    generated by: makeheader    Thu Feb 28 22:12:19 2019
 *
 *		built from:	beWriterService_impl.ifc
 */

#ifndef commend_beWriterService_impl_h
#define commend_beWriterService_impl_h


#ifndef osapi_bufferUtils_h
  #include "osapi/osapi_bufferUtils.h"
#endif
#ifndef reda_orderedDataType_h
  #include "reda/reda_orderedDataType.h"
#endif
#ifndef mig_rtps_h
  #include "mig/mig_rtps.h"
#endif

#ifdef __cplusplus
    extern "C" {
#endif


/* ---------------------------------------------------------------- */
#define COMMENDBeWriterServiceProperty_copy(to, from) \
   RTIOsapiMemory_copy(to, from, sizeof(struct COMMENDBeWriterServiceProperty))

/* ---------------------------------------------------------------- */
#define COMMENDBeWriterServiceRemoteReaderProperty_copy(to, from) \
   RTIOsapiMemory_copy(to, from,                                  \
              sizeof(struct COMMENDBeWriterServiceRemoteReaderProperty))


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* commend_beWriterService_impl_h */
