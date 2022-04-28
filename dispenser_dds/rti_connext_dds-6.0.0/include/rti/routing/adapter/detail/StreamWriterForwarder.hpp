/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_STREAM_WRITER_FORWARDER_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_STREAM_WRITER_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <rti/routing/adapter/StreamWriter.hpp>
#include <rti/routing/detail/UpdatableEntityForwarder.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace adapter { namespace detail {


class StreamWriterForwarder {
public:
    
    static RTI_RoutingServiceStreamWriterExt* create_native(
            Connection *connection,
            Session *session,
            const struct RTI_RoutingServiceStreamInfo *native_stream_info,
            const struct RTI_RoutingServiceProperties *native_properties,
            RTI_RoutingServiceEnvironment *environment)
    {
        try {
            StreamInfo stream_info(*native_stream_info);

            std::map<std::string, std::string> properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);

            StreamWriterForwarder *forwarder = new StreamWriterForwarder(
                    NULL);
            ScopedForwarder<Connection, StreamWriterForwarder> scoped(
                    connection,
                    forwarder,
                    environment);
            forwarder->stream_writer_ = connection->create_stream_writer(
                    session,
                    stream_info,
                    properties);     
            RTI_ROUTING_THROW_ON_NULL(forwarder->stream_writer_);
            
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
            RTI_RoutingServiceStreamWriterExt *native_stream_writer,
            RTI_RoutingServiceEnvironment *environment)
    {       
        StreamWriterForwarder *stream_writer_forwarder = 
                static_cast<StreamWriterForwarder*>(
                    native_stream_writer->stream_writer_data);
        try {            
            if (stream_writer_forwarder->stream_writer_ != NULL) {
                connection->delete_stream_writer(
                        stream_writer_forwarder->stream_writer_);
                stream_writer_forwarder->stream_writer_ = NULL;
            }
        } catch(const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment, 
                    "%s",
                    ex.what());
        } catch (...) {
        } 
               
        delete stream_writer_forwarder;
    }
    
    
    static int write(
        void *native_stream_writer_data,
        const RTI_RoutingServiceSample *sample_array,
        const RTI_RoutingServiceSampleInfo *sample_info_array,
        int array_length,
        RTI_RoutingServiceEnvironment *environment)
    {

        StreamWriterForwarder *forwarder = 
                static_cast<StreamWriterForwarder*>(native_stream_writer_data);

        try {
            RTI_ROUTING_SAMPLE_VECTOR_COPY_FROM_NATIVE(
                    forwarder->sample_seq_,
                    sample_array,
                    array_length);
            if (sample_info_array != NULL) {
                RTI_ROUTING_SAMPLE_VECTOR_COPY_FROM_NATIVE(
                        forwarder->info_seq_,
                        sample_info_array,
                        array_length);
            } else {
                forwarder->info_seq_.clear();
            }
            return forwarder->stream_writer_->write(
                    forwarder->sample_seq_,
                    forwarder->info_seq_);
        } catch (const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
        } catch (...) {
             RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
        }  

        return 0;
    }
    
    static void update(
            void *native_stream_writer_data,
            const struct RTI_RoutingServiceProperties * native_properties,
            RTI_RoutingServiceEnvironment * environment)
    {

        StreamWriterForwarder *stream_writer_forwarder =
                static_cast<StreamWriterForwarder*> (native_stream_writer_data);

        rti::routing::detail::UpdatableEntityForwarder::update(
                stream_writer_forwarder->stream_writer_,
                native_properties,
                environment);
    }

     RTI_RoutingServiceStreamWriterExt* native()
    {
        return &this->native_;
    }
    
private: 
    
    StreamWriterForwarder(
            StreamWriter *stream_writer) :
            stream_writer_(stream_writer)
    {
        RTIOsapiMemory_zero(&native_, sizeof(native_));
        native_.stream_writer_data =
                static_cast<void*>(this);
        native_.write =
                StreamWriterForwarder::write;
        native_.update =
                StreamWriterForwarder::update;

    }
    
    ~StreamWriterForwarder()
    {
    }
    
private:
    RTI_RoutingServiceStreamWriterExt native_;
    StreamWriter *stream_writer_;
    std::vector<StreamWriter::SamplePtr> sample_seq_;
    std::vector<StreamWriter::InfoPtr> info_seq_;
    
};

}}}}

#endif // RTI_ROUTING_ADAPTER_DETAIL_STREAM_WRITER_FORWARDER_HPP_
