/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_PROCESSOR_PLUGIN_HPP_
#define RTI_ROUTING_PROCESSOR_PROCESSOR_PLUGIN_HPP_

#include "routingservice/routingservice_log.h"

#include <rti/config/Version.hpp>
#include <rti/routing/PropertySet.hpp>
#include <rti/routing/processor/Route.hpp>
#include <rti/routing/processor/Processor.hpp>

/** @file
 * @brief \product C++ Processor API
 */
/** @defgroup RTI_RoutingServiceProcessorModule  RTI Routing Service Processor API
 * @ingroup ROUTER
 * @brief This module describes the Processor API.
 *
 * @product rti::routing::processor::Processor are **event-oriented pluggable
 * components** that allow you to control the forwarding process that occur within a Route.
 *
 * ##  Development Requirements
 *
 * |                 | Unix-based Systems                        | Windows Systems           |
 * | --------------: | :----------------:                        | :-------------:           |
 * | Shared Libraries| libnddscpp2.so                            | nddscpp2.lib              |
 * | ^               | librtirsinfrastructure.so                 | rtirsinfrastructure.lib   |
 * | ^               | libnddsc.so                               | nddsc.lib                 |
 * | ^               | libnddscore.so                            | nddscore.lib              |
 * | Headers         | rti/routing/processor/ProcessorPlugin.hpp ||
 *
 * ## Architecture
 *
 * A rti::routing::processor::Processor represents a multiple-input,
 * multiple-output component attached to a rti::routing::processor::Route,
 * which dispatches events to the rti::routing::processor::Processor.
 * The figure below shows the role of a rti::routing::processor::Processor within
 * @product.
 *
 * \htmlonly <div style="margin:auto;width:700px;">\endhtmlonly
 * \image html RouterProcessorComponent.svg "Overview of a Processor component in @product" width=700px
 * \htmlonly </div>\endhtmlonly
 * 
 * A Processor can access the *N* inputs and *M* outputs of the owner Route.
 * Upon event notification, the Processor can read data from any input,
 * perform any manipulation on the data, and write it on any of the outputs.
 *
 * Note in the figure above that any data a Processor writes on an output is
 * first transformed with an rti::routing::transf::Transformation before passing
 * it to the underlying rti::routing::adapter::StreamWriter.
 *
 * An example snippet is shown below. The example code is reading data from
 * two inputs, merging it together in an intermediate data buffer and writing
 * into a single output.
 *
 * \code{.cpp}
 * on_data_available(Route& route)
 * {
 *    auto output = route.output<DynamicData>(0);
 *    auto output_sample = output.create_data();
 *    for(const auto& status : route.input<DynamicData>(0).take()) {
 *         auto periodic  = route.input<DynamicData>(1)
 *                 .select().instance(status.info().instance_handle()).read();
 *         output_sample.value<int>(
 *                 "id",
 *                 status.data().get<int>("id"));
 *         output_sample.value<int>(
 *                 "config",
 *                  status.data().get<string>("config"));
 *         output_sample.value<int>(
 *                  "latency",
 *                  periodic[0].data().get<int>("latency"));
 *         output.write(output_sample);
 *    }
 * }
 * \endcode
 *
 * The Processor API component model is shown in figure below.
 *
 * \htmlonly <div style="margin:auto;width:800px;">\endhtmlonly
 * \image html RouterProcessorClass.svg "Processor API component model" width=800px
 * \htmlonly </div>\endhtmlonly
 *
 *  * rti::routing::processor::Processor
 *  * rti::routing::processor::Route
 *  * rti::routing::processor::Input
 *  * rti::routing::processor::Output
 *  * rti::routing::processor::Selector
 *
 * ## Event dispatching
 *
 * A rti::routing::processor::Route will notify its contained
 * rti::routing::processor::Processor about the events that affect the Route
 * object. Each event kind maps to a virtual operation in the
 * rti::routing::processor::Processor interface:
 *
 *  * **Input Enabled**: Event that represents the transition from disables to
 *    enabled on any of the contained rti::routing::processor::Input. Enabling
 *    an Input results in the creation of the underlying
 *    rti::routing::adapter::StreamReader.
 *    This event is notified through rti::routing::processor::Processor::on_input_enabled.
 *
 *  * **Input Disabled**: Event that represents the transition from enabled to
 *    disabled on any of the contained rti::routing::processor::Input. Disabling
 *    an Input results in the deletion of the underlying
 *    rti::routing::adapter::StreamReader.
 *    This event is notified through rti::routing::processor::Processor::on_input_disabled.
 *
 *  * **Output Enabled**: Event that represents the transition from disabled to
 *    enabled on any of the contained rti::routing::processor::Output. Enabling
 *    an Output results in the creation of the underlying
 *    rti::routing::transf::Transformation and rti::routing::adapter::StreamWriter.
 *    This event is notified through rti::routing::processor::Processor::on_output_enabled.
 *
 *  * **Output Disabled**: Event that represents the transition from enabled to
 *    disabled on any of the contained rti::routing::processor::Output. Disabling
 *    an Output results in the deletion of the underlying
 *    rti::routing::transf::Transformation and rti::routing::adapter::StreamWriter.
 *    This event is notified through rti::routing::processor::Processor::on_output_disabled.
 *
 *  * **Route Started**: This event indicates that the owner
 *    rti::routing::processor::Route has enabled all inputs and outputs.
 *    This event is notified through rti::routing::processor::Processor::on_start.
 *
 *  * **Route Stopped**: This event indicates that the owner
 *    rti::routing::processor::Route is about to disable at least one of its
 *    inputs or outputs.
 *    This event is notified through rti::routing::processor::Processor::on_stop.
 *
 *  * **Route Running**: This event indicates that the owner
 *    rti::routing::processor::Route is ready to provide user event
 *    notifications.
 *    This event is notified through rti::routing::processor::Processor::on_run.
 *
 *  * **Route Paused**: This event indicates that the owner
 *    rti::routing::processor::Route will temporarily stop providing user
 *    event notifications.
 *    This event is notified through rti::routing::processor::Processor::on_pause.
 *
 *  * **Data Available**: This user event indicates at least one of the inputs
 *    within the owner rti::routing::processor::Route has received new data.
 *    This event is notified through rti::routing::processor::Processor::on_data_available.
 *
 *  * **Periodic Action**: This user event represents a periodic notification,
 *    at a rate configured in the parent Session of the owner
 *    rti::routing::processor::Route.
 *    This event is notified through rti::routing::processor::Processor::on_periodic_action.
 *
 *
 * ## Threading
 *
 * A rti::routing::processor::Route dispatches all the events to its contained
 * processors **sequentially**, from within one of the parent Session's threads.
 * For any given Route, and hence a Processor, it is guaranteed that only
 * one event is dispatched at at time. That is, the operations on the Processor
 * are never called concurrently for a given Route.
 *
 * A parent Session with *L* threads can only process one Route at
 * a time but it can dispatch different Routes concurrently. Namely, it can
 * dispatch up to *L* Routes concurrently. You should keep this behavior in mind
 * for implementations that share state between Processor objects.
 *
 * ## Constraints
 *
 * There are several constraints that affect the behavior and relationship
 * of the Processor API components:
 *
 * * A Route can have one and only one Processor. Alternatively, *semantically* a
 *   Processor can belong to one and only one Route. That is, each Route will
 *   call rti::routing::processor::ProcessorPlugin::create_processor and
 *   rti::routing::processor::ProcessorPlugin::delete_processor on the
 *   corresponding plug-in instance, if the implementation is returning the
 *   same physical object.
 *
 * * An Input/Output can belong to one and only one Route. Thus, they cannot
 *   be shared across different Routes. Alternatively, operations on an
 *   Input, Output and Route can be performed only from within the associated
 *   Processor. It is forbidden to pass Input, Output and Route objects between
 *   Processors
 */


namespace rti { namespace routing { namespace processor {

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::ProcessorPlugin
 * @brief The top-level plug-in class.
 *
 * Represents a factory of Processor.
 */
class ProcessorPlugin {
public:

    /**
     * @brief Creates a Route Processor.
     *
     * This function is called when the Route containing the Processor
     * is enabled.
     *
     * A Routing Service running instance will product a log indicating the
     * occurrence of this event. For example:
     * \code
     * [.../domain_routes/DomainRoute|START|/sessions/Session|START|/routes/Route|ENABLE]
     * \endcode
     *
     *
     * <b>Required:</b> yes
     *
     * @param route
     *        @rs_st_in An object representation of the Route that owns
     *        the Processor.
     * @param properties
     *        @rs_st_in Configuration properties for the Processor.
     *        These properties corresponds to the properties specified within
     *        the tag &lt;processor&gt;.
     *
     * @return New Processor if successful. Cannot return @null_value.
     * @throw std::exception
     * @mtsafety Safe
     */
    virtual Processor * create_processor(
            Route& route,
            const rti::routing::PropertySet& properties) = 0;

    /**
     * @brief Deletes a Route Processor.
     *
     * This function is called when the Route containing the Processor
     * is disabled.
     *
     * <b>Required:</b> yes
     *
     * @param route
     *        @rs_st_in An object representation of the Route that owns
     *        the Processor.
     * @param processor
     *        @rs_st_in Processor object to be deleted.
     *
     * @throw std::exception
     * @mtsafety Safe
     */
    virtual void delete_processor(
            Route& route,
            Processor *processor) = 0;

    /**
     * @return  The version of this TransformationPlugin.
     *
     * The version is used for logging purposes. It allows you to track which
     * version of the TransformationPlugin the @product is using.
     *
     * Default implementation of this operation returns the version of the
     * required Connext libraries.
     */
    virtual rti::config::LibraryVersion get_version() const
    {
        return rti::config::LibraryVersion();
    }

    /**
     * @brief Virtual destructor
     */
    virtual ~ProcessorPlugin() {}

};

} } }


#include <rti/routing/processor/detail/ProcessorPluginForwarder.hpp>


/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @brief Utility macro that declares a native extern function that can
 * be used to load a ProcessorPlugin through a shared library.
 *
 * The prototype of the function is given by a native definition of the
 * create operation.
 *
 * To register a ProcessorPlugin with @product, you must use the tag
 * &lt;processor_plugin&gt; within &lt;plugin_library&gt;. For example:
 *
 * \code
 * <dds>
 *     ...
 *      <plugin_library name="MyPluginLib">
 *          <processor_plugin name="MyProcessorPlugin">
 *              <dll>myprocessor</dll>
 *              <create_function>
 *                 MyProcessorPlugin_create
 *             </create_function>
 *         </processor_plugin>
 *         ...
 *      </plugin_library>
 *      ...
 *      <routing_service>
 *      ...
 *      </routing_service>
 *      ...
 * </dds>
 * \endcode
 *
 * Once a ProcessorPlugin is registered, a Route can use it to create a
 * Processor.
 *
 * For example:
 *
 * \code
 * <topic_route name="SquareAndCircleToTriangle">
 *    ...
 *    <processor plugin_name="MyPluginLib::MyProcessorPlugin">
 *        <property>
 *            <value>
 *                <element>
 *                    <name>my_property_name</name>
 *                    <value>my_property_value</value>
 *                </element>
 *            </value>
 *        </property>
 *    </processor>
 *    <input participant="DomainIn">
 *        <topic_name>Square</topic_name>
 *        <registered_type_name>ShapeType</registered_type_name>
 *    </input>
 *    <input participant="DomainIn">
 *        <topic_name>Circle</topic_name>
 *        <registered_type_name>ShapeType</registered_type_name>
 *    </input>
 *    <output participant="DomainOut">
 *        <topic_name>Triangle</topic_name>
 *        <registered_type_name>ShapeType</registered_type_name>
 *    </output>
 * </topic_route>
 * \endcode
 *
 * For additional information on configuring Processors, see the
 * \ref_url_routing_service_users_manual.
 *
 * @param PROCESSOR_CLASS
 *        Class name of a ProcessorPlugin implementation
 */
#define RTI_PROCESSOR_PLUGIN_CREATE_FUNCTION_DECL(PROCESSOR_CLASS) \
extern "C" RTI_USER_DLL_EXPORT struct RTI_RoutingServiceProcessorPlugin* \
    PROCESSOR_CLASS ## _create_processor_plugin(\
        const struct RTI_RoutingServiceProperties *, \
        RTI_RoutingServiceEnvironment *); \

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @brief Utility macro that implements the ProcessorPlugin entry point
 * declared with RTI_PROCESSOR_PLUGIN_CREATE_FUNCTION_DECL.
 */
#define RTI_PROCESSOR_PLUGIN_CREATE_FUNCTION_DEF(PROCESSOR_CLASS) \
struct RTI_RoutingServiceProcessorPlugin * PROCESSOR_CLASS ## _create_processor_plugin( \
        const struct RTI_RoutingServiceProperties * native_properties, \
        RTI_RoutingServiceEnvironment *environment) \
{ \
    PropertySet properties; \
    rti::routing::PropertyAdapter::add_properties_from_native(\
            properties,\
            native_properties); \
    try { \
        return rti::routing::processor::detail::ProcessorPluginForwarder::create_plugin(\
                new PROCESSOR_CLASS(properties)); \
    } catch (const std::exception& ex) {\
        RTI_RoutingServiceEnvironment_set_error(\
                environment,\
                "%s",\
                ex.what());\
    } catch (...) {}\
    \
    return NULL; \
}



#endif // RTI_ROUTING_PROCESSOR_PROCESSOR_PLUGIN_HPP_
