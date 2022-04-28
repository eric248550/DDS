/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)event_activeObject.h    generated by: makeheader    Thu Feb 28 22:11:40 2019
 *
 *		built from:	activeObject.ifc
 */

#ifndef event_activeObject_h
#define event_activeObject_h

struct REDAWorker;


  #ifndef osapi_thread_h
    #include "osapi/osapi_thread.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIEventActiveObject;


#define RTI_EVENT_ACTIVE_OBJECT_STATE_STARTING (0x0)


#define RTI_EVENT_ACTIVE_OBJECT_STATE_RUNNING (0x1)


#define RTI_EVENT_ACTIVE_OBJECT_STATE_PRE_SHUTDOWN (0x2)


#define RTI_EVENT_ACTIVE_OBJECT_STATE_SHUTDOWN (0x4)


#define RTI_EVENT_ACTIVE_OBJECT_STATE_STOPPED (0x8)

struct RTIEventActiveObjectProperty {
    /*e An active object has its own thread(s) */
    int priority, stackSize, options;
    struct RTIOsapiCpuBitmap bitmap;
};


#define RTI_EVENT_ACTIVE_OBJECT_PROPERTY_DEFAULT { \
    RTI_OSAPI_THREAD_PRIORITY_DEFAULT, \
    RTI_OSAPI_THREAD_STACK_SIZE_DEFAULT, \
    (RTI_OSAPI_THREAD_OPTION_PRIORITY_ENFORCE | RTI_OSAPI_THREAD_OPTION_STDIO), \
    RTI_OSAPI_CPU_BITMAP_DEFAULT \
}

typedef RTIBool (*RTIEventActiveObjectShutdownFunction)(
    struct RTIEventActiveObject *me,
    struct REDAWorker *worker);

typedef void (*RTIEventActiveObjectListenerOnStoppedCallback)(
    struct RTIEventActiveObject *me, void *onStoppedParam,
    struct REDAWorker *worker);

struct RTIEventActiveObjectListener {
    /*e */
    RTIEventActiveObjectListenerOnStoppedCallback onStopped;
    /*e pointer associated with onStopped method */
    void *onStoppedParam;
};


  #define RTI_EVENT_ACTIVE_OBJECT_LISTENER_DEFAULT {NULL, NULL}


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* event_activeObject_h */
