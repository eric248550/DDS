/* 
 (c) Copyright, Real-Time Innovations, 2017-
 All rights reserved.
 
 No duplications, whole or partial, manual or electronic, may be made without 
 express written permission.  Any such copies, or revisions thereof, must 
 display this notice unaltered.
 
 This code contains trade secrets of Real-Time Innovations, Inc.
*/

#ifndef HPP_ROUTING_LOG_LOG_CONFIG_HPP_
#define HPP_ROUTING_LOG_LOG_CONFIG_HPP_

#include <cstdio>
#include <cstdarg>

#include "log/log_common.h"
#include "routingservice/routingservice_log.h"

#include <rti/service/log/LogConfig.hpp>

namespace rti { namespace routing { namespace log {

class LogConfig : public rti::service::log::LogConfig {
public:

    static rti::routing::log::LogConfig& instance()
    {
        static rti::routing::log::LogConfig singleton;
        return singleton;
    }
   
     
    void router_instrumentation_mask(RTILogBitmap logmask)
    {
        ROUTERLog_setBitmaps(mask_all(), logmask);
    }
    
    void update_router_bitmaps()
    {
        router_instrumentation_mask(instrumentation_mask_);
    }
    
private:

    // Constructor is private: this class is a singleton
    LogConfig()
    {
        update_router_bitmaps();
    }
};

}}} // rti::routing::log

#endif /* HPP_ROUTING_LOG_LOG_CONFIG_HPP_ */
