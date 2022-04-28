/*
 * (c) Copyright, Real-Time Innovations, 2017-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_STORAGE_STORAGESTREAMWRITER_HPP_
#define RTI_RECORDING_STORAGE_STORAGESTREAMWRITER_HPP_

#include <vector>

#include "dds/dds.hpp"

#include "rti/routing/detail/ForwarderUtils.hpp"

namespace rti { namespace recording { namespace storage {

/** \ingroup RTI_RecordingServiceStorageModule
 * class rti::recording::storage::StorageStreamWriter
 * @brief Storage stream writer
 *
 * Inherit from this class and implement the store method to store data to
 * the storage of your choice.
 */
class StorageStreamWriter {
public:

    typedef void* SamplePtr;
    typedef void* InfoPtr;

    /**
     * @brief Virtual destructor
     */
    virtual ~StorageStreamWriter() {}

    /**
     * @brief Implement this method to store data in the storage of your choice.
     *
     * @param sample_seq Vector of SamplePtr objects containing the data to
     *        store. A SamplePtr is generally a DDS_DynamicData *, unless
     *        this is a discovery stream, in which case this is the builtin
     *        discovery type.  Check the stream name to determine if this is a
     *        discovery stream.
     * @param info_seq Vector of InfoType objects. An InfoType is a
     *        DDS_SampleInfo * cast to a void *.
     */
    virtual void store(
            const std::vector<SamplePtr>& sample_seq,
            const std::vector<InfoPtr>& info_seq) = 0;
};


/** \ingroup RTI_RecordingServiceStorageModule
 * class rti::recording::storage::TStorageStreamWriter
 * @brief A templatized wrapping implementation of StorageStreamWriter,
 * providing a strongly-typed interface regarding data and info representations.
 *
 * You can implement this interface as a convenience to manipulate the data
 * and info representation without dealing with opaque pointers.
 */
template <typename Data, typename Info>
class TStorageStreamWriter : public StorageStreamWriter {
public:

    /**
    * @brief The data type
    */
   typedef Data DataRep;
   /**
    * @brief The info type
    */
   typedef Info InfoRep;

   using StorageStreamWriter::store;

   /**
    * @brief Performs the conversion between the vector of data and info
    * pointers to strongly-typed pointers.
    */
   void store(
           const std::vector<SamplePtr>& sample_seq,
           const std::vector<InfoPtr>& info_seq)
   {
       RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq_, sample_seq);
       RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(info_seq_, info_seq);

       store(sample_seq_, info_seq_);
   }

   /**
    * @brief Interface redefinition
    *
    * @see StorageStreamWriter::store
    */
   virtual void store(
           const std::vector<Data *>& sample_seq,
           const std::vector<Info *>& info_seq) = 0;

   /**
    * @brief Virtual destructor
    */
   virtual ~TStorageStreamWriter()
   {
   }

private:
    std::vector<Data *> sample_seq_;
    std::vector<Info *> info_seq_;

};

/** \ingroup RTI_RecordingServiceStorageModule
 * @brief Convenience definition of typed StorageStreamWriter that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 *
 */
typedef TStorageStreamWriter<
        dds::core::xtypes::DynamicData,
        dds::sub::SampleInfo> DynamicDataStorageStreamWriter;


} } } // namespace rti::recording::storage

#endif /* HPP_RTI_RECORDING_STORAGE_STORAGESTREAMWRITER_HPP_ */
