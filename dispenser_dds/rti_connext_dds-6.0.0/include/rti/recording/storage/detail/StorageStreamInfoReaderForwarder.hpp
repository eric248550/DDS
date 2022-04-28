/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_STORAGE_DETAIL_STORAGE_DISC_STREAM_READER_FORWARDER_HPP_
#define RTI_RECORDING_STORAGE_DETAIL_STORAGE_DISC_STREAM_READER_FORWARDER_HPP_

#include <map>
#include <string>

#include "rti/recording/storage/StorageStreamInfoReader.hpp"
#include "log/log_common.h"
#include "recordingservice/recordingservice_storagereader.h"

#include "rtiboost/smart_ptr/shared_ptr.hpp"
#include "rti/routing/detail/ForwarderUtils.hpp"

#include "rti/recording/storage/StorageReader.hpp"

namespace rti { namespace recording { namespace storage { namespace detail {

/**
 * The following class is a helper to be able to fully associate the life
 * of the StorageStreamInfoReader object to a shared pointer, which will provide
 * us with RAII capabilities.
 */
class StorageStreamInfoReaderDeleter {
public:
    StorageStreamInfoReaderDeleter(StorageReader *storage_reader_parent)
            : storage_reader_parent_(storage_reader_parent)
    {
        RTIBOOST_ASSERT(storage_reader_parent != NULL);
    }

    void operator ()(StorageStreamInfoReader *stream_reader_instance)
    {
        RTIBOOST_ASSERT(stream_reader_instance != NULL);
        storage_reader_parent_->delete_stream_info_reader(
                stream_reader_instance);
    }

private:
    StorageReader *storage_reader_parent_;
};

class StorageStreamInfoReaderForwarder :
        public RTI_RecordingServiceStorageStreamInfoReader {
public:

    StorageStreamInfoReaderForwarder(
            StorageStreamInfoReader *stream_reader,
            StorageReader *storage_reader_parent)
            : storage_stream_reader_(
                      stream_reader,
                      StorageStreamInfoReaderDeleter(storage_reader_parent))
    {
        read = StorageStreamInfoReaderForwarder::read_fwd;
        return_loan = StorageStreamInfoReaderForwarder::return_loan_fwd;
        get_service_start_time =
                StorageStreamInfoReaderForwarder::get_service_start_time_fwd;
        get_service_stop_time =
                StorageStreamInfoReaderForwarder::get_service_stop_time_fwd;
        finished = StorageStreamInfoReaderForwarder::finished_fwd;
        reset = StorageStreamInfoReaderForwarder::reset_fwd;
        stream_reader_data = this;
    }

    ~StorageStreamInfoReaderForwarder()
    {
    }


    static void read_fwd(
            void *stream_reader_data,
            RTI_RoutingServiceStreamInfo ***stream_info_array,
            int *array_length,
            const struct RTI_RecordingServiceSelectorState *native_selector)
    {
        try {
            StorageStreamInfoReaderForwarder *forwarder =
                    static_cast<StorageStreamInfoReaderForwarder *>(
                            stream_reader_data);
            forwarder->storage_stream_reader_->read(
                    forwarder->sample_seq_,
                    SelectorState(*native_selector));

            *array_length = forwarder->sample_seq_.size();
            if (*array_length > 0) {
                forwarder->native_sample_seq_.resize(*array_length);
                for (size_t i = 0; i < forwarder->sample_seq_.size(); i++) {
                    forwarder->native_sample_seq_[i] =
                            &(forwarder->sample_seq_[i]->native());
                }
                *stream_info_array =
                        reinterpret_cast<RTI_RoutingServiceStreamInfo **>(
                                forwarder->native_sample_seq_.data());
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
            struct RTI_RoutingServiceStreamInfo **stream_info_array,
            int array_length)
    {
        RTIOsapiUtility_unusedParameter(stream_info_array);
        RTIOsapiUtility_unusedParameter(array_length);

        try {
            StorageStreamInfoReaderForwarder *forwarder =
                    static_cast<StorageStreamInfoReaderForwarder *>(
                            stream_reader_data);
            // Deleting what's inside the vectors (dynamic data objects) and any
            // related objects is responsability of the implementation
            forwarder->storage_stream_reader_->return_loan(
                    forwarder->sample_seq_);
            // Clear our internal containers
            forwarder->sample_seq_.clear();
            forwarder->native_sample_seq_.clear();
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

    static long long get_service_start_time_fwd(void *stream_reader_data)
    {
        try {
            StorageStreamInfoReaderForwarder *forwarder =
                    static_cast<StorageStreamInfoReaderForwarder *>(
                            stream_reader_data);
            return (long long)
                    forwarder->storage_stream_reader_->service_start_time();
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
        return 0;
    }

    static long long get_service_stop_time_fwd(void *stream_reader_data)
    {
        try {
            StorageStreamInfoReaderForwarder *forwarder =
                    static_cast<StorageStreamInfoReaderForwarder *>(
                            stream_reader_data);
            return (long long)
                    forwarder->storage_stream_reader_->service_stop_time();
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
        return 0;
    }

    static int finished_fwd(void *stream_reader_data)
    {
        try {
            StorageStreamInfoReaderForwarder *forwarder =
                    static_cast<StorageStreamInfoReaderForwarder *>(
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
            StorageStreamInfoReaderForwarder *forwarder =
                    static_cast<StorageStreamInfoReaderForwarder *>(
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

    StorageStreamInfoReader * stream_reader()
    {
        return storage_stream_reader_.get();
    }

private:
    rtiboost::shared_ptr<StorageStreamInfoReader> storage_stream_reader_;

    std::vector<rti::routing::StreamInfo *> sample_seq_;
    std::vector<RTI_RoutingServiceStreamInfo *> native_sample_seq_;
    std::vector<int32_t> domain_id_seq_;

};

} } } } // rti::recording::storage::detail

#endif // RTI_RECORDING_STORAGE_DETAIL_STORAGE_DISC_STREAM_READER_FORWARDER_HPP_
