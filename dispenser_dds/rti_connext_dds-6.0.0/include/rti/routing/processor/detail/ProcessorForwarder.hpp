/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_DETAIL_PROCESSOR_FORWARDER_HPP_
#define RTI_ROUTING_PROCESSOR_DETAIL_PROCESSOR_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include "routingservice/routingservice_processor_impl.h"
#include <rti/routing/detail/ForwarderUtils.hpp>
#include <rti/routing/detail/UpdatableEntityForwarder.hpp>
#include <rti/routing/processor/Route.hpp>
#include <rti/routing/processor/Input.hpp>
#include <rti/routing/processor/Output.hpp>

namespace rti { namespace routing { namespace processor { namespace detail {

class ProcessorForwarder  {

private:
    
    template <typename PORT, typename NATIVE>
    class ScopedPort {

    public:
        ScopedPort(Route& route,  int32_t index, NATIVE *native)
            : route_(route), 
              port_(new PORT(native, index, route.native_route_, route.native_env_))
        {
        }

        PORT* get()
        {
            return port_;
        }

        void clear()
        {
            port_ = NULL;
        }

        ~ScopedPort()
        {
            if (port_ != NULL) {
                delete port_;
                port_ = NULL;
            }
        }

    private:
        Route& route_;
        PORT *port_;
    };

public:

    static RTI_RoutingServiceProcessor * create_native(
            ProcessorPlugin *plugin, 
            RTI_RoutingServiceRoute *native_route,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {
        try {
            std::map<std::string, std::string> properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);

            ProcessorForwarder *forwarder = new ProcessorForwarder(
                    native_route,
                    environment);
            ScopedForwarder<ProcessorPlugin, ProcessorForwarder> scoped(
                    plugin,
                    forwarder,
                    environment);
            forwarder->processor_ = plugin->create_processor(
                    forwarder->route(),
                    properties);
            RTI_ROUTING_THROW_ON_NULL(forwarder->processor_);

            scoped.release();
            return forwarder->native();
        } catch(const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
            return NULL;
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
            return NULL;
        }


    }

    static void delete_native(
            ProcessorPlugin *plugin, 
            RTI_RoutingServiceProcessor *native_processor,
            RTI_RoutingServiceEnvironment *environment)
    {
        ProcessorForwarder *processor_forwarder =
                static_cast<ProcessorForwarder*>(native_processor->processor_data);
        try {
            if (processor_forwarder->processor_ != NULL) {
                plugin->delete_processor(
                        processor_forwarder->route_,
                        processor_forwarder->processor_);
                processor_forwarder->processor_ = NULL;
            }
        } catch(const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
        }

        delete processor_forwarder;
    }


    static void forward_on_route_event(
        void *native_processor_data,
        RTI_RoutingServiceRouteEvent *native_route_event,
        RTI_RoutingServiceEnvironment *environment)
    {

        ProcessorForwarder *forwarder =
                static_cast<ProcessorForwarder*>(native_processor_data);
        
        try {

            // build up wrapper objects based on the event
            switch (RTI_RoutingServiceRouteEvent_get_kind(native_route_event)) {

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_DATA_ON_INPUTS:
                forwarder->processor_->on_data_available(forwarder->route());
                break;
                
            case RTI_ROUTING_SERVICE_ROUTE_EVENT_PERIODIC_ACTION:

                forwarder->processor_->on_periodic_action(forwarder->route());
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_INPUT_ENABLED:
            {
                void *affected_entity =
                        RTI_RoutingServiceRouteEvent_get_affected_entity(native_route_event);             
                void *index =
                        RTI_RoutingServiceRouteEvent_get_event_data(native_route_event);
                ScopedPort<Input, RTI_RoutingServiceStreamReaderExt> port(
                        forwarder->route_,
                        *(static_cast<int32_t*>(index)),
                        static_cast<RTI_RoutingServiceStreamReaderExt *>(affected_entity));
                forwarder->processor_->on_input_enabled(
                        forwarder->route(),
                        *port.get());
                RTI_RoutingServiceRoute_set_stream_port_user_data(
                        forwarder->route_.native_route_,
                        static_cast<RTI_RoutingServiceStreamReaderExt *>(affected_entity)->stream_reader_data,
                        port.get());
                port.clear();

            }
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_INPUT_DISABLED:
            {

                void *affected_entity =
                        RTI_RoutingServiceRouteEvent_get_affected_entity(native_route_event);
                RTI_RoutingServiceStreamReaderExt *native_input =
                        static_cast<RTI_RoutingServiceStreamReaderExt *>(affected_entity);
                Input *input = reinterpret_cast<Input*>(
                        RTI_RoutingServiceRoute_get_stream_port_user_data(
                                forwarder->route_.native_route_,
                                native_input->stream_reader_data));
                forwarder->processor_->on_input_disabled(
                        forwarder->route(),
                        *input);
                RTI_RoutingServiceRoute_set_stream_port_user_data(
                        forwarder->route_.native_route_,
                        native_input->stream_reader_data,
                        NULL);
                delete input;
            }
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_OUTPUT_ENABLED:
            {
                void *affected_entity =
                        RTI_RoutingServiceRouteEvent_get_affected_entity(native_route_event);
                void *index =
                        RTI_RoutingServiceRouteEvent_get_event_data(native_route_event);
                ScopedPort<Output, RTI_RoutingServiceStreamWriterExt> port(
                        forwarder->route_,
                        *(static_cast<int32_t*>(index)),
                        static_cast<RTI_RoutingServiceStreamWriterExt *>(affected_entity));
                forwarder->processor_->on_output_enabled(
                        forwarder->route(),
                        *port.get());
                RTI_RoutingServiceRoute_set_stream_port_user_data(
                        forwarder->route_.native_route_,
                        static_cast<RTI_RoutingServiceStreamWriterExt *>(affected_entity)->stream_writer_data,
                        port.get());
                port.clear();

            }
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_OUTPUT_DISABLED:
            {
                void *affected_entity =
                        RTI_RoutingServiceRouteEvent_get_affected_entity(native_route_event);
                RTI_RoutingServiceStreamWriterExt *native_output =
                        static_cast<RTI_RoutingServiceStreamWriterExt *>(affected_entity);
                Output *output = reinterpret_cast<Output*>(
                        RTI_RoutingServiceRoute_get_stream_port_user_data(
                                forwarder->route_.native_route_,
                                native_output->stream_writer_data));
                forwarder->processor_->on_output_disabled(
                        forwarder->route(),
                        *output);
                RTI_RoutingServiceRoute_set_stream_port_user_data(
                        forwarder->route_.native_route_,
                        native_output->stream_writer_data,
                        NULL);
                delete output;
            }
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_STARTED:

                forwarder->processor_->on_start(forwarder->route());
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_STOPPED:

                forwarder->processor_->on_stop(forwarder->route());
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_RUNNING:

                forwarder->processor_->on_run(forwarder->route());
                break;

            case RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_PAUSED:

                forwarder->processor_->on_pause(forwarder->route());
                break;            

            default:
                break;
            };

        } catch (const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    "unexpected exception");
        }        
    }

    static void forward_update(
            void *native_processor_data,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {

        ProcessorForwarder *processorForwarder =
                static_cast<ProcessorForwarder*> (native_processor_data);

        rti::routing::detail::UpdatableEntityForwarder::update(
                processorForwarder->processor_,
                native_properties,
                environment);
    }

    RTI_RoutingServiceProcessor* native()
    {
        return &native_;
    }

private:

    ProcessorForwarder(
            RTI_RoutingServiceRoute *native_route,
            RTI_RoutingServiceEnvironment *native_env) :
            processor_(NULL),
            route_(native_route, native_env)
    {
        RTIOsapiMemory_zero(&native_, sizeof(native_));
        /* initialize native implementation */
        native_.processor_data =
                static_cast<void*>(this);
        native_.on_route_event =
                ProcessorForwarder::forward_on_route_event;
        native_.update =
                ProcessorForwarder::forward_update;
    }

    rti::routing::processor::Route& route()
    {
        return route_;
    }

    ~ProcessorForwarder()
    {
    }

private:
    RTI_RoutingServiceProcessor native_;
    Processor *processor_;
    rti::routing::processor::Route route_;

};

}}}}

#endif // RTI_ROUTING_PROCESSOR_DETAIL_PROCESSOR_FORWARDER_HPP_
