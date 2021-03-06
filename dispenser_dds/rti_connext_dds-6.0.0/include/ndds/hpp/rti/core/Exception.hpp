/* $Id$
 (c) Copyright, Real-Time Innovations, 2013-2016.
 All rights reserved.

 No duplications, whole or partial, manual or electronic, may be made
 without express written permission.  Any such copies, or
 revisions thereof, must display this notice unaltered.
 This code contains trade secrets of Real-Time Innovations, Inc.

modification history
--------------------
1.0,18feb13,acr Created
============================================================================= */

#ifndef RTI_DDS_CORE_EXCEPTION_HPP_
#define RTI_DDS_CORE_EXCEPTION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_infrastructure.h"

#include <dds/core/Exception.hpp>

#define RTI_STRINGIFY(x) #x
#define RTI_TOSTRING(x) RTI_STRINGIFY(x)

// Debug assertions
#ifdef NDEBUG
#define RTI_CHECK_PRECONDITION(EXPRESSION)
#else
#define RTI_CHECK_PRECONDITION(EXPRESSION)                       \
    if(!(EXPRESSION)) {                                          \
        throw dds::core::PreconditionNotMetError(                \
            __FILE__ ":" RTI_TOSTRING(__LINE__)      \
            ": precondition failed: " #EXPRESSION);              \
    }
#endif

namespace rti { namespace core {

namespace detail {

void OMG_DDS_API throw_return_code_ex(
        DDS_ReturnCode_t retcode, 
        const char * message);
void OMG_DDS_API throw_get_entity_ex(const char * entity_name);
void OMG_DDS_API throw_create_entity_ex(const char * entity_name);
void OMG_DDS_API throw_tc_ex(DDS_ExceptionCode_t ex, const char * message);

}

inline void check_return_code(DDS_ReturnCode_t retcode, const char * message)
{
    if (retcode == DDS_RETCODE_OK || retcode == DDS_RETCODE_NO_DATA) {
        return; // No exception
    }

    detail::throw_return_code_ex(retcode, message);
}

inline void check_return_code(
        DDS_ReturnCode_t retcode, 
        const std::string& message)
{
    check_return_code(retcode, message.c_str());
}

inline void check_get_entity(const void * ptr, const char * entity_name)
{
    if (ptr != NULL) {
        return; // No exception
    }

    detail::throw_get_entity_ex(entity_name);
}


inline void check_create_entity(const void * ptr, const char * entity_name)
{
    if (ptr != NULL) {
        return; // No exception
    }

    detail::throw_create_entity_ex(entity_name);
}

inline void check_tc_ex_code(DDS_ExceptionCode_t ex, const char * message)
{
    if (ex == DDS_NO_EXCEPTION_CODE) {
        return; // No exception
    }

    detail::throw_tc_ex(ex, message);
}


template <class T>
void check_not_closed(const T& entity, const char * entity_name)
{
    if (entity.closed()) {
        throw dds::core::AlreadyClosedError(entity_name);
    }
}

}} // namespace rti::core

#endif // RTI_DDS_CORE_EXCEPTION_HPP_
