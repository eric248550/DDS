/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


============================================================================= */

#ifndef RTI_ROUTING_PROCESSOR_LOANED_SAMPLES_HPP_
#define RTI_ROUTING_PROCESSOR_LOANED_SAMPLES_HPP_

#ifdef RTI_CXX11_RVALUE_REFERENCES
#include <utility> // std::move
#endif

#include <iterator>

#include "routingservice/routingservice_adapter_new.h"
#include <rti/routing/processor/LoanedSample.hpp>
#include <rti/routing/adapter/StreamReader.hpp>
#include <rti/routing/processor/SampleIterator.hpp>

namespace rti { namespace routing { namespace processor {

template <typename T, typename U> class TypedInput;

namespace detail {

struct NativeSamples {

public:

    NativeSamples() : sample_array_(NULL), info_array_(NULL), length_(0)
    {
    }

    RTI_RoutingServiceSample *sample_array_;
    RTI_RoutingServiceSampleInfo *info_array_;
    int length_;
};

}

/** @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::LoanedSamples
 *
 * @brief Provides temporary access to a collection of samples (data and info)
 * from a TypedInput.
 *
 * @tparam T The sample data type representation. It has to match the type of
 *         the underlying rti::routing::adapter::StreamReader of the TypedInput.
 *
 * @tparam U The sample info type representation. It has to match the type of
 *         the underlying rti::routing::adapter::StreamReader of the TypedInput.
 *
 * This STL-like container encapsulates a collection of loaned, read-only data
 * samples rti::sub::LoanedSample::data() and
 * rti::sub::LoanedSample::info() from a TypedInput.
 *
 * To obtain a LoanedSamples, you need to call one of the read/take operations
 * from a TypedInput. The samples have to be eventually returned to the
 * TypedInput by calling rti::routing::adapter::StreamReader::return_loan on
 * the underlying rti::routing::adapter::StreamReader of the TypedInput. The
 * destructor takes care of that, and the return_loan() function lets you do
 * it explicitly if needed.
 *
 * As a move-only type, copying a LoanedSamples is not allowed. If you need
 * to return a LoanedSamples from a function or assign it to another variable,
 * use \p dds::core::move() (or \p std::move() for C++11).
 *
 * Iterators and overloaded subscript operators let you access the samples
 * in this container, which are of the type rti::routing::processor::LoanedSample.
 *
 * This code demonstrates how to access the info and data of each sample in
 * a DataReader:
 *
 * \code
 * auto samples = reader.take();
 * for (const auto& sample : samples) {
 *     if (sample.info().valid()) {
 *         std::cout << sample.data() << std::endl;
 *     }
 * }
 * \endcode
 *
 * @see dds::sub::LoanedSamples
 *
 */
template <typename T, typename U = dds::sub::SampleInfo>
class LoanedSamples {
public:

    typedef rti::routing::adapter::StreamReader StreamReader;
    typedef typename std::vector<StreamReader::SamplePtr> SampleSeqType;
    typedef typename std::vector<StreamReader::InfoPtr> InfoSeqType;

    /**
     * @brief The iterator type
     */
    typedef SampleIterator<T, U> iterator;
    typedef SampleIterator<T, U> const_iterator;
    typedef typename SampleIterator<T, U>::value_type value_type;
    typedef std::ptrdiff_t difference_type;

    /**
     * @brief Creates an empty LoanedSamples object.
     */
    LoanedSamples() : reader_(NULL), native_env_(NULL)
    {
    }

public:
    // Private c-tor only to be used by static method create_from_loans()
    LoanedSamples(
            RTI_RoutingServiceStreamReaderExt *native_reader,
            detail::NativeSamples& native_samples,
            RTI_RoutingServiceEnvironment *native_env)
        : reader_(native_reader),
          native_samples_(native_samples),
          native_env_(native_env)
    {
    }

public:

    /**
     * @brief Automatically returns the loan to the TypedInput used
     * to obtained these samples.
     *
     * @see return_loan
     */
    ~LoanedSamples() throw()
    {
        try {
            return_loan();
        } catch (const std::exception& ex) { // Do not throw in destructor

        }
    }


    /**
     * @brief Provides access to the underlying LoanedSample object in
     * array-like syntax.
     *
     * @param[in] index
     *            The index of the Sample. Allowed values are from 0 to length()-1.
     *
     * @return A LoanedSample object that refers to data and info
     *         at the specified \p index.
     */
    LoanedSample<T,U> operator [] (size_t index)
    {
       return LoanedSample<T,U>(
               native_samples_.sample_array_[index],
               native_samples_.info_array_[index]);
    }

   /**
     * @brief Gets the number of samples in this collection
     */
    int32_t length() const
    {
        return native_samples_.length_;
    }

    /**
     * @brief Returns the samples to the TypedInput used to get these
     * samples.
     *
     * Thes operation returns the samples by calling the
     * \link rti::routing::adapter::StreamReader::return_loan  return_loan\endlink
     * operation on the underlying rti::routing::stream::StreamReader of the
     * TypedInput.
     *
     * @note Explicitly calling return_loan is optional, since the
     * destructor does it implicitly.
     *
     * This operation tells the TypedInput that the application
     * is done accessing the collection of samples.
     *
     * It is not necessary for an application to return the loans immediately
     * after the call to read or take. However, as these buffers correspond to
     * internal resources, the application should not retain them indefinitely.
     *
     * @throw std::exception
     *        If there was an error returning the loan to the TypedInput.
     */
    void return_loan()
    {
        if (reader_) {
            reader_->return_loan(
                    reader_->stream_reader_data,
                    native_samples_.sample_array_,
                    native_samples_.info_array_,
                    native_samples_.length_,
                    native_env_);
            RTI_ROUTING_THROW_ON_ENV_ERROR(native_env_);
            reader_ = NULL; // Indicate that this object doesn't hold a loan anymore
        }
    }


    /**
     * @brief Gets an iterator to the first sample
     */
    iterator begin()
    {
        return iterator(
                native_samples_.sample_array_,
                native_samples_.info_array_,
                native_samples_.length_,
                0);
    }

    /**
     * @brief Gets an iterator to one past the last sample
     */
    iterator end()
    {
        return iterator(
                native_samples_.sample_array_,
                native_samples_.info_array_,
                native_samples_.length_,
                native_samples_.length_);
    }

    /**
     * @brief Gets an iterator to the first sample
     */
    const_iterator begin() const
    {
        return const_iterator(
                native_samples_.sample_array_,
                native_samples_.info_array_,
                0);
    }

    /**
     * @brief Gets an iterator to one past the last sample
     */
    const_iterator end() const
    {
        return const_iterator(
                native_samples_.sample_array_,
                native_samples_.info_array_,
                native_samples_.length_);
    }

    /**
     * @brief Swaps two LoanedSamples containers
     */
    void swap(LoanedSamples& other) throw()
    {
        std::swap(reader_, other.reader_);
        std::swap(native_samples_, other.native_samples_);
        std::swap(native_env_, other.native_env_);
    }

#if !defined(RTI_CXX11_RVALUE_REFERENCES)
    // Enables the safe-move-constructor idiom without C++11 move constructors
    struct MoveProxy {
        MoveProxy() : reader_(NULL)
        {
        }

        RTI_RoutingServiceStreamReaderExt *reader_;
        detail::NativeSamples native_samples_;
        RTI_RoutingServiceEnvironment *native_env_;
    };

    LoanedSamples(MoveProxy proxy) throw() // move constructor idiom
        : reader_(proxy.reader_),
          native_samples_(proxy.native_samples_),
          native_env_(proxy.native_env_)
    {
    }

    LoanedSamples& operator= (MoveProxy proxy) throw ()
    {
        // copy-and-swap idiom: copy new value, use temp's destructor to
        // clean up existing values
        LoanedSamples temp(proxy);
        temp.swap(*this);
        return *this;
    }

    operator MoveProxy () throw() // move-constructor idiom
    {
        MoveProxy proxy;

        // move data to the proxy and return *this to an 'emtpy' state
        std::swap(reader_, proxy.reader_);
        std::swap(native_samples_, proxy.native_samples_);
        std::swap(native_env_, proxy.native_env_);

        return proxy;
    }

private:
    // Direct assignment from one LoanedSamples to another is disabled.
    // Use the move function to assign one LoanedSamples to another.
    LoanedSamples(LoanedSamples &);
    LoanedSamples & operator = (LoanedSamples &);

#else


    LoanedSamples(LoanedSamples&& other)
        :reader_(NULL), native_env_(NULL)
    {
        other.swap(*this);
    }


    LoanedSamples& operator= (LoanedSamples&& other) throw ()
    {
        // clean up existing values
        LoanedSamples temp(std::move(other));
        temp.swap(*this);
        return *this;
    }

#endif // !defined(RTI_CXX11_RVALUE_REFERENCES)

private:
   friend class TypedInput<T, U>;

    void release()
    {
        reader_ = NULL;
    }

    detail::NativeSamples& native_samples()
    {
        return native_samples_;
    }

    bool has_infos()
    {
        return native_samples_.info_array_ != NULL;
    }

private:
    // reference to the reader that created this LoanedSamples object
    RTI_RoutingServiceStreamReaderExt *reader_;
    detail::NativeSamples native_samples_;
    RTI_RoutingServiceEnvironment *native_env_;

};

template <typename T, typename U>
LoanedSamples<T, U> move(LoanedSamples<T,U> & ls) OMG_NOEXCEPT
{
#if defined(RTI_CXX11_RVALUE_REFERENCES)
    return std::move(ls);
#else
    return LoanedSamples<T,U>(typename LoanedSamples<T,U>::MoveProxy(ls));
#endif
}


} } }

#endif // RTI_ROUTING_PROCESSOR_LOANED_SAMPLES_HPP_
