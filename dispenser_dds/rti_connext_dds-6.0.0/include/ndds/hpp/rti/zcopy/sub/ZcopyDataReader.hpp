/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/
#ifndef RTI_ZCOPY_SUB_ZEROCOPYDATAREADER_HPP_
#define RTI_ZCOPY_SUB_ZEROCOPYDATAREADER_HPP_

#include <rti/zcopy/topic/ZcopyTraits.hpp>
#include <dds/sub/DataReader.hpp>
#include "metp/metp_dds.h"

namespace rti { namespace sub {

template <typename T>
class NativeDataConsistencyPolicy<T,
        typename rtiboost::enable_if_c<
                rti::zcopy::topic::is_zcopy_type<T>::value>::type> {
public:
    static bool is_data_consistent(
            DDS_DataReader *self,
            const T* data,
            const DDS_SampleInfo *sample_info)
    {
        DDS_Boolean result = DDS_BOOLEAN_FALSE;
        DDS_ReturnCode_t retcode = DDS_DataReader_is_metp_data_consistent(
                self,
                &result,
                data,
                sample_info);
        rti::core::check_return_code(retcode, "is data consistent");
        return result == DDS_BOOLEAN_TRUE;
    }
};

} } // namespace rti::sub

#endif /* RTI_ZCOPY_SUB_ZEROCOPYDATAREADER_HPP_ */
