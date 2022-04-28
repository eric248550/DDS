/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_STORAGE_DETAIL_STORAGE_READER_FORWARDER_HPP_
#define RTI_RECORDING_STORAGE_DETAIL_STORAGE_READER_FORWARDER_HPP_


#include "log/log_common.h"

#include "rti/routing/detail/ForwarderUtils.hpp"
#include "rti/routing/ServiceProperty.hpp"

#include "recordingservice/recordingservice_storagereader.h"
#include "rti/recording/storage/detail/StorageStreamReaderForwarder.hpp"
#include "StorageStreamInfoReaderForwarder.hpp"

namespace rti { namespace recording { namespace storage { namespace detail {

class StorageReaderForwarder : public RTI_RecordingServiceStorageReader {
public:

    StorageReaderForwarder(StorageReader *storage_reader)
            : storage_reader_(storage_reader)
    {
        create_stream_reader = StorageReaderForwarder::create_stream_reader_fwd;
        delete_stream_reader = StorageReaderForwarder::delete_stream_reader_fwd;
        create_stream_info_reader =
                StorageReaderForwarder::create_stream_info_reader_fwd;
        delete_stream_info_reader =
                StorageReaderForwarder::delete_stream_info_reader_fwd;
        delete_instance = StorageReaderForwarder::delete_instance_fwd;

        storage_reader_data = this;
    }

    ~StorageReaderForwarder()
    {
    }

    static void delete_instance_fwd(
            struct RTI_RecordingServiceStorageReader *storage_reader)
    {
        try {
            StorageReaderForwarder *forwarder =
                    static_cast<StorageReaderForwarder *>(storage_reader);
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

    static RTI_RecordingServiceStorageStreamReader * create_stream_reader_fwd(
            void *storage_reader,
            const struct RTI_RoutingServiceStreamInfo *native_stream_info,
            const struct RTI_RoutingServiceProperties *native_properties)
    {
        try {
            StorageReaderForwarder *forwarder =
                    static_cast<StorageReaderForwarder *>(storage_reader);
            rti::routing::StreamInfo stream_info(*native_stream_info);
            rti::routing::PropertySet properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);
            StorageStreamReaderForwarder *stream_reader_forwarder =
                    new StorageStreamReaderForwarder(
                            forwarder->storage_reader_->create_stream_reader(
                                    stream_info,
                                    properties),
                            forwarder->storage_reader_.get());
            return stream_reader_forwarder;
        } catch (const std::exception& ex) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    ex.what());
            return NULL;
        } catch (...) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    "unknown exception");
        }
        return NULL;
    }

    static void delete_stream_reader_fwd(
            void *,
            RTI_RecordingServiceStorageStreamReader *storage_stream_reader)
    {
        try {
            StorageStreamReaderForwarder *stream_reader_forwarder =
                    static_cast<StorageStreamReaderForwarder *>(
                            storage_stream_reader);
            delete stream_reader_forwarder;
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

    static RTI_RecordingServiceStorageStreamInfoReader *
    create_stream_info_reader_fwd(
            void *storage_reader_data,
            const struct RTI_RoutingServiceProperties *native_properties)
    {
        try {
            StorageReaderForwarder *forwarder =
                    static_cast<StorageReaderForwarder *>(storage_reader_data);
            rti::routing::PropertySet properties;
            rti::routing::PropertyAdapter::add_properties_from_native(
                    properties,
                    native_properties);
            StorageStreamInfoReaderForwarder *disc_reader_forwarder =
                    new StorageStreamInfoReaderForwarder(
                            forwarder->storage_reader_->create_stream_info_reader(
                                    properties),
                            forwarder->storage_reader_.get());
            return disc_reader_forwarder;
        } catch (const std::exception& ex) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    ex.what());
            return NULL;
        } catch (...) {
            RTILog_printContextAndMsg(
                    RTI_FUNCTION_NAME,
                    &RTI_LOG_ANY_s,
                    "unknown exception");
        }
        return NULL;
    }

    static void delete_stream_info_reader_fwd(
            void *,
            RTI_RecordingServiceStorageStreamInfoReader *stream_info_reader)
    {
        try {
            StorageStreamInfoReaderForwarder *disc_reader_forwarder =
                    static_cast<StorageStreamInfoReaderForwarder *>(
                            stream_info_reader);
            delete disc_reader_forwarder;
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

    rtiboost::shared_ptr<StorageReader> storage_reader_;

};

} } } }

#endif // RTI_RECORDING_STORAGE_DETAIL_STORAGE_WRITER_FORWARDER_HPP_
