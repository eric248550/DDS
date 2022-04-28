/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef RTI_DDS_ZCOPY_PACKAGE_INCLUDE_HPP_
#define RTI_DDS_ZCOPY_PACKAGE_INCLUDE_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include "metp/metp_dds.h"
#include "metp/metp_type_plugin.h"

#include <dds/pub/ddspub.hpp>
#include <dds/core/types.hpp>

#include "topic/ZcopyTraits.hpp"
#include "pub/ZcopyDataWriter.hpp"
#include "sub/ZcopyDataReader.hpp"

#endif // RTI_DDS_ZCOPY_PACKAGE_INCLUDE_HPP_
