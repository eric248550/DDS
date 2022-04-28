/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_DETAIL_UPDATABLE_ENTITY_FORWARDER_HPP_
#define RTI_ROUTING_DETAIL_UPDATABLE_ENTITY_FORWARDER_HPP_

#include <rti/core/Exception.hpp>
#include <rti/routing/UpdatableEntity.hpp>
#include <rti/routing/ServiceProperty.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace detail {


class UpdatableEntityForwarder {
public:   
    
    static void update(
            UpdatableEntity *updatable_entity,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {
        
        try {
            // Set properties
            PropertySet properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);
            updatable_entity->update(properties);
        } catch (const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
            return;
        }
    }
    
};

}}}

#endif // RTI_ROUTING_DETAIL_UPDATABLE_ENTITY_FORWARDER_HPP_
