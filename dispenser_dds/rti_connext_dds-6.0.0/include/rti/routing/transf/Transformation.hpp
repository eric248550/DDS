/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_TRANSF_TRANSFORMATION_HPP_
#define RTI_ROUTING_TRANSF_TRANSFORMATION_HPP_

#include <vector>

#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/routing/UpdatableEntity.hpp>
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing { namespace transf {

/** @ingroup RTI_RoutingServiceTransformationModule
 *
 * @class rti::routing::transf::Transformation
 * @brief Provides a way to transform input samples into output samples of a
 *        different format and/or content.
 *
 * @mtsafety Partially Safe
 *           All operations on a concrete Transformation object are safe and
 *           always serialized on a given Output. Operations on different
 *           Transformations objects may be called concurrently if they
 *           belong to different Outputs from different Routes.
 */
class Transformation : public UpdatableEntity{
public:         

    typedef void* SamplePtr;
    typedef void* InfoPtr;
    
    /**
     * @brief Transforms a vector of input samples into a vector of output 
     * samples.
     *
     * When @product is done using the output samples, it will 'return the loan'
     * to the transformation by calling Transformation::return_loan. It is
     * guaranteed @product takes one outstanding loan at time.
     *
     * The number of output samples can be different than the number of input
     * samples.
     * 
     * The format associated with the input and output data samples and info
     * samples depends on the format provided and consumed by the input's
     * rti::routing::adapter::StreamReader and the output's
     * rti::routing::adapter::StreamWriter.
     *
     * For the built-in DDS adapter, the format of the samples is 
     * dds::core::xtypes::DynamicData and the format of the sample info is
     * dds::sub::SampleInfo.
     *
     * @param output_sample_seq
     *        @rs_st_inout Vector that will hold the output data samples. @product
     *        provides this vector to the Transformation to fill. For each call,
     *        the size of the vector is zero.
     * @param output_info_seq
     *        @rs_st_inout Vector that will hold the input info samples. @product
     *        provides this vector to the Transformation to fill. For each call,
     *        the size of the vector is zero.
     * @param input_sample_seq
     *        @rs_st_in Vector of input data samples. This vector contains the list
     *        of samples that need to be transformed before calling
     *        rti::routing::adapter::StreamWriter::write.    
     * @param input_info_seq
     *        @rs_st_in Vector of input info sample. This vector contains the list
     *        of samples that need to be transformed before calling
     *        rti::routing::adapter::StreamWriter::write.
     *
     * @throw std::exception
     */
    virtual void transform(
            std::vector<SamplePtr>& output_sample_seq,
            std::vector<InfoPtr>& output_info_seq,
            const std::vector<SamplePtr>& input_sample_seq,
            const std::vector<InfoPtr>& input_info_seq) = 0;

     /**
     * @brief Returns a loan on the transformed data samples and info samples.
     *
     * @product calls this method to indicate that it is done accessing
     * the collection of data samples and info samples obtained by an earlier
     * invocation of Transformation::transform.
     *
     * @param   sample_seq
     *          @rs_st_in Vector of loaned data samples.
     * @param   info_seq
     *          @rs_st_in Vector of loaned info samples.
     *
     * @throw std::exception
     *
     */
    virtual void return_loan(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) = 0;

    
    virtual ~Transformation() {}
};


/** @ingroup RTI_RoutingServiceTransformationModule
 *
 * @class rti::routing::transf::TypedTransformation
 *
 * @brief A wrapper implementation of a Transformation that provides a
 * strongly-typed interface through template parameters for data and info
 * representation.
 *
 * You can implement this interface as a convenience to manipulate the data
 * and info representation without dealing with opaque pointers.
 */
template <typename Data, typename Info>
class TypedTransformation : public Transformation {

public:

     /**
     * @brief The data type
     */
    typedef Data DataRep;
    /**
     * @brief The info type
     */
    typedef Info InfoRep;

    using Transformation::transform;
    using Transformation::return_loan;

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    void transform(
            std::vector<SamplePtr>& output_sample_seq,
            std::vector<InfoPtr>& output_info_seq,
            const std::vector<SamplePtr>& input_sample_seq,
            const std::vector<InfoPtr>& input_info_seq) RTI_FINAL
    {
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(in_sample_seq_, input_sample_seq);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(in_info_seq_, input_info_seq);
        transform(
                out_sample_seq_,
                out_info_seq_,
                in_sample_seq_,
                in_info_seq_);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(output_sample_seq, out_sample_seq_);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(output_info_seq, out_info_seq_);
    }

    /**
     * @brief Performs the conversion between the vector of data and info
     * pointers to strongly-type pointers.
     */
    void return_loan(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) RTI_FINAL
    {
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(out_sample_seq_, sample_seq);
        RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(out_info_seq_, info_seq);
        return_loan(out_sample_seq_, out_info_seq_);
        out_sample_seq_.clear();
        out_info_seq_.clear();
    }

    /**
     * @brief Interface redefinition
     *
     * @see Transformation::transform
     */
    virtual void transform(
            std::vector<Data*>& output_sample_seq,
            std::vector<Info*>& output_info_seq,
            const std::vector<Data*>& input_sample_seq,
            const std::vector<Info*>& input_info_seq) = 0;

     /**
     * @brief Interface redefinition
     *
     * @see Transformation::return_loan
     */
    virtual void return_loan(
            std::vector<Data*>& sample_seq,
            std::vector<Info*>& info_seq) = 0;

    /**
     * @brief Virtual destructor
     */
    virtual ~TypedTransformation()
    {

    }
private:
    std::vector<Data*> in_sample_seq_;
    std::vector<Info*> in_info_seq_;
    std::vector<Data*> out_sample_seq_;
    std::vector<Info*> out_info_seq_;

};

/** @ingroup RTI_RoutingServiceTransformationModule
 *
 * @brief Convenient definition of TypedTransformation that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 *
 */
typedef TypedTransformation<dds::core::xtypes::DynamicData, dds::sub::SampleInfo>
        DynamicDataTransformation;


}}}


#endif // RTI_ROUTING_TRANSF_TRANSFORMATION_HPP_
