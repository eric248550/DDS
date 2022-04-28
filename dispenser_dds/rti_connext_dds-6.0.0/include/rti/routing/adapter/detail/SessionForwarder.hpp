/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_SESSION_FORWARDER_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_SESSION_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <rti/routing/adapter/Connection.hpp>
#include <rti/routing/detail/UpdatableEntityForwarder.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace adapter { namespace detail {


class SessionForwarder {
public:
    static RTI_RoutingServiceSessionExt* create_native(
            Connection *connection,
            const RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {               
        
        try {
            // Set properties
            std::map<std::string, std::string> properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);

            SessionForwarder *forwarder = new SessionForwarder();
            ScopedForwarder<Connection, SessionForwarder> scoped(
                    connection,
                    forwarder,
                    environment);
            // Create session: Note we don't check for NULL because a Session
            // is not required
            forwarder->session_ = connection->create_session(properties);
            
            scoped.release();
            return forwarder->native();
        } catch(const std::exception& ex) {
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
            Connection *connection,
            RTI_RoutingServiceSessionExt *native_session,
            RTI_RoutingServiceEnvironment *environment)
    {
        SessionForwarder *forwarder = static_cast<SessionForwarder*>(
                native_session->session_data);
        try {
            // delete session
            if (forwarder->session_ != NULL) {
                connection->delete_session(forwarder->session_);
                forwarder->session_ = NULL;
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
    
    Session * session()
    {
        return session_;
    }

    RTI_RoutingServiceSessionExt* native()
    {
        return &this->native_;
    }
    
    static void update(
            void *native_session_data,
            const struct RTI_RoutingServiceProperties * native_properties,
            RTI_RoutingServiceEnvironment * environment)
    {
        SessionForwarder *forwarder =
                static_cast<SessionForwarder*> (native_session_data);

        rti::routing::detail::UpdatableEntityForwarder::update(
                forwarder->session_,
                native_properties,
                environment);
    }
    
private:    
    SessionForwarder() : session_(NULL)
    {
        RTIOsapiMemory_zero(&native_, sizeof(native_));
        native_.session_data =
                static_cast<void*>(this);
        native_.update =
                SessionForwarder::update;
    }

    ~SessionForwarder()
    {
    }
    
private:
    RTI_RoutingServiceSessionExt native_;
    Session *session_;
    
};

}}}}

#endif // RTI_ROUTING_ADAPTER_DETAIL_SESSION_FORWARDER_HPP_
