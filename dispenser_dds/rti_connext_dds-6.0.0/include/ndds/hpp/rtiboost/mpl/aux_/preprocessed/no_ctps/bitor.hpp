
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "rtiboost/mpl/bitor.hpp" header
// -- DO NOT modify by hand!

namespace rtiboost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct bitor_impl
    : if_c<
          ( RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > RTIBOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< bitor_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< bitor_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct bitor_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< na,rtiboost_integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct bitor_impl< rtiboost_integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        RTIBOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct bitor_tag
{
    typedef typename T::tag type;
};

/// forward declaration

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(N1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N2)
    >
struct bitor_2;

template<
      typename RTIBOOST_MPL_AUX_NA_PARAM(N1)
    , typename RTIBOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct bitor_

    : if_<

          is_na<N3>
        , bitor_2< N1,N2 >
        , bitor_<
              bitor_2< N1,N2 >
            , N3, N4, N5
            >
        >::type

{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , bitor_
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct bitor_2
    : bitor_impl<
          typename bitor_tag<N1>::type
        , typename bitor_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    RTIBOOST_MPL_AUX_LAMBDA_SUPPORT(2, bitor_2, (N1, N2))

};

RTIBOOST_MPL_AUX_NA_SPEC2(2, 5, bitor_)

}}

namespace rtiboost { namespace mpl {
template<>
struct bitor_impl< rtiboost_integral_c_tag,rtiboost_integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( RTIBOOST_MPL_AUX_VALUE_WKND(N1)::value
                  | RTIBOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}
