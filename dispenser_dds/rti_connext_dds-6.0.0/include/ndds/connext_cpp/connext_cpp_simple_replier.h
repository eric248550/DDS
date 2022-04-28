/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)connext_cpp_simple_replier.h    generated by: makeheader    Thu Feb 28 22:14:07 2019
 *
 *		built from:	simple_replier.ifcxx
 */

#ifndef connext_cpp_simple_replier_h
#define connext_cpp_simple_replier_h



#include <string>

#ifndef ndds_cpp_h
  #include "ndds/ndds_cpp.h"
#endif

#ifndef xmq_cpp_dll_h
  #include "connext_cpp/connext_cpp_dll.h"
#endif

// Include the declaration and implementation of ReplierImpl
#ifndef xmq_cpp_replier_details_h
  #include "connext_cpp/connext_cpp_replier_details.h"
#endif

namespace connext {

typedef ::DDS_SampleInfo ReplyInfo;

template <class TReq, class TRep>
class SimpleReplierListener;

template <class TReq, class TRep>
class SimpleReplierParams;

// --- SimpleReplier: -------------------------------------------------------------

/**
 * \dref_SimpleReplier
 */
template <typename TReq, typename TRep>
class XMQCPPDllExport SimpleReplier {
public:

    // --- types: -------------------------------------------------------------

    typedef TReq Request;
    typedef TRep Reply;
    typedef typename dds_type_traits<TRep>::DataWriter ReplyDataWriter;
    typedef typename dds_type_traits<TReq>::DataReader RequestDataReader;
    typedef SimpleReplierParams<TReq, TRep> Params;

    // --- constructor, destructor, and others : ----------------------------------------

    /**
     * \dref_SimpleReplier_new
     */
    SimpleReplier(
        DDSDomainParticipant * participant,
        const std::string& service_name,
        SimpleReplierListener<TReq, TRep> & listener);

    /**
     * \dref_SimpleReplier_new_w_params
     */
    explicit SimpleReplier(const SimpleReplierParams<TReq, TRep> & params);

    void swap(SimpleReplier & other);

    /**
     * \dref_SimpleReplier_finalize
     */
    virtual ~SimpleReplier();

    inline RequestDataReader * get_request_datareader() const;
    inline ReplyDataWriter   * get_reply_datawriter() const;

private:
    SimpleReplier(const SimpleReplier & other);
    SimpleReplier & operator = (SimpleReplier other);

    details::SimpleReplierImpl<TReq, TRep> * _pImpl;
};

template <class TReq, class TRep>
void swap(SimpleReplier<TReq, TRep> & cr1,  
          SimpleReplier<TReq, TRep> & cr2)
{
    cr1.swap(cr2);
}

} // namespace connext

/************************ SimpleReplier Implementation *************************/

namespace connext {

template <typename TReq, typename TRep>
SimpleReplier<TReq, TRep>::SimpleReplier(DDS::DomainParticipant * participant,
                                         const std::string& service_name,
                                         SimpleReplierListener<TReq, TRep> & listener) 
    : _pImpl(new details::SimpleReplierImpl<TReq, TRep>(
                    participant, service_name, &listener))
{
}

template <typename TReq, typename TRep>
SimpleReplier<TReq, TRep>::SimpleReplier(const SimpleReplierParams<TReq, TRep> & params) 
    : _pImpl(new details::SimpleReplierImpl<TReq, TRep>(params))
{
}

template <typename TReq, typename TRep>
void SimpleReplier<TReq, TRep>::swap(SimpleReplier & other)
{
    // Swapping two pointers is automic on most platfroms 
    // so I hope there is no race condition here. 
    // However, swapping two repliers do not swap their listeners. 
    // For example, consider SR=SimpleReplier and L=Listener
    // if SR1 had L1 and SR2 had L2. After swapping,
    // SR1 will callback L2 and SR2 will callback L1.
    // This is anologous to how std::vector iterators get swapped.
    std::swap(_pImpl, other._pImpl);
}

template <typename TReq, typename TRep>
SimpleReplier<TReq, TRep>::~SimpleReplier() 
{
    delete _pImpl;
}

template <typename TReq, typename TRep>
typename SimpleReplier<TReq, TRep>::ReplyDataWriter * 
SimpleReplier<TReq, TRep>::get_reply_datawriter() const
{
    return _pImpl->get_reply_datawriter();
}

template <typename TReq, typename TRep>
typename SimpleReplier<TReq, TRep>::RequestDataReader * 
SimpleReplier<TReq, TRep>::get_request_datareader() const
{
    return _pImpl->get_request_datareader();
}

} // namespace connext


#endif /* connext_cpp_simple_replier_h */
