/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_host.h    generated by: makeheader    Thu Feb 28 22:11:23 2019
 *
 *		built from:	host.ifc
 */

#ifndef osapi_host_h
#define osapi_host_h


  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif
  #ifndef osapi_dll_h
    #include "osapi/osapi_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

extern RTIOsapiDllExport RTI_UINT32 RTIOsapiHost_getId();


#define RTI_OSAPI_HOSTID_LEN        (16)
#define RTI_OSAPI_HOSTID_UNKNOWN    {{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}}
struct RTIOsapiHostId {
	RTI_UINT8 value[RTI_OSAPI_HOSTID_LEN]; 
};

extern RTIOsapiDllExport 
void RTIOsapiHost_getUniqueId(struct RTIOsapiHostId *hostId);

extern RTIOsapiDllExport 
RTIBool RTIOsapiHost_isUnknown(struct RTIOsapiHostId *hostId);


/* 64bit MAC address of host */
#define RTIHOST_HWADDR_LEN (8) 
#define RTIHOSTWADDR_UNKNOWN {{0,0,0,0,0,0,0,0}}
struct RTIHostHWAddr {
	RTI_UINT8 hwAddr[RTIHOST_HWADDR_LEN]; 
};

extern RTIOsapiDllExport void RTIOsapiHost_getHWAddress(struct RTIHostHWAddr *hwAddrOut);

extern RTIOsapiDllExport int RTIOsapiHost_getHostName(char *name, int len);

struct RTINtpTime;

extern RTIOsapiDllExport void
RTIOsapiHost_generateRandomTime(struct RTINtpTime* randomTimeOut,
				const struct RTINtpTime* timeMaxIn);


/* 12-byte UUID */
#define GUIDPREFIX_UNKNOWN {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
typedef unsigned int RTIOsapiGuidPrefix[3];


extern RTIOsapiDllExport void RTIOsapiHost_generate_uuid(RTIOsapiGuidPrefix *uuid_out);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_host_h */
