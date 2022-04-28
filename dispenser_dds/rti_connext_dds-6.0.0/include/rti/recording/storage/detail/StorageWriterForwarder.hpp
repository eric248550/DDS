/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_STORAGE_DETAIL_STORAGE_WRITER_FORWARDER_HPP_
#define RTI_RECORDING_STORAGE_DETAIL_STORAGE_WRITER_FORWARDER_HPP_

#include <map>
#include <string>

#include "log/log_common.h"
#include "rti/routing/detail/ForwarderUtils.hpp"
#include "rti/routing/ServiceProperty.hpp"

#include "recordingservice/recordingservice_storagewriter.h"
#include "rti/recording/storage/StorageDefs.hpp"
#include "rti/recording/storage/detail/StorageStreamWriterForwarder.hpp"

namespace rti { namespace recording { namespace storage { namespace detail {

class StorageWriterForwarder : public RTI_RecordingServiceStorageWriter {
public:

    StorageWriterForwarder(StorageWriter *storage_writer) :
        storage_writer_(storage_writer)
    {
        // User-data stream creation function
        create_stream_writer = StorageWriterForwarder::create_stream_writer_fwd;
        // Discovery stream creation functions
        create_participant_writer =
                StorageWriterForwarder::create_participant_writer_fwd;
        create_publication_writer =
                StorageWriterForwarder::create_publication_writer_fwd;
        create_subscription_writer =
                StorageWriterForwarder::create_subscription_writer_fwd;
        // User-data stream deletion function
        delete_stream_writer = StorageWriterForwarder::delete_stream_writer_fwd;
        // Discovery stream deletion functions
        delete_participant_writer =
                StorageWriterForwarder::delete_participant_writer_fwd;
        delete_publication_writer =
                StorageWriterForwarder::delete_publication_writer_fwd;
        delete_subscription_writer =
                StorageWriterForwarder::delete_subscription_writer_fwd;
        // Delete storage writer instance method
        delete_instance = StorageWriterForwarder::delete_instance_fwd;

        storage_writer_data = this;
    }

    ~StorageWriterForwarder()
    {
    }

    static void delete_instance_fwd(
            struct RTI_RecordingServiceStorageWriter *storage_writer)
    {
        try {
            StorageWriterForwarder *forwarder =
                    static_cast<StorageWriterForwarder *>(storage_writer);
            delete forwarder;
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

    static RTI_RecordingServiceStorageStreamWriter * create_stream_writer_fwd(
            void *storage_writer,
            const RTI_RoutingServiceStreamInfo *native_stream_info,
            const RTI_RoutingServiceProperties *native_properties)
    {
        RTIBOOST_ASSERT(!rti::recording::is_discovery_stream(
                std::string(native_stream_info->stream_name)));
        try {
            StorageWriterForwarder *forwarder =
                    static_cast<StorageWriterForwarder *>(storage_writer);
            rti::routing::StreamInfo stream_info(*native_stream_info);
            rti::routing::PropertySet properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);
            StorageStreamWriterForwarder *stream_writer_forwarder =
                    new StorageStreamWriterForwarder(
                            forwarder->storage_writer_->create_stream_writer(
                                    stream_info,
                                    properties),
                            forwarder->storage_writer_.get());
            return stream_writer_forwarder;
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
        return NULL;
    }

    static RTI_RecordingServiceStorageParticipantWriter *
    create_participant_writer_fwd(void *storage_writer)
    {
        try {
            StorageWriterForwarder *forwarder =
                    static_cast<StorageWriterForwarder *>(storage_writer);
            StorageParticipantWriterForwarder *stream_writer_forwarder =
                    new StorageParticipantWriterForwarder(
                            forwarder->storage_writer_->create_participant_writer(),
                            forwarder->storage_writer_.get());
            return stream_writer_forwarder;
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
        return NULL;
    }

    static RTI_RecordingServiceStoragePublicationWriter *
    create_publication_writer_fwd(void *storage_writer)
    {
        try {
            StorageWriterForwarder *forwarder =
                    static_cast<StorageWriterForwarder *>(storage_writer);
            StoragePublicationWriterForwarder *stream_writer_forwarder =
                    new StoragePublicationWriterForwarder(
                            forwarder->storage_writer_->create_publication_writer(),
                            forwarder->storage_writer_.get());
            return stream_writer_forwarder;
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
        return NULL;
    }

    static RTI_RecordingServiceStorageSubscriptionWriter *
    create_subscription_writer_fwd(void *storage_writer)
    {
        try {
            StorageWriterForwarder *forwarder =
                    static_cast<StorageWriterForwarder *>(storage_writer);
            StorageSubscriptionWriterForwarder *stream_writer_forwarder =
                    new StorageSubscriptionWriterForwarder(
                            forwarder->storage_writer_->create_subscription_writer(),
                            forwarder->storage_writer_.get());
            return stream_writer_forwarder;
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
        return NULL;
    }

    static void delete_stream_writer_fwd(
            void *,
            RTI_RecordingServiceStorageStreamWriter *storage_stream_writer)
    {
        try {
            StorageStreamWriterForwarder *stream_writer_forwarder =
                    static_cast<StorageStreamWriterForwarder *>(
                            storage_stream_writer);
            delete stream_writer_forwarder;
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

    static void delete_participant_writer_fwd(
            void *,
            RTI_RecordingServiceStorageParticipantWriter *stream_writer)
    {
        try {
            StorageParticipantWriterForwarder *forwarder =
                    static_cast<StorageParticipantWriterForwarder *>(
                            stream_writer);
            delete forwarder;
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

    static void delete_publication_writer_fwd(
            void *,
            RTI_RecordingServiceStoragePublicationWriter *stream_writer)
    {
        try {
            StoragePublicationWriterForwarder *forwarder =
                    static_cast<StoragePublicationWriterForwarder *>(
                            stream_writer);
            delete forwarder;
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

    static void delete_subscription_writer_fwd(
            void *,
            RTI_RecordingServiceStorageSubscriptionWriter *stream_writer)
    {
        try {
            StorageSubscriptionWriterForwarder *forwarder =
                    static_cast<StorageSubscriptionWriterForwarder *>(
                            stream_writer);
            delete forwarder;
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

private:

    rtiboost::shared_ptr<StorageWriter> storage_writer_;

};

} } } } // rti::recording::storage::namespace

#endif // RTI_RECORDING_STORAGE_DETAIL_STORAGE_WRITER_FORWARDER_HPP_
