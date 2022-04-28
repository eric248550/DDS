/*
 * (c) Copyright, Real-Time Innovations, 2018-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef HPP_RECORDER_DB_REPLAYPLUGIN_HPP_
#define HPP_RECORDER_DB_REPLAYPLUGIN_HPP_

#include "rti/routing/PropertySet.hpp"
#include "rti/routing/StreamInfo.hpp"

#include "StorageStreamInfoReader.hpp"
#include "rti/recording/storage/StorageStreamReader.hpp"

/** @file
 * @brief \product Pluggable Storage Reader API
 *
 * These APIs define a plugin that can be used by \replay_product and
 * \converter_product to retrieve data from storage.
 */

/**
 * @brief The RTI namespace.
 *
 */
namespace rti {

/** 
 * @brief The \product namespace.
 *
 * The \product namespace includes all public classes of \product
 */
namespace recording {

/** 
 * @brief The \product storage namespace.
 *
 * The \product namespace includes all classes needed to plug in custom storage.
 */
namespace storage {

/** \ingroup RTI_RecordingServiceStorageModule
 * class rti::recording::storage::StorageReader
 * @brief Storage reader
 *
 * This class creates and deletes:
 *   - StreamInfoReaders, that will be used to query discovery data from
 *     storage and provide it to \replay_product and \converter_product
 *   - StreamReaders, that will be used to query user data from storage and
 *     provide it to \replay_product and \converter_product
 */
class StorageReader {
public:

    typedef void* SampleType;
    typedef void* InfoType;
    typedef std::vector<SampleType> SampleSeqType;
    typedef std::vector<InfoType> InfoSeqType;

    /**
     * @memberof rti::recording::storage::StorageReader
     * @brief Constructor.
     *
     * Creates a StorageReader object.
     *
     * @param properties Routing Service PropertySet.  Contains name/value
     *        pairs that can be passed to the plugin in the XML, using the
     *        following snippet:
     \verbatim
    <replay_service name="ExampleReplay>
        <storage>
            <plugin plugin_name="StorageLibrary::ExamplePlugin">
                <!-- Storage properties. These are passed to the plugin in the
                     plugin_library -->
                <property>
                    <value>
                        <element>
                            <name>example.filename</name>
                            <value>PluggableStorage.dat</value>
                        </element>
                    </value>
                </property>
            </plugin>
        </storage>
    </replay_service>
    \endverbatim
    */
    StorageReader(const rti::routing::PropertySet& properties)
    {
        RTI_UNUSED_PARAMETER(properties);
    }

    /**
     * @brief Virtual destructor
     */
    virtual ~StorageReader()
    {
    }

    /**
     * @brief \replay_product calls this to create a stream in charge of
     * discovering information about the available user-data streams in the
     * storage, and read them.
     *
     * @param properties A collection of name-value properties. They include
     *        some built-in values, like:
     *        1) name='rti.recording_service.start_timestamp'
     *           value=the initial timestamp of the selected time range (64-bit
     *           integer in text format) for this stream info reader to query
     *           data
     *        2) name='rti.recording_service.end_timestamp'
     *           value=the final timestamp of the selected time range (64-bit
     *           integer in text format) for this stream info reader to query
     *           data
     */
    virtual StorageStreamInfoReader * create_stream_info_reader(
            const rti::routing::PropertySet& properties) = 0;

    /**
     * @brief \replay_product calls this to delete a stream information reader
     *
     * @param stream_info_reader Stream information reader to be deleted.
     */
    virtual void delete_stream_info_reader(
            StorageStreamInfoReader *stream_info_reader) = 0;

    /**
     * @brief \replay_product calls this to create a user-data stream reader.
     *
     * @param stream_info Information about the stream (DDS topic) this stream
     *        reader will query from the database.
     * @param properties A collection of name-value properties. They include
     *        some built-in values, like:
     *        1) name='rti.recording_service.domain_id'
     *           value=the DDS domain ID the stream was found in (32-bit integer
     *           as text)
     *        2) name='rti.recording_service.start_timestamp'
     *           value=the initial timestamp of the selected time range (64-bit
     *           integer in text format) for this stream info reader to query
     *           data
     *        3) name='rti.recording_service.end_timestamp'
     *           value=the final timestamp of the selected time range (64-bit
     *           integer in text format) for this stream info reader to query
     *           data
     */
    virtual StorageStreamReader * create_stream_reader(
            const rti::routing::StreamInfo& stream_info,
            const rti::routing::PropertySet& properties) = 0;

    /**
    * @brief \replay_product calls this to delete a stream reader.
    *
    * @param stream_reader Stream reader to be deleted.
    */
    virtual void delete_stream_reader(StorageStreamReader *stream_reader) = 0;

private:

    StorageReader() {}

};

} } } /* namespace rti::recording::storage */

#include "rti/recording/storage/detail/StorageReaderForwarder.hpp"
#include "rti/routing/ServiceProperty.hpp"
#include "rti/routing/detail/ForwarderUtils.hpp"

/** \ingroup RTI_RecordingServiceStorageModule
 * @def RTI_RECORDING_STORAGE_READER_CREATE_DECL
 * @brief Convenience macro to declare the C-style function that will be called
 * by \replay_product and \converter_product to create your class
 *
 * This macro automatically declares a C wrapper function for your class
 * creation.  \replay_product and \converter_product must be initialized
 * with the name of this function.  For example if your StorageReader class is
 * 'FileStorageReader' this creates wrapper function called
 * 'FileStorageReader_get_storage_reader' that you must specify in your XML
 * file, such as:
 *
 * \verbatim
    <plugin_library name="StorageLibrary">
        <storage_plugin name="ExamplePlugin">
            <dll>FileStorageReader</dll>
            <create_function>FileStorageReader_get_storage_reader</create_function>
        </storage_plugin>
    </plugin_library>
    \endverbatim
 */
#define RTI_RECORDING_STORAGE_READER_CREATE_DECL(STORAGE_READER_CLASS) \
extern "C" RTI_USER_DLL_EXPORT \
struct RTI_RecordingServiceStorageReader * \
STORAGE_READER_CLASS ## _get_storage_reader( \
        const struct RTI_RoutingServiceProperties *);

/** \ingroup RTI_RecordingServiceStorageModule
 * @brief Convenience macro to implement the C-style function that will be
 * called by \replay_product and \converter_product to create your class
 *
 * This macro automatically defines a C wrapper function for your class
 * creation.  \replay_product and \converter_product must be initialized
 * with the name of this function.
 */
#define RTI_RECORDING_STORAGE_READER_CREATE_DEF(STORAGE_READER_CLASS) \
struct RTI_RecordingServiceStorageReader * \
STORAGE_READER_CLASS ## _get_storage_reader( \
        const struct RTI_RoutingServiceProperties *native_properties) \
{ \
    rti::routing::PropertySet properties; \
    rti::routing::PropertyAdapter::add_properties_from_native( \
            properties, \
            native_properties); \
    return new rti::recording::storage::detail::StorageReaderForwarder( \
            new STORAGE_READER_CLASS(properties)); \
}

#endif /* HPP_RECORDER_DB_REPLAYPLUGIN_HPP_ */

