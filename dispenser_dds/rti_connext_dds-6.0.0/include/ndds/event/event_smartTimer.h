/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)event_smartTimer.h    generated by: makeheader    Thu Feb 28 22:11:40 2019
 *
 *		built from:	smartTimer.ifc
 */

#ifndef event_smartTimer_h
#define event_smartTimer_h


  #ifndef event_interface_h
    #include "event/event_timer.h"
  #endif
  #ifndef event_dll_h
    #include "event/event_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIEventSmartTimer; /* forward declare to appease compiler */

extern RTIEventDllExport void
RTIEventSmartTimer_delete(struct RTIEventTimer *me);

extern RTIEventDllExport struct RTIEventTimer *RTIEventSmartTimer_new();


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* event_smartTimer_h */
