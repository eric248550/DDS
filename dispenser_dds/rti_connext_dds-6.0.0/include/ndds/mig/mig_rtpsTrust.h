/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)mig_rtpsTrust.h    generated by: makeheader    Thu Feb 28 22:12:16 2019
 *
 *		built from:	rtpsTrust.ifc
 */

#ifndef mig_rtpsTrust_h
#define mig_rtpsTrust_h


  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif
  #ifndef cdr_type_h
    #include "cdr/cdr_type.h"
  #endif
  #ifndef mig_dll_h
    #include "mig/mig_dll.h"
  #endif
  #ifndef mig_rtps_h
    #include "mig/mig_rtps.h"
  #endif
  #ifndef mig_interpreter_h
    #include "mig/mig_interpreter.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

typedef RTICdrOctet MIGRtpsInterceptorTransformKind[4];

typedef RTICdrOctet MIGRtpsInterceptorTransformKeyId[4];

struct MIGRtpsInterceptorTransformIdentifier {
    MIGRtpsInterceptorTransformKind transformation_kind;
    MIGRtpsInterceptorTransformKeyId transformation_key_id;
};

extern MIGDllExport
void MIGRtpsTrustSubmessage_serializePrefix(
        struct REDABuffer *buffer,
        struct REDABuffer *pluginHeader,
        MIGRtpsInterceptorTransformKind transformKind,
        MIGRtpsInterceptorTransformKeyId transformKeyId,
        int pluginHeaderLength,
        RTICdrBoolean isRtpsMessage);

extern MIGDllExport
void MIGRtpsTrustSubmessage_serializePostfix(
        struct REDABuffer *buffer,
        struct REDABuffer *pluginTag,
        int pluginTagLength,
        RTICdrBoolean isRtpsMessage);

extern MIGDllExport
void MIGRtpsTrustSubmessage_serializeBody(
        struct REDABuffer *buffer,
        struct REDABuffer *pluginDataBody,
        int pluginDataBodyLength);

extern MIGDllExport
int MIGRtpsTrustSubmessage_deserializeSubMsgHeader(
        MIGRtpsSubmessageId *submessageId,
        MIGRtpsSubmessageFlag *submessageFlags,
        RTI_UINT16 *submessagePayloadLength,
        const struct REDABuffer *bufferIn);

extern MIGDllExport
int MIGRtpsTrustSubmessage_deserializePrefix(
        struct MIGRtpsInterceptorTransformIdentifier *transformId,
        struct REDABuffer *pluginHeader,
        const struct REDABuffer *bufferIn,
        RTICdrBoolean isRtpsMessage);

extern MIGDllExport
int MIGRtpsTrustSubmessage_deserializePostfix(
        struct REDABuffer *pluginTag,
        const struct REDABuffer *bufferIn,
        RTICdrBoolean isRtpsMessage);

extern MIGDllExport
int MIGRtpsTrustSubmessage_skipToSubmessage(
        struct REDABuffer *bufferOut,
        const struct REDABuffer *bufferIn,
        MIGRtpsSubmessageId requestedSubmessageId);

extern MIGDllExport
int MIGRtpsTrustSubmessage_deserializeBody(
        struct REDABuffer *pluginData,
        const struct REDABuffer *bufferIn);

extern MIGDllExport
int MIGRtpsTrustSubmessage_serializeInfoSrcFromRtpsBuffer(
        char *buffer,
        char *rtpsBuffer);

extern MIGDllExport
RTICdrBoolean MIGRtpsTrustSubmessage_validateInfoSrc(
        char *buffer,
        char *rtpsBuffer);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "mig/mig_rtps_impl.h"

#endif /* mig_rtpsTrust_h */
