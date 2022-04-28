/*
 * (c) Copyright, Real-Time Innovations, 2018-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef HPP_RTI_RECORDING_STORAGE_STORAGEDEFS_HPP_
#define HPP_RTI_RECORDING_STORAGE_STORAGEDEFS_HPP_

#ifndef dds_c_builtin_h
#include "dds_c/dds_c_builtin.h"
#endif

#include <dds/core/Exception.hpp>
#include "rtiboost/smart_ptr/shared_ptr.hpp"
#include "rti/routing/PropertySet.hpp"

#include "recordingservice/recordingservice_storagereader.h"
#include "recordingservice/recordingservice_storagewriter.h"

namespace rti { namespace recording {

// Writer-related defines
typedef rtiboost::shared_ptr<RTI_RecordingServiceStorageWriter>
        StorageWriterSharedPtr;
typedef rtiboost::shared_ptr<RTI_RecordingServiceStorageStreamWriter>
        StorageStreamWriterSharedPtr;
typedef rtiboost::shared_ptr<RTI_RecordingServiceStorageParticipantWriter>
        StorageParticipantWriterSharedPtr;
typedef rtiboost::shared_ptr<RTI_RecordingServiceStoragePublicationWriter>
        StoragePublicationWriterSharedPtr;
typedef rtiboost::shared_ptr<RTI_RecordingServiceStorageSubscriptionWriter>
        StorageSubscriptionWriterSharedPtr;

// Reader-related defines
typedef rtiboost::shared_ptr<RTI_RecordingServiceStorageReader>
        StorageReaderSharedPtr;
typedef rtiboost::shared_ptr<RTI_RecordingServiceStorageStreamReader>
        StorageStreamReaderSharedPtr;
typedef rtiboost::shared_ptr<RTI_RecordingServiceStorageStreamInfoReader>
        StorageStreamInfoReaderSharedPtr;

/*
 * Helper classes to be used with the pointer definitions above, to create the
 * smart pointers and use this class as a deleter (pointing to the () operator)
 */

class NativeStorageStreamWriterDeleter {
public:
    NativeStorageStreamWriterDeleter(
            RTI_RecordingServiceStorageWriter *storage_writer_parent)
            : storage_writer_parent_(storage_writer_parent)
    {
        RTIBOOST_ASSERT(storage_writer_parent != NULL);
    }

    void operator ()(RTI_RecordingServiceStorageStreamWriter *instance)
    {
        if (instance != NULL) {
            storage_writer_parent_->delete_stream_writer(
                    storage_writer_parent_,
                    instance);
        }
    }

    void operator ()(RTI_RecordingServiceStorageParticipantWriter *instance)
    {
        // The delete participant writer operation is not required, better be
        // safe than sorry
        if (instance != NULL
                && storage_writer_parent_->delete_participant_writer != NULL) {
            storage_writer_parent_->delete_participant_writer(
                    storage_writer_parent_,
                    instance);
        }
    }

    void operator ()(RTI_RecordingServiceStoragePublicationWriter *instance)
    {
        // The delete publication writer operation is not required, better be
        // safe than sorry
        if (instance != NULL
                && storage_writer_parent_->delete_publication_writer != NULL) {
            storage_writer_parent_->delete_publication_writer(
                    storage_writer_parent_,
                    instance);
        }
    }

    void operator ()(RTI_RecordingServiceStorageSubscriptionWriter *instance)
    {
        // The delete subscription writer operation is not required, better be
        // safe than sorry
        if (instance != NULL
                && storage_writer_parent_->delete_subscription_writer != NULL) {
            storage_writer_parent_->delete_subscription_writer(
                    storage_writer_parent_,
                    instance);
        }
    }

private:
    RTI_RecordingServiceStorageWriter *storage_writer_parent_;
};

class NativeStorageStreamInfoReaderDeleter {
public:
    NativeStorageStreamInfoReaderDeleter(
            RTI_RecordingServiceStorageReader *storage_reader_parent)
            : storage_reader_parent_(storage_reader_parent)
    {
        RTIBOOST_ASSERT(storage_reader_parent != NULL);
    }

    void operator ()(RTI_RecordingServiceStorageStreamInfoReader *instance)
    {
        if (instance != NULL) {
            storage_reader_parent_->delete_stream_info_reader(
                    storage_reader_parent_,
                    instance);
        }
    }

private:
    RTI_RecordingServiceStorageReader *storage_reader_parent_;
};

class NativeStorageStreamReaderDeleter {
public:
    NativeStorageStreamReaderDeleter(
            RTI_RecordingServiceStorageReader *storage_reader_parent)
            : storage_reader_parent_(storage_reader_parent)
    {
        RTIBOOST_ASSERT(storage_reader_parent != NULL);
    }

    void operator ()(RTI_RecordingServiceStorageStreamReader *instance)
    {
        if (instance != NULL) {
            storage_reader_parent_->delete_stream_reader(
                    storage_reader_parent_,
                    instance);
        }
    }

private:
    RTI_RecordingServiceStorageReader *storage_reader_parent_;
};

inline bool is_discovery_stream(const std::string& stream_name)
{
    if (stream_name.compare(DDS_PARTICIPANT_TOPIC_NAME) == 0
            || stream_name.compare(DDS_PUBLICATION_TOPIC_NAME) == 0
            || stream_name.compare(DDS_SUBSCRIPTION_TOPIC_NAME) == 0) {
        return true;
    }
    return false;
}

inline std::string domain_id_property_name()
{
    return RTI_RECORDING_SERVICE_DOMAIN_ID_PROPERTY_NAME;
}

inline std::string start_timestamp_property_name()
{
    return RTI_RECORDING_SERVICE_START_TIMESTAMP_PROPERTY_NAME;
}

inline std::string end_timestamp_property_name()
{
    return RTI_RECORDING_SERVICE_END_TIMESTAMP_PROPERTY_NAME;
}

template <typename T>
inline T get_from_properties(
        const rti::routing::PropertySet& properties,
        const std::string& property_name)
{
    rti::routing::PropertySet::const_iterator found =
            properties.find(property_name);
    if (found == properties.end()) {
        throw dds::core::Error(
                "!found property with name=" +  property_name);
    }
    T value;
    std::stringstream str_stream(found->second);
    str_stream >> value;
    if (str_stream.fail()) {
       throw dds::core::Error(
                "!parse value from property with name=" +  property_name);
    }
    return value;
}

template <typename T>
inline void add_to_properties(
        rti::routing::PropertySet& properties,
        const std::string& property_name,
        const T value)
{
    rti::routing::PropertySet::const_iterator found =
            properties.find(property_name);
    if (found != properties.end()) {
        return;
    }
    std::stringstream str_stream;
    str_stream << value;
    if (str_stream.fail()) {
        throw dds::core::Error(
                "!add value for property with name=" +  property_name);
    }
    properties[property_name] = str_stream.str();
}


} } /* namespace rti::recording */

#endif /* HPP_RTI_RECORDING_STORAGE_STORAGEDEFS_HPP_ */
