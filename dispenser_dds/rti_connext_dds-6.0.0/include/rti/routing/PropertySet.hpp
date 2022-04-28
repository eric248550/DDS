/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROPERTY_SET_HPP_
#define RTI_ROUTING_PROPERTY_SET_HPP_

#include <map>

#include "routingservice/routingservice_infrastructure.h"
#include <rti/config/Version.hpp>

namespace rti { namespace routing {

inline
std::string app_name_property_name()
{
    return RTI_ROUTING_SERVICE_APP_NAME_PROPERTY_NAME;
}

inline
std::string group_name_property_name()
{
    return RTI_ROUTING_SERVICE_GROUP_PROPERTY_NAME;
}

inline
std::string version_property_name()
{
    return RTI_ROUTING_SERVICE_VERSION_PROPERTY_NAME;
}

inline
std::string verbosity_property_name()
{
    return RTI_ROUTING_SERVICE_VERBOSITY_PROPERTY_NAME;
}

inline
std::string entity_resource_name_property_name()
{
    return RTI_ROUTING_SERVICE_ENTITY_RESOURCE_NAME_PROPERTY_NAME;
}
/** @ingroup RTI_RoutingServiceInfrastructureModule
 *
 * @brief The definition of a pluggable entity’s configuration properties.
 *
 * Configuration properties for an entity are obtained as a result of parsing
 * the &lt;property&gt; corresponding to each pluggable entity. The result is a 
 * map keyed by property name,  represented as std::string, whose values are 
 * the property values, also represented as std::string. Hence, a property name
 * shall be unique for each set of entity properties.
 */
typedef std::map<std::string,std::string> PropertySet;

}}

#endif // RTI_ROUTING_PROPERTY_SET_HPP_
