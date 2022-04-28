/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_INPUT_HPP_
#define RTI_ROUTING_PROCESSOR_INPUT_HPP_

#include <dds/core/Value.hpp>
#include <dds/core/SafeEnumeration.hpp>
#include <rti/core/NativeValueType.hpp>

#include "routingservice/routingservice_processor.h"
#include "routingservice/routingservice_adapter_new.h"
#include <rti/routing/StreamInfo.hpp>
#include <rti/routing/adapter/StreamReader.hpp>
#include <rti/routing/processor/LoanedSamples.hpp>
#include <rti/routing/processor/Query.hpp>

namespace rti { namespace routing { namespace processor {

class Route;

template <typename Data, typename Info> class TypedInput;

inline
rti::routing::StreamInfo from_native_input(
        RTI_RoutingServiceStreamReaderExt *native,
        RTI_RoutingServiceRoute *native_route)
{
    return rti::routing::StreamInfo(
            *RTI_RoutingServiceRoute_get_input_stream_info(native_route, native));
}

inline
std::string name_from_native_input(
        RTI_RoutingServiceStreamReaderExt *native,
        RTI_RoutingServiceRoute *native_route)
{
    return RTI_RoutingServiceRoute_get_input_name(
            native_route,
            native);
}

template <typename Data, typename Info = dds::sub::SampleInfo>
class TypedInput;

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::Input
 *
 * @brief Generic Representation of a Route's input.
 *
 * This class provides a wrapper to the underlying
 * rti::routing::adapter::StreamReader.
 *
 * This class provides a base representation of the inputs contained in a Route.
 * Since it is generic, this object does not allow you to perform any operation
 * that requires dealing with the data provided by the underlying
 * rti::routing::adapter::StreamReader.
 */
class Input : private rti::routing::adapter::StreamReader {
public:

    /*i
     */
    Input(RTI_RoutingServiceStreamReaderExt *native,
          int32_t index,
          RTI_RoutingServiceRoute *native_route,
          RTI_RoutingServiceEnvironment *native_env)
        : native_(native),
          index_(index),
        native_route_(native_route),
        native_env_(native_env),
        stream_info_(from_native_input(native, native_route)),
        name_(name_from_native_input(native, native_route))
    {
    }

    /*i
     *
     */
    const rti::routing::StreamInfo& stream_info() const
    {
        return stream_info_;
    }

     /*i
     *
     */
    const std::string& name() const
    {
        return name_;
    }

    /*i
     *
     */
    int32_t index()
    {
        return index_;
    }

    /**
     * @brief Returns a typed version of this Input.
     *
     * Note: This operation is not type-safe. It is the caller's responsibility
     * to use the appropriate type.
     *
     *
     * @see TypedInput
     * @see <tt>TypedInput<DataRep, Info> Route<DataRep, InfoRep>::input(int32_t index)</tt>
     */
    template <typename Data, typename Info>
    TypedInput<Data, Info> get()
    {
        return this;
    }

    /**
     * @brief Returns a typed version of this Input.
     *
     * Note: This operation is not type-safe. It is the caller's responsibility
     * to use the appropriate type.
     *
     * @see TypedInput
     * @see TypedInput<tt><DataRep, dds::sub::SampleInfo></tt> Route<DataRep>::input(int32_t index)
     */
    template <typename Data>
    TypedInput<Data, dds::sub::SampleInfo> get()
    {
        return this;
    }


    /*
     * --- StreamReader Implementation ----------------------------------------
     */
private:
    /*i
     * @brief Returns the underlying rti::routing::adapter::StreamReader.
     *
     * @warning The returned object is a wrapper to an implementation of the
     *          StreamReader, which may be an object returned by any of the
     *          possible adapter API bindings.
     *          The use of this operation is not recommended unless your Processor
     *          implementation strictly needs to perform operations on the
     *          StreamReader.
     */
    rti::routing::adapter::StreamReader& stream_reader()
    {
        return *this;
    }

    void take(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        using namespace rti::routing::adapter;

        detail::NativeSamples native_samples;
        native_->take(
                native_->stream_reader_data,
                &native_samples.sample_array_,
                &native_samples.info_array_,
                &native_samples.length_,
                native_env_);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
        get_samples_from_native(sample_seq, info_seq, native_samples);
    }

    void read(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        using namespace rti::routing::adapter;

        detail::NativeSamples native_samples;
        native_->take(
                native_->stream_reader_data,
                &native_samples.sample_array_,
                &native_samples.info_array_,
                &native_samples.length_,
                native_env_);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
        get_samples_from_native(sample_seq, info_seq, native_samples);
    }

    void take(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            const rti::routing::adapter::SelectorState& selector_state) RTI_FINAL
    {
        detail::NativeSamples native_samples;
        native_->take_w_selector(
                native_->stream_reader_data,
                &native_samples.sample_array_,
                &native_samples.info_array_,
                &native_samples.length_,
                &selector_state.native(),
                native_env_);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
        get_samples_from_native(sample_seq, info_seq, native_samples);
    }

    void read(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            const rti::routing::adapter::SelectorState& selector_state) RTI_FINAL
    {
        detail::NativeSamples native_samples;
        native_->read_w_selector(
                native_->stream_reader_data,
                &native_samples.sample_array_,
                &native_samples.info_array_,
                &native_samples.length_,
                &selector_state.native(),
                native_env_);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
        get_samples_from_native(sample_seq, info_seq, native_samples);
    }

    void return_loan(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        detail::NativeSamples native_samples;
        native_samples.length_ = sample_seq.size();
        native_samples.sample_array_ = static_cast<RTI_RoutingServiceSample*>
                (sample_seq[native_samples.length_]);
        if (info_seq.size() > 0) {
            native_samples.info_array_ = static_cast<RTI_RoutingServiceSample*>
                (info_seq[info_seq.size()]);
        }

        native_->return_loan(
                native_->stream_reader_data,
                native_samples.sample_array_,
                native_samples.info_array_,
                native_samples.length_,
                native_env_);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
        sample_seq.clear();
        info_seq.clear();
    }


    void* create_content_query(
            void* old_query_data,
            const dds::topic::Filter& filter) RTI_FINAL
    {
        if (native_->create_content_query == NULL) {
            throw dds::core::UnsupportedError("Unsupported operation: create_content_query");
        }

        RTI_RoutingServiceSelectorContent content =
                RTI_RoutingServiceSelectorContent_INITIALIZER;
        content.expression = (char *) filter.expression().c_str();
        rti::core::native_conversions::to_native(
                content.expression_parameters,
                filter->parameters());
        void* query_data = native_->create_content_query(
                native_->stream_reader_data,
                old_query_data,
                &content,
                native_env_);
        DDS_StringSeq_finalize(&content.expression_parameters);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
        return query_data;
    }

    void delete_content_query(void* query_data) RTI_FINAL
    {
        if (native_->delete_content_query == NULL) {
            throw dds::core::UnsupportedError("delete_content_query");
        }

        native_->delete_content_query(
                native_->stream_reader_data,
                query_data,
                native_env_);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
    }


    virtual void update(const std::map<std::string, std::string>&) RTI_FINAL
    {
        throw dds::core::PreconditionNotMetError(
                "update not applicable within a Processor notification context");
    }

    // Implementation details
private:
    void get_samples_from_native(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            detail::NativeSamples& native_samples)
    {
        sample_seq.reserve(native_samples.length_ + 1);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_FROM_NATIVE(
                sample_seq,
                native_samples.sample_array_,
                native_samples.length_);
        sample_seq[native_samples.length_] =
                native_samples.sample_array_;
        if (native_samples.info_array_ != NULL) {
            info_seq.reserve(native_samples.length_ + 1);
            RTI_ROUTING_SAMPLE_VECTOR_COPY_FROM_NATIVE(
                    info_seq,
                    native_samples.info_array_,
                    native_samples.length_);
            info_seq[info_seq.size()] =
                    native_samples.info_array_;
        } else {
            info_seq.clear();
        }
    }

    RTI_RoutingServiceStreamReaderExt* native()
    {
        return native_;
    }

    template <typename Data, typename Info> friend class TypedInput;
    friend class Route;
    friend class std::allocator<Input>;
    RTI_RoutingServiceStreamReaderExt *native_;
    int32_t index_;
    RTI_RoutingServiceRoute *native_route_;
    RTI_RoutingServiceEnvironment *native_env_;
    rti::routing::StreamInfo stream_info_;
    std::string name_;
};

template <typename Data, typename Info = dds::sub::SampleInfo>
class Selector;

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::TypedInput
 *
 * @brief Representation of an Input whose data representation is \p DataRep,
 *        whose info representation is \p InfoRep.
 *
 */
template <typename Data, typename Info>
class TypedInput{
public:

    typedef rti::routing::processor::Selector<Data, Info> Selector;

    TypedInput(Input *input);

    /**
     * @brief Returns the StreamInfo associated with this object.
     *
     * The associated StreamInfo represents an equivalent object to the one
     * used to create the underlying rti::routing::adapter::StreamReader.
     */
    const rti::routing::StreamInfo& stream_info() const;

    /**
     * @brief Returns the name of this output.
     *
     * The name is given by the name of the corresponding XML configuration tag.
     */
    const std::string& name() const;

    /**
     * @brief Returns all the available samples in this object.
     *
     * This operation will call rti::routing::adapter::StreamReader::take on
     * the underlying rti::routing::adapter::StreamReader.
     *
     * The returned samples are interpreted to contain data represented
     * as \c Data and info represented as \c Info.
     *
     * @see LoanedSamples
     * @see rti::routing::adapter::StreamReader::take
     */
    LoanedSamples<Data, Info> take();

    /**
     * @brief Same as take() but this calls
     * rti::routing::adapter::StreamReader::read instead.
     *
     * @see LoanedSamples
     * @see rti::routing::adapter::StreamReader::read
     * @see take
     */
    LoanedSamples<Data, Info> read();

    /**
     * @brief Gets a Selector to perform complex data selections, such as
     * per-instance selection, content and status filtering.
     *
     * The selector can be used as follows:
     * \code{.c++}
     * LoanedSamples<DynamicData> samples = input.select()
     *     .instance(handle)
     *     .content(query)
     *     .state(state)
     *     .take();
     * \endcode
     *
     * This shows how samples can be taken by selecting a specific instance,
     * then filtering by state and content.
     *
     * Note that when the application wants to access all available samples,
     * it can simply call read() or take().
     *
     * @return A Selector, typically used in-line to configure it and finally
     *         call Selector::read() or Selector::take().
     *
     * @see Selector for the different parameters that can be set to
     *      configure which samples to read or take. Selecting what samples to
     *      read.
     */
    Selector select();

    rti::routing::processor::Query query(
            const dds::topic::Filter& filter);

    /**
     * @brief Indicates whether this input has received new data since the last
     *        time any variant of the read operations was called.
     *
     * @note Given the time decoupling between the notification of new data and
     *       when it the data is read, it is possible this function may return
     *       true and yet there is no data to be returned.
     *
     * @return True if this input has new data received since the last read
     *         access.
     */
    bool active();

    /**
     * @brief Creates a new data sample from this input.
     *
     * The data constructor called in this operation depends on the data
     * representation kind of the TypeInfo associated with this input.
     * If the type representation is a dynamic type, then it will assume
     * the following constructor:
     * \code Data(const dds::core::xtypes::DynamicType&) \endcode
     *
     * and will use the type code object downcasted from the value
     * returned by TypeInfo::type_representation.
     *
     * Otherwise:
     * \code Data() \endcode
     *
     * @return A new data sample
     */
    Data create_data();

    /*i
     *
     */
    TypedInput<Data, Info>* operator->()
    {
        return this;
    }

private:
    TypedInput();

    friend class rti::routing::processor::Selector<Data, Info>;

    LoanedSamples<Data, Info> take(
            const rti::routing::adapter::SelectorState& selector_state);

    LoanedSamples<Data, Info> read(
            const rti::routing::adapter::SelectorState& selector_state);

    friend class rti::routing::processor::Route;
    Input *input_;
};


/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::Selector
 *
 * @brief An element that allows reading data that meet a set of specified
 *        attributes.
 *
 * The Selector class is used by the TypedInput to compose read and take
 * operations.
 *
 * A Selector has an associated TypedInput and configures the behavior of the
 * read or take operation performed by that TypedInput.
 *
 * For example, to perform a read of at most 5 unread samples:
 * \code
 * LoanedSamples<Foo> samples = reader.select()
 *     .read()
 *     .max_samples(5)
 *     .state(dds::sub::status::DataState::new_data());
 * \endcode
 *
 * @note It's very important to consider that the behavior of this class is
 *       tightly coupled and dependent on the underlying
 *       rti::routing::adapter::StreamReader of the attached TypedInput. In
 *       particular, the samples returned by a Selector depend on the behavior
 *       of the rti::routing::adapter::StreamReader::take(SelectorState) and
 *       rti::routing::adapter::StreamReader::read(SelectorState). If the
 *       implementation of these operations behave according to the requirements,
 *       then the behavior offered by this class will be consistent.
 *
 * @see rti::routing::adapter::SelectorState
 * @see dds::sub::DataReader::Selector for equivalent semantics and behavior
 *      with DataReaders
 */
template <typename Data, typename Info>
class Selector {
public:

    /**
     * @brief Create a Selector for a TypedInput.
     *
     * Selectors are created with the default filter state of the TypedInput.
     *
     * @param[in] input
     *            The TypedInput that this Selector is attached to.
     */
    Selector(const rti::routing::processor::TypedInput<Data, Info> input)
        : typed_input_(input), query_(dds::core::null)
    {

    }

    /**
     * @brief Copy constructor
     */
    Selector(const Selector& other)
        : typed_input_(other.typed_input_),
          state_(other.state_),
          query_(other.query_)
    {

    }

    /**
     * @brief Select a specific dds::sub::status::DataState.
     *
     * By setting the DataState, you can specify the state of the samples that
     * should be read or taken. The DataState of a sample encapsulates the
     * SampleState, ViewState, and InstanceState of a sample.
     *
     * @param[in] the_state
     *            The selected DataState
     *
     */
    Selector& state(
            const dds::sub::status::DataState& the_state)
    {
        state_.state(the_state);
        return *this;
    }

    /**
     * @brief Choose to only read/take up to a maximum number of samples.
     *
     * @param[in] count
     *            The maximum number of samples to read/take.
     */
    Selector& max_samples(
            const int32_t count)
    {
        state_.max_samples(count);
        return *this;
    }

    /**
     * @brief Select a specific instance to read/take.
     *
     * This operation causes the subsequent read or take operation to access
     * only samples belonging the single specified instance whose handle is
     * \p the_handle.
     *
     * Upon successful completion, the data collection will contain samples all
     * belonging to the same instance.
     *
     * The subsequent read/take may operation may fail if the InstanceHandle
     * does not correspond to an existing data-object known to the TypedInput.
     *
     * @param[in] the_handle
     *            The handle of the instance to select
     *
     * @see rti::routing::adapter::SelectorState
     * @see dds::sub::DataReader::Selector::instance
     */
    Selector& instance(
            const dds::core::InstanceHandle& the_handle)
    {
        state_.instance(the_handle);
        return *this;
    }

    /**
     * @brief Select the instance after a specific instance.
     *
     * This operation causes the subsequent read or take operation to
     * access only samples belonging a single instance whose handle is
     * considered 'next' after the provided InstanceHandle, \p the_handle.
     *
     * The accessed samples will all belong to the 'next' instance with
     * InstanceHandle 'greater' than the specified previous handle that has
     * available samples.
     *
     * The special value dds::core::InstanceHandle::nil() is guaranteed to be
     * 'less than' any valid instance_handle. So the use of the parameter value
     * previous_handle == dds::core::InstanceHandle::nil() will return the
     * samples for the instance that has the smallest instance_handle among all
     * the instances that contain available samples.
     *
     * Note that it is possible to call the
     * dds::sub::next_instance(const dds::core::InstanceHandle& h) operation
     * with a previous_handle that does not correspond to an instance currently
     * managed by the underlying rti::routing::adapter::StreamReader.
     *
     * @param[in] the_handle
     *            The reference instance. The instance after this one will be
     *            selected.
     *
     * @see rti::routing::adapter::SelectorState
     * @see dds::sub::DataReader::Selector::next_instance
     */
    Selector& next_instance(
            const dds::core::InstanceHandle& the_handle)
    {
        state_.next_instance(the_handle);
        return *this;
    }

    /**
     * @brief Select samples based on a content filter parameters.
     *
     * The effect of using this manipulator is that the subsequent read/take
     * will filter the samples based on the dds::topic::Filter. If the
     * Input has no samples that meet the constraints, the read/take will not
     * return any data.
     *
     * This selection is applied in combination with the other settings of
     * this Selector.
     *
     * @param[in] the_filter
     */
    Selector& filter(
            const dds::topic::Filter& the_filter)
    {
        state_.filter(the_filter);
        return *this;
    }


    /**
     * @brief Select samples based on a rti::routing::processor::Query.
     *
     * When passing a Query, the effect of calling this method is that the
     * underlying rti::routing::adapter::StreamReader shall filter the samples
     * based only on the Query's settings.
     *
     * Using this manipulator will always override the selection specified
     * with Selector::filter, no matter the order in which operations are
     * called. To reset this selection, you can call this operation passing
     * dds::core::null.
     *
     * @param[in] the_query
     *            The Query to read/take with.
     */
    Selector& query(const rti::routing::processor::Query& the_query)
    {
        query_ = the_query;
        state_.content(the_query.delegate().get()->query_data_);
        return *this;
    }

    /**
     * @brief Take samples based on the state associated with this Selector.
     *
     * @note This operation will call rti::routing::adapter::StreamReader::take(SelectorState)
     *       on the underlying rti::routing::adapter::StreamReader.
     *
     * @throw std::exception
     *
     * @return rti::routing::processor::LoanedSamples
     */
    LoanedSamples<Data, Info> take()
    {
        return typed_input_.take(state_);
    }

    /**
     * @brief Read samples based on the state associated with this Selector.
     *
     * @note This operation will call rti::routing::adapter::StreamReader::read(SelectorState)
     *       on the underlying rti::routing::adapter::StreamReader.
     *
     * @throw std::exception
     *
     * @return rti::routing::processor::LoanedSamples
     */
    LoanedSamples<Data, Info> read()
    {
        return typed_input_.read(state_);
    }

private:
    rti::routing::processor::TypedInput<Data, Info> typed_input_;
    rti::routing::adapter::SelectorState state_;
    rti::routing::processor::Query query_;
};


template <typename Data, typename Info>
struct create_data_from_input {

    static Data get(TypedInput<Data, Info>& )
    {
        return Data();
    }
};

template <typename Info>
struct create_data_from_input<dds::core::xtypes::DynamicData, Info> {

    static dds::core::xtypes::DynamicData get(
            TypedInput<dds::core::xtypes::DynamicData, Info>& input)
    {
        if (input->stream_info().type_info().type_representation_kind()
                != TypeRepresentationKind::DYNAMIC_TYPE) {
            throw dds::core::PreconditionNotMetError(
                    "inconsistent data representation kind");
        }
        dds::core::xtypes::DynamicType *type_code =
                static_cast<dds::core::xtypes::DynamicType *> (
                input->stream_info().type_info().type_representation());
        return dds::core::xtypes::DynamicData(*type_code);
    }
};

template <typename Data, typename Info>
TypedInput<Data, Info>::TypedInput(Input *input)
: input_(input)
{
}

template <typename Data, typename Info>
const rti::routing::StreamInfo& TypedInput<Data, Info>::stream_info() const
{
    return input_->stream_info_;
}

template <typename Data, typename Info>
const std::string& TypedInput<Data, Info>::name() const
{
    return input_->name_;
}

template <typename Data, typename Info>
LoanedSamples<Data, Info> TypedInput<Data, Info>::take()
{
    detail::NativeSamples native_samples;
    input_->native_->take(
            input_->native_->stream_reader_data,
            &native_samples.sample_array_,
            &native_samples.info_array_,
            &native_samples.length_,
            input_->native_env_);
    RTI_ROUTING_THROW_ON_ENV_ERROR(input_->native_env_);
    return LoanedSamples<Data, Info>(
            input_->native_,
            native_samples,
            input_->native_env_);
}

template <typename Data, typename Info>
LoanedSamples<Data, Info> TypedInput<Data, Info>::read()
{
    detail::NativeSamples native_samples;
    input_->native_->read(
            input_->native_->stream_reader_data,
            &native_samples.sample_array_,
            &native_samples.info_array_,
            &native_samples.length_,
            input_->native_env_);
    RTI_ROUTING_THROW_ON_ENV_ERROR(input_->native_env_);
    return LoanedSamples<Data, Info>(
            input_->native_,
            native_samples,
            input_->native_env_);
}

template <typename Data, typename Info>
rti::routing::processor::Selector<Data, Info>
TypedInput<Data, Info>::select()
{
    return rti::routing::processor::Selector<Data, Info>(*this);
}

template <typename Data, typename Info>
rti::routing::processor::Query TypedInput<Data, Info>::query(
        const dds::topic::Filter& filter)
{
    return rti::routing::processor::Query(
            &input_->stream_reader(),
            filter);

}

template <typename Data, typename Info>
LoanedSamples<Data, Info> TypedInput<Data, Info>::take(
        const rti::routing::adapter::SelectorState& selector_state)
{
    detail::NativeSamples native_samples;
    input_->native_->take_w_selector(
            input_->native_->stream_reader_data,
            &native_samples.sample_array_,
            &native_samples.info_array_,
            &native_samples.length_,
            &selector_state.native(),
            input_->native_env_);
    RTI_ROUTING_THROW_ON_ENV_ERROR(input_->native_env_);
    return LoanedSamples<Data, Info>(
            input_->native_,
            native_samples,
            input_->native_env_);
}

template <typename Data, typename Info>
LoanedSamples<Data, Info> TypedInput<Data, Info>::read(
        const rti::routing::adapter::SelectorState& selector_state)
{
    detail::NativeSamples native_samples;
    input_->native_->read_w_selector(
            input_->native_->stream_reader_data,
            &native_samples.sample_array_,
            &native_samples.info_array_,
            &native_samples.length_,
            &selector_state.native(),
            input_->native_env_);
    RTI_ROUTING_THROW_ON_ENV_ERROR(input_->native_env_);
    return LoanedSamples<Data, Info>(
            input_->native_,
            native_samples,
            input_->native_env_);
}

template <typename Data, typename Info>
bool TypedInput<Data, Info>::active()
{
    return RTI_RoutingServiceRoute_is_input_active(
            input_->native_route_,
            input_->native_) ? true : false;
}

template <typename Data, typename Info>
Data TypedInput<Data,Info>::create_data()
{
    return create_data_from_input<Data, Info>::get(*this);
}

/**
 * @brief Convenient definition of a TypedInput whose data representation
 * is DynamicData and info representation is dds::sub::SampleInfo.
 *
 * These data and info representations are expected be used by most of the
 * rti::routing::adapter::StreamReader implementations.
 */
typedef TypedInput<dds::core::xtypes::DynamicData> DynamicDataInput;

} } }


#endif // RTI_ROUTING_PROCESSOR_INPUT_HPP_
