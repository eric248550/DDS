/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_UPDATABLE_ENTITY_HPP_
#define RTI_ROUTING_UPDATABLE_ENTITY_HPP_

#include <map>
#include <string>

namespace rti { namespace routing {

/** @ingroup RTI_RoutingServiceInfrastructureModule
 *
 * @class rti::routing::UpdatableEntity
 *
 * @brief Defines a common interface for all the pluggable entities that can
 *        be updated at runtime.
 *
 * @product allows to update an pluggable entity through remote administration.
 * 
 * @mtsafety Safe
 *           The UpdatableEntity::update operation is called only for one
 *           entity at a time. Additionally, no other operations can be made
 *           concurrently on a pluggable entity during the
 *           UpdatableEntity::update call.
 */
class UpdatableEntity {
public:

    /**
     * @brief Updates a pluggable entity.
     *
     * @param properties
     *        @rs_st_in The new configuration properties, obtained as result
     *        of parsing the elements within the &lt;property&gt; tag
     *        corresponding to the entity being updated.
     */
    virtual void update(const std::map<std::string, std::string>& properties)
    {
        (void) properties;
    }

    /**
     * @brief Virtual destructor.
     */
    virtual ~UpdatableEntity() 
    {
    }
};

}}

#endif // RTI_ROUTING_UPDATABLE_ENTITY_HPP_
