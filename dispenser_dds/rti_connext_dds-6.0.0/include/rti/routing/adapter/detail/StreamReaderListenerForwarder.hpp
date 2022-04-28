/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_STREAM_READER_LISTENER_FORWARDER_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_STREAM_READER_LISTENER_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <routingservice/routingservice_adapter_new.h>

#include <rti/routing/adapter/StreamReader.hpp>
#include <rti/routing/adapter/DiscoveryStreamReader.hpp>

namespace rti { namespace routing { namespace adapter { namespace detail {

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::StreamReaderListener
 *
 * @brief Listener representation used by StreamReader to notify @product
 * when new data is available.
 *
 * When a StreamReader receives new data, it shall call
 * StreamReaderListener::on_data_available to wake up the associated Session. 
 * After that, the Session will invoke any of the StreamReader operations to
 * read the new data.               
 * 
 */
class StreamReaderListener {
public:
    
public:
    /**
     * @brief Operation to notify @product about data available on the
     * a StreamReader.
     *
     * @param stream_reader
     *        @rs_st_in Stream reader for which new data is available.
     *    
     */
    void on_data_available(
            rti::routing::adapter::StreamReader *stream_reader)
    {
        native_listener_.on_data_available(
                static_cast<void*>(stream_reader),
                native_listener_.listener_data);
    }
    
    
    StreamReaderListener(
            const RTI_RoutingServiceStreamReaderListenerExt *native_listener) :
            native_listener_(*native_listener)
    {
    }
    
    ~StreamReaderListener()
    {
    }
        
private:
    
    RTI_RoutingServiceStreamReaderListenerExt native_listener_;
    
};

}}}}

#endif // RTI_ROUTING_ADAPTER_DETAIL_STREAM_READER_LISTENER_FORWARDER_HPP_
