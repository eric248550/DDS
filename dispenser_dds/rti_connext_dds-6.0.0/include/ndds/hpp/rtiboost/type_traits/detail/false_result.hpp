//  Copyright David Abrahams 2002. 
//  Use, modification and distribution are subject to the Boost Software License,
//  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt).
//
//  See http://www.boost.org/libs/type_traits for most recent version including documentation.


#ifndef RTIBOOST_TT_DETAIL_FALSE_RESULT_HPP_INCLUDED
#define RTIBOOST_TT_DETAIL_FALSE_RESULT_HPP_INCLUDED

#include <rtiboost/config.hpp>

namespace rtiboost {
namespace type_traits {

// Utility class which always "returns" false
struct false_result
{
    template <typename T> struct result_
    {
        RTIBOOST_STATIC_CONSTANT(bool, value = false);
    };
};

}} // namespace rtiboost::type_traits

#endif // RTIBOOST_TT_DETAIL_FALSE_RESULT_HPP_INCLUDED
