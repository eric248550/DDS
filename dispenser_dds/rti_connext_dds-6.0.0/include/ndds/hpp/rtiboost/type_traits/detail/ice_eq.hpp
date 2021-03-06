//  (C) Copyright John Maddock and Steve Cleary 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_DETAIL_ICE_EQ_HPP_INCLUDED
#define RTIBOOST_TT_DETAIL_ICE_EQ_HPP_INCLUDED

#include <rtiboost/config.hpp>

namespace rtiboost {
namespace type_traits {

template <int b1, int b2>
struct ice_eq
{
    RTIBOOST_STATIC_CONSTANT(bool, value = (b1 == b2));
};

template <int b1, int b2>
struct ice_ne
{
    RTIBOOST_STATIC_CONSTANT(bool, value = (b1 != b2));
};

#ifndef RTIBOOST_NO_INCLASS_MEMBER_INITIALIZATION
template <int b1, int b2> bool const ice_eq<b1,b2>::value;
template <int b1, int b2> bool const ice_ne<b1,b2>::value;
#endif

} // namespace type_traits
} // namespace rtiboost

#endif // RTIBOOST_TT_DETAIL_ICE_EQ_HPP_INCLUDED
