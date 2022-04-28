/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_PLUGIN_DETAIL_PROCESSOR_PLUGIN_FORWARDER_HPP_
#define RTI_ROUTING_PROCESSOR_PLUGIN_DETAIL_PROCESSOR_PLUGIN_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <rti/routing/processor/ProcessorPlugin.hpp>
#include <rti/routing/processor/detail/ProcessorForwarder.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace processor { namespace detail {


class ProcessorPluginForwarder {
public:

    static RTI_RoutingServiceProcessorPlugin * create_plugin(
            ProcessorPlugin *plugin)
    {      
        RTI_RoutingServiceProcessorPlugin *native_plugin = NULL;
        RTIOsapiHeap_allocateStructure(
                &native_plugin,
                struct RTI_RoutingServiceProcessorPlugin);
        rti::core::check_create_entity(
                native_plugin,
                "RTI_RoutingServiceProcessorPlugin");
        RTI_RoutingServiceProcessorPlugin_initialize(native_plugin);

        // Set adapter version
        rti::config::LibraryVersion version =  plugin->get_version();
        native_plugin->plugin_version.major = version.major_version();
        native_plugin->plugin_version.minor = version.minor_version();
        native_plugin->plugin_version.release = version.release_version();        

        // Initialize native implementation
        native_plugin->processor_plugin_data = 
                static_cast<void *>(plugin);
        native_plugin->plugin_delete =
                ProcessorPluginForwarder::delete_plugin;
        native_plugin->create_processor = 
                ProcessorPluginForwarder::forward_create_processor;
        native_plugin->delete_processor =
                ProcessorPluginForwarder::forward_delete_processor;

        return native_plugin;
    }

    static void delete_plugin(
        RTI_RoutingServiceProcessorPlugin *native_plugin,
        RTI_RoutingServiceEnvironment *)
    {
        ProcessorPlugin *plugin = static_cast<ProcessorPlugin*>(
                native_plugin->processor_plugin_data);
        // Plug-in is destructor not allowed to throw
        delete plugin;
        RTIOsapiHeap_freeStructure(native_plugin);
    }


    static RTI_RoutingServiceProcessor * forward_create_processor(
        void *native_plugin_data,
        RTI_RoutingServiceRoute *native_route,
        const struct RTI_RoutingServiceProperties *native_properties,
        RTI_RoutingServiceEnvironment *environment)
    {
        return ProcessorForwarder::create_native(
                static_cast<ProcessorPlugin *>(native_plugin_data),
                native_route,
                native_properties,
                environment);

    }

    static void forward_delete_processor(
            void *native_plugin_data,
            struct RTI_RoutingServiceProcessor *native_processor,
            RTI_RoutingServiceRoute *,
            RTI_RoutingServiceEnvironment *environment)
    {

        ProcessorForwarder::delete_native(
                static_cast<ProcessorPlugin *>(native_plugin_data),
                native_processor,
                environment);
    }

};

}}}}

#endif // RTI_ROUTING_PROCESSOR_PLUGIN_DETAIL_PROCESSOR_PLUGIN_FORWARDER_HPP_
