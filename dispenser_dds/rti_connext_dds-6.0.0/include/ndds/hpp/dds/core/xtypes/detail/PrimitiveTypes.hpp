/* Copyright 2010, Object Management Group, Inc.
 * Copyright 2010, PrismTech, Corp.
 * Copyright 2010, Real-Time Innovations, Inc.
 * All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef OMG_DDS_CORE_XTYPES_DETAIL_PRIMITIVE_TYPES_HPP_
#define OMG_DDS_CORE_XTYPES_DETAIL_PRIMITIVE_TYPES_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <rti/core/xtypes/PrimitiveTypesImpl.hpp>

namespace dds { namespace core { namespace xtypes { namespace detail {

using rti::core::xtypes::PrimitiveType;

} } } }

#if DISABLE
// This template specialization have the intent to provide guidelines
// implementors of this specification. Notice that this define only a subset
// of primitive types, thus more work for you to do...
namespace dds {
  namespace core {
    namespace xtypes {
      // Notice that const char* const is used instead of std::string
      // to limit initialization issues with ctors.
      template<>
      struct dynamic_type_traits<uint8_t> {
        static const TypeKind TYPE_ID = TypeKind::UINT_8_TYPE;
        static const  char* const NAME; // "uint8_t"
      };

      template<>
      struct dynamic_type_traits<int16_t> {
        static const TypeKind TYPE_ID = TypeKind::INT_16_TYPE;
        static const  char* const NAME; // "uint16_t"
      };


      template<>
      struct dynamic_type_traits<uint16_t> {
        static const TypeKind TYPE_ID = TypeKind::UINT_16_TYPE;
        static const  char* const NAME; // "int16_t"
      };

      template<>
      struct dynamic_type_traits<int32_t> {
        static const TypeKind TYPE_ID = TypeKind::INT_32_TYPE;
        static const  char* const NAME; // "int16_t"
      };

      template<>
      struct dynamic_type_traits<uint32_t> {
        static const TypeKind TYPE_ID = TypeKind::UINT_32_TYPE;
        static const  char* const NAME; // "uint32_t"
      };

    }
  }
}

#endif

#endif /* OMG_DDS_CORE_XTYPES_DETAIL_PRIMITIVE_TYPES_HPP_ */
