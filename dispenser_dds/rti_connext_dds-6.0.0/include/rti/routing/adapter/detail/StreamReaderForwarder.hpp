/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_STREAM_READER_FORWARDER_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_STREAM_READER_FORWARDER_HPP_

#include <list>
#include <rti/core/Exception.hpp>

#include <rti/routing/adapter/StreamReader.hpp>
#include <rti/routing/StreamInfo.hpp>
#include <rti/routing/detail/UpdatableEntityForwarder.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>
#include <rti/routing/adapter/detail/DiscoveryStreamReaderForwarder.hpp>


namespace rti { namespace routing { namespace adapter { namespace detail {

template <bool ReadOrTake, bool HasSelector> struct read_or_take;


template<>
struct read_or_take<false, false> {

    static void read(
            rti::routing::adapter::StreamReader& stream_reader,
            std::vector<StreamReader::SamplePtr>& sample_seq,
            std::vector<StreamReader::InfoPtr>& info_seq,
            const struct RTI_RoutingServiceSelectorState *)
    {
        stream_reader.take(sample_seq, info_seq);
    }
};

template<>
struct read_or_take<true, false> {

    static void read(
            rti::routing::adapter::StreamReader& stream_reader,
            std::vector<StreamReader::SamplePtr>& sample_seq,
            std::vector<StreamReader::InfoPtr>& info_seq,
            const struct RTI_RoutingServiceSelectorState *)
    {
        stream_reader.read(sample_seq, info_seq);
    }
};

template<>
struct read_or_take<false, true> {

    static void read(
            rti::routing::adapter::StreamReader& stream_reader,
            std::vector<StreamReader::SamplePtr>& sample_seq,
            std::vector<StreamReader::InfoPtr>& info_seq,
            const struct RTI_RoutingServiceSelectorState *native_selector)
    {
        stream_reader.take(
                sample_seq,
                info_seq,
                SelectorState(*native_selector));
    }
};


template<>
struct read_or_take<true, true> {

    static void read(
            rti::routing::adapter::StreamReader& stream_reader,
            std::vector<StreamReader::SamplePtr>& sample_seq,
            std::vector<StreamReader::InfoPtr>& info_seq,
            const struct RTI_RoutingServiceSelectorState *native_selector)
    {
        stream_reader.read(
                sample_seq,
                info_seq,
                SelectorState(*native_selector));
    }
};


struct SamplesHolder {
public:

    SamplesHolder()
    {
    }

    std::vector<StreamReader::SamplePtr> sample_seq_;
    std::vector<StreamReader::InfoPtr> info_seq_;
};

class StreamReaderForwarder {
public:
    static RTI_RoutingServiceStreamReaderExt* create_native(
            Connection *connection,
            Session *session,
            const struct RTI_RoutingServiceStreamInfo *native_stream_info,
            const struct RTI_RoutingServiceProperties *native_properties,
            const struct RTI_RoutingServiceStreamReaderListenerExt *native_listener,
            RTI_RoutingServiceEnvironment *environment)
    {

        try {           
            StreamInfo stream_info(*native_stream_info);

            std::map<std::string, std::string> properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);

            StreamReaderForwarder *forwarder = new StreamReaderForwarder(
                    native_listener);
            ScopedForwarder<Connection, StreamReaderForwarder> scoped(
                    connection,
                    forwarder,
                    environment);
            forwarder->stream_reader_ = connection->create_stream_reader(
                    session,
                    stream_info,
                    properties,
                    &forwarder->listener_);
            RTI_ROUTING_THROW_ON_NULL(forwarder->stream_reader_);
            
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
            RTI_RoutingServiceStreamReaderExt *native_stream_reader,
            RTI_RoutingServiceEnvironment *environment)
    {
        StreamReaderForwarder *stream_reader_forwarder =
                from_native(native_stream_reader);
        try {
            if (stream_reader_forwarder->stream_reader_ != NULL) {
                connection->delete_stream_reader(
                        stream_reader_forwarder->stream_reader_);
                stream_reader_forwarder->stream_reader_ = NULL;
            }
        } catch(const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
        }

        delete stream_reader_forwarder;
    }


    RTI_RoutingServiceStreamReaderExt* native()
    {
        return &this->native_;
    }


private:

    StreamReaderForwarder(
            const RTI_RoutingServiceStreamReaderListenerExt *native_listener) :
            stream_reader_(NULL),
            listener_(native_listener)
    {
        RTIOsapiMemory_zero(&native_, sizeof(native_));
        native_.stream_reader_data =
                static_cast<void *>(this);
        native_.take =
                StreamReaderForwarder::take;
        native_.read =
                StreamReaderForwarder::read;
        native_.take_w_selector =
                StreamReaderForwarder::take_with_selector;
        native_.read_w_selector =
                StreamReaderForwarder::read_with_selector;
        native_.return_loan =
                StreamReaderForwarder::return_loan;
        native_.create_content_query =
                StreamReaderForwarder::create_content_query;
        native_.delete_content_query =
                StreamReaderForwarder::delete_content_query;
        native_.update =
                StreamReaderForwarder::update;
    }

    ~StreamReaderForwarder()
    {
        // delete holders
        for (std::list<SamplesHolder*>::iterator it = holder_pool_.begin();
             it != holder_pool_.end();
             ++it) {
            delete (*it);
        }
    }


    static void take(
        void *native_stream_reader_data,
        RTI_RoutingServiceSample **sample_array,
        RTI_RoutingServiceSampleInfo **sample_info_array,
        int *array_length,
        RTI_RoutingServiceEnvironment *environment)
    {
        proxy_read<false, false>(
                native_stream_reader_data,
                sample_array,
                sample_info_array,
                array_length,
                NULL,
                environment);
    }

    static void read(
        void *native_stream_reader_data,
        RTI_RoutingServiceSample **sample_array,
        RTI_RoutingServiceSampleInfo **sample_info_array,
        int *array_length,
        RTI_RoutingServiceEnvironment *environment)
    {
        proxy_read<true, false>(
                native_stream_reader_data,
                sample_array,
                sample_info_array,
                array_length,
                NULL,
                environment);
    }

    static void take_with_selector(
        void *native_stream_reader_data,
        RTI_RoutingServiceSample **sample_array,
        RTI_RoutingServiceSampleInfo **sample_info_array,
        int *array_length,
        const struct RTI_RoutingServiceSelectorState *native_selector,
        RTI_RoutingServiceEnvironment *environment)
    {
        proxy_read<false, true>(
                native_stream_reader_data,
                sample_array,
                sample_info_array,
                array_length,
                native_selector,
                environment);
    }

    static void read_with_selector(
        void *native_stream_reader_data,
        RTI_RoutingServiceSample **sample_array,
        RTI_RoutingServiceSampleInfo **sample_info_array,
        int *array_length,
        const struct RTI_RoutingServiceSelectorState *native_selector,
        RTI_RoutingServiceEnvironment *environment)
    {
        proxy_read<true, true>(
                native_stream_reader_data,
                sample_array,
                sample_info_array,
                array_length,
                native_selector,
                environment);
    }

    static void return_loan(
        void *native_stream_reader_data,
        RTI_RoutingServiceSample *native_samples,
        RTI_RoutingServiceSampleInfo *,
        int count,
        RTI_RoutingServiceEnvironment *environment)
    {
        StreamReaderForwarder *forwarder =
                static_cast<StreamReaderForwarder*>(native_stream_reader_data);
        RTIBOOST_ASSERT(forwarder != NULL);

        SamplesHolder *holder = static_cast<SamplesHolder*>(
                native_samples[count]);
        RTIBOOST_ASSERT(holder != NULL);


        try {
            forwarder->stream_reader_->return_loan(
                    holder->sample_seq_,
                    holder->info_seq_);
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

        forwarder->return_holder(holder);
    }

    static void update(
            void *native_stream_reader_data,
            const struct RTI_RoutingServiceProperties * native_properties,
            RTI_RoutingServiceEnvironment * environment)
    {

        StreamReaderForwarder *stream_reader_forwarder =
                static_cast<StreamReaderForwarder*>(native_stream_reader_data);

        rti::routing::detail::UpdatableEntityForwarder::update(
                stream_reader_forwarder->stream_reader_,
                native_properties,
                environment);
    }

    static void* create_content_query(
        void *native_stream_reader_data,
        RTI_RoutingServiceSelectorStateQueryData old_query_data,
        const struct RTI_RoutingServiceSelectorContent *content,
        RTI_RoutingServiceEnvironment *environment)
    {
        StreamReaderForwarder *forwarder =
                static_cast<StreamReaderForwarder*>(native_stream_reader_data);

        void *query_data = NULL;
        try {
            dds::topic::Filter filter(
                    content->expression == NULL ? "" : content->expression,
                    rti::core::native_conversions::from_native<std::string>(
                            content->expression_parameters));
            query_data = forwarder->stream_reader_->create_content_query(
                    old_query_data,
                    filter);
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

        return query_data;
    }

    static void delete_content_query(
        void *native_stream_reader_data,
        RTI_RoutingServiceSelectorStateQueryData query_data,
        RTI_RoutingServiceEnvironment *environment)
    {
        StreamReaderForwarder *forwarder =
                static_cast<StreamReaderForwarder*>(native_stream_reader_data);
        try {
            forwarder->stream_reader_->delete_content_query(query_data);
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

    static StreamReaderForwarder* from_native(
            RTI_RoutingServiceStreamReaderExt *native)
    {
        return static_cast<StreamReaderForwarder*>(native->stream_reader_data);
    }

    template <bool ReadOrTake, bool HasSelector>
    static void proxy_read(
        void *native_stream_reader_data,
        RTI_RoutingServiceSample **sample_array,
        RTI_RoutingServiceSampleInfo **sample_info_array,
        int *array_length,
        const struct RTI_RoutingServiceSelectorState *native_selector,
        RTI_RoutingServiceEnvironment *environment)
    {
        StreamReaderForwarder *forwarder =
                static_cast<StreamReaderForwarder*>(native_stream_reader_data);
        RTIBOOST_ASSERT(forwarder != NULL);

        SamplesHolder *holder = forwarder->get_holder();

        *array_length = 0;
        try {
            read_or_take<ReadOrTake, HasSelector>::read(
                    *forwarder->stream_reader_,
                    holder->sample_seq_,
                    holder->info_seq_,
                    native_selector);
            if (!holder->info_seq_.empty()
                    && (holder->info_seq_.size() != holder->sample_seq_.size())) {
                throw dds::core::PreconditionNotMetError(
                        "sample and info sequences length mismatch");
            }
            holder->sample_seq_.reserve(holder->sample_seq_.size() + 1);
            holder->sample_seq_[holder->sample_seq_.size()] = holder;
        } catch (const std::exception& ex) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "%s",
                    ex.what());
            forwarder->return_holder(holder);
            return;
        } catch (...) {
            RTI_RoutingServiceEnvironment_set_error(
                    environment,
                    "unexpected exception");
            forwarder->return_holder(holder);
            return;
        }

        // direct mapping
        *array_length = holder->sample_seq_.size();
        *sample_array = &holder->sample_seq_[0];
        if (holder->info_seq_.empty()) {
            *sample_info_array = NULL;
        } else {
            *sample_info_array = &holder->info_seq_[0];
        }
    }

    SamplesHolder* get_holder()
    {
        if (holder_pool_.size() == 0) {
            return new SamplesHolder();
        }

        SamplesHolder *holder = holder_pool_.front();
        holder_pool_.pop_front();

        return holder;
    }

    void return_holder(SamplesHolder *holder)
    {
        holder->sample_seq_.clear();
        holder->info_seq_.clear();
        holder_pool_.push_front(holder);
    }

private:

    RTI_RoutingServiceStreamReaderExt native_;
    StreamReader *stream_reader_;
    StreamReaderListener listener_;
    std::list<SamplesHolder*> holder_pool_;
};

}}}}

#endif // RTI_ROUTING_ADAPTER_DETAIL_STREAM_READER_FORWARDER_HPP_
