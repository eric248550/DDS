/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_DISCOVERY_STREAM_READER_HPP_
#define RTI_ROUTING_ADAPTER_DISCOVERY_STREAM_READER_HPP_

#include <stdlib.h>

#include <rti/routing/UpdatableEntity.hpp>
#include <rti/routing/StreamInfo.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>


namespace rti { namespace routing { namespace adapter {

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::DiscoveryStreamReader
 *
 * @brief Definition of a special StreamReader to read information about
 *        data streams.
 *
 * @mtsafety Safe
 *           All the operations on a DiscoveryStreamReader always serialized,
 *           no matter from which Connection it belongs.
 */
class DiscoveryStreamReader : public StreamReader{

    using StreamReader::take;
    using StreamReader::return_loan;
    /**
     * @brief Performs the conversion between the vector of data
     * pointers to strongly-type pointers.
     */
    void take(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>&) RTI_FINAL
    {
        take(sample_seq_);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq, sample_seq_);
    }

    /**
     * @brief Performs the conversion between the vector of data
     * pointers to strongly-type pointers.
     */
    void return_loan(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>&) RTI_FINAL
    {
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq_, sample_seq);
        return_loan(sample_seq_);
        sample_seq_.clear();
    }

    void read(
            std::vector<SamplePtr>&,
            std::vector<InfoPtr>&) RTI_FINAL
    {
    }

    void take(
            std::vector<SamplePtr>&,
            std::vector<InfoPtr>&,
            const SelectorState&) RTI_FINAL
    {
    }

    void read(
            std::vector<SamplePtr>&,
            std::vector<InfoPtr>&,
            const SelectorState&) RTI_FINAL
    {
    }

     virtual void* create_content_query(
            void *,
            const dds::topic::Filter&) RTI_FINAL
    {
        return NULL;
    }


    virtual void delete_content_query(void*) RTI_FINAL
    {

    }

    
public:

    /**
     * @brief Takes a collection of all available StreamInfo samples.
     *
     * When \product is done using the samples, it will 'return the loan' to the
     * DiscoveryStreamReader by calling DiscoveryStreamReader::return_loan.
     * It is guaranteed \product takes one outstanding loan at time.
     *
     * The samples provided with this operation are considered 'removed'
     * from the DiscoveryStreamReader's cache, and they shall no longer be
     * returned by subsequent DiscoveryStreamReader::take.     
     *
     * @param sample_seq
     *        @rs_st_inout Vector that will hold the StreamInfo samples. \product
     *        provides this vector to the StreamReader to fill. For each call,
     *        the size of the vector is zero.
     * @throw std::exception
     */
    virtual void take(
            std::vector<rti::routing::StreamInfo*>& sample_seq) = 0;

    /** @brief Returns a loan on the read or taken StreamInfo samples.
     *
     * \product calls this method to indicate that it is done accessing
     *  the collection of StreamInfo samples obtained by an earlier
     *  invocation of DiscoveryStreamReader::take.
     *
     * @param sample_seq
     *        @rs_st_in Vector of loaned data samples.
     *
     * @throw std::exception
     */
    virtual void return_loan(
            std::vector<rti::routing::StreamInfo*>& sample_seq) = 0;

    /*
     * @brief Virtual destructor
     */
    virtual ~DiscoveryStreamReader()
    {
    }   

private:
    std::vector<StreamInfo*> sample_seq_;
};

}}}

#endif // RTI_ROUTING_ADAPTER_DISCOVERY_STREAM_READER_HPP_

