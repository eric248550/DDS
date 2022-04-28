/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_ROUTE_HPP_
#define RTI_ROUTING_PROCESSOR_ROUTE_HPP_

#include <dds/core/Value.hpp>
#include <dds/core/SafeEnumeration.hpp>
#include <rti/core/NativeValueType.hpp>

#include "routingservice/routingservice_processor.h"
#include "routingservice/routingservice_processor_impl.h"

#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/processor/Input.hpp>
#include <rti/routing/processor/Output.hpp>
#include <rti/routing/processor/LoanedSamples.hpp>
#include <rti/routing/processor/PortIterator.hpp>

namespace rti { namespace routing { namespace processor {

namespace detail {

class ProcessorForwarder;
struct ScopedPort;

}

class Route;

template <typename PORT> struct port_list;

template <> struct port_list<Input>
{
    static std::vector<Input>& get(Route& route);
};

template <> struct port_list<Output>
{
    static std::vector<Output>& get(Route& route);
};

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::Route
 *
 * @brief Representation of the Route object that owns a Processor.
 *
 * This class provides an interface to access the capabilities of a Route, such
 * as retrieving any of its inputs and outputs. Usage of this class
 * is restricted within the Processor context where the object is passed.
 *
 * An example of how to use this object is shown below. This example illustrates
 * a simple use case of reading from all inputs and writing to all outputs,
 * assuming that the sample data and info have the same representation and
 * type.
 *
 * \code{.c++}
 * using dds::core::xtypes::DynamicData;
 * using dds::sub::SampleInfo;
 * using namespace rti::routing::processor;
 *
 * ...
 *
 * for (auto input : route.inputs<DynamicData>()) {
 *     LoanedSamples<DynamicData> samples = input->read();
 *
 *     for (auto output : route.outputs<DynamicData>()) {
 *         for(auto sample = samples) {
 *              output.write(sample.data(), sample.info());
 *         }
 *     }
 * }
 * \endcode
 */
class Route {

public:

    template <typename DataRep, typename InfoRep = dds::sub::SampleInfo>
    struct Inputs {
        typedef PortIterator<Input, DataRep, InfoRep> iterator;

        Inputs(RTI_RoutingServiceRoute *native_route)
                : native_route_(native_route)
        {
        }

        iterator begin()
        {
            return iterator(native_route_);
        }

        iterator end()
        {
            return iterator();
        }

        private:
            RTI_RoutingServiceRoute *native_route_;
    };

    template <typename DataRep, typename InfoRep = dds::sub::SampleInfo>
    struct Outputs {
        typedef PortIterator<Output, DataRep, InfoRep> iterator;

        Outputs(RTI_RoutingServiceRoute *native_route)
                : native_route_(native_route)
        {
        }

        iterator begin()
        {
            return iterator(native_route_);
        }

        iterator end()
        {
            return iterator();
        }

    private:
        RTI_RoutingServiceRoute *native_route_;
    };


public:

    /**
     * @brief Returns the total number of inputs in this Route.
     *
     */
    int32_t input_count() const
    {
        return RTI_RoutingServiceRoute_get_input_count(native_route_);
    }

    /**
     * @brief Returns the total number of outputs in this Route.
     *
     */
    int32_t output_count() const
    {
        return RTI_RoutingServiceRoute_get_output_count(native_route_);
    }

/**
     * @brief Returns the Input object at the specified index.
     *
     * Input indexes are assigned in increasing creation order, starting at 0.
     * The creation order is the same order than the inputs are defined within
     * the Route configuration.
     *
     * The returned object can be used to construct the appropriate TypedInput,
     * which can be used  for reading data.
     *
     * @param[in] index
     *            The index of the Input to be retrieved.
     *
     * @return The Input at the specified index.
     *
     * @see TypedInput
     *
     */
    Input& input(int32_t index)
    {
        return *(get_input_at_index(index));
    }

     /**
     * @brief Returns the Input object with the specified name.
     *
     * @param[in] name The input configuration name
     *
     * @return The object with the specified name or throws
     *
     * @see TypedInput::name
     * @throw std::logic_error
     */
    Input& input(const std::string& name)
    {
        return *(lookup_input(name));
    }

    /**
     * @brief Returns the TypedInput object at the specified index.
     *
     * The returned object is typed so it can read samples whose type is
     * \p DataRep for data, and \p InfoRep for info. These types must
     * match the expected type representations of the underlying
     * rti::routing::adapter::StreamReader.
     *
     * Typically, these template arguments are typed
     * dds::core::xtypes::DynamicData and dds::sub::SampleInfo, respectively.
     *
     * @warning This operation performs no type integrity check. It is
     *          responsibility of the caller to ensure the provided template
     *          arguments match with the expected types of the input. Otherwise
     *          behavior accessing the input is undefined.
     *
     * @return The TypedInput object at the specified index.
     *
     * @see input(int32_t)
     * @see TypedInput
     */
    template <typename DataRep, typename InfoRep>
    TypedInput<DataRep, InfoRep> input(int32_t index)
    {
        return &input(index);
    }

    /**
     * @brief Same as <tt>input<DataRep, InfoRep>(int32_t)</tt> with
     * InfoRep = dds::sub::SampleInfo.
     *
     */
    template <typename DataRep>
    TypedInput<DataRep> input(int32_t index)
    {
        return input<DataRep, dds::sub::SampleInfo>(index);
    }

    /**
     * @brief Same as <tt>input<DataRep, InfoRep>(int32_t)</tt> but using
     * the configuration name of the input.
     *
     */
    template <typename DataRep, typename InfoRep>
    TypedInput<DataRep, InfoRep> input(const std::string& name)
    {
        return &input(name);
    }

    /**
     * @brief Same as <tt>input<DataRep, InfoRep>(std::string&)</tt> with
     * InfoRep = dds::sub::SampleInfo.
     */
    template <typename DataRep>
    TypedInput<DataRep> input(const std::string& name)
    {
        return input<DataRep, dds::sub::SampleInfo>(name);
    }

    /**
     * @brief Returns the Output object at the specified index.
     *
     * Output indexes are assigned in increasing creation order, starting at 0.
     * The creation order is the same order than the outputs are defined within
     * the Route configuration.
     *
     * The returned object can be used to construct the appropriate TypedOutput,
     * which can be used for writing data.
     *
     * @param[in] index
     *            The index of the Output to be retrieved.
     *
     * @return The Output at the specified index.
     *
     * @see TypedOutput
     *
     */
    Output& output(int32_t index)
    {
        return *(get_output_at_index(index));
    }

    /**
     * @brief Returns the Output object with the specified name.
     *
     * @param[in] name The output configuration name
     *
     * @return The object with the specified name or throws
     *
     * @see TypedOutput::name
     * @throw std::logic_error
     */
    Output& output(const std::string& name)
    {
        return *(lookup_output(name));
    }

    /**
     * @brief Returns the TypedOutput object at the specified index.
     *
     * The returned object is typed so it can write samples whose type is
     * \p DataRep for data, and \p InfoRep for info. These types must
     * match the expected type representations of the underlying
     * rti::routing::adapter::StreamWriter.
     *
     * Typically, these template arguments are typed
     * dds::core::xtypes::DynamicData and dds::sub::SampleInfo, respectively.
     *
     * @warning This operation performs no type integrity check. It is
     *          responsibility of the caller to ensure the provided template
     *          arguments match with the expected types of the output. Otherwise
     *          behavior accessing the output is undefined.
     *
     * @return The TypedOutput object at the specified index.
     *
     * @see input(int32_t)
     */
    template <typename DataRep, typename InfoRep>
    TypedOutput<DataRep, InfoRep> output(int32_t index)
    {
        return &output(index);
    }

    /**
     * @brief Same as <tt>output<DataRep, InfoRep>(int32_t)</tt> with
     * InfoRep = dds::sub::SampleInfo.
     *
     */
    template <typename DataRep>
    TypedOutput<DataRep> output(int32_t index)
    {
        return output<DataRep, dds::sub::SampleInfo>(index);
    }

     /**
     * @brief Same as <tt>output<DataRep, InfoRep>(int32_t)</tt> but using
     * the configuration name of the output.
     *
     */
    template <typename DataRep, typename InfoRep>
    TypedOutput<DataRep, InfoRep> output(const std::string& name)
    {
        return &output(name);
    }

    /**
     * @brief Same as <tt>output<DataRep, InfoRep>(std::string&)</tt> with
     * InfoRep = dds::sub::SampleInfo.
     */
    template <typename DataRep>
    TypedOutput<DataRep> output(const std::string& name)
    {
        return output<DataRep, dds::sub::SampleInfo>(name);
    }

    /**
     * @brief  Returns an accessor for the contained inputs.
     *
     * The returned object that allows iterating over the
     * contained inputs, treating them as <tt>TypedInput<DataRep, InfoRep></tt>.
     *
     * @see <tt>Inputs<DataRep, InfoRep></tt>
     * @see <tt>TypedInput<DataRep, InfoRep> input(int32_t index)</tt>
     */
    template <typename DataRep, typename InfoRep>
    Inputs<DataRep, InfoRep> inputs()
    {
        return Inputs<DataRep, InfoRep>(native_route_);
    }

    /**
     * @brief  Same as <tt>Inputs<DataRep, InfoRep> inputs()</tt> with
     * InfoRep = dds::sub::SampleInfo.
     */
    template <typename DataRep>
    Inputs<DataRep> inputs()
    {
        return inputs<DataRep, dds::sub::SampleInfo>();
    }

     /**
     * @brief  Returns an accessor for the contained outputs.
     *
     * The returned object that allows iterating over the
     * contained outputs, treating them as <tt>TypedOutput<DataRep, InfoRep></tt>.
     *
     * @see <tt>Outputs<DataRep, InfoRep></tt>
     * @see <tt>TypedOutput<DataRep, InfoRep> input(int32_t index)</tt>
     */
    template <typename DataRep, typename InfoRep>
    Outputs<DataRep, InfoRep> outputs()
    {
        return Outputs<DataRep, InfoRep>(native_route_);
    }

    /**
     * @brief  Same as <tt>Inputs<DataRep, InfoRep> outputs()</tt> with
     * InfoRep = dds::sub::SampleInfo.
     */
    template <typename DataRep>
    Outputs<DataRep> outputs()
    {
        return outputs<DataRep, dds::sub::SampleInfo>();
    }

    /**
     *
     * @brief Changes the event period of the Session.
     *
     * This operation can be called many times within the same periodic event,
     * in which only the last call will have effect. If many Routes within a
     * Session are calling this operation, then only the call made by the last
     * Route will have effect.
     *
     * The operation has no effect if the periodic event is not enabled in the
     * session.
     *
     * @param[in] period  New session period
     */
    void period(const dds::core::Duration& period)
    {
        RTI_RoutingServiceRoute_set_session_period(
                native_route_,
                period.to_millisecs());
    }


private:
    friend class detail::ProcessorForwarder;
    friend class Output;
    friend struct port_list<Input>;
    friend struct port_list<Output>;

    typedef std::vector<Input>::iterator private_input_it;
    typedef std::vector<Output>::iterator private_output_it;

    Route& operator= (const Route& other);

    Route(RTI_RoutingServiceRoute *native_route,
          RTI_RoutingServiceEnvironment *native_env)
        : native_route_(native_route),
        native_env_(native_env)
    {
    }

    template<typename PORT>
    PORT * get_port_from_native(void *native)
    {
        return static_cast<PORT*>(
                RTI_RoutingServiceRoute_get_stream_port_user_data(
                        native_route_,
                        native));
    }

    Input* get_input_at_index(int32_t index)
    {
        RTI_RoutingServiceStreamReaderExt *native_input =
                RTI_RoutingServiceRoute_get_input_at(
                    native_route_,
                    index);
        if (native_input == NULL) {
            throw dds::core::InvalidArgumentError(
                    RTI_RoutingServiceEnvironment_get_error_message(native_env_));
        }

        return get_port_from_native<Input>(native_input->stream_reader_data);
    }

    Output* get_output_at_index(int32_t index)
    {
        RTI_RoutingServiceStreamWriterExt *native_output =
                RTI_RoutingServiceRoute_get_output_at(
                    native_route_,
                    index);
        if (native_output == NULL) {
            throw dds::core::InvalidArgumentError(
                    RTI_RoutingServiceEnvironment_get_error_message(native_env_));
        }

        return get_port_from_native<Output>(
                native_output->stream_writer_data);
    }


    Input* lookup_input(const std::string& name)
    {
        RTI_RoutingServiceStreamReaderExt *native_input =
                RTI_RoutingServiceRoute_lookup_input_by_name(
                    native_route_,
                    name.c_str());
        if (native_input == NULL) {
            throw dds::core::InvalidArgumentError(
                    RTI_RoutingServiceEnvironment_get_error_message(native_env_));
        }
        return get_port_from_native<Input>(native_input->stream_reader_data);

    }

    Output* lookup_output(const std::string& name)
    {
       RTI_RoutingServiceStreamWriterExt *native_output =
                RTI_RoutingServiceRoute_lookup_output_by_name(
                    native_route_,
                    name.c_str());
        if (native_output == NULL) {
            throw dds::core::InvalidArgumentError(
                    RTI_RoutingServiceEnvironment_get_error_message(native_env_));
        }
        return get_port_from_native<Output>(
                native_output->stream_writer_data);

    }

    RTI_RoutingServiceRoute *native_route_;
    RTI_RoutingServiceEnvironment *native_env_;

};


} } }

#endif // RTI_ROUTING_PROCESSOR_ROUTE_HPP_
