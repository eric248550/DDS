/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

============================================================================= */

#ifndef RTI_DDS_TOPIC_FLATDATATRAITS_HPP_
#define RTI_DDS_TOPIC_FLATDATATRAITS_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

// Include the FlatData API, which is shared among the traditional C++ and
// this modern C++ API
#include "rti/flat/rtiflat.hpp"

#include <rtiboost/utility/enable_if.hpp>
#include <dds/core/types.hpp>
#include <rti/topic/cdr/InterpreterHelpers.hpp>

namespace rti { namespace flat { namespace topic {
// is_flat_data_type:
// type trait that indicates if a type is a flat-data type

// General case (false_type)
template <typename TopicType>
struct is_flat_data_type_only : dds::core::false_type {};

template <typename TopicType>
struct is_flat_data_type : dds::core::false_type {};

// Only Sample<OffsetType> types are flat-data types (true_type)
template <typename OffsetType>
struct is_flat_data_type<rti::flat::Sample<OffsetType> > : dds::core::true_type {};

} } } // namespace rti::flat::topic

namespace rti { namespace xcdr {

// Specialization of serialization functions from xcdr for safe_enum, which is
// defined in dds_cpp.2.0
template <typename Enum>
struct primitive_type_traits<dds::core::safe_enum<Enum> > {
    typedef dds::core::safe_enum<Enum> SafeEnum;

    static void serialize_fast(RTIXCdrStream *stream, const SafeEnum* v)
    {
        RTIXCdrStream_serialize4ByteFast(stream, (RTIXCdr4Byte *) v);
    }
    static void deserialize_fast(RTIXCdrStream *stream, SafeEnum* v)
    {
        RTIXCdrStream_deserialize4ByteFast(stream, (RTIXCdr4Byte *) v);
    }
    static bool serialize(RTIXCdrStream *stream, const SafeEnum* v)
    {
        return RTIXCdrStream_serialize4Byte(
                stream, 
                (RTIXCdr4Byte *) v, 
                RTI_XCDR_TRUE) == RTI_XCDR_TRUE;
    }
    static bool deserialize(RTIXCdrStream *stream, SafeEnum* v)
    {
        return RTIXCdrStream_deserialize4Byte(
                stream, 
                (RTIXCdr4Byte *) v, 
                RTI_XCDR_TRUE) == RTI_XCDR_TRUE;
    }
};

} // namespace xcdr

namespace flat { namespace detail {

template <typename InnerEnum, unsigned int N>
struct final_offset_initializer<
    rti::flat::PrimitiveArrayOffset<dds::core::safe_enum<InnerEnum>, N> > {

    static bool initialize(
            rti::flat::PrimitiveArrayOffset<dds::core::safe_enum<InnerEnum>, N>& array)
    {
        dds::core::safe_enum<InnerEnum> default_value = InnerEnum::get_default();
        if (static_cast<int>(default_value.underlying()) == 0) {
            memset(array.get_buffer(), 0, array.get_buffer_size());
        } else {
            for (unsigned int i = 0; i < array.element_count(); i++) {
                array.set_element(i, default_value);
            }
        }
        return true;
    }
};

} } // namespace flat::detail

namespace topic {

// All flat-data types are uncopyable. By defining this trait as true_type
// an static_assert in DataReader methods that copy the data will fail to 
// compile
template <typename OffsetType>
struct topic_type_disabled_copy<rti::flat::Sample<OffsetType> > :
        dds::core::true_type
{
};

} // namespace topic

} // namespace rti

#endif // RTI_DDS_TOPIC_FLATDATATRAITS_HPP_
