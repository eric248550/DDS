/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)commend_anonReaderService.h    generated by: makeheader    Thu Feb 28 22:12:21 2019
 *
 *		built from:	anonReaderService.ifc
 */

#ifndef commend_anonReaderService_h
#define commend_anonReaderService_h


  #ifndef reda_worker_h
    #include "reda/reda_worker.h"
  #endif
  #ifndef reda_weakReference_h
    #include "reda/reda_weakReference.h"
  #endif
  #ifndef reda_database_h
    #include "reda/reda_database.h"
  #endif
  #ifndef netio_common_h
    #include "netio/netio_common.h"
  #endif
  #ifndef mig_rtps_h
    #include "mig/mig_rtps.h"
  #endif
  #ifndef commend_dll_h
    #include "commend/commend_dll.h"
  #endif
  #ifndef commend_readerService_h
    #include "commend/commend_readerService.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIClock;

struct REDADatabase;

struct COMMENDFacade;

struct COMMENDAnonReaderService;

struct COMMENDAnonReaderServiceRemoteWriterProperty {
    /*e port used in ACK. */
    NDDS_Transport_Port_t unicastReplyPort;
};


  #define COMMEND_ANON_READER_SERVICE_REMOTE_WRITER_PROPERTY_DEFAULT { \
    NDDS_TRANSPORT_PORT_INVALID     /* unicastReplyPort */  }

extern COMMENDDllExport struct COMMENDAnonReaderService *
COMMENDAnonReaderService_new(
    struct REDADatabase *db, struct COMMENDFacade *facade,
    const struct COMMENDReaderServiceProperty *property,
    struct REDAExclusiveArea *ea, struct REDAWorker *worker);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* commend_anonReaderService_h */
