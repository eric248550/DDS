/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)cdr_type.h    generated by: makeheader    Thu Feb 28 22:11:48 2019
 *
 *		built from:	type.ifc
 */

#ifndef cdr_type_h
#define cdr_type_h


 #ifndef osapi_type_h
    #include "osapi/osapi_type.h"
 #endif
 #ifndef cdr_dll_h
    #include "cdr/cdr_dll.h"
 #endif
 #ifndef cdr_encapsulation_h
    #include "cdr/cdr_encapsulation.h"
 #endif

#include "xcdr/xcdr_infrastructure.h"
#include "xcdr/xcdr_stream.h"

#ifdef __cplusplus
    extern "C" {
#endif


#define RTI_CDR_MAX_SERIALIZED_SIZE RTI_XCDR_MAX_SERIALIZED_SIZE


#if defined(RTI_DARWIN)
#else
#if defined(RTI_UNIX) && !defined(RTI_LINUX) && !defined(RTI_IRIX) && !defined(RTI_ENDIAN_LITTLE)
#define RTI_CDR_SIZEOF_LONG_DOUBLE 16
#endif
#endif
    
#define RTI_CDR_SIZEOF_LONG_LONG 8



/*e \ingroup RTICdrTypeModule
  CDR char type.
*/
typedef char RTICdrChar;

/*e \ingroup RTICdrTypeModule
  CDR wchar type.
*/
typedef RTIXCdrWchar RTICdrWchar;

/*e \ingroup RTICdrTypeModule
  CDR octet type.
*/
typedef RTI_UINT8 RTICdrOctet;

/*e \ingroup RTICdrTypeModule
  CDR short type.
*/
typedef RTI_INT16 RTICdrShort;

/*e \ingroup RTICdrTypeModule
  CDR unsigned short type.
*/
typedef RTI_UINT16 RTICdrUnsignedShort;

/*e \ingroup RTICdrTypeModule
  CDR long type.
*/
typedef RTI_INT32 RTICdrLong;

/*e \ingroup RTICdrTypeModule
  CDR unsigned long type.
*/
typedef RTI_UINT32 RTICdrUnsignedLong;

/*e \ingroup RTICdrTypeModule
  CDR long long type.
*/
typedef RTI_INT64 RTICdrLongLong;

/*e \ingroup RTICdrTypeModule
  CDR Unsigned long long type.
*/
typedef RTI_UINT64 RTICdrUnsignedLongLong;

/*e \ingroup RTICdrTypeModule
  CDR unsigned float type.
*/
typedef RTI_FLOAT32 RTICdrFloat;

/*e \ingroup RTICdrTypeModule
  CDR unsigned double type.
*/
typedef RTI_DOUBLE64 RTICdrDouble;

#if (RTI_CDR_SIZEOF_LONG_DOUBLE == 16)

  /*e \ingroup RTICdrTypeModule
    CDR long double type.
  */
  typedef long double RTICdrLongDouble;
#else
  typedef struct RTICdrLongDouble {
      char bytes[16];
  } RTICdrLongDouble;
#endif /* RTI_CDR_SIZEOF_LONGDOUBLE == 16 */

/*e \ingroup RTICdrTypeModule
  CDR boolean type.
*/
typedef RTI_UINT8 RTICdrBoolean;

/*e \ingroup RTICdrTypeModule
  CDR enum type.
*/
typedef RTI_INT32 RTICdrEnum;




/*e \ingroup RTICdrTypeModule
  CDR boolean true value.
*/
#define RTI_CDR_BOOLEAN_TRUE 1

/*e \ingroup RTICdrTypeModule
  CDR boolean false value.
*/
#define RTI_CDR_BOOLEAN_FALSE 0




/*e \ingroup RTICdrTypeSizeModule
  CDR char type size.
*/
#define RTI_CDR_CHAR_SIZE 1

/*e \ingroup RTICdrTypeSizeModule
  CDR octet type size.
*/
#define RTI_CDR_OCTET_SIZE 1

/*e \ingroup RTICdrTypeSizeModule
  CDR wchar type size.
*/
#define RTI_CDR_WCHAR_SIZE 4

/*e \ingroup RTICdrTypeSizeModule
  CDR short type size.
*/
#define RTI_CDR_SHORT_SIZE 2

/*e \ingroup RTICdrTypeSizeModule
  CDR unsigned short type size.
*/
#define RTI_CDR_UNSIGNED_SHORT_SIZE 2

/*e \ingroup RTICdrTypeSizeModule
  CDR long type size.
*/
#define RTI_CDR_LONG_SIZE 4

/*e \ingroup RTICdrTypeSizeModule
  CDR unsigned long type size.
*/
#define RTI_CDR_UNSIGNED_LONG_SIZE 4

/*e \ingroup RTICdrTypeSizeModule
  CDR long long type size.
*/
#define RTI_CDR_LONG_LONG_SIZE 8

/*e \ingroup RTICdrTypeSizeModule
  CDR unsigned long long type size.
*/
#define RTI_CDR_UNSIGNED_LONG_LONG_SIZE 8

/*e \ingroup RTICdrTypeSizeModule
  CDR float type size.
*/
#define RTI_CDR_FLOAT_SIZE 4

/*e \ingroup RTICdrTypeSizeModule
  CDR double type size.
*/
#define RTI_CDR_DOUBLE_SIZE 8

/*e \ingroup RTICdrTypeSizeModule
  CDR long double type size.
*/
#define RTI_CDR_LONG_DOUBLE_SIZE 16

/*e \ingroup RTICdrTypeSizeModule
  CDR boolean type size.
*/
#define RTI_CDR_BOOLEAN_SIZE 1

/*e \ingroup RTICdrTypeSizeModule
  CDR enum type size.
*/
#define RTI_CDR_ENUM_SIZE 4




/*e \ingroup RTICdrTypeAlignModule 
  CDR char alignment
*/
#define RTI_CDR_CHAR_ALIGN 1
/*e \ingroup RTICdrTypeAlignModule 
  CDR octet alignment
*/
#define RTI_CDR_OCTET_ALIGN 1
/*e \ingroup RTICdrTypeAlignModule 
  CDR wchar alignment
*/
#define RTI_CDR_WCHAR_ALIGN 4
/*e \ingroup RTICdrTypeAlignModule 
  CDR short alignment
*/
#define RTI_CDR_SHORT_ALIGN 2
/*e \ingroup RTICdrTypeAlignModule 
  CDR unsigned short alignment
*/
#define RTI_CDR_UNSIGNED_SHORT_ALIGN 2
/*e \ingroup RTICdrTypeAlignModule 
  CDR long alignment
*/
#define RTI_CDR_LONG_ALIGN 4
/*e \ingroup RTICdrTypeAlignModule 
  CDR unsigned long alignment
*/
#define RTI_CDR_UNSIGNED_LONG_ALIGN 4
/*e \ingroup RTICdrTypeAlignModule 
  CDR long long alignment
*/
#define RTI_CDR_LONG_LONG_ALIGN 8
/*e \ingroup RTICdrTypeAlignModule 
  CDR unsigned long long alignment
*/
#define RTI_CDR_UNSIGNED_LONG_LONG_ALIGN 8
/*e \ingroup RTICdrTypeAlignModule 
  CDR float alignment
*/
#define RTI_CDR_FLOAT_ALIGN 4
/*e \ingroup RTICdrTypeAlignModule 
  CDR double alignment
*/
#define RTI_CDR_DOUBLE_ALIGN 8
/*e \ingroup RTICdrTypeAlignModule 
  CDR long double alignment
*/
#define RTI_CDR_LONG_DOUBLE_ALIGN 8
/*e \ingroup RTICdrTypeAlignModule 
  CDR boolean alignment
*/
#define RTI_CDR_BOOLEAN_ALIGN 1
/*e \ingroup RTICdrTypeAlignModule 
  CDR enum alignment
*/
#define RTI_CDR_ENUM_ALIGN 4
/*e \ingroup RTICdrTypeAlignModule 
  CDR maximum alignment
*/
#define RTI_CDR_MAX_ALIGNMENT 8


typedef enum {
    /*e CDR char primitive type */
    RTI_CDR_CHAR_TYPE,
    /*e CDR wchar primitive type */
    RTI_CDR_WCHAR_TYPE,
    /*e CDR octet primitive type */
    RTI_CDR_OCTET_TYPE,
    /*e CDR short primitive type */
    RTI_CDR_SHORT_TYPE,
    /*e CDR unsigned short primitive type */
    RTI_CDR_UNSIGNED_SHORT_TYPE,
    /*e CDR long primitive type */
    RTI_CDR_LONG_TYPE,
    /*e CDR unsigned long primitive type */
    RTI_CDR_UNSIGNED_LONG_TYPE,
    /*e CDR long long primitive type */
    RTI_CDR_LONG_LONG_TYPE,
    /*e CDR unsigned long long primitive type */
    RTI_CDR_UNSIGNED_LONG_LONG_TYPE,
    /*e CDR float primitive type */
    RTI_CDR_FLOAT_TYPE,
    /*e CDR double primitive type */
    RTI_CDR_DOUBLE_TYPE,
    /*e CDR long double primitive type */
    RTI_CDR_LONG_DOUBLE_TYPE,
    /*e CDR boolean primitive type */
    RTI_CDR_BOOLEAN_TYPE,
    /*e CDR enum primitive type */
    RTI_CDR_ENUM_TYPE
} RTICdrPrimitiveType;

extern RTICdrDllExport
int RTICdrType_getPrimitiveTypeAlignment(RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getPrimitiveTypeSize(RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getWstringLength(const RTICdrWchar * str);

extern RTICdrDllExport
unsigned int RTICdrType_getCORBAWstringLength(const void * str,RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getCharMaxSizeSerialized(unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getWcharMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getCORBAWCharMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getOctetMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getShortMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getUnsignedShortMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getLongMaxSizeSerialized(unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getUnsignedLongMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getLongLongMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getUnsignedLongLongMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getFloatMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getDoubleMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getLongDoubleMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getBooleanMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getEnumMaxSizeSerialized(
    unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getPrimitiveArrayMaxSizeSerialized(
    unsigned int currentAlignment,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getCORBAWCharArrayMaxSizeSerialized(
    unsigned int currentAlignment,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getPrimitiveSequenceMaxSizeSerialized(
    unsigned int currentAlignment, RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getPrimitiveSequenceSerializedSize(
    unsigned int currentAlignment, RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getCORBAWCharSequenceMaxSizeSerialized(
    unsigned int currentAlignment, RTICdrUnsignedLong maximumLength,
    RTICdrPrimitiveType type);


typedef unsigned int (*RTICdrTypeGetSerializedSampleMaxSizeFunction)
    (void *endpointData,
     RTIBool includeEncapsulation,
     RTIEncapsulationId encapsulationId,
     unsigned int currentAlignment);


typedef unsigned int (*RTICdrTypeGetSerializedSampleMaxSizeExFunction)
    (void *endpointData,
     RTIBool * overflow,
     RTIBool includeEncapsulation,
     RTIEncapsulationId encapsulationId,
     unsigned int currentAlignment);

extern RTICdrDllExport
unsigned int RTICdrType_getNonPrimitiveArrayMaxSizeSerialized(
    unsigned int currentAlignment, RTICdrUnsignedLong length,
    RTICdrTypeGetSerializedSampleMaxSizeFunction 
        getSerializedSampleMaxSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    void *endpointData);

extern RTICdrDllExport
unsigned int RTICdrType_getNonPrimitiveArrayMaxSizeSerializedEx(
    RTIBool * overflow,
    unsigned int currentAlignment, RTICdrUnsignedLong length,
    RTICdrTypeGetSerializedSampleMaxSizeExFunction 
        getSerializedSampleMaxSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    void *endpointData);

extern RTICdrDllExport
unsigned int RTICdrType_getNonPrimitiveSequenceMaxSizeSerialized(
    unsigned int currentAlignment, RTICdrUnsignedLong maximumLength,
    RTICdrTypeGetSerializedSampleMaxSizeFunction
        getSerializedSampleMaxSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    void *endpointData);

extern RTICdrDllExport
unsigned int RTICdrType_getNonPrimitiveSequenceMaxSizeSerializedEx(
    RTIBool * overflow,
    unsigned int currentAlignment, RTICdrUnsignedLong maximumLength,
    RTICdrTypeGetSerializedSampleMaxSizeExFunction
        getSerializedSampleMaxSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    void *endpointData);


typedef unsigned int (*RTICdrTypeGetSerializedSampleSizeFunction)
    (void *endpointData, 
     RTIBool includeEncapsulation,
     RTIEncapsulationId encapsulationId,
     unsigned int currentAlignment,
     const void * sample);

extern RTICdrDllExport
unsigned int RTICdrType_getNonPrimitiveArraySerializedSize(
    unsigned int currentAlignment, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrTypeGetSerializedSampleSizeFunction
        getSerializedSampleMaxSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    const void *in,
    void *endpointData);

extern RTICdrDllExport
unsigned int RTICdrStream_getNonPrimitivePointerArraySerializedSize(
    unsigned int currentAlignment, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrTypeGetSerializedSampleSizeFunction
        getSerializedSampleSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    const void ** in,
    void *endpointData);

/*e \ingroup RTICdrTypeSizeModule
  Maximum serialized size of CDR string type from the current location.
 */
extern RTICdrDllExport
unsigned int RTICdrType_getStringMaxSizeSerialized(
    unsigned int currentAlignment,
    RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
unsigned int RTICdrType_getStringSerializedSize(
    unsigned int currentAlignment,
    const RTICdrChar * in);

extern RTICdrDllExport
unsigned int RTICdrType_getWstringMaxSizeSerialized(
    unsigned int currentAlignment, RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
unsigned int RTICdrType_getWstringSerializedSize(
    unsigned int currentAlignment,
    const RTICdrWchar * in);

extern RTICdrDllExport
unsigned int RTICdrType_getCORBAWstringSerializedSize(
    unsigned int currentAlignment,
    const void * in,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getBitsMaxSizeSerialized(
    unsigned int currentAlignment, unsigned int* currentBits, int numBits);

extern RTICdrDllExport
unsigned int RTICdrType_getStringArrayMaxSizeSerialized(
    unsigned int currentAlignment,
    RTICdrUnsignedLong length,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getStringSequenceMaxSizeSerialized(
    unsigned int currentAlignment, RTICdrUnsignedLong maximumLength,
    RTICdrUnsignedLong maximumStringLength,RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getStringArraySerializedSize(
    unsigned int currentAlignment,
    RTICdrUnsignedLong length,
    const void * in,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrType_getStringPointerArraySerializedSize(
    unsigned int currentAlignment,
    RTICdrUnsignedLong length,
    const void ** in,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrStream_getStringSequenceSerializedSize(
    unsigned int currentAlignment,
    const void *in,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrStream_getStringPointerSequenceSerializedSize(
    unsigned int currentAlignment,
    const void **in,
    RTICdrUnsignedLong length,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
unsigned int RTICdrStream_getNonPrimitiveSequenceSerializedSize(
    unsigned int currentAlignment, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrTypeGetSerializedSampleSizeFunction
        getSerializedSampleSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    const void * in,
    void *endpointData);

extern RTICdrDllExport
unsigned int RTICdrStream_getNonPrimitivePointerSequenceSerializedSize(
    unsigned int currentAlignment, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrTypeGetSerializedSampleSizeFunction
        getSerializedSampleSizeFunction,
    RTIBool includeEncapsulation,
    RTIEncapsulationId encapsulationId,
    const void ** in,
    void *endpointData);

extern RTICdrDllExport
unsigned int RTICdrType_flushBitsMaxSizeSerialized(
    unsigned int currentAlignment, unsigned int* currentBits);

extern RTICdrDllExport
unsigned int RTICdrType_getPadSize(
    unsigned int currentAlignment, unsigned int alignment);

extern RTICdrDllExport
RTIBool RTICdrType_initChar(RTICdrChar *value);

extern RTICdrDllExport
RTIBool RTICdrType_initWchar(RTICdrWchar *value);

extern RTICdrDllExport
RTIBool RTICdrType_initOctet(RTICdrOctet *value);

extern RTICdrDllExport
RTIBool RTICdrType_initShort(RTICdrShort *value);

extern RTICdrDllExport
RTIBool RTICdrType_initUnsignedShort(RTICdrUnsignedShort *value);

extern RTICdrDllExport
RTIBool RTICdrType_initLong(RTICdrLong *value);

extern RTICdrDllExport
RTIBool RTICdrType_initUnsignedLong(RTICdrUnsignedLong *value);

extern RTICdrDllExport
RTIBool RTICdrType_initLongLong(RTICdrLongLong *value);

extern RTICdrDllExport
RTIBool RTICdrType_initUnsignedLongLong(RTICdrUnsignedLongLong *value);

extern RTICdrDllExport
RTIBool RTICdrType_initFloat(RTICdrFloat *value);

extern RTICdrDllExport
RTIBool RTICdrType_initDouble(RTICdrDouble *value);

extern RTICdrDllExport
RTIBool RTICdrType_initLongDouble(RTICdrLongDouble *value);

extern RTICdrDllExport
RTIBool RTICdrType_initBoolean(RTICdrBoolean *value);

extern RTICdrDllExport
RTIBool RTICdrType_initEnum(RTICdrEnum *value);

extern RTICdrDllExport
RTIBool RTICdrType_initVariableSizedInteger(void *value,RTICdrUnsignedLong size);

extern RTICdrDllExport
RTIBool RTICdrType_initString(RTICdrChar *value,
			      RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrType_initWstring(RTICdrWchar *value,
			       RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrType_initArray(
    void *value, RTICdrUnsignedLong length,
    unsigned int elementSize);

extern RTICdrDllExport
RTIBool RTICdrType_initStringArray(
    void *value, RTICdrUnsignedLong length,
    RTICdrUnsignedLong maximumStringLength,
    RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrType_finalizeStringArray(
    void *value, RTICdrUnsignedLong length,RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrType_copyChar(RTICdrChar *out, const RTICdrChar *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyWchar(RTICdrWchar *out, const RTICdrWchar *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyCORBAWChar(void *out,const void *in,RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrType_copyOctet(RTICdrOctet *out, const RTICdrOctet *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyShort(RTICdrShort *out, const RTICdrShort *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyUnsignedShort(RTICdrUnsignedShort *out,
				     const RTICdrUnsignedShort *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyLong(RTICdrLong *out, const RTICdrLong *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyUnsignedLong(RTICdrUnsignedLong *out,
				    const RTICdrUnsignedLong *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyLongLong(RTICdrLongLong *out,
				const RTICdrLongLong *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyUnsignedLongLong(RTICdrUnsignedLongLong *out,
					const RTICdrUnsignedLongLong *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyFloat(RTICdrFloat *out, const RTICdrFloat *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyDouble(RTICdrDouble *out, const RTICdrDouble *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyLongDouble(RTICdrLongDouble *out,
				  const RTICdrLongDouble *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyBoolean(RTICdrBoolean *out,
			       const RTICdrBoolean *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyEnum(RTICdrEnum *out, const RTICdrEnum *in);

extern RTICdrDllExport
RTIBool RTICdrType_copyVariableSizedInteger(void *out, const void *in,RTICdrUnsignedLong size);

extern RTICdrDllExport
RTIBool RTICdrType_copyArray(
    void *out, const void* in, RTICdrUnsignedLong length,
    unsigned int elementSize);

extern RTICdrDllExport
RTIBool RTICdrType_copyStringArray(
    void *out, const void* in, RTICdrUnsignedLong length,
    RTICdrUnsignedLong maximumStringLength,RTICdrPrimitiveType type);

extern RTICdrDllExport
RTIBool RTICdrType_copyStringArrayEx(
    void *out, const void* in, RTICdrUnsignedLong length,
    RTICdrUnsignedLong maximumStringLength,RTICdrPrimitiveType type,
    RTIBool reallocate);

extern RTICdrDllExport
RTIBool RTICdrType_copyString(RTICdrChar *out, const RTICdrChar* in,
			      RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrType_copyStringEx(RTICdrChar **out, const RTICdrChar* in,
                              RTICdrUnsignedLong maximumLength,
                              RTIBool reallocate);

extern RTICdrDllExport
RTIBool RTICdrType_copyWstring(RTICdrWchar *out, const RTICdrWchar* in,
                        RTICdrUnsignedLong maximumLength);

extern RTICdrDllExport
RTIBool RTICdrType_copyWstringEx(RTICdrWchar **out, const RTICdrWchar* in,
                        RTICdrUnsignedLong maximumLength,
                        RTIBool reallocate);

extern RTICdrDllExport
const void* RTICdrType_printPreamble(const void* p, const char *desc,
				     unsigned int indent);

extern RTICdrDllExport
const void* RTICdrType_printPrimitivePreamble(const void* ptr, const char *desc,
                                              unsigned int indent);

extern RTICdrDllExport
void RTICdrType_printChar(const RTICdrChar *value, const char *desc,
			    int indent);

extern RTICdrDllExport
void RTICdrType_printWchar(const RTICdrWchar *value, const char *desc,
			     int indent);

extern RTICdrDllExport
void RTICdrType_printCORBAWChar(const void *value, const char *desc,
			     int indent,RTICdrPrimitiveType type);

extern RTICdrDllExport
void RTICdrType_printOctet(const RTICdrOctet *value, const char *desc,
			     int indent);

extern RTICdrDllExport
void RTICdrType_printShort(const RTICdrShort *value, const char *desc,
			     int indent);

extern RTICdrDllExport
void  RTICdrType_printUnsignedShort(const RTICdrUnsignedShort *value,
				      const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printLong(const RTICdrLong *value, const char *desc,
			    int indent);

extern RTICdrDllExport
void RTICdrType_printUnsignedLong(const RTICdrUnsignedLong *value,
				    const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printLongLong(const RTICdrLongLong *value,
			      const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printUnsignedLongLong(const RTICdrUnsignedLongLong *value,
					const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printFloat(const RTICdrFloat *value, const char *desc,
			     int indent);

extern RTICdrDllExport
void RTICdrType_printDouble(const RTICdrDouble *value, const char *desc,
			      int indent);

extern RTICdrDllExport
void RTICdrType_printLongDouble(const RTICdrLongDouble *value,
				  const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printBoolean(const RTICdrBoolean *value, const char *desc,
			       int indent);

extern RTICdrDllExport
void RTICdrType_printEnum(const RTICdrEnum *value, const char *desc,
			    int indent);

extern RTICdrDllExport
void RTICdrType_printVariableSizedInteger(const void *p,const char *desc,int indent,RTICdrUnsignedLong size);

extern RTICdrDllExport
void RTICdrType_printString(const RTICdrChar *value, const char *desc,int indent);

extern RTICdrDllExport
void RTICdrType_printWstring(const RTICdrWchar *value,const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printCORBAWstring(const void *value,
			          RTICdrUnsignedLong length,
			          const char *desc, int indent,RTICdrPrimitiveType type);

extern RTICdrDllExport
void RTICdrType_printBits(const RTICdrLong *value, const char *desc,
			    int indent, int numBits);

extern RTICdrDllExport
void RTICdrType_printUnsignedBits(const RTICdrLong *value,
				    const char *desc, int indent, int numBits);


typedef void (*RTICdrTypePrintFunction)(const void *value,
					const char *desc,
					int indent);


typedef void (*RTICdrTypePrintVariableSizedIntegerFunction)(const void *value,
					const char *desc,
					int indent,
					RTICdrUnsignedLong size);

extern RTICdrDllExport
void RTICdrType_printIndent(int count);

extern RTICdrDllExport
void RTICdrType_printArray(
    const void *array, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrTypePrintFunction printFunction,
    const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printVariableSizedIntegerArray(
    const void *array, RTICdrUnsignedLong length,
    unsigned int elementSize,
    RTICdrTypePrintVariableSizedIntegerFunction printFunction,
    const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printStringArray(const void * array,
                                   RTICdrUnsignedLong length,
                                   const char * desc,int indent, 
                                   RTICdrPrimitiveType type);

extern RTICdrDllExport
void RTICdrType_printPointerArray(
    const void *array, RTICdrUnsignedLong length,
    RTICdrTypePrintFunction printFunction,
    const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printStringPointerArray(const void * array,
					RTICdrUnsignedLong length,
					const char * desc,int indent, 
					RTICdrPrimitiveType type);

extern RTICdrDllExport
void RTICdrType_printNativeLongLong(const RTICdrLongLong *value,
				    const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printNativeUnsignedLongLong(
    const RTICdrUnsignedLongLong *value, const char *desc, int indent);

extern RTICdrDllExport
void RTICdrType_printNativeLongDouble(
    const RTICdrLongDouble *value, const char *desc, int indent);

struct RTINtpTime;

extern RTICdrDllExport
void RTICdrType_printNtpTime(const struct RTINtpTime *p,
			     const char *desc, unsigned int indent);


/* ========================================================================== */
/*                       ENDPOINT TYPE SUPPORT PROPERTIES                     */
/* ========================================================================== */


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "cdr/cdr_type_impl.h"
  
/* ----------------------------------------------------------------- */
/* String encoding properties */
#define DDS_DATA_READER_STRING_ENCODING_KIND_PROPERTY "dds.data_reader.type_support.cdr_string_encoding_kind"

#define DDS_DATA_WRITER_STRING_ENCODING_KIND_PROPERTY "dds.data_writer.type_support.cdr_string_encoding_kind"
 

#endif /* cdr_type_h */
