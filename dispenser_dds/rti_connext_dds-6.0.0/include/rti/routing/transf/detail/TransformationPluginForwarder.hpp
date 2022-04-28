/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_TRANSF_DETAIL_TRANSFORMATION_PLUGIN_FORWARDER_HPP_
#define RTI_ROUTING_TRANSF_DETAIL_TRANSFORMATION_PLUGIN_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <routingservice/routingservice_transformation.h>

#include <rti/routing/transf/TransformationPlugin.hpp>
#include <rti/routing/transf/detail/TransformationForwarder.hpp>

namespace rti { namespace routing { namespace transf { namespace detail {


class TransformationPluginForwarder {
public:
    static RTI_RoutingServiceTransformationPlugin * create_plugin(
            TransformationPlugin *transformation_plugin)
    {
        RTI_RoutingServiceTransformationPlugin *native_plugin = NULL;
        RTIOsapiHeap_allocateStructure(
                &native_plugin,
                struct RTI_RoutingServiceTransformationPlugin);
        rti::core::check_create_entity(
                native_plugin,
                "RTI_RoutingServiceTransformationPlugin");
        RTI_RoutingServiceTransformationPlugin_initialize(native_plugin);
        
        // Set adapter version
        rti::config::LibraryVersion version =  transformation_plugin->get_version();
        native_plugin->plugin_version.major = version.major_version();
        native_plugin->plugin_version.minor = version.minor_version();
        native_plugin->plugin_version.release = version.release_version();
        
        // Initiallize adapter methods
        native_plugin->user_object = static_cast<void *>(transformation_plugin);
        native_plugin->transformation_plugin_delete =
                TransformationPluginForwarder::delete_plugin;
        native_plugin->transformation_plugin_create_transformation =
                TransformationPluginForwarder::create_transformation;
        native_plugin->transformation_plugin_delete_transformation =
                TransformationPluginForwarder::delete_transformation;
        native_plugin->transformation_transform =
                TransformationForwarder::transform;
        native_plugin->transformation_return_loan =
                TransformationForwarder::return_loan;
        native_plugin->transformation_update =
                TransformationForwarder::update;          
        
        return native_plugin;
    }        

    static void delete_plugin(
        RTI_RoutingServiceTransformationPlugin *native_plugin,
        RTI_RoutingServiceEnvironment *)
    {
        TransformationPlugin *plugin = static_cast<TransformationPlugin *>(
                native_plugin->user_object);
        // Plug-in is destructor not allowed to throw
        delete plugin;
        RTIOsapiHeap_freeStructure(native_plugin);
    }

    static RTI_RoutingServiceTransformation create_transformation(
            struct RTI_RoutingServiceTransformationPlugin  *native_plugin,
            const struct RTI_RoutingServiceTypeInfo *input_type_info,
            const struct RTI_RoutingServiceTypeInfo *output_type_info,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment  *environment)
    {                       
        return TransformationForwarder::create_native(
                static_cast<TransformationPlugin *>(native_plugin->user_object),
                input_type_info,
                output_type_info,
                native_properties,
                environment);

    }

    static void delete_transformation(
            struct RTI_RoutingServiceTransformationPlugin *native_plugin,
            RTI_RoutingServiceTransformation native_transformation,
            RTI_RoutingServiceEnvironment *environment)
    {        
        TransformationForwarder::delete_native(
                static_cast<TransformationPlugin *>(native_plugin->user_object), 
                native_transformation,
                environment);      
    }
    
};


}}}}

#endif // RTI_ROUTING_TRANSF_DETAIL_TRANSFORMATION_PLUGIN_FORWARDER_HPP_
