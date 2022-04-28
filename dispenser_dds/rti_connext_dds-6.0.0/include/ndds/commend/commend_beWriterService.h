/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)commend_beWriterService.h    generated by: makeheader    Thu Feb 28 22:12:21 2019
 *
 *		built from:	beWriterService.ifc
 */

#ifndef commend_beWriterService_h
#define commend_beWriterService_h


  #ifndef reda_worker_h
    #include "reda/reda_worker.h"
  #endif
  #ifndef reda_weakReference_h
    #include "reda/reda_weakReference.h"
  #endif
  #ifndef reda_database_h
    #include "reda/reda_database.h"
  #endif
  #ifndef mig_rtps_h
    #include "mig/mig_rtps.h"
  #endif
  #ifndef commend_dll_h
    #include "commend/commend_dll.h"
  #endif
  #ifndef commend_writerService_h
    #include "commend/commend_writerService.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIClock;

struct REDADatabase;

struct COMMENDBeWriterService;

struct COMMENDBeWriterServiceRemoteReaderProperty {
    /* parent property */
    struct COMMENDWriterServiceRemoteReaderProperty parent;
    /* minimum separation */
    struct RTINtpTime ms;
};


  #define COMMEND_BE_WRITER_SERVICE_REMOTE_READER_PROPERTY_DEFAULT {    \
    COMMEND_WRITER_SERVICE_REMOTE_READER_PROPERTY_DEFAULT, /* parent */ \
    RTI_NTP_TIME_ZERO /* ms */                                     }

extern COMMENDDllExport struct COMMENDBeWriterService *
COMMENDBeWriterService_new(
    struct REDADatabase *db, struct COMMENDFacade *facade,
    const struct COMMENDWriterServiceProperty *property,
    struct REDAExclusiveArea *ea, struct REDAWorker *worker);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "commend/commend_beWriterService_impl.h"

#endif /* commend_beWriterService_h */