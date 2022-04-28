/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)event_polledTimer.h    generated by: makeheader    Thu Feb 28 22:11:40 2019
 *
 *		built from:	polledTimer.ifc
 */

#ifndef event_polledTimer_h
#define event_polledTimer_h


  #ifndef event_interface_h
    #include "event/event_timer.h"
  #endif
  #ifndef event_dll_h
    #include "event/event_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIEventPolledTimer; /* forward declare to appease compiler */

extern RTIEventDllExport void
RTIEventPolledTimer_delete(struct RTIEventTimer *me);

struct RTIEventPolledTimerProperty {
    /*e Must be > 0 */
    struct RTINtpTime pollPeriod;
};


  #define RTI_EVENT_POLLED_TIMER_PROPERTY_DEFAULT {{0, 0x80000000}}

extern RTIEventDllExport struct RTIEventTimer *
RTIEventPolledTimer_new(const struct RTIEventPolledTimerProperty *p);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* event_polledTimer_h */
