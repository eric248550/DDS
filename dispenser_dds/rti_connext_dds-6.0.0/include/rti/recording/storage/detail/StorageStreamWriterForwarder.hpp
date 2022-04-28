/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_STORAGE_DETAIL_STORAGE_STREAM_WRITER_FORWARDER_HPP_
#define RTI_RECORDING_STORAGE_DETAIL_STORAGE_STREAM_WRITER_FORWARDER_HPP_

#include <map>
#include <string>

#include "log/log_common.h"
#include "recordingservice/recordingservice_storagewriter.h"

#include "rtiboost/smart_ptr/shared_ptr.hpp"
#include "rti/routing/detail/ForwarderUtils.hpp"

#include "rti/recording/storage/StorageWriter.hpp"
#include "rti/recording/storage/StorageStreamWriter.hpp"

namespace rti { namespace recording { namespace storage { namespace detail {

/**
 * The following class is a helper to be able to fully associate the life
 * of the StorageStreamWriter object to a shared pointer, which will provide
 * us with RAII capabilities.
 */
class StorageStreamWriterDeleter {
public:
    StorageStreamWriterDeleter(StorageWriter *storage_writer_parent)
            : storage_writer_parent_(storage_writer_parent)
    {
        RTIBOOST_ASSERT(storage_writer_parent != NULL);
    }

    void operator ()(StorageStreamWriter *stream_writer_instance)
    {
        if (stream_writer_instance != NULL) {
            storage_writer_parent_->delete_stream_writer(
                    stream_writer_instance);
        }
    }

private:
    StorageWriter *storage_writer_parent_;
};

class StorageStreamWriterForwarder :
        public RTI_RecordingServiceStorageStreamWriter {
public:

    StorageStreamWriterForwarder(
            StorageStreamWriter *stream_writer,
            StorageWriter *storage_writer_parent)
            : storage_stream_writer_(
                      stream_writer,
                      StorageStreamWriterDeleter(storage_writer_parent))
    {
        store = StorageStreamWriterForwarder::store_fwd;
        stream_writer_data = this;
    }

    ~StorageStreamWriterForwarder()
    {
    }

    static void store_fwd(
            void *stream_writer_data,
            const RTI_RoutingServiceSample *samples,
            const RTI_RoutingServiceSampleInfo *sample_infos,
            const int count)
    {
        try {
            StorageStreamWriterForwarder *forwarder =
                    static_cast<StorageStreamWriterForwarder *>(
                            stream_writer_data);
            // Fill in internal vector with incoming samples
            forwarder->sample_seq_.assign(samples, samples + count);
            // Fill in internal vector with incoming sample infos, the sample
            // info array is optional so check for validity before doing
            // anything
            if (sample_infos != NULL) {
                forwarder->info_seq_.assign(sample_infos, sample_infos + count);
            }
            // Forward the call to the StorageStreamWriter implementation
            forwarder->storage_stream_writer_->store(
                    forwarder->sample_seq_,
                    forwarder->info_seq_);
        } catch (const std::exception& ex) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    ex.what());
        } catch (...) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    "unknown exception");
        }
    }

    StorageStreamWriter * stream_writer()
    {
        return storage_stream_writer_.get();
    }

private:
    rtiboost::shared_ptr<StorageStreamWriter> storage_stream_writer_;

    std::vector<StorageStreamWriter::SamplePtr> sample_seq_;
    std::vector<StorageStreamWriter::InfoPtr> info_seq_;
};

/**
 * This generic forwarding wrapper class defines a store method that forwards a
 * call to a native stream writer's store method to a C++ stream writer
 * specialisation.
 * Two template parameters:
 * - NativeStreamWriterType: one of the native stream writer types defined
 *   in recordingservice_storagewriter.h. These types have to implement a
 *   store() method to store the samples.
 * - NativeStoredType: the type passed in to the store() method.
 */
template<typename NativeStreamWriterType, typename NativeStoredType>
class StorageGenericStreamWriterForwarder : public NativeStreamWriterType {
public:

    StorageGenericStreamWriterForwarder(
            StorageStreamWriter *stream_writer,
            StorageWriter *storage_writer_parent)
            : storage_stream_writer_(
                      stream_writer,
                      StorageStreamWriterDeleter(storage_writer_parent))
    {
    }

    ~StorageGenericStreamWriterForwarder()
    {
    }

    static void store_fwd(
            void *stream_writer_data,
            const NativeStoredType **samples,
            const RTI_RoutingServiceSampleInfo *sample_infos,
            const int count)
    {
        try {
            StorageGenericStreamWriterForwarder *forwarder =
                    static_cast<StorageGenericStreamWriterForwarder *>(
                            stream_writer_data);
            /*
             * In the case of the generic stream writer forwarder, used for the
             * built-in DDS discovery topics, we are not guaranteed that the
             * stream writer will not be null. This can happen if the user
             * doesn't override the default implementations, which return null.
             * The user may not have interest in recording one or any of the
             * topics. We should account for that case.
             */
            if (forwarder->storage_stream_writer_.get() == NULL) {
                return;
            }
            // Fill in internal vector with incoming samples
            StorageStreamWriter::SamplePtr *untyped_samples =
                    (StorageStreamWriter::SamplePtr *) samples;
            forwarder->sample_seq_.assign(
                    untyped_samples,
                    untyped_samples + count);
            /*
             * Fill in internal vector with incoming sample infos, the sample
             * info array is optional so check for validity before doing
             * anything
             */
            if (sample_infos != NULL) {
                forwarder->info_seq_.assign(sample_infos, sample_infos + count);
            }
            // Forward the call to the StorageStreamWriter implementation
            forwarder->storage_stream_writer_->store(
                    forwarder->sample_seq_,
                    forwarder->info_seq_);
        } catch (const std::exception& ex) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    ex.what());
        } catch (...) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    "unknown exception");
        }
    }

    StorageStreamWriter * stream_writer()
    {
        return storage_stream_writer_.get();
    }

private:
    rtiboost::shared_ptr<StorageStreamWriter> storage_stream_writer_;

    std::vector<StorageStreamWriter::SamplePtr> sample_seq_;
    std::vector<StorageStreamWriter::InfoPtr> info_seq_;

};

class StorageParticipantWriterForwarder :
        public StorageGenericStreamWriterForwarder<
                RTI_RecordingServiceStorageParticipantWriter,
                DDS_ParticipantBuiltinTopicData> {
public:

    StorageParticipantWriterForwarder(
            StorageStreamWriter *stream_writer,
            StorageWriter *storage_writer_parent) :
        StorageGenericStreamWriterForwarder<
                RTI_RecordingServiceStorageParticipantWriter,
                DDS_ParticipantBuiltinTopicData>(
                        stream_writer,
                        storage_writer_parent)
    {
        store = store_fwd;
        stream_writer_data = this;
    }
};

class StoragePublicationWriterForwarder :
        public StorageGenericStreamWriterForwarder<
                RTI_RecordingServiceStoragePublicationWriter,
                DDS_PublicationBuiltinTopicData> {
public:

    StoragePublicationWriterForwarder(
            StorageStreamWriter *stream_writer,
            StorageWriter *storage_writer_parent) :
        StorageGenericStreamWriterForwarder<
                RTI_RecordingServiceStoragePublicationWriter,
                DDS_PublicationBuiltinTopicData>(
                        stream_writer,
                        storage_writer_parent)
    {
        store = store_fwd;
        stream_writer_data = this;
    }
};

class StorageSubscriptionWriterForwarder :
        public StorageGenericStreamWriterForwarder<
                RTI_RecordingServiceStorageSubscriptionWriter,
                DDS_SubscriptionBuiltinTopicData> {
public:

    StorageSubscriptionWriterForwarder(
            StorageStreamWriter *stream_writer,
            StorageWriter *storage_writer_parent) :
        StorageGenericStreamWriterForwarder<
                RTI_RecordingServiceStorageSubscriptionWriter,
                DDS_SubscriptionBuiltinTopicData>(
                        stream_writer,
                        storage_writer_parent)
    {
        store = store_fwd;
        stream_writer_data = this;
    }
};

} } } } // rti::recording::storage::detail

#endif // RTI_RECORDING_STORAGE_DETAIL_STORAGE_STREAM_WRITER_FORWARDER_HPP_
