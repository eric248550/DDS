/*
 * $Id$
 *
 * (c) Copyright, Real-Time Innovations, 2016-.
 * All rights reserved.
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef HPP_SERVICE_SERVICEPROPERTY_HPP_
#define HPP_SERVICE_SERVICEPROPERTY_HPP_

#include "stdio.h"
#include "stdlib.h"
#include <string>
#include <stdint.h>
#include <map>

#include "osapi/osapi_type.h"

#include "routingservice/routingservice_infrastructure.h"
#include "routingservice/routingservice_service.h"

#include <dds/core/SafeEnumeration.hpp>

namespace rti { namespace recording {

/** \ingroup RTI_RecordingServiceLibModule
 *
 * The definition of the rti::recording::ApplicationRoleKind
 *
 * It indicates the operation mode of @product.
 */
struct ApplicationRoleKind_def {
    /**
     * @brief The underlying \p enum type
     */
    enum type {
        /**
         * @brief Record mode
         */
        RECORD_APPLICATION,
        /**
         * @brief Replay mode
         */
        REPLAY_APPLICATION,
        /**
         * @brief Converter mode
         */
        CONVERTER_APPLICATION,
        /*i
         * @brief Internal use only
         */
        XML_CONVERTER_APPLICATION,
        /*i
         */
        count_
    };
};

typedef dds::core::safe_enum<ApplicationRoleKind_def> ApplicationRoleKind;

/*i
 * @brief Internal use only
 */
struct XmlConverterRoleKind_def {

    enum type {
        RECORD_CONVERT,
        REPLAY_CONVERT,
        count_
    };
};

typedef dds::core::safe_enum<XmlConverterRoleKind_def> XmlConverterRoleKind;

/** \ingroup RTI_RecordingServiceLibModule
 *
 * @brief Configuration for a @product object.
 *
 */
class ServiceProperty {
public:
    /**
     * @brief Creates a property object with default settings.
     */
    ServiceProperty() :
        cfg_file_(""),
        service_name_(""),
        application_name_(""),
        domain_id_base_(0),
        enable_administration_(false),
        administration_domain_id_(0),
        enable_monitoring_(false),
        monitoring_domain_id_(0),
        application_role_(ApplicationRoleKind::RECORD_APPLICATION),
        enforce_xsd_validation_(true),
        ignore_default_files_(false),
        output_cfg_file_(""),
        converter_role_(XmlConverterRoleKind::RECORD_CONVERT)

    {

    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const std::string& cfg_file() const
    {
        return cfg_file_;
    }

    /**
     * @brief Path to an @product configuration file
     *
     * @default empty string.
     */
    ServiceProperty& cfg_file(const std::string & cfg_file)
    {
        cfg_file_ = cfg_file;

        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const std::string & service_name() const
    {
        return service_name_;
    }

    /**
     * @brief The name of the @product configuration to run.
     *
     * This is the name used to find the service XML tag in the configuration
     * file; the name that will  be used to refer to this execution in remote
     * administration and
     * monitoring.
     *
     * @default empty string.
     */
    ServiceProperty& service_name(const std::string & service_name)
    {
        service_name_ = service_name;

        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const std::string & application_name() const
    {
        return application_name_;
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
    ServiceProperty& application_name(const std::string & application_name)
    {
        application_name_ = application_name;

        return *this;
    }


    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t domain_id_base() const
    {
        return domain_id_base_;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool enforce_xsd_validation() const
    {
        return enforce_xsd_validation_;
    }

    /**
     * @brief Controls whether the service applies XSD validation to the loaded
     * configuration.
     *
     * @default true
     */
    ServiceProperty& enforce_xsd_validation(bool enforce)
    {
        enforce_xsd_validation_ = enforce;

        return *this;
    }

    /**
     * @brief Value that is added to the domain IDs of the
     *        domain routes in the XML configuration.
     *
     * By using this, an XML file can use relative domain IDs.
     *
     * @default 0
     */
    ServiceProperty& domain_id_base(int32_t domain_id)
    {
        domain_id_base_ = domain_id;

        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_administration() const
    {
        return enable_administration_;
    }

    /**
     * @brief Set this to true to enable remote administration
     * or false to disable it.
     *
     * @default false
     */
    ServiceProperty& enable_administration(bool enable_administration)
    {
        enable_administration_ = enable_administration;

        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t administration_domain_id() const
    {
        return administration_domain_id_;
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
    ServiceProperty& administration_domain_id(int32_t domain_id)
    {
        administration_domain_id_ = domain_id;

        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool enable_monitoring() const
    {
        return enable_monitoring_;
    }

    /**
     * @brief Set it to true to enable remote monitoring
     * or false to disable it.
     *
     * @default false
     */
    ServiceProperty& enable_monitoring(bool enable_monitoring)
    {
        enable_monitoring_ = enable_monitoring;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    int32_t monitoring_domain_id() const
    {
        return monitoring_domain_id_;
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
    ServiceProperty& monitoring_domain_id(int32_t domain_id)
    {
        monitoring_domain_id_ = domain_id;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const ApplicationRoleKind& application_role() const
    {
        return application_role_;
    }

    /**
     * @brief Selects the operation mode of the service
     *
     * @see ApplicationRoleKind
     */
    ServiceProperty& application_role(ApplicationRoleKind application_role)
    {
        application_role_ = application_role;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    bool ignore_default_files() const
    {
        return ignore_default_files_;
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
    ServiceProperty& ignore_default_files(bool ignore)
    {
        ignore_default_files_ = ignore;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const std::string& license_file() const
    {
        return license_file_;
    }

    /**
     * @brief Path to an RTI Connext license file. This field is only used by
     * license-managed versions of the tool.
     *
     * @default empty string.
     */
    ServiceProperty& license_file(const std::string& license_file)
    {
        license_file_ = license_file;
        return *this;
    }

    /*i
     * @brief Internal use only
     */
    const std::string output_cfg_file() const
    {
        return output_cfg_file_;
    }

    /*i
     * @brief Internal use only
     */
    ServiceProperty& output_cfg_file(
            const std::string & output_cfg_file)
    {
        output_cfg_file_ = output_cfg_file;
        return *this;
    }

    /*i
     * @brief Internal use only
     */
    XmlConverterRoleKind converter_role() const
    {
        return converter_role_;
    }

    /*i
     * @brief Internal use only
     */
    ServiceProperty& converter_role(
            const XmlConverterRoleKind & converter_role)
    {
        converter_role_ = converter_role;
        return *this;
    }

    /**
     * @brief Getter (see setter with the same name)
     */
    const std::map<std::string, std::string>& user_environment() const
    {
        return user_env_;
    }

    /**
     * @brief Non-const getter for modification that can be used to add
     * elements individually. (see setter with the same name)
     */
    std::map<std::string, std::string>& user_environment()
    {
        return user_env_;
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
        user_env_ = user_environment;

        return *this;
    }

private:
    std::string cfg_file_;
    //std::string cfg_strings[] ?
    std::string service_name_;
    std::string application_name_;
    int32_t domain_id_base_;
    bool enable_administration_;
    int32_t administration_domain_id_;
    bool enable_monitoring_;
    int32_t monitoring_domain_id_;
    ApplicationRoleKind application_role_;
    bool enforce_xsd_validation_;
    bool ignore_default_files_;
    std::string license_file_;
    // Specific to XML conversion
    std::string output_cfg_file_;
    XmlConverterRoleKind converter_role_;
    std::map<std::string, std::string> user_env_;
};


}
} /* namespace rti::recording */

#endif /* HPP_SERVICE_SERVICEPROPERTY_HPP_ */
