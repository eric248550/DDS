/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_STREAM_INFO_HPP_
#define RTI_ROUTING_ADAPTER_STREAM_INFO_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>


#include <routingservice/routingservice_infrastructure.h>
#include <dds/core/Value.hpp>
#include <dds/core/Exception.hpp>
#include <rti/core/NativeValueType.hpp>
#include <rti/routing/TypeInfo.hpp>

namespace rti { namespace routing {

/** @ingroup RTI_RoutingServiceInfrastructureModule
 *
 */

class StreamInfoAdapter {
public:
    typedef RTI_RoutingServiceStreamInfo native_type;

    static void initialize(native_type& native_value)
    {
        RTIOsapiMemory_zero(
                &native_value, 
                sizeof (RTI_RoutingServiceStreamInfo));
    }

    static void finalize(native_type& native_value)
    {        
        TypeInfoAdapter::finalize(native_value.type_info);
        if (native_value.stream_name != NULL) {
            DDS_String_free(native_value.stream_name); 
            native_value.stream_name = NULL;
        }
    }

    static void copy(native_type& destination, const native_type& source)
    {        
        char *result = DDS_String_replace(
                &destination.stream_name,
                source.stream_name);
        if (source.stream_name != NULL && result == NULL) {
            throw std::bad_alloc();
        }
        destination.disposed = source.disposed;        
        TypeInfoAdapter::copy(
                destination.type_info,
                source.type_info);
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        if (strcmp(first.stream_name, second.stream_name) != 0) {
            return false;
        }
        if (first.disposed != second.disposed) {
            return false;
        }
        return TypeInfoAdapter::equals(first.type_info, second.type_info);
    }

};

class StreamInfo;

}

// native_type_traits needs to be defined in rti::core
namespace core {

template <>
struct native_type_traits<rti::routing::StreamInfo> {
    typedef rti::routing::StreamInfoAdapter adapter_type;
    typedef RTI_RoutingServiceStreamInfo native_type;
};

}

namespace routing {

/** @ingroup RTI_RoutingServiceInfrastructureModule
 *
 * @class rti::routing::StreamInfo
 *
 * @brief Definition of the stream information that @product needs to manage
 * user data streams.
 *
 * A stream in @product is a typed data channel to consume/produce data
 * in a data domain.
 * 
 */
class StreamInfo : public rti::core::NativeValueType<StreamInfo> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(StreamInfo)

    typedef rti::core::NativeValueType<StreamInfo> Base;
public:

    /**
     * @brief Constructs a StreamInfo with the minimum required information.
     * 
     * @param the_stream_name
     *        @rs_st_in The name of the stream.
     * @param the_type_name
     *        @rs_st_in The name of the type associated with the data in the
     *        stream.
     */
    StreamInfo(
            const std::string& the_stream_name,
            const std::string& the_type_name)
    {
        stream_name(the_stream_name);
        type_info().type_name(the_type_name);
    }

    StreamInfo(const RTI_RoutingServiceStreamInfo &native_stream_info)
            : Base(native_stream_info)
    {
    }

    /**
     * @brief Getter (see setter with the same name)    
     */
    bool disposed() const
    {
        return native().disposed ? true : false;
    }

    /**
     * @brief Sets the dispose flag in this object.
     *
     * Indicates whether the stream is a newly discovered stream  or a
     * disposed stream that no longer exists.
     *
     * @param the_disposed
     *         @rs_st_in true if the stream is marked as disposed or false
     *         otherwise.
     */
    StreamInfo& disposed(bool the_disposed) 
    {
        native().disposed = the_disposed ? 1 : 0;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    std::string stream_name() const
    {
        return native().stream_name;
    }

    /**
     * @brief Sets the name of the stream
     *
     * @param the_stream_name
     *         @rs_st_in Name of the stream.
     */
    StreamInfo& stream_name(const std::string& the_stream_name)
    {
        if (DDS_String_replace(
                &native().stream_name,
                the_stream_name.c_str()) == NULL) {
            throw std::bad_alloc();
        }

        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    TypeInfo& type_info()
    {
        using namespace rti::core::native_conversions;
        
        return cast_from_native<TypeInfo>(native().type_info);
    }

    /**
     * @brief Sets the type information associated with the stream.
     *
     * @see TypeInfo.
     */
    const TypeInfo& type_info() const
    {   
        using namespace rti::core::native_conversions;
        
        return cast_from_native<TypeInfo>(native().type_info);
    }
    
};

}}

#endif // RTI_ROUTING_ADAPTER_STREAM_INFO_HPP_
