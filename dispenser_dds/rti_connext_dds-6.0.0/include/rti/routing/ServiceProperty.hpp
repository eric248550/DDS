/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_ROUTING_ROUTING_SERVICE_PROPERTY_HPP_
#define RTI_ROUTING_ROUTING_SERVICE_PROPERTY_HPP_

// IMPORTANT: macros.hpp must be the first RTI header included in every header
// file so that symbols are exported correctly on Windows
#include <dds/core/macros.hpp>
#include <rti/core/NativeValueType.hpp>

#include "routingservice/routingservice_service.h"
#include <rti/routing/detail/ForwarderUtils.hpp>

namespace rti { namespace routing {

class PropertyAdapter {
public:
    typedef RTI_RoutingServiceProperty native_type;

    static void initialize(native_type& native_value)
    {
        static const native_type DEFAULT
                = RTI_RoutingServiceProperty_INITIALIZER;
        native_value = DEFAULT;
        native_value.service_verbosity = -1;
        native_value.dds_verbosity = -1;
    }

    static void finalize(native_type& native_value)
    {
        if (native_value.cfg_strings != NULL) {
            RTIOsapiHeap_freeArray(native_value.cfg_strings);
            native_value.cfg_strings = NULL;
        }

        RTI_RoutingServiceProperty_finalize(&native_value);
    }

    static void copy(native_type& destination, const native_type& source)
    {
        RTIOsapiUtility_unusedParameter(destination);
        RTIOsapiUtility_unusedParameter(source);

        throw dds::core::UnsupportedError("Unsupported operation: copy");
    }

    static bool equals(const native_type& first, const native_type& second)
    {
        RTIOsapiUtility_unusedParameter(first);
        RTIOsapiUtility_unusedParameter(second);

        throw dds::core::UnsupportedError("Unsupported operation: equals");
    }

    static void add_properties_from_native(
            std::map<std::string, std::string>& properties,
            const RTI_RoutingServiceProperties *native_properties)
    {
        for (int i = 0; i < native_properties->count; i++) {
            properties[native_properties->properties[i].name] =
                    (const char *) native_properties->properties[i].value;
        }
    }

    static void add_properties_to_native(
            RTI_RoutingServiceProperties *native_properties,
            const std::map<std::string, std::string>& properties)
    {
        RTI_RoutingServiceProperties_finalize(native_properties);
        RTI_RoutingServiceProperties_initialize(native_properties);    

        std::map<std::string, std::string>::const_iterator it = properties.begin();
        for (; it != properties.end(); ++it) {
            if (!RTI_RoutingServiceProperties_add(
                    native_properties,
                    it->first.c_str(),
                    it->second.c_str())) {
                throw dds::core::Error("failed to add native property");
            }
        }
    }

};

class ServiceProperty;

}

namespace core {

template<>
struct native_type_traits<rti::routing::ServiceProperty> {
    typedef rti::routing::PropertyAdapter adapter_type;
    typedef RTI_RoutingServiceProperty native_type;
};

}

namespace routing {

/** \ingroup RTI_RoutingServiceLibModule
 *
 * @brief Configuration for a @product object.
 * 
 */
class ServiceProperty : public rti::core::NativeValueType<ServiceProperty> {
public:
    RTI_NATIVE_VALUE_TYPE_DEFINE_DEFAULT_MOVE_OPERATIONS(ServiceProperty)
    
    typedef rti::core::NativeValueType<ServiceProperty> Base;

    /**
     * @brief Creates a property object with default settings. 
     */
    ServiceProperty(): Base()
    {
    }

    ServiceProperty(const struct RTI_RoutingServiceProperty &native_property)
            : Base(native_property)
    {
    }


    /**
     * @brief Getter (see setter with the same name)
     */
    std::string cfg_file() const
    {
        return native().cfg_file == NULL ? "" : native().cfg_file;
    }

    /**    
     * @brief Path to an @product configuration file
     * 
     * @default empty string.
     */
    ServiceProperty& cfg_file(const std::string& filename)
    {
        DDS_String_replace(
                &native().cfg_file,
                filename.c_str());
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const std::vector<std::string>& cfg_strings() const
    {
        return cfg_strings_;
    }

    /**
     * @brief XML configuration represented as strings
     *
     * An array of strings that altogether make up an
     * XML document to configure @product. This parameter is used
     * only if ServiceProperty::cfg_file is empty.
     * 
     * The reason for using an array instead of one single string is to
     * get around the limited size of literal strings.
     * In general, if you create the XML string dynamically
     * the vector needs only one element.
     *
     * @default empty.
     */
    ServiceProperty& cfg_strings(
            const std::vector<std::string>& the_cfg_strings)
    {
        cfg_strings_ = the_cfg_strings;
        if (cfg_strings_.size() > 0) {
            if (!RTIOsapiHeap_reallocateArray(
                    (char ***) &native().cfg_strings,
                    cfg_strings_.size(),
                    char *)) {
                throw dds::core::OutOfResourcesError("cfg_strings native array");
            }
            for (uint32_t i = 0; i < cfg_strings_.size(); i++) {
            native().cfg_strings[i] = cfg_strings_[i].c_str();
            }
        }
        native().cfg_strings_count = static_cast<int>(cfg_strings_.size());
        
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    std::string service_name() const
    {
        return native().service_name == NULL ? "" : native().service_name;
    }

    /**
     * @brief The name of the @product configuration to run.
     *
     * This is the name used to find the &lt;routing_service&gt;
     * XML tag in the configuration file; the name that will
     * be used to refer to this execution in remote administration and
     * monitoring.
     *
     * @default empty string.
     */
    ServiceProperty& service_name(const std::string& name)
    {
        DDS_String_replace(
                &native().service_name,
                name.c_str());
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    std::string application_name() const
    {
        return native().application_name;
    }

    /**
     * @brief Assigns a name to the execution of the @product.
     *
     * Remote commands and status information will refer to the service using
     * this name.
     *
     * In addition, the name of DomainParticipants created by @product will be
     * based on this name.
     *
     * @default empty string.
     *          If no application name is specified, @product will use
     *          ServiceProperty::service_name.
     *
     */
    ServiceProperty& application_name(const std::string& name)
    {
        DDS_String_replace(
                &native().application_name,
                name.c_str());
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool enforce_xsd_validation() const
    {
        return (native().enforce_xsd_validation == DDS_BOOLEAN_TRUE)
                ? true
                : false;
    }

    /**
     * @brief Controls whether the service applies XSD validation to the loaded
     * configuration.
     *
     * @default true
     */
    ServiceProperty& enforce_xsd_validation(const bool enforce_xsd_validation)
    {
        native().enforce_xsd_validation = enforce_xsd_validation;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int domain_id_base() const
    {
        return native().domain_id_base;
    }

    /*e
     * @brief Value that is added to the domain IDs of the
     *        domain routes in the XML configuration.
     *
     * By using this, an XML file can use relative domain IDs.
     *
     * @default 0
     */
    ServiceProperty& domain_id_base(const int domain_id)
    {
        native().domain_id_base = domain_id;
        return *this;
    }
    
    /**
     * @brief Getter (see setter with the same name)
     */
    std::string plugin_search_path() const
    {
        return native().plugin_search_path == NULL
                ? ""
                : native().plugin_search_path;
    }

    /**
     * @brief This path is used to look for plugin libraries.
     *
     * If the plugin class libraries specified in the XML file don't
     * contain a full path, @product looks for them in this
     * directory if not NULL.
     *
     * @default "." (working directory)
     */
    ServiceProperty& plugin_search_path(const std::string& path)
    {
        DDS_String_replace(
                &native().plugin_search_path,
                path.c_str());
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool dont_start_service() const
    {
        return (native().dont_start_service == DDS_BOOLEAN_TRUE)
                ? true
                : false;
    }

    /**
     * @brief Set this to true to if you do not want @product enabled when
     *       RoutingServcie::start is called.
     *
     * @product can be enabled afterwards through remote administration.
     *
     * @default false
     */
    ServiceProperty& dont_start_service(const bool not_start)
    {
        native().dont_start_service = not_start
                ? DDS_BOOLEAN_TRUE
                : DDS_BOOLEAN_FALSE;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_administration() const
    {
        return (native().enable_administration == DDS_BOOLEAN_TRUE)
                ? true
                : false;
    }

    /**
     * @brief Set this to true to enable remote administration
     * or false to disable it.
     *
     * @default false
     */
    ServiceProperty& enable_administration(const bool enable)
    {
        native().enable_administration = enable
                ? DDS_BOOLEAN_TRUE
                : DDS_BOOLEAN_FALSE;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int administration_domain_id() const
    {
        return native().administration_domain_id;
    }

    /**
     * @brief If ServiceProperty::enable_administration is true, this is
     * the domain ID to use for remote administration.
     *
     * Takes precedence over the XML configuration.
     * If ServiceProperty::enable_administration is false, this value is not used
     * even if remote administration is enabled in the XML configuration.
     *
     * @default 0
     */
    ServiceProperty& administration_domain_id(const int domain_id)
    {
        native().administration_domain_id = domain_id;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_monitoring() const
    {
        return native().enable_monitoring == DDS_BOOLEAN_TRUE
                ? true
                : false;
    }

    /**
     * @brief Set it to true to enable remote monitoring
     * or false to disable it.
     *
     * @default false
     */
    ServiceProperty& enable_monitoring(const bool& enable)
    {
        native().enable_monitoring = enable
                ? DDS_BOOLEAN_TRUE
                : DDS_BOOLEAN_FALSE;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int monitoring_domain_id() const
    {
        return native().monitoring_domain_id;
    }

    /**
     * @brief If ServiceProperty::enable_monitoring is true, this is
     * the domain ID to use for remote monitoring.
     *
     * Takes precedence over the XML configuration.
     * If ServiceProperty::enable_monitoring is false, this value is not used,
     * even if remote monitoring is enabled in the XML configuration.
     *
     * @default 0
     */
    ServiceProperty& monitoring_domain_id(const int& domain_id)
    {
        native().monitoring_domain_id = domain_id;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool skip_default_files() const
    {
        return (native().skip_default_files == DDS_BOOLEAN_TRUE)
                ? true
                : false;
    }

    /**
     * @brief Set it to true to avoid loading the
     * standard files usually loaded by @product.
     *
     * Only the configuration in ServiceProperty::cfg_file or
     * ServiceProperty::cfg_strings will be loaded.
     *
     * @default false
     */
    ServiceProperty& skip_default_files(const bool& skip)
    {
        native().skip_default_files = skip
                ? DDS_BOOLEAN_TRUE
                : DDS_BOOLEAN_FALSE;
        return *this;
    }


    /**
     * @brief Getter (see setter with the same name)
     */
    bool identify_execution() const
    {
        return (native().identify_execution == DDS_BOOLEAN_TRUE)
                ? true
                : false;
    }

     /**
     * @brief Set this to true to append the host name and process ID
     * to the @product execution name.
     *
     * Used to get unique names for remote administration and monitoring.
     *
     * @default false
     */
    ServiceProperty& identify_execution(const bool& identify)
    {
        native().identify_execution = identify
                ? DDS_BOOLEAN_TRUE
                : DDS_BOOLEAN_FALSE;
        return *this;
    }    
    
    /**
     * @brief Getter (see setter with the same name)
     */
    std::string license_file_name() const
    {
        return native().license_file_name == NULL? "" 
                : native().license_file_name;
    }

    /**
     * @brief Path to an @product license file.
     *
     * If not empty, this file is checked for a valid license; otherwise,
     * default location will be used. This parameter is not used in
     * unlicensed versions.
     *
     * @default empty string.
     */
    ServiceProperty& license_file_name(const std::string& filename)
    {
        DDS_String_replace(
                &native().license_file_name,
                filename.c_str());
        return *this;
    }    

    /**
     * @brief Getter (see setter with the same name)
     */
    std::map<std::string, std::string> user_environment() const
    {
        std::map<std::string, std::string> properties;

        PropertyAdapter::add_properties_from_native(
                properties,
                &native().user_environment);

        return properties;
    }

    /**
     * @brief Dictionary of user variables.
     * The dictionary provides a parallel way to expand XML configuration
     * variables in the form $(my_var), when they are not defined in the
     * environment.
     *
     * @default empty
     */
    ServiceProperty& user_environment(
            const std::map<std::string, std::string>& user_environment)
    {        
        rti::routing::PropertyAdapter::add_properties_to_native(                
                &native().user_environment,
                user_environment);

        return *this;
    }

private:
    std::vector<std::string> cfg_strings_;
};

}}

#endif // RTI_ROUTING_ROUTING_SERVICE_PROPERTY_HPP_
