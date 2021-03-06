#ifndef RTI_DDS_CORE_PACKAGE_INCLUDE_HPP_
#define RTI_DDS_CORE_PACKAGE_INCLUDE_HPP_

/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/core/ddscore.hpp>

#include <rti/core/EntityLock.hpp>
#include <rti/core/ListenerBinder.hpp>
#include <rti/core/thread.hpp>

// using namespace rti::core::all will include all core sub-namespaces
namespace rti {

/**
 * @brief @extension Extensions to dds::core
 */
namespace core {

/**
 * @brief @extension Extensions to dds::core::xtypes
 */
namespace xtypes {}

namespace all {

using namespace dds::core::all;

using namespace rti::core;
using namespace rti::core::policy;
using namespace rti::core::cond;
using namespace rti::core::status;
using namespace rti::core::xtypes;

} // namespace all

} // namespace core

} // namespace rti

#endif // RTI_DDS_CORE_PACKAGE_INCLUDE_HPP_
