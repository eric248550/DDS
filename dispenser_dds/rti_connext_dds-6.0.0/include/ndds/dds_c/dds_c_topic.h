/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_c_topic.h    generated by: makeheader    Thu Feb 28 22:12:55 2019
 *
 *		built from:	topic.ifc
 */

#ifndef dds_c_topic_h
#define dds_c_topic_h


  #ifndef dds_c_sequence_h
     #include "dds_c/dds_c_sequence.h"
  #endif
  #ifndef dds_c_infrastructure_h
    #include "dds_c/dds_c_infrastructure.h"
  #endif
  #ifndef dds_c_dll_h
#include "dds_c/dds_c_dll.h"
  #endif

#ifdef __cplusplus
    extern "C" {
#endif

struct DDS_FilterSampleInfo;

struct DDS_ExpressionProperty;

typedef struct MIGRtpsKeyHash DDS_KeyHash_t;

struct DDS_InconsistentTopicStatus {
    /*e \dref_InconsistentTopicStatus_total_count
     */
    DDS_Long total_count;

    /*e \dref_InconsistentTopicStatus_total_count_change
     */
    DDS_Long total_count_change;
};


#define DDS_InconsistentTopicStatus_INITIALIZER { 0L, 0L }

extern DDSCDllExport DDS_ReturnCode_t DDS_InconsistentTopicStatus_initialize(
    struct DDS_InconsistentTopicStatus* self);

extern DDSCDllExport DDS_ReturnCode_t DDS_InconsistentTopicStatus_copy(
    struct DDS_InconsistentTopicStatus *self,
    const struct DDS_InconsistentTopicStatus *source);

extern DDSCDllExport DDS_ReturnCode_t DDS_InconsistentTopicStatus_finalize(
    struct DDS_InconsistentTopicStatus *self);

struct DDS_TopicQos;

extern DDSCDllExport DDS_Boolean DDS_TopicQos_equals(
    const struct DDS_TopicQos *self,
    const struct DDS_TopicQos *other);

struct DDS_TopicQos {

    /*e \dref_TopicQos_topic_data
     */
    struct DDS_TopicDataQosPolicy           topic_data;

    /*e \dref_TopicQos_durability
     */
    struct DDS_DurabilityQosPolicy          durability;

    /*e \dref_TopicQos_durability_service
     */
    struct DDS_DurabilityServiceQosPolicy   durability_service;

    /*e \dref_TopicQos_deadline
     */
    struct DDS_DeadlineQosPolicy            deadline;

    /*e \dref_TopicQos_latency_budget
     */
    struct DDS_LatencyBudgetQosPolicy       latency_budget;

    /*e \dref_TopicQos_liveliness
     */
    struct DDS_LivelinessQosPolicy          liveliness;

    /*e \dref_TopicQos_reliability
     */
    struct DDS_ReliabilityQosPolicy         reliability;

    /*e \dref_TopicQos_destination_order
     */
    struct DDS_DestinationOrderQosPolicy    destination_order;

    /*e \dref_TopicQos_history
     */
    struct DDS_HistoryQosPolicy             history;

    /*e \dref_TopicQos_resource_limits
     */
    struct DDS_ResourceLimitsQosPolicy      resource_limits;

    /*e \dref_TopicQos_transport_priority
     */
    struct DDS_TransportPriorityQosPolicy   transport_priority;

    /*e \dref_TopicQos_lifespan
     */
    struct DDS_LifespanQosPolicy            lifespan;

    /*e \dref_TopicQos_ownership
     */
    struct DDS_OwnershipQosPolicy           ownership;

    /*e \dref_TopicQos_representation
    */
    struct DDS_DataRepresentationQosPolicy representation;

    /* --- Extensions: ---------------------------- */

    /*i \dref_TopicQos_protocol
    */
    struct DDS_TopicProtocolQosPolicy 	    protocol;

#ifdef RTI_CPP
    /*e 
      @brief Compares two TopicQos objects for equality
      @see DDS_TopicQos_equals
    */ 
    inline bool operator==(const DDS_TopicQos& r) const {
        if (DDS_TopicQos_equals(this, &r)) {
            return true;
        }

        return false;
    };

    /*e 
      @brief Compares two TopicQos objects for inequality
      @see DDS_TopicQos_equals
    */ 
    inline bool operator!=(const DDS_TopicQos& r) const {
        if (DDS_TopicQos_equals(this, &r)) {
            return false;
        }

        return true;
    };
#endif
};

extern DDSCDllExport DDS_ReturnCode_t DDS_TopicQos_initialize(
    struct DDS_TopicQos* self);

extern DDSCDllExport DDS_ReturnCode_t DDS_TopicQos_copy(
    struct DDS_TopicQos *self,
    const struct DDS_TopicQos *source);

extern DDSCDllExport DDS_ReturnCode_t DDS_TopicQos_finalize(
    struct DDS_TopicQos *self);


#define DDS_TopicQos_INITIALIZER   {           \
    DDS_TOPIC_DATA_QOS_POLICY_DEFAULT,         \
    DDS_DURABILITY_QOS_POLICY_DEFAULT,         \
    DDS_DURABILITY_SERVICE_QOS_POLICY_DEFAULT, \
    DDS_DEADLINE_QOS_POLICY_DEFAULT,           \
    DDS_LATENCY_BUDGET_QOS_POLICY_DEFAULT,     \
    DDS_LIVELINESS_QOS_POLICY_DEFAULT,         \
    DDS_RELIABILITY_QOS_POLICY_DEFAULT,        \
    DDS_DESTINATION_ORDER_QOS_POLICY_DEFAULT,  \
    DDS_HISTORY_QOS_POLICY_DEFAULT,            \
    DDS_RESOURCE_LIMITS_QOS_POLICY_DEFAULT,    \
    DDS_TRANSPORT_PRIORITY_QOS_POLICY_DEFAULT, \
    DDS_LIFESPAN_QOS_POLICY_DEFAULT,           \
    DDS_OWNERSHIP_QOS_POLICY_DEFAULT,          \
    DDS_DataRepresentationQosPolicy_INITIALIZER,\
    DDS_TOPIC_PROTOCOL_QOS_POLICY_DEFAULT      \
}

extern DDSCDllExport
void DDS_TopicQos_save(const struct DDS_TopicQos* self,
                       const struct DDS_TopicQos* base, 
                       struct RTIXMLSaveContext* dst);

typedef struct DDS_TopicDescriptionImpl DDS_TopicDescription;

extern DDSCDllExport const char* DDS_TopicDescription_get_type_name(
    DDS_TopicDescription* self);

extern DDSCDllExport const char* DDS_TopicDescription_get_name(
    DDS_TopicDescription* self);

extern DDSCDllExport DDS_DomainParticipant*
DDS_TopicDescription_get_participant(DDS_TopicDescription* self);

struct DDS_TopicWrapperI {
    /*i
     * Pointer to Entity supertype instance.
     */
    DDS_Entity*            _as_Entity;
    
    /*i
     * Pointer to TopicDescription supertype instance.
     */
    DDS_TopicDescription*  _as_TopicDescription;
    
    /*i
     * Pointer to opaque Topic implementation fields.
     */
    struct DDS_TopicImpl* _impl;
};

typedef struct DDS_TopicWrapperI DDS_Topic;

typedef void (*DDS_TopicListener_InconsistentTopicCallback)(
    void* listener_data,
    DDS_Topic* topic,
    const struct DDS_InconsistentTopicStatus* status);

struct DDS_TopicListener {
    /*ce \dref_TopicListener_as_listener
     */
    struct DDS_Listener as_listener;

    /*ce \dref_TopicListener_on_inconsistent_topic
     */
    DDS_TopicListener_InconsistentTopicCallback on_inconsistent_topic;
};


#define DDS_TopicListener_INITIALIZER \
{ DDS_Listener_INITIALIZER, (DDS_TopicListener_InconsistentTopicCallback)NULL}


#define DDS_Topic_as_entity(topicPtr) ((topicPtr)->_as_Entity)


#define DDS_Topic_as_topicdescription(topicPtr) \
            (topicPtr) ? ((topicPtr)->_as_TopicDescription) : NULL

extern DDSCDllExport DDS_Topic* DDS_Topic_narrow(DDS_TopicDescription* self);

extern DDSCDllExport DDS_Topic* DDS_Topic_narrow_from_entity(
    DDS_Entity* self);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_get_inconsistent_topic_status(
    DDS_Topic* self,
    struct DDS_InconsistentTopicStatus* status);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_get_inconsistent_topic_status_ex(
    DDS_Topic* self,
    struct DDS_InconsistentTopicStatus* status,
    DDS_Boolean clear_change);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_set_inconsistent_topic_statusT(
    DDS_Topic* self,
    const struct DDS_InconsistentTopicStatus* status);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_set_qos(
    DDS_Topic* self,
    const struct DDS_TopicQos* qos);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_set_qos_with_profile(
    DDS_Topic* self,
    const char *library_name,const char *profile_name);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_get_qos(
    DDS_Topic* self,
    struct DDS_TopicQos* qos);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_set_listener(
    DDS_Topic* self,
    const struct DDS_TopicListener* l, DDS_StatusMask mask);

extern DDSCDllExport struct DDS_TopicListener DDS_Topic_get_listener(
    DDS_Topic* self);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_get_listenerX(
    DDS_Topic* self, struct DDS_TopicListener* listener);

extern DDSCDllExport DDS_ReturnCode_t
DDS_Topic_get_builtin_topic_key(const DDS_Topic* self,
                                DDS_BuiltinTopicKey_t *key);

extern DDSCDllExport DDS_ReturnCode_t DDS_Topic_call_listenerT(
    DDS_Topic* self, DDS_StatusMask mask);

typedef DDS_Topic* DDS_Topic_ptr;


DDS_SEQUENCE(DDS_TopicSeq, DDS_Topic_ptr);

struct DDS_ContentFilteredTopicWrapperI {
    /*i
     * Pointer to TopicDescription supertype instance.
     */
    DDS_TopicDescription* _as_TopicDescription;
    
    /*i
     * Pointer to opaque ContentFilteredTopic implementation fields.
     */
    struct DDS_ContentFilteredTopicImpl* _impl;
};

typedef struct DDS_ContentFilteredTopicWrapperI DDS_ContentFilteredTopic;

typedef DDS_ContentFilteredTopic* DDS_ContentFilteredTopic_ptr;


DDS_SEQUENCE(DDS_ContentFilteredTopicSeq, DDS_ContentFilteredTopic_ptr);

struct DDS_TypeCode;

typedef DDS_ReturnCode_t (*DDS_ContentFilterCompileFunction)
	(void *filter_data, void** new_compile_data, const char *expression,
	 const struct DDS_StringSeq *parameters,const struct DDS_TypeCode* type_code,
	 const char* type_class_name,
	 void *old_compile_data);

typedef DDS_Boolean (*DDS_ContentFilterEvaluateFunction)
	(void *filter_data, void* compile_data, const void* sample, const struct DDS_FilterSampleInfo * meta_data);

typedef DDS_Long (*DDS_ContentFilterQueryFunction)
    (void* filter_data, void *handle);

typedef void (*DDS_ContentFilterFinalizeFunction)
	(void *filter_data, void* compile_data);

typedef void (*DDS_ContentFilterWriterFinalizeFunction)
	(void *filter_data, void* writer_filter_data,const struct DDS_Cookie_t *cookie);

typedef DDS_ReturnCode_t (*DDS_ContentFilterWriterAttachFunction)
	(void *filter_data,void ** writer_filter_data,void*reserved);

typedef void (*DDS_ContentFilterWriterDetachFunction)
	(void *filter_data,void *writer_filter_data);

typedef DDS_ReturnCode_t (*DDS_ContentFilterWriterCompileFunction)
	(void *filter_data,void *writer_filter_data,struct DDS_ExpressionProperty *prop,
    const char *expression,const struct DDS_StringSeq *parameters,
    const struct DDS_TypeCode* type_code,const char* type_class_name,const struct DDS_Cookie_t *cookie);

typedef struct DDS_CookieSeq * (*DDS_ContentFilterWriterEvaluateFunction)
	(void *filter_data, void* writer_filter_data, const void* sample,const struct DDS_FilterSampleInfo * meta_data);

typedef void (*DDS_ContentFilterWriterReturnLoanFunction)
	(void *filter_data, void* writer_filter_data, struct DDS_CookieSeq * cookies);

struct DDS_ContentFilter {

    /*ce \dref_ContentFilter_compile
     */
    DDS_ContentFilterCompileFunction compile;

    /*ce \dref_ContentFilter_writer_compile
     */
    DDS_ContentFilterWriterCompileFunction writer_compile;

    /*ce \dref_ContentFilter_evaluate
     */
    DDS_ContentFilterEvaluateFunction evaluate;

    /*ce \dref_ContentFilter_writer_evaluate
     */
    DDS_ContentFilterWriterEvaluateFunction writer_evaluate;

    /*ce \dref_ContentFilter_finalize
     */
    DDS_ContentFilterFinalizeFunction finalize;

    /*ce \dref_ContentFilter_writer_finalize
     */
    DDS_ContentFilterWriterFinalizeFunction writer_finalize;

    /*ce \dref_ContentFilter_writer_attach
     */
    DDS_ContentFilterWriterAttachFunction writer_attach;

    /*ce \dref_ContentFilter_writer_detach
     */
    DDS_ContentFilterWriterDetachFunction writer_detach;

    /*ce \dref_ContentFilter_writer_return_loan
     */
    DDS_ContentFilterWriterReturnLoanFunction writer_return_loan;

    /*ce \dref_ContentFilter_filter_data
     */
    void *filter_data;
};


#define DDS_ContentFilter_INITIALIZER { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL }


#define DDS_ContentFilteredTopic_as_topicdescription(contentFiltered) \
	((contentFiltered)->_as_TopicDescription)

extern DDSCDllExport DDS_ContentFilteredTopic*
DDS_ContentFilteredTopic_narrow(DDS_TopicDescription* self);

extern DDSCDllExport const char* DDS_ContentFilteredTopic_get_filter_expression(
    DDS_ContentFilteredTopic* self);

extern DDSCDllExport
DDS_ReturnCode_t DDS_ContentFilteredTopic_get_expression_parameters(
    DDS_ContentFilteredTopic* self,
    struct DDS_StringSeq* parameters);

extern DDSCDllExport DDS_ReturnCode_t
 DDS_ContentFilteredTopic_set_expression_parameters(
    DDS_ContentFilteredTopic* self,
    const struct DDS_StringSeq* parameters);

extern DDSCDllExport DDS_ReturnCode_t
DDS_ContentFilteredTopic_set_expression(
    DDS_ContentFilteredTopic* self,
    const char * expression,
    const struct DDS_StringSeq* parameters);

extern DDSCDllExport DDS_ReturnCode_t
 DDS_ContentFilteredTopic_append_to_expression_parameter(
    DDS_ContentFilteredTopic* self,
    const DDS_Long index,
    const char* val);

extern DDSCDllExport DDS_ReturnCode_t
 DDS_ContentFilteredTopic_remove_from_expression_parameter(
    DDS_ContentFilteredTopic* self,
    const DDS_Long index,
    const char* val);

extern DDSCDllExport DDS_Topic* DDS_ContentFilteredTopic_get_related_topic(
    DDS_ContentFilteredTopic* self);

typedef struct DDS_MultiTopicImpl DDS_MultiTopic;


#define DDS_MultiTopic_as_topicdescription(multiTopicPtr) \
            ((DDS_TopicDescription*) multiTopicPtr)

extern DDSCDllExport DDS_MultiTopic*
DDS_MultiTopic_narrow(DDS_TopicDescription* self);

extern DDSCDllExport const char* DDS_MultiTopic_get_subscription_expression(
    DDS_MultiTopic* self);

extern DDSCDllExport
DDS_ReturnCode_t DDS_MultiTopic_get_expression_parameters(
    DDS_MultiTopic* self,
    struct DDS_StringSeq* parameters);

extern DDSCDllExport DDS_ReturnCode_t DDS_MultiTopic_set_expression_parameters(
    DDS_MultiTopic* self,
    const struct DDS_StringSeq* parameters);

struct DDS_ExpressionProperty {

    /*e \dref_ExpressionProperty_key_only_filter
    */
    DDS_Boolean key_only_filter;

    /*e \dref_ExpressionProperty_writer_side_filter_optimization
    */
    DDS_Boolean writer_side_filter_optimization;
};


#define DDS_ExpressionProperty_DEFAULT { DDS_BOOLEAN_FALSE, DDS_BOOLEAN_FALSE}

struct DDS_FilterSampleInfo {
    /*e \dref_FilterSampleInfo_related_sample_identity
    */
    struct DDS_SampleIdentity_t related_sample_identity;
    /*e \dref_FilterSampleInfo_related_source_guid
     */
    struct DDS_GUID_t related_source_guid;
    /*e \dref_FilterSampleInfo_related_reader_guid
     */
    struct DDS_GUID_t related_reader_guid;
    /*i \dref_FilterSampleInfo_priority
    */
    DDS_Long priority;
};

 extern DDSCDllVariable const struct DDS_FilterSampleInfo
DDS_FILTERSAMPLEINFO_DEFAULT;

extern DDSCDllExport void 
DDS_FilterSampleInfo_initialize(struct DDS_FilterSampleInfo * self);

extern DDSCDllExport struct DDS_FilterSampleInfo* 
DDS_FilterSampleInfo_copy(
        struct DDS_FilterSampleInfo* self,
        const struct DDS_FilterSampleInfo* src);

extern DDSCDllExport DDS_Boolean
DDS_FilterSampleInfo_equals(const struct DDS_FilterSampleInfo* self,
                       const struct DDS_FilterSampleInfo* other);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* dds_c_topic_h */
