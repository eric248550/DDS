/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_cpp_dll.h    generated by: makeheader    Thu Feb 28 22:13:03 2019
 *
 *		built from:	dll.ifcxx
 */

#ifndef dds_cpp_dll_h
#define dds_cpp_dll_h



#if defined(RTI_WIN32) || defined(RTI_WINCE) || defined(RTI_INTIME)
  #if defined(RTI_dds_cpp_DLL_EXPORT)
    #define DDSCPPDllExport __declspec( dllexport )
  #else
    #define DDSCPPDllExport
  #endif /* RTI_dds_cpp_DLL_EXPORT */

  #if defined(RTI_dds_cpp_DLL_VARIABLE) 
    #if defined(RTI_dds_cpp_DLL_EXPORT)
      #define DDSCPPDllVariable __declspec( dllexport )
    #else
      #define DDSCPPDllVariable __declspec( dllimport )
    #endif /* RTI_dds_cpp_DLL_EXPORT */
  #else 
    #define DDSCPPDllVariable
  #endif /* RTI_dds_cpp_DLL_VARIABLE */
#else
  #define DDSCPPDllExport
  #define DDSCPPDllVariable
#endif /* RTI_WIN32 || RTI_WINCE || RTI_INTIME */

/* Use the C++ constructs that are included in the DDS/C interfaces. */
#ifndef RTI_USE_CPP_API
#define RTI_USE_CPP_API
#endif


#endif /* dds_cpp_dll_h */
