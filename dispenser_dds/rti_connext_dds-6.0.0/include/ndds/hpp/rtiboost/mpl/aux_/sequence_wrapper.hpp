
// NO INCLUDE GUARDS, THE HEADER IS INTENDED FOR MULTIPLE INCLUSION

#if !defined(RTIBOOST_PP_IS_ITERATING)

///// header body

// Copyright Aleksey Gurtovoy 2000-2008
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#   include <rtiboost/mpl/aux_/config/ctps.hpp>
#   include <rtiboost/mpl/aux_/config/static_constant.hpp>
#   include <rtiboost/mpl/aux_/nttp_decl.hpp>

#   include <rtiboost/preprocessor/arithmetic/sub.hpp>
#   include <rtiboost/preprocessor/tuple/elem.hpp>
#   include <rtiboost/preprocessor/enum_params_with_a_default.hpp>
#   include <rtiboost/preprocessor/enum_params.hpp>
#   include <rtiboost/preprocessor/enum.hpp>
#   include <rtiboost/preprocessor/repeat.hpp>
#   include <rtiboost/preprocessor/comma_if.hpp>
#   include <rtiboost/preprocessor/iterate.hpp>

#if defined(RTIBOOST_MPL_PREPROCESSING_MODE)
#   undef LONG_MAX
#endif

namespace rtiboost { namespace mpl {

#if !defined(RTIBOOST_AUX778076_SEQUENCE_BASE_NAME)
#   define RTIBOOST_AUX778076_SEQUENCE_BASE_NAME RTIBOOST_AUX778076_SEQUENCE_NAME
#endif

#if !defined(RTIBOOST_AUX778076_SEQUENCE_INTEGRAL_WRAPPER)

#   define RTIBOOST_AUX778076_SEQUENCE_PARAM_NAME T
#   define RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM typename T
#   define RTIBOOST_AUX778076_SEQUENCE_DEFAULT na

#   define RTIBOOST_AUX778076_SEQUENCE_NAME_N(n) \
    RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_BASE_NAME,n) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_PARAMS() \
    RTIBOOST_PP_ENUM_PARAMS( \
          RTIBOOST_AUX778076_SEQUENCE_LIMIT \
        , RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_ARGS() \
    RTIBOOST_PP_ENUM_PARAMS( \
          RTIBOOST_AUX778076_SEQUENCE_LIMIT \
        , T \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_DEFAULT_PARAMS() \
     RTIBOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          RTIBOOST_AUX778076_SEQUENCE_LIMIT \
        , RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM \
        , RTIBOOST_AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_N_PARAMS(n) \
    RTIBOOST_PP_ENUM_PARAMS(n, RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_N_ARGS(n) \
    RTIBOOST_PP_ENUM_PARAMS(n, T) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(n) \
    RTIBOOST_PP_ENUM_PARAMS(n, T) \
    RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_PP_ENUM( \
          RTIBOOST_PP_SUB_D(1,RTIBOOST_AUX778076_SEQUENCE_LIMIT,n) \
        , RTIBOOST_PP_TUPLE_ELEM_3_2 \
        , RTIBOOST_AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#else // RTIBOOST_AUX778076_SEQUENCE_INTEGRAL_WRAPPER

#   define RTIBOOST_AUX778076_SEQUENCE_PARAM_NAME C
#   define RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM RTIBOOST_MPL_AUX_NTTP_DECL(long, C)
#   define RTIBOOST_AUX778076_SEQUENCE_DEFAULT LONG_MAX

#   define RTIBOOST_AUX778076_SEQUENCE_PARAMS() \
    typename T, RTIBOOST_PP_ENUM_PARAMS( \
          RTIBOOST_AUX778076_SEQUENCE_LIMIT \
        , RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_ARGS() \
    T, RTIBOOST_PP_ENUM_PARAMS( \
          RTIBOOST_AUX778076_SEQUENCE_LIMIT \
        , C \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_DEFAULT_PARAMS() \
    typename T, \
    RTIBOOST_PP_ENUM_PARAMS_WITH_A_DEFAULT( \
          RTIBOOST_AUX778076_SEQUENCE_LIMIT \
        , RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM \
        , RTIBOOST_AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_N_PARAMS(n) \
    typename T RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_PP_ENUM_PARAMS(n, RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM) \
    /**/

#   if !defined(RTIBOOST_AUX778076_SEQUENCE_CONVERT_CN_TO)
#       define RTIBOOST_AUX778076_SEQUENCE_CONVERT_CN_TO(z,n,TARGET) RTIBOOST_PP_CAT(C,n)
#   endif

#   define RTIBOOST_AUX778076_SEQUENCE_N_ARGS(n) \
    T RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_PP_ENUM(n,RTIBOOST_AUX778076_SEQUENCE_CONVERT_CN_TO,T) \
    /**/

#   define RTIBOOST_AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(n) \
    T, RTIBOOST_PP_ENUM_PARAMS(n, C) \
    RTIBOOST_PP_COMMA_IF(n) \
    RTIBOOST_PP_ENUM( \
          RTIBOOST_PP_SUB_D(1,RTIBOOST_AUX778076_SEQUENCE_LIMIT,n) \
        , RTIBOOST_PP_TUPLE_ELEM_3_2 \
        , RTIBOOST_AUX778076_SEQUENCE_DEFAULT \
        ) \
    /**/

#endif // RTIBOOST_AUX778076_SEQUENCE_INTEGRAL_WRAPPER


#if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)
// forward declaration
template<
      RTIBOOST_AUX778076_SEQUENCE_DEFAULT_PARAMS()
    >
struct RTIBOOST_AUX778076_SEQUENCE_NAME;
#else
namespace aux {
template< RTIBOOST_MPL_AUX_NTTP_DECL(int, N) > 
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_NAME,_chooser);
}
#endif

#define RTIBOOST_PP_ITERATION_PARAMS_1 \
    (3,(0, RTIBOOST_AUX778076_SEQUENCE_LIMIT, <rtiboost/mpl/aux_/sequence_wrapper.hpp>))
#include RTIBOOST_PP_ITERATE()

// real C++ version is already taken care of
#if defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

namespace aux {
// ???_count_args
#define RTIBOOST_AUX778076_COUNT_ARGS_PREFIX         RTIBOOST_AUX778076_SEQUENCE_NAME
#define RTIBOOST_AUX778076_COUNT_ARGS_DEFAULT        RTIBOOST_AUX778076_SEQUENCE_DEFAULT
#define RTIBOOST_AUX778076_COUNT_ARGS_PARAM_NAME     RTIBOOST_AUX778076_SEQUENCE_PARAM_NAME
#define RTIBOOST_AUX778076_COUNT_ARGS_TEMPLATE_PARAM RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM
#define RTIBOOST_AUX778076_COUNT_ARGS_ARITY          RTIBOOST_AUX778076_SEQUENCE_LIMIT
#define RTIBOOST_AUX778076_COUNT_ARGS_USE_STANDARD_PP_PRIMITIVES
#include <rtiboost/mpl/aux_/count_args.hpp>

template<
      RTIBOOST_AUX778076_SEQUENCE_PARAMS()
    >
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_NAME,_impl)
{
    typedef aux::RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_NAME,_count_args)<
          RTIBOOST_PP_ENUM_PARAMS(RTIBOOST_AUX778076_SEQUENCE_LIMIT, RTIBOOST_AUX778076_SEQUENCE_PARAM_NAME)
        > arg_num_;
    
    typedef typename aux::RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_NAME,_chooser)< arg_num_::value >
        ::template result_< RTIBOOST_AUX778076_SEQUENCE_ARGS() >::type type;
};

} // namespace aux

template<
      RTIBOOST_AUX778076_SEQUENCE_DEFAULT_PARAMS()
    >
struct RTIBOOST_AUX778076_SEQUENCE_NAME
    : aux::RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_NAME,_impl)<
          RTIBOOST_AUX778076_SEQUENCE_ARGS()
        >::type
{
    typedef typename aux::RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_NAME,_impl)<
          RTIBOOST_AUX778076_SEQUENCE_ARGS()
        >::type type;
};

#endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#   undef RTIBOOST_AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS
#   undef RTIBOOST_AUX778076_SEQUENCE_N_ARGS
#   undef RTIBOOST_AUX778076_SEQUENCE_CONVERT_CN_TO
#   undef RTIBOOST_AUX778076_SEQUENCE_N_PARAMS
#   undef RTIBOOST_AUX778076_SEQUENCE_DEFAULT_PARAMS
#   undef RTIBOOST_AUX778076_SEQUENCE_ARGS
#   undef RTIBOOST_AUX778076_SEQUENCE_PARAMS
#   undef RTIBOOST_AUX778076_SEQUENCE_NAME_N
#   undef RTIBOOST_AUX778076_SEQUENCE_DEFAULT
#   undef RTIBOOST_AUX778076_SEQUENCE_TEMPLATE_PARAM
#   undef RTIBOOST_AUX778076_SEQUENCE_PARAM_NAME
#   undef RTIBOOST_AUX778076_SEQUENCE_LIMIT
#   undef RTIBOOST_AUX778076_SEQUENCE_BASE_NAME
#   undef RTIBOOST_AUX778076_SEQUENCE_NAME
#   undef RTIBOOST_AUX778076_SEQUENCE_INTEGRAL_WRAPPER

}}

///// iteration

#else
#define i_ RTIBOOST_PP_FRAME_ITERATION(1)

#   if !defined(RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION)

#if i_ == RTIBOOST_AUX778076_SEQUENCE_LIMIT

/// primary template (not a specialization!)
template<
      RTIBOOST_AUX778076_SEQUENCE_N_PARAMS(i_)
    >
struct RTIBOOST_AUX778076_SEQUENCE_NAME
    : RTIBOOST_AUX778076_SEQUENCE_NAME_N(i_)< RTIBOOST_AUX778076_SEQUENCE_N_ARGS(i_) >
{
    typedef typename RTIBOOST_AUX778076_SEQUENCE_NAME_N(i_)< RTIBOOST_AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
};

#else

template<
      RTIBOOST_AUX778076_SEQUENCE_N_PARAMS(i_)
    >
struct RTIBOOST_AUX778076_SEQUENCE_NAME< RTIBOOST_AUX778076_SEQUENCE_N_PARTIAL_SPEC_ARGS(i_) >
    : RTIBOOST_AUX778076_SEQUENCE_NAME_N(i_)< RTIBOOST_AUX778076_SEQUENCE_N_ARGS(i_) >
{
#if i_ > 0 || defined(RTIBOOST_AUX778076_SEQUENCE_INTEGRAL_WRAPPER)
    typedef typename RTIBOOST_AUX778076_SEQUENCE_NAME_N(i_)< RTIBOOST_AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
#else
    typedef RTIBOOST_AUX778076_SEQUENCE_NAME_N(i_)< RTIBOOST_AUX778076_SEQUENCE_N_ARGS(i_) >::type type;
#endif
};

#endif // i_ == RTIBOOST_AUX778076_SEQUENCE_LIMIT

#   else

namespace aux {

template<>
struct RTIBOOST_PP_CAT(RTIBOOST_AUX778076_SEQUENCE_NAME,_chooser)<i_>
{
    template<
          RTIBOOST_AUX778076_SEQUENCE_PARAMS()
        >
    struct result_
    {
#if i_ > 0 || defined(RTIBOOST_AUX778076_SEQUENCE_INTEGRAL_WRAPPER)
        typedef typename RTIBOOST_AUX778076_SEQUENCE_NAME_N(i_)<
              RTIBOOST_AUX778076_SEQUENCE_N_ARGS(i_)
            >::type type;
#else
        typedef RTIBOOST_AUX778076_SEQUENCE_NAME_N(i_)<
              RTIBOOST_AUX778076_SEQUENCE_N_ARGS(i_)
            >::type type;
#endif
    };
};

} // namespace aux

#   endif // RTIBOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION

#undef i_
#endif // RTIBOOST_PP_IS_ITERATING
