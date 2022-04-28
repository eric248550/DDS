/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)reda_dll.h    generated by: makeheader    Thu Feb 28 22:11:32 2019
 *
 *		built from:	dll.ifc
 */

#ifndef reda_dll_h
#define reda_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
  #if defined(RTI_reda_DLL_EXPORT)
    #define REDADllExport __declspec( dllexport )
  #else
    #define REDADllExport
  #endif /* RTI_reda_DLL_EXPORT */

  #if defined(RTI_reda_DLL_VARIABLE) 
    #if defined(RTI_reda_DLL_EXPORT)
      #define REDADllVariable __declspec( dllexport )
    #else
      #define REDADllVariable __declspec( dllimport )
    #endif /* RTI_reda_DLL_EXPORT */
  #else 
    #define REDADllVariable
  #endif /* RTI_reda_DLL_VARIABLE */
#else
  #define REDADllExport
  #define REDADllVariable
#endif /* RTI_WIN32 || RTI_WINCE || RTI_INTIME */


#endif /* reda_dll_h */
