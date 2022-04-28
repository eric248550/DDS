/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ADAPTER_TYPE_INFOHPP_
#define RTI_ROUTING_ADAPTER_TYPE_INFOHPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>

#include <routingservice/routingservice_infrastructure.h>
#include <dds/core/Value.hpp>
#include <dds/core/SafeEnumeration.hpp>
#include <rti/core/NativeValueType.hpp>

namespace rti { namespace routing {

/** 
 * @ingroup RTI_RoutingServiceInfrastructureModule
 *
 */

/** @ingroup RTI_RoutingServiceInfrastructureModule
 *
 * @class TypeRepresentationKind_def
 * 
 * @brief The definition of the rti::routing::TypeRepresentationKind
 *
 * The range [0-100] is reserved for RTI use. Within that range are some
 * predefined type representations.
 *
 */
struct TypeRepresentationKind_def {
    /**
     * @brief Definition of all the possible type representation kinds
     */
    enum type {
        /**
         * @brief Dynamic type representation.
         *
         * Types with this representation are provided as \ndds TypeCodes.
         * 
         * For more information about TypeCodes, see Chapter 3 in the
         * RTI Core Libraries and Utilities User's Manual.
         */
        DYNAMIC_TYPE = RTI_ROUTING_SERVICE_TYPE_REPRESENTATION_DYNAMIC_TYPE,
        /**
         * @brief @not_supported XML type representation.
         *
         * Types with this representation are provided as XML strings.
         * The XML schema is the \ndds XML schema for type representation.
         *
         * For more information about XML representation,
         * see Chapter 3 in the RTI Core Libraries and Utilities User's Manual.
         */
        XML = RTI_ROUTING_SERVICE_TYPE_REPRESENTATION_XML,
        /**
         * @brief @not_supported Java object type representation.
         *
         * Types with this representation are provided as Java objects.
         */
        JAVA_OBJECT = RTI_ROUTING_SERVICE_TYPE_REPRESENTATION_JAVA_OBJECT,        
        /**
         * @brief @not_supported Custom type representation.
         *
         * Types with this representation are specific to a concrete
         * adapter implementation
         */
        CUSTOM = RTI_ROUTING_SERVICE_TYPE_REPRESENTATION_FIRST_CUSTOM_REPRESENTATION
    };
};

/** @ingroup RTI_RoutingServiceInfrastructureModule
 *
 * @class TypeRepresentationKind
 * 
 * @brief valid type representations that @product accepts.
 *
 * @see rti::routing::TypeRepresentationKind_def
 */
typedef dds::core::safe_enum<TypeRepresentationKind_def> TypeRepresentationKind;


class TypeInfoAdapter {
public:
    typedef RTI_RoutingServiceTypeInfo native_type;

    static void initialize(native_type& native_value)
    {
        static const native_type default_value = {
            NULL, 
            RTI_ROUTING_SERVICE_TYPE_REPRESENTATION_DYNAMIC_TYPE, 
            NULL};
        native_value = default_value;
    }

    static void finalize(native_type& native_value)
    {
        if (native_value.type_name != NULL) {
            RTIOsapiHeap_freeString(native_value.type_name);
            native_value.type_name = NULL;
        }
    }

    static void copy(native_type& destination, const native_type& source)
    {
        char *result = DDS_String_replace(
                &destination.type_name,
                source.type_name);
        if (source.type_name != NULL && result == NULL) {
            throw std::bad_alloc();
        }
        destination.type_representation_kind = 
                source.type_representation_kind;
        destination.type_representation =
                source.type_representation;
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        if (strcmp(first.type_name, second.type_name) != 0) {
            return false;
        }
        if (first.type_representation_kind 
                != second.type_representation_kind) {
            return false;
        }
        
        return first.type_representation == second.type_representation;
    }

};

class TypeInfo;

}

// native_type_traits needs to be defined in rti::core
namespace core {

template <>
struct native_type_traits<rti::routing::TypeInfo> {
    typedef rti::routing::TypeInfoAdapter adapter_type;
    typedef RTI_RoutingServiceTypeInfo native_type;
};

}

namespace routing {

/** @ingroup RTI_RoutingServiceInfrastructureModule
 *
 * @class rti::routing::TypeInfo
 *
 * @brief Definition of the type information associated with a @product
 * stream.
 * 
 * @see StreamInfo.
 *
 */
class TypeInfo : public rti::core::NativeValueType<TypeInfo> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(TypeInfo)

    typedef rti::core::NativeValueType<TypeInfo> Base;

    /**
     * @brief Type representation defined as an opaque pointer.
     *
     * How this opaque is interpreted depends on the TypeRepresentationKind.
     */
    typedef RTI_RoutingServiceTypeRepresentation TypeRepresentationType;    
public:

    /**
     * @brief Constructs a TypeInfo with the minimum required information.
     *
     * @param the_type_name
     *        @rs_st_in Registered name of the type associated with the data.
     * @param the_type_representation_kind
     *        @rs_st_in Indicates the representation of the object that
     *        describes the type. Default: TypeRepresentationKind::DYNAMIC_TYPE.
     */
    TypeInfo(
            std::string& the_type_name,
            TypeRepresentationKind the_type_representation_kind = 
                    TypeRepresentationKind::DYNAMIC_TYPE) 
    {
        type_name(the_type_name);
        type_representation_kind(the_type_representation_kind);
    }

    TypeInfo(const struct RTI_RoutingServiceTypeInfo &native_stream_info)
            : Base(native_stream_info)
    {
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    std::string type_name() const
    {
        return native().type_name;
    }

    /**
     * @brief Sets the registered name of the type associated with the data.
     *
     * @product uses the type name to provide the right type information to
     * StreamReader and StreamWriter. Namely, a type match is performed by
     * comparing this type name with the value specified in the tag
     * &lt;registered_type_name&gt; within the &lt;input&gt; and &lt;output&gt;
     * tags.
     */
    TypeInfo& type_name(const std::string& the_type_name)
    {

        if (DDS_String_replace(
                &native().type_name,
                the_type_name.c_str()) == NULL) {
            throw std::bad_alloc();
        }
        
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    TypeRepresentationKind type_representation_kind() const
    {
        return static_cast<TypeRepresentationKind::type>(
                native().type_representation_kind);
    }

    /**
     * @brief Sets the type representation kind.
     *
     * This member indicates how to interpret the type representation.
     *
     * @see TypeRepresentationKind
     */
    TypeInfo& type_representation_kind(
            TypeRepresentationKind the_type_representation_kind)
    {
        native().type_representation_kind = static_cast<int>(
                the_type_representation_kind.underlying());
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    TypeRepresentationType  type_representation() const
    {
        return native().type_representation;
    }

    /**
     * @brief Sets the type representation value.
     *
     * This member is defined as an opaque pointer that can hold any type
     * representation. How to interpret this pointer is determined by the
     * TypeRepresentationKind, which shall be consistent with the object set
     * in this member.
     */
    TypeInfo&  type_representation(TypeRepresentationType the_type_representation) 
    {
        native().type_representation = the_type_representation;
        return *this;
    }
};

}}

#endif // RTI_ROUTING_ADAPTER_TYPE_INFOHPP_
