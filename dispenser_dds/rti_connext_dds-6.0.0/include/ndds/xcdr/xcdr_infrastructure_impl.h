/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
(c) Copyright, Real-Time Innovations, 2018-2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
============================================================================= */

#ifndef xcdr_infrastructure_impl_h
#define xcdr_infrastructure_impl_h


#ifdef __cplusplus
    extern "C" {
#endif


/* ------------------------------------------------------------------------- */
/* ---- Macro implementations ---------------------------------------------- */
/* ------------------------------------------------------------------------- */
#define RTIXCdrAlignment_alignSizeUp(size, alignment) \
    (((size) + (((RTIXCdrUnsignedLong)(alignment)) - 1)) & \
        ~(((RTIXCdrUnsignedLong)(alignment)) - 1))


#ifdef __cplusplus
    }   /* extern "C" */
#endif


/******************************************************************************
 * Including infrastructure_psm_impl must be the last thing we do in this file.
 ******************************************************************************/
#include "xcdr/xcdr_infrastructure_psm_impl.h"

#endif /* xcdr_infrastructure_impl_h */
