/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_REQUEST_VERSION_HPP_
#define RTI_REQUEST_VERSION_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <rti/request/detail/macros.hpp>

#include <rti/core/ProductVersion.hpp>

namespace rti { namespace config {

/**
 * @ingroup NDDSConfigModule
 * @brief Get the version of the C++ API library.
 */
XMQCPP2DllExport
rti::core::ProductVersion request_reply_api_version();

/**
 * @ingroup NDDSConfigModule
 * @brief Get the build number of the C++ API library.
 */
XMQCPP2DllExport
std::string request_reply_build_number();

} } // namespace rti::request::config

#endif // RTI_CONFIG_VERSION_HPP_
