#ifndef RTI_DDS_CORE_THREAD_HPP_
#define RTI_DDS_CORE_THREAD_HPP_

/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/


// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "dds_c/dds_c_domain.h"

namespace rti { namespace core {

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile rti/core/thread.hpp
 * @brief @extension Releases resources that \ndds keeps for this thread
 *
 * @details \dref_details_DomainParticipantFactory_unregister_thread
 *
 * @see UnregisterThreadOnExit
 */
OMG_DDS_API
void unregister_thread();

/**
 * @ingroup DDSCPP2SupportingTypes
 * @headerfile rti/core/thread.hpp
 * @brief @extension Utility that calls rti::core::unregister_thread when leaving scope
 *
 * Declare an instance of this type in a thread function before any DDS
 * API is called. After the function exits, this variable will be destroyed and
 * the thread unregistered after everything else.
 *
 * For example:
 *
 * \code
 * void my_thread()
 * {
 *     // Whenever my_thread leaves, rti::core::unregister_thread will be called.
 *     UnregisterThreadOnExit unregister_thread_on_exit;
 *
 *     // Use DDS API
 * }
 * \endcode
 */
class UnregisterThreadOnExit {
public:
    UnregisterThreadOnExit()
    {
    }

    /**
     * @brief Calls rti::core::unregister_thread
     */
    ~UnregisterThreadOnExit()
    {
        try {
            unregister_thread();
        } catch (...) { // Don't let exception leave destructor
            std::cout << "~UnregisterThreadOnExit(): failed to unregister thread"
                      << std::endl;
        }
    }

private:
    UnregisterThreadOnExit(const UnregisterThreadOnExit&); // = delete
    UnregisterThreadOnExit& operator=(const UnregisterThreadOnExit&); // = delete
};

} } // namespace rti::core

#endif // RTI_DDS_CORE_THREAD_HPP_
