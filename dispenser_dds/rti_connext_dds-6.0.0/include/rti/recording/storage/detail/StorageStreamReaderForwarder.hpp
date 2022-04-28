/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_STORAGE_DETAIL_STORAGE_STREAM_READER_FORWARDER_HPP_
#define RTI_RECORDING_STORAGE_DETAIL_STORAGE_STREAM_READER_FORWARDER_HPP_

#include <map>
#include <string>

#include "log/log_common.h"
#include "recordingservice/recordingservice_storagereader.h"

#include "rtiboost/smart_ptr/shared_ptr.hpp"
#include "rti/routing/detail/ForwarderUtils.hpp"

#include "rti/recording/storage/StorageReader.hpp"
#include "rti/recording/storage/StorageStreamReader.hpp"
#include "rti/recording/storage/SelectorState.hpp"

namespace rti { namespace recording { namespace storage { namespace detail {

/**
 * The following class is a helper to be able to fully associate the life
 * of the StorageStreamReader object to a shared pointer, which will provide
 * us with RAII capabilities.
 */
class StorageStreamReaderDeleter {
public:
    StorageStreamReaderDeleter(StorageReader *storage_reader_parent)
            : storage_reader_parent_(storage_reader_parent)
    {
        RTIBOOST_ASSERT(storage_reader_parent != NULL);
    }

    void operator ()(StorageStreamReader *stream_reader_instance)
    {
        RTIBOOST_ASSERT(stream_reader_instance != NULL);
        storage_reader_parent_->delete_stream_reader(
                stream_reader_instance);
    }

private:
    StorageReader *storage_reader_parent_;
};

class StorageStreamReaderForwarder :
        public RTI_RecordingServiceStorageStreamReader {
public:

    StorageStreamReaderForwarder(
            StorageStreamReader *stream_reader,
            StorageReader *storage_reader_parent)
            : storage_stream_reader_(
                      stream_reader,
                      StorageStreamReaderDeleter(storage_reader_parent))
    {
        read = StorageStreamReaderForwarder::read_fwd;
        return_loan = StorageStreamReaderForwarder::return_loan_fwd;
        finished = StorageStreamReaderForwarder::finished_fwd;
        reset = StorageStreamReaderForwarder::reset_fwd;
        stream_reader_data = this;
    }

    ~StorageStreamReaderForwarder()
    {
    }

    static void read_fwd(
            void *stream_reader_data,
            RTI_RoutingServiceSample **sample_array,
            RTI_RoutingServiceSampleInfo **sample_info_array,
            int *array_length,
            const struct RTI_RecordingServiceSelectorState *native_selector)
    {
        RTIOsapiUtility_unusedParameter(sample_array);
        RTIOsapiUtility_unusedParameter(sample_info_array);
        RTIOsapiUtility_unusedParameter(array_length);

        try {
            StorageStreamReaderForwarder *forwarder =
                    static_cast<StorageStreamReaderForwarder *>(
                            stream_reader_data);
            forwarder->storage_stream_reader_->read(
                    forwarder->sample_seq_,
                    forwarder->info_seq_,
                    SelectorState(*native_selector));
            *array_length = forwarder->sample_seq_.size();
            if (*array_length > 0) {
                *sample_array = forwarder->sample_seq_.data();
                *sample_info_array = forwarder->info_seq_.data();
            }
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

    static void return_loan_fwd(
            void *stream_reader_data,
            RTI_RoutingServiceSample *sample_array,
            RTI_RoutingServiceSampleInfo *sample_info_array,
            int array_length)
    {
        RTIOsapiUtility_unusedParameter(sample_array);
        RTIOsapiUtility_unusedParameter(sample_info_array);
        RTIOsapiUtility_unusedParameter(array_length);

        try {
            StorageStreamReaderForwarder *forwarder =
                    static_cast<StorageStreamReaderForwarder *>(
                            stream_reader_data);
            // Deleting what's inside the vectors (dynamic data objects) and any
            // related objects is responsability of the implementation
            forwarder->storage_stream_reader_->return_loan(
                    forwarder->sample_seq_,
                    forwarder->info_seq_);
            // Clear our internal containers
            forwarder->sample_seq_.clear();
            forwarder->info_seq_.clear();
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

    static int finished_fwd(void *stream_reader_data)
    {
        try {
            StorageStreamReaderForwarder *forwarder =
                    static_cast<StorageStreamReaderForwarder *>(
                            stream_reader_data);
            return (forwarder->storage_stream_reader_->finished() ?
                    RTI_TRUE :
                    RTI_FALSE);
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
        return RTI_FALSE;
    }

    static void reset_fwd(void *stream_reader_data)
    {
        try {
            StorageStreamReaderForwarder *forwarder =
                    static_cast<StorageStreamReaderForwarder *>(
                            stream_reader_data);
            forwarder->storage_stream_reader_->reset();
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

    StorageStreamReader * stream_reader()
    {
        return storage_stream_reader_.get();
    }

private:
    rtiboost::shared_ptr<StorageStreamReader> storage_stream_reader_;

    std::vector<StorageStreamReader::SamplePtr> sample_seq_;
    std::vector<StorageStreamReader::InfoPtr> info_seq_;

};

} } } } // rti::recording::storage::detail

#endif // RTI_RECORDING_STORAGE_DETAIL_STORAGE_STREAM_READER_FORWARDER_HPP_
