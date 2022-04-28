/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

============================================================================= */

//
// Support for flat-data types in the modern C++ API.
//
// *** Important
// DO NOT include this header from any other header in the API.
// This header should be included only by generated code that uses flat data.
// Applications that never use flat data will not compile this.
//
// There are three pieces that together provide Flat-Data for a data type:
//  - The generic code in xcdr.1.0/hpp, where most of the API is implemented and
//    is common for the three C++ APIs (modern, traditional, and micro)
//  - The API-specific header (this header). It customizes certain aspects of 
//    the common implementation that are specific to a particular C++ API.
//  - The rtiddsgen-generated code. It provides a thin wrapper on top of
//    the generic implementation that is specific for each IDL type.
//
// This header customizes the following aspects of the generic (xcdr) code:
//   - Enable exceptions
//   - Provide equality operators between an Offset and dds::core::null
//   - Specialize templates so that the generic code can work with safe_enum
//   - Provides the function build_data(dds::pub::DataWriter).
//   - Provides the implementation of DataWriter Policies that customize how 
//     a DataWriter for a flat-data type writes, gets loaned samples, etc
//   - It provides generic implementations of some type traits used in the
//     xcdr code, such as the one that provides the type_code for a given type.
//     In traditional C++ this has to be done in generated code.
//
//

#ifndef RTI_DDS_TOPIC_FLATDATA_HPP_
#define RTI_DDS_TOPIC_FLATDATA_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#if !defined(RTI_NO_CXX11_SMART_PTR)
#include <memory>
#endif

#if defined(RTI_CXX11_RVALUE_REFERENCES) \
    && !defined(RTI_CXX11_NO_IMPLICIT_MOVE_OPERATIONS)
// Define C++11 move operations in Flat Data API if the platform has full
// support for rvalue references (VS2010-2013 do not define the implicit move
// constructor or assignment operators).
#define RTI_FLAT_DATA_CXX11_RVALUE_REFERENCES
#endif

#if !defined(RTI_NO_CXX11_DELETED_FUNCTIONS)
#define RTI_FLAT_DATA_CXX11_DELETED_FUNCTIONS
#endif

#include <rti/pub/flat/FlatDataWriter.hpp>
#include <rti/topic/to_string.hpp>

namespace rti { namespace flat {

// Provide sample creation as shared pointer:
#if !defined(RTI_NO_CXX11_SMART_PTR)
/*i
 * @brief @st_cpp11 Creates a FlatData sample managed by a \p std::shared_ptr
 * 
 * @tparam FlatType A @language_binding(FLAT_DATA)-annotated IDL type
 * @return A shared pointer that manages the destruction of this FlatData
 *  sample by calling FlatType::delete_data.
 */
template <typename FlatType>
std::shared_ptr<FlatType> create_shared_data()
{
    return std::shared_ptr<FlatType>(
            FlatType::create_data(),
            [](FlatType *sample) { FlatType::delete_data(sample); });
}
#endif

// Provide an operator<< for flat-data samples implemented via to_string()
template <typename OffsetType>
std::ostream& operator<<(std::ostream& out, const Sample<OffsetType>& sample)
{
    rti::topic::to_string(out, sample);
    return out;
}

// Provide dds::core::null comparison with offsets

inline bool operator==(const OffsetBase& offset, dds::core::null_type)
{
    return offset.is_null();
}

inline bool operator==(dds::core::null_type, const OffsetBase& offset)
{
    return offset.is_null();
}

inline bool operator!=(const OffsetBase& offset, dds::core::null_type)
{
    return !offset.is_null();
}

inline bool operator!=(dds::core::null_type, const OffsetBase& offset)
{
    return !offset.is_null();
}

} } // namespace rti::flat

#endif // RTI_DDS_TOPIC_FLATDATA_HPP_
