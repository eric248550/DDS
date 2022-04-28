/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)mig_generator.h    generated by: makeheader    Thu Feb 28 22:12:16 2019
 *
 *		built from:	generator.ifc
 */

#ifndef mig_generator_h
#define mig_generator_h


  #ifndef osapi_ntptime_h
    #include "osapi/osapi_ntptime.h"
  #endif
  #ifndef reda_buffer_h
    #include "reda/reda_buffer.h"
  #endif
  #ifndef netio_common_h
    #include "netio/netio_common.h"
  #endif
  #ifndef mig_dll_h
    #include "mig/mig_dll.h"
  #endif
  #ifndef mig_rtps_h
    #include "mig/mig_rtps.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct RTIClock;

struct REDAWorker;

struct REDAWeakReference;

struct RTINetioSender;

struct REDAWorkerFactory;

struct RTINetioSenderDestinationGroup;

struct MIGGenerator;

struct MIGGeneratorSampleInlineParams {
    struct REDABuffer params;

    struct REDAFastBufferPool *paramsPool;

    struct RTICdrStream *paramsStream;

    RTI_INT32 signatureOffset;

    /*i Used for timestamp only */
    RTI_UINT32 _bitmap;
};

struct MIGSerializedData {
    RTIEncapsulationId encapsulationId;
    struct REDABuffer serializedData;
};


  #define MIG_SERIALIZED_DATA_DEFAULT { \
    RTI_CDR_ENCAPSULATION_ID_CDR_NATIVE, /* encapsulationId */ \
    REDA_BUFFER_INVALID, /* serializedData buffer */ \
  }

struct MIGGeneratorSample {
    /*e \brief Sequence number assigned to the sample; this will be the "key" */
    struct REDASequenceNumber sn;
    /*e \brief Virtual sn */
    /* For batches is the first sn in the batch */
    struct REDASequenceNumber vSn;
    /*e \brief Sequence number of first sample in set to which this sample
      belongs; will be UNKNOWN if this sample does not belong to a set */
    struct REDASequenceNumber setFirstSn;
    /*e \brief For CST use only */
    struct MIGRtpsKeyHash objectKeyHash;
    /*e \brief time when sample created; optional */
    struct RTINtpTime timestamp;
    /*e \brief directed reader GUID; optional */
    struct MIGRtpsGuid readerGuid;
    /*e \brief sample deadline (time when sample created + writer latency budget); optional */
    struct RTINtpTime deadline;
    /*e \brief publication priority; optional */
    RTI_INT32 publicationPriority;
    /*e \brief Issue/Var flags */
    char flags;
    /*e \brief Var status info */
    MIGRtpsStatusInfo statusInfo; /*RTPS.2.0*/
    /*e \brief application-reference "cookie"
    */
    struct REDABuffer cookie;
    /*e \brief encapsulated serialized data
    */
    struct MIGSerializedData *serializedData; /* array */
    /*e
    */
    int cachedEncapsulationIdIndex;
    /*e \brief convenience-ref to writer-side user data 
    */
    void *data;
    /*e Raw user data (include user parameters as well),
      serialized and aligned STRONG reference.
    */
    struct REDABuffer userData;
    /*e \brief Raw protocol parameters,
      serialized and aligned STRONG reference. */
    struct REDABuffer protocolParameters;
    /*e \brief CDR Stream used to encode the
         protocol parameters. Passed from the highest
        layer that allocated the protocol buffer
     */
    struct RTICdrStream *protocolStream;
    /*e \brief Fastbuffer pool used to allocate
        and free buffers to store protocol parameters
        from. Passed from the layer the allcated the
        protocol buffer
     */
    struct REDAFastBufferPool *protocolPool;

    /*e \brief mutable inline qos. 
    */
    struct REDABuffer *mutableParameters;
    /*e \brief immutable inline qos. 
    requested by stateless readers 
    that expect all inline qos. */
    struct REDABuffer *expectedParameters;
    /*e \brief flag indicating whether reader 
    expects all inline qos. 
    */
    RTIBool useExpectedInlineQos;
    /*e \brief location of the first signature in the
     * inline parameter. This is used to
     * rewrite the signature in case an issue needs
     * to be resent. The reaosn for adding this variable
     * is to speed up the rewrite. The alternative is
     * to not rewrite (not very useful) and to search
     * for it (more overhead).
     */
    RTI_INT32 signatureOffset;

    /*i Used for timestamp only */
    RTI_UINT32 _bitmap;

    /*e \brief extra flags of data submessage 
    */
    MIGRtpsDataFlags extraFlags;

    /*e \brief location where all COMMEND inline-params 
        are serialized after.  Corresponds to length
        of PRES inline-params. 
    */
    RTI_INT32 inlineQosOffset;

    struct RTINtpTime keepDurationStart;

    /*----- Batching related fields ---- */
    /*e \brief Batch sample count */
    RTI_UINT32 batchSampleCount;

    /*e \brief Sequence number offset to the last sample in the batch */
    RTI_UINT32 batchSnOffset;

    struct REDABuffer singleBatchSampleInfoData;
    /*e \brief Sample info data. 
       There is one buffer per encapsulation.
       If there is only one encapsulation batchSampleInfoData = &singleBatchSampleInfoData
    */
    struct REDABuffer * batchSampleInfoData;

    /* ---- Session related fields ---- */
    RTI_INT32 sessionId;

    /* --- Locator directed write field --- */
    /* When this list is not empty the writer will write to the specified locators */
    /* This field is only used by AnonWriters for now */
    struct REDAInlineList locatorList;

    /*i Set to true if the sample was reassembled from fragments */
    RTIBool reassembledSample;
};


#define MIG_SESSION_ID_UNKNOWN (-2)


  #define MIG_GENERATOR_SAMPLE_DEFAULT { \
     REDA_SEQUENCE_NUMBER_UNKNOWN, /* sn */ \
     REDA_SEQUENCE_NUMBER_UNKNOWN, /* vsn */ \
     REDA_SEQUENCE_NUMBER_UNKNOWN, /* setFirstSn */ \
     MIG_RTPS_KEY_HASH_DEFAULT, /* objectKeyHash */ \
     RTI_NTP_TIME_ZERO, /* timestamp */ \
     MIG_RTPS_GUID_UNKNOWN, /* readerGuid */ \
     RTI_NTP_TIME_ZERO, /* deadline */ \
     0, /* publicationPriority */ \
     MIG_RTPS_NO_FLAG, /* flags */ \
     MIG_RTPS_NO_STATUS_INFO, /* statusInfo */ \
     {0, NULL}, /* cookie */ \
     NULL, /* serializedData */ \
     0, /* cachedIdIndex */ \
     NULL, /* data */ \
     {0, NULL}, /* userData */ \
     {0, NULL}, /* protocolParameters */ \
     NULL, /* protocolStream */ \
     NULL, /* protocolPool */ \
     NULL, /*mutableParameters*/ \
     NULL, /*expectedParameters*/ \
     RTI_FALSE, /*useExpectedInlineQos*/ \
     0, /* signatureOffset */ \
     0, /* bitmap */ \
     MIG_RTPS_DATA_FLAGS_NONE, /* extraFlags */ \
     0, /* inlineQosOffset */ \
     RTI_NTP_TIME_ZERO, /* keepDurationStart */ \
     1, /* batchSampleCount */ \
     0, /* batchSnOffset */ \
     {0,NULL}, /* singleBatchSampleInfoData */ \
     NULL, /* batchSampleInfoData */ \
     MIG_SESSION_ID_UNKNOWN, /* sessionId */ \
     REDA_INLINE_LIST_EMPTY, /* locator list */ \
     RTI_FALSE /* reassembledSample */ \
}

extern MIGDllExport RTIBool
MIGGeneratorSample_set(struct MIGGeneratorSample *me,
                       const struct REDASequenceNumber *sn,
                       const struct REDASequenceNumber * setFirstSn,
                       const struct REDASequenceNumber * firstSnInBatch, /* RTPS.2.1 */
                       RTI_UINT32 batchOffsetSn, /* RTPS.2.1 */
                       const struct MIGRtpsKeyHash *srcKeyHash,
                       const struct RTINtpTime *timestamp,
                       const struct MIGRtpsGuid *readerGuid,
                       char flags, 
                       MIGRtpsDataFlags extraFlags,
                       MIGRtpsStatusInfo statusInfo,
                       const struct REDABuffer *userData,
                       const struct REDABuffer *parameter,
                       const struct REDABuffer *mutableParameter,
                       const struct REDABuffer *expectedParameter,
                       const struct REDABuffer *batchSampleInfo /* RTPS.2.1 */,
                       const struct MIGSerializedData *serializedData);


#define  MIGGeneratorSample_setParameterLength(__sampleParams,__length) \
(__sampleParams)->length = (__length)


#define  MIGGeneratorSample_getParameterLength(__sample) \
(__sample)->protocolParameters.length


#define  MIGGeneratorSample_getExpectedParameterLength(__sample) \
(__sample)->expectedParameters->length


#define  MIGGeneratorSample_setExpectedParameterLength(__sample,__length) \
(__sample)->expectedParameters->length = (__length)


#define  MIGGeneratorSample_adjustParameterLength(__sampleParam,__delta) \
(__sampleParam)->length += (__delta)


#define  MIGGeneratorSample_adjustExpectedParameterLength(__sample,__delta) \
(__sample)->expectedParameters->length += (__delta)


#define  MIGGeneratorSample_initializeInlineParameter(__sample,__pool,__stream) \
(__sample)->protocolPool = (__pool); \
(__sample)->protocolStream = (__stream);


#define  MIGGeneratorSample_setParameterStream(__sample,__stream) \
(__sample)->protocolStream = (__stream)


#define  MIGGeneratorSample_getParameterStream(__sample) \
(__sample)->protocolStream

extern MIGDllExport RTIBool
MIGGeneratorSample_isValid(const struct MIGGeneratorSample *me,
                           int encapsulationIndex);

extern MIGDllExport RTIBool
MIGGeneratorSample_isTimestamped(const struct MIGGeneratorSample *me);

extern MIGDllExport int MIGGeneratorSample_compare(const void *l,
						   const void *r);

extern MIGDllExport void
MIGGeneratorSample_copy(struct MIGGeneratorSample *me,
			const struct MIGGeneratorSample *src);

struct MIGGeneratorForwarder;

typedef RTIBool
(*MIGGenerator_EncodeFunction)(
    struct MIGGeneratorForwarder *forwarder,
    struct REDABuffer *encodedBuffer,
    const struct REDABuffer *plainBuffers,
    int plainBufferCount,
    MIGRtpsObjectId senderOid,
    const void *localInterceptorHandle,
    const struct REDAInlineList *remoteEntityInterceptorHandleList,
    struct REDAWorker *worker);

struct MIGGeneratorForwarder {
    MIGGenerator_EncodeFunction encode;
};


struct MIGInterceptorHandleNode {
    struct REDAInlineListNode node;
    void *interceptorHandle;
};


struct MIGInterceptorHandles {
    struct MIGInterceptorHandleNode *endpoint;
    struct MIGInterceptorHandleNode *participant;
};


struct MIGInterceptorHandlesGroup {

    /*
     * These nodes are in the directed lists of the sender. The directed lists
     * are used to encode content directed to specific receivers.
     */
    struct MIGInterceptorHandles directed;

    /*
     * These nodes are in the matched lists of the sender. The matched lists
     * are used to encode content sent to all matched receivers.
     */
    struct MIGInterceptorHandles matched;
};


  #define MIGInterceptorHandleNode_INITIALIZER { \
      REDAInlineListNode_INITIALIZER, /* node */ \
      NULL /* interceptorHandle */ \
  }
  #define MIGInterceptorHandles_INITIALIZER { \
      NULL, /* endpoint */ \
      NULL /* participant */ \
  }
  #define MIGInterceptorHandlesGroup_INITIALIZER { \
      MIGInterceptorHandles_INITIALIZER, /* directed */ \
      MIGInterceptorHandles_INITIALIZER /* matched */ \
  }

struct MIGGeneratorSecurityProperty {
    /*e \brief Whether or not to call encode_xxx_submessage for a particular
        submessage. This is mostly configured by the user through security
        attributes, but some builtin endpoints must have this set to a certain
        value.
     */
    RTIBool encodeSubmessage;
    /*e \brief Whether or not to call encode_rtps_message for a particular
        message. This is mostly configured by the user through a security
        attribute, but some builtin endpoints must have this set to a certain
        value.
     */
    RTIBool encodeRtpsMessage;
    /*e
     * \brief Whether or not to alter a byte of the data before flushing it
     *  out. Used for testing purposes to test the effects of tainting data
     *  after MAC is computed.
     */
    RTIBool taintData;

    /*e \brief Represents the local key material used to encode a submessage.
     */
    void *interceptorHandle;
    /*e
     * \brief Represents the remote key material list used to encode a
     *  submessage. This list includes all matched remote endpoints.
     */
    struct REDAInlineList matchedRemoteEndpointInterceptorHandleList;
    /*e
     * \brief Represents the remote key material list used to encode a
     *  message. This list includes all matched remote participants.
     */
    struct REDAInlineList matchedRemoteParticipantInterceptorHandleList;
    /*e
     * \brief Represents the remote key material list used to encode a
     *  submessage. This list includes only the remote endpoints towards which
     *  this specific submessage is directed.
     */
    struct REDAInlineList directedRemoteEndpointInterceptorHandleList;
    /*e
     * \brief Represents the remote key material list used to encode a
     *  message. This list includes only the remote participants towards which
     *  this specific message is directed.
     */
    struct REDAInlineList directedRemoteParticipantInterceptorHandleList;

    /*e
     * \brief If true, then we clear the
     * directedRemoteEndpoint/ParticipantInterceptorHandleLists in
     * beginMessage.
     */
    RTIBool clearDirectedInterceptorHandleLists;
};


  #define MIG_GENERATOR_SECURITY_PROPERTY_DEFAULT { \
      RTI_FALSE, /* encodeSubmessage */\
      RTI_FALSE, /* encodeRtpsMessage */\
      RTI_FALSE, /* taintData */ \
      NULL, /* interceptorHandle */ \
      REDA_INLINE_LIST_EMPTY, /* matchedRemoteEndpointInterceptorHandleList */ \
      REDA_INLINE_LIST_EMPTY, /* matchedRemoteParticipantInterceptorHandleList */ \
      REDA_INLINE_LIST_EMPTY, /* directedRemoteEndpointInterceptorHandleList */ \
      REDA_INLINE_LIST_EMPTY, /* directedRemoteParticipantInterceptorHandleList */ \
      RTI_TRUE /* clearDirectedInterceptorHandleLists */ \
  }

#define MIG_GENERATOR_SECURITY_ENCODE_BUFFER_MAX_SIZE         65535

extern MIGDllExport
void MIGGeneratorSecurityProperty_removeDirectedInterceptorHandles(
        struct MIGGeneratorSecurityProperty *self);

extern MIGDllExport
void MIGGeneratorSecurityProperty_assertDirectedInterceptorHandles(
        struct MIGGeneratorSecurityProperty *self,
        struct MIGInterceptorHandles *interceptorHandles);

extern MIGDllExport
void MIGGeneratorSecurityProperty_removeRemoteEndpoint(
        struct MIGGeneratorSecurityProperty *self,
        const struct MIGInterceptorHandlesGroup *interceptorHandles);

extern MIGDllExport
void MIGGeneratorSecurityProperty_assertRemoteEndpoint(
        struct MIGGeneratorSecurityProperty *self,
        const struct MIGInterceptorHandlesGroup *interceptorHandles);


typedef void
(*MIGGeneratorListener_OnBeforeEndSubmessageFunction)(
        /* inouts */
        void *listenerData,
        struct REDABuffer *buffers,
        /* inputs */
        const int bufferCount,
        const MIGRtpsSubmessageId submessageId,
        const struct MIGRtpsGuid *senderGuid);


typedef void
(*MIGGeneratorListener_OnBeforeFlushFunction)(
        /* inouts */
        void *listenerData,
        struct REDABuffer *buffers,
        /* inputs */
        const int bufferCount,
        const struct MIGRtpsGuidPrefix *senderParticipantId);


typedef void
(*MIGGeneratorListener_OnAfterFlushFunction)(
        /* inouts */
        void *listenerData,
        struct REDABuffer *buffers,
        /* input */
        const int bufferCount,
        const struct MIGRtpsGuidPrefix *senderParticipantId);


struct MIGGeneratorListener {
    void *listenerData;

    MIGGeneratorListener_OnBeforeEndSubmessageFunction
            onBeforeEndSubmessage;
    MIGGeneratorListener_OnBeforeFlushFunction
            onBeforeFlush;
    MIGGeneratorListener_OnAfterFlushFunction
            onAfterFlush;
};


  #define MIGGeneratorListener_INITIALIZER { \
    NULL, /* listenerData */ \
    NULL, /* onBeforeEndSubmessage */ \
    NULL, /* onBeforeFlush */ \
    NULL /* onAfterFlush */ \
  }

struct MIGGeneratorProperty {
    /*e \brief Total gather buffer count to use to form the message.

      The generator needs
      the maximum iovec count supported across the transports.  Must be
      greater than or equal to
       NDDS_Transport_Property_t#gatherSendBuffercountMax for all
      transport to be used.
    */
    int gatherSendBufferCountMax;

    /*e \brief The smallest maximum message size supported
        by all transport plugin instances 
    */
    int transportMessageSize;

    /*e \brief Specifies if RTPS CRC32 checksum needs to be sent
        Used to allow computation of RTPS packet statistics at receiver.
    */
    RTIBool crcEnabled;

    /* corruptionDuration is used for testing purposes. Set in seconds. */
    int corruptionDuration;

    /*e preallocate a buffer to store output of encode_xxx_submessage */
    RTIBool canEncodeSubmessage;

    /*e preallocate a buffer to store output of encode_rtps_message */
    RTIBool canEncodeRtpsMessage;

    /*e \brief The maximum overhead in bytes introduced by
     *  encode_xxx_submessage
     */
    int encodedSubmessageMaxOverhead;

    /*e \brief The maximum overhead in bytes introduced by
     *  encode_rtps_message
     */
    int encodedMessageMaxOverhead;

    /*e \brief functions to forward to PRES. */
    struct MIGGeneratorForwarder *forwarder;
};


  #define MIG_GENERATOR_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT (128)
  #define MIG_GENERATOR_TRANSPORT_MESSAGE_SIZE_MAX_DEFAULT \
      (MIG_GENERATOR_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT*MIG_RTPS_SUBMESSAGE_HEADER_SIZE_MAX)


  #define MIG_GENERATOR_PROPERTY_DEFAULT { \
    MIG_GENERATOR_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT, \
    MIG_GENERATOR_TRANSPORT_MESSAGE_SIZE_MAX_DEFAULT, \
    RTI_FALSE, /* crcEnabled */ \
    0, /* corruptionDuration */ \
    RTI_FALSE, /* canEncodeSubmessage */ \
    RTI_FALSE, /* canEncodeRtpsMessage */ \
    0, /* encodedSubmessageMaxOverhead */ \
    0, /* encodedMessageMaxOverhead */ \
    NULL /* forwarder */ \
  }

extern MIGDllExport struct MIGGenerator *
MIGGenerator_new(MIGRtpsHostId hostId, MIGRtpsAppId appId, 
                 MIGRtpsInstanceId instanceId, /*RTPS.2.0*/
		 struct RTINetioSender *sender,
		 const struct MIGGeneratorProperty *property,
		 struct RTIClock *clock,
		 struct REDAWorkerFactory *workerFactory);

extern MIGDllExport void MIGGenerator_delete(struct MIGGenerator *me,
                                             struct REDAWorker *worker);


extern	MIGDllExport void MIGGenerator_setListener(
        struct MIGGenerator *me,
        const struct MIGGeneratorListener *listener);

struct MIGGeneratorWorkerStat {
    /* begin message generation. */
    struct RTINtpTime timeBegun;
    /* generator handed over the formed message to  RTINetioSender. */
    struct RTINtpTime timeFinished;
};

extern MIGDllExport RTIBool
MIGGeneratorWorkerStat_init(struct REDAWorkerFactory *workerFactory);

extern MIGDllExport void
MIGGeneratorWorkerStat_finalize(struct REDAWorkerFactory *workerFactory,
                                struct REDAWorker *worker);


  #define MIG_GENERATOR_STAT_STRING_LENGTH (46)

extern MIGDllExport char *
MIGGeneratorWorkerStat_toString(const void *me, struct REDABuffer *buffer);

typedef enum {
    /*e use this machine's own endianness, as defined by RTI_ENDIAN_LITTLE
      define during compile time. */
    MIG_GENERATOR_ENDIAN_UNKNOWN = -1,
    /*e Use big endian, regardless of the machine's true endianness */
    MIG_GENERATOR_ENDIAN_BIG     =  0,
    /*e Use little endian, regardless of the machine's true endianness */
    MIG_GENERATOR_ENDIAN_LITTLE  =  1
} MIGGeneratorEndian;

extern MIGDllExport RTIBool MIGGenerator_beginMessage(
    struct MIGGenerator *me, MIGGeneratorEndian endian,
    const struct RTINetioSenderDestinationGroup *destinationGroup,
    const struct REDAWeakReference *destinationArray, int destinationCount,
    int transportPriority, const struct MIGGeneratorSecurityProperty *security,
    struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_finishMessage(struct MIGGenerator *me, struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_finishExtMessage(struct MIGGenerator *me, struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_setEndian(struct MIGGenerator *me,
		       MIGGeneratorEndian endian, struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addAck(struct MIGGenerator *me, int *size, char flags,
		    MIGRtpsObjectId readerObjectId,
		    const struct MIGRtpsGuid *writerGuidIn,
		    const struct MIGRtpsBitmap *bitmap,
            REDAEpoch epoch,
            MIGAckKind ackKind,
		    struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addNackFrag(struct MIGGenerator *me, char flags,
                     MIGRtpsObjectId readerObjectId,
                     const struct MIGRtpsGuid *writerGuidIn,
                     const struct REDASequenceNumber *sequenceNumber,
                     const struct MIGRtpsBitmap *bitmap,
                     REDAEpoch epoch,
                     struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addGap(struct MIGGenerator *me, 
                    int *size, char flags,
		    const struct MIGRtpsGuid *readerGuidIn,
		    MIGRtpsObjectId writerObjectId,
		    const struct REDASequenceNumber *sequenceNumber,
		    const struct MIGRtpsBitmap *bitmap,
		    struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addHeartbeat(struct MIGGenerator *me, char flags,
			  const struct MIGRtpsGuid *readerGuidIn,
			  MIGRtpsObjectId writerObjectId,
			  const struct REDASequenceNumber *firstSequenceNumber,
			  const struct REDASequenceNumber *lastSequenceNumber,
              const struct REDASequenceNumber *firstVirtualSequenceNumber,
              const struct REDASequenceNumber *lastVirtualSequenceNumber,
              REDAEpoch epoch, 
              MIGHeartbeatKind hbKind,
			  struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addHeartbeatFrag(struct MIGGenerator *me, char flags,
                          const struct MIGRtpsGuid *readerGuidIn,
                          MIGRtpsObjectId writerObjectId,
                          const struct REDASequenceNumber *sequenceNumber,
                          RTI_UINT32 lastFragmentNum,
                          REDAEpoch epoch,
                          struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addHeartbeatVirtual(struct MIGGenerator *me, 
                                 char flags,
                                 const struct MIGRtpsGuid *readerGuidIn,
                                 MIGRtpsObjectId writerObjectId,
                                 struct MIGRtpsWriterInfoList *writerInfoList,
                                 REDAEpoch epoch,
                                 struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addInfoDestination(struct MIGGenerator *me,
                                char flags,
                                const struct MIGRtpsGuidPrefix *destGuidPrefix, /*RTPS.2.0*/
                                struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addData(struct MIGGenerator *me,
                     int *size,
                     const struct MIGRtpsGuid *readerGuidIn,
                     MIGRtpsObjectId writerObjectId,
                     const struct MIGGeneratorSample *sample,
                     int encapsulationIndex,
                     struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addDataSession(
    struct MIGGenerator *me,
    int *size,
    const struct MIGRtpsGuid *readerGuidIn,
    MIGRtpsObjectId writerObjectId,
    const struct MIGGeneratorSample *sample,
    int encapsulationIndex,
    struct REDAWorker *worker);

extern MIGDllExport RTIBool
MIGGenerator_addDataBatch(struct MIGGenerator *me,
                          int *size,
                          const struct MIGRtpsGuid *readerGuidIn,
                          MIGRtpsObjectId writerObjectId,
                          const struct MIGGeneratorSample *sample,
                          int encapsulationIndex,
                          struct REDAWorker *worker);

extern MIGDllExport RTIBool MIGGenerator_addDataFrag(
             struct MIGGenerator *me,
             int *size,
	     const struct MIGRtpsGuid *readerGuidIn,
	     MIGRtpsObjectId writerObjectId,
	     const struct MIGGeneratorSample *sample,
	     int numFragsToAdd,
	     int firstFragNumber,
	     int fragSize,
	     int *numFragsAdded,
             RTIBool use43DataFragFormat,
             int encapsulationIndex,
	     struct REDAWorker *worker);

extern MIGDllExport 
RTIBool MIGGenerator_addAppAck(
                           struct MIGGenerator *me,
                           char flags, 
                           MIGRtpsObjectId readerObjectId,
                           const struct MIGRtpsGuid * writerGuidIn,
                           struct MIGRtpsAppAck * appAck,
                           struct REDAWorker *worker);

extern MIGDllExport
RTIBool MIGGenerator_addAppAckConf(struct MIGGenerator *me,
                           char flags, 
                           const struct MIGRtpsGuid * readerGuidIn,
                           MIGRtpsObjectId writerObjectId,
                           struct MIGRtpsAppAck * appAck,
                           struct REDAWorker *worker);

extern MIGDllExport
void MIGGenerator_getGuidPrefix(
        struct MIGGenerator *me,
        struct MIGRtpsGuidPrefix *guidPrefix);

extern MIGDllExport
void MIGGenerator_getProperty(
        struct MIGGenerator *me,
        struct MIGGeneratorProperty *property);

extern MIGDllExport
void MIGGenerator_setProperty(
        struct MIGGenerator *me,
        const struct MIGGeneratorProperty *property);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "mig/mig_generator_impl.h"

#endif /* mig_generator_h */
