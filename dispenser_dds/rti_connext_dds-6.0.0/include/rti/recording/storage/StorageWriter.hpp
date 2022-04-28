/*
 * (c) Copyright, Real-Time Innovations, 2016-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#include "rti/routing/StreamInfo.hpp"
#include "rti/routing/PropertySet.hpp"

#include "rti/recording/storage/StorageStreamWriter.hpp"
#include "rti/recording/storage/StorageDiscoveryStreamWriter.hpp"
#include "dds/dds.hpp"

#ifndef HPP_RTI_RECORDING_STORAGE_STORAGEWRITER_HPP_
#define HPP_RTI_RECORDING_STORAGE_STORAGEWRITER_HPP_

/** @file
 * @brief \product Pluggable Storage Writer API
 *
 * These APIs define a plugin that can be used by \product
 * to store data.
 */

namespace rti { namespace recording { namespace storage {

/** \ingroup RTI_RecordingServiceStorageModule
 * class rti::recording::storage::StorageWriter
 * @brief Storage writer
 *
 * This class is responsible for creating StorageStreamWriters when notified
 * that a new stream has been discovered.  A stream is defined by a Topic/type
 * combination
 */
class StorageWriter {
public:

    /**
     * @brief Constructor.
     *
     * Creates a StorageWriter object.
     *
     * @param properties Routing Service PropertySet.  Contains name/value
     *        pairs that can be passed to the plugin in the XML, using the
     *        following snippet:
     \verbatim
     <recording_service name="ExampleRecorder">
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
     </recording_service>
     \endverbatim
    */
    StorageWriter(const rti::routing::PropertySet& properties)
    {
        RTI_UNUSED_PARAMETER(properties);
    }

    /**
     * @brief Virtual destructor
     */
    virtual ~StorageWriter() {}

    /**
     * @brief \product calls this to create a user-data stream writer.
     *        The built-in DDS discovery topics can be recorded, however,
     *        \product will use the create_discovery_stream_writer() call to
     *        obtain a stream writer for those types.
     * @param stream_info Information about the stream to be created, such as
     *        stream name (DDS topic name).
     * @param properties A collection of value-pair properties. They include
     *        some built-in values, like:
     *        1) name='rti.recording_service.domain_id'
     *           value=the DDS domain ID the stream was found in (32-bit integer
     *           as text)
     *
     * @see create_discovery_stream_writer
     */
    virtual StorageStreamWriter * create_stream_writer(
            const rti::routing::StreamInfo& stream_info,
            const rti::routing::PropertySet& properties) = 0;

    /**
     * @brief \product calls this to create a stream writer for the DDS built-in
     *        topic DCPSParticipant.
     *        In order for the stream writer to be created, this function has to
     *        be implemented. Otherwise, no DCPSParticipant data will be
     *        recorded.
     * @see ParticipantStorageWriter
     */
    virtual ParticipantStorageWriter * create_participant_writer()
    {
        return NULL;
    }

    /**
     * @brief \product calls this to create a stream writer for the DDS built-in
     *        topic DCPSPublication.
     *        In order for the stream writer to be created, this function has to
     *        be implemented. Otherwise, no DCPSPublication data will be
     *        recorded.
     * @see PublicationStorageWriter
     */
    virtual PublicationStorageWriter * create_publication_writer()
    {
        return NULL;
    }

    /**
     * @brief \product calls this to create a stream writer for the DDS built-in
     *        topic DCPSSubscription.
     *        In order for the stream writer to be created, this function has to
     *        be implemented. Otherwise, no DCPSSubscription data will be
     *        recorded.
     * @see SubscriptionStorageWriter
     */
    virtual SubscriptionStorageWriter * create_subscription_writer()
    {
        return NULL;
    }

    /**
     * @brief \product calls this to delete a stream writer. This method should
     *        be able to work with any stream, user-data or discovery.
     *
     * @param writer Stream Writer to be deleted.
     */
    virtual void delete_stream_writer(StorageStreamWriter *writer) = 0;

private:

    StorageWriter() {}
};

} } } /* namespace rti::recording::storage */

#include "rti/recording/storage/detail/StorageWriterForwarder.hpp"
#include "rti/routing/ServiceProperty.hpp"
#include "rti/routing/detail/ForwarderUtils.hpp"

/** \ingroup RTI_RecordingServiceStorageModule
 * @def RTI_RECORDING_STORAGE_WRITER_CREATE_DECL
 * @brief Convenience macro to declare the C-style function that will be called
 * by \product to create your class
 *
 * This macro automatically declares a C wrapper function for your class
 * creation.  \product must be initialized
 * with the name of this function.  For example if your StorageWriter class is
 * 'FileStorageWriter' this creates wrapper function called
 * 'FileStorageWriter_get_storage_writer' that you must specify in your XML
 * file, such as:
 *
 * \verbatim
   <plugin_library name="StorageLibrary">
       <storage_plugin name="ExamplePlugin">
           <dll>FileStorageWriter</dll>
           <create_function>FileStorageWriter_get_storage_writer</create_function>
       </storage_plugin>
   </plugin_library>
 \endverbatim
 */
#define RTI_RECORDING_STORAGE_WRITER_CREATE_DECL(STORAGE_WRITER_CLASS) \
extern "C" RTI_USER_DLL_EXPORT \
struct RTI_RecordingServiceStorageWriter * \
STORAGE_WRITER_CLASS ## _get_storage_writer( \
        const struct RTI_RoutingServiceProperties *);

/** \ingroup RTI_RecordingServiceStorageModule
 * @brief Convenience macro to implement the C-style function that will be
 * called by \product to create your class
 *
 * This macro automatically defines a C wrapper function for your class
 * creation.  \product must be initialized
 * with the name of this function.
 */
#define RTI_RECORDING_STORAGE_WRITER_CREATE_DEF(STORAGE_WRITER_CLASS) \
struct RTI_RecordingServiceStorageWriter * \
STORAGE_WRITER_CLASS ## _get_storage_writer( \
        const struct RTI_RoutingServiceProperties *native_properties) \
{ \
    rti::routing::PropertySet properties; \
    rti::routing::PropertyAdapter::add_properties_from_native( \
            properties, \
            native_properties); \
    return new rti::recording::storage::detail::StorageWriterForwarder( \
            new STORAGE_WRITER_CLASS(properties)); \
}

#endif /* HPP_RTI_RECORDING_STORAGE_STORAGEWRITER_HPP_ */
