/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)pres_common_impl.h    generated by: makeheader    Thu Feb 28 22:12:33 2019
 *
 *		built from:	common_impl.ifc
 */

#ifndef pres_common_impl_h
#define pres_common_impl_h


#ifdef __cplusplus
    extern "C" {
#endif



/* RTPS spec - PB + DG*domainId + dX */ 
#define PRESRtps_getWellKnownMulticastPort(domain_id, port_base, domain_id_gain, port_offset) \
    ((port_base) + ((domain_id_gain)*(domain_id)) + (port_offset))

/* RTPS spec - PB + DG*domainId + PG*participantId + dX */ 
#define PRESRtps_getWellKnownUnicastPort(domain_id, participant_id, port_base, domain_id_gain, participant_id_gain, port_offset) \
    ((port_base) + ((domain_id_gain)*(domain_id)) + ((participant_id_gain)*(participant_id)) + (port_offset))

/* --------------------------------------------------------- */
  #define PRESGroupSuffix_fromObjectSuffix(osx) \
    (( \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_USER_WRITER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_USER_READER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_RESERVED_USER_WRITER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_RESERVED_USER_READER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_META_WRITER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_META_READER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_RESERVED_META_WRITER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_RESERVED_META_READER_GROUP) || \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_USER_VIRTUAL_READER_GROUP) \
     ) ? \
      ((PRESGroupSuffix)(osx)) : /* valid topic suffix, cast and return */ \
      (PRES_GROUP_SUFFIX_UNKNOWN_GROUP) /* not valid topic suffix */ \
    )

/* --------------------------------------------------------- */
  #define PRESGroupSuffix_getRWType(osx) \
    (((osx) & 0x0F) == 0x08 ? MIG_RTPS_RW_TYPE_WRITER : \
    (((osx) & 0x0F) == 0x09 ? MIG_RTPS_RW_TYPE_READER : \
    (((osx) == PRES_GROUP_SUFFIX_NORMAL_USER_VIRTUAL_READER_GROUP) ? \
     MIG_RTPS_RW_TYPE_READER : MIG_RTPS_RW_TYPE_UNKNOWN)))

/* --------------------------------------------------------- */
  #define PRESTopicSuffix_fromObjectSuffix(osx) \
    (( \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_USER_TOPIC) || \
      ((osx) == MIG_RTPS_OBJECT_RESERVED_USER_TOPIC) || \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_META_TOPIC) || \
      ((osx) == MIG_RTPS_OBJECT_RESERVED_META_TOPIC) || \
      ((osx) == MIG_RTPS_OBJECT_NORMAL_USER_VIRTUAL_TOPIC) \
     ) ? \
      ((PRESTopicSuffix)(osx)) : /* valid topic suffix, cast and return */ \
      (PRES_TOPIC_SUFFIX_UNKNOWN_TOPIC) /* not valid topic suffix */ \
    )

/* --------------------------------------------------------- */
  #define PRESTopicSuffix_isTopic(osx) \
    ((PRESTopicSuffix_fromObjectSuffix(osx) != \
        PRES_TOPIC_SUFFIX_UNKNOWN_TOPIC) ? \
        RTI_TRUE : RTI_FALSE)
/* --------------------------------------------------------- */
  #define PRESIeeeTime_compare(time1, time2) \
    ((((time1).sec) > ((time2).sec)) ? 1 : \
     ((((time1).sec) < ((time2).sec)) ? -1 : \
      ((((time1).nanosec) > ((time2).nanosec)) ? 1 : \
       ((((time1).nanosec) < ((time2).nanosec)) ? -1 : 0))))

/* --------------------------------------------------------- */
  #define PRESEntity_isEnabled(entity) \
    ((entity).state == PRES_ENTITY_STATE_ENABLED)

/* --------------------------------------------------------- */
  #define PRESEntity_isDestroyed(entity) \
    ((entity).state == PRES_ENTITY_STATE_DESTROYED)

/* --------------------------------------------------------- */
 #define PRESReducedLocatorQosPolicy_asLocatorQosPolicy(qos) \
        ((struct PRESLocatorQosPolicy *) (qos))

/* --------------------------------------------------------- */
 #define PRESReducedLocatorQosPolicy_copy(to, from) \
        (PRESLocatorQosPolicy_copy( \
                PRESReducedLocatorQosPolicy_asLocatorQosPolicy(to), \
                PRESReducedLocatorQosPolicy_asLocatorQosPolicy(from)))

/* --------------------------------------------------------- */
 #define PRESReducedLocatorQosPolicy_compare(left, right) \
        (PRESLocatorQosPolicy_compare( \
                PRESReducedLocatorQosPolicy_asLocatorQosPolicy(left), \
                PRESReducedLocatorQosPolicy_asLocatorQosPolicy(right)))

/* --------------------------------------------------------- */
  #define PRESResourceLimitQos_limitExceeded(maximal, x) \
    (((maximal) >= 0) && (((x) < 0) || ((x) > (maximal))))

/* --------------------------------------------------------- */
  #define PRESResourceLimitQos_limitReached(maximal, x) \
    (((maximal) >= 0) && (((x) < 0) || ((x) >= (maximal))))

/* --------------------------------------------------------- */
  #define PRESCookie_fromBuffer(cookie, buffer) \
      (cookie)->data._maximum = (buffer)->length; \
      (cookie)->data._length = (buffer)->length; \
      (cookie)->data._buffer = (RTICdrOctet *)((buffer)->pointer);

/* --------------------------------------------------------- */
  #define PRESCookie_toBuffer(cookie, buffer) \
     (buffer)->length = (cookie)->data._length; \
     (buffer)->pointer = (char *)((cookie)->data._buffer);

/* --------------------------------------------------------- */
  #define PRESAckResponse_fromBuffer(ackresp, buffer) \
      (ackresp)->data._maximum = (buffer)->length; \
      (ackresp)->data._length = (buffer)->length; \
      (ackresp)->data._buffer = (RTICdrOctet *)((buffer)->pointer);

/* --------------------------------------------------------- */
  #define PRESAckResponse_toBuffer(ackresp, buffer) \
     (buffer)->length = (ackresp)->data._length; \
     (buffer)->pointer = (char *)((ackresp)->data._buffer);

/* --------------------------------------------------------- */
  #define PRESOctetGuid_isUnknown PRESOctetGuid_isZero
  #define PRESOctetGuid_setUnknown PRESOctetGuid_setZero

#define PRES_GmClassId_toServiceId(gmClassId) \
( \
  (strcmp(gmClassId, PRES_GMCLASSID_TRUST_AUTH_HANDSHAKE) == 0) \
    ? (PRES_GMCLASSID_SERVICE_ID_TRUST_AUTH_HANDSHAKE) \
    : ((strcmp(gmClassId, PRES_GMCLASSID_TRUST_AUTH_REQUEST) == 0) \
      ? (PRES_GMCLASSID_SERVICE_ID_TRUST_AUTH_REQUEST) \
      : ((strcmp(gmClassId, PRES_GMCLASSID_TRUST_RTI_AUTH_REQUEST) == 0) \
        ? (PRES_GMCLASSID_SERVICE_ID_TRUST_RTI_AUTH_REQUEST) \
        : ((strcmp(gmClassId, PRES_GMCLASSID_TRUST_PARTICIPANT_INTERCEPTOR_STATE) == 0) \
          ? (PRES_GMCLASSID_SERVICE_ID_TRUST_PARTICIPANT_CRYPTO_TOKENS) \
          : ((strcmp(gmClassId, PRES_GMCLASSID_TRUST_DATAWRITER_INTERCEPTOR_STATE) == 0) \
            ? (PRES_GMCLASSID_SERVICE_ID_TRUST_DATAWRITER_CRYPTO_TOKENS) \
            : ((strcmp(gmClassId, PRES_GMCLASSID_TRUST_DATAREADER_INTERCEPTOR_STATE) == 0) \
              ? (PRES_GMCLASSID_SERVICE_ID_TRUST_DATAREADER_CRYPTO_TOKENS) \
              : (PRES_GMCLASSID_SERVICE_ID_UNKNOWN)))))) \
)

#define PRES_ServiceId_toGmClassId(serviceId) \
( \
  (serviceId == PRES_GMCLASSID_SERVICE_ID_TRUST_AUTH_HANDSHAKE) \
    ? (PRES_GMCLASSID_TRUST_AUTH_HANDSHAKE) \
    : ((serviceId == PRES_GMCLASSID_SERVICE_ID_TRUST_AUTH_REQUEST) \
      ? (PRES_GMCLASSID_TRUST_AUTH_REQUEST) \
      : ((serviceId == PRES_GMCLASSID_SERVICE_ID_TRUST_RTI_AUTH_REQUEST) \
        ? (PRES_GMCLASSID_TRUST_RTI_AUTH_REQUEST) \
        : ((serviceId == PRES_GMCLASSID_SERVICE_ID_TRUST_PARTICIPANT_CRYPTO_TOKENS) \
          ? (PRES_GMCLASSID_TRUST_PARTICIPANT_INTERCEPTOR_STATE) \
          : ((serviceId == PRES_GMCLASSID_SERVICE_ID_TRUST_DATAWRITER_CRYPTO_TOKENS) \
            ? (PRES_GMCLASSID_TRUST_DATAWRITER_INTERCEPTOR_STATE) \
            : ((serviceId == PRES_GMCLASSID_SERVICE_ID_TRUST_DATAREADER_CRYPTO_TOKENS) \
              ? (PRES_GMCLASSID_TRUST_DATAREADER_INTERCEPTOR_STATE) \
              : ("UNKNOWN")))))) \
)

#define PRESDataHolder_isNil(dataHolder) \
( \
  ((dataHolder).classId == NULL) \
   && ((dataHolder).properties._length == 0) \
   && ((dataHolder).binaryProperties._length == 0) \
)


typedef RTIOsapiHash PRESSampleHash;


#define PRES_SAMPLE_HASH_NIL RTI_OSAPI_HASH_NIL

#define PRESSampleHash_initialize(x) RTIOsapiHash_initialize(x)

#define PRESSampleHash_copy(a, b) RTIOsapiHash_copy(a, b)

#define PRESSampleHash_equals(a, b) RTIOsapiHash_equals(a, b)

#define PRESSampleHash_compare(a, b) RTIOsapiHash_compare(a, b)

#define PRESSampleHash_reset(x) RTIOsapiHash_reset(x)

#define PRESSampleHash_isValid(x) RTIOsapiHash_isValid(x)

#define PRESSampleHash_length(x) RTIOsapiHash_length(x)

#define PRESSampleHash_value(x) RTIOsapiHash_value(x)

#define PRESSampleHash_print(a) RTIOsapiHash_print(a)

#define PRESSampleHash_computeMd5(hash, buff, size) \
    RTIOsapiHash_computeMd5(hash, buff, size)

#define PRESSampleHash_computeScatterMd5(hash, buff, size, elementSize) \
    RTIOsapiHash_computeScatterMd5(hash, buff, size, elementSize)


#define PRES_SAMPLE_SIGNATURE_MAX_LENGTH 512 /* 512 bytes */
#define PRES_SAMPLE_SIGNATURE_FLAG_NONE                                      0
#define PRES_SAMPLE_SIGNATURE_FLAG_IGNORE                           (0x01 << 0)


struct PRESSampleSignature {
    RTI_UINT64 epoch;
    RTI_UINT32 nonce;
    RTI_UINT32 length;
    RTI_UINT8 signature[PRES_SAMPLE_SIGNATURE_MAX_LENGTH];
    RTI_UINT8 flags;
};


#define PRES_SAMPLE_SIGNATURE_INVALID { \
    0, /* epoch */\
    0, /* nonce */\
    0, /* length */\
    {0}, /* signature */ \
    0 /* flags */ \
}

#define PRESSampleSignature_isIgnoreFlagSet(s) \
    (((s)->flags & PRES_SAMPLE_SIGNATURE_FLAG_IGNORE) != 0)

extern PRESDllExport
void PRESSampleSignature_print(
        const struct PRESSampleSignature *signature,
        const char *desc,
        unsigned int indent);

extern PRESDllExport
RTIBool PRESSampleSignatureUtil_marshallSampleSignatureDataI(
        struct REDABuffer *dataToSign,
        RTI_UINT64 epoch,
        RTI_UINT32 nonce,
        MIGRtpsStatusInfo statusInfo,
        const PRESSampleHash *sampleHash);

typedef struct PRESTrustedState {
    RTI_UINT64 participantDiscoveryDataEpoch;
    RTI_UINT32 participantDiscoveryDataNonce;
    PRESSampleHash participantDiscoveryDataHash;
} PRESTrustedState;


#define PRES_TRUSTED_STATE_NONCE_INVALID 0
#define PRES_TRUSTED_STATE_INVALID { \
    0, \
    PRES_TRUSTED_STATE_NONCE_INVALID, \
    PRES_SAMPLE_HASH_NIL}

extern PRESDllExport
RTIBool PRESTrustedState_marshallSignatureDataI(
        const PRESTrustedState *self,
        struct REDABuffer *outputBuffer);

typedef struct {
    MIGRtpsVendorId vendorId;
    struct PRESProductVersion productVersion;
} PRESTrustedParticipantInfo;


#define PRES_TRUSTED_PARTICIPANT_INFO_INVALID { \
    MIG_RTPS_VENDOR_ID_UNKNOWN, \
    PRES_PRODUCT_VERSION_DEFAULT \
}



#define PRESSequenceOctet_isEmpty(seq) \
    ((seq)._length == 0 \
    || (seq)._buffer == NULL)



#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* pres_common_impl_h */
