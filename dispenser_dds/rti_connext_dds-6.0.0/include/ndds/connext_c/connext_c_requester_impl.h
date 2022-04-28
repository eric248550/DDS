/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)connext_c_requester_impl.h    generated by: makeheader    Thu Feb 28 22:14:06 2019
 *
 *		built from:	requester_impl.ifc
 */

#ifndef connext_c_requester_impl_h
#define connext_c_requester_impl_h



#include "clock/clock_interface.h"

#include "ndds/ndds_c.h"

#include "connext_c/connext_c_dll.h"
#include "connext_c/connext_c_untyped_impl.h"
#include "connext_c/connext_c_requester.h"


extern XMQCDllExport
DDS_ReturnCode_t RTI_Connext_RequesterParams_to_RTI_Connext_EntityParams(
    const RTI_Connext_RequesterParams* self,
    RTI_Connext_EntityParams* toParams);

extern XMQCDllExport
RTI_Connext_RequesterUntypedImpl* RTI_Connext_RequesterUntypedImpl_create(
    const RTI_Connext_RequesterParams * params,
    RegisterTypeFunc _request_type_fnc,
    const char * request_type_name,
    RegisterTypeFunc _reply_type_fnc,
    const char * reply_type_name,
    int reply_size);

extern XMQCDllExport
DDS_ReturnCode_t RTI_Connext_RequesterUntypedImpl_delete(
    RTI_Connext_RequesterUntypedImpl* self);

extern XMQCDllExport
DDS_ReturnCode_t RTI_Connext_RequesterUntypedImpl_wait_for_replies(
    RTI_Connext_RequesterUntypedImpl * self,
    const struct DDS_Duration_t * max_wait,
    int min_sample_count,
    const struct DDS_SampleIdentity_t* related_request_info);

extern XMQCDllExport
DDS_ReturnCode_t RTI_Connext_RequesterUntypedImpl_get_reply_loaned(
    RTI_Connext_RequesterUntypedImpl * self,
    void *** received_data,
    int * data_count,
    DDS_Boolean* is_loan,
    void* dataSeqContiguousBuffer,
    struct DDS_SampleInfoSeq* info_seq,
    DDS_Long data_seq_len,
    DDS_Long data_seq_max_len,
    DDS_Boolean ownership,
    DDS_Long max_samples,
    const struct DDS_SampleIdentity_t* related_request_id,
    RTIBool take);

typedef struct FooBarRequesterImpl FooBarRequesterImpl;

extern XMQCDllExport
FooBarRequesterImpl* FooBarRequesterImpl_create(
    const RTI_Connext_RequesterParams* params);

extern XMQCDllExport
void FooBarRequesterImpl_delete();

extern XMQCDllExport
DDS_DataWriter* RTI_Connext_RequesterUntypedImpl_get_request_datawriter(
    RTI_Connext_RequesterUntypedImpl * self);

extern XMQCDllExport
DDS_DataReader* RTI_Connext_RequesterUntypedImpl_get_request_datareader(
    RTI_Connext_RequesterUntypedImpl * self);

#endif /* connext_c_requester_impl_h */