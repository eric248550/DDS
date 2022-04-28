/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ROUTING_SERVICE_HPP_
#define RTI_ROUTING_ROUTING_SERVICE_HPP_

#include <dds/core/Reference.hpp>
#include <rti/config/Logger.hpp>

#include "routingservice/routingservice_adapter_new.h"

#include <rti/routing/ServiceProperty.hpp>
#include <rti/routing/detail/RoutingServiceImpl.hpp>
#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/processor/ProcessorPlugin.hpp>

namespace rti { namespace routing {

/*e \defgroup RTI_RoutingServiceLibModule RTI Routing Service API
 * \ingroup ROUTER
 * 
 * @brief @product  can be deployed as a native library linked into your
 * application in select architectures.
 *
 * This API allows you to create, configure and start @product instances from
 * your application.
 *
 * The following code shows the typical use of the API:
 *
 * \code
 *
 * int main ()
 * {
 *     rti::routing::RoutingService service(
 *             rti::routing::ServiceProperty()
 *             .cfg_file("MyRouter.xml")
 *             .cfg_name("MyRouter"));
 *     ...
 * 
 *     service.start();
 *
 *     while(keep_running) {
 *         sleep();
 *         ...
 *     }
 *
 *     return 0;
 * }
 *
 * \endcode
 *
 * Instead of a file, you can use XML strings to configure @product.
 * See ServiceProperty for more information.
 * <p>
 * To build your application you need to link with the @product native library
 * in <b> &lt;@ndds home&gt;/bin/&lt;architecture&gt;/ </b>.
 *
 * ### Development Requirements
 *
 * |                 | Unix-based Systems                      | Windows Systems           |
 * | --------------: | :----------------:                      | :-------------:           |
 * | Shared Libraries| libnddscpp2.so                          | nddscpp2.dll              |
 * | ^               | librtirsinfrastructure.so               | rtirsinfrastructure.dll   |
 * | ^               | librtidlc.so                            | rtidlc.dll                |
 * | ^               | libnddsmetp.so                          | nddsmetp.dll              |
 * | ^               | libnddsc.so                             | nddsc.dll                 |
 * | ^               | librtixml2.so                           | rtixml2.dll               |
 * | ^               | libnddscore.so                          | nddscore.dll              |
 * | Headers         | rti/routing/RoutingService.hpp          ||
 * 
 */

/** \ingroup RTI_RoutingServiceLibModule
 *
 * @brief The @product.
 *
 */
class RoutingService : public dds::core::Reference<RoutingServiceImpl> {
public:
    typedef dds::core::Reference<RoutingServiceImpl> Base;
    OMG_DDS_REF_TYPE_NOTYPENAME(
            RoutingService,
            dds::core::Reference,
            RoutingServiceImpl);

    /**
     * @brief Creates a @product instance
     *
     * @param property
     *        @rs_st_in The property to configure @product instance.
     * 
     */
    explicit RoutingService(const ServiceProperty& property)
            : Base(new RoutingServiceImpl(property))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    RoutingService(const RTI_RoutingServiceProperty& property)
            : Base(new RoutingServiceImpl(property))
    {
        this->delegate()->remember_reference(this->delegate());
    }
    
    explicit RoutingService(Base::DELEGATE_REF_T reference) : Base(reference)
    {
        if (this->delegate()) {
            this->delegate()->remember_reference(this->delegate());
        }
    }

    /**
     * @brief Starts @product.
     *
     * This is a non-blocking operation. @product will create its own set of
     * threads to perform its tasks.
     */
    void start()
    {
        this->delegate()->start();
    }

    /**
     * @brief Stops @product.
     *
     * This operation will bloc the instance is fully stopped.
     */
    void stop()
    {
        this->delegate()->stop();
    }

    /**    
     * @brief Attaches an Adapter plugin to be used by @product when it is
     * started.
     *
     * By using this function an adapter can be statically compiled, created
     * in your application and have the service load it, instead of registering
     * a shared library and a create function in the configuration.
     *
     * The name passed in this function is the name that has to be used in the
     * configuration to instantiate connections from the plugin.
     *
     * Example:
     *
     * \code
     *
     * rti::routing::RoutingService service(property);
     *
     * service.attach_adapter_plugin(myAdapter, "rti.test.cpp.TestAdapter");
     *
     * service.start();
     * ...
     *
     * \endcode
     *
     * And our configuration would look like this:
     *
     * \code
     * <dds>
     *  <!-- No need to register the plugin in
     *       <adapter_library><adpater_plugin>
     *  -->
     *  <routing_service name="example">
     *   <domain_route name="myadapter_to_dds">
     *
     *     <connection name="MyConnection" plugin_name="MyAdapter">
     *        ...
     *     </connection>
     *
     *     ...
     *   </domain_route>
     *  </routing_service>
     * </dds>
     *
     * \endcode
     *
     * This function can be called as many times as desired to attach
     * several plugins.
     *
     * @pre Routing Service must not be started
     * 
     * @param adapter_plugin
     *        @rs_st_in The adapter plugin object to be attached. The object
     *        shall remain alive during the execution of the service. Once the
     *        plugin is attached, the memory is owned by @product and will delete
     *        it upon service stop.
     *
     * @param plugin_name
     *        @rs_st_in
     *        The name used for this plugin in the &lt;connection&gt;
     *        tag in the configuration.
     *
     */
    void attach_adapter_plugin(
            rti::routing::adapter::AdapterPlugin *adapter_plugin,
            const std::string& plugin_name)
    {         
        this->delegate()->attach_adapter_plugin(
                adapter_plugin,
                plugin_name);
    }

    /**
     * @brief Attaches a Processor plugin to be used by @product when it is
     * started.
     *
     * @see attach_adapter_plugin
     */
    void attach_processor_plugin(
            rti::routing::processor::ProcessorPlugin *processor_plugin,
            const std::string& plugin_name)
    {
        this->delegate()->attach_processor_plugin(
                processor_plugin,
                plugin_name);
    }

     /**
     * @brief Attaches a Transformation plugin to be used by @product when it
      * is started.
     *
     * @see attach_adapter_plugin
     */
    void attach_transformation_plugin(
            rti::routing::transf::TransformationPlugin *transformation_plugin,
            const std::string& plugin_name)
    {         
        this->delegate()->attach_transformation_plugin(
                transformation_plugin,
                plugin_name);
    }


    /**
     * @brief Finalizes global resources that @product requires to operate.
     *
     * This operation releases resources specific to @product only. @ndds
     * global state shall be released separately through the
     * DomainParticipantFactory's finalize_instance().
     *
     * This operation should be called by your application only upon exit, after
     * all service instances have been deleted. Calling it at a different time may
     * cause the application to crash.
     *
     * @mtsafety unsafe. Applications are not allowed to call this operation
     * concurrently
     *
     * @throw std::exception
     */
    static void finalize_globals()
    {
        RoutingServiceImpl::finalize_globals();
    }

};

/** \ingroup RTI_RoutingServiceLibModule
 *
 * @brief The singleton type used to configure @product verbosity
 *
 * For configuring other aspects such as output file, print format or
 * RTI Connext specific logging, use rti::config::Logger.
 */
class Logger
{
public:

    typedef rti::config::Verbosity Verbosity;
    typedef rti::config::LogCategory LogCategory;
    typedef rti::config::LoggerMode LoggerMode;
    typedef rti::config::PrintFormat PrintFormat;

    static Logger& instance()
    {
        static Logger singleton;
        return singleton;
    }

    /**
     * @brief Sets the verbosity for the log messages generated at the 
     * @product level.
     * 
     * @param verbosity
     *        @rs_st_in The verbosity of the service logs     
     */
    void service_verbosity(rti::config::Verbosity verbosity)
    {
        RTILogBitmap submodule_mask = ROUTER_SUBMODULE_MASK_ALL;
        ROUTERLog_setBitmaps(
                submodule_mask,
                static_cast<RTILogBitmap>(verbosity.underlying()));
    }

    /**
     * @brief Getter for the same attribute
     *
     * @see service_verbosity(rti::config::Verbosity)
     */
     rti::config::Verbosity service_verbosity()
    {
        RTILogBitmap submodule_mask = ROUTER_SUBMODULE_MASK_ALL;
        RTILogBitmap instrumentation_mask = ROUTER_SUBMODULE_MASK_ALL;
        ROUTERLog_getBitmaps(&submodule_mask, &instrumentation_mask);

        return static_cast<rti::config::Verbosity::type>(instrumentation_mask);
    }    

    virtual ~Logger()
    {
    }

private:

    Logger()
    {
    }
     // Disable copy
    Logger(const Logger&);
    Logger& operator=(const Logger&);
};

}}

#endif // RTI_ROUTING_ROUTING_SERVICE_HPP_
