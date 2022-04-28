# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef RTIBOOST_PREPROCESSOR_DEBUG_ASSERT_HPP
# define RTIBOOST_PREPROCESSOR_DEBUG_ASSERT_HPP
#
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/control/expr_iif.hpp>
# include <rtiboost/preprocessor/control/iif.hpp>
# include <rtiboost/preprocessor/logical/not.hpp>
# include <rtiboost/preprocessor/tuple/eat.hpp>
#
# /* RTIBOOST_PP_ASSERT */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ASSERT RTIBOOST_PP_ASSERT_D
# else
#    define RTIBOOST_PP_ASSERT(cond) RTIBOOST_PP_ASSERT_D(cond)
# endif
#
# define RTIBOOST_PP_ASSERT_D(cond) RTIBOOST_PP_IIF(RTIBOOST_PP_NOT(cond), RTIBOOST_PP_ASSERT_ERROR, RTIBOOST_PP_TUPLE_EAT_1)(...)
# define RTIBOOST_PP_ASSERT_ERROR(x, y, z)
#
# /* RTIBOOST_PP_ASSERT_MSG */
#
# if ~RTIBOOST_PP_CONFIG_FLAGS() & RTIBOOST_PP_CONFIG_EDG()
#    define RTIBOOST_PP_ASSERT_MSG RTIBOOST_PP_ASSERT_MSG_D
# else
#    define RTIBOOST_PP_ASSERT_MSG(cond, msg) RTIBOOST_PP_ASSERT_MSG_D(cond, msg)
# endif
#
# define RTIBOOST_PP_ASSERT_MSG_D(cond, msg) RTIBOOST_PP_EXPR_IIF(RTIBOOST_PP_NOT(cond), msg)
#
# endif
