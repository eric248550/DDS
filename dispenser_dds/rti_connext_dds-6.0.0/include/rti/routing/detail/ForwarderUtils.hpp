/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_DETAIL_ForwarderType_UTILS_HPP_
#define RTI_ROUTING_DETAIL_ForwarderType_UTILS_HPP_

#include <map>

#include <rti/core/Exception.hpp>
#include <routingservice/routingservice_infrastructure.h>

#define RTI_ROUTING_THROW_ON_NULL(pointer) \
    if ((pointer) == NULL) { \
        throw dds::core::Error("invalid return of NULL"); \
    }

#define RTI_ROUTING_THROW_ON_ENV_ERROR(NATIVE_ENV) \
    if (RTI_RoutingServiceEnvironment_error_occurred((NATIVE_ENV))) { \
            dds::core::Error rex( \
                    RTI_RoutingServiceEnvironment_get_error_message((NATIVE_ENV))); \
            RTI_RoutingServiceEnvironment_clear_error((NATIVE_ENV)); \
            throw rex; \
    }

#define RTI_ROUTING_SAMPLE_VECTOR_COPY_FROM_NATIVE( \
        VECTOR, \
        NATIVE_ARRAY, \
        ARRAY_LENGTH) \
    (VECTOR).resize((ARRAY_LENGTH)); \
    memcpy(&((VECTOR)[0]), \
            (NATIVE_ARRAY), \
            sizeof (void*) * (ARRAY_LENGTH));

#define RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS( \
        TO_VECTOR, \
        FROM_VECTOR) \
    (TO_VECTOR).resize((FROM_VECTOR).size()); \
    memcpy(&(TO_VECTOR[0]), &(FROM_VECTOR)[0], sizeof(void*) * (FROM_VECTOR).size());


template <typename OwnerType, typename ForwarderType>
struct ScopedForwarder {
    
    ScopedForwarder(
            OwnerType *owner,
            ForwarderType *forwarder,
            RTI_RoutingServiceEnvironment *environment)
        :owner_(owner), forwarder_(forwarder), environment_(environment)
    {
    }

    void release()
    {
        forwarder_ = NULL;
    }

    ~ScopedForwarder()
    {
        if (forwarder_ != NULL) {
            ForwarderType::delete_native(owner_, forwarder_->native(), environment_);
        }
    }

private:
    OwnerType *owner_;
    ForwarderType *forwarder_;
    RTI_RoutingServiceEnvironment *environment_;

};


#endif // RTI_ROUTING_DETAIL_ForwarderType_UTILS_HPP_
