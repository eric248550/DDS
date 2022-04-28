/* $Id$

(c) Copyright, Real-Time Innovations, 2013-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,20mar13,acr Created
============================================================================= */

#ifndef RTI_DDS_SUB_LOANED_SAMPLES_IMPL_HPP_
#define RTI_DDS_SUB_LOANED_SAMPLES_IMPL_HPP_

#ifdef RTI_CXX11_RVALUE_REFERENCES
#include <utility> // std::move
#endif

#include <iterator>

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/sub/SampleIterator.hpp>
#include <dds/sub/Sample.hpp>
#include <rti/util/util.hpp>

/** @RTI_namespace_start dds::sub */
namespace rti { namespace sub {

/**
 * @ingroup DDSDataSampleModule
 * @brief @st_move_type Provides temporary access to a collection of samples (data and info) from a DataReader.
 *
 * @tparam T The topic-type. It has to match the type of the DataReader.
 *
 * This STL-like container encapsulates a collection of loaned, read-only data
 * samples (\link rti::sub::LoanedSample::data() data\endlink and \link rti::sub::LoanedSample::info() info\endlink)
 * from a DataReader.
 *
 * To obtain a LoanedSamples you need to call one of the read/take operations
 * from a DataReader. The samples have to be eventually returned to the DataReader. The
 * destructor takes care of that, and the return_loan() function lets you do
 * it explicitly if needed.
 *
 * As a move-only type copying a LoanedSamples is not allowed. If you want to have more than
 * one reference to a collection of loaned sample, see SharedSamples. If you need
 * to return a LoanedSamples from a function or assign it to another variable,
 * use \p dds::core::move() (or \p std::move() @st_cpp11).
 *
 * Iterators and overloaded subscript operators let you access the samples
 * in this container, which are of the type rti::sub::LoanedSample.
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
 *
 * @see @ref DDSReaderExampleModule_read_samples for more examples
 *
 */
template <typename T>
class LoanedSamples {
public:
   /**
    * @brief The iterator type
    */
   typedef SampleIterator<T> iterator;
   typedef SampleIterator<T> const_iterator;

   typedef typename SampleIterator<T>::value_type value_type;
   //typedef typename dds_type_traits<T>::ConstSampleIteratorValueType    const_value_type;
   typedef std::ptrdiff_t difference_type;

   typedef std::ostream_iterator<typename LoanedSamples<T>::value_type> ostream_iterator;

   // reference type (shared pointer) to DataReader<T>
   typedef typename dds::sub::DataReader<T>::DELEGATE_REF_T DataReaderRef;

public:

    /**
     * @brief Creates an empty LoanedSamples object.
     */
    LoanedSamples()
    {
    }

private:
    // Private c-tor only to be used by static method create_from_loans()
    LoanedSamples(
        DataReaderRef& reader,
        void ** data,
        DDS_SampleInfoSeq& info_seq)
        : reader_(reader),
          data_seq_(data, DDS_SampleInfoSeq_get_length(&info_seq))
    {
        info_seq_ = info_seq;
    }

public:
    /*
     * @brief Create a new LoanedSamples object by moving the ownership of the data sequence and
     *        the \idref_SampleInfo sequences.
     *
     * @pre   The \p data_seq and \p info_seq parameters must contained loaned sample from the same
     *        DataReader.
     *
     * @param reader     The DataReader from which the loan was taken.
     * @param data_seq   The \idref_FooSeq object containing the loaned samples.
     *                    After the call this sequence will be empty.
     * @param info_seq   The \idref_SampleInfoSeq object containing the loaned SampleInfo.
     *                   After this call the sequence will be empty.
     * @post The new LoanedSamples object will manage the ownership of the loans.
     *
     * @return void
     *
     * @see \idref_LoanedContainer
     */
    static LoanedSamples<T> create_from_loans(
        DataReaderRef reader,
        void ** data_seq,
        DDS_SampleInfoSeq& info_seq)
    {
        return LoanedSamples<T>(reader, data_seq, info_seq);
    }

    /**
     * @brief Automatically returns the loan to the DataReader
     * @see return_loan
     */
    ~LoanedSamples() throw()
    {
        try {
            return_loan();
        } catch (const dds::core::Error& ex) { // Do not throw in destructor
            DDSLog_exception(
                "~LoanedSamples", &RTI_LOG_ANY_FAILURE_s, ex.what());
        }
    }

    /**
     * @brief Provides access to the underlying LoanedSample object in array-like syntax.
     *
     * @param index The index of the Sample. Allowed values are from 0 to length()-1.
     *
     * @return A LoanedSample object that refers to data and SampleInfo
     *         at the specified \p index.
     */
    value_type operator [] (size_t index) {
       return value_type(
           &data_seq_[index],
           DDS_SampleInfoSeq_get_reference(
               &info_seq_, rti::util::cast_length(index)));
    }

    /**
     * @brief Gets the number of samples in this collection
     */
    unsigned int length() const {
        return static_cast<int>(data_seq_.length());
    }

    /**
     * @brief Returns the samples to the DataReader
     *
     * @note Explicitly calling return_loan is optional, since the
     * destructor does it implicitly.
     *
     * This operation tells the dds::sub::DataReader that the application
     * is done accessing the collection of samples.
     *
     * It is not necessary for an application to return the loans immediately
     * after the call to read or take. However, as these buffers correspond to
     * internal resources, the application should not retain them indefinitely.
     */
    void return_loan() {
        if (reader_) {
            reader_->return_loan_untyped(
                (void **) data_seq_.get_buffer(), info_seq_);
            reader_.reset(); // Indicate that this object doesn't hold a loan anymore
        }
    }

    /**
     * @brief Gets an iterator to the first sample
     */
    iterator begin()
    {
        return iterator(data_seq_, info_seq_, 0);
    }

    /**
     * @brief Gets an iterator to one past the last sample
     */
    iterator end()
    {
        return iterator(
            data_seq_, info_seq_, rti::util::cast_length(data_seq_.length()));
    }

    /**
     * @brief Gets an iterator to the first sample
     */
    const_iterator begin() const
    {
        return const_iterator(data_seq_, info_seq_, 0);
    }

    /**
     * @brief Gets an iterator to one past the last sample
     */
    const_iterator end() const
    {
        return const_iterator(data_seq_, info_seq_, data_seq_.length());
    }

    /**
     * @brief Swap two LoanedSamples containers
     */
    void swap(LoanedSamples& other) throw()
    {
        data_seq_.swap(other.data_seq_);
        // for the native DDS_SampleInfoSeq, use generic, shallow-copy std::swap
        std::swap(info_seq_, other.info_seq_);
        reader_.swap(other.reader_);
    }

#if !defined(RTI_CXX11_RVALUE_REFERENCES)

    // Enables the safe-move-constructor idiom without C++11 move constructors
    struct MoveConstructProxy {
        DataReaderRef reader_;
        rti::core::detail::ContiguousDataSequence<T> data_seq_;
        DDS_SampleInfoSeq info_seq_;
    };

    LoanedSamples(MoveConstructProxy proxy) throw() // move constructor idiom
        : reader_(proxy.reader_),
          data_seq_(proxy.data_seq_)
    {
        info_seq_ = proxy.info_seq_; // shallow copy is OK
    }

    LoanedSamples& operator= (MoveConstructProxy proxy) throw ()
    {
        // copy-and-swap idiom: copy new value, use temp's destructor to
        // clean up existing values
        LoanedSamples temp(proxy);
        temp.swap(*this);
        return *this;
    }

    operator MoveConstructProxy () throw() // move-constructor idiom
    {
        MoveConstructProxy proxy;

        // move data to the proxy and return *this to an 'emtpy' state
        proxy.reader_.swap(reader_);
        proxy.data_seq_.swap(data_seq_);
        std::swap(proxy.info_seq_, info_seq_);

        return proxy;
    }

private:
    // Direct assignment from one LoanedSamples to another is disabled.
    // Use the move function to assign one LoanedSamples to another.
    LoanedSamples(LoanedSamples &);
    LoanedSamples & operator = (LoanedSamples &);

#else

    /**
     * @brief @st_cpp11 Moves the loan from an existing LoanedSamples to a new one
     */
    // Move constructor
    // (defining move ctor disables default copy constructor automatically)
    LoanedSamples(LoanedSamples&& other)
    {
        other.swap(*this);
    }

    /**
     *
     */
    // Move assignment operator
    LoanedSamples& operator= (LoanedSamples&& other) throw ()
    {
        // copy-and-swap idiom: copy new value, use temp's destructor to
        // clean up existing values
        LoanedSamples temp(std::move(other));
        temp.swap(*this);
        return *this;
    }

#endif // !defined(RTI_CXX11_RVALUE_REFERENCES)


private:
    // reference to the reader that created this LoanedSamples object
    DataReaderRef reader_;
    rti::core::detail::ContiguousDataSequence<T> data_seq_;
    DDS_SampleInfoSeq info_seq_;
};

/**
 * @relatesalso LoanedSamples
 * @brief Creates a new LoanedSamples instance by moving the contents of an existing one.
 *
 * Note: in @st_cpp11 you can directly use \p std::move.
 *
 * The parameter object loses the ownership of the underlying samples and its state
 * is reset as if it was default initialized. This function must be used to move
 * any named LoanedSamples instance (lvalue) in and out of a function by-value.
 * Using this function is not necessary if the original LoanedSamples is an rvalue.
 * Moving is a very efficient operation and is guaranteed to not throw any exception.
 *
 * @param ls The LoanedSamples object that transfers its ownership of the contained
 *           samples into the returned object. After this call, \p ls is empty.
 *
 * @return A new LoanedSamples object, the new loan owner,
 *         with the same contents as \p ls had.
 *
 * @see LoanedSamples
 */
template <typename T>
LoanedSamples<T> move(LoanedSamples<T> & ls) OMG_NOEXCEPT
{
#if defined(RTI_CXX11_RVALUE_REFERENCES)
    return std::move(ls);
#else
    return LoanedSamples<T>(typename LoanedSamples<T>::MoveConstructProxy(ls));
#endif
}

/**
 * @relatesalso LoanedSamples
 * @see LoanedSamples::begin()
 */
template <typename T>
typename LoanedSamples<T>::iterator begin(LoanedSamples<T> & ls)
{
    return ls.begin();
}

/**
 * @relatesalso LoanedSamples
 * @see LoanedSamples::begin()
 */
template <typename T>
typename LoanedSamples<T>::const_iterator begin(const LoanedSamples<T> & ls)
{
    return ls.begin();
}

/**
 * @relatesalso LoanedSamples
 * @see LoanedSamples::end()
 */
template <typename T>
typename LoanedSamples<T>::iterator end(LoanedSamples<T> & ls)
{
    return ls.end();
}

/**
 * @relatesalso LoanedSamples
 * @see LoanedSamples::end()
 */
template <typename T>
typename LoanedSamples<T>::const_iterator end(const LoanedSamples<T> & ls)
{
    return ls.end();
}

/**
 * @relatesalso LoanedSamples
 * @see LoanedSamples::swap()
 */
template <typename T>
void swap(LoanedSamples<T> &ls1, LoanedSamples<T> &ls2) throw()
{
    ls1.swap(ls2);
}

} } // close and reopen namespace for documentation purposes

namespace rti { namespace sub {

/**
 * @ingroup DDSDataSampleModule
 * @brief @extension A functor that returns true when a sample has valid data.
 *
 * This functor is useful in algorithms that iterate on LoanedSamples. For example:
 *
 * \code
 * LoanedSamples<Foo> samples = reader.take();
 * std::cout << "Valid sample count: "
 *           << std::count_if(samples.begin(), samples.end(), IsValidData<Foo>());
 * \endcode
 *
 * A similar utility is the iterator valid_data().
 *
 * @see dds::sub::LoanedSamples
 * @see valid_data()
 */
template <typename T>
struct IsValidData {
public:
    /**
     * @brief LoanedSample type
     */
    typedef typename LoanedSamples<T>::value_type sample_type;

    /**
     * @brief Returns true if this sample contains valid data
     *
     * That is, if \p sample.info().valid().
     */
    bool operator () (const sample_type& sample)
    {
        return sample.info().valid();
    }

    bool operator () (const dds::sub::Sample<T>& sample)
    {
        return sample.info().valid();
    }
};

#if defined(RTI_CXX11_RVALUE_REFERENCES)

/**
 * @ingroup DDSDataSampleModule
 * @brief @extension @st_cpp11 @st_move_type Provides access to only those samples that contain valid data
 *
 * @tparam T The topic-type. It has to match the type of the DataReader.
 *
 * An instance of ValidLoanedSamples is a wrapper that takes an existing
 * LoanedSamples and provides forward iterators that only access samples with
 * valid data.
 *
 * The typical way to use this collection is through the function
 * rti::sub::valid_data, which transforms a dds::sub::LoanedSamples into
 * a ValidLoanedSamples.
 *
 * For more information and a code example, see
 * rti::sub::valid_data(LoanedSamples<T>&&)
 *
 * @see @ref DDSReaderExampleModule_read_samples
 */
template <typename T>
class ValidLoanedSamples {
public:
    /**
     * @brief The iterator type that ValidLoanedSamples provides
     */
    typedef ValidSampleIterator<T> iterator;

    /**
     * @brief The const-iterator type that ValidLoanedSamples provides
     */
    typedef ValidSampleIterator<T> const_iterator;

    /**
     * @brief This collection's value type, LoanedSample<T>
     */
    typedef typename ValidSampleIterator<T>::value_type value_type;

    /**
     * @brief Constructor from an rvalue LoanedSamples
     *
     * The only way to create a ValidLoanedSamples is through moving an existing
     * LoanedSamples.
     *
     * @post loaned_samples is invalid should not be used; this ValidLoanedSamples
     * now owns it.
     *
     * @note This constructor should not be used directly, the function
     * rti::sub::valid_data(LoanedSamples<T>&&) is more convenient since it
     * can deduce the template type.
     */
    ValidLoanedSamples(LoanedSamples<T>&& loaned_samples) :
        samples_(std::move(loaned_samples))
    {
    }

    /**
     * @brief Move constructor
     *
     * A ValidLoanedSamples, just like LoanedSamples can be moved but not copied.
     */
    ValidLoanedSamples(ValidLoanedSamples<T>&& other) :
            samples_(std::move(other.samples_))
    {
    }

    /**
     * @brief Returns a forward iterator to the first valid-data sample
     */
    iterator begin()
    {
        return valid_data(samples_.begin());
    }

    /**
     * @brief Returns a forward const iterator to the first valid-data sample
     */
    const_iterator begin() const
    {
        return valid_data(samples_.begin());
    }

    /**
     * @brief Returns a forward iterator that indicates the end of the collection
     */
    iterator end()
    {
        return valid_data(samples_.end());
    }

    /**
     * @brief Returns a forward const iterator that indicates the end of the collection
     */
    const_iterator end() const
    {
        return valid_data(samples_.end());
    }

private:
    LoanedSamples<T> samples_;
};

/**
 * @relatesalso ValidLoanedSamples
 * @see ValidLoanedSamples::begin()
 */
template <typename T>
typename ValidLoanedSamples<T>::iterator begin(ValidLoanedSamples<T> & ls)
{
    return ls.begin();
}

/**
 * @relatesalso ValidLoanedSamples
 * @see ValidLoanedSamples::begin()
 */
template <typename T>
typename ValidLoanedSamples<T>::const_iterator begin(const ValidLoanedSamples<T> & ls)
{
    return ls.begin();
}

/**
 * @relatesalso ValidLoanedSamples
 * @see ValidLoanedSamples::end()
 */
template <typename T>
typename ValidLoanedSamples<T>::iterator end(ValidLoanedSamples<T> & ls)
{
    return ls.end();
}

/**
 * @relatesalso ValidLoanedSamples
 * @see ValidLoanedSamples::end()
 */
template <typename T>
typename ValidLoanedSamples<T>::const_iterator end(const ValidLoanedSamples<T> & ls)
{
    return ls.end();
}

/**
 * @relatesalso ValidLoanedSamples
 * @see ValidLoanedSamples::swap()
 */
template <typename T>
void swap(ValidLoanedSamples<T> &ls1, ValidLoanedSamples<T> &ls2) throw()
{
    ls1.swap(ls2);
}

/**
 * @relatesalso dds::sub::LoanedSamples
 * @brief @st_cpp11 @extension Returns a collection that provides access only
 * to samples with valid data
 *
 * @tparam T The topic-type. It has to match the type of the DataReader.
 *
 * This function transforms a LoanedSamples collection into another collection
 * whose iterators only access valid-data samples, skipping any
 * sample such that !sample.info().valid().
 *
 * This operation is O(1) and will not copy the data samples or allocated
 * any additional memory.
 *
 * The typical way to use this function is to directly call it on the return
 * value of a read()/take() operation and use it in a for-loop. For example:
 *
 * \code
 * auto valid_samples = rti::sub::valid_data(reader.read());
 * for (const auto& sample : valid_samples) {
 *     // no need to check sample.info().valid()
 *     std::cout << sample.data() << std::endl;
 * }
 * \endcode
 *
 * @param samples The collection of LoanedSamples to transform into a
 *   ValidLoanedSamples. It must be an rvalue, so valid actual parameters are
 *   the result of one of the read/take operations:
 *   \code
 *   auto vs = rti::sub::valid_data(reader.take());
 *   \endcode
 *   Or an \p std::move'd existing collection:
 *   \code
 *   auto ls = reader.take();
 *   auto vs = rti::sub::valid_data(std::move(ls));
 *   // 'ls' is now invalid and can't be further used
 *   \endcode
 *
 * @return A forward-iterable collection that provides access only to
 *   samples with valid data. Note that this collection doesn't provide random
 *   access.
 *
 * @post \p samples is invalid cannot be used after this call
 *
 * @see rti::sub::valid_data(const SampleIterator<T>&), which applies to an
 *   iterator rather to the whole collection
 * @see @ref DDSReaderExampleModule_read_samples
 *
 */
template <typename T>
ValidLoanedSamples<T> valid_data(LoanedSamples<T>&& samples)
{
    return ValidLoanedSamples<T>(std::move(samples));
}

#endif // defined(RTI_CXX11_RVALUE_REFERENCES)

} } // namespace rti::sub

#endif // RTI_DDS_SUB_LOANED_SAMPLES_IMPL_HPP_
