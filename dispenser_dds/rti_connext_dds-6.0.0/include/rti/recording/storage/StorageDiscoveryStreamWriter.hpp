/*
 * (c) Copyright, Real-Time Innovations, 2018-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_STORAGE_STORAGEDISCOVERYSTREAMWRITER_HPP_
#define RTI_RECORDING_STORAGE_STORAGEDISCOVERYSTREAMWRITER_HPP_

#include <vector>

#include "dds/dds.hpp"

#include "rti/recording/storage/StorageStreamWriter.hpp"
#include "rti/routing/detail/ForwarderUtils.hpp"

namespace rti { namespace recording { namespace storage {

/** \ingroup RTI_RecordingServiceStorageModule
 *
 * @brief Convenience definition of typed StorageStreamWriter that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 *
 */
typedef TStorageStreamWriter<
        dds::topic::ParticipantBuiltinTopicData,
        dds::sub::SampleInfo> ParticipantStorageWriter;

/** \ingroup RTI_RecordingServiceStorageModule
 * @brief Convenience definition of typed StorageStreamWriter that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 *
 */
typedef TStorageStreamWriter<
        dds::topic::PublicationBuiltinTopicData,
        dds::sub::SampleInfo> PublicationStorageWriter;

/** \ingroup RTI_RecordingServiceStorageModule
 * @brief Convenience definition of typed StorageStreamWriter that requires
 * dds::core::xtypes::DynamicData for data samples and dds::sub::SampleInfo
 * for info samples.
 *
 */
typedef TStorageStreamWriter<
        dds::topic::SubscriptionBuiltinTopicData,
        dds::sub::SampleInfo> SubscriptionStorageWriter;


} } } // namespace rti::recording::storage

#endif /* RTI_RECORDING_STORAGE_STORAGEDISCOVERYSTREAMWRITER_HPP_ */
