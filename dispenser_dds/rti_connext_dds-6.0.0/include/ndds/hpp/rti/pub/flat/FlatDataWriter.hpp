/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

============================================================================= */

#ifndef RTI_DDS_TOPIC_FLATDATAWRITER_HPP_
#define RTI_DDS_TOPIC_FLATDATAWRITER_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/topic/flat/FlatDataTraits.hpp>
#include <dds/pub/DataWriter.hpp>

namespace rti { namespace pub {

template <typename T>
struct NativeGetLoanPolicy<
        T,
        typename rtiboost::enable_if_c<rti::flat::topic::is_flat_data_type_only<T>::value>::type> {

    static T* get_loan(DDS_DataWriter *self)
    {
        T *sample;

        RTIXCdrInterpreterPrograms *programs
                = rti::xcdr::type_programs<T>::get();

        detail::get_flat_loan_untyped(
                self,
                reinterpret_cast<char **>(&sample),
                programs,
                rti::flat::is_fixed_size_type<T>::value ? true : false);

        return sample;
    }
};

template <typename T>
struct NativeDiscardLoanPolicy<
        T,
        typename rtiboost::enable_if_c<rti::flat::topic::is_flat_data_type_only<T>::value>::type> {

    static void discard_loan(DDS_DataWriter *self, T *sample)
    {
        DDS_ReturnCode_t retcode = DDS_DataWriter_discard_loan_untypedI(
                self,
                sample);
        rti::core::check_return_code(retcode, "discard loan");
    }
};

template <typename T>
struct NativeCreateDataPolicy<
        T,
        typename rtiboost::enable_if_c<rti::flat::topic::is_flat_data_type_only<T>::value>::type> {

    static T* create_data(DDS_DataWriter *)
    {
        return T::create_data();
    }
};

template <typename T>
struct NativeDeleteDataPolicy<
        T,
        typename rtiboost::enable_if_c<rti::flat::topic::is_flat_data_type_only<T>::value>::type> {

    static bool delete_data(DDS_DataWriter *, T *sample)
    {
        T::delete_data(sample);
        return true;
    }
};

} } // namespace rti::pub

namespace rti { namespace flat {

/**
 * @ingroup RTIFlatBuildersModule
 * 
 * @brief Begins building a new sample
 * 
 * @tparam TopicType A FlatData mutable type that corresponds to 
 * the type of the DataWriter argument.
 * 
 * @param writer The writer that will be used to write this sample.
 * @return The Builder to build the sample. For example if TopicType is 
 * \ref MyFlatMutable, this function returns a MyFlatMutableBuilder. 
 * 
 * Once you have completed the sample, call 
 * \ref MyFlatMutableBuilder::finish_sample() "finish_sample()" to 
 * obtain a \ref MyFlatMutable sample that can be written with \p writer.
 * 
 * If the building of this sample needs to be aborted before calling 
 * finish_sample(), use rti::flat::discard_builder(). If, after obtaining a
 * sample with finish_sample(), this sample is not written, then discard it with
 * \idref_FooDataWriter_discard_loan().
 * 
 * @see \idref_FooDataWriter_get_loan, the function that build_data() uses to obtain 
 * the memory required to build the sample.
 * @see \ref PublishingFlatData
 */
template <typename TopicType>
typename rti::flat::flat_type_traits<TopicType>::builder build_data(
        dds::pub::DataWriter<TopicType>& writer)
{
    unsigned int max_size =
            PRESTypePluginDefaultEndpointData_getMaxSizeSerializedSample(
                    DDS_DataWriter_get_endpoint_dataI(writer->native_writer()));

    return typename rti::flat::flat_type_traits<TopicType>::builder(
            reinterpret_cast<unsigned char*>(writer->get_loan()),
            max_size,
            DDS_DataWriter_is_initialize_writer_loaned_sample(writer->native_writer()));
}

/**
 * @ingroup RTIFlatBuildersModule
 * 
 * @brief Discards a sample builder
 * 
 * @tparam TopicType An IDL-defined FlatData type that corresponds to the
 * type of the DataWriter argument.
 * 
 * This function invalidates and discards a builder before it is finished() and
 * before the sample it would have created was written.
 * 
 * @param writer The writer that was used to create the builder
 * @param builder The builder, created with \p rti::flat::build_data(writer);
 */
template <typename TopicType>
void discard_builder(
        dds::pub::DataWriter<TopicType>& writer,
        typename rti::flat::flat_type_traits<TopicType>::builder& builder)
{
    unsigned char *buffer = builder.discard_sample_impl();
    if (buffer != NULL) {
        writer->discard_loan(*reinterpret_cast<TopicType *>(buffer));
    }
}

} }

#endif // RTI_DDS_TOPIC_FLATDATAWRITER_HPP_
