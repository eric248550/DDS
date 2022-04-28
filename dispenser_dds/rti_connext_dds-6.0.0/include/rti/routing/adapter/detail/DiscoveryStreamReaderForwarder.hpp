/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_DISCOVERY_STREAM_READER_FORWARDER_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_DISCOVERY_STREAM_READER_FORWARDER_HPP_

#include <rti/core/Exception.hpp>

#include <routingservice/routingservice_adapter_new.h>

#include <rti/routing/adapter/AdapterPlugin.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace adapter { namespace detail {


class DiscoveryStreamReaderForwarder {
public:   
    static void take(
            void *native_stream_reader_data,
            RTI_RoutingServiceSample **sample_array,
            RTI_RoutingServiceSampleInfo **sample_info_array,
            int *array_length,
            RTI_RoutingServiceEnvironment *environment)
    {
        DiscoveryStreamReaderForwarder *forwarder =
                static_cast<DiscoveryStreamReaderForwarder*>(native_stream_reader_data);

        *sample_info_array = NULL;
        *array_length = 0;
        try {
            forwarder->stream_reader_->take(forwarder->sample_seq_);
            *array_length = forwarder->sample_seq_.size();
            if (*array_length > 0) {
                *sample_array = reinterpret_cast<RTI_RoutingServiceSample*> (
                        &forwarder->sample_seq_[0]);
            }
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

    }
    
    static void return_loan(
            void *native_stream_reader_data,
            RTI_RoutingServiceSample *,
            RTI_RoutingServiceSampleInfo *,
            int,
            RTI_RoutingServiceEnvironment *environment)
    {
        DiscoveryStreamReaderForwarder *forwarder =
                static_cast<DiscoveryStreamReaderForwarder*> (native_stream_reader_data);

        try {
            forwarder->stream_reader_->return_loan(forwarder->sample_seq_);
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
        forwarder->sample_seq_.clear();
    }
    
        
    DiscoveryStreamReaderForwarder(
            DiscoveryStreamReader *stream_reader) :
            stream_reader_(stream_reader)
    {
        RTIOsapiMemory_zero(&native_, sizeof(native_));
        native_.stream_reader_data =
                static_cast<void *>(this);
        native_.take =
                DiscoveryStreamReaderForwarder::take;
        native_.return_loan =
                DiscoveryStreamReaderForwarder::return_loan;
    }


    ~DiscoveryStreamReaderForwarder()
    {
    }
    

    static DiscoveryStreamReaderForwarder* from_native(
            RTI_RoutingServiceStreamReaderExt *native)
    {
        return static_cast<DiscoveryStreamReaderForwarder*>(native->stream_reader_data);
    }

    RTI_RoutingServiceStreamReaderExt * native()
    {
        return &native_;
    }

private:
    RTI_RoutingServiceStreamReaderExt native_;
    DiscoveryStreamReader *stream_reader_;
    std::vector<StreamInfo*> sample_seq_;
};

}}}}

#endif // RTI_ROUTING_ADAPTER_DETAIL_DISCOVERY_STREAM_READER_FORWARDER_HPP_
