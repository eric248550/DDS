/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_PROCESSOR_HPP_
#define RTI_ROUTING_PROCESSOR_PROCESSOR_HPP_

#include <dds/core/Value.hpp>
#include <dds/core/SafeEnumeration.hpp>
#include <rti/core/NativeValueType.hpp>

#include "routingservice/routingservice_processor.h"

#include <rti/routing/processor/Route.hpp>
#include <rti/routing/UpdatableEntity.hpp>

namespace rti { namespace routing { namespace processor {

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::Processor
 *
 * @brief Processor interface definition. Provides a way to process Route events
 *        and control the data forwarding process.
 *
 * A Processor receives event notifications from its Route owner in the form of
 * operation callbacks. Each event occurrence will be dispatched to the Processor
 * by calling the corresponding method.
 *
 * Each dispatching method has a signature according to the event kind and data
 * it is associated with. Each event is associated with a Route state; hence
 * limitations and constraints may apply individually to each method.
 *
 * Note that throwing an exception while processing any of the
 * event notifications is allowed. In this situation, the Route owner will
 * reject the events and none of the associated post conditions will be applied,
 * including state transitions.
 *
 * @mtsafety Partially Safe
 *           All operations on a concrete Processor object are safe and
 *           always serialized on a given Session. Operations on different
 *           Processor objects may be called concurrently if they belong
 *           to different Routes.
 *
 * @see ProcessorPlugin
 * @see Route
 */
class Processor : public rti::routing::UpdatableEntity {
public:


    /**
     * @brief Notification of the \c INPUT_ENABLED event.
     *
     * This operation is called when an Input enabled event occurs that
     * affects any of the inputs contained in the owner Route.
     *
     * This operation is called right after the affected Input has been enabled.
     *
     * A running Routing Service instance will produce a log indicating the occurrence
     * of the event. For example:
     *
     * \code
     * [.../sessions/Session/routes/Route/inputs/Input1|ENABLE] stream=Example
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     * @param[in] input
     *            The just enabled Input.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p input
     *        to be automatically disabled right after.
     */
    virtual void on_input_enabled(
            Route& route,
            rti::routing::processor::Input& input) = 0;

    /**
     * @brief Notification of the Input disabled event.
     *
     * This operation is called when an \c INPUT_DISABLED event occurs that
     * affects any of the inputs contained in the owner Route.
     *
     * This operation is called right before the affected Input is disabled.
     *
     * A running Routing Service instance will produce a log indicating the occurrence
     * of the event. For example:
     *
     * \code
     * [.../sessions/Session/routes/Route/inputs/Input1|DISABLE] stream=Example
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     * @param[in] input
     *            The Input about to be disabled.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p input
     *        to remain enabled.
     */
    virtual void on_input_disabled(
            Route& route,
            rti::routing::processor::Input& input) = 0;

    /**
     * @brief Notification of the Output enabled event.
     *
     * This operation is called when an \c OUTPUT_DISABLED event occurs that
     * affects any of the outputs contained in the owner Route.
     *
     * This operation is called right after the affected Output has been enabled.
     *
     * A running Routing Service instance will produce a log indicating the occurrence
     * of the event. For example:
     *
     * \code
     * [.../sessions/Session/routes/Route/outputs/Output1|ENABLE] stream=Example
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     * @param[in] output
     *            The just enabled output.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p output
     *        to be automatically disabled right after.
     */
    virtual void on_output_enabled(
            Route& route,
            rti::routing::processor::Output& output) = 0;

    /**
     * @brief Notification of the Output disabled event.
     *
     * This operation is called when an \c OUTPUT_DISABLED event occurs that
     * affects any of the outputs contained in the owner Route.
     *
     * This operation is called right before the affected Output is disabled.
     *
     * A running Routing Service instance will produce a log indicating the occurrence
     * of the event. For example:
     *
     * \code
     * [.../sessions/Session/routes/Route/outputs/Output1|DISABLE] stream=Example
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     * @param[in] output
     *            The Output about to be disabled.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p output
     *        to remain enabled.
     */
    virtual void on_output_disabled(
            Route& route,
            rti::routing::processor::Output& output) = 0;

    /**
     * @brief Notification of the Route started event.
     *
     * This operation is called right before the Route enters the \c STARTED
     * state. At the time this operation is called, all the inputs and outputs
     * within the Route are enabled.
     *
     * A running Routing Service instance will produce a log indicating the
     * occurrence of the event. For example:
     * \code
     * [.../domain_routes/DomainRoute/sessions/Session/routes/Route|START]
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p route
     *        to remain \c STOPPED.
     */
    virtual void on_start(Route& route) = 0;

    /**
     * @brief Notification of the Route stopped event.
     *
     * This operation is called right before the Route enters the \c STOPPED
     * state. At the time this operation is called, all the inputs and outputs
     * within the Route are still enabled.
     *
     * A running Routing Service instance will produce a log indicating the
     * occurrence of the event. For example:
     * \code
     * [.../domain_routes/DomainRoute/sessions/Session/routes/Route|STOP]
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p route
     *        to remain \c STARTED.
     *
     */
    virtual void on_stop(Route& route) = 0;

    /**
     * @brief Notification of the Route \c RUN event.
     *
     * This operation is called right before the Route enters the \c RUNNING
     * state. This operation is called after the Route went to \c STARTED after
     * a successful notification to this Processor,
     *
     * \note
     * If the Route was manually paused before via an Administration call, this
     * operation will not be called until a manual run operation is performed.
     *
     * A Routing Service running instance will produce a log indicating the occurrence
     * of the event. For example:
     * \code
     * [.../domain_routes/DomainRoute/sessions/Session/routes/Route|RUN]
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p route
     *        to remain \c PAUSED.
     *
     */
    virtual void on_run(Route& route) = 0;

    /**
     * @brief Notification of the Route stopped event.
     *
     * This operation is called right before the Route enters the \c PAUSED
     * state. At the time this operation is called, all the inputs and outputs
     * within the Route are still enabled.
     *
     * A Routing Service running instance will produce a log indicating the occurrence
     * of the event. For example:
     * \code
     * [.../domain_routes/DomainRoute/sessions/Session/routes/Route|PAUSE]
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     *
     * @throw std::exception
     *        Throwing an error in this operation will cause the \p route
     *        to remain \c RUNNING.
     *
     */
    virtual void on_pause(Route& route) = 0;

    /**
     * @brief Notification of the Route periodic action event.
     *
     * This operation is called periodically at the rate specified in the parent
     * Session of the Route owner.
     *
     * Periodic notifications can occur only while the Route is in the \c RUNNING
     * state.
     *
     * Implementations are allowed to access any of the Input and Output of the
     * owner Route to read and write data, respectively.
     *
     * A Routing Service running instance will produce a log indicating the occurrence
     * of the event. For example:
     * \code
     * [.../domain_routes/DomainRoute/sessions/Session/routes/Route]  process event=PERODIC_ACTION
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     *
     * @throw std::exception
     *        Throwing an error in this operation will produce a log message
     *        without affecting the Route state and notifications of this event
     *        to this Processor will keep occurring.
     */
    virtual void on_periodic_action(Route& route) = 0;

    /**
     * @brief Notification of the Route \c DATA_AVAILABLE event
     *
     * This operation is called each time any of the inputs contained in the
     * owner Route is notified about new data. Notifications of this event can
     * occur only while the Route is in the \c RUNNING state.
     *
     * Implementations are allowed to access any of the Input and Output of the
     * owner Route to read and write data, respectively.
     *
     * A running Routing Service instance will produce a log indicating the
     * occurrence of the event. For example:
     * \code
     * [.../domain_routes/DomainRoute/sessions/Session/routes/Route] process event=DATA_ON_INPUTS
     * \endcode
     *
     *
     * @param[in] route
     *            Route owner that contains this Processor.
     *
     * @throw std::exception
     *        Throwing an error in this operation will produce a log message
     *        without affecting the Route state and notifications of this event
     *        to this Processor will keep occurring.
     *
     */
    virtual void on_data_available(Route& route) = 0;

    /**
     * @brief Virtual destructor
     */
    virtual ~Processor() {}
};


/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::NoOpProcessor
 *
 * @brief An empty implementation of the pure virtual interface
 * rti::routing::processor::Processor.
 *
 * Your Processor implementation can inherit from this class and override
 * just the methods that are of interest.
 */
class NoOpProcessor : public Processor {


    virtual void on_input_enabled(Route&, rti::routing::processor::Input&)
    {
    }

    virtual void on_input_disabled(Route&, rti::routing::processor::Input&)
    {
    }

    virtual void on_output_enabled(Route&, rti::routing::processor::Output&)
    {
    }

    virtual void on_output_disabled(Route&, rti::routing::processor::Output&)
    {
    }

    virtual void on_start(Route&)
    {
    }

    virtual void on_stop(Route&)
    {
    }

    virtual void on_run(Route&)
    {
    }

    virtual void on_pause(Route&)
    {
    }


    virtual void on_data_available(Route&)
    {
    }


    virtual void on_periodic_action(Route&)
    {
    }

};

} } }


#endif // RTI_ROUTING_PROCESSOR_PROCESSOR_HPP_
