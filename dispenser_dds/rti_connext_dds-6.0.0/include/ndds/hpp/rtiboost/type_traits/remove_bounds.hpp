
//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.

#ifndef RTIBOOST_TT_REMOVE_BOUNDS_HPP_INCLUDED
#define RTIBOOST_TT_REMOVE_BOUNDS_HPP_INCLUDED

#include <rtiboost/type_traits/remove_extent.hpp>

namespace rtiboost 
{

template <class T> struct remove_bounds : public remove_extent<T> {};

} // namespace rtiboost

#endif // RTIBOOST_TT_REMOVE_BOUNDS_HPP_INCLUDED
