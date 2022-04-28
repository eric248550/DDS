/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_TRANSF_TRANSFORMATION_PLUGIN_HPP_
#define RTI_ROUTING_TRANSF_TRANSFORMATION_PLUGIN_HPP_

#include "routingservice/routingservice_log.h"

#include <rti/config/Version.hpp>
#include <rti/routing/TypeInfo.hpp>
#include <rti/routing/PropertySet.hpp>
#include <rti/routing/transf/Transformation.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

/*e \file
  @brief RTI Routing Service Transformation API
*/
/** @defgroup RTI_RoutingServiceTransformationModule  RTI Routing Service Transformation API
 * @ingroup ROUTER
 * @brief This module describes the Transformation API.
 *
 * An @product Output transforms the incoming data using a @em transformation,
 * which is an object created by a transformation plugin.<br>
 * 
 */

namespace rti { namespace routing { namespace transf {

/** @ingroup RTI_RoutingServiceTransformationModule
 *
 * @class rti::routing::transf::TransformationPlugin
 * 
 * @brief The top-level plug-in class.
 *
 * Represents a factory of Transformation.
 */
class TransformationPlugin {
public:         

    /**
     * @brief Creates an Output Transformation.
     *
     * This function is called when the Output containing the transformation
     * is enabled.
     *
     * The format associated with the input and output types depends on
     * the format provided by the input and output adapters.
     *
     * For the built-in DDS adapter, the format of the types is DDS_TypeCode.
     * <b>Required:</b> yes
     *
     * @param input_type_info
     *        @rs_st_in Type information associated with the input samples.
     * @param output_type_info 
     *        @rs_st_in Type information associated with the output samples.
     * @param properties
     *        @rs_st_in Configuration properties for the Transformation.
     *        These properties corresponds to the properties specified within
     *        the tag &lt;transformation&gt;.
     *
     * @return New Transformation if successful. Cannot return @null_value.
     * @throw std::exception
     * @mtsafety Safe
     */
    virtual Transformation * create_transformation(
            const rti::routing::TypeInfo& input_type_info,
            const rti::routing::TypeInfo& output_type_info,
            const rti::routing::PropertySet& properties) = 0;

    /**
     * @brief Deletes a Transformation.
     * 
     * This function is called when the Output containing the transformation is
     * disabled.
     * 
     * @param transformation
     *        @rs_st_in Transformation to be deleted.
     * 
     * @throw std::exception
     * @mtsafety Safe
     */
    virtual void delete_transformation(Transformation *transformation) = 0;

    /**
     * @return  The version of this TransformationPlugin.
     *
     * Version is used for logging purposes and allows you to track which
     * version of the TransformationPlugin @product is using.
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
    virtual ~TransformationPlugin() {}
};

}}}

#include <rti/routing/transf/detail/TransformationPluginForwarder.hpp>

/** @ingroup RTI_RoutingServiceTransformationModule
 * 
 * @brief Utility macro that declares a native extern function that can
 * be used to load a TransformationPlugin through a shared library.
 *
 * The prototype of the function is given by 
 * RTI_RoutingServiceTransformationPlugin_CreateFcn.
 *
 * To register a transformation plugin with @product, you must use the tag
 * &lt;transformation_plugin&gt; within &lt;plugin_library&gt;. For example:
 *
 * \code
 * <dds>
 *     ...
 *      <plugin_library name="MyPluginLib">
 *          <transformation_plugin name="MyTransfPlugin">
 *              <dll>mytransformation</dll>
 *              <create_function>
 *                 MyTransfPlugin_create
 *             </create_function>
 *         </transformation_plugin>
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
 * Once a transformation plugin is registered, an Output can use it to create a
 * data transformation.
 *
 * For example:
 *
 * \code
 * <topic_route name="SquareSwitchCoord">
 *    <input participant="1">
 *        <topic_name>Square</topic_name>
 *        <registered_type_name>ShapeType</registered_type_name>
 *    </input>
 *    <output>
 *        <topic_name>Square</topic_name>
 *        <registered_type_name>ShapeType</registered_type_name>
 *        <transformation plugin_name="MyPluginLib::MyTransPlugin">
 *            <property>
 *                <value>
 *                    <element>
 *                        <name>X</name>
 *                        <value>Y</value>
 *                    </element>
 *                    <element>
 *                        <name>Y</name>
 *                        <value>X</value>
 *                    </element>
 *                </value>
 *            </property>
 *        </transformation>
 *    </output>
 * </topic_route>
 * \endcode
 *
 * For additional information on configuring transformations, see the
 * \ref_url_routing_service_users_manual.
 *
 * @param TRANSFORMATION_PLUGIN_CLASS 
 *        Class name of a TransformationPlugin implementation
 */
#define RTI_TRANSFORMATION_PLUGIN_CREATE_FUNCTION_DECL(TRANSFORMATION_PLUGIN_CLASS) \
extern "C" RTI_USER_DLL_EXPORT struct RTI_RoutingServiceTransformationPlugin * \
    TRANSFORMATION_PLUGIN_CLASS ## _create_transformation_plugin(\
        const struct RTI_RoutingServiceProperties *, \
        RTI_RoutingServiceEnvironment *); \

/** @ingroup RTI_RoutingServiceTransformationModule
 *
 * @brief Utility macro that implements the TransformationPlugin entry point
 * declared with RTI_TRANSFORMATION_PLUGIN_CREATE_FUNCTION_DECL.
 */
#define RTI_TRANSFORMATION_PLUGIN_CREATE_FUNCTION_DEF(TRANSFORMATION_PLUGIN_CLASS) \
struct RTI_RoutingServiceTransformationPlugin * \
    TRANSFORMATION_PLUGIN_CLASS ## _create_transformation_plugin( \
        const struct RTI_RoutingServiceProperties * native_properties, \
        RTI_RoutingServiceEnvironment *environment) \
{ \
    rti::routing::PropertySet properties; \
    rti::routing::PropertyAdapter::add_properties_from_native(\
            properties,\
            native_properties); \
    try { \
        return rti::routing::transf::detail::TransformationPluginForwarder::create_plugin(\
            new TRANSFORMATION_PLUGIN_CLASS(properties)); \
    } catch (const std::exception& ex) {\
        RTI_RoutingServiceEnvironment_set_error(\
                environment,\
                "%s",\
                ex.what());\
    } catch (...) {}\
    \
    return NULL; \
}




#endif // RTI_ROUTING_TRANSF_TRANSFORMATION_PLUGIN_HPP_
