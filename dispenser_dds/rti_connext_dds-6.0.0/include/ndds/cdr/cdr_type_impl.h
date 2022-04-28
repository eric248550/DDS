/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)cdr_type_impl.h    generated by: makeheader    Thu Feb 28 22:11:47 2019
 *
 *		built from:	type_impl.ifc
 */

#ifndef cdr_type_impl_h
#define cdr_type_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



#define RTICdrType_getPrimitiveTypeAlignment(type)    \
  ((((type) == RTI_CDR_CHAR_TYPE) ||                  \
    ((type) == RTI_CDR_OCTET_TYPE) ||                 \
    ((type) == RTI_CDR_BOOLEAN_TYPE)) ? 1 :           \
   ((((type) == RTI_CDR_SHORT_TYPE) ||                \
     ((type) == RTI_CDR_UNSIGNED_SHORT_TYPE)) ? 2 :   \
    ((((type) == RTI_CDR_WCHAR_TYPE) ||               \
      ((type) == RTI_CDR_LONG_TYPE) ||                \
      ((type) == RTI_CDR_UNSIGNED_LONG_TYPE) ||       \
      ((type) == RTI_CDR_FLOAT_TYPE) ||               \
      ((type) == RTI_CDR_ENUM_TYPE)) ? 4 :            \
     ((((type) == RTI_CDR_LONG_LONG_TYPE) ||          \
       ((type) == RTI_CDR_UNSIGNED_LONG_LONG_TYPE) || \
       ((type) == RTI_CDR_DOUBLE_TYPE) ||             \
       ((type) == RTI_CDR_LONG_DOUBLE_TYPE)) ? 8 : 0))))

#define RTICdrType_getPrimitiveTypeSize(type)         \
  ((((type) == RTI_CDR_CHAR_TYPE) ||                  \
    ((type) == RTI_CDR_OCTET_TYPE) ||                 \
    ((type) == RTI_CDR_BOOLEAN_TYPE)) ? 1U :          \
   ((((type) == RTI_CDR_SHORT_TYPE) ||                \
     ((type) == RTI_CDR_UNSIGNED_SHORT_TYPE)) ? 2U :  \
    ((((type) == RTI_CDR_WCHAR_TYPE)||                \
      ((type) == RTI_CDR_LONG_TYPE) ||                \
      ((type) == RTI_CDR_UNSIGNED_LONG_TYPE) ||       \
      ((type) == RTI_CDR_FLOAT_TYPE) ||               \
      ((type) == RTI_CDR_ENUM_TYPE)) ? 4U :           \
     ((((type) == RTI_CDR_LONG_LONG_TYPE) ||          \
       ((type) == RTI_CDR_UNSIGNED_LONG_LONG_TYPE) || \
       ((type) == RTI_CDR_DOUBLE_TYPE)) ? 8U :        \
      ((type) == RTI_CDR_LONG_DOUBLE_TYPE) ? 16U : 0U))))
      



#define RTICdrType_getPadSize(currentSize, align) \
  (((align) <= RTI_CDR_MAX_ALIGNMENT) ? \
    (RTIOsapiAlignment_alignSizeUp((currentSize), (align)) - (currentSize)) : \
    (RTIOsapiAlignment_alignSizeUp((currentSize), RTI_CDR_MAX_ALIGNMENT)    \
     - (currentSize)))

#define RTICdrType_get1ByteMaxSizeSerialized(currentSize) (1)

#define RTICdrType_get2ByteMaxSizeSerialized(currentSize) \
  (RTICdrType_getPadSize((currentSize), RTI_CDR_SHORT_ALIGN) + \
   RTI_CDR_SHORT_SIZE)

#define RTICdrType_get4ByteMaxSizeSerialized(currentSize) \
  (RTICdrType_getPadSize((currentSize), RTI_CDR_LONG_ALIGN) + \
   RTI_CDR_LONG_SIZE)

#define RTICdrType_get8ByteMaxSizeSerialized(currentSize) \
  (RTICdrType_getPadSize((currentSize), RTI_CDR_LONG_LONG_ALIGN) + \
   RTI_CDR_LONG_LONG_SIZE)

#define RTICdrType_get16ByteMaxSizeSerialized(currentSize) \
  (RTICdrType_getPadSize((currentSize), RTI_CDR_LONG_DOUBLE_ALIGN) + \
   RTI_CDR_LONG_DOUBLE_SIZE)




#define RTICdrType_getCharMaxSizeSerialized \
  RTICdrType_get1ByteMaxSizeSerialized

#define RTICdrType_getWcharMaxSizeSerialized \
  RTICdrType_get4ByteMaxSizeSerialized

#define RTICdrType_getCORBAWCharMaxSizeSerialized \
  RTICdrType_get4ByteMaxSizeSerialized

#define RTICdrType_getOctetMaxSizeSerialized \
  RTICdrType_get1ByteMaxSizeSerialized

#define RTICdrType_getShortMaxSizeSerialized \
  RTICdrType_get2ByteMaxSizeSerialized

#define RTICdrType_getUnsignedShortMaxSizeSerialized \
  RTICdrType_get2ByteMaxSizeSerialized

#define RTICdrType_getLongMaxSizeSerialized \
  RTICdrType_get4ByteMaxSizeSerialized

#define RTICdrType_getUnsignedLongMaxSizeSerialized \
  RTICdrType_get4ByteMaxSizeSerialized

#define RTICdrType_getLongLongMaxSizeSerialized \
  RTICdrType_get8ByteMaxSizeSerialized

#define RTICdrType_getUnsignedLongLongMaxSizeSerialized \
  RTICdrType_get8ByteMaxSizeSerialized

#define RTICdrType_getFloatMaxSizeSerialized \
  RTICdrType_get4ByteMaxSizeSerialized

#define RTICdrType_getDoubleMaxSizeSerialized \
  RTICdrType_get8ByteMaxSizeSerialized

#define RTICdrType_getLongDoubleMaxSizeSerialized \
  RTICdrType_get16ByteMaxSizeSerialized

#define RTICdrType_getBooleanMaxSizeSerialized \
  RTICdrType_get1ByteMaxSizeSerialized

#define RTICdrType_getEnumMaxSizeSerialized \
  RTICdrType_get4ByteMaxSizeSerialized

#define RTICdrType_getStringMaxSizeSerialized(currentSize, length) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
   (RTI_CDR_CHAR_SIZE * (length)))

#define RTICdrType_getStringSerializedSize(currentSize, in) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
      (((const char *) (in) == NULL)?0:((unsigned int)(strlen((in)) + 1))))

#define RTICdrType_getWstringMaxSizeSerialized(currentSize, length) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
   (RTI_CDR_WCHAR_SIZE * (length)))

#define RTICdrType_getWstringSerializedSize(currentSize, in) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
      ((((void *) (in) == NULL)?0:(RTICdrType_getWstringLength((in))*RTI_CDR_WCHAR_SIZE)) + RTI_CDR_WCHAR_SIZE))

#define RTICdrType_getCORBAWstringSerializedSize(currentSize, in, charType) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
      ((((in) == NULL)?0:(RTICdrType_getCORBAWstringLength((in), (charType))*RTI_CDR_WCHAR_SIZE)) + RTI_CDR_WCHAR_SIZE))

#define RTICdrType_getPrimitiveArrayMaxSizeSerialized(currentSize, length, type) \
  ((length != 0)? \
  ((RTICdrType_getPadSize((currentSize), \
   RTICdrType_getPrimitiveTypeSize((type))) + \
   (RTICdrType_getPrimitiveTypeSize((type)) * (length)))) : \
   0)

#define RTICdrType_getCORBAWCharArrayMaxSizeSerialized(currentSize, length, type) \
  ((length != 0)? \
  ((RTICdrType_getPadSize((currentSize), \
   RTICdrType_getPrimitiveTypeSize((RTI_CDR_UNSIGNED_LONG_TYPE))) + \
   (RTICdrType_getPrimitiveTypeSize((RTI_CDR_UNSIGNED_LONG_TYPE)) * (length)))): \
   0)

#define RTICdrType_getPrimitiveSequenceMaxSizeSerialized(currentSize, maximumLength, type) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
   RTICdrType_getPrimitiveArrayMaxSizeSerialized( \
     (currentSize) + RTICdrType_get4ByteMaxSizeSerialized( \
       (currentSize)), (maximumLength), (type)))

#define RTICdrType_getPrimitiveSequenceSerializedSize(currentSize, length, type) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
   RTICdrType_getPrimitiveArrayMaxSizeSerialized( \
     (currentSize) + RTICdrType_get4ByteMaxSizeSerialized( \
       (currentSize)), (length), (type)))

#define RTICdrType_getCORBAWCharSequenceMaxSizeSerialized(currentSize, maximumLength, type) \
  (RTICdrType_get4ByteMaxSizeSerialized((currentSize)) + \
   RTICdrType_getPrimitiveArrayMaxSizeSerialized( \
     (currentSize) + RTICdrType_get4ByteMaxSizeSerialized( \
       (currentSize)), (maximumLength), (RTI_CDR_UNSIGNED_LONG_TYPE)))

#define RTICdrType_getBitsMaxSizeSerialized(currentSize, currentBits, bitSize) \
  (((bitSize) + *(currentBits) > 32) ?                                         \
   (*(currentBits) = (bitSize),                                                \
    RTICdrType_get4ByteMaxSizeSerialized(currentSize)) :		               \
   (*(currentBits) += (bitSize), 0))
     
#define RTICdrType_flushBitsMaxSizeSerialized(currentSize, currentBits) \
  (*(currentBits) = 0,                                                  \
   RTICdrType_get4ByteMaxSizeSerialized(currentSize))




#define RTICdrType_printNativeLongLongMacro(value, desc, indent)      \
   RTICdrType_printIndent((indent));                                  \
   (((void *) (value) == NULL) ?                                               \
    (((void *) (desc) != NULL) ? RTILog_debug("%s: NULL\n", (desc)) :         \
      RTILog_debug("NULL\n")) :                                      \
    (((void *) (desc) != NULL) ?                                               \
      RTILog_debug("%s: %lld\n", (desc), *(value)) :                 \
      RTILog_debug("%lld\n", *(value))))

#define RTICdrType_printNativeUnsignedLongLongMacro(value, desc, indent) \
   RTICdrType_printIndent((indent));                                  \
   (((void *) (value) == NULL) ?                                               \
    (((void *) (desc) != NULL) ? RTILog_debug("%s: NULL\n", (desc)) :         \
      RTILog_debug("NULL\n")) :                                      \
    (((void *) (desc) != NULL) ?                                               \
      RTILog_debug("%s: %llu\n", (desc), *(value)) :                 \
      RTILog_debug("%llu\n", *(value))))

#define RTICdrType_printNativeLongDoubleMacro(value, desc, indent)     \
   RTICdrType_printIndent((indent));                                   \
   (((void *) (value) == NULL) ?                                                \
    (((void *) (desc) != NULL) ? RTILog_debug("%s: NULL\n", (desc)) :          \
      RTILog_debug("NULL\n")) :                                       \
    (((void *) (desc) != NULL) ? RTILog_debug("%s: %Lf\n", (desc), *(value)) : \
      RTILog_debug("%Lf\n", *(value))))

#define RTICdrType_printNotImplMacro(value, desc, indent)             \
   RTICdrType_printIndent((indent));                                  \
   (((void *) (value) == NULL) ?                                               \
    (((void *) (desc) != NULL) ? RTILog_debug("%s: NULL\n", (desc)) :          \
      RTILog_debug("NULL\n")) :                                       \
    (((void *) (desc) != NULL) ?                                               \
      RTILog_debug("%s: not implemented\n", (desc)) :                 \
      RTILog_debug("not implemented\n")))

#if (RTI_CDR_SIZEOF_LONG_LONG == 8)
#define RTICdrType_printNativeLongLong(value, desc, indent) \
 RTICdrType_printNativeLongLongMacro(value, desc, indent)
#define RTICdrType_printNativeUnsignedLongLong(value, desc, indent) \
 RTICdrType_printNativeUnsignedLongLongMacro(value, desc, indent)
#else
#define RTICdrType_printNativeLongLong(value, desc, indent) \
 RTICdrType_printNotImplMacro(value, desc, indent)
#define RTICdrType_printNativeUnsignedLongLong(value, desc, indent) \
 RTICdrType_printNotImplMacro(value, desc, indent)
#endif

#if (RTI_CDR_SIZEOF_LONG_DOUBLE == 16)
#define RTICdrType_printNativeLongDouble(value, desc, indent) \
 RTICdrType_printNativeLongDoubleMacro(value, desc, indent)
#else
#define RTICdrType_printNativeLongDouble(value, desc, indent) \
 RTICdrType_printNotImplMacro(value, desc, indent)
#endif




#define RTICdrType_init8Byte(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (memset((value), 0, RTI_CDR_LONG_LONG_SIZE), RTI_TRUE))

#define RTICdrType_init16Byte(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (memset((value), 0, RTI_CDR_LONG_DOUBLE_SIZE), RTI_TRUE))

#define RTICdrType_initChar(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrChar)0, RTI_TRUE))

#define RTICdrType_initWchar(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrWchar)0, RTI_TRUE))

#define RTICdrType_initCORBAWChar(value,type)\
    (\
	((void *) (value) == NULL) ? RTI_FALSE :\
	(\
	    ((type)==RTI_CDR_UNSIGNED_SHORT_TYPE)?\
	    (memset((value),0,RTI_CDR_UNSIGNED_SHORT_SIZE),RTI_TRUE):\
            (memset((value),0,RTI_CDR_UNSIGNED_LONG_SIZE),RTI_TRUE)\
	)\
    )

#define RTICdrType_initOctet(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrOctet)0, RTI_TRUE))

#define RTICdrType_initShort(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrShort)0, RTI_TRUE))

#define RTICdrType_initUnsignedShort(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrUnsignedShort)0, RTI_TRUE))

#define RTICdrType_initLong(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrLong)0, RTI_TRUE))

#define RTICdrType_initUnsignedLong(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrUnsignedLong)0, RTI_TRUE))

#define RTICdrType_initLongLong(value) \
   RTICdrType_init8Byte((RTICdr8Byte *)(value))

#define RTICdrType_initUnsignedLongLong(value) \
   RTICdrType_init8Byte((RTICdr8Byte *)(value))

#define RTICdrType_initFloat(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrFloat)0, RTI_TRUE))

#define RTICdrType_initDouble(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrDouble)0, RTI_TRUE))

#define RTICdrType_initLongDouble(value) \
   RTICdrType_init16Byte((RTICdr16Byte *)(value))

#define RTICdrType_initBoolean(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = RTI_CDR_BOOLEAN_FALSE, RTI_TRUE))

#define RTICdrType_initEnum(value) \
  (((void *) (value) == NULL) ? RTI_FALSE : \
   (*(value) = (RTICdrEnum)0, RTI_TRUE))

#define RTICdrType_initVariableSizedInteger(value,size)                                                 \
  ((void *) (value) == NULL ? RTI_FALSE :                                                                         \
     ((size) == 1 ? ((*(RTICdrOctet*)value) = 0,RTI_TRUE) :                                              \
         ((size) == 2 ? ((*(RTICdrUnsignedShort*)(value)) = 0,RTI_TRUE) :                                  \
             ((size) == 4 ? ((*(RTICdrUnsignedLong*)(value)) = 0,RTI_TRUE) : RTI_FALSE))))

/* (size == 8 ? (RTICdrType_init8Byte((RTICdr8Byte *)(value)),RTI_TRUE) : RTI_FALSE))))) */

#define RTICdrType_initArray(value, length, elementSize) \
  (((void *) (value) == NULL) ? RTI_FALSE :                         \
   (memset((value), 0, ((elementSize) * (length))), RTI_TRUE))   

#define RTICdrType_initString(value, maximumLength) \
   RTICdrType_initArray((value), (maximumLength), sizeof(RTICdrChar))

#define RTICdrType_initWstring(value, maximumLength)   \
   RTICdrType_initArray((value), (maximumLength), sizeof(RTICdrWchar))




#define RTICdrType_copy8Byte(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (memcpy((out), (in), RTI_CDR_LONG_LONG_SIZE), RTI_TRUE))

#define RTICdrType_copy16Byte(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (memcpy((out), (in), RTI_CDR_LONG_DOUBLE_SIZE), RTI_TRUE))

#define RTICdrType_copyChar(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))


#define RTICdrType_copyWchar(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyCORBAWChar(out, in, type)\
    (\
	((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE :\
	(\
	    ((type)==RTI_CDR_UNSIGNED_SHORT_TYPE)?\
	    (memcpy((out),(in),RTI_CDR_UNSIGNED_SHORT_SIZE),RTI_TRUE):\
            (memcpy((out),(in),RTI_CDR_UNSIGNED_LONG_SIZE),RTI_TRUE)\
	)\
    )

#define RTICdrType_copyOctet(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyShort(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyUnsignedShort(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyLong(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyUnsignedLong(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyLongLong(out, in) \
   RTICdrType_copy8Byte((RTICdr8Byte *)(out), (RTICdr8Byte *)(in))

#define RTICdrType_copyUnsignedLongLong(out, in) \
   RTICdrType_copy8Byte((RTICdr8Byte *)(out), (RTICdr8Byte *)(in))

#define RTICdrType_copyFloat(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyDouble(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyLongDouble(out, in) \
   RTICdrType_copy16Byte((RTICdr16Byte *)(out), (RTICdr16Byte *)(in))

#define RTICdrType_copyBoolean(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyEnum(out, in) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE : \
   (*(out) = *(in), RTI_TRUE))

#define RTICdrType_copyVariableSizedInteger(out,in,size)                                                \
  (((void *) (out) == NULL) || ((void *) (in) == NULL) ? RTI_FALSE :                                                          \
     (size == 1 ? (*(RTICdrOctet*)(out) = *(RTICdrOctet*)(in),RTI_TRUE) :                               \
         (size == 2 ? (*(RTICdrUnsignedShort*)(out) = *(RTICdrUnsignedShort*)(in),RTI_TRUE) :           \
             (size == 4 ? (*(RTICdrUnsignedLong*)(out) = *(RTICdrUnsignedLong*)(in),RTI_TRUE) : RTI_FALSE))))

#define RTICdrType_copyArray(out, in, length, elementSize) \
  (((void *) (out) == NULL || (void *) (in) == NULL) ? RTI_FALSE :                         \
   (memcpy((out), (in), ((elementSize) * (length))), RTI_TRUE))   

#define RTICdrType_copyString(out, in, maximumLength) \
   (((void *) (in) == NULL) ? RTI_FALSE : \
   ((strlen((in)) + 1 > (maximumLength)) ? RTI_FALSE : \
    RTICdrType_copyArray((out), (in), strlen((in)) + 1, \
                         sizeof(RTICdrChar))))
                         
#define RTICdrType_copyWstring(out, in, maximumLength) \
   (((void *) (in) == NULL) ? RTI_FALSE : \
   ((RTICdrType_getWstringLength((in)) + 1 > (maximumLength)) ? RTI_FALSE : \
    RTICdrType_copyArray((out), (in), RTICdrType_getWstringLength((in)) + 1, \
                         sizeof(RTICdrWchar))))
                         



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* cdr_type_impl_h */
