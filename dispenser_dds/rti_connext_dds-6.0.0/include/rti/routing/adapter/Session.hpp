/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */
#ifndef RTI_ROUTING_ADAPTER_SESSION_HPP_
#define RTI_ROUTING_ADAPTER_SESSION_HPP_

#include <rti/routing/UpdatableEntity.hpp>

namespace rti { namespace routing { namespace adapter {

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::Session
 *
 * A Session is a concurrency unit within a Connection that has an associated 
 * set of StreamReaders and StreamWriter. Access to the StreamReader and
 * StreamWriters in the same Session is serialized by @product.
 *
 * In the XML configuration file, Sessions are associated with the tag
 * &lt;session&gt; within a DomainRoute.
 */
class Session : public UpdatableEntity {
    
public:

    /**
     * @brief Virtual destructor
     */
    virtual ~Session()
    {
    }
};

}}}

#endif // RTI_ROUTING_ADAPTER_SESSION_HPP_
