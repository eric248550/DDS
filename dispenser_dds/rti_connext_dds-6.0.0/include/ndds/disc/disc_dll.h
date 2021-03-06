/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)disc_dll.h    generated by: makeheader    Thu Feb 28 22:12:46 2019
 *
 *		built from:	dll.ifc
 */

#ifndef disc_dll_h
#define disc_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
  #if defined(RTI_disc_DLL_EXPORT)
    #define DISCDllExport __declspec( dllexport )
  #else
    #define DISCDllExport
  #endif /* RTI_disc_DLL_EXPORT */

  #if defined(RTI_disc_DLL_VARIABLE) 
    #if defined(RTI_disc_DLL_EXPORT)
      #define DISCDllVariable __declspec( dllexport )
    #else
      #define DISCDllVariable __declspec( dllimport )
    #endif /* RTI_disc_DLL_EXPORT */
  #else 
    #define DISCDllVariable
  #endif /* RTI_disc_DLL_VARIABLE */
#else
  #define DISCDllExport
  #define DISCDllVariable
#endif /* RTI_WIN32 || RTI_WINCE || RTI_INTIME */


#endif /* disc_dll_h */
