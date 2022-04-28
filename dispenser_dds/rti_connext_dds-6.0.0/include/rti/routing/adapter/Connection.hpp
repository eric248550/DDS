/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_CONNECTION_HPP_
#define RTI_ROUTING_ADAPTER_CONNECTION_HPP_

#include <rti/routing/PropertySet.hpp>
#include <rti/routing/UpdatableEntity.hpp>
#include <rti/routing/adapter/Session.hpp>
#include <rti/routing/adapter/StreamWriter.hpp>
#include <rti/routing/adapter/StreamReader.hpp>
#include <rti/routing/StreamInfo.hpp>
#include <rti/routing/adapter/DiscoveryStreamReader.hpp>
#include <rti/routing/adapter/StreamReaderListener.hpp>

namespace rti { namespace routing { namespace adapter {

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::Connection
 *
 * @brief A Connection provides access to a data domain (such as a DDS domain
 * or a JMS network provider).
 *
 * In the XML configuration file, Connections are associated with the tag
 * &lt;connection&gt; within a domain route.
 */
class Connection : public UpdatableEntity {
    
public:
    /** 
     * @brief Creates a Session
     *
     * Session objects are created when the associated @product Sessions are
     * enabled. This operation is called once for each service Session and
     * for each Connection within the DomainRoute.
     *
     * @param properties
     *        @rs_st_in Configuration properties for the Session.
     * 
     * @return New Session if successful. Can return @null_value if sessions
     *         are not required by this AdapterPlugin.
     *
     * @throw std::exception
     *
     * 
     * @mtsafety Safe
     * 
     */
    virtual Session * create_session(
            const PropertySet& properties)
    {
        (void) properties;
        
        return NULL;
    }

    /**
     * @brief Deletes a Session
     *
     * Session objects are deleted when the @product Sessions that contain them
     * are disabled.
     *
     * @param session
     *        @rs_st_in Session to be deleted.
     *
     * @throw std::exception
     * @mtsafety Safe
     */
    virtual void delete_session(Session *session)
    {
        (void) session;
    }

    /**
     * @brief Creates a StreamWriter.
     * 
     * This @method is called for each Route's output when the associated
     * 'creation mode' condition is met. The operation is called on the output
     * Connection as a specified through the 'connection' attribute in the
     * &lt;output&gt; tag.
     * 
     * @param session
     *        @rs_st_in Session associated with the StreamWriter. This 
     *        parameter is \null_value if Sessions are not used by the adapter.
     * @param stream_info
     *        @rs_st_in Information related to the stream where the StreamWriter
     *        sends data.                   
     * @param properties
     *        @rs_st_in Configuration properties for the StreamWriter.
     * 
     * @return New StreamWriter if successful. Cannot return @null_value
     *
     * @throw std::exception
     * @mtsafety Partially Safe.
     *           This operation is never called concurrently for the same
     *           Connection, even if multiple outputs are configured in different
     *           Sessions. It can only be called concurrently for different
     *           Connections.
     *
     */
    virtual StreamWriter * create_stream_writer(
            Session *session,
            const StreamInfo& stream_info,
            const PropertySet& properties) = 0;

    /**
     * @brief Deletes a StreamWriter.
     *
     * A StreamWriter object is deleted when:
     * - The route that contains it is disabled
     * - The 'creation mode' condition associated with the route's output
     *   becomes false
     * - \product is shutdown.
     *
     * @param stream_writer
     *        @rs_st_in StreamWriter to be deleted.
     *
     * @throw std::exception
     */
    virtual void delete_stream_writer(
            StreamWriter *stream_writer) = 0;

    /**
     * @brief Creates a StreamReader.
     *
     * This @method is called for each Route's input when the associated
     * 'creation mode' condition is met. The operation is called on the input
     * Connection as a specified through the 'connection' attribute in the
     * &lt;output&gt; tag.
     *
     * @param session
     *        @rs_st_in Session associated with the StreamReader. This
     *        parameter is \null_value if Sessions are not used by the adapter.
     * @param stream_info
     *        @rs_st_in Information related to the stream where the StreamReader
     *        read data.
     * @param properties
     *        @rs_st_in Configuration properties for the StreamReader.
     * @param listener
     *        @rs_st_in The listener for the StreamReader implementation used
     *        to notify \product when new data is available.
     * 
     * @return New StreamReader if successful. Cannot return @null_value.
     *
     * @throw std::exception
     * 
     * @mtsafety Partially Safe.
     *           This operation is never called concurrently for the same
     *           Connection, even if multiple outputs are configured in different
     *           Sessions. It can only be called concurrently for different
     *           Connections.
     *
     */
    virtual StreamReader * create_stream_reader(
            Session *session,
            const StreamInfo& stream_info,
            const PropertySet& properties,
            StreamReaderListener *listener) = 0;

    /**
     * @brief Deletes a StreamReader.
     *
     * A StreamReader object is deleted when:
     * - The route that contains it is disabled
     * - The 'creation mode' condition associated with the route's input
     *   becomes false
     * - \product is shutdown.
     *
     * @param stream_reader
     *        @rs_st_in StreamReader to be deleted.
     *
     * @throw std::exception
     */
    virtual void delete_stream_reader(
            StreamReader *stream_reader) = 0;
    
    /**
     * @brief Gets the input stream discovery StreamReader.
     *
     * Returns a DiscoveryStreamReader that is used by \product to discover
     * input streams.
     * 
     * An input stream is a stream from which a StreamReader can read data.
     * Disposed scenarios, where an input stream disappears, are also notified 
     * using this DiscoveryStreamReader.
     *
     * The StreamReaderListener associated with this DiscoveryStreamReader is 
     * provided as a parameter to the method AdapterPlugin::create_connection
     *
     * Implementations may return @null_value if they do not support stream
     * discovery.
     * 
     * @throw std::exception
     */
    virtual DiscoveryStreamReader * input_stream_discovery_reader() 
    {
        return NULL;
    }
    
   /**
     * @brief Gets the output stream discovery StreamReader.
     *
     * Returns a DiscoveryStreamReader that is used by \product to discover
     * output streams.
     *
     * An output stream is a stream from which a StreamWrite can write data.
     * Disposed scenarios, where an output stream disappears, are also notified
     * using this DiscoveryStreamReader.
     *
     * The StreamReaderListener associated with this DiscoveryStreamReader is
     * provided as a parameter to the method AdapterPlugin::create_connection.
     *
     * Implementations may return @null_value if they do not support stream
     * discovery.
     *
     * @throw std::exception
     */
    virtual DiscoveryStreamReader * output_stream_discovery_reader()
    {
        return NULL;
    }

    /**
     * @brief Virtual destructor
     */
    virtual ~Connection()
    {
    }

};

}}}

#endif // RTI_ROUTING_ADAPTER_CONNECTION_HPP_
