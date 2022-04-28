#ifndef OMG_DDS_SUB_TSAMPLE_HPP_
#define OMG_DDS_SUB_TSAMPLE_HPP_

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

#include <dds/core/Value.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/sub/LoanedSample.hpp>

namespace dds { namespace sub {

/** 
 * @ingroup DDSDataSampleModule
 * @RTI_class_definition template<typename T> class Sample 
 * @headerfile Sample.hpp "dds/sub/Sample.hpp"
 *  
 * @brief @st_value_type This class encapsulate the data and meta-data 
 * associated with DDS samples. 
 *  
 * @tparam The type of the data that Sample represents
 */
template<typename T, template<typename Q> class DELEGATE>
class Sample : public dds::core::Value<DELEGATE<T> > {
public:
    typedef T DataType;

    /**
     * @brief Create a sample
     *
     * @post The value of data() is default-constructed, and info().valid() is false.
     */
    Sample() : dds::core::Value< DELEGATE<T> >()
    {
    }

    /**
     * @brief Create a Sample with the provided data and SampleInfo
     * 
     * @param the_data The data to create the Sample with
     * @param the_info The SampleInfo to create the Sample with
     */
    Sample(const T& the_data, const SampleInfo& the_info)
        : dds::core::Value<DELEGATE<T> >(the_data, the_info)
    {
    }

    /**
     * @brief @extension Construct a Sample from a LoanedSample
     *
     * If \p loaned_sample.info().valid() is false, this sample's data value
     * is default-constructed.
     */
    explicit Sample(const rti::sub::LoanedSample<T>& loaned_sample)
        : dds::core::Value<DELEGATE<T> >(loaned_sample)
    {
    }

    /**
     * @brief Copy Constructor
     */
    Sample(const Sample& other)  : dds::core::Value< DELEGATE<T> >(other)
    {
    }

    /**
     * @brief Get the data of type T associated with this Sample
     *
     * This function returns the current value of the data even if info().valid()
     * is false.
     *
     */
    const DataType& data() const
    {
        return this->delegate().data();
    }

    /**
     * @brief Set the data of type T associated with this Sample
     */
    void data(const DataType& the_data)
    {
        this->delegate().data(the_data);
    }

    /**
     * @brief Get the SampleInfo associated with this Sample
     */
    const SampleInfo& info() const
    {
        return this->delegate().info();
    }

    /**
     * @brief Set the SampleInfo associated with this Sample
     */
    void info(const SampleInfo& the_info)
    {
        this->delegate().info(the_info);
    }

    /**
     * @brief @extension Assignment operator from an rti::sub::LoanedSample
     *
     * This operator allows obtaining a copy of both the data and the info from
     * a LoanedSample.
     *
     * @post If \p loaned_sample.info().valid() is false, this sample's data() value
     * is not modified, but info().valid() is false.
     *
     */
    Sample& operator =(const rti::sub::LoanedSample<T>& loaned_sample)
    {
        // Call the delegate's operator =
        this->delegate() = loaned_sample;
        return *this;
    }
};

} } // namespace dds::sub

#endif /* OMG_DDS_SUB_TSAMPLE_HPP_ */
