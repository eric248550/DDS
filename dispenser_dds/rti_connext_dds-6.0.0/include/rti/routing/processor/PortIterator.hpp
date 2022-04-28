/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_PROCESSOR_PORTS_ITERATOR_HPP_
#define RTI_ROUTING_PROCESSOR_PORTS_ITERATOR_HPP_

#include <dds/core/Value.hpp>
#include <dds/core/SafeEnumeration.hpp>
#include <rti/core/NativeValueType.hpp>


#include <dds/core/xtypes/DynamicData.hpp>
#include <dds/sub/SampleInfo.hpp>
#include <rti/routing/processor/Input.hpp>
#include <rti/routing/processor/Output.hpp>

namespace rti { namespace routing { namespace processor {

template <typename PORT, typename DataRep, typename InfoRep> struct TypedPortType;

template <typename DataRep, typename InfoRep>
struct TypedPortType<Input, DataRep, InfoRep>
{
    typedef TypedInput<DataRep, InfoRep> type;
    typedef RTI_RoutingServiceStreamReaderExt native_type;

    static native_type * begin(RTI_RoutingServiceRoute *native_route)
    {
        return  RTI_RoutingServiceRoute_get_first_input(native_route);
    }

    static native_type * next(
            RTI_RoutingServiceRoute *native_route,
            native_type *native)
    {
        return  RTI_RoutingServiceRoute_get_next_input(native_route, native);
    }

    static Input* from_native(
            RTI_RoutingServiceRoute *native_route,
            native_type *native)
    {
        return static_cast<Input*>(RTI_RoutingServiceRoute_get_stream_port_user_data(
                native_route,
                native->stream_reader_data));
    }

};

template <typename DataRep, typename InfoRep>
struct TypedPortType<Output, DataRep, InfoRep>
{
    typedef TypedOutput<DataRep, InfoRep> type;
    typedef RTI_RoutingServiceStreamWriterExt native_type;

    static native_type * begin(RTI_RoutingServiceRoute *native_route)
    {
        return  RTI_RoutingServiceRoute_get_first_output(native_route);
    }

    static native_type * next(
            RTI_RoutingServiceRoute *native_route,
            native_type *native)
    {
        return  RTI_RoutingServiceRoute_get_next_output(native_route, native);
    }

    static Output* from_native(
            RTI_RoutingServiceRoute *native_route,
            native_type *native)
    {
        return static_cast<Output*>(RTI_RoutingServiceRoute_get_stream_port_user_data(
                native_route,
                native->stream_writer_data));
    }
};

template <typename PORT, 
          typename DataRep,
          typename InfoRep = dds::sub::SampleInfo>
class PortIterator  {
public:
    // iterator traits
   typedef std::random_access_iterator_tag iterator_category;
   typedef typename TypedPortType<PORT, DataRep, InfoRep>::type value_type;
   typedef value_type reference;
   typedef value_type pointer;
   typedef std::ptrdiff_t difference_type;


    explicit PortIterator(
            RTI_RoutingServiceRoute *native_route)
        : native_route_(native_route)
    {
       native_ = TypedPortType<PORT, DataRep, InfoRep>::begin(native_route);
    }

    explicit PortIterator()
        : native_route_(NULL), native_(NULL)
    {       
    }

    PortIterator (const PortIterator<PORT, DataRep, InfoRep>& other)
        : native_route_(other.native_route_),
          native_(other.native_)
    {}

    PortIterator & operator = (const PortIterator<PORT, DataRep, InfoRep>& other)
    {
        native_route_ = other.native_route_;
        native_ = other.native_;

        return *this;
    }  

    value_type operator*()
    {
        return TypedPortType<PORT, DataRep, InfoRep>::from_native(
                native_route_,
                native_);
    }

    value_type operator->()
    {
        return *(*this);
    }

    PortIterator & operator++()
    {
        native_ = TypedPortType<PORT, DataRep, InfoRep>::next(
                native_route_,
                native_);
        
        return *this;
    }

    PortIterator operator++(int)
    {
        PortIterator temp(*this);
        ++(*this);
        return temp;
    }


    friend bool operator<(
            const PortIterator & s1,
            const PortIterator & s2)
    {
        return s1.index() < s2.index();
    }

    friend bool operator>(
            const PortIterator & s1,
            const PortIterator & s2)
    {
        return s1.index() > s2.index();
    }

    friend bool operator<=(
            const PortIterator & s1,
            const PortIterator & s2)
    {
        return s1.index() <= s2.index();
    }

    friend bool operator>=(
            const PortIterator & s1,
            const PortIterator & s2)
    {
        return s1.index() >= s2.index();
    }

    friend bool operator==(
            const PortIterator & s1,
            const PortIterator & s2)
    {
        return (s1.index() == s2.index());
    }

    friend bool operator!=(
            const PortIterator & s1,
            const PortIterator & s2)
    {
        return !(s1 == s2);
    }

private:
    int32_t index() const
    {
        return (native_ == NULL)
                ? RTI_INT32_MAX
                : TypedPortType<PORT, DataRep, InfoRep>::from_native(
                        native_route_,
                        native_)->index();
    }

    RTI_RoutingServiceRoute *native_route_;
    typename TypedPortType<PORT, DataRep, InfoRep>::native_type *native_;

};


} } }

#endif // RTI_ROUTING_PROCESSOR_PORTS_ITERATOR_HPP_
