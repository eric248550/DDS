/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ROUTING_SERVICE_IMPL_HPP_
#define RTI_ROUTING_ROUTING_SERVICE_IMPL_HPP_

#include <dds/core/refmacros.hpp>
#include <rti/core/detail/SelfReference.hpp>
#include "routingservice/routingservice_adapter.h"
#include "routingservice/routingservice_service.h"
#include "routingservice/routingservice_log.h"

#include <rti/routing/ServiceProperty.hpp>
#include <rti/routing/adapter/detail/AdapterForwarder.hpp>
#include <rti/routing/transf/detail/TransformationPluginForwarder.hpp>
#include <rti/routing/processor/detail/ProcessorPluginForwarder.hpp>


namespace rti { namespace routing {

class RoutingServiceImpl
        : public rti::core::detail::RetainableType<RoutingServiceImpl> {
public:
    explicit RoutingServiceImpl(const ServiceProperty& property)
    {
        native_ = RTI_RoutingService_new(&property.native());
        rti::core::check_create_entity(native_, "RoutingService");
    }

    RoutingServiceImpl(const RTI_RoutingServiceProperty& property)
            : native_(NULL)
    {
        native_ = RTI_RoutingService_new(&property);
        rti::core::check_create_entity(native_, "RoutingService");
    }
    
    RoutingServiceImpl(RTI_RoutingService *native)
            : native_(native)
    {        
        rti::core::check_create_entity(native_, "RoutingService");
    }    

    ~RoutingServiceImpl()
    {
        RTI_RoutingService_delete(native_);
    }

    void start()
    {
        if (!RTI_RoutingService_start(native_)) {
            throw dds::core::Error("failed to start RoutingService");
        }
    }

    void stop()
    {
        if (!RTI_RoutingService_stop(native_)) {
            throw dds::core::Error("failed to stop RoutingService");
        }
    }

    void attach_adapter_plugin(
            rti::routing::adapter::AdapterPlugin *adapter_plugin,
            const std::string& registered_name)
    {
        RTI_RoutingServiceAdapterPluginExt *native_plugin =
                adapter::detail::AdapterForwarder::create_plugin(adapter_plugin);
        if (!RTI_RoutingService_attach_adapter_plugin(
                native_,
                native_plugin,
                registered_name.c_str())) {
            throw dds::core::Error("failed to attach native adapter");
        }
    }
    
    void attach_transformation_plugin(
            rti::routing::transf::TransformationPlugin *transformation_plugin,
            const std::string& registered_name)
    {         
        RTI_RoutingServiceTransformationPlugin *native_plugin =
                transf::detail::TransformationPluginForwarder::create_plugin(
                        transformation_plugin);
        if (!RTI_RoutingService_attach_transformation_plugin(
                native_,
                native_plugin,
                registered_name.c_str())) {
            throw dds::core::Error("failed to attach native transformation");
        }
    }

    void attach_processor_plugin(
            rti::routing::processor::ProcessorPlugin *processor_plugin,
            const std::string& registered_name)
    {
        RTI_RoutingServiceProcessorPlugin *native_plugin =
                processor::detail::ProcessorPluginForwarder::create_plugin(
                        processor_plugin);
        if (!RTI_RoutingService_attach_processor_plugin(
                native_,
                native_plugin,
                registered_name.c_str())) {
            throw dds::core::Error("failed to attach native processor");
        }
    }

    RTI_RoutingService* native() const
    {
        return native_;
    }

    static void finalize_globals()
    {
        if (!RTI_RoutingService_finalize_globals()) {
            throw dds::core::Error("failed to finalize global state");
        }
    }

private:
    RTI_RoutingService *native_;
};

}}

#endif // RTI_ROUTINGv_ROUTING_SERVICE_IMPL_HPP_
