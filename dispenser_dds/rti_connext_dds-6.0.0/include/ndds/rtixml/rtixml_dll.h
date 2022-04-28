/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)rtixml_dll.h    generated by: makeheader    Thu Feb 28 22:11:39 2019
 *
 *		built from:	dll.ifc
 */

#ifndef rtixml_dll_h
#define rtixml_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
  #if defined(RTI_rtixml_DLL_EXPORT)
    #define RTIXMLDllExport __declspec( dllexport )
  #else
    #define RTIXMLDllExport
  #endif /* RTI_ddsxml_DLL_EXPORT */

  #if defined(RTI_rtixml_DLL_VARIABLE) 
    #if defined(RTI_rtixml_DLL_EXPORT)
      #define RTIXMLDllVariable __declspec( dllexport )
    #else
      #define RTIXMLDllVariable __declspec( dllimport )
    #endif /* RTI_ddsxml_DLL_EXPORT */
  #else 
    #define RTIXMLDllVariable
  #endif /* RTI_ddsxml_DLL_VARIABLE */
#else
  #define RTIXMLDllExport
  #define RTIXMLDllVariable
#endif /* RTI_WIN32 || RTI_WINCE || RTI_INTIME */


#endif /* rtixml_dll_h */
