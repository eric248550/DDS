/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_CONNECTION_FORWARDER_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_CONNECTION_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <osapi/osapi_heap.h>
#include <routingservice/routingservice_adapter_new.h>

#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/adapter/detail/SessionForwarder.hpp>
#include <rti/routing/adapter/detail/StreamReaderForwarder.hpp>
#include <rti/routing/adapter/detail/StreamWriterForwarder.hpp>
#include <rti/routing/adapter/detail/DiscoveryStreamReaderForwarder.hpp>
#include <rti/routing/detail/UpdatableEntityForwarder.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace adapter { namespace detail {

class ConnectionForwarder {
public:    
    static RTI_RoutingServiceConnectionExt * create_native(
            AdapterPlugin *adapter,
            const char *,
            const char *,           
            const RTI_RoutingServiceStreamReaderListenerExt *native_output_stream_listener,
            const RTI_RoutingServiceStreamReaderListenerExt *native_input_stream_listener,
            const RTI_RoutingServiceTypeInfo **,
            int,
            const RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {
        try {
            // Set properties
            std::map<std::string, std::string> properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);

            ConnectionForwarder *forwarder = new ConnectionForwarder(
                    native_output_stream_listener,
                    native_input_stream_listener);
            ScopedForwarder<AdapterPlugin, ConnectionForwarder> scoped(
                    adapter,
                    forwarder,
                    environment);
            // Create connection
            forwarder->connection_ = adapter->create_connection(
                    &forwarder->input_discovery_listener_,
                    &forwarder->output_discovery_listener_,
                    properties);
            RTI_ROUTING_THROW_ON_NULL(forwarder->connection_);

            // Create built-in SRs
            forwarder->input_stream_discovery_forwarder_ = new DiscoveryStreamReaderForwarder(
                    forwarder->connection_->input_stream_discovery_reader());

            forwarder->output_stream_discovery_forwarder_ = new DiscoveryStreamReaderForwarder(
                    forwarder->connection_->output_stream_discovery_reader());
            
            scoped.release();
            return forwarder->native();
        } catch (const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
            return NULL;
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
            return NULL;
        }
    }
    
    static void delete_native(
            AdapterPlugin *adapter,
            RTI_RoutingServiceConnectionExt *native_connection,
            RTI_RoutingServiceEnvironment *environment)
    {
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection->connection_data);
        try {
            // delete built-in SRs
            delete forwarder->input_stream_discovery_forwarder_;
            delete forwarder->output_stream_discovery_forwarder_;
            
            // delete connection
            if (forwarder->connection_ != NULL) {
                adapter->delete_connection(forwarder->connection_);
                forwarder->connection_ = NULL;
            }                        
        } catch(const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment, 
                    "%s",
                    ex.what());
        } catch (...) {
        } 
               
        delete forwarder;
    }
   

    static RTI_RoutingServiceStreamReaderExt *
    get_input_stream_discovery_reader(
            void *native_connection_data,
            RTI_RoutingServiceEnvironment *)
    {
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection_data);
        return forwarder->input_stream_discovery_forwarder_->native();
    }
    
    static RTI_RoutingServiceStreamReaderExt *
    get_output_stream_discovery_reader(
            void *native_connection_data,
            RTI_RoutingServiceEnvironment *)
    {
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection_data);
        return forwarder->output_stream_discovery_forwarder_->native();
    }
    
    static RTI_RoutingServiceSessionExt * create_session(
        void *native_connection_data,
        const struct RTI_RoutingServiceProperties * native_properties,
        RTI_RoutingServiceEnvironment *environment) 
    {

        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection_data);

        return SessionForwarder::create_native(
                forwarder->connection_,
                native_properties,
                environment);
    }
    
    static void delete_session(
            void *native_connection_data,
            RTI_RoutingServiceSessionExt *native_session,
            RTI_RoutingServiceEnvironment *environment)
    {
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*> (
                native_connection_data);
        
        SessionForwarder::delete_native(
                forwarder->connection_,
                native_session,
                environment);
    }

    static RTI_RoutingServiceStreamReaderExt* create_stream_reader(
            void *native_connection_data,
            void *native_session_data,
            const struct RTI_RoutingServiceStreamInfo *native_stream_info,
            const struct RTI_RoutingServiceProperties *native_properties,
            const struct RTI_RoutingServiceStreamReaderListenerExt *native_listener,
            RTI_RoutingServiceEnvironment *environment)
    {        
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection_data);
        SessionForwarder *session_forwarder = static_cast<SessionForwarder*>(
                native_session_data);

        return StreamReaderForwarder::create_native(
                forwarder->connection_,
                session_forwarder->session(),
                native_stream_info,
                native_properties,
                native_listener,
                environment);
    }
    
    static void delete_stream_reader(
        void *native_connection_data,
        RTI_RoutingServiceStreamReaderExt *native_reader,
        RTI_RoutingServiceEnvironment *environment) 
    {        
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection_data);
        StreamReaderForwarder::delete_native(
                forwarder->connection_,
                native_reader,                
                environment);        
    }
    
    static RTI_RoutingServiceStreamWriterExt* create_stream_writer(
            void *native_connection_data,
            void *native_session_data,
            const struct RTI_RoutingServiceStreamInfo *native_stream_info,
            const struct RTI_RoutingServiceProperties *native_properties,
            const struct RTI_RoutingServiceStreamWriterListenerExt *,
            RTI_RoutingServiceEnvironment *environment)
    {        
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection_data);
        SessionForwarder *session_forwarder = static_cast<SessionForwarder*>(
                native_session_data);

        return StreamWriterForwarder::create_native(
                forwarder->connection_,
                session_forwarder->session(),
                native_stream_info,
                native_properties,
                environment);
    }
    
    static void delete_stream_writer(
        void *native_connection_data,
        RTI_RoutingServiceStreamWriterExt *native_writer,
        RTI_RoutingServiceEnvironment *environment) 
    {
        ConnectionForwarder *forwarder = static_cast<ConnectionForwarder*>(
                native_connection_data);
        StreamWriterForwarder::delete_native(
                forwarder->connection_,
                native_writer,                
                environment); 
    }

    static void update(
            void *native_connection_data,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {
        ConnectionForwarder *forwarder =
                static_cast<ConnectionForwarder*> (native_connection_data);

        rti::routing::detail::UpdatableEntityForwarder::update(
                forwarder->connection_,
                native_properties,
                environment);
    }    
    
    
    Connection * connection()
    {
        return connection_;
    }
    
    RTI_RoutingServiceConnectionExt* native()
    {
        return &this->native_;
    }
    
    RTI_RoutingServiceStreamReaderExt* native_input_discovery_reader()
    {
        return input_stream_discovery_forwarder_->native();
    }
    
    RTI_RoutingServiceStreamReaderExt* native_output_discovery_reader()
    {
        return output_stream_discovery_forwarder_->native();
    }

private:

    ConnectionForwarder(
            const RTI_RoutingServiceStreamReaderListenerExt *native_output_stream_listener,
            const RTI_RoutingServiceStreamReaderListenerExt *native_input_stream_listener) :
        connection_(NULL),
        output_stream_discovery_forwarder_(NULL),
        output_discovery_listener_(native_output_stream_listener),
        input_stream_discovery_forwarder_(NULL),
        input_discovery_listener_(native_input_stream_listener)
    {
        RTIOsapiMemory_zero(&native_, sizeof(native_));
        native_.connection_data =
                static_cast<void*>(this);
        native_.create_session =
                ConnectionForwarder::create_session;
        native_.delete_session =
                ConnectionForwarder::delete_session;
        native_.create_stream_reader =
                ConnectionForwarder::create_stream_reader;
        native_.delete_stream_reader =
                ConnectionForwarder::delete_stream_reader;
        native_.create_stream_writer =
                ConnectionForwarder::create_stream_writer;
        native_.delete_stream_writer =
                ConnectionForwarder::delete_stream_writer;
        native_.get_input_stream_discovery_reader =
                ConnectionForwarder::get_input_stream_discovery_reader;
        native_.get_output_stream_discovery_reader =
                ConnectionForwarder::get_output_stream_discovery_reader;
        native_.update =
                ConnectionForwarder::update;
    }

    ~ConnectionForwarder()
    {
    }
    
private:
    RTI_RoutingServiceConnectionExt native_;
    Connection *connection_;
    DiscoveryStreamReaderForwarder *output_stream_discovery_forwarder_;
    StreamReaderListener output_discovery_listener_;
    DiscoveryStreamReaderForwarder *input_stream_discovery_forwarder_;
    StreamReaderListener input_discovery_listener_;
    
};

}}}}

#endif // RTI_ROUTING_ADAPTER_DETAIL_CONNECTION_FORWARDER_HPP_
