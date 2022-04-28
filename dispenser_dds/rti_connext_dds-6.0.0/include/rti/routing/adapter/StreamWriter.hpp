/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_STREAM_WRITER_HPP_
#define RTI_ROUTING_ADAPTER_STREAM_WRITER_HPP_

#include <vector>

#include <rti/routing/UpdatableEntity.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace adapter {

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::StreamWriter
 *
 * @brief Provides a way to write samples of a specific type in a data domain.
 * 
 * In the XML configuration file, A StreamWriter is associated with the tag
 * &lt;output&gt; within &lt;route&gt; or &lt;auto_route&gt;.
 *
 * @mtsafety Partially Safe
 *           All operations on a concrete StreamWriter objects are safe and
 *           always serialized on a given Session. Operations on different
 *           StreamWriter objects can be called concurrently if the
 *           StreamWriter objects belong to different Sessions.
 */
class StreamWriter : public UpdatableEntity {

public:
    
    typedef void* SamplePtr;
    typedef void* InfoPtr;

    /**
     * @brief Writes a collection of data samples to the output stream
     * associated with this StreamWriter.
     *
     * @param sample_seq
     *        @rs_st_in Vector of sample pointers.
     *        The data representation associated with the samples will be given
     *        by the value of TypeInfo::data_representation_kind that is
     *        part of the StreamInfo object passed at StreamWriter creation
     *        time.
     *        Usually the data representation is dynamic type, which corresponds
     *        to dds::core::xtypes::DynamicData.
     * @param info_seq
     *        @rs_st_in Vector of sample info pointers.
     *        The info representation is dependent of the StreamWriter
     *        implementation.
     *        Usually when data representation is dynamic type, the sample
     *        info is dds::sub::SampleInfo.
     * @return Number of samples written.
     * @throw std::exception
     */
    virtual int write(
            const std::vector<SamplePtr>& sample_seq,
            const std::vector<InfoPtr>& info_seq) = 0;

    /**
     * @brief Virtual destructor
     */
    virtual ~StreamWriter()
    {
    }
};

/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @class rti::routing::adapter::TStreamWriter
 *
 * @brief A wrapper implementation of a StreamWriter that provides a
 * strongly-typed interface through template parameters for data and info
 * representation.
 *
 * You can implement this interface as a convenience to manipulate the data
 * and info representation without dealing with opaque pointers.
 */
template <typename Data, typename Info>
class TStreamWriter : public StreamWriter {
    
public:

    /**
     * @brief The data type
     */
    typedef Data DataRep;
    typedef DataRep* DataRepPtr;
    /**
     * @brief The info type
     */
    typedef Info InfoRep;
    typedef InfoRep* InfoRepPtr;

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    int write(
            const std::vector<SamplePtr>& sample_seq,
            const std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq_, sample_seq);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(info_seq_, info_seq);
        
        return write(sample_seq_, info_seq_);
    }

    /**
     * @brief Interface redefinition
     *
     * @see StreamWriter::write
     */
    virtual int write(
            const std::vector<Data*>& sample_seq,
            const std::vector<Info*>& info_seq) = 0;

    /**
     * @brief Virtual destructor
     */
    virtual ~TStreamWriter()
    {
    }

private:
    std::vector<Data*> sample_seq_;
    std::vector<Info*> info_seq_;
};


/** @ingroup RTI_RoutingServiceAdapterModule
 *
 * @brief Convenient definition of typed StreamWriter that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 *
 */
typedef TStreamWriter<dds::core::xtypes::DynamicData, dds::sub::SampleInfo>
        DynamicDataStreamWriter;

}}}

#endif // RTI_ROUTING_ADAPTER_STREAM_WRITER_HPP_
