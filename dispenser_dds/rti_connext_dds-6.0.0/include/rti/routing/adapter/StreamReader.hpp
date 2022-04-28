/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_STREAM_READER_HPP_
#define RTI_ROUTING_ADAPTER_STREAM_READER_HPP_

#include <vector>

#include <dds/core/SafeEnumeration.hpp>
#include <dds/sub/status/DataState.hpp>
#include <dds/core/InstanceHandle.hpp>
#include <dds/core/types.hpp>
#include <dds/topic/Filter.hpp>
#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/routing/UpdatableEntity.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace adapter {

class SelectorState;

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::StreamReader
 *
 * @brief Provides a way to read samples of a specific type from a data domain.
 * In the XML configuration file, StreamReaders are associated with the tag 
 * &lt;input&gt; within &lt;route&gt; and &lt;auto_route&gt;.
 *
 * @mtsafety Partially Safe
 *           All operations on a concrete StreamReader objects are safe and
 *           always serialized on a given Session. Operations on different 
 *           StreamReader objects can be called concurrently if the
 *           StreamReader objects belong to different Sessions.
 */
class StreamReader : public UpdatableEntity{

public:    
    typedef void* SamplePtr;
    typedef void* InfoPtr;

    /**
     * @brief Takes a collection of all data samples and info samples available
     * from an input stream.
     *
     * When \product is done using the samples, it will 'return the loan' to the
     * StreamReader by calling StreamReader::return_loan. Note that multiple
     * calls to this operation can be made before returning the loans.
     *
     * The samples provided with this operation are considered 'removed'
     * from the StreamReader cache, and they shall no longer be returned by
     * subsequent StreamReader::take or StreamReader::read operations.
     *
     * This operation represents the minimum required behavior by \product
     * in order to forward data.
     *
     * @param sample_seq
     *        @rs_st_inout Vector that will hold the output samples. \product
     *        provides this vector to the StreamReader to fill. For each call,
     *        the size of the vector is zero.
     *        The data representation associated with the samples will be given
     *        by the value of TypeInfo::data_representation_kind that is
     *        part of the StreamInfo object passed at StreamWriter creation
     *        time.
     *        Usually the data representation is dynamic type, which corresponds
     *        to dds::core::xtypes::DynamicData.
     * @param info_seq
     *        @rs_st_inout Vector that will hold the output info samples. \product
     *        provides this vector to the StreamReader to fill. For each call,
     *        the size of the vector is zero.
     *        The implementation may leave the vector untouched if it does not
     *        support the concept of sample info.
     *        The info representation is dependent of the StreamWriter
     *        implementation.
     *        Usually when data representation is dynamic type, the sample
     *        info is dds::sub::SampleInfo.
     *
     * @throw std::exception
     */
    virtual void take(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) = 0;

    /**
     * @brief Variation of StreamReader::take where the returned samples will
     * remain in the StreamReader's cache, so they can be read again by
     * subsequence StreamReader::take or StreamReader::read operations.
     *
     * @see StreamReader::take
     */
    virtual void read(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) = 0;

    /**
     * @brief Variation of StreamReader::take where the returned samples shall
     * represent the subset specified by the SelectorState.
     *
     * SelectorState is configured accordingly from the values set on
     * rti::routing::processor::Selector. This operation will be called only
     * by custom rti::routing::processor::Processor implementations.
     *
     * @param sample_seq
     * @param info_seq
     * @param selector_state
     *        @rs_st_in A description of the subset of samples that shall
     *        be returned.
     *
     * @see SelectorState.
     */
    virtual void take(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            const SelectorState& selector_state) = 0;

     /**
     * @brief Variation of StreamReader::read where the returned samples shall
     * represent the subset specified by the SelectorState.
     * 
     * SelectorState is configured accordingly from the values set on
     * rti::routing::processor::Selector. This operation will be called only
     * by custom rti::routing::processor::Processor implementations.
     *
     * @param sample_seq
     * @param info_seq
     * @param selector_state
     *        @rs_st_in A description of the subset of samples that shall
     *        be returned.
     *
     * @see SelectorState.
     */
    virtual void read(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            const SelectorState& selector_state) = 0;

    /**
     * @brief Returns a loan on the read or taken data samples and info samples.
     *
     * \product calls this method to indicate that it is done accessing
     *  the collection of data samples and info samples obtained by an earlier
     *  invocation of any variation of StreamReader::take.
     *
     * @param   sample_seq
     *          @rs_st_in Vector of loaned data samples.
     * @param   info_seq
     *          @rs_st_in Vector of loaned info samples.
     *
     * @throw std::exception
     * 
     */
    virtual void return_loan(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) = 0;

    /**
     * @brief Creates a query object that selects the data with the specified
     * filter.
     *
     * This operation allows to read data with a SelectorState that contains
     * a query object returned by this operation.
     *
     * A query object type is implementation dependent and it's guaranteed to
     * to be used only within the same StreamReader that created it. Because
     * a query object may be a expensive resource, this operation allows to
     * receive a previously created query for a potential reuse and update of
     * its filter.
     *
     * @param[in] old_query_data A previously created query object that
     *            that is provided for potential reuse and update of its filter.
     * @param[in] filter The query content filter
     *
     * @return The new or updated query object.
     *
     * @throw std::exception
     *
     */
    virtual void* create_content_query(
            void *old_query_data,
            const dds::topic::Filter& filter) = 0;

    /**
     * @brief Deletes a content query created from this StreamReader.
     * 
     * @param[in] query_data the query object to be deleted.
     */
    virtual void delete_content_query(void* query_data) = 0;

    /**
     * @brief Virtual destructor.
     */
    virtual ~StreamReader()
    {
    }

};


/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::TStreamReader
 *
 * @brief A wrapper implementation of a StreamReader that provides a
 * strongly-typed interface through template parameters for data and info
 * representation.
 *
 * You can implement this interface as a convenience to manipulate the data
 * and info representation without dealing with opaque pointers.
 */
template <typename Data, typename Info>
class TStreamReader : public StreamReader {

public:

     /**
     * @brief The data type
     */
    typedef Data DataRep;
    /**
     * @brief The info type
     */
    typedef Info InfoRep;

    using StreamReader::take;
    using StreamReader::read;
    using StreamReader::return_loan;

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    void take(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        take(sample_seq_, info_seq_);
        convert_samples(sample_seq, info_seq);
    }

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    void read(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        read(sample_seq_, info_seq_);
        convert_samples(sample_seq, info_seq);
    }

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    void take(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            const SelectorState& selector_state) RTI_FINAL
    {
        take(sample_seq_, info_seq_, selector_state);
        convert_samples(sample_seq, info_seq);
    }

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    void read(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            const SelectorState& selector_state) RTI_FINAL
    {
        read(sample_seq_, info_seq_, selector_state);
        convert_samples(sample_seq, info_seq);
    }

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    void return_loan(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq_, sample_seq);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(info_seq_, info_seq);
        return_loan(sample_seq_, info_seq_);
        sample_seq_.clear();
        info_seq_.clear();
    }

    /**
     * @brief Interface redefinition
     *
     * @see StreamReader::take
     */
    virtual void take(
            std::vector<Data*>& sample_seq,
            std::vector<Info*>& info_seq) = 0;

    /**
     * @brief Interface redefinition
     *
     * @see StreamReader::read
     */
    virtual void read(
            std::vector<Data*>& sample_seq,
            std::vector<Info*>& info_seq) = 0;

    /**
     * @brief Interface redefinition
     *
     * @see StreamReader::take(std::vector&, std::vector&,const SelectorState&);
     */
    virtual void take(
            std::vector<Data*>& sample_seq,
            std::vector<Info*>& info_seq,
            const SelectorState& selector_state) = 0;

    /**
     * @brief Interface redefinition
     *
     * @see StreamReader::read(std::vector&, std::vector&,const SelectorState&);
     */
    virtual void read(
            std::vector<Data*>& sample_seq,
            std::vector<Info*>& info_seq,
            const SelectorState& selector_state) = 0;

    /**
     * @brief Interface redefinition
     *
     * @see StreamReader::return_loan
     */
    virtual void return_loan(
            std::vector<Data*>& sample_seq,
            std::vector<Info*>& info_seq) = 0;

    /*
     * @brief Virtual destructor
     */
    virtual ~TStreamReader()
    {

    }

private:
    void convert_samples(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq)
    {
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq, sample_seq_);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(info_seq, info_seq_);
    }
    
private:
    std::vector<Data*> sample_seq_;
    std::vector<Info*> info_seq_;

};

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::NoOpStreamReader
 *
 * @brief An empty implementation of the TStreamReader interface.
 *
 * Each implemented operation performs as a no-op.
 */
template <typename Data, typename Info>
class NoOpStreamReader : public TStreamReader<Data, Info> {

public:
    virtual void take(
            std::vector<Data*>&,
            std::vector<Info*>&) RTI_OVERRIDE
    {
    }

    virtual void read(
            std::vector<Data*>&,
            std::vector<Info*>&) RTI_OVERRIDE
    {
    }

    virtual void take(
            std::vector<Data*>&,
            std::vector<Info*>&,
            const SelectorState&) RTI_OVERRIDE
    {
    }

    virtual void read(
            std::vector<Data*>&,
            std::vector<Info*>&,
            const SelectorState&) RTI_OVERRIDE
    {
    }

    virtual void return_loan(
            std::vector<Data*>&,
            std::vector<Info*>&) RTI_OVERRIDE
    {
    }

    virtual void* create_content_query(
            void *,
            const dds::topic::Filter&) RTI_OVERRIDE
    {
        return NULL;
    }


    virtual void delete_content_query(void*) RTI_OVERRIDE
    {

    }



    virtual ~NoOpStreamReader()
    {
    }

};

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @brief Convenient definition of typed StreamReader that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 *
 */
typedef NoOpStreamReader<dds::core::xtypes::DynamicData, dds::sub::SampleInfo>
        DynamicDataStreamReader;



class SelectorStateAdapter {
public:
    typedef RTI_RoutingServiceSelectorState native_type;

    static void initialize(native_type& native_value)
    {
        RTI_RoutingServiceSelectorState native_state =
                RTI_RoutingServiceSelectorState_INITIALIZER;
        memcpy(&native_value, &native_state, sizeof(native_state));
    }

    static void finalize(native_type& native_value)
    {
        if (native_value.content.expression != NULL) {
            DDS_String_free(native_value.content.expression);
        }
        DDS_StringSeq_finalize(&native_value.content.expression_parameters);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        destination.sample_state = source.sample_state;
        destination.view_state = source.view_state;
        destination.instance_state = source.instance_state;
        destination.instance_handle = source.instance_handle;
        destination.instance_selection = source.instance_selection;
        destination.sample_count_max = source.sample_count_max;
        destination.query_data = source.query_data;
        char *result = DDS_String_replace(
                &destination.content.expression,
                source.content.expression);
        if (source.content.expression != NULL && result == NULL) {
            throw std::bad_alloc();
        }
        if (DDS_StringSeq_copy(
                &destination.content.expression_parameters,
                &source.content.expression_parameters) == NULL) {
            throw std::bad_alloc();
        }
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        if (first.sample_state != second.sample_state) {
            return false;
        }
        if (first.view_state != second.view_state) {
            return false;
        }
        if (first.instance_state != second.instance_state) {
            return false;
        }
        if (first.instance_selection != second.instance_selection) {
            return false;
        }
        if (first.sample_count_max != second.sample_count_max) {
            return false;
        }
        if (first.query_data != second.query_data) {
            return false;
        }
        if (first.content.expression != NULL
                && second.content.expression != NULL
                && strcmp(first.content.expression, second.content.expression) != 0) {
            return false;
        }
        return DDS_StringSeq_equals(
                &first.content.expression_parameters,
                &second.content.expression_parameters);
    }

};

} }

// native_type_traits needs to be defined in rti::core
namespace core {

template <>
struct native_type_traits<rti::routing::adapter::SelectorState> {
    typedef rti::routing::adapter::SelectorStateAdapter adapter_type;
    typedef RTI_RoutingServiceSelectorState native_type;
};

}

namespace routing { namespace adapter {

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::SelectorState
 *
 * @brief Defines a set of attributes that can be used to read a subset of
 *        data from StreamReader.
 *
 * 
 *
 */
class SelectorState : public rti::core::NativeValueType<SelectorState> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SelectorState)

    typedef rti::core::NativeValueType<SelectorState> Base;
public:
    SelectorState()
    {

    }

    SelectorState(const RTI_RoutingServiceSelectorState &native)
            : Base(native)
    {
    }

    dds::sub::status::DataState state() const
    {
        return dds::sub::status::DataState(
                dds::sub::status::SampleState(native().sample_state),
                dds::sub::status::ViewState(native().view_state),
                dds::sub::status::InstanceState(native().instance_state));
    }

    SelectorState& state(const dds::sub::status::DataState& state)
    {
         native().sample_state = state.sample_state().to_ulong();
         native().view_state = state.view_state().to_ulong();
         native().instance_state = state.instance_state().to_ulong();
         return *this;
    }    

    int32_t max_samples() const 
    {
       return native().sample_count_max;
    }

    SelectorState& max_samples(const int32_t count)
    {
        native().sample_count_max = count;
        return *this;
    }

    dds::core::InstanceHandle instance() const
    {
        if (native().instance_selection
                == RTI_ROUTING_SERVICE_THIS_INSTANCE_SELECTION) {
            return rti::core::native_conversions::from_native_handle(
                        native().instance_handle);
        }

        return dds::core::InstanceHandle::nil();
    }

    SelectorState& instance(const dds::core::InstanceHandle& handle)
    {
        native().instance_handle =
                static_cast<DDS_InstanceHandle_t>(handle->native());
        native().instance_selection = RTI_ROUTING_SERVICE_THIS_INSTANCE_SELECTION;
        return *this;
    }

    dds::core::InstanceHandle next_instance() const
    {
        if (native().instance_selection
                == RTI_ROUTING_SERVICE_NEXT_INSTANCE_SELECTION) {
            return rti::core::native_conversions::from_native_handle(
                        native().instance_handle);
        }

        return dds::core::InstanceHandle::nil();
    }

    SelectorState& next_instance(
            const dds::core::InstanceHandle& handle)
    {
        native().instance_handle =
                static_cast<DDS_InstanceHandle_t>(handle->native());
        native().instance_selection = RTI_ROUTING_SERVICE_NEXT_INSTANCE_SELECTION;
        return *this;
    }

    void* content()
    {
        return native().query_data;
    }

    SelectorState& content(void *query_data)
    {
        native().query_data = query_data;
        return *this;
    }

    dds::topic::Filter filter() const
    {
        return dds::topic::Filter(
                native().content.expression == NULL ? "" : native().content.expression,
                rti::core::native_conversions::from_native<std::string>(
                        native().content.expression_parameters));
    }

    SelectorState& filter(const dds::topic::Filter& filter)
    {
        DDS_String_replace(
                &native().content.expression,
                filter.expression().c_str());
        rti::core::native_conversions::to_native(
                native().content.expression_parameters,
                filter->parameters());    
        return *this;
    }
   
};

}}}

#endif // RTI_ROUTING_ADAPTER_STREAM_READER_HPP_
