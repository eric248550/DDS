/*
 * (c) Copyright, Real-Time Innovations, 2017-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 *
 */

#ifndef HPP_RTI_RECORDING_STORAGE_STREAMREADER_HPP_
#define HPP_RTI_RECORDING_STORAGE_STREAMREADER_HPP_

#include <vector>

#include "dds/dds.hpp"

#include "rti/routing/detail/ForwarderUtils.hpp"

#include "rti/recording/storage/SelectorState.hpp"


namespace rti { namespace recording { namespace storage {

/** \ingroup RTI_RecordingServiceStorageModule
 * class rti::recording::storage::StorageStreamReader
 * @brief Storage stream reader
 *
 * This class retrieves user data from storage.
 */
class StorageStreamReader {
public:
    
    typedef void* SamplePtr;
    typedef void* InfoPtr;

    /**
     * @brief Virtual destructor
     */
    virtual ~StorageStreamReader() 
    {
    }

    /**
     * @brief Method called by \replay_product and \converter_product
     *        to retrieve samples from storage for a particular stream
     *        (DDS topic). The data samples retrieved have to be provided in
     *        increasing time-stamp order (reception time-stamp).
     *
     * @param sample_seq A vector of data samples that \replay_product or 
     *        \converter_product will replay or convert to a new format.
     *         A SampleType is a DDS_DynamicData * cast as a void * 
     * @param info_seq A vector of sample information about the samples,
     *        such as recorded timestamps of the sample data.  An InfoType is
     *        a DDS_SampleInfo * cast as a void *.
     * @param selector Provides the statefulness and constraints of the data
     *        queried by \replay_product or \converter_product. When the
     *        selector's sample state is set to 'any', it means its asking for
     *        stateless information (it doesn't care whether the data has been
     *        read before or not). When the selector's sample state is set to
     *        'not read' then it's a stateful read, and only samples that
     *        weren't given to the application before have to be provided.
     *        Note: for the moment, \replay_product or
     *        \converter_product won't ask for data with sample state equal to
     *        'read', so this state can be ignored.
     */
    virtual void read(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq,
            const SelectorState& selector) = 0;
    /** 
     * @brief Method for releasing resources related to the queried data 
     *        samples.
     *
     * This is called back when the \replay_product or \converter_product has 
     * finished with the data samples queried in the take() function, and 
     * wants to notify the plugin that it can free any related resources.
     *
     * @param sample_seq A vector of sample objects that the plugin can
     *        now free.
     * @param info_seq A vector of sample_info objects that the plugin can
     *        now free.
     *
     */
    virtual void return_loan(
            std::vector<SamplePtr>& sample_seq,
            std::vector<InfoPtr>& info_seq) = 0;

    /**
     * @brief Method for querying whether there are no more samples for this 
     *        stream.
     *
     * @return true if there is no more data available for this stream,
     *         false otherwise.
     *
     */
    virtual bool finished() = 0;

    /**
     * @brief Method used by \replay_product when looping, to start over. After
     * this method is called, the stream reader should be ready to start reading
     * data from the beginning of the stream, again.
     */
    virtual void reset() = 0;
};

/** \ingroup RTI_RecordingServiceStorageModule
 * class rti::recording::storage::TStorageStreamReader
 * @brief A templatized wrapping implementation of StorageStreamReader,
 * providing a strongly-typed interface regarding data and info representations.
 *
 * You can implement this interface as a convenience to manipulate the data
 * and info representation without dealing with opaque pointers.
 */
template <typename Data, typename Info>
class TStorageStreamReader : public StorageStreamReader {
public:

    /**
    * @brief The data type
    */
   typedef Data DataRep;
   /**
    * @brief The info type
    */
   typedef Info InfoRep;

   using StorageStreamReader::read;
   using StorageStreamReader::return_loan;

   /**
    * @brief Performs the conversion between the vector of data and info
    * pointers to strongly-typed pointers.
    */
   void read(
           std::vector<SamplePtr>& sample_seq,
           std::vector<InfoPtr>& info_seq,
           const SelectorState& selector) RTI_FINAL
   {
       read(sample_seq_, info_seq_, selector);
       RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq, sample_seq_);
       RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(info_seq, info_seq_);
   }

   /**
    * @brief Performs the conversion between the vector of data and info
    * pointers to strongly-typed pointers.
    */
   void return_loan(
           std::vector<SamplePtr>& sample_seq,
           std::vector<InfoPtr>& info_seq) RTI_FINAL
   {
       RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(sample_seq_, sample_seq);
       RTI_ROUTING_SAMPLE_VECTOR_COPY_PTRS(info_seq_, info_seq);
       return_loan(sample_seq_, info_seq_);
       sample_seq_.clear();
       info_seq_.clear();
   }

   virtual void read(
           std::vector<Data *>& sample_seq,
           std::vector<Info *>& info_seq,
           const SelectorState& selector) = 0;

   virtual void return_loan(
           std::vector<Data *>& sample_seq,
           std::vector<Info *>& info_seq) = 0;

   /*
    * @brief Virtual destructor
    */
   virtual ~TStorageStreamReader() {}

private:

   std::vector<Data*> sample_seq_;
   std::vector<Info*> info_seq_;
};

/** \ingroup RTI_RecordingServiceStorageModule
 * @brief Convenience definition of typed StorageStreamReader that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 */
typedef TStorageStreamReader<
        dds::core::xtypes::DynamicData,
        dds::sub::SampleInfo> DynamicDataStorageStreamReader;

} } } // namespace rti::recording::storage

#endif /* HPP_RTI_RECORDING_STORAGE_STREAMREADER_HPP_ */
