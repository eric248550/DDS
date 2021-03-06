/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)osapi_compression.h    generated by: makeheader    Thu Feb 28 22:11:24 2019
 *
 *		built from:	compression.ifc
 */

#ifndef osapi_compression_h
#define osapi_compression_h


  #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
  #endif
  #ifndef osapi_dll_h
    #include "osapi/osapi_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

typedef enum {
    RTI_OSAPI_COMPRESSION_RETCODE_OK = 0,
    RTI_OSAPI_COMPRESSION_RETCODE_ERROR = -1,
    RTI_OSAPI_COMPRESSION_RETCODE_NOT_SUPPORTED = -2
} RTIOsapiCompressionRetcode;

typedef enum {
    RTI_OSAPI_COMPRESSION_LEVEL_AUTO = 0,
    RTI_OSAPI_COMPRESSION_LEVEL_NO_COMPRESSION = 1,
    RTI_OSAPI_COMPRESSION_LEVEL_BEST_SPEED = 2,
    RTI_OSAPI_COMPRESSION_LEVEL_BEST_COMPRESSION = 3
} RTIOsapiCompressionLevel;

typedef enum {
    RTI_OSAPI_COMPRESSION_CLASS_ID_NONE = 0,
    RTI_OSAPI_COMPRESSION_CLASS_ID_ZLIB = 1,
    RTI_OSAPI_COMPRESSION_CLASS_ID_BZIP2 = 2,
    RTI_OSAPI_COMPRESSION_CLASS_ID_AUTO = -1
} RTIOsapiCompressionPluginClassId;

struct RTIOsapiCompressionPlugin;

typedef struct RTIOsapiCompressionPlugin RTIOsapiCompressionPlugin;


typedef RTIOsapiCompressionRetcode (*RTIOsapiCompressionPlugin_compressFunction)(
        RTIOsapiCompressionPlugin *self,
        char *bufferOut,
        int *lengthInOut,
        const char *bufferIn,
        int lengthIn,
        RTIOsapiCompressionLevel compressionLevel);


typedef RTIOsapiCompressionRetcode (*RTIOsapiCompressionPlugin_uncompressFunction)(
        RTIOsapiCompressionPlugin *self,
        char *bufferOut,
        int *lengthInOut,
        const char *bufferIn,
        int inLength);


typedef RTIOsapiCompressionRetcode (*RTIOsapiCompressionPlugin_destroyFunction)(
        RTIOsapiCompressionPlugin *self);

struct RTIOsapiCompressionPlugin {
    RTIOsapiCompressionPluginClassId classId;
    RTIOsapiCompressionPlugin_compressFunction compress;
    RTIOsapiCompressionPlugin_uncompressFunction uncompress;
    RTIOsapiCompressionPlugin_destroyFunction destroy;
};

extern RTIOsapiDllVariable
const RTIOsapiCompressionPlugin RTI_OSAPI_COMPRESSION_PLUGIN_ZLIB;

extern RTIOsapiDllExport
RTIOsapiCompressionRetcode RTIOsapi_Zlib_compress(
        RTIOsapiCompressionPlugin *self,
        char *bufferOut,
        int *lengthInOut,
        const char *bufferIn,
        int lengthIn,
        RTIOsapiCompressionLevel compressionLevel);

extern RTIOsapiDllExport
RTIOsapiCompressionRetcode RTIOsapi_Zlib_uncompress(
        RTIOsapiCompressionPlugin *self,
        char *bufferOut,
        int *lengthInOut,
        const char *bufferIn,
        int inLength);

extern RTIOsapiDllExport
RTIOsapiCompressionRetcode RTIOsapi_Zlib_destroy(
        RTIOsapiCompressionPlugin *self);

extern RTIOsapiDllVariable
const RTIOsapiCompressionPlugin RTI_OSAPI_COMPRESSION_PLUGIN_BZIP2;

extern RTIOsapiDllExport
RTIOsapiCompressionRetcode RTIOsapi_Bzip2_compress(
        RTIOsapiCompressionPlugin *self,
        char *bufferOut,
        int *lengthInOut,
        const char *bufferIn,
        int lengthIn,
        RTIOsapiCompressionLevel compressionLevel);

extern RTIOsapiDllExport
RTIOsapiCompressionRetcode RTIOsapi_Bzip2_uncompress(
        RTIOsapiCompressionPlugin *self,
        char *bufferOut,
        int *lengthInOut,
        const char *bufferIn,
        int inLength);

extern RTIOsapiDllExport
RTIOsapiCompressionRetcode RTIOsapi_Bzip2_destroy(
        RTIOsapiCompressionPlugin *self);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* osapi_compression_h */
