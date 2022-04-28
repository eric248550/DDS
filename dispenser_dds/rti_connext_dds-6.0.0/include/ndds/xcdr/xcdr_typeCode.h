/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
(c) Copyright, Real-Time Innovations, 2017-2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
============================================================================= */

#ifndef xcdr_typeCode_h
#define xcdr_typeCode_h


#ifdef __cplusplus
    extern "C" {
#endif


#include "xcdr/xcdr_stream.h"


/* Value assigned to the label DEFAULT in a union.
 * This value should not be used to determine if a label is the default label
 * or not. Use the function RTIXCdrTypeCode_get_default_index instead.
 */
#define RTI_XCDR_TYPE_CODE_UNION_DEFAULT_LABEL 0x40000001

typedef enum {
    RTI_XCDR_TK_NULL,
    RTI_XCDR_TK_SHORT,
    RTI_XCDR_TK_LONG,
    RTI_XCDR_TK_USHORT,
    RTI_XCDR_TK_ULONG,
    RTI_XCDR_TK_FLOAT,
    RTI_XCDR_TK_DOUBLE,
    RTI_XCDR_TK_BOOLEAN,
    RTI_XCDR_TK_CHAR,
    RTI_XCDR_TK_OCTET,
    RTI_XCDR_TK_STRUCT,
    RTI_XCDR_TK_UNION,
    RTI_XCDR_TK_ENUM,
    RTI_XCDR_TK_STRING,
    RTI_XCDR_TK_SEQUENCE,
    RTI_XCDR_TK_ARRAY,
    RTI_XCDR_TK_ALIAS,
    RTI_XCDR_TK_LONGLONG,
    RTI_XCDR_TK_ULONGLONG,
    RTI_XCDR_TK_LONGDOUBLE,
    RTI_XCDR_TK_WCHAR,
    RTI_XCDR_TK_WSTRING,
    RTI_XCDR_TK_VALUE,
    RTI_XCDR_TK_SPARSE,

    RTI_XCDR_TK_RAW_BYTES =       0x7e,
    RTI_XCDR_TK_RAW_BYTES_KEYED = 0x7f,

    /* 
     * Important! When adding new flags, make sure that the value does not
     * conflict with the values used to indicate that a typecode is in cdr
     * representation, see RTIXCdrTypeCode_isCdrRepresentation
     */

    /* only used for local representation, OR with above */
    RTI_XCDR_TK_FLAG_IS_INDEXED = 0x8000,

    /* only used to represent xtypes annotations */
    RTI_XCDR_TK_FLAGS_IS_FINAL = 0x4000,
    RTI_XCDR_TK_FLAGS_IS_MUTABLE = 0x2000,

    /* only used to represent RTI-specific annotations */
    RTI_XCDR_TK_FLAGS_IS_FLAT_DATA = 0x10000,
    RTI_XCDR_TK_FLAGS_IS_SHMEM_REF = 0x20000,

    RTI_XCDR_TK_FLAGS_ALL = 0xfff00

} RTIXCdrTCKind;

typedef enum 
{ 
    RTI_XCDR_FINAL_EXTENSIBILITY,
    RTI_XCDR_EXTENSIBLE_EXTENSIBILITY,
    RTI_XCDR_MUTABLE_EXTENSIBILITY
} RTIXCdrExtensibilityKind;

typedef short RTIXCdrValueModifier;


#define RTI_XCDR_VM_NONE 0
#define RTI_XCDR_VM_CUSTOM 1
#define RTI_XCDR_VM_ABSTRACT 2
#define RTI_XCDR_VM_TRUNCATABLE 3
#define RTI_XCDR_VM_MUTABLE 4

typedef short RTIXCdrVisibility;


#define RTI_XCDR_PRIVATE_MEMBER 0
#define RTI_XCDR_PUBLIC_MEMBER 1

typedef RTIXCdrOctet RTIXCdrMemberFlags;


#define RTI_XCDR_NONKEY_MEMBER 0
#define RTI_XCDR_KEY_MEMBER 1
#define RTI_XCDR_REQUIRED_MEMBER 2 /* for TK_SPARSE, STRUCT AND VALUE */

/* bit flags: [... required | key ] */
#define RTI_XCDR_FLAG_KEY_MEMBER 1
#define RTI_XCDR_FLAG_REQUIRED_MEMBER 2

struct RTIXCdrTypeCode;

struct RTIXCdrTypeCodeMember;

typedef RTIXCdrOctet RTIXCdrLanguageBinding;

#define RTI_XCDR_TYPE_BINDING_INVALID       0x00
#define RTI_XCDR_TYPE_BINDING_C             0x01
#define RTI_XCDR_TYPE_BINDING_CPP           0x02
#define RTI_XCDR_TYPE_BINDING_CPP_03        0x03
#define RTI_XCDR_TYPE_BINDING_CPP_03_STL    0x04
#define RTI_XCDR_TYPE_BINDING_CPP_11        0x05
#define RTI_XCDR_TYPE_BINDING_CPP_11_STL    0x06
#define RTI_XCDR_TYPE_BINDING_DYN_DATA      0x07
#define RTI_XCDR_TYPE_BINDING_SQL_FILTER    0x08

#define RTI_XCDR_TYPE_BINDING_FLAT_DATA_C           0x11
#define RTI_XCDR_TYPE_BINDING_FLAT_DATA_CPP         0x12
#define RTI_XCDR_TYPE_BINDING_FLAT_DATA_CPP_03      0x13
#define RTI_XCDR_TYPE_BINDING_FLAT_DATA_CPP_11      0x14
#define RTI_XCDR_TYPE_BINDING_FLAT_DATA_CPP_03_STL  0x15
#define RTI_XCDR_TYPE_BINDING_FLAT_DATA_CPP_11_STL  0x16

#define RTI_XCDR_TYPE_BINDING_FLAT_DATA_MASK 0x10

/* We created this structure to support use cases in which the language binding
 * implementation cannot return a pointer to a member value with the expected
 * format.
 *
 * For example, in modern C++, a vector of booleans does not store an array
 * of elements where each byte represent a boolean. In fact, it does store
 * booleans in a compact form (booleans)
 *
 * Because of this language binding implementation, the call to
 * getMemberValuePointerFcn cannot return a pointer to a buffer containing
 * the boolean values of the vector
 *
 * The interpreter will have to get/set one boolean at a time and the language
 * binding will not return a pointer to the value but the actual value
 * as part of this union.
 */
typedef struct RTIXCdrMemberValue {
    RTIXCdrBoolean isNull;
    union RTIXCdrMemberValue_v {
        char *ptr;
        RTIXCdrBoolean bVal;
        RTIXCdrWchar wVal;
        RTIXCdrLong lVal;
    } value;
} RTIXCdrMemberValue;

#define RTIXCdrMemberValue_INITIALIZER {RTI_XCDR_FALSE, {0}}

extern RTIXCdrDllVariable
const RTIXCdrMemberValue RTI_XCDR_MEMBER_VALUE_INVALID;

extern RTIXCdrDllVariable
const RTIXCdrMemberValue RTI_XCDR_MEMBER_VALUE_NIL;

/*
 * If the member is an optional member or a pointer, isNull must be set in the
 * returned value. Otherwise, setting isNull is not mandatory.
 *
 * This output elementCount value must be set for sequences and strings.For
 * strings, the elementCount shall include the null terminator.
 */
typedef RTIXCdrMemberValue (*RTIXCdrGetMemberValuePointerFcn)(
        void *sample,
        RTIXCdrUnsignedLong *elementCount,
        RTIXCdrUnsignedLongLong bindingMemberValueOffset,
        /* The elementIndex is only used when setMemberElementValueFcn is set
         */
        RTIXCdrUnsignedLong elementIndex,
        const struct RTIXCdrTypeCode *memberTc,
        /* In some cases this parameter could be NULL. Do not assume it cannot
         * be NULL
         *
         * For example, if the interpreter calls the function to get a pointer
         * for the element in a sequence. Technically in this case
         * there is no memberInfo because the memberInfo corresponds
         * to the sequence
         */
        const struct RTIXCdrTypeCodeMember *tcMemberInfo,
        RTIXCdrBoolean allocateMemberIfNull,
        void *programData);

/*
 * @brief Sets elementCount in sequences and strings
 *
 * @param trimToSize. Used for unbounded members. When set to true the
 * implementation must reallocate sequences and strings to have a capacity
 * of elementCount elements.
 *
 * For sequences, elementCount is the sequence length
 * For strings, elementCount is the string length including the NULL-terminated
 * character. elementCount should never be zero.
 *
 * The function must set failure to RTI_XCDR_TRUE if there is an error.
 */
typedef RTIXCdrMemberValue (*RTIXCdrSetMemberElementCountFcn)(
        RTIXCdrBoolean *failure,
        void *sample,
        RTIXCdrUnsignedLong elementCount,
        RTIXCdrUnsignedLongLong bindingMemberValueOffset,
        const struct RTIXCdrTypeCode *memberTc,
        const struct RTIXCdrTypeCodeMember *tcMemberInfo,
        RTIXCdrBoolean allocateMemberIfNull,
        RTIXCdrBoolean trimToSize,
        void *programData);

/*
 * @brief Sets the value for the element with index elementIndex in a
 * sequence or string.
 *
 * @precondition For optional members, the member should be set before this
 * function is invoked.
 *
 * For sequences, elementCount is the sequence length
 * For strings, elementCount is the string length including the NULL-terminated
 * character. elementCount should never be zero.
 */
typedef void (*RTIXCdrSetMemberElementValueFcn)(
        void *sample,
        RTIXCdrUnsignedLongLong bindingMemberValueOffset,
        /* The elementIndex is only used when setMemberElementValueFcn is set
         */
        RTIXCdrUnsignedLong elementIndex,
        RTIXCdrMemberValue val,
        const struct RTIXCdrTypeCode *memberTc,
        const struct RTIXCdrTypeCodeMember *memberInfo,
        RTIXCdrBoolean allocateMemberIfNull,
        void *programData);

/*
 * @brief Finalize a member
 *
 * @param sample The sample containing the member to finalize
 *
 * @param bindingMemberValueOffset The offset of the member to finalize within
 *        sample
 *
 * @param memberInfo the memberInfo of the member to finalize
 *
 * @param deallocateReference Whether to deallocate memory associated with the
 *        member being finalized or to just clear the reference to allocated
 *        memory. This is true when called from the finalize program, but
 *        set to false when called from the copy program because we have copied
 *        reference from the source to the destination and we simply want to
 *        clear the reference and then reallocate memory to copy into
 *
 * @param programData The language binding-specific programData
 */
typedef void (*RTIXCdrFinalizeMemberValueFcn) (
        void *sample,
        RTIXCdrUnsignedLongLong bindingMemberValueOffset,
        const struct RTIXCdrTypeCodeMember *memberInfo,
        RTIXCdrBoolean deallocateReference,
        void *programData);


#define RTIXCdrMemberAccessInfo_OFFSET_COUNT 4

typedef struct RTIXCdrMemberAccessInfo {
    /* A member can have multiple offsets for flat data language binding
     * in which a member offset varies depending on the address in which
     * the sample containing the member starts
     * 
     * For the rest of the languages only the first offset is used
     * 
     * Note that the bindingMemberValueOffset type is RTIXCdrUnsignedLong
     * versus RTIXCdrUnsignedLongLong. We chose to do this to save space
     * because our implementation restricts the maximum size of a sample to
     * 2^31 for other reasons
     */
    RTIXCdrUnsignedLong bindingMemberValueOffset[RTIXCdrMemberAccessInfo_OFFSET_COUNT];
    /* When this is true, the deserialize program will skip this member instead.
     * Additionally, the initialize program will not be generated for the
     * member.
     */
    RTIXCdrBoolean skipDeserialization;
} RTIXCdrMemberAccessInfo;


#define RTIXCdrMemberAccessInfo_INITIALIZER {{0,0,0,0}, RTI_XCDR_FALSE}


/* 
 * The boolean type in the TypePlugin functions is RTIXCdrLong to match
 * RTIBool in higher layers
 */

typedef RTIXCdrLong (*RTIXCdrTypePluginSerializeFunction)(
        void *endpointPluginData,
        const void *sample, 
        struct RTIXCdrStream *stream, 
        RTIXCdrLong serializeEncapsulation,
        RTIXCdrEncapsulationId encapsulationId,
        RTIXCdrLong serializeSample, 
        void *endpointPluginQos);

typedef RTIXCdrLong (*RTIXCdrTypePluginSerializeKeyFunction)(
        void *endpointPluginData,
        const void *sample, 
        struct RTIXCdrStream *stream, 
        RTIXCdrLong serializeEncapsulation,
        RTIXCdrEncapsulationId encapsulationId,
        RTIXCdrLong serializeKey, 
        void *endpointPluginQos);

typedef RTIXCdrLong (*RTIXCdrTypePluginDeserializeFunction)(
        void *endpointData,
        void *sample,
        struct RTIXCdrStream *stream,
        RTIXCdrLong deserializeEncapsulation,
        RTIXCdrLong deserializeSample, 
        void *endpointPluginQos);

typedef RTIXCdrLong (*RTIXCdrTypePluginDeserializeKeyFunction)(
        void *endpointData,
        void *sample,
        struct RTIXCdrStream *stream,
        RTIXCdrLong deserializeEncapsulation,
        RTIXCdrLong deserializeKey, 
        void *endpointPluginQos);

typedef RTIXCdrLong (*RTIXCdrTypePluginSkipFunction)(
        void *endpointData,
        struct RTIXCdrStream *stream,   
        RTIXCdrLong skipEncapsulation,
        RTIXCdrLong skipSample, 
        void *endpointPluginQos);
 
typedef RTIXCdrUnsignedLong (*RTIXCdrTypePluginGetSerializedSampleSizeFunction)(
        void *endpointData,
        RTIXCdrLong includeEncapsulation,
        RTIXCdrEncapsulationId encapsulationId,
        RTIXCdrUnsignedLong size,
        const void *sample);

typedef RTIXCdrUnsignedLong (*RTIXCdrTypePluginGetSerializedSampleMaxSizeFunction)(
        void *endpointData,
        RTIXCdrLong *overflow,
        RTIXCdrLong includeEncapsulation,
        RTIXCdrEncapsulationId encapsulationId,
        RTIXCdrUnsignedLong size);
 
typedef RTIXCdrUnsignedLong (*RTIXCdrTypePluginGetSerializedSampleMinSizeFunction)(
        void *endpointData,
        RTIXCdrLong includeEncapsulation,
        RTIXCdrEncapsulationId encapsulationId,
        RTIXCdrUnsignedLong size);

typedef RTIXCdrUnsignedLong (*RTIXCdrTypePluginGetSerializedKeyMaxSizeFunction)(
        void *endpointData,
        RTIXCdrLong *overflow,
        RTIXCdrLong includeEncapsulation,
        RTIXCdrEncapsulationId encapsulation_id,
        RTIXCdrUnsignedLong size);

typedef RTIXCdrLong (*RTIXCdrTypePluginSerializedSampleToKeyFunction)(
        void *endpointData,
        void *sample,
        struct RTIXCdrStream *stream, 
        RTIXCdrLong deserializeEncapsulation,  
        RTIXCdrLong deserializeKey, 
        void *endpointPluginQos);

typedef RTIXCdrLong (*RTIXCdrTypePluginInitializeSampleFunction)(
        void *sample,
        RTIXCdrLong allocatePointers, 
        RTIXCdrLong allocateMemory);

/* 
 * A type used when deserializing unions in order to indicate to the
 * initializeWParam callback the previous discriminator value that was set and
 * the one that was received.
 * 
 * This allows the callback implementation to finalize and reinitialize the
 * member if needed. 
 */
typedef struct RTIXCdrUnionInitializeInfo {
    RTIXCdrLong discValuePrev;
    RTIXCdrLong discValueNext;
} RTIXCdrUnionInitializeInfo;

#define RTIXCdrUnionInitializeInfo_INTIALIZER { \
    0, /* discValuePrev */ \
    0 /* discValueNext */ \
}

/* 
 * Used for language bindings that do no provide the generated initialize
 * methods. Currently the only user is the DynamicData language binding.
 * 
 * @param sample The member getting initiaized
 * @param typeCode The typecode of the member getting initialized
 * @param unionInfo If this method is called for a union, the union info will
 *        be set indicating that the previous union member should be finalized
 *        and the new member should be initialized
 * @param programData The programData from the calling program
 * @param param A language binding specific param that is provided in the
 *        RTIXCdrTypePlugin when this initialize method is set
 */ 
typedef RTIXCdrLong (*RTIXCdrTypePluginInitializeSampleWParamsFunction)(
        void *sample,
        const struct RTIXCdrTypeCode *typeCode,
        RTIXCdrUnionInitializeInfo *unionInfo,
        void *programData,
        void *param);

typedef RTIXCdrLong (*RTIXCdrTypePluginFinalizeSampleFunction)(
        void *sample);

typedef struct RTIXCdrTypePlugin {
    RTIXCdrTypePluginSerializeFunction serializeFnc;
    RTIXCdrTypePluginSerializeKeyFunction serializeKeyFnc;
    RTIXCdrTypePluginDeserializeFunction deserializeFnc;
    RTIXCdrTypePluginDeserializeKeyFunction deserializeKeyFnc;
    RTIXCdrTypePluginSkipFunction skipFnc;
    RTIXCdrTypePluginGetSerializedSampleSizeFunction getSerSampleSizeFnc;
    RTIXCdrTypePluginGetSerializedSampleMaxSizeFunction getSerSampleMaxSizeFnc;
    RTIXCdrTypePluginGetSerializedKeyMaxSizeFunction getSerKeyMaxSizeFnc;
    RTIXCdrTypePluginGetSerializedSampleMinSizeFunction getSerSampleMinSizeFnc; 
    RTIXCdrTypePluginSerializedSampleToKeyFunction serializedSampleToKeyFnc;
    RTIXCdrTypePluginInitializeSampleFunction initializeSampleFnc;
    RTIXCdrTypePluginInitializeSampleWParamsFunction initializeSampleWParamsFnc;
    RTIXCdrTypePluginFinalizeSampleFunction finalizeSampleFnc;
    /* 
     * Can be used by a language binding to pass in language binding specific
     * information to any RTIXCdrTypePlugin *WParamsFnc 
     */
    void *typePluginParam;
} RTIXCdrTypePlugin;

#define RTIXCdrTypePlugin_INITIALIZER { \
    NULL, /* serializeFnc */ \
    NULL, /* serializeKeyFnc */ \
    NULL, /* deserializeFnc */ \
    NULL, /* deserializeKeyFnc */ \
    NULL, /* skipFnc */ \
    NULL, /* getSerSampleSizeFnc */ \
    NULL, /* getSerSampleMaxSizeFnc */ \
    NULL, /* getSerKeyMaxSizeFnc */ \
    NULL, /* getSerSampleMinSizeFnc */ \
    NULL, /* serializedSampleToKeyFnc */ \
    NULL, /* initializeSampleFnc */ \
    NULL, /* initializeSampleWParamsFnc */ \
    NULL, /* finalizeSampleFnc */ \
    NULL /* typePluginParam */ \
}


#define RTIXCdrMemberAccessInfo_NUM_TYPE_SIZES 4

typedef struct RTIXCdrSampleAccessInfo {
    RTIXCdrLanguageBinding languageBinding;
    /* A type can have multiple sizes for flat data language binding
     * in which the type size varies depending on the address in which
     * a member of that type starts
     * 
     * For the rest of the languages only the type is used
     */
    RTIXCdrUnsignedLong typeSize[RTIXCdrMemberAccessInfo_NUM_TYPE_SIZES];
    /* Set to TRUE if the user wants to call getMemberValuePointerFcn only
     * for optional or external members
     */
    RTIXCdrBoolean useGetMemberValueOnlyWithRef;
    RTIXCdrGetMemberValuePointerFcn getMemberValuePointerFcn;
    RTIXCdrSetMemberElementCountFcn setMemberElementCountFcn;
    RTIXCdrSetMemberElementValueFcn setMemberElementValueFcn;
    RTIXCdrFinalizeMemberValueFcn finalizeMemberValueFcn;
    struct RTIXCdrMemberAccessInfo *memberAccessInfos;
} RTIXCdrSampleAccessInfo;

extern RTIXCdrDllExport 
RTIXCdrBoolean RTIXCdrSampleAccessInfo_isFlatDataLanguageBinding(
        RTIXCdrLanguageBinding languageBinding);


#define RTIXCdrSampleAccessInfo_INITIALIZER { \
    RTI_XCDR_TYPE_BINDING_C, \
    {0,0,0,0}, \
    RTI_XCDR_FALSE, \
    NULL, \
    NULL, \
    NULL, \
    NULL, \
    NULL \
}

typedef struct RTIXCdrTypeCodeRepresentation {
    RTIXCdrUnsignedLong _pid; /* sparse */
    RTIXCdrBoolean _isPointer; /* struct, union, value, sparse */
    RTIXCdrShort _bits; /* struct, value, sparse */
    struct RTIXCdrTypeCode *_typeCode; /* struct, union, value, sparse */
} RTIXCdrTypeCodeRepresentation;

typedef enum {
    RTI_XCDR_XCDR = (0x00000001 << 0),
    RTI_XCDR_XML = (0x00000001 << 1),
    RTI_XCDR_XCDR2 = (0x00000001 << 2)
} RTIXCdrDataRepresentationMaskBits;

typedef RTIXCdrLong RTIXCdrDataRepresentationMask;

#define RTI_XCDR_DATA_REPRESENTATION_MASK_DEFAULT (RTI_XCDR_XCDR|RTI_XCDR_XCDR2)

/*
 * Literal value of an annotation member: either the default value in its
 * definition or the value applied in its usage.
 */
typedef struct RTIXCdrAnnotationParameterValue {

    RTIXCdrTCKind _d;
    union RTIXCdrAnnotationParameterValue_u {
        RTIXCdrBoolean boolean_value;
        RTIXCdrOctet octet_value;
        RTIXCdrShort short_value;
        RTIXCdrUnsignedShort ushort_value;
        RTIXCdrLong long_value;
        RTIXCdrUnsignedLong ulong_value;
        RTIXCdrLongLong long_long_value;
        RTIXCdrUnsignedLongLong ulong_long_value;
        RTIXCdrFloat float_value;
        RTIXCdrDouble double_value;
        /* RTIXCdrLongDouble long_double_value; Not supported yet */
        RTIXCdrChar char_value;
        RTIXCdrWchar wchar_value;
        RTIXCdrLong enumerated_value;
        RTIXCdrChar *string_value;
        RTIXCdrWchar *wstring_value;
    } _u;

} RTIXCdrAnnotationParameterValue;


#define RTIXCdrAnnotationParameterValue_INITIALIZER {   \
    RTI_XCDR_TK_NULL,                                   \
    {                                                   \
        0                                               \
    }                                                   \
}

typedef struct RTIXCdrTypeCodeAnnotations {
    struct RTIXCdrAnnotationParameterValue _defaultValue;
    struct RTIXCdrAnnotationParameterValue _minValue;
    struct RTIXCdrAnnotationParameterValue _maxValue;
    RTIXCdrDataRepresentationMask _allowedDataRepresentationMask;
} RTIXCdrTypeCodeAnnotations;


#define RTIXCdrTypeCodeAnnotations_INITIALIZER { \
    RTIXCdrAnnotationParameterValue_INITIALIZER, \
    RTIXCdrAnnotationParameterValue_INITIALIZER, \
    RTIXCdrAnnotationParameterValue_INITIALIZER, \
    RTI_XCDR_DATA_REPRESENTATION_MASK_DEFAULT \
}

extern RTIXCdrDllExport 
void RTIXCdrTypeCodeAnnotations_initialize(
        struct RTIXCdrTypeCodeAnnotations *annotations);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrTypeCodeAnnotations_copy(
        struct RTIXCdrTypeCodeAnnotations *out,
        const struct RTIXCdrTypeCodeAnnotations *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrTypeCodeAnnotations_equals(
        const struct RTIXCdrTypeCodeAnnotations *first,
        const struct RTIXCdrTypeCodeAnnotations *second);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrTypeCodeAnnotations_isDefaultAndRangeConsistent(
        const struct RTIXCdrTypeCodeAnnotations *self,
        RTIXCdrBoolean isRequiredMember);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrTypeCodeAnnotations_haveNonDefaultRange(
        const struct RTIXCdrTypeCodeAnnotations *annotations);

extern RTIXCdrDllExport
void RTIXCdrTypeCodeAnnotations_finalize(
        struct RTIXCdrTypeCodeAnnotations *annotations);

typedef struct RTIXCdrTypeCodeMember {
    char *_name; /* struct, union, enum, value, sparse */
    struct RTIXCdrTypeCodeRepresentation _representation; /* struct, union, value, sparse */
    RTIXCdrLong _ordinal; /* enum */
    RTIXCdrUnsignedLong _labelsCount; /* union */
    RTIXCdrLong _label; /* union */
    RTIXCdrLong *_labels; /* union */
    RTIXCdrMemberFlags _memberFlags; /* struct, value, sparse */
    RTIXCdrVisibility _visibility; /* value, sparse */
    RTIXCdrUnsignedShort _representationCount; /* sparse */
    struct RTIXCdrTypeCodeRepresentation *_representations; /* sparse */
    struct RTIXCdrTypeCodeAnnotations _annotations; /* default, min, max */
} RTIXCdrTypeCodeMember;


struct RTIXCdrInterpreterPrograms;

typedef struct RTIXCdrTypeCode {
    RTIXCdrLong _kind;  /* All types */
    RTIXCdrBoolean _isPointer; /* alias */
    RTIXCdrLong _default_index; /* unions */
    char *_name; /* struct, union, enum, alias, value, sparse */
    struct RTIXCdrTypeCode *_typeCode; /* alias, sequence, array, union, value, sparse, struct */
    RTIXCdrUnsignedLong _maximumLength; /* string, wstring, sequence */
    RTIXCdrUnsignedLong _dimensionsCount; /* array */
    RTIXCdrUnsignedLong *_dimensions; /* array */
    RTIXCdrUnsignedLong _memberCount; /* struct, union, enum, value, sparse */
    struct RTIXCdrTypeCodeMember *_members; /* struct, union, enum, value, sparse */
    RTIXCdrValueModifier _typeModifier; /* value, sparse */
    struct RTIXCdrTypeCodeAnnotations _annotations; /* default, min, max */
    /* 
     * To be used by the midlleware. Indicates if a TypeCode is copyable
     * or not (constant). Non copyable typecodes are not copied and/or deleted
     * because they are consider and treated as constants.
     * You just can use them as references
     */
    RTIXCdrBoolean _isCopyable;

    /* Information used by the interpreter */
    /* This information is specific to a language binding */
    RTIXCdrSampleAccessInfo *_sampleAccessInfo;
    RTIXCdrTypePlugin *_typePlugin;
} RTIXCdrTypeCode;

/*
 * @brief The following function return RTI_XCDR_TRUE if the input TypeCode is a
 * struct/valuetype (or an alias to struct/valuetype) and its serialized
 * samples have a format that can potentially be directly copied into a C sample
 * for the type with a memcpy operation
 *
 * This property is interesting because it will allow to serialize/deserialize
 * structures/valuetypes or arrays/sequences of structures/valuetypes
 * with a single memcpy.
 *
 * For example:
 *
 * struct Point {
 *     long x;
 *     long y;
 * };
 *
 * The previous struct has a CDR layout friendly to C
 *
 * A struct/valuetype 'MyStruct' has a C friendly CDR layout when:
 * 1) MyStruct is marked as @final or @appendable when the data representation
 * is XCDR v1. Mutable structures are not C friendly.
 * 2) MyStruct does not have a base type
 * 3) MyStruct only contain primitive members or complex members composed only
 * of primitive members. A primitive member is a member with any of the
 * following types: int16, int32, int64, uint16, uint32, uint64, float, double,
 * octet, and char. The following primitive types are not currently supported
 * for inlining purposes: long double, wchar, boolean, enum.
 * 4) With any initial alignment (1, 2, 4, 8) greater than the alignment of
 * the first member of the struct, there is no padding between the members
 * that are part of MyStruct. To apply this rule consider these alignments and
 * size for primitive types
 * 5) With any initial alignment (1, 2, 4, 8) greater than the alignment of
 * the first member of the struct, there is no padding between the elements of
 * an array of MyStruct.
 *
 * struct InlineStruct {
 *     char m1;
 *     long m2;
 * }; --> Not C friendly by 4)
 *
 * struct InlineStruct {
 *     long m1;
 *     short m2;
 * }; --> Not C friendly by 5)
 *
 * struct InlineStruct {
 *     long m1;
 *     short m2;
 *     short m3;
 * }; --> C frienly
 *
 * @param tc \b In. TypeCode
 *
 * @param elementCount \b In. Number of elements in an array of tc
 *
 * @param serSize \b Out. Serialized size of the inlinable struct
 *
 * @param alignment \b Out. Alignment required by the first member of the
 * struct/valuetype
 *
 * @param v2Encapsulation \b In. Indicates if the serialization format is
 * V1 or V2
 *
 */
extern RTIXCdrDllExport 
RTIXCdrBoolean RTIXCdrTypeCode_hasCFriendlyCdrLayout(
        const struct RTIXCdrTypeCode *tc,
        RTIXCdrUnsignedLongLong *serSize,
        RTIXCdrAlignment *alignment,
        RTIXCdrUnsignedLong elementCount,
        RTIXCdrBoolean v2Encapsulation);

/*
 * @brief Indicates if the inout member is optional
 */
extern RTIXCdrDllExport 
RTIXCdrBoolean RTIXCdrTypeCodeMember_isOptional(
        const struct RTIXCdrTypeCodeMember *member);

extern RTIXCdrDllExport 
RTIXCdrTCKind RTIXCdrTypeCode_getKind(const struct RTIXCdrTypeCode *tc);


#ifdef __cplusplus
    }	/* extern "C" */
#endif


#include "xcdr/xcdr_typeCode_impl.h"

#endif /* xcdr_typeCode_h */
