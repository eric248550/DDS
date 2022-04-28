/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_RECORDING_SERVICE_HPP_
#define RTI_RECORDING_RECORDING_SERVICE_HPP_

#include <dds/core/Reference.hpp>
#include <rti/config/Logger.hpp>

#include <rti/recording/ServiceProperty.hpp>
#include <rti/recording/detail/RecordingServiceImpl.hpp>

namespace rti { namespace recording {

/*e \defgroup RTI_RecordingServiceLibModule RTI Recording Service API
 *
 * @brief @product  can be deployed as a native library linked into your
 * application in select architectures.
 *
 * This API allows you to create, configure and start @product instances from
 * your application.
 *
 * The following code shows the typical use of the API:
 *
 * \code
 *
 * int main ()
 * {
 *     rti::recording::RecordingService service(
 *             rti::recording::ServiceProperty()
 *             .cfg_file("MyRecorder.xml")
 *             .cfg_name("MyRecorder"));
 *     ...
 *
 *     service.start();
 *
 *     while(keep_running) {
 *         sleep();
 *         ...
 *     }
 *
 *     return 0;
 * }
 *
 * \endcode
 *
 * Instead of a file, you can use XML strings to configure @product.
 * See ServiceProperty for more information.
 * <p>
 * To build your application you need to link with the @product native library
 * in <b> &lt;@ndds home&gt;/bin/&lt;architecture&gt;/ </b>.
 *
 * ### Development Requirements
 *
 * |                 | Unix-based Systems                      | Windows Systems           |
 * | --------------: | :----------------:                      | :-------------:           |
 * | Shared Libraries| libnddscpp2.so                          | nddscpp2.dll              |
 * | Shared Libraries| librtiroutingservice.so                 | rtiroutingservice.dll     |
 * | ^               | librtirsinfrastructure.so               | rtirsinfrastructure.dll   |
 * | ^               | librtidlc.so                            | rtidlc.dll                |
 * | ^               | libnddsmetp.so                          | nddsmetp.dll              |
 * | ^               | libnddsc.so                             | nddsc.dll                 |
 * | ^               | librtixml2.so                           | rtixml2.dll               |
 * | ^               | libnddscore.so                          | nddscore.dll              |
 * | Headers         | rti/routing/RoutingService.hpp          ||
 *
 */

/** \ingroup RTI_RoutingServiceLibModule
 *
 * @brief The @product.
 *
 */
class RecordingService : public dds::core::Reference<RecordingServiceImpl> {
public:
    typedef dds::core::Reference<RecordingServiceImpl> Base;
    OMG_DDS_REF_TYPE_NOTYPENAME(
            RecordingService,
            dds::core::Reference,
            RecordingServiceImpl);

    /**
     * @brief Creates a @product instance
     *
     * @param[in] property
     *            The property to configure @product instance.
     *
     */
    RecordingService(const ServiceProperty& property)
            : Base(new RecordingServiceImpl(property))
    {
        this->delegate()->remember_reference(this->delegate());
    }

    explicit RecordingService(Base::DELEGATE_REF_T reference) : Base(reference)
    {
        if (this->delegate()) {
            this->delegate()->remember_reference(this->delegate());
        }
    }

    /**
     * @brief Starts @product.
     *
     * This is a non-blocking operation. @product will create its own set of
     * threads to perform its tasks.
     */
    void start()
    {
        this->delegate()->start();
    }

    /**
     * @brief Stops @product.
     *
     * This operation will bloc the instance is fully stopped.
     */
    void stop()
    {
        this->delegate()->stop();
    }


    /**
     * @brief Finalizes global resources that @product requires to operate.
     *
     * This operation releases resources specific to @product only. @ndds
     * global state shall be released separately through the
     * DomainParticipantFactory's finalize_instance().
     *
     * This operation should be called by your application only upon exit, after
     * all service instances have been deleted. Calling it at a different time may
     * cause the application to crash.
     *
     * @mtsafety unsafe. Applications are not allowed to call this operation
     * concurrently
     *
     * @throw std::exception
     */
    static void finalize_globals()
    {
        RecordingServiceImpl::finalize_globals();
    }
};

/** \ingroup RTI_RoutingServiceLibModule
 *
 * @brief The singleton type used to configure @product verbosity
 *
 * For configuring other aspects such as output file, print format or
 * RTI Connext specific logging, use rti::config::Logger.
 *
 */
class RECORDERDllExport Logger
{
public:

    typedef rti::config::Verbosity Verbosity;
    typedef rti::config::LogCategory LogCategory;
    typedef rti::config::LoggerMode LoggerMode;
    typedef rti::config::PrintFormat PrintFormat;

    static Logger& instance();

    /**
     * @brief Sets the verbosity for the log messages generated at the
     * @product level.
     *
     * @param[in] verbosity
     *            The verbosity of the service logs
     */
    void verbosity(rti::config::Verbosity verbosity);

    /**
     * @brief Getter for the same attribute
     *
     * @see verbosity(rti::config::Verbosity)
     */
    rti::config::Verbosity verbosity();

    virtual ~Logger();

private:

    Logger();

     // Disable copy
    Logger(const Logger&);
    Logger& operator=(const Logger&);
};

}}

#endif // RTI_RECORDING_RECORDING_SERVICE_HPP_
