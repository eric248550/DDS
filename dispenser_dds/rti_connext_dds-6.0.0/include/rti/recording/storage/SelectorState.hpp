/*
 * (c) Copyright, Real-Time Innovations, 2018-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef HPP_RTI_RECORDING_STORAGE_SAMPLESELECTOR_HPP_
#define HPP_RTI_RECORDING_STORAGE_SAMPLESELECTOR_HPP_

#include "dds/dds.hpp"
#include "rti/core/NativeValueType.hpp"
#include "rti/core/constants.hpp"

#include "recordingservice/recordingservice_storagereader.h"

namespace rti { namespace recording { namespace storage {

class SelectorState;


/**
 * Adapter class for the native type RTI_RecordingServiceSelectorState.
 */
class SelectorStateAdapter {
public:
    typedef RTI_RecordingServiceSelectorState native_type;

    static void initialize(native_type& native_value)
    {
        RTI_RecordingServiceSelectorState native_state =
                RTI_RecordingServiceSelectorState_INITIALIZER;
        memcpy(&native_value, &native_state, sizeof(native_state));
    }

    static void finalize(native_type&)
    {
    }

    static void copy(native_type& destination, const native_type& source)
    {
        destination.sample_state = source.sample_state;
        destination.time_range_start = source.time_range_start;
        destination.time_range_end = source.time_range_end;
        destination.max_samples = source.max_samples;
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        if (first.sample_state != second.sample_state) {
            return false;
        }
        if (first.max_samples != second.max_samples) {
            return false;
        }
        if (!DDS_Time_t_equals(
                first.time_range_start,
                second.time_range_start)) {
            return false;
        }
        return DDS_Time_t_equals(
                first.time_range_end,
                second.time_range_end);
    }
};

} }

/*
 * Type native_type_traits needs to be defined in the rti::core namespace.
 */
namespace core {

template <>
struct native_type_traits<rti::recording::storage::SelectorState> {
    typedef rti::recording::storage::SelectorStateAdapter adapter_type;
    typedef RTI_RecordingServiceSelectorState native_type;
};

}

namespace recording { namespace storage {

/** \ingroup RTI_RecordingServiceStorageModule 
 *
 * @brief This class is used by \replay_product or \converter_product when
 * asking the storage plugin for data. It specifies whether the samples should
 * be 'not read' samples, that haven't been returned before, or that 'any'
 * sample state is needed. It also allows to specify the time range the samples
 * returned have to lay within (upper and lower limit).
 */
class SelectorState : public rti::core::NativeValueType<SelectorState> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(SelectorState)

    typedef rti::core::NativeValueType<SelectorState> Base;

    SelectorState()
    {
    }

    SelectorState(const RTI_RecordingServiceSelectorState &native) :
        Base(native)
    {
    }

    /**
     * @brief Returns the sample state. This is used to represent the state of
     *        the samples asked for, whether they have been already read or not.
     *        When this value is set to:
     *        - Not read: the storage plugin should provide samples that hasn't
     *          provided before. This implies that the storage plugin has to
     *          keep track of what samples it has already returned and what
     *          samples it hasn't.
     *        - Any: the storage plugin should provide all the samples within
     *          the specified time range, no matter their read state. This
     *          implies a stateless read, the storage plugin is not supposed to
     *          keep track of what samples have been read or not in this case.
     *        - Read: in the current version, this sample state is not used by
     *          \replay_product or \converter_product.
     */
    inline dds::sub::status::SampleState sample_state() const
    {
        return dds::sub::status::SampleState(native().sample_state);
    }

    /**
     * @brief Sets the sample state.
     */
    SelectorState& sample_state(const dds::sub::status::SampleState& state)
    {
         native().sample_state = state.to_ulong();
         return *this;
    }

    /**
     * @brief Returns the time that represents the lower limit (inclusive) of
     *        the time range the retrieved data samples should lay within. When
     *        retrieving stateful samples (not read), this parameter becomes
     *        irrelevant as the lower limit should be the time-stamp of the
     *        latest sample returned.
     */
    inline dds::core::Time time_range_start() const
    {
        return dds::core::Time(
                native().time_range_start.sec,
                native().time_range_start.nanosec);
    }

    /**
     * @brief Like the time_range_start() method, but returns the timestamp in
     *        long long (int-64) format
     */
    inline int64_t timestamp_range_start() const
    {
        int64_t timestamp =
                (int64_t) native().time_range_start.sec
                        * rti::core::nanosec_per_sec
                + native().time_range_start.nanosec;
        return timestamp;
    }

    /**
     * @brief Sets the lower limit of the time range.
     */
    SelectorState& time_range_start(const dds::core::Time& time_range_start)
    {
        native().time_range_start.sec = (DDS_Long) time_range_start.sec();
        native().time_range_start.nanosec =
                (DDS_UnsignedLong) time_range_start.nanosec();
        return *this;
    }

    /**
     * @brief Returns the time that represents the upper limit (inclusive) of
     *        the time range the retrieved samples should lay within. This
     *        parameter is always relevant, as samples should be returned in
     *        increasing time-stamp order.
     */
    inline dds::core::Time time_range_end() const
    {
        return dds::core::Time(
                native().time_range_end.sec,
                native().time_range_end.nanosec);
    }

    /**
     * @brief Like the time_range_end() method, but returns the timestamp in
     *        long long (int-64) format
     */
    inline int64_t timestamp_range_end() const
    {
        int64_t timestamp =
                (int64_t) native().time_range_end.sec
                        * rti::core::nanosec_per_sec
                + native().time_range_end.nanosec;
        return timestamp;
    }

    /**
     * @brief Sets the upper limit of the time range.
     */
    SelectorState& time_range_end(const dds::core::Time& time_range_end)
    {
        native().time_range_end.sec = (DDS_Long) time_range_end.sec();
        native().time_range_end.nanosec =
                (DDS_UnsignedLong) time_range_end.nanosec();
        return *this;
    }

    /**
     * @brief Returns the maximum number of samples to be returned by a single
     *        read() call, when the value is positive.
     *        A negative value indicates an unlimited number of samples.
     */
    inline int32_t max_samples() const
    {
        return native().max_samples;
    }

    /**
     * @brief Sets the maximum number of samples to be returned by a single call
     *        to read().
     */
    SelectorState& max_samples(const int32_t max_samples)
    {
        native().max_samples = (int) max_samples;
        return *this;
    }

};


} } } /* namespace rti::recording::storage */

#endif /* HPP_RTI_RECORDING_STORAGE_SAMPLESELECTOR_HPP_ */
