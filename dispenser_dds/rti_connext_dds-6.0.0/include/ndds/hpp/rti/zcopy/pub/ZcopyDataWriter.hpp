/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.
*/
#ifndef RTI_ZCOPY_PUB_ZEROCOPYDATAWRITER_HPP_
#define RTI_ZCOPY_PUB_ZEROCOPYDATAWRITER_HPP_

#include <rti/topic/flat/FlatDataTraits.hpp>
#include <rti/zcopy/topic/ZcopyTraits.hpp>
#include "metp/metp_dds.h"

namespace rti { namespace pub {

template <typename T>
struct NativeWritePolicy<T,
        typename rtiboost::enable_if_c<rti::zcopy::topic::is_zcopy_type<T>::value>::type> {
public:
    static DDS_ReturnCode_t write(
            DDS_DataWriter *self,
            const T *instance_data,
            const DDS_InstanceHandle_t *handle)
    {
        DDS_WriteParams_t w_params = DDS_WRITEPARAMS_DEFAULT;
        return DDS_DataWriter_write_metp_data(
                self,
                instance_data,
                handle,
                &w_params);
    }

    static DDS_ReturnCode_t write(
            DDS_DataWriter *self,
            const T *instance_data,
            const DDS_InstanceHandle_t *handle,
            const DDS_Time_t *source_timestamp)
    {
        DDS_WriteParams_t w_params = DDS_WRITEPARAMS_DEFAULT;
        w_params.source_timestamp.sec = source_timestamp->sec;
        w_params.source_timestamp.nanosec = source_timestamp->nanosec;
        return DDS_DataWriter_write_metp_data(
                self,
                instance_data,
                handle,
                &w_params);
    }

    static DDS_ReturnCode_t write(
            DDS_DataWriter *self,
            const T *instance_data,
            DDS_WriteParams_t *params)
    {
        DDS_Cookie_t default_cookie = DDS_COOKIE_DEFAULT;
        if (!DDS_Cookie_equals(&params->cookie, &default_cookie)) {
            return DDS_RETCODE_ILLEGAL_OPERATION;
        }
        return DDS_DataWriter_write_metp_data(
                self,
                instance_data,
                &params->handle,
                params);
    }
};

template <typename T>
struct NativeGetLoanPolicy<T,
        typename rtiboost::enable_if_c<rti::zcopy::topic::is_zcopy_type_only<T>::value>::type> {
public:
    static T* get_loan(DDS_DataWriter *self)
    {
        DDS_Boolean initialize_data = RTI_FALSE;
        DDS_ReturnCode_t retcode;
        T* sample;
        retcode = DDS_DataWriter_create_metp_data(
                self,
                reinterpret_cast<void **>(&sample),
                &initialize_data);
        rti::core::check_return_code(retcode, "get loan");

        if (initialize_data) {
            new (sample) T();
        }
        return sample;
    }
};

template <typename T>
struct NativeGetLoanPolicy<T,
        typename rtiboost::enable_if_c<rti::zcopy::topic::is_zcopy_and_flat_data_type<T>::value>::type> {
public:
    static T* get_loan(DDS_DataWriter *self)
    {
        DDS_ReturnCode_t retcode;
        T* sample;
        retcode = DDS_DataWriter_create_metp_data(
                self,
                reinterpret_cast<void **>(&sample),
                NULL);
        rti::core::check_return_code(retcode, "get loan");

        RTIXCdrInterpreterPrograms *programs
                = rti::xcdr::type_programs<T>::get();

        retcode = detail::initialize_flat_loan_untyped(
                self,
                reinterpret_cast<char **>(&sample),
                programs,
                rti::flat::is_fixed_size_type<T>::value ? true : false);
        if (retcode != DDS_RETCODE_OK) {
            DDS_DataWriter_delete_metp_data(self, sample);
        }
        rti::core::check_return_code(retcode, "initialize loaned sample");

        return sample;
    }
};

template <typename T>
struct NativeDiscardLoanPolicy<T,
        typename rtiboost::enable_if_c<rti::zcopy::topic::is_zcopy_type<T>::value>::type> {
public:
    static void discard_loan(DDS_DataWriter *self, T *sample)
    {
        DDS_ReturnCode_t retcode = DDS_DataWriter_delete_metp_data(
                self, static_cast<void*>(sample));
        rti::core::check_return_code(retcode, "discard loan");
    }
};

} } // namespace rti::pub

#endif /* RTI_ZCOPY_PUB_ZEROCOPYDATAWRITER_HPP_ */
