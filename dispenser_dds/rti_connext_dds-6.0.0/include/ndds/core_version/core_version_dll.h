/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)core_version_dll.h    generated by: makeheader    Thu Feb 28 22:12:47 2019
 *
 *		built from:	dll.ifc
 */

#ifndef core_version_dll_h
#define core_version_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
  #if defined(RTI_core_version_DLL_EXPORT)
    #define VERSDllExport __declspec( dllexport )
  #else
    #define VERSDllExport
  #endif /* RTI_core_version_DLL_EXPORT */

  #if defined(RTI_core_version_DLL_VARIABLE) 
    #if defined(RTI_core_version_DLL_EXPORT)
      #define VERSDllVariable __declspec( dllexport )
    #else
      #define VERSDllVariable __declspec( dllimport )
    #endif /* RTI_core_version_DLL_EXPORT */
  #else 
    #define VERSDllVariable
  #endif /* RTI_core_version_DLL_VARIABLE */
#else
  #define VERSDllExport
  #define VERSDllVariable
#endif /* RTI_WIN32 || RTI_WINCE || RTI_INTIME */


#endif /* core_version_dll_h */
