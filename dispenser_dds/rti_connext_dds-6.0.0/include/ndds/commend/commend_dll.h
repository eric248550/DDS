/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)commend_dll.h    generated by: makeheader    Thu Feb 28 22:12:20 2019
 *
 *		built from:	dll.ifc
 */

#ifndef commend_dll_h
#define commend_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
  #if defined(RTI_mig_DLL_EXPORT)
    #define COMMENDDllExport __declspec( dllexport )
  #else
    #define COMMENDDllExport
  #endif /* RTI_mig_DLL_EXPORT */

  #if defined(RTI_mig_DLL_VARIABLE) 
    #if defined(RTI_mig_DLL_EXPORT)
      #define COMMENDDllVariable __declspec( dllexport )
    #else
      #define COMMENDDllVariable __declspec( dllimport )
    #endif /* RTI_mig_DLL_EXPORT */
  #else 
    #define COMMENDDllVariable
  #endif /* RTI_mig_DLL_VARIABLE */
#else
  #define COMMENDDllExport
  #define COMMENDDllVariable
#endif /* RTI_WIN32 || RTI_WINCE || RTI_INTIME */


#endif /* commend_dll_h */