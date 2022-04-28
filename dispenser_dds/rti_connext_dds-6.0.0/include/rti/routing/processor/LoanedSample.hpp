/* $Id$

(c) Copyright, Real-Time Innovations, 2015-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


============================================================================= */

#ifndef RTI_ROUTING_PROCESSOR_LOANED_SAMPLE_HPP_
#define RTI_ROUTING_PROCESSOR_LOANED_SAMPLE_HPP_

#include <exception>

namespace rti { namespace routing { namespace processor {

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::LoanedSample
 *
 * @brief
 */
template <typename T, typename U>
class LoanedSample
{
public:
    /**
     * @brief The data type
     */
    typedef T DataType;
    /**
     * @brief The info type
     */
    typedef U InfoType;

    LoanedSample()
        : _data_ptr(NULL),
          _info_ptr(NULL)
    {}

    LoanedSample(const DataType * the_data, const InfoType * the_info)
        : _data_ptr(the_data),
          _info_ptr(the_info)
    {}
        

    LoanedSample(const DataType & the_data, const InfoType & the_info)
        : _data_ptr(&the_data),
          _info_ptr(&the_info)
    {}

    LoanedSample(const void * the_data, const void * the_info)
        : _data_ptr(static_cast<const T*>(the_data)),
          _info_ptr(static_cast<const U*>(the_info))
    {}

   
    const DataType & data() const
    {
        if (!info().valid()) {
            throw dds::core::PreconditionNotMetError("Invalid data");
        }

        return *_data_ptr;
    }

    /**
     * @brief Gets the sample info
     */
    const InfoType & info() const {
        return *_info_ptr;
    }

   
    operator const DataType & () const
    {
        return data();
    }

    LoanedSample<DataType, InfoType> * operator ->() {
        return this;
    }

    const LoanedSample<DataType, InfoType> * operator ->() const {
        return this;
    }

    /**
     * @brief Compares the data and info
     */
    bool operator==(const LoanedSample& other) const
    {
        if (info() != other.info()) {
            return false;
        }

        if (info().valid()) {
            if (data() != other.data()) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const LoanedSample& other) const
    {
        return !(*this == other);
    }

    void swap(LoanedSample & other) throw()
    {
        using std::swap;

        swap(_data_ptr, other._data_ptr);
        swap(_info_ptr, other._info_ptr);
    }

private:
    const DataType * _data_ptr;
    const InfoType * _info_ptr;
};

} } }

#endif // RTI_ROUTING_PROCESSOR_LOANED_SAMPLE_HPP_
