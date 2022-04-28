/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DETAIL_READ_PROXY_HPP_
#define RTI_ROUTING_ADAPTER_DETAIL_READ_PROXY_HPP_

#include <rti/routing/adapter/StreamReader.hpp>

namespace rti { namespace routing { namespace adapter { namespace detail {


struct TakeProxy {

    TakeProxy (StreamReader& stream_reader)
            : stream_reader_(stream_reader)
    {

    }

    void operator() (
            std::vector<rti::routing::adapter::StreamReader::SamplePtr>& sample_seq,
            std::vector<rti::routing::adapter::StreamReader::InfoPtr>& info_seq)
    {
        stream_reader_.take(sample_seq, info_seq);
    }

private:
    StreamReader& stream_reader_;
};

struct ReadProxy {

    ReadProxy (StreamReader& stream_reader)
            : stream_reader_(stream_reader)
    {

    }

    void operator() (
            std::vector<rti::routing::adapter::StreamReader::SamplePtr>& sample_seq,
            std::vector<rti::routing::adapter::StreamReader::InfoPtr>& info_seq)
    {
        stream_reader_.read(sample_seq, info_seq);
    }

private:
    StreamReader& stream_reader_;
};

struct TakeSelectorProxy {

    TakeSelectorProxy(
            StreamReader& stream_reader,
            const rti::routing::adapter::SelectorState& state)
    : stream_reader_(stream_reader), state_(state)
    {

    }

    void operator() (
            std::vector<rti::routing::adapter::StreamReader::SamplePtr>& sample_seq,
            std::vector<rti::routing::adapter::StreamReader::InfoPtr>& info_seq)
    {
        stream_reader_.take(sample_seq, info_seq, state_);
    }

private:
    StreamReader& stream_reader_;
    const rti::routing::adapter::SelectorState& state_;
};

struct ReadSelectorProxy {

    ReadSelectorProxy (
                StreamReader& stream_reader,
                const rti::routing::adapter::SelectorState& state)
            : stream_reader_(stream_reader), state_(state)
    {

    }

    void operator() (
            std::vector<rti::routing::adapter::StreamReader::SamplePtr>& sample_seq,
            std::vector<rti::routing::adapter::StreamReader::InfoPtr>& info_seq)
    {
        stream_reader_.read(sample_seq, info_seq, state_);
    }

private:
    StreamReader& stream_reader_;
    const rti::routing::adapter::SelectorState& state_;
};


} } } }


#endif /* RTI_ROUTING_ADAPTER_DETAIL_READ_PROXY_HPP_ */

