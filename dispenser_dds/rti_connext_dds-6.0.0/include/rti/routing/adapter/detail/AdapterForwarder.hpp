/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_ADAPTER_FORWARDER_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_ADAPTER_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <routingservice/routingservice_adapter_new.h>

#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/adapter/detail/ConnectionForwarder.hpp>

namespace rti { namespace routing { namespace adapter { namespace detail {


class AdapterForwarder {
public:
    static RTI_RoutingServiceAdapterPluginExt * create_plugin(
            AdapterPlugin *adapter_plugin)
    {
        RTI_RoutingServiceAdapterPluginExt *native_adapter = NULL;
        RTIOsapiHeap_allocateStructure(
                &native_adapter,
                struct RTI_RoutingServiceAdapterPluginExt);
        rti::core::check_create_entity(
                native_adapter,
                "RTI_RoutingServiceAdapterPluginExt");
        RTI_RoutingServiceAdapterPluginExt_initialize(native_adapter);
        
        // Set adapter version
        rti::config::LibraryVersion version =  adapter_plugin->get_version();
        native_adapter->plugin_version.major = version.major_version();
        native_adapter->plugin_version.minor = version.minor_version();
        native_adapter->plugin_version.release = version.release_version();
        
        // Initialize adapter methods
        native_adapter->adapter_plugin_data =
                static_cast<void *>(adapter_plugin);
        native_adapter->plugin_delete =
                AdapterForwarder::delete_plugin;
        native_adapter->create_connection =
                AdapterForwarder::create_connection;
        native_adapter->delete_connection =
                AdapterForwarder::delete_connection;
        
        
        return native_adapter;
    }        

    static void delete_plugin(
        RTI_RoutingServiceAdapterPluginExt *native_adapter,
        RTI_RoutingServiceEnvironment *)
    {
        AdapterPlugin *adapter = static_cast<AdapterPlugin *>(
                native_adapter->adapter_plugin_data);
        // Plug-in is destructor not allowed to throw
        delete adapter;
        RTIOsapiHeap_freeStructure(native_adapter);
    }

    static RTI_RoutingServiceConnectionExt* create_connection(
            void *native_adapter_data,
            const char *routing_service_name,
            const char *routing_service_group_name,
            const RTI_RoutingServiceStreamReaderListenerExt *native_output_stream_listener,
            const RTI_RoutingServiceStreamReaderListenerExt *native_input_stream_listener,
            const RTI_RoutingServiceTypeInfo **registered_types,
            int registered_type_count,
            const RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {                       
        return ConnectionForwarder::create_native(
                static_cast<AdapterPlugin *>(native_adapter_data),
                routing_service_name,
                routing_service_group_name,
                native_output_stream_listener,
                native_input_stream_listener,
                registered_types,
                registered_type_count,
                native_properties,
                environment);
    }

    static void delete_connection(
            void *native_adapter_data,
            RTI_RoutingServiceConnectionExt *native_connection,
            RTI_RoutingServiceEnvironment *environment)
    {        
        ConnectionForwarder::delete_native(
                static_cast<AdapterPlugin *>(native_adapter_data),
                native_connection,
                environment);      
    }
    
};


}}}}

#endif // RTI_ROUTING_ADAPTER_DETAIL_ADAPTER_FORWARDER_HPP_
