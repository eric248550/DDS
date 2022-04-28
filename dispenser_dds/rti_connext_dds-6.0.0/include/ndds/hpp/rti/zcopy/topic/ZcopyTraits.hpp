/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_ZCOPY_TOPIC_ZEROCOPYTRAITS_HPP_
#define RTI_ZCOPY_TOPIC_ZEROCOPYTRAITS_HPP_

#include <dds/core/macros.hpp>
#include <dds/core/types.hpp>

// is_zcopy_type is set to true if the type is a zero copy type, with or without
// flat_data support
namespace rti { namespace zcopy { namespace topic {
template <typename T>
    struct is_zcopy_type  : public dds::core::false_type {};
} } }

// is_zcopy_type_only is set to true if the type is a zero copy type without
// flat_data support
namespace rti { namespace zcopy { namespace topic {
template <typename T>
    struct is_zcopy_type_only  : public dds::core::false_type {};
} } }

// is_zcopy_and_flat_data_type is set to true if the type is a zero copy type
// with flat_data support
namespace rti { namespace zcopy { namespace topic {
template <typename T>
    struct is_zcopy_and_flat_data_type  : public dds::core::false_type {};
} } }

#endif /* RTI_ZCOPY_TOPIC_ZEROCOPYTRAITS_HPP_ */
