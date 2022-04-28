/******************************************************************************
 * (c) Copyright, Real-Time Innovations, 2016-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 *****************************************************************************/

#ifndef HPP_RTI_RECORDING_STORAGE_DISCOVERYSTREAMREADER_HPP_
#define HPP_RTI_RECORDING_STORAGE_DISCOVERYSTREAMREADER_HPP_

#include "dds/dds.hpp"
#include "rti/routing/StreamInfo.hpp"

#include "SelectorState.hpp"

namespace rti { namespace recording { namespace storage {

/** \ingroup RTI_RecordingServiceStorageModule
 * class rti::recording::storage::StorageStreamInfoReader
 * @brief Storage discovery stream reader
 *
 * This class is used by the \replay_product and \converter_product to query
 * the contents of storage to be replayed or converted, including:
 * - The names of streams that are stored, and their associated type
 *   representations, when recorded.
 * - The domain IDs associated with those streams.
 * - The first and last timestamps in the stored data.
 */
class StorageStreamInfoReader {
public:

    /**
     * @brief Virtual destructor
     *
     */
    virtual ~StorageStreamInfoReader() {}

    /**
     * @brief Retrieve stream information data from storage. This operation
     * should behave differently depending on the product's needs, stated in the
     * SelectorState object passed as a parameter. The stream info samples have
     * to be provided in increasing time-stamp order (reception time-stamp).
     *
     * \replay_product and \converter_product will call this method to
     * retrieve discovery data from the plugins. Discovery data describes which
     * streams are available from storage.
     *
     * @param sample_seq Vector of SampleType data. A SampleType is
     *        an rti::routing::StreamInfo.
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
            std::vector<rti::routing::StreamInfo *>& sample_seq,
            const SelectorState& selector) = 0;

    /**
     * @brief Notifies plugin it can release the read stream information objects
     *
     * @param sample_seq A vector of stream info objects that the plugin can
     *        now release resources for.
     */
    virtual void return_loan(
            std::vector<rti::routing::StreamInfo *>& sample_seq) = 0;

    /**
     * @brief The time within the recorded time range that can be considered
     * time zero of the recording
     */
    virtual int64_t service_start_time() = 0;

    /**
     * @brief The time relative to the recorded time range that can be
     * considered the final recording time of the recording
     */
    virtual int64_t service_stop_time() = 0;

    /**
     * @brief Whether this discovery stream has finished with all discovery data
     * or not.
     */
    virtual bool finished() = 0;

    /**
     * @brief Method used by \replay_product when looping, to start over. After
     * this method is called, the stream reader should be ready to start reading
     * data from the beginning of the stream, again.
     */
    virtual void reset() = 0;
};

} } } /* namespace rti::recording::storage */

#endif /* HPP_RTI_RECORDING_STORAGE_DISCOVERYSTREAMREADER_HPP_ */
