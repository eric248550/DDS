// (C) Copyright Douglas Gregor 2010
//
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

// Clang compiler setup.

#define RTIBOOST_HAS_PRAGMA_ONCE

// Detecting `-fms-extension` compiler flag assuming that _MSC_VER defined when that flag is used.
#if defined (_MSC_VER) && (__clang_major__ > 3 || (__clang_major__ == 3 && __clang_minor__ >= 4))
#   define RTIBOOST_HAS_PRAGMA_DETECT_MISMATCH
#endif

// When compiling with clang before __has_extension was defined,
// even if one writes 'defined(__has_extension) && __has_extension(xxx)',
// clang reports a compiler error. So the only workaround found is:

#ifndef __has_extension
#define __has_extension __has_feature
#endif

#ifndef __has_attribute
#define __has_attribute(x) 0
#endif

#if !__has_feature(cxx_exceptions) && !defined(RTIBOOST_NO_EXCEPTIONS)
#  define RTIBOOST_NO_EXCEPTIONS
#endif

#if !__has_feature(cxx_rtti) && !defined(RTIBOOST_NO_RTTI)
#  define RTIBOOST_NO_RTTI
#endif

#if !__has_feature(cxx_rtti) && !defined(RTIBOOST_NO_TYPEID)
#  define RTIBOOST_NO_TYPEID
#endif

#if defined(__int64) && !defined(__GNUC__)
#  define RTIBOOST_HAS_MS_INT64
#endif

#define RTIBOOST_HAS_NRVO

// Branch prediction hints
#if defined(__has_builtin)
#if __has_builtin(__builtin_expect)
#define RTIBOOST_LIKELY(x) __builtin_expect(x, 1)
#define RTIBOOST_UNLIKELY(x) __builtin_expect(x, 0)
#endif
#endif

// Clang supports "long long" in all compilation modes.
#define RTIBOOST_HAS_LONG_LONG

//
// We disable this if the compiler is really nvcc with C++03 as it
// doesn't actually support __int128 as of CUDA_VERSION=7500
// even though it defines __SIZEOF_INT128__.
// See https://svn.boost.org/trac/boost/ticket/10418
//     https://svn.boost.org/trac/boost/ticket/11852
// Only re-enable this for nvcc if you're absolutely sure
// of the circumstances under which it's supported.
// Similarly __SIZEOF_INT128__ is defined when targetting msvc
// compatibility even though the required support functions are absent.
//
#if defined(__CUDACC__)
#  if defined(RTIBOOST_GCC_CXX11)
#    define RTIBOOST_NVCC_CXX11
#  else
#    define RTIBOOST_NVCC_CXX03
#  endif
#endif

#if defined(__SIZEOF_INT128__) && !defined(RTIBOOST_NVCC_CXX03) && !defined(_MSC_VER)
#  define RTIBOOST_HAS_INT128
#endif


//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if !defined(_WIN32) && !defined(__WIN32__) && !defined(WIN32)
#  define RTIBOOST_SYMBOL_EXPORT __attribute__((__visibility__("default")))
#  define RTIBOOST_SYMBOL_IMPORT
#  define RTIBOOST_SYMBOL_VISIBLE __attribute__((__visibility__("default")))
#endif

//
// The RTIBOOST_FALLTHROUGH macro can be used to annotate implicit fall-through
// between switch labels.
//
#if __cplusplus >= 201103L && defined(__has_warning)
#  if __has_feature(cxx_attributes) && __has_warning("-Wimplicit-fallthrough")
#    define RTIBOOST_FALLTHROUGH [[clang::fallthrough]]
#  endif
#endif

#if !__has_feature(cxx_auto_type)
#  define RTIBOOST_NO_CXX11_AUTO_DECLARATIONS
#  define RTIBOOST_NO_CXX11_AUTO_MULTIDECLARATIONS
#endif

//
// Currently clang on Windows using VC++ RTL does not support C++11's char16_t or char32_t
//
#if defined(_MSC_VER) || !(defined(__GXX_EXPERIMENTAL_CXX0X__) || __cplusplus >= 201103L)
#  define RTIBOOST_NO_CXX11_CHAR16_T
#  define RTIBOOST_NO_CXX11_CHAR32_T
#endif

#if !__has_feature(cxx_constexpr)
#  define RTIBOOST_NO_CXX11_CONSTEXPR
#endif

#if !__has_feature(cxx_decltype)
#  define RTIBOOST_NO_CXX11_DECLTYPE
#endif

#if !__has_feature(cxx_decltype_incomplete_return_types)
#  define RTIBOOST_NO_CXX11_DECLTYPE_N3276
#endif

#if !__has_feature(cxx_defaulted_functions)
#  define RTIBOOST_NO_CXX11_DEFAULTED_FUNCTIONS
#endif

#if !__has_feature(cxx_deleted_functions)
#  define RTIBOOST_NO_CXX11_DELETED_FUNCTIONS
#endif

#if !__has_feature(cxx_explicit_conversions)
#  define RTIBOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#endif

#if !__has_feature(cxx_default_function_template_args)
#  define RTIBOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define RTIBOOST_NO_CXX11_HDR_INITIALIZER_LIST
#endif

#if !__has_feature(cxx_lambdas)
#  define RTIBOOST_NO_CXX11_LAMBDAS
#endif

#if !__has_feature(cxx_local_type_template_args)
#  define RTIBOOST_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#endif

#if !__has_feature(cxx_noexcept)
#  define RTIBOOST_NO_CXX11_NOEXCEPT
#endif

#if !__has_feature(cxx_nullptr)
#  define RTIBOOST_NO_CXX11_NULLPTR
#endif

#if !__has_feature(cxx_range_for)
#  define RTIBOOST_NO_CXX11_RANGE_BASED_FOR
#endif

#if !__has_feature(cxx_raw_string_literals)
#  define RTIBOOST_NO_CXX11_RAW_LITERALS
#endif

#if !__has_feature(cxx_reference_qualified_functions)
#  define RTIBOOST_NO_CXX11_REF_QUALIFIERS
#endif

#if !__has_feature(cxx_generalized_initializers)
#  define RTIBOOST_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#endif

#if !__has_feature(cxx_rvalue_references)
#  define RTIBOOST_NO_CXX11_RVALUE_REFERENCES
#endif

#if !__has_feature(cxx_strong_enums)
#  define RTIBOOST_NO_CXX11_SCOPED_ENUMS
#endif

#if !__has_feature(cxx_static_assert)
#  define RTIBOOST_NO_CXX11_STATIC_ASSERT
#endif

#if !__has_feature(cxx_alias_templates)
#  define RTIBOOST_NO_CXX11_TEMPLATE_ALIASES
#endif

#if !__has_feature(cxx_unicode_literals)
#  define RTIBOOST_NO_CXX11_UNICODE_LITERALS
#endif

#if !__has_feature(cxx_variadic_templates)
#  define RTIBOOST_NO_CXX11_VARIADIC_TEMPLATES
#endif

#if !__has_feature(cxx_user_literals)
#  define RTIBOOST_NO_CXX11_USER_DEFINED_LITERALS
#endif

#if !__has_feature(cxx_alignas)
#  define RTIBOOST_NO_CXX11_ALIGNAS
#endif

#if !__has_feature(cxx_trailing_return)
#  define RTIBOOST_NO_CXX11_TRAILING_RESULT_TYPES
#endif

#if !__has_feature(cxx_inline_namespaces)
#  define RTIBOOST_NO_CXX11_INLINE_NAMESPACES
#endif

#if !__has_feature(cxx_override_control)
#  define RTIBOOST_NO_CXX11_FINAL
#endif

#if !(__has_feature(__cxx_binary_literals__) || __has_extension(__cxx_binary_literals__))
#  define RTIBOOST_NO_CXX14_BINARY_LITERALS
#endif

#if !__has_feature(__cxx_decltype_auto__)
#  define RTIBOOST_NO_CXX14_DECLTYPE_AUTO
#endif

#if !__has_feature(__cxx_aggregate_nsdmi__)
#  define RTIBOOST_NO_CXX14_AGGREGATE_NSDMI
#endif

#if !__has_feature(__cxx_init_captures__)
#  define RTIBOOST_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif

#if !__has_feature(__cxx_generic_lambdas__)
#  define RTIBOOST_NO_CXX14_GENERIC_LAMBDAS
#endif

// clang < 3.5 has a defect with dependent type, like following.
//
//  template <class T>
//  constexpr typename enable_if<pred<T> >::type foo(T &)
//  { } // error: no return statement in constexpr function
//
// This issue also affects C++11 mode, but C++11 constexpr requires return stmt.
// Therefore we don't care such case.
//
// Note that we can't check Clang version directly as the numbering system changes depending who's
// creating the Clang release (see https://github.com/boostorg/config/pull/39#issuecomment-59927873)
// so instead verify that we have a feature that was introduced at the same time as working C++14
// constexpr (generic lambda's in this case):
//
#if !__has_feature(__cxx_generic_lambdas__) || !__has_feature(__cxx_relaxed_constexpr__)
#  define RTIBOOST_NO_CXX14_CONSTEXPR
#endif

#if !__has_feature(__cxx_return_type_deduction__)
#  define RTIBOOST_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif

#if !__has_feature(__cxx_variable_templates__)
#  define RTIBOOST_NO_CXX14_VARIABLE_TEMPLATES
#endif

#if __cplusplus < 201400
// All versions with __cplusplus above this value seem to support this:
#  define RTIBOOST_NO_CXX14_DIGIT_SEPARATORS
#endif
//
// __builtin_unreachable:
#if defined(__has_builtin) && __has_builtin(__builtin_unreachable)
#define RTIBOOST_UNREACHABLE_RETURN(x) __builtin_unreachable();
#endif

// Clang has supported the 'unused' attribute since the first release.
#define RTIBOOST_ATTRIBUTE_UNUSED __attribute__((__unused__))

#ifndef RTIBOOST_COMPILER
#  define RTIBOOST_COMPILER "Clang version " __clang_version__
#endif

// Macro used to identify the Clang compiler.
#define RTIBOOST_CLANG 1

