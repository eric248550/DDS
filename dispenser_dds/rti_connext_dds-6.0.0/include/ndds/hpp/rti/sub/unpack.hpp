/* $Id$

(c) Copyright, Real-Time Innovations, 2018.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.

============================================================================= */

#ifndef RTI_DDS_SUB_UNPACK_HPP_
#define RTI_DDS_SUB_UNPACK_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <dds/sub/SharedSamples.hpp>
#include <vector>

#ifndef RTI_NO_CXX11_SMART_PTR
namespace rti { namespace sub {
namespace detail {

// Custom deleter for the shared_ptr's returned by unpack()
//
// This deleter doesn't actually delete anything, it just keeps
// a reference to the common SharedSamples so that when all the samples
// that belong in that collection go out, the loan is returned.
template <typename T>
struct SharedSampleDeleter {
    SharedSampleDeleter(const dds::sub::SharedSamples<T>& samples) : samples_(samples)
    {
    }

    void operator()(const T*) const
    {
        // nothing to delete
    }

    const dds::sub::SharedSamples<T> samples_; // This reference retains the loan
};

} // namespace detail

/**
 * @relatesalso dds::sub::SharedSamples
 * @note \p \#include \p \<rti/sub/unpack.hpp\>
 *
 * @brief @extension @st_cpp11 Unpacks a SharedSamples collection into individual
 * shared_ptr's in a vector
 *
 * This function creates a reference (not a copy) to each sample with valid
 * data in a SharedSamples container and pushes it back into a vector.
 *
 * Each individual sample in the vector retains a reference
 * to the original SharedSamples that controls when the loan is returned. These
 * references can be further shared. When all the references go out of scope, the
 * loan is returned.
 *
 * This can be also useful to insert samples from different calls to read()/take()
 * into the same vector. It is however recommended to not hold these samples
 * indefinitely, since they use internal resources.
 *
 *
 * Example:
 *
 * \code
 * dds::sub::SharedSamples<Foo> shared_samples = reader.take();
 * std::vector<std::shared_ptr<const Foo>> sample_vector;
 * rti::sub::unpack(shared_samples, sample_vector);
 *
 * std::cout << *sample_vector[0] << std::endl;
 *
 * // ...
 *
 * // Read more samples, unpack them at the end of the same vector
 * shared_samples = reader.take();
 * rti::sub::unpack(shared_samples, sample_vector);
 *
 * // References to the samples can be shared freely
 * std::shared_ptr<const Foo> sample = sample_vector[3];
 *
 * // ...
 *
 * // The loans will be returned automatically
 * \endcode
 *
 * @note To finalize a DataReader, all the shared_ptr obtained via unpack()
 * need to have been released. Otherwise DataReader::close() will fail with
 * dds::core::PreconditionNotMetError.
 *
 * @tparam T The topic-type
 * @param samples The collection of samples obtained from the DataReader
 * @param sample_vector The destination where the samples are pushed back.
 */
template <typename T>
void unpack(
        const dds::sub::SharedSamples<T>& samples,
        std::vector<std::shared_ptr<const T> >& sample_vector)
{
    detail::SharedSampleDeleter<T> shared_deleter(samples);
    for (auto& sample : samples) {
        if (sample.info().valid()) {
            sample_vector.push_back(std::shared_ptr<const T>(
                    &sample.data(),
                    shared_deleter));
        }
    }
}

/**
 * @relatesalso dds::sub::SharedSamples
 *
 * @brief @extension @st_cpp11 Unpacks a SharedSamples collection into individual
 * shared_ptr's in a vector
 *
 * This overload returns a new vector instead of adding into an existing one.
 *
 * @see unpack(const dds::sub::SharedSamples<T>&, std::vector<std::shared_ptr<const T> >&)
 */
template <typename T>
std::vector<std::shared_ptr<const T> > unpack(
        const dds::sub::SharedSamples<T>& samples)
{
    std::vector<std::shared_ptr<const T> > sample_vector;
    sample_vector.reserve(samples.length());
    unpack(samples, sample_vector);
    return sample_vector;
}

/**
 * @relatesalso dds::sub::SharedSamples
 * @headerfile dds/sub/SharedSamples.hpp
 *
 * @brief @extension @st_cpp11 Unpacks a LoanedSamples collection into individual
 * shared_ptr's in a vector
 *
 * This overload is a shortcut for \p unpack(SharedSamples<T>(loaned_samples)) to
 * simplify code like the following:
 *
 * \code
 * auto sample_vector = unpack(reader.take());
 * \endcode
 *
 * @see unpack(const dds::sub::SharedSamples<T>&, std::vector<std::shared_ptr<const T> >&)
 */
#ifdef RTI_CXX11_RVALUE_REFERENCES
template <typename T>
std::vector<std::shared_ptr<const T> > unpack(
        dds::sub::LoanedSamples<T>&& samples)
{
    return unpack(dds::sub::SharedSamples<T>(std::move(samples)));
}
#endif

} }
#endif

#endif // RTI_DDS_SUB_UNPACK_HPP_
