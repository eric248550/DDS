/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_dll.h    generated by: makeheader    Thu Feb 28 22:11:22 2019
 *
 *		built from:	dll.ifc
 */

#ifndef osapi_dll_h
#define osapi_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
  #if defined(RTI_osapi_DLL_EXPORT)
    #define RTIOsapiDllExport __declspec( dllexport )
  #else
    #define RTIOsapiDllExport
  #endif /* RTI_osapi_DLL_EXPORT */

  #if defined(RTI_osapi_DLL_VARIABLE) 
    #if defined(RTI_osapi_DLL_EXPORT)
      #define RTIOsapiDllVariable __declspec( dllexport )
    #else
      #define RTIOsapiDllVariable __declspec( dllimport )
    #endif /* RTI_osapi_DLL_EXPORT */
  #else 
    #define RTIOsapiDllVariable
  #endif /* RTI_osapi_DLL_VARIABLE */
#else
  #define RTIOsapiDllExport
  #define RTIOsapiDllVariable
#endif /* RTI_WIN32 || RTI_WINCE || RTI_INTIME */


#endif /* osapi_dll_h */
