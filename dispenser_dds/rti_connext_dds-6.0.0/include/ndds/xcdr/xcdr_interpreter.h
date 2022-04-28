/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
(c) Copyright, Real-Time Innovations, 2017-2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
============================================================================= */

#ifndef xcdr_interpreter_h
#define xcdr_interpreter_h


#include "xcdr/xcdr_dll.h"
#include "xcdr/xcdr_infrastructure.h"
#include "xcdr/xcdr_stream.h"
#include "xcdr/xcdr_typeCode.h"


#ifdef __cplusplus
    extern "C" {
#endif

typedef RTIXCdrOctet RTIXCdrRefMemberKind;
#define RTI_XCDR_INTERPRETER_VALUE_MEMBER 0
#define RTI_XCDR_INTERPRETER_OPTIONAL_MEMBER 1
#define RTI_XCDR_INTERPRETER_EXTERNAL_MEMBER 2

/* How the parameters are organized in the following structures is important
 * due to resource consumption reasons.
 *
 * Try to not create padding between fields.
 */
typedef struct RTIXCdrCommonInsParameters {
    struct RTIXCdrTypeCode *memberTc;
    struct RTIXCdrTypeCode *seqElementTc;
    struct RTIXCdrTypeCodeMember *tcMemberInfo;
    RTIXCdrUnsignedLong count;
    struct RTIXCdrMemberAccessInfo memberAccessInfo;
    /* Indicates if the member is
     * optional: RTI_XCDR_INTERPRETER_OPTIONAL_MEMBER
     * external: RTI_XCDR_INTERPRETER_EXTERNAL_MEMBER
     * value: RTI_XCDR_INTERPRETER_VALUE_MEMBER
     */
    RTIXCdrRefMemberKind refMemberKind;
    RTIXCdrBoolean useGetMemberValue;
} RTIXCdrCommonInsParameters;

typedef struct RTIXCdrStringInsParameters {
    RTIXCdrCommonInsParameters parent;
    RTIXCdrUnsignedLong charMaxCount;
    RTIXCdrLong charAlignment;
    RTIXCdrOctet charSize;
} RTIXCdrStringInsParameters;

typedef struct RTIXCdrPrimitiveInsParameters {
    RTIXCdrCommonInsParameters parent;
    /* When set the value of an enum must be check on ser/deser,
     * enumTc contains the enumTc
     */
    struct RTIXCdrTypeCode *enumTc;
    RTIXCdrUnsignedLong primitiveByteCount;
    RTIXCdrTCKind primitiveKind;
    RTIXCdrLong primitiveAlignment;
    RTIXCdrBoolean checkRange;
    RTIXCdrBoolean mustAlign;
    RTIXCdrOctet primitiveSize;
    RTIXCdrOctet origPrimitiveSize;
} RTIXCdrPrimitiveInsParameters;

struct RTIXCdrProgram;

typedef struct RTIXCdrComplexInsParameters {
    RTIXCdrCommonInsParameters parent;
    RTIXCdrTypePlugin *typePlugin;
    struct RTIXCdrProgram *program;
    RTIXCdrBoolean baseClass;
} RTIXCdrComplexInsParameters;

typedef struct RTIXCdrMemberHeaderInsParameters {
    RTIXCdrCommonInsParameters parent;
    RTIXCdrExtendedBoolean v1ExtendedId;
    /* This field will contain the LC (length code) value for a member in a
     * mutable type
     */
    RTIXCdrOctet v2LC;
} RTIXCdrMemberHeaderInsParameters;

typedef struct RTIXCdrPrimitiveSampleInsParameters {
    RTIXCdrCommonInsParameters parent;
    RTIXCdrLong primitiveKind;
    RTIXCdrLong primitiveAlignment;
    /* The size of the primtive member */
    RTIXCdrOctet primitiveSize;
} RTIXCdrPrimitiveSampleInsParameters;

typedef struct RTIXCdrComplexSampleInsParameters {
    RTIXCdrCommonInsParameters parent;
    struct RTIXCdrProgram *program;
    /* The possible different sizes of the array member */
    RTIXCdrUnsignedLong arrayTypeSize[RTIXCdrMemberAccessInfo_NUM_TYPE_SIZES];
} RTIXCdrComplexSampleInsParameters;

typedef union RTIXCdrInsParameters {
    RTIXCdrStringInsParameters strParams;
    RTIXCdrPrimitiveInsParameters primitiveParams;
    RTIXCdrComplexInsParameters complexParams;
    RTIXCdrMemberHeaderInsParameters memberHeaderParams;
    /* Used for the Sample Interpreter */
    RTIXCdrPrimitiveSampleInsParameters primitiveSampleParams;
    RTIXCdrComplexSampleInsParameters complexSampleParams;
} RTIXCdrInsParameters;

/* 
 * Opcode structure:
 * 
 * Bit 8-4 (object to which instruction applies):
 * PrimSeq: 0xC0
 * StringSeq: 0xA0
 * WStringSeq: 0x90
 * ComplexSeq: 0x88
 * Prim: 0x40
 * String: 0x20
 * WString: 0x10
 * Complex: 0x08
 * DHEADER: 0x18
 * Member Header: 0x28
 * SENTINEL: 0x30
 * Sequences: 0x80 
 * Arrays: 0x58 
 * 
 * Bit 3-1 (operation):
 * Ser: 0x00
 * Deser: 0x01
 * Skip: 0x02
 * Init: 0x03
 * Allocated Members: 0x04
 * FinishSer: 0x05
 *
 */

#define RTI_XCDR_OPCODE_COUNT 52
#define RTI_XCDR_INVALID_OPCODE 0

#define RTI_XCDR_SER_PRIMITIVE_OPCODE 0x40
#define RTI_XCDR_DESER_PRIMITIVE_OPCODE 0x41
#define RTI_XCDR_SKIP_PRIMITIVE_OPCODE 0x42
#define RTI_XCDR_INITIALIZE_PRIMITIVE_OPCODE 0x43
#define RTI_XCDR_ALLOCATED_PRIMITIVE_OPCODE 0x44
#define RTI_XCDR_FINALIZE_PRIMITIVE_OPCODE RTI_XCDR_ALLOCATED_PRIMITIVE_OPCODE
#define RTI_XCDR_COPY_PRIMITIVE_OPCODE RTI_XCDR_ALLOCATED_PRIMITIVE_OPCODE

#define RTI_XCDR_SER_STRING_OPCODE 0x20
#define RTI_XCDR_DESER_STRING_OPCODE 0x21
#define RTI_XCDR_SKIP_STRING_OPCODE 0x22
#define RTI_XCDR_INITIALIZE_STRING_OPCODE 0x23
#define RTI_XCDR_ALLOCATED_STRING_OPCODE 0x24
#define RTI_XCDR_FINALIZE_STRING_OPCODE RTI_XCDR_ALLOCATED_STRING_OPCODE
#define RTI_XCDR_COPY_STRING_OPCODE RTI_XCDR_ALLOCATED_STRING_OPCODE

#define RTI_XCDR_SER_WSTRING_OPCODE 0x10
#define RTI_XCDR_DESER_WSTRING_OPCODE 0x11
#define RTI_XCDR_SKIP_WSTRING_OPCODE 0x12
#define RTI_XCDR_INITIALIZE_WSTRING_OPCODE 0x13
#define RTI_XCDR_ALLOCATED_WSTRING_OPCODE 0x14
#define RTI_XCDR_FINALIZE_WSTRING_OPCODE RTI_XCDR_ALLOCATED_WSTRING_OPCODE
#define RTI_XCDR_COPY_WSTRING_OPCODE RTI_XCDR_ALLOCATED_WSTRING_OPCODE

#define RTI_XCDR_SER_COMPLEX_OPCODE 0x08
#define RTI_XCDR_DESER_COMPLEX_OPCODE 0x09
#define RTI_XCDR_SKIP_COMPLEX_OPCODE 0x0A
#define RTI_XCDR_INITIALIZE_COMPLEX_OPCODE 0x0B
#define RTI_XCDR_ALLOCATED_COMPLEX_OPCODE 0x0C
#define RTI_XCDR_FINALIZE_COMPLEX_OPCODE RTI_XCDR_ALLOCATED_COMPLEX_OPCODE
#define RTI_XCDR_COPY_COMPLEX_OPCODE RTI_XCDR_ALLOCATED_COMPLEX_OPCODE

#define RTI_XCDR_SER_PRIMITIVE_SEQ_OPCODE 0xC0
#define RTI_XCDR_DESER_PRIMITIVE_SEQ_OPCODE 0xC1
#define RTI_XCDR_SKIP_PRIMITIVE_SEQ_OPCODE 0xC2
#define RTI_XCDR_INITIALIZE_PRIMITIVE_SEQ_OPCODE 0xC3
#define RTI_XCDR_ALLOCATED_PRIMITIVE_SEQ_OPCODE 0xC4
#define RTI_XCDR_FINALIZE_PRIMITIVE_SEQ_OPCODE RTI_XCDR_ALLOCATED_PRIMITIVE_SEQ_OPCODE
#define RTI_XCDR_COPY_PRIMITIVE_SEQ_OPCODE RTI_XCDR_ALLOCATED_PRIMITIVE_SEQ_OPCODE

#define RTI_XCDR_SER_STRING_SEQ_OPCODE 0xA0
#define RTI_XCDR_DESER_STRING_SEQ_OPCODE 0xA1
#define RTI_XCDR_SKIP_STRING_SEQ_OPCODE 0xA2
#define RTI_XCDR_INITIALIZE_STRING_SEQ_OPCODE 0xA3
#define RTI_XCDR_ALLOCATED_STRING_SEQ_OPCODE 0xA4
#define RTI_XCDR_FINALIZE_STRING_SEQ_OPCODE RTI_XCDR_ALLOCATED_STRING_SEQ_OPCODE
#define RTI_XCDR_COPY_STRING_SEQ_OPCODE RTI_XCDR_ALLOCATED_STRING_SEQ_OPCODE

#define RTI_XCDR_SER_WSTRING_SEQ_OPCODE 0x90
#define RTI_XCDR_DESER_WSTRING_SEQ_OPCODE 0x91
#define RTI_XCDR_SKIP_WSTRING_SEQ_OPCODE 0x92
#define RTI_XCDR_INITIALIZE_WSTRING_SEQ_OPCODE 0x93
#define RTI_XCDR_ALLOCATED_WSTRING_SEQ_OPCODE 0x94
#define RTI_XCDR_FINALIZE_WSTRING_SEQ_OPCODE RTI_XCDR_ALLOCATED_WSTRING_SEQ_OPCODE
#define RTI_XCDR_COPY_WSTRING_SEQ_OPCODE RTI_XCDR_ALLOCATED_WSTRING_SEQ_OPCODE

#define RTI_XCDR_SER_COMPLEX_SEQ_OPCODE 0x88
#define RTI_XCDR_DESER_COMPLEX_SEQ_OPCODE 0x89
#define RTI_XCDR_SKIP_COMPLEX_SEQ_OPCODE 0x8A
#define RTI_XCDR_INITIALIZE_COMPLEX_SEQ_OPCODE 0x8B
#define RTI_XCDR_ALLOCATED_COMPLEX_SEQ_OPCODE 0x8C
#define RTI_XCDR_FINALIZE_COMPLEX_SEQ_OPCODE RTI_XCDR_ALLOCATED_COMPLEX_SEQ_OPCODE
#define RTI_XCDR_COPY_COMPLEX_SEQ_OPCODE RTI_XCDR_ALLOCATED_COMPLEX_SEQ_OPCODE

#define RTI_XCDR_SER_DHEADER_OPCODE 0x18
#define RTI_XCDR_DESER_DHEADER_OPCODE 0x19
#define RTI_XCDR_SKIP_DHEADER_OPCODE 0x1A

#define RTI_XCDR_SER_SENTINEL_HEADER_OPCODE 0x30
#define RTI_XCDR_SKIP_SENTINEL_HEADER_OPCODE 0x32

#define RTI_XCDR_SER_MEMBER_HEADER_OPCODE 0x28
#define RTI_XCDR_DESER_MEMBER_HEADER_OPCODE 0x29
#define RTI_XCDR_SKIP_MEMBER_HEADER_OPCODE 0x2A

#define RTI_XCDR_INITIALIZE_SEQ_OPCODE 0x83
#define RTI_XCDR_ALLOCATED_SEQ_OPCODE 0x84
#define RTI_XCDR_FINALIZE_SEQ_OPCODE RTI_XCDR_ALLOCATED_SEQ_OPCODE
#define RTI_XCDR_COPY_SEQ_OPCODE RTI_XCDR_ALLOCATED_SEQ_OPCODE

#define RTI_XCDR_INITIALIZE_ARRAY_OPCODE 0x5B
#define RTI_XCDR_ALLOCATED_ARRAY_OPCODE 0x5C
#define RTI_XCDR_FINALIZE_ARRAY_OPCODE RTI_XCDR_ALLOCATED_ARRAY_OPCODE
#define RTI_XCDR_COPY_ARRAY_OPCODE RTI_XCDR_ALLOCATED_ARRAY_OPCODE

#define RTI_XCDR_INSTRUCTION_INVALID RTIXCdrUnsignedLong_MAX

typedef struct RTIXCdrInstruction {
    RTIXCdrOctet opcode;
    RTIXCdrInsParameters params;
} RTIXCdrInstruction;


struct RTIXCdrInlineList;


typedef enum RTIXCdrTypeProgramKind {
    RTI_XCDR_SER_PROGRAM = 0x00000001 << 0,
    RTI_XCDR_DESER_PROGRAM = 0x00000001 << 1,
    RTI_XCDR_SKIP_PROGRAM = 0x00000001 << 2,
    RTI_XCDR_GET_SER_SIZE_PROGRAM = 0x00000001 << 3,
    RTI_XCDR_GET_MAX_SER_SIZE_PROGRAM = 0x00000001 << 4,
    RTI_XCDR_GET_MIN_SER_SIZE_PROGRAM = 0x00000001 << 5,
    RTI_XCDR_SER_TO_KEY_PROGRAM = 0x00000001 << 6,
    RTI_XCDR_INITIALIZE_SAMPLE_PROGRAM = 0x00000001 << 7,
    RTI_XCDR_ALLOCATED_SAMPLE_PROGRAM = 0x00000001 << 8
} RTIXCdrTypeProgramKind;

struct RTIXCdrInstructionIndex;

/* Gets the pointer to the value pointed by an external reference.
 * For example, in modern C++ an external reference has the type:
 * dds::core::external
 *
 * This function must return the pointer associated with the value associated
 * with the external reference
 *
 * For example:
 *
 * @external int a;
 *
 * The call to RTIXCdrGetExternalRefPointerFcn will return a pointer to a
 */
typedef char * (*RTIXCdrGetExternalRefPointerFcn)(void *ref);


typedef struct RTIXCdrProgram {
    /* A program can be part of a dependentProgramList */
    struct RTIXCdrInlineListNode node;
    RTIXCdrTypeProgramKind kind;
    RTIXCdrBoolean isFlatDataProgram;
    /* 
     * RTI_XCDR_TK_NULL if the program is not for a union. The unaliased kind
     * of the discriminator otherwise
     */
    RTIXCdrTCKind unionDiscKind;
    RTIXCdrLong defaultUnionDisc;

    /* Used for the TypePlugin programs */
    RTIXCdrBoolean isCdr2;
    RTIXCdrBoolean hasBase;
    RTIXCdrBoolean isUnbounded;
    RTIXCdrExtensibilityKind extKind;
    RTIXCdrEncapsulationId encapsulationId;

    /* 
     * When used in a TypePlugin program:
     * The instruction index of the instruction that processes the
     * discriminator in union
     * 
     * When used in a Sample program:
     * The instruction of the member identified by the
     * default (implicit or explicit) label 
     */
    RTIXCdrUnsignedLong unionInsIndex;

    /* For TK_STRUCT and TK_VALUE this field conatisn the alignment of the
     * first member
     */
    RTIXCdrAlignment firstMemberAlignment;

    /* TypeCode associated with the program */
    struct RTIXCdrTypeCode *typeCode;
    /* A program can contain complex instructions that reference other programs
     * The following list contains the list of programs that can be referenced
     * by this program.
     * 
     * Usually this list is created by the top level program and provided
     * to the nested programs so that they can use it.
     * 
     * The sole purpose of the list is to avoid the creation of multiple 
     * programs for the same type.
     */
    struct RTIXCdrInlineList *dependentProgramList;
    /* Indicates if this program is the owner of the list. The list will
     * be deleted only by its owner when RTIXCdrInterpreter_deleteProgram
     * is invoked.
     */
    RTIXCdrBoolean listOwner;
    RTIXCdrUnsignedLong instructionCount;
    RTIXCdrInstruction *instructions;

    /* Instruction index by member ID */
    struct RTIXCdrInstructionIndex *instructionIndex;
    /* Instruction index by label for unions */
    struct RTIXCdrInstructionIndex *instructionIndexByLabel;

    /* member used to manipulate external refs */
    RTIXCdrUnsignedShort externalReferenceSize;
    RTIXCdrGetExternalRefPointerFcn getExternalRefPointerFcn;

    RTIXCdrBoolean isFastSerializationSupported;

    RTIXCdrBoolean serializeSentinelOnBase;
    RTIXCdrBoolean disableMustUnderstandOnSentinel;

    /* Used by getSerSampleMaxSize and getSerSampleMinSize when optimization
     * is 2. In this case, after the program is generated we run it once,
     * we cache the result here and we delete the instructions.
     *
     * The program execution will return this number
     */
    RTIXCdrUnsignedLong serSize;

    /* Indicates if a program is only for key fields */
    RTIXCdrBoolean onlyKey;
} RTIXCdrProgram;

extern RTIXCdrDllExport
void RTIXCdrInterpreter_deleteProgram(RTIXCdrProgram * me);


#define RTI_XCDR_PROGRAM_COUNT 9


typedef RTIXCdrLong RTIXCdrProgramMask;


#define RTI_XCDR_PROGRAM_MASK_NONE ((RTIXCdrProgramMask) 0)

#define RTI_XCDR_PROGRAM_MASK_TYPEPLUGIN \
( \
    RTI_XCDR_SER_PROGRAM | \
    RTI_XCDR_DESER_PROGRAM | \
    RTI_XCDR_SKIP_PROGRAM | \
    RTI_XCDR_GET_SER_SIZE_PROGRAM | \
    RTI_XCDR_GET_MAX_SER_SIZE_PROGRAM | \
    RTI_XCDR_GET_MIN_SER_SIZE_PROGRAM | \
    RTI_XCDR_SER_TO_KEY_PROGRAM \
)

#define RTI_XCDR_PROGRAM_MASK_SAMPLE \
( \
    RTI_XCDR_INITIALIZE_SAMPLE_PROGRAM | \
    RTI_XCDR_ALLOCATED_SAMPLE_PROGRAM \
)

#define RTI_XCDR_PROGRAM_MASK_ALL  ((RTIXCdrProgramMask)0xFFFFFFFF)


struct RTIXCdrSampleAssignabilityProperty {
    /* Whether or not to accept samples with unknown enumeration values */
    RTIXCdrBoolean acceptUnknownEnumValue;
    RTIXCdrBoolean acceptUnknownUnionDiscriminator;
};


#define RTIXCdrSampleAssignabilityProperty_INITIALIZER { \
    RTI_XCDR_FALSE, \
    RTI_XCDR_FALSE \
}


/* @brief Generates a type plugin program that manipulates a CDR stream
 *
 * @param tc \b In. TypeCode.
 * 
 * @param programKind \b Program kind.
 * 
 * @param littleEndianEncapsulation \b In. Indicates if the program is for
 * a little endian encapsulation or not.
 * 
 * @param v2Encapsulation \b In. Indicates if the program is for a V2
 * (XTypes 1.2) encapsulation or a V1.
 * 
 * @param onlyKey \b In. Indicates if the program must be generated for only
 * key fields.
 * 
 * @return The stream program if success. Otherwise, NULL.
 */
typedef struct RTIXCdrTypePluginProgramProperty {
    RTIXCdrBoolean littleEndianEncapsulation;
    RTIXCdrBoolean v2Encapsulation;
    RTIXCdrBoolean onlyKey;
    /* This parameter is used only when littleEndianEncapsulation is FALSE,
     * v2Encapsulation is TRUE, and onlyKey is TRUE.
     *
     * The value of this parameter determines if the program will serialize
     * the key fir keyhash generation purposes or not.
     */
    RTIXCdrBoolean onlyKeyForKeyhash;
    /* Indicates if aliases can be resolved to their most primitive type
     * for optimization purposes. If the user does not need to customize
     * the TypePlugin code for an alias, this parameter must be
     * set to RTI_XCDR_TRUE to optimize performance.
     * 
     * When this parameter is set to TRUE the following structure can be
     * serialized with a single instruction:
     * 
     * typedef LongType x;
     * 
     * struct Point {
     *     LongType x;
     *     LongType y;
     * };
     */
    RTIXCdrBoolean resolveAlias;
    /* Indicates if the processing of enumeration values can be optimized
     * by not calling the TypePlugin functions associated with the enum
     * 
     * For example:
     * 
     * enum VehicleKind {
     *     CAR,
     *     PLANE
     * };
     * 
     * struct Vehicle {
     *     VehicleKind kind;
     * };
     * 
     * With optimizing enums, the TypePlugin functions for Vehicle will call
     * the TypePlugin functions for VehicleKind to operate with enums. 
     * 
     * If the user does not require changing the TypePlugin code for the enum,
     * the program execution for Vehicle can be optimized by operating 
     * directly on the enum value without calling the enum's TyePlugin
     * functions.
     * 
     * For example, the serialization of kind with be done with a single
     * SER_PRIMITIVE instruction.
     */
    RTIXCdrBoolean optimizeEnum;
    /* Indicates if the interpreter can inline nested structs within the
     * parent struct. For example:
     * 
     * struct Point {
     *     long x;
     *     long y;
     * };
     * 
     * struct Rectangle {
     *     Point p1;
     *     Point p2;
     * };
     * 
     * With inlineStruct enabled, a Rectangle sample can be serialized with a
     * single SER_PRIMITIVE instruction for 4 longs.
     */
    RTIXCdrBoolean inlineStruct;
    /*
     * Used to force the program generation for every complex type, even when a
     * struct is inlined. This does NOT mean that structs are not inlined, but
     * that if a user requires retrieving the programs for nested complex types,
     * they will be available for lookup in the dependentPrograms list.
     * 
     * DynamicData sets this property to TRUE because member programs are
     * retrieved during the bind operation
     */
    RTIXCdrBoolean forceDependentPrograms;

    /* Indicates if the V1 sentinel for mutable types must set the
     * must understand bit
     */
    RTIXCdrBoolean disableMustUnderstandOnSentinel;
    /* Indicates if the V1 sentinel must be serialized for a base class for
     * the purposes of key serialization and keyhash generation
     */
    RTIXCdrBoolean serializeSentinelOnBase;

    /* Members required to manipulate external references */
    RTIXCdrUnsignedShort externalReferenceSize;
    RTIXCdrGetExternalRefPointerFcn getExternalRefPointerFcn;
} RTIXCdrTypePluginProgramProperty;


#define RTIXCdrTypePluginProgramProperty_INITIALIZER \
{ \
    /* littleEndianEncapsulation */ RTI_XCDR_TRUE, \
    /* v2Encapsulation */ RTI_XCDR_TRUE, \
    /* onlyKey */ RTI_XCDR_FALSE, \
    /* onlyKeyForKeyhash */ RTI_XCDR_FALSE, \
    /* resolveAlias */ RTI_XCDR_TRUE, \
    /* otpimizeEnum */ RTI_XCDR_TRUE, \
    /* inlineStruct */ RTI_XCDR_TRUE, \
    /* forceDependentPrograms */ RTI_XCDR_FALSE, \
    /* disableMustUnderstandOnSentinel */ RTI_XCDR_FALSE, \
    /* serializeSentinelOnBase */ RTI_XCDR_FALSE, \
    /* externalReferenceSize */ sizeof(char *), \
    /* getExternalRefPointerFcn */ NULL \
}

struct RTIXCdrTypePluginProgramContext {
    /* This parameter is specific to a language binding an it is provided
     * to the RTIXCdrSampleAccessInfo accessor methods
     */
    void *programData;
    /* This is the endpointPluginData parameter in the TypePlugin functions 
     * This value is opaque to the interpreter. It is needed because it needs
     * to be propagated to the TypePlugin calls for complex nested members
     */
    void *endpointPluginData;
    /* This is the endpointPluginQos parameter in the TypePlugin functions 
     * This value is opaque to the interpreter. It is needed because it needs
     * to be propagated to the TypePlugin calls for complex nested members
     */    
    void *endpointPluginQos;
    /* Indicates if the Interpreter functions must log errors due to lack of
     * space in the RTIXCdrStream
     */
    RTIXCdrBoolean logSpaceError;
    /* Indicates if the Interpreter functions must log errors due to errors that
     * are not space errors.
     */
    RTIXCdrBoolean logNonSpaceError;
    /* Indicates if there was a failure due to lack of space on XCDR stream */
    RTIXCdrBoolean spaceError;
    
    /* Pointer to the program that will have to be executed when calling
     * a TypePlugin function on a nested complex member.
     * 
     * The TopLevel type will get its program by calling:
     * RTIXCdrInterpreterPrograms_getXXXProgram
     * 
     * For complex nested members the program will be obtained from 
     * this variable.
     * 
     * This variable will be assigned by the interpreter's TypePlugin 
     * functions (for example RTIXCdrInterpreter_serializeSample) before 
     * calling TypePlugin functions for nested complex members.
     */
    RTIXCdrProgram *program;
    /* Pointer to he typeCode associated with the program above */
    struct RTIXCdrTypeCode *typeCode; 
    
    /* Used for getSerSampleSizeFnc */
    RTIXCdrEncapsulationId encapsulationId;
    /* Used by functions that can work with onlyKey members:
     * serialize
     * deserialize
     * getMaxSizeSerialized
     */
    RTIXCdrBoolean onlyKey;
    /* Used to indicate if there is an overflow when invoking the TypePlugin
     * getMaxSizeSerialized functions
     */
    RTIXCdrLong overflow;
    
    /* For the getSerSampleSize, getSerSampleMaxSize and getSerSampleMinSize
     * this pointer will be used to propagate the stream that is used to 
     * calculate the sizes downstream, as the stream is not a parameter of
     * the corresponding TypePlugin operations
     */
    RTIXCdrStream *xcdrStream;
    
    /* Indicates if we are processing a base class
     * This field is needed to not include the DHEADER field or the SENTINEL
     * when working with V1 mutable types
     */
    RTIXCdrBoolean inBaseClass;
    
    /* Indicates whether or not to use extended ID header for 
     * non-primitive fields when the encapsulation is XCDR1
     */
    RTIXCdrBoolean useXcdr1ExtendedId;

    /* Used to change range in alias of primitive values */
    struct RTIXCdrTypeCodeAnnotations *annotations;
};


#define RTIXCdrTypePluginProgramContext_INTIALIZER { \
    NULL, /* programData */ \
    NULL, /* endpointPluginData */ \
    NULL, /* endpointPluginQos */ \
    RTI_XCDR_FALSE, /* logSpaceError */ \
    RTI_XCDR_TRUE, /* logNonSpaceError */ \
    RTI_XCDR_TRUE, /* spaceError */ \
    NULL, /* program */ \
    NULL, /* typeCode */ \
    RTI_XCDR_ENCAPSULATION_ID_CDR_LE, /* encapsulationId */ \
    RTI_XCDR_FALSE, /* onlyKey */ \
    RTI_XCDR_FALSE, /* overflow */ \
    NULL, /* xcdrStream */ \
    RTI_XCDR_FALSE, /* inBaseClass */ \
    RTI_XCDR_FALSE, /* useXcdr1ExtendedId */ \
    NULL \
}

/* @brief Generates a type plugin program that manipulates a CDR stream
 *
 * @param tc \b In. TypeCode. The TypeCode should not be deleted for the 
 * duration of the program
 * 
 * @param dependentProgramList \b InOut. List of dependent programs. If this
 * parameter is NULL the program will generate a new list that will be used
 * to store dependent programs.
 * 
 * @param programKind \b In. Program kind.
 * 
 * @return The program if success. Otherwise, NULL.
 */

extern RTIXCdrDllExport
RTIXCdrProgram *RTIXCdrInterpreter_generateTypePluginProgram(
        /* The TypeCode should not be deleted for the duration of the program */
        const RTIXCdrTypeCode *tc,
        struct RTIXCdrInlineList *dependentProgramList,
        RTIXCdrTypeProgramKind programKind,
        const struct RTIXCdrTypePluginProgramProperty *property);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_serializeSample(
        struct RTIXCdrStream *me,
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_fullSerializeSample(
        RTIXCdrStream *stream,
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_fastSerializeSample(
        RTIXCdrStream *stream,
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_deserializeSample(
        void *sample,
        RTIXCdrStream *stream,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        const struct RTIXCdrSampleAssignabilityProperty *sampleAssignability,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_fullDeserializeSample(
        void *sample,
        RTIXCdrStream *stream,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        const struct RTIXCdrSampleAssignabilityProperty *sampleAssignability,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_fastDeserializeSample(
        void *sample,
        RTIXCdrStream *stream,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        const struct RTIXCdrSampleAssignabilityProperty *sampleAssignability,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_serializedSampleToKey(
        void *sample,
        RTIXCdrStream *stream,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        const struct RTIXCdrSampleAssignabilityProperty *sampleAssignability,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_fullSerializedSampleToKey(
        void *sample,
        RTIXCdrStream *stream,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        const struct RTIXCdrSampleAssignabilityProperty *sampleAssignability,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_fastSerializedSampleToKey(
        void *sample,
        RTIXCdrStream *stream,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        const struct RTIXCdrSampleAssignabilityProperty *sampleAssignability,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_skipSample(
        RTIXCdrStream *stream,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_getSerSampleSize(
        RTIXCdrUnsignedLong *size,
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_getSerSampleMaxSize(
        RTIXCdrUnsignedLong *size,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreter_getSerSampleMinSize(
        RTIXCdrUnsignedLong *size,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        struct RTIXCdrTypePluginProgramContext *context);

extern RTIXCdrDllExport
void RTIXCdrProgram_print(RTIXCdrProgram *me, const char * title);


typedef struct RTIXCdrInterpreterProgramsGenProperty {
    RTIXCdrBoolean generateV1Encapsulation;
    RTIXCdrBoolean generateV2Encapsulation;
    RTIXCdrBoolean generateLittleEndian;
    RTIXCdrBoolean generateBigEndian; 
    RTIXCdrBoolean generateWithAllFields;
    RTIXCdrBoolean generateWithOnlyKeyFields;    
    RTIXCdrBoolean resolveAlias;
    RTIXCdrBoolean optimizeEnum;    
    RTIXCdrBoolean inlineStruct;    
    RTIXCdrBoolean forceDependentPrograms;
    /* Indicates if the V1 sentinel for mutable types must set the
     * must understand bit
     */
    RTIXCdrBoolean disableMustUnderstandOnSentinel;
    /* Indicates if the V1 sentinel must be serialized for a base class for
     * the purposes of key serialization and keyhash generation
     */
    RTIXCdrBoolean serializeSentinelOnBase;
    /* Members required to manipulate external references */
    RTIXCdrUnsignedShort externalReferenceSize;
    RTIXCdrGetExternalRefPointerFcn getExternalRefPointerFcn;
} RTIXCdrInterpreterProgramsGenProperty;


#define RTIXCdrInterpreterProgramsGenProperty_INITIALIZER \
{ \
    /* generateV1Encapsulation */ RTI_XCDR_TRUE, \
    /* generateV2Encapsulation */ RTI_XCDR_TRUE, \
    /* generateLittleEndian */ RTI_XCDR_TRUE, \
    /* generateBigEndian */ RTI_XCDR_TRUE, \
    /* generateWithAllFields */ RTI_XCDR_TRUE, \
    /* generateWithOnlyKeyFields */ RTI_XCDR_TRUE, \
    /* resolveAlias */ RTI_XCDR_TRUE, \
    /* optimizeEnum */ RTI_XCDR_TRUE, \
    /* inlineStruct */ RTI_XCDR_TRUE, \
    /* forceDependentPrograms */ RTI_XCDR_FALSE, \
    /* disableMustUnderstandOnSentinel */ RTI_XCDR_FALSE, \
    /* serializeSentinelOnBase */ RTI_XCDR_FALSE, \
    /* externalReferenceSize */ sizeof(char **), \
    /* getExternalRefPointerFcn */ NULL \
}

extern RTIXCdrDllExport
int RTIXCdrInterpreterProgramsGenProperty_compare(
        const RTIXCdrInterpreterProgramsGenProperty *left,
        const RTIXCdrInterpreterProgramsGenProperty *right);

extern RTIXCdrDllExport
void RTIXCdrInterpreterProgramsGenProperty_toTypePluginProperty(
        const RTIXCdrInterpreterProgramsGenProperty *self,
        RTIXCdrTypePluginProgramProperty *tpProperty);

struct RTIXCdrInterpreterPrograms;

/* @brief Creates a program set. This program set is the owner of the programs,
 * and the responsible of creating/destroying them.
 * 
 * A program set is a set of related programs associated with an input
 * TypeCode.
 * 
 * The kind of programs contained in a program set is determined
 * by the input mask.
 * 
 * Given a program kind, the user can generate multiple versions of the 
 * program for different endianness, encapsulations, and so on. The generated
 * versions are configured using the input generation property.
 * 
 * Why do we have to generate multiple versions of a program kind?
 * 
 * For example, in the case of deserialization, this is needed because the input
 * sample maybe serialized in LITTLE endian or BIG endian. This information is
 * not known at program generation time. In this case, when the sample is
 * received, the application should pick the right version of the program by
 * looking at the encapsulation header and using the program set API: 
 * RTIXCdrInterpreterPrograms_getSerProgram
 * 
 * @param type \b In. TypeCode associated with the program set. This TypeCode
 * should have _sampleAccessInfo set for the language binding for which the
 * program are generated.
 * 
 * @param property \b In. Determine what programs to generate for a given
 * program kind. It also configures the generation optimization parameters.
 *
 * @param mask \b In. Program kinds contained in the program set.
 *
 * @return Program set if success. Otherwise, NULL.
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreterPrograms_initialize(
        struct RTIXCdrInterpreterPrograms *me,
        const RTIXCdrTypeCode *type,
        const struct RTIXCdrInterpreterProgramsGenProperty *property,
        RTIXCdrProgramMask mask);

/* @brief Creates a program set from an existing program set. The programs will
 * be loaned from the top-level programs associated to the passed parent
 * programs.
 *
 * @param tc \b In. TypeCode associated with the program set. This TypeCode
 * should have _sampleAccessInfo set for the language binding for which the
 * program are generated.
 *
 * @param parentPrograms \b In. Program set from which we will retrieve the
 * properties and the top-level programs (the owner of the programs).
 *
 * @param mask \b In. Program kinds contained in the generated program set.
 *
 * @return Program set if success. Otherwise, NULL.
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreterPrograms_initializeFromPrograms(
        struct RTIXCdrInterpreterPrograms *me,
        const RTIXCdrTypeCode *type,
        const struct RTIXCdrInterpreterPrograms *parentPrograms,
        RTIXCdrProgramMask mask);

/* @brief If the program set is the owner of the programs, releases the
 * resources associated to the programs. If the program set is not the owner,
 * this function is a noop.
 */
extern RTIXCdrDllExport
void RTIXCdrInterpreterPrograms_finalize(struct RTIXCdrInterpreterPrograms *me);

extern RTIXCdrDllExport
struct RTIXCdrInterpreterPrograms *RTIXCdrInterpreterPrograms_new(
        const RTIXCdrTypeCode *type,
        const struct RTIXCdrInterpreterProgramsGenProperty *property,
        RTIXCdrProgramMask mask);

extern RTIXCdrDllExport
void RTIXCdrInterpreterPrograms_delete(struct RTIXCdrInterpreterPrograms *me);

/*
 * @brief Assert the programs for a given program set. Programs will be either
 * retrieved from the top-level program set (potentially triggering its
 * generation as part of the top-level program set) or generated if me is
 * the owner of the programs.
 *
 * @param me Program set where we will assert the programs.
 *
 * @param mask The program kind mask. Only program kinds in the mask will be
 *        asserted.
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrInterpreterPrograms_assertPrograms(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrProgramMask mask);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getSerProgram(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean littleEndianEncapsulation,
        RTIXCdrBoolean v2Encapsulation,
        RTIXCdrBoolean onlyKey);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getSerProgramForKeyhash(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean v2Encapsulation);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getDeserProgram(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean littleEndianEncapsulation,
        RTIXCdrBoolean v2Encapsulation,
        RTIXCdrBoolean onlyKey);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getSerToKeyProgram(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean littleEndianEncapsulation,
        RTIXCdrBoolean v2Encapsulation);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getSkipProgram(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean littleEndianEncapsulation,
        RTIXCdrBoolean v2Encapsulation,
        RTIXCdrBoolean onlyKey);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getSerSizeProgram(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean v2Encapsulation,
        RTIXCdrBoolean onlyKey);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getMaxSerSizeProgram(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean v2Encapsulation,
        RTIXCdrBoolean onlyKey);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getMaxSerSizeProgramForKeyhash(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean v2Encapsulation);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getMinSerSizeProgram(
        struct RTIXCdrInterpreterPrograms *me,
        RTIXCdrBoolean v2Encapsulation,
        RTIXCdrBoolean onlyKey);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getInitializeSampleProgram(
        struct RTIXCdrInterpreterPrograms *me);

extern RTIXCdrDllExport
struct RTIXCdrProgram * RTIXCdrInterpreterPrograms_getAllocatedMembersSampleProgram(
        struct RTIXCdrInterpreterPrograms *me);

typedef struct RTIXCdrSampleProgramContext {
    /* 
     * This parameter is specific to a language binding an it is provided
     * to the RTIXCdrSampleAccessInfo accessor methods
     */
    void *programData;

    /* 
     * Members do not always a tcMemberInfo, for example, when a sequence or
     * array is a top-level type. In these cases, we need to create a
     * tcMemberInfo. This field allows us to always create the tcMemberInfo with
     * the correct value for optionality/pointers  
     */
    RTIXCdrRefMemberKind refMemberKind;

    /* 
     * Indicates whether the program needs to treat this member as though it has
     * not been processed at all yet.
     * 
     * This is used in the initialization program to indicate whether to set the
     * sample to 0 or not. It is not necessary to set a nested complex member
     * to 0 if the enclosing type has already done this work.
     * 
     * In the copy program, the top level type is copied, any nested members
     * do not need to be copied unless they are refered to through a reference
     * from the enclosing type. 
     */
    RTIXCdrBoolean isTopLevel;

    /* 
     * The sample interpreter has a program for every array. At the beginning of
     * a program we are required to check if the language binding is flat data
     * in order to get the correct offsets and sizes. Arrays, however, are not
     * required to have sample access infos. In this case, we cache the
     * language in the context so that we can still determine this information.
     * 
     * It is not required for callers of the sample interpreter programs to
     * set this value correctly. The program will set it based on the first tc's
     * sampleAccessInfo
     */ 
    RTIXCdrLanguageBinding languageBinding;
} RTIXCdrSampleProgramContext;


#define RTIXCdrSampleProgramContext_INITIALIZER { \
    NULL, /* programData */ \
    RTI_XCDR_INTERPRETER_VALUE_MEMBER, /* refMemberKind */ \
    RTI_XCDR_TRUE, /* isTopLevel */ \
    RTI_XCDR_TYPE_BINDING_INVALID /* languageBinding */\
}

/*
 * @brief Given a typecode, generate a program that will act on a user-level
 *        sample of that type.
 *
 * @param tc The typecode describing the type of the sample for which to
 *        generate the program
 * @param dependentProgramList \b InOut. List of dependent programs. If this
 *        parameter is NULL the program will generate a new list that will be
 *        used to store dependent programs.
 * @param programKind The kind of the program to generate. Currently support
 *        programs:
 *        - initialize
 *        - allocated
 * @param property Properties that may alter how a given programKind is
 *        generated
 */
extern RTIXCdrDllExport
RTIXCdrProgram *RTIXCdrInterpreter_generateSampleProgram(
        const RTIXCdrTypeCode *tc,
        struct RTIXCdrInlineList *dependentProgramList,
        RTIXCdrTypeProgramKind programKind, 
        const struct RTIXCdrTypePluginProgramProperty *property);

/*
 * @brief Initialize a sample to its default values.
 *
 * No memory currently allocated to this sample will be freed
 * (i.e. for pointer members). Finalize must be called first if the sample
 * has not just been created on the stack or the heap.
 *
 * @param sample the sample to initialize
 * @param tc the Typecode of the sample that is being initialized
 * @param program the initialize program for the sample that was generated in
 *        RTIXCdrSampleInterpreter_generateProgram
 * @param initializeToZero whether or not to initialize the sample to all zeroes
 *        before then going through and setting the members with non-zero
 *        defaults.
 *        This is set to false for flat data as flat data will set the sample
 *        contents to zero before calling the initialize program. *
 * @param context The program context. Contains the program data
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrSampleInterpreter_initializeSample(
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        RTIXCdrBoolean initializeToZero,
        RTIXCdrSampleProgramContext *context);

/*
 * @brief Initialize a range of indexes in a sequence. This method is used when
 *        resizing a sequence. This method assumes that the sequence buffer has
 *        already been allocated
 *
 * @param sample the sequence to initialize
 * @param program The sequence's program
 * @param indexBegin The index of the first member to initialize
 * @param indexEnd The index of the last member to initialize
 * @param context The program context
 *
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrSampleInterpreter_initializeSequenceMembers(
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        RTIXCdrUnsignedLong indexBegin,
        RTIXCdrUnsignedLong indexEnd,
        RTIXCdrSampleProgramContext *context);

/*
 * @brief Initialize a union to the specified discriminator
 * 
 * This method allows the initialization of a union to a case value that is not
 * the default case value.
 * 
 * @param sample the union to initialize
 * @param tc the union's typecode
 * @param program The unions's program
 * @param initializeToZero whether or not to initialize the sample to all zeroes
 *        before then going through and setting the members with non-zero
 *        defaults.
 * @param discValue The discriminator value to initialize
 * @param context The program context
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrSampleInterpreter_initializeUnion(
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        RTIXCdrBoolean initializeToZero,
        RTIXCdrLong discValue,
        RTIXCdrSampleProgramContext *context);

/*
 * @brief Finalize a sample. All memory will be released, but memory will not
 * be set to default values. the initialize program must be used for that.
 *
 * @param sample the sample to finalize
 * @param tc the Typecode of the sample that is being finalized
 * @param program the finalize program for the sample that was generated in
 *        RTIXCdrSampleInterpreter_generateProgram
 * @param discValue A specific discriminator value to finalise. This
 *        functionality is used when we're deserializing a union and we need to
 *        finalize the previously initialized union member
 * @param programData an opaque pointer that may be used in different language
 *        binding to provide language-specific program data to the program that
 *        is being run
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrSampleInterpreter_finalizeSample(
        void *sample,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        RTIXCdrLong *discValue,
        RTIXCdrSampleProgramContext *context);

/*
 * @brief Copy a sample.
 * For flat data and dynamic data, the program copies the source to the
 * destination as a single memcpy and then traverses through the nested members,
 * allocating members in the destination sample where necessary (sequences/
 * strings/optional/reference members).
 *
 *
 * @param destPt The destination sample
 * @param source The source sample
 * @param tc the Typecode of the samples that are being copied
 * @param program The copy program for this type
 * @param sourceContext The context for the source sample
 * @param destContext The context for the destination sample
 *
 */
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrSampleInterpreter_copySample(
        void *destPt,
        void *source,
        const RTIXCdrTypeCode *tc,
        const RTIXCdrProgram *program,
        RTIXCdrSampleProgramContext *sourceContext,
        RTIXCdrSampleProgramContext *destContext);


#ifdef __cplusplus
    }	/* extern "C" */
#endif


#include "xcdr/xcdr_interpreter_impl.h"

#endif /* xcdr_interpreter_h */
