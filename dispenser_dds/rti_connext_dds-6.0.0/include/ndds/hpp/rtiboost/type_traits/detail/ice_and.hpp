//  (C) Copyright John Maddock and Steve Cleary 2000.
//
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_DETAIL_ICE_AND_HPP_INCLUDED
#define RTIBOOST_TT_DETAIL_ICE_AND_HPP_INCLUDED

#include <rtiboost/config.hpp>

namespace rtiboost {
namespace type_traits {

template <bool b1, bool b2, bool b3 = true, bool b4 = true, bool b5 = true, bool b6 = true, bool b7 = true>
struct ice_and;

template <bool b1, bool b2, bool b3, bool b4, bool b5, bool b6, bool b7>
struct ice_and
{
    RTIBOOST_STATIC_CONSTANT(bool, value = false);
};

template <>
struct ice_and<true, true, true, true, true, true, true>
{
    RTIBOOST_STATIC_CONSTANT(bool, value = true);
};

} // namespace type_traits
} // namespace rtiboost

#endif // RTIBOOST_TT_DETAIL_ICE_AND_HPP_INCLUDED
