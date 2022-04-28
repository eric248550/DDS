/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
(c) Copyright, Real-Time Innovations, 2014-2017.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
============================================================================= */

#ifndef xcdr_stream_h
#define xcdr_stream_h


#include "xcdr/xcdr_dll.h"
#include "xcdr/xcdr_infrastructure.h"


#ifdef __cplusplus
    extern "C" {
#endif

/* The maximum size of a CDR stream
 *
 * We subtract 1024 because the core does some operations
 * on the returned result that may end up adding some additional bytes
 *
 */
#define RTI_XCDR_MAX_SERIALIZED_SIZE (RTIXCdrLong_MAX-1024)

typedef RTIXCdrUnsignedShort RTIXCdrEncapsulationId;

#define RTI_XCDR_ENCAPSULATION_ID_CDR_BE     0x0000
#define RTI_XCDR_ENCAPSULATION_ID_CDR_LE     0x0001
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR_BE  0x0002
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR_LE  0x0003
#define RTI_XCDR_ENCAPSULATION_ID_CDR2_BE    0x0006
#define RTI_XCDR_ENCAPSULATION_ID_CDR2_LE    0x0007
#define RTI_XCDR_ENCAPSULATION_ID_D_CDR2_BE  0x0008
#define RTI_XCDR_ENCAPSULATION_ID_D_CDR2_LE  0x0009
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR2_BE  0x000a
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR2_LE  0x000b

#ifdef RTI_ENDIAN_LITTLE
#define RTI_XCDR_ENCAPSULATION_ID_CDR_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_CDR_LE
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_PL_CDR_LE
#define RTI_XCDR_ENCAPSULATION_ID_CDR2_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_CDR2_LE
#define RTI_XCDR_ENCAPSULATION_ID_D_CDR2_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_D_CDR2_LE
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR2_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_PL_CDR2_LE
#else
#define RTI_XCDR_ENCAPSULATION_ID_CDR_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_CDR_BE
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_PL_CDR_BE
#define RTI_XCDR_ENCAPSULATION_ID_CDR2_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_CDR2_BE
#define RTI_XCDR_ENCAPSULATION_ID_D_CDR2_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_D_CDR2_BE
#define RTI_XCDR_ENCAPSULATION_ID_PL_CDR2_NATIVE_ENDIAN RTI_XCDR_ENCAPSULATION_ID_PL_CDR2_BE
#endif

#define RTI_XCDR_ENCAPSULATION_HEADER_SIZE 4

struct RTIXCdrStreamState;

/*
 * The number of entries in the RTIXCdr_TCKind_g_primitiveSizes array so that
 * we can index into the array to get a primitve type's size without calling a
 * function and having to do a switch
 */
#define DDS_TK_NUM_PRIMITIVE_SIZES 23

/*
 * The sizes of primitive kinds in CDR, NOT in a language binding
 * 1st dimension: v1 or v2
 * 2nd dimension: memberKind
 */
extern RTIXCdrDllVariable const RTIXCdrUnsignedLong 
RTIXCdr_TCKind_g_primitiveCdrSizes[2][DDS_TK_NUM_PRIMITIVE_SIZES];

/*
 * The alignments of primitive kinds in CDR, NOT in a language binding
 * 1st dimension: v1 or v2
 * 2nd dimension: memberKind
 */
extern RTIXCdrDllVariable const RTIXCdrAlignment
RTIXCdr_TCKind_g_primitiveCdrAlignments[2][DDS_TK_NUM_PRIMITIVE_SIZES];

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrEncapsulationId_isCdr(
        RTIXCdrEncapsulationId encapsulationId);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrEncapsulationId_isCdrV2(
        RTIXCdrEncapsulationId encapsulationId);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrEncapsulationId_isLittleEndianCdr(
        RTIXCdrEncapsulationId encapsulationId);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrEncapsulationId_isBigEndianCdr(
        RTIXCdrEncapsulationId encapsulationId);

/*
 * Returns the encapsulation Id that corresponds to the plain (non-PL) CDR
 * version 2 with the native endianness
 */
extern RTIXCdrDllExport
RTIXCdrEncapsulationId RTIXCdrEncapsulationId_getNativePlainCdr2();

/*
 * Returns the encapsulation Id that corresponds to the PL CDR
 * version 2 with the native endianness
 */
extern RTIXCdrDllExport
RTIXCdrEncapsulationId RTIXCdrEncapsulationId_getNativePlCdr2();

typedef RTIXCdrOctet RTIXCdrEndian;

struct RTIXCdrStream;

extern RTIXCdrDllExport
void RTIXCdrStream_init(struct RTIXCdrStream *me);

extern RTIXCdrDllExport
void RTIXCdrStream_initWithBuffer(
        struct RTIXCdrStream *me,
        char *buffer,
        RTIXCdrUnsignedLong bufferLength);

extern RTIXCdrDllExport
void RTIXCdrStream_set(
        struct RTIXCdrStream *me,
        char *buffer,
        RTIXCdrUnsignedLong bufferLength);

extern RTIXCdrDllExport
RTIXCdrEncapsulationId RTIXCdrStream_getEncapsulationId(
        struct RTIXCdrStream *me);

extern RTIXCdrDllExport
void RTIXCdrStream_setEncapsulationId(
        struct RTIXCdrStream *me,
        RTIXCdrEncapsulationId encapsulationId);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serializeAndSetCdrEncapsulation(
        struct RTIXCdrStream *me,
        RTIXCdrEncapsulationId encapsulationId);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serializeAndSetCdrEncapsulationWithEndianness(
        struct RTIXCdrStream *me,
        RTIXCdrEncapsulationId encapsulationId,
        RTIXCdrBoolean littleEndian);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserializeAndSetCdrEncapsulation(
        struct RTIXCdrStream *me);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_checkSize(
        struct RTIXCdrStream *me,
        RTIXCdrUnsignedLong size);

extern RTIXCdrDllExport
RTIXCdrUnsignedLong RTIXCdrStream_getCurrentPositionOffset(
        struct RTIXCdrStream *me);

extern RTIXCdrDllExport
char * RTIXCdrStream_resetAlignment(struct RTIXCdrStream *me);

extern RTIXCdrDllExport
void RTIXCdrStream_restoreAlignment(struct RTIXCdrStream *me, char *position);

extern RTIXCdrDllExport
char * RTIXCdrStream_getCurrentPosition(struct RTIXCdrStream *me);

extern RTIXCdrDllExport
void RTIXCdrStream_setCurrentPosition(
        struct RTIXCdrStream *me, 
        char *position);

extern RTIXCdrDllExport
void RTIXCdrStream_increaseCurrentPosition(
        struct RTIXCdrStream *me,
        RTIXCdrUnsignedLong count);

extern RTIXCdrDllExport
char *RTIXCdrStream_getBuffer(struct RTIXCdrStream *me);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serializeCdrEncapsulationDefault(
        struct RTIXCdrStream *me);

extern RTIXCdrDllExport
RTIXCdrUnsignedLong RTIXCdrStream_getRemainder(struct RTIXCdrStream *me);

extern RTIXCdrDllExport
void RTIXCdrStream_initFromStream(
        struct RTIXCdrStream *me, 
        struct RTIXCdrStream *srcStream);

/*
 * Primitive-type serialization
 */

extern RTIXCdrDllExport
void RTIXCdrStream_serializeWcharFast(
        struct RTIXCdrStream *me,
        const RTIXCdrWchar *in,
        RTIXCdrBoolean v1);

extern RTIXCdrDllExport
void RTIXCdrStream_deserializeWcharFast(
        struct RTIXCdrStream *me,
        const RTIXCdrWchar *in,
        RTIXCdrBoolean v1);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serialize1ByteFast(
        struct RTIXCdrStream *me,
        const RTIXCdr1Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserialize1ByteFast(
        struct RTIXCdrStream *me,
        RTIXCdr1Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serialize2ByteFast(
        struct RTIXCdrStream *me,
        const RTIXCdr2Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserialize2ByteFast(
        struct RTIXCdrStream *me,
        RTIXCdr2Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serialize4ByteFast(
        struct RTIXCdrStream *me,
        const RTIXCdr4Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserialize4ByteFast(
        struct RTIXCdrStream *me,
        RTIXCdr4Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serialize8ByteFast(
        struct RTIXCdrStream *me,
        const RTIXCdr8Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserialize8ByteFast(
        struct RTIXCdrStream *me,
        RTIXCdr8Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serialize16ByteFast(
        struct RTIXCdrStream *me,
        const RTIXCdr8Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserialize16ByteFast(
        struct RTIXCdrStream *me,
        RTIXCdr8Byte *in);

extern RTIXCdrDllExport  
RTIXCdrUnsignedLong RTIXCdrStream_getCurrentPositionOffset(
        struct RTIXCdrStream *me);

extern RTIXCdrDllExport        
RTIXCdrBoolean RTIXCdrStream_checkSize(
        struct RTIXCdrStream *me,
        RTIXCdrUnsignedLong size);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserializeNByte(
        struct RTIXCdrStream *me,
        RTIXCdr1Byte *in,
        RTIXCdrAlignment alignment,
        RTIXCdrUnsignedLong count);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serializeNByte(
        struct RTIXCdrStream *me,
        const RTIXCdr1Byte *in,
        RTIXCdrAlignment alignment,
        RTIXCdrUnsignedLong count);

extern RTIXCdrDllExport   
RTIXCdrBoolean RTIXCdrStream_align(
        struct RTIXCdrStream *me,
        RTIXCdrAlignment alignment);

extern RTIXCdrDllExport
void RTIXCdrStream_serializeWchar(
        struct RTIXCdrStream *me,
        RTIXCdrBoolean* result,
        const RTIXCdrWchar *in,
        RTIXCdrBoolean v1);

extern RTIXCdrDllExport
void RTIXCdrStream_deserializeWchar(
        struct RTIXCdrStream *me,
        RTIXCdrBoolean* result,
        const RTIXCdrWchar *in,
        RTIXCdrBoolean v1);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serialize1Byte(
        struct RTIXCdrStream *me,
        const RTIXCdr1Byte *in);

extern RTIXCdrDllExport             
RTIXCdrBoolean RTIXCdrStream_serialize2Byte(
        struct RTIXCdrStream *me,
        const RTIXCdr2Byte *in,
        RTIXCdrBoolean align);

extern RTIXCdrDllExport             
RTIXCdrBoolean RTIXCdrStream_serialize4Byte(
        struct RTIXCdrStream *me,
        const RTIXCdr4Byte *in,
        RTIXCdrBoolean align);

extern RTIXCdrDllExport 
RTIXCdrBoolean RTIXCdrStream_serialize8Byte(
        struct RTIXCdrStream *me,
        const RTIXCdr8Byte *in,
        RTIXCdrBoolean align,
        RTIXCdrAlignment alignment);

extern RTIXCdrDllExport 
RTIXCdrBoolean RTIXCdrStream_serializePrimitiveArray(
        struct RTIXCdrStream *me,
        const void *in,
        RTIXCdrBoolean align,
        RTIXCdrAlignment alignment,
        RTIXCdrUnsignedLong elementSize,
        RTIXCdrUnsignedLong length);

extern RTIXCdrDllExport         
RTIXCdrBoolean RTIXCdrStream_serializePrimitiveSequence(
    struct RTIXCdrStream *me,
    const void *in,
    RTIXCdrUnsignedLong length,
    RTIXCdrUnsignedLong maximumLength,
    RTIXCdrAlignment alignment,
    RTIXCdrUnsignedLong elementSize);
        
extern RTIXCdrDllExport   
RTIXCdrBoolean RTIXCdrStream_deserialize1Byte(
        struct RTIXCdrStream *me,
        RTIXCdr1Byte *in);

extern RTIXCdrDllExport         
RTIXCdrBoolean RTIXCdrStream_deserialize2Byte(
        struct RTIXCdrStream *me,
        RTIXCdr2Byte *in,
        RTIXCdrBoolean align);

extern RTIXCdrDllExport   
RTIXCdrBoolean RTIXCdrStream_deserialize4Byte(
        struct RTIXCdrStream *me,
        RTIXCdr4Byte *in,
        RTIXCdrBoolean align);

extern RTIXCdrDllExport   
RTIXCdrBoolean RTIXCdrStream_deserialize8Byte(
        struct RTIXCdrStream *me,
        RTIXCdr8Byte *in,
        RTIXCdrBoolean align,
        RTIXCdrAlignment alignment);

extern RTIXCdrDllExport 
RTIXCdrBoolean RTIXCdrStream_deserialize16Byte(
        struct RTIXCdrStream *me,
        RTIXCdr16Byte *in,
        RTIXCdrBoolean align,
        RTIXCdrAlignment alignment);

extern RTIXCdrDllExport 
RTIXCdrBoolean RTIXCdrStream_deserializePrimitiveArray(
        struct RTIXCdrStream *me,
        void *out,
        RTIXCdrBoolean align,
        RTIXCdrAlignment alignment,
        RTIXCdrUnsignedLong elementSize,
        RTIXCdrUnsignedLong length);

extern RTIXCdrDllExport        
RTIXCdrBoolean RTIXCdrStream_deserializePrimitiveSequence(
    	struct RTIXCdrStream *me,
    	void *out,
    	RTIXCdrUnsignedLong *length,
    	RTIXCdrUnsignedLong maximumLength,
    	RTIXCdrAlignment alignment,
    	RTIXCdrUnsignedLong elementSize);
   		 
extern RTIXCdrDllExport      		 
RTIXCdrBoolean RTIXCdrStream_skipPrimitiveArray(
    struct RTIXCdrStream *me,
    RTIXCdrBoolean align,
    RTIXCdrAlignment alignment,
    RTIXCdrUnsignedLong elementSize,
    RTIXCdrUnsignedLong length);   		

extern RTIXCdrDllExport     
RTIXCdrBoolean RTIXCdrStream_skipPrimitiveSequence (
    struct RTIXCdrStream *me,
    RTIXCdrUnsignedLong *length,
    RTIXCdrAlignment alignment,
    RTIXCdrUnsignedLong elementSize);
        
extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_skipNByte(
        struct RTIXCdrStream *me,
        RTIXCdrAlignment alignment,
        RTIXCdrUnsignedLong count);

/* Align and does not check size */
extern RTIXCdrDllExport
void RTIXCdrStream_alignFast(
        struct RTIXCdrStream *me,
        RTIXCdrAlignment alignment);

extern RTIXCdrDllExport
void RTIXCdrStream_skipNByteNoCheckSize(
        struct RTIXCdrStream *me,
        RTIXCdrAlignment alignment,
        RTIXCdrUnsignedLong count);

extern RTIXCdrDllExport
RTIXCdrUnsignedLong RTIXCdrStream_getRelativeCurrentPositionOffset(
        struct RTIXCdrStream *me);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serializeUnsignedShortToBigEndianFast(
        struct RTIXCdrStream *me,
        const RTIXCdr2Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserializeUnsignedShortFromBigEndianFast(
        struct RTIXCdrStream *me,
        RTIXCdr2Byte *in);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_skipWString(
    struct RTIXCdrStream *me);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_serializeDHeaderLength(
        struct RTIXCdrStream *stream,
        char *dHeaderPosition);

extern RTIXCdrDllExport
char * RTIXCdrStream_serializeDHeader(
        struct RTIXCdrStream *stream);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_deserializeDHeader(
        struct RTIXCdrStream *stream,
        RTIXCdrUnsignedLong *size,
        char **dheaderPosition,
        struct RTIXCdrStreamState *state);

/* \brief Serializes a V2 mutable member HEADER
 *
 * The function returns the position that will contain the member length when
 * LC is 4. Otherwise, the function returns NULL.
 *
 * The user has to call RTIXCdrStream_finishV2ParameterHeader only when the
 * returned position is different than NULL.
 */
extern RTIXCdrDllExport
char * RTIXCdrStream_serializeV2ParameterHeader(
        struct RTIXCdrStream *me,
        RTIXCdrBoolean *failure,
        RTIXCdrUnsignedLong parameterId,
        RTIXCdrBoolean mustUnderstand,
        RTIXCdrUnsignedLong LC);

extern RTIXCdrDllExport
void RTIXCdrStream_finishV2ParameterHeader(
    struct RTIXCdrStream *me,
    char *lengthPosition);

extern RTIXCdrDllExport
void RTIXCdrStream_popState(
        struct RTIXCdrStream *me,
        const struct RTIXCdrStreamState *state);

extern RTIXCdrDllExport
RTIXCdrEncapsulationId RTIXCdrEncapsulation_getAppendableCdrEncapsulationId(
        RTIXCdrEncapsulationId plainCdrEncapsulationId);

extern RTIXCdrDllExport
RTIXCdrBoolean RTIXCdrStream_findV2MutableSampleMember(
        struct RTIXCdrStream *stream,
        RTIXCdrUnsignedLong searchMemberId,
        RTIXCdrUnsignedLong *sizeOut);

#define RTI_XCDR_ENDIAN_BIG (0)
#define RTI_XCDR_ENDIAN_LITTLE (1)


#ifdef __cplusplus
    }   /* extern "C" */
#endif


#include "xcdr/xcdr_stream_impl.h"

#endif /* xcdr_stream_h */
