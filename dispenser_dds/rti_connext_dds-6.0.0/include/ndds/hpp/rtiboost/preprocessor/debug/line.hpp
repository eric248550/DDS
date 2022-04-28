# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef RTIBOOST_PREPROCESSOR_DEBUG_LINE_HPP
# define RTIBOOST_PREPROCESSOR_DEBUG_LINE_HPP
#
# include <rtiboost/preprocessor/cat.hpp>
# include <rtiboost/preprocessor/config/config.hpp>
# include <rtiboost/preprocessor/iteration/iterate.hpp>
# include <rtiboost/preprocessor/stringize.hpp>
#
# /* RTIBOOST_PP_LINE */
#
# if RTIBOOST_PP_CONFIG_EXTENDED_LINE_INFO
#    define RTIBOOST_PP_LINE(line, file) line RTIBOOST_PP_CAT(RTIBOOST_PP_LINE_, RTIBOOST_PP_IS_ITERATING)(file)
#    define RTIBOOST_PP_LINE_RTIBOOST_PP_IS_ITERATING(file) #file
#    define RTIBOOST_PP_LINE_1(file) RTIBOOST_PP_STRINGIZE(file RTIBOOST_PP_CAT(RTIBOOST_PP_LINE_I_, RTIBOOST_PP_ITERATION_DEPTH())())
#    define RTIBOOST_PP_LINE_I_1() [RTIBOOST_PP_FRAME_ITERATION(1)]
#    define RTIBOOST_PP_LINE_I_2() RTIBOOST_PP_LINE_I_1()[RTIBOOST_PP_FRAME_ITERATION(2)]
#    define RTIBOOST_PP_LINE_I_3() RTIBOOST_PP_LINE_I_2()[RTIBOOST_PP_FRAME_ITERATION(3)]
#    define RTIBOOST_PP_LINE_I_4() RTIBOOST_PP_LINE_I_3()[RTIBOOST_PP_FRAME_ITERATION(4)]
#    define RTIBOOST_PP_LINE_I_5() RTIBOOST_PP_LINE_I_4()[RTIBOOST_PP_FRAME_ITERATION(5)]
# else
#    define RTIBOOST_PP_LINE(line, file) line __FILE__
# endif
#
# endif
