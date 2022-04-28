/* $Id$

(c) Copyright, Real-Time Innovations, 2014-2016.
All rights reserved.

No duplications, whole or partial, manual or electronic, may be made
without express written permission.  Any such copies, or
revisions thereof, must display this notice unaltered.
This code contains trade secrets of Real-Time Innovations, Inc.


modification history
--------------------
1.0a,05may14,acr Added ValidSampleIterator and valid_samples helper
1.0a,20mar13,acr Created
============================================================================= */

#ifndef RTI_ROUTING_PROCESSOR_SAMPLE_ITERATOR_HPP_
#define RTI_ROUTING_PROCESSOR_SAMPLE_ITERATOR_HPP_


#include <rti/routing/processor/LoanedSample.hpp>


namespace rti { namespace routing { namespace processor {

/**
 * @ingroup RTI_RoutingServiceProcessorModule
 *
 * @class rti::routing::processor::SampleIterator
 * @brief A random-access iterator of LoanedSample
 *
 * @see rti::routing::processor::LoanedSamples
 */
template <typename T, typename U>
class SampleIterator {
public:
   // iterator traits
   typedef std::random_access_iterator_tag iterator_category;
   typedef const LoanedSample<T,U> value_type;
   typedef value_type reference;
   typedef value_type pointer;
   typedef std::ptrdiff_t difference_type;
   typedef RTI_RoutingServiceSample* SampleSeqType;
   typedef RTI_RoutingServiceSampleInfo* InfoSeqType;

   SampleIterator()
     : _sample_seq(0),
       _info_seq(0),
       _length(0),
       _pos(0)
   {}

   explicit SampleIterator(
       const SampleSeqType sample_seq,
       const InfoSeqType info_seq,
       int length,
       int position = 0)
     : _sample_seq(sample_seq),
       _info_seq(info_seq),
       _length(length),
       _pos(position)
   {}

   SampleIterator (const SampleIterator<T,U> & other)
     : _sample_seq(other._sample_seq),
       _info_seq(other._info_seq),
       _length(other._length),
       _pos(other._pos)
   {}

   SampleIterator & operator = (const SampleIterator<T,U> & other)
    {
        _sample_seq = other._sample_seq;
        _info_seq = other._info_seq;
        _length = other._length;
        _pos = other._pos;

        return *this;
    }   

   value_type operator * () const {
     return value_type(_sample_seq[_pos], _info_seq[_pos]);
   }

   value_type operator ->() const {
     return value_type(_sample_seq[_pos], _info_seq[_pos]);
   }

   value_type operator [] (difference_type offset) const {
       return value_type(_sample_seq[_pos + offset], _info_seq[_pos + offset]);
   }

   SampleIterator & operator ++ () {
     ++_pos;
     return *this;
   }

   SampleIterator operator ++ (int) {
     SampleIterator temp(*this);
     ++(*this);
     return temp;
   }

   SampleIterator & operator -- () {
     --_pos;
     return *this;
   }

   SampleIterator operator -- (int) {
     SampleIterator temp(*this);
     --(*this);
     return temp;
   }

   SampleIterator & operator -= (difference_type i) {
     _pos -= i;
     return *this;
   }

   SampleIterator & operator += (difference_type i) {
     _pos += i;
     return *this;
   }

   friend SampleIterator operator - (const SampleIterator & si,
                                     difference_type i) {
     return SampleIterator(si._sample_seq, si._info_seq, si._pos - i);
   }

   friend SampleIterator operator + (const SampleIterator & si,
                                     difference_type i) {
     return SampleIterator(si._sample_seq, si._info_seq, si._pos + i);
   }

   friend difference_type operator - (const SampleIterator & s1,
                                      const SampleIterator & s2) {
     return s1._pos - s2._pos;
   }

   friend bool operator < (const SampleIterator & s1,
                           const SampleIterator & s2) {
     return s1._pos < s2._pos;
   }

   friend bool operator > (const SampleIterator & s1,
                           const SampleIterator & s2) {
     return s1._pos > s2._pos;
   }

   friend bool operator <= (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return s1._pos <= s2._pos;
   }

   friend bool operator >= (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return s1._pos >= s2._pos;
   }

   friend bool operator == (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return (s1._sample_seq == s2._sample_seq) && (s1._pos == s2._pos);
   }

   friend bool operator != (const SampleIterator & s1,
                            const SampleIterator & s2) {
     return !(s1 == s2);
   }

   bool is_end() const {
       return (_length == _pos);
   }

   // Keep these members public otherwise some of the
   // converting constructors will not compile.
public:
   SampleSeqType _sample_seq;
   InfoSeqType _info_seq;
   int _length;
   int _pos;
};


} } } 

#endif // RTI_ROUTING_PROCESSOR_SAMPLE_ITERATOR_HPP_
