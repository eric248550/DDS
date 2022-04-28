/*
 * (c) Copyright, Real-Time Innovations, 2017.
 * All rights reserved.
 *
 * No duplications, whole or partial, manual or electronic, may be made
 * without express written permission.  Any such copies, or
 * revisions thereof, must display this notice unaltered.
 * This code contains trade secrets of Real-Time Innovations, Inc.
 */

#ifndef RTI_RECORDING_RECORDING_SERVICE_IMPL_HPP_
#define RTI_RECORDING_RECORDING_SERVICE_IMPL_HPP_

#include "recordingservice/recordingservice_dll.h"

#include <dds/core/refmacros.hpp>
#include <rti/core/detail/SelfReference.hpp>
#include <rti/recording/ServiceProperty.hpp>

namespace rti { namespace recording{

namespace  service {
class Service;
}

class Application;

class RECORDERDllExport RecordingServiceImpl
        : public rti::core::detail::RetainableType<RecordingServiceImpl> {
public:

    RecordingServiceImpl(const ServiceProperty& property);
    ~RecordingServiceImpl();

    void start();

    void stop();

    static void initialize_globals();
    static void finalize_globals();

private:
    friend class rti::recording::Application;
    RecordingServiceImpl(
            const ServiceProperty& property,
            const void *shutdown_hook);

    rti::recording::service::Service *impl_;
};

}}

#endif // RTI_RECORDING_RECORDING_SERVICE_IMPL_HPP_
