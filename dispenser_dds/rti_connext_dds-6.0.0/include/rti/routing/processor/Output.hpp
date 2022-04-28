/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_OUTPUT_HPP_
#define RTI_ROUTING_PROCESSOR_OUTPUT_HPP_

#include <dds/core/Value.hpp>
#include <dds/core/SafeEnumeration.hpp>
#include <rti/core/NativeValueType.hpp>

#include "routingservice/routingservice_processor.h"
#include "routingservice/routingservice_adapter_new.h"
#include <rti/routing/adapter/StreamWriter.hpp>

namespace rti { namespace routing { namespace processor {

class Route;

template <typename Data, typename Info> class TypedOutput;

inline
rti::routing::StreamInfo stream_info_from_native_output(
        RTI_RoutingServiceStreamWriterExt *native,
        RTI_RoutingServiceRoute *native_route)
{
    return rti::routing::StreamInfo(
            *RTI_RoutingServiceRoute_get_output_stream_info(native_route, native));
}

inline
std::string name_from_native_output(
        RTI_RoutingServiceStreamWriterExt *native,
        RTI_RoutingServiceRoute *native_route)
{
    return RTI_RoutingServiceRoute_get_output_name(
            native_route,
            native);
}

template <typename Data, typename Info = dds::sub::SampleInfo>
class TypedOutput;

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::Output
 *
 * @brief Generic Representation of a Route's output.
 *
 * This class provides a wrapper to the underlying
 * rti::routing::adapter::StreamWriter.
 *
 * This class provides a base representation of the outputs contained in a Route.
 * Since it is generic, this object does not allow performing any operation
 * that requires dealing with the data passed to the underlying
 * rti::routing::adapter::StreamWriter.
 */
class Output : private rti::routing::adapter::StreamWriter {
public:

    /*i
     */
    Output(
        RTI_RoutingServiceStreamWriterExt *native,
        int32_t index,
        RTI_RoutingServiceRoute *native_route,
        RTI_RoutingServiceEnvironment *native_env)
            : native_(native),
             index_(index),
             native_env_(native_env),
             stream_info_(stream_info_from_native_output(native, native_route)),
             name_(name_from_native_output(native, native_route))
    {
    }

    /*i
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
     * @brief Returns a typed version of this Output.
     *
     * Note: This operation is not type-safe and it is the caller's
     * responsibility to use the appropriate type.
     *
     * @see TypedOutput
     * @see <tt>TypedOutput<DataRep, Info> Route<DataRep, InfoRep>::output(int32_t index)</tt>
     */
    template <typename Data, typename Info>
    TypedOutput<Data, Info> get()
    {
        return this;
    }

    /**
     * @brief Returns a typed version of this Output.
     *
     * Note: This operation is not type-safe and it is the caller's
     * responsibility to use the appropriate type.
     *
     * @see TypedOutput
     * @see TypedOutput<tt><DataRep, dds::sub::SampleInfo></tt> Route<DataRep>::output(int32_t index)
     */
    template <typename Data>
    TypedOutput<Data, dds::sub::SampleInfo> get()
    {
        return this;
    }


private:
    /*i
     */
    rti::routing::adapter::StreamWriter& stream_writer()
    {
        return *this;
    }

    int write(
            const std::vector<SamplePtr>& sample_seq,
            const std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        int count = native_->write(
                native_->stream_writer_data,
                &sample_seq[0],
                &info_seq[0],
                sample_seq.size(),
                native_env_);
        RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
        return count;
    }

    virtual void update(const std::map<std::string, std::string>&) RTI_FINAL
    {
        throw dds::core::PreconditionNotMetError(
                "update not applicable within a Processor notification context");
    }


    RTI_RoutingServiceStreamWriterExt* native()
    {
        return native_;
    }

private:
    template <typename Data, typename Info> friend class TypedOutput;
    friend class Route;
    RTI_RoutingServiceStreamWriterExt *native_;
    int32_t index_;
    RTI_RoutingServiceEnvironment *native_env_;
    rti::routing::StreamInfo stream_info_;
    std::string name_;
};

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::TypedOutput
 *
 * @brief Representation of an Output whose data representation is \p DataRep,
 *        whose info representation is \p InfoRep.
 *
 */
template <typename Data, typename Info>
class TypedOutput{
public:
    TypedOutput(Output *output) ;

    TypedOutput<Data, Info>* operator->();

    /**
     * @brief Returns the StreamInfo associated with this object.
     *
     * The associated StreamInfo represents an equivalent object to the one
     * used to create the underlying rti::routing::adapter::StreamWriter.
     */
    const rti::routing::StreamInfo& stream_info() const;

    /**
     * @brief Returns the name of this output.
     *
     * The name is given by the name of the corresponding XML configuration tag.
     */
    const std::string& name() const;

    /**
     * @brief Writes the specified data and info sample in this output.
     *
     * This operation will call rti::routing::adapter::StreamWriter::write on
     * the underlying rti::routing::adapter::StreamWriter.
     *
     * The provided sample is interpreted to contain data represented
     * as \c Data and the info as \c Info.
     *
     * @see rti::routing::adapter::StreamWriter::write
     */
    void write(const Data& sample, const Info& info);

    /*
     * @brief Writes a sample given its data only.
     *
     * This operation will call rti::routing::adapter::StreamWriter::write
     * on the underlying rti::routing::adapter::StreamWriter, providing a null
     * value for the info sample. The underlying adapter will compute any
     * associated metadata from the data sample.
     */
    void write(const Data& sample);

    /**
     * @brief Creates a new data sample that can be used to write in this
     *        output.
     *
     * The data constructor called in this operation depends on the data
     * representation kind of the TypeInfo associated with this output.
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

private:
    friend class rti::routing::processor::Route;

    Output *output_;
};

template <typename Data, typename Info>
struct create_data_from_output {

    static Data get(TypedOutput<Data, Info>& )
    {
        return Data();
    }
};


template <typename Info>
struct create_data_from_output<dds::core::xtypes::DynamicData, Info> {

    static dds::core::xtypes::DynamicData get(TypedOutput<dds::core::xtypes::DynamicData, Info>& output)
    {
        if (output->stream_info().type_info().type_representation_kind()
                != TypeRepresentationKind::DYNAMIC_TYPE) {
            throw dds::core::PreconditionNotMetError(
                    "inconsistent data representation kind");
        }
        dds::core::xtypes::DynamicType *type_code =
                static_cast<dds::core::xtypes::DynamicType *> (
                output->stream_info().type_info().type_representation());
        return dds::core::xtypes::DynamicData(*type_code);
    }
};


template <typename Data, typename Info>
TypedOutput<Data,Info>::TypedOutput(Output* output) : output_(output)
{
}

template <typename Data, typename Info>
const rti::routing::StreamInfo& TypedOutput<Data, Info>::stream_info() const
{
    return output_->stream_info_;
}

template <typename Data, typename Info>
const std::string& TypedOutput<Data, Info>::name() const
{
    return output_->name_;
}

template <typename Data, typename Info>
TypedOutput<Data, Info>* TypedOutput<Data,Info>::operator->()
{
    return this;
}

template <typename Data, typename Info>
void TypedOutput<Data,Info>::write(const Data& sample, const Info& info)
{
    const RTI_RoutingServiceSample out_samples[1] = {
        const_cast<void *> (reinterpret_cast<const void *> (&sample))
    };
    const RTI_RoutingServiceSampleInfo out_infos[1] = {
        const_cast<void *> (reinterpret_cast<const void *> (&info))
    };
    output_->native_->write(
            output_->native_->stream_writer_data,
            reinterpret_cast<const RTI_RoutingServiceSample *> (&out_samples),
            reinterpret_cast<const RTI_RoutingServiceSample *> (&out_infos),
            1,
            output_->native_env_);
    RTI_ROUTING_THROW_ON_ENV_ERROR(output_->native_env_);
}

template <typename Data, typename Info>
void TypedOutput<Data,Info>::write(const Data& sample)
{
    const RTI_RoutingServiceSample out_samples[1] = {
        const_cast<void *> (reinterpret_cast<const void *> (&sample))
    };
    output_->native_->write(
            output_->native_->stream_writer_data,
            reinterpret_cast<const RTI_RoutingServiceSample *> (&out_samples),
            NULL,
            1,
            output_->native_env_);
    RTI_ROUTING_THROW_ON_ENV_ERROR(output_->native_env_);
}

template <typename Data, typename Info>
Data TypedOutput<Data,Info>::create_data()
{
    return create_data_from_output<Data, Info>::get(*this);
}


/**
 * @brief Convenient definition of a TypedOutput whose data representation
 * is DynamicData and info representation is dds::sub::SampleInfo.
 *
 * These data and info representations are expected be used by most
 * rti::routing::adapter::StreamWriter implementations.
 */
typedef TypedOutput<dds::core::xtypes::DynamicData> DynamicDataOutput;

} } }


#endif // RTI_ROUTING_PROCESSOR_OUTPUT_HPP_
