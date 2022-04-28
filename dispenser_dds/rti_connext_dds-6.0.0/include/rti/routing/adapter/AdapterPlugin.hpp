/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_ADAPTER_HPP_
#define RTI_ROUTING_ADAPTER_ADAPTER_HPP_

#include <map>

#include "routingservice/routingservice_infrastructure.h"
#include <rti/config/Version.hpp>
#include <rti/routing/adapter/StreamReaderListener.hpp>
#include <rti/routing/adapter/Connection.hpp>

/** @file
 * @brief \product C++ Adapter API
 */

namespace rti { namespace routing { namespace adapter {

/** @ingroup RTI_RoutingServiceAdapterModule
 * 
 * @class rti::routing::adapter::AdapterPlugin
 * @brief The top-level plug-in class. 
 *
 * Represents a factory of Connection.
 */
class AdapterPlugin {
public:         
    /**
     * @brief Creates a Connection.
     *
     * Connection objects are created when the domain routes that contain them
     * are enabled.
     *
     * @param input_stream_discovery_listener
     *        @rs_st_in The listener of the built-in @ref DiscoveryStreamReader 
     *        that notifies the discovery of new input streams.
     * @param output_stream_discovery_listener
     *        @rs_st_in The listener of the built-in  @ref DiscoveryStreamReader
     *        that notifies the discovery of new output streams.
     * @param properties
     *        @rs_st_in Configuration properties for the Connection.
     *        These properties corresponds to the properties specified within
     *        the tag &lt;connection&gt;.
     *
     * @return New Connection if successful. Cannot return @null_value.
     * 
     * @throw std::exception
     *
     * @mtsafety Safe
     */
    virtual Connection * create_connection(
            StreamReaderListener *input_stream_discovery_listener,
            StreamReaderListener *output_stream_discovery_listener,
            const PropertySet& properties) = 0;

    /**
     * @brief Deletes a Connection.
     *
     * Connection objects are deleted when the domain routes that contain them
     * are disabled or @product is stopped.
     * 
     * @param connection @rs_st_in Connection to be deleted
     *
     * @throw std::exception
     * 
     * @mtsafety Safe
     */
    virtual void delete_connection(Connection *connection) = 0;

    /**
     * @return  The version of this AdapterPlugin.
     *
     * Version is used for logging purposes and allows you to track which
     * version of the AdapterPlugin @product is using.
     *
     *Default implementation of this operation returns the version of the
     * required Connext libraries.
     */
    virtual rti::config::LibraryVersion get_version() const
    {
        return rti::config::LibraryVersion();
    }

    /**
     * @brief Virtual destructor
     */
    virtual ~AdapterPlugin() {}
};

}}}

#include <rti/routing/adapter/detail/AdapterForwarder.hpp>


/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @brief Utility macro that declares a native extern function that can
 * be used to load an AdapterPlugin through a shared library.
 *
 * The prototype of the function is given by
 * RTI_RoutingServiceAdapterPlugin_CreateFcn.
 *
 * To register an AdapterPlugin plugin with @product, you must use the tag
 * &lt;adapter_plugin&gt; within &lt;plugin_library&gt;. For example:
 *
 * \code
 * <dds>
 *     ...
 *      <plugin_library name="MyPluginLib">
            <adapter_plugin name="MyAdapterPlugin">
                <dll>mycadapter</dll>
                <create_function>
                    MyAdapterPlugin_create
                </create_function>
            </adapter_plugin>
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
 * Once an AdapterPlugin is registered, a Connection can refer to it as
 * follows:
 *
 * For example:
 *
 * \code
 * <dds>
 *     <routing_service name="example">
 *         <domain_route name="myadapter_to_dds">
 *
 *             <connection name="MyConnection" plugin_name="MyAdapter">                
 *                  <property>
 *                      <value>
 *                          <element>
 *                              <name>my_property_name</name>
 *                              <value>my_property_value</value>
 *                          </element>
 *                      </value>
 *                  </property>
 *             </connection>
 *
 *          ...
 *         </domain_route>
 *      </routing_service>
 * </dds>
 * \endcode
 *
 * For additional information on configuring adapters, see the
 * \ref_url_routing_service_users_manual.
 *
 * @param ADAPTER_CLASS
 *        Class name of an AdapterPlugin implementation
 */
#define RTI_ADAPTER_PLUGIN_CREATE_FUNCTION_DECL(ADAPTER_CLASS) \
extern "C" RTI_USER_DLL_EXPORT struct RTI_RoutingServiceAdapterPluginExt * \
    ADAPTER_CLASS ## _create_adapter_plugin(\
        const struct RTI_RoutingServiceProperties *, \
        RTI_RoutingServiceEnvironment *); \

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @brief Utility macro that implements the AdapterPlugin entry point declared
 * with RTI_ADAPTER_PLUGIN_CREATE_FUNCTION_DECL.
 */
#define RTI_ADAPTER_PLUGIN_CREATE_FUNCTION_DEF(ADAPTER_CLASS) \
struct RTI_RoutingServiceAdapterPluginExt * ADAPTER_CLASS ## _create_adapter_plugin( \
        const struct RTI_RoutingServiceProperties * native_properties, \
        RTI_RoutingServiceEnvironment *environment) \
{ \
    PropertySet properties; \
    rti::routing::PropertyAdapter::add_properties_from_native(\
            properties,\
            native_properties); \
    try { \
        return rti::routing::adapter::detail::AdapterForwarder::create_plugin(new ADAPTER_CLASS(properties)); \
    } catch (const std::exception& ex) {\
        RTI_RoutingServiceEnvironment_set_error(\
                environment,\
                "%s",\
                ex.what());\
    } catch (...) {}\
    \
    return NULL; \
}




#endif // RTI_ROUTING_ADAPTER_ADAPTER_HPP_
