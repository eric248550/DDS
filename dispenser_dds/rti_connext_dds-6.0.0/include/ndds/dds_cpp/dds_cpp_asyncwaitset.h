/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_cpp_asyncwaitset.h    generated by: makeheader    Thu Feb 28 22:13:03 2019
 *
 *		built from:	asyncwaitset.ifcxx
 */

#ifndef dds_cpp_asyncwaitset_h
#define dds_cpp_asyncwaitset_h


#ifndef dds_cpp_dll_h
  #include "dds_cpp/dds_cpp_dll.h"
#endif
#ifndef dds_cpp_subscription_h
  #include "dds_cpp/dds_cpp_subscription.h"
#endif
#ifndef dds_cpp_infrastructure_h
  #include "dds_cpp/dds_cpp_infrastructure.h"
#endif
#ifndef dds_c_asyncwaitset_h
  #include "dds_c/dds_c_asyncwaitset.h"
#endif

class DDSAsyncWaitSetCompletionToken;

class DDSAsyncWaitSet_impl;

class DDSCPPDllExport DDSAsyncWaitSetListener {
  // --- <<interface>> DDSAsyncWaitSetListener: -----------------------
  public:

    /*e \dref_AsyncWaitSetListener_on_thread_spawned */
    virtual void on_thread_spawned(
            RTI_UINT64 thread_id);


    /*e \dref_AsyncWaitSetListener_on_thread_deleted */
    virtual void on_thread_deleted(
            RTI_UINT64 thread_id);

    /*e \dref_AsyncWaitSetListener_on_wait_timeout */
    virtual void on_wait_timeout(
            RTI_UINT64 thread_id);

public: 

    virtual ~DDSAsyncWaitSetListener();
};

class DDSAsyncWaitSet;

class DDSAsyncWaitSetCompletionToken_impl;

class DDSCPPDllExport  DDSAsyncWaitSetCompletionToken {
    
public:
         
    /*e \dref_AsyncWaitSetCompletionToken_wait */
    virtual DDS_ReturnCode_t wait(
            const DDS_Duration_t& max_wait) = 0;    
    
    virtual DDSAsyncWaitSetCompletionToken_impl* get_impl_completion_token() = 0;

protected:    
    
    virtual ~DDSAsyncWaitSetCompletionToken();

};

class DDSCPPDllExport DDSAsyncWaitSet {
public:

    /*e \dref_AsyncWaitSet_start */
    virtual DDS_ReturnCode_t start();
    
    /*e \dref_AsyncWaitSet_start_with_completion_token */
    virtual DDS_ReturnCode_t start_with_completion_token(
            DDSAsyncWaitSetCompletionToken *completion_token);
    
    /*e \dref_AsyncWaitSet_stop */
    virtual DDS_ReturnCode_t stop();
    
    /*e \dref_AsyncWaitSet_stop_with_completion_token */
    virtual DDS_ReturnCode_t stop_with_completion_token(
            DDSAsyncWaitSetCompletionToken *completion_token);

    /*e \dref_AsyncWaitSet_attach_condition */
    virtual DDS_ReturnCode_t attach_condition(
            DDSCondition *condition);

    /*e \dref_AsyncWaitSet_detach_condition */
    virtual DDS_ReturnCode_t detach_condition(
            DDSCondition *condition);

    /*e \dref_AsyncWaitSet_attach_condition_with_completion_token */
    virtual DDS_ReturnCode_t attach_condition_with_completion_token(
            DDSCondition *condition,
            DDSAsyncWaitSetCompletionToken *completion_token);
    
    /*e \dref_AsyncWaitSet_detach_condition_with_completion_token */
    virtual DDS_ReturnCode_t detach_condition_with_completion_token(
            DDSCondition *condition,
            DDSAsyncWaitSetCompletionToken *completion_token);

    /*e \dref_AsyncWaitSet_unlock_condition
     */
    virtual DDS_ReturnCode_t unlock_condition(DDSCondition *condition);

    /*e \dref_AsyncWaitSet_get_property */
    virtual DDS_ReturnCode_t get_property(
            DDS_AsyncWaitSetProperty_t &property);

    /*e \dref_AsyncWaitSet_get_conditions */
    virtual DDS_ReturnCode_t get_conditions(
            DDSConditionSeq& attached_conditions);
    
    /*e \dref_AsyncWaitSet_create_completion_token */
    virtual DDSAsyncWaitSetCompletionToken * create_completion_token();
    
    /*e \dref_AsyncWaitSet_delete_completion_token */
    virtual DDS_ReturnCode_t delete_completion_token(
            DDSAsyncWaitSetCompletionToken *completion_token);


public:

    /*e 
     * @brief Creates a \idref_AsyncWaitSet with default property.
     */
    DDSAsyncWaitSet();

    /*e \dref_AsyncWaitSet_new */
    DDSAsyncWaitSet(
            const DDS_AsyncWaitSetProperty_t &property);
    
    /*e \dref_AsyncWaitSet_new_with_listener */
    DDSAsyncWaitSet(
            const DDS_AsyncWaitSetProperty_t &property,
            DDSAsyncWaitSetListener *listener);
    
    /*e \dref_AsyncWaitSet_new_with_thread_factory */
    DDSAsyncWaitSet(
            const DDS_AsyncWaitSetProperty_t &property,
            DDSAsyncWaitSetListener *listener,
            DDSThreadFactory *thread_factory);

    /*e \dref_AsyncWaitSet_delete */
    virtual ~DDSAsyncWaitSet();
    
public:

    /*e \dref_ASYNC_WAITSET_COMPLETION_TOKEN_USE_IMPLICIT_AND_WAIT
     */    
    static DDSAsyncWaitSetCompletionToken *const COMPLETION_TOKEN_USE_IMPLICIT_AND_WAIT;

    /*e \dref_ASYNC_WAITSET_COMPLETION_TOKEN_IGNORE
     */
    static DDSAsyncWaitSetCompletionToken *const COMPLETION_TOKEN_IGNORE;
    
protected:
    
    DDSAsyncWaitSet(DDSAsyncWaitSet_impl* impl);

private:

    DDSAsyncWaitSet_impl *_impl;
};

class DDSDataReaderStatusConditionHandler_impl;

class DDSCPPDllExport DDSDataReaderStatusConditionHandler :
                             public DDSConditionHandler {
    
public:
    
    virtual void on_condition_triggered(DDSCondition* condition);

public:

    /*e \dref_DataReaderStatusConditionHandler_new
     */
    DDSDataReaderStatusConditionHandler(
            DDSDataReader *reader,
            DDSDataReaderListener *listener,
            DDS_StatusMask listener_mask);
    
    /*e \dref_DataReaderStatusConditionHandler_delete
     */
    virtual ~DDSDataReaderStatusConditionHandler();
    
protected:
    
    DDSDataReaderStatusConditionHandler();
    
private:    
    
    DDSDataReaderStatusConditionHandler_impl *_impl;
};

#endif /* dds_cpp_asyncwaitset_h */
