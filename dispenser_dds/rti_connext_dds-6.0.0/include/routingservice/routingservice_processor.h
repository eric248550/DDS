/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)routingservice_processor.h    generated by: makeheader    Thu Feb 28 22:15:02 2019
 *
 *		built from:	processor.ifc
 */

#ifndef routingservice_processor_h
#define routingservice_processor_h



  #include "routingservice/routingservice_infrastructure.h"
  #include "routingservice/routingservice_adapter_new.h"
  
  #ifdef __cplusplus
      extern "C" {
  #endif


struct RTI_RoutingServiceRouteImpl;


typedef struct RTI_RoutingServiceRouteImpl RTI_RoutingServiceRoute;

extern ROUTERDllExport
int RTI_RoutingServiceRoute_get_input_count(RTI_RoutingServiceRoute * self);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamReaderExt * 
RTI_RoutingServiceRoute_get_input_at(
        RTI_RoutingServiceRoute * self,
        int index);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamReaderExt * 
RTI_RoutingServiceRoute_lookup_input_by_name(
        RTI_RoutingServiceRoute * self,
        const char * input_name);

extern ROUTERDllExport
int RTI_RoutingServiceRoute_is_input_active(
        RTI_RoutingServiceRoute * self,
        struct RTI_RoutingServiceStreamReaderExt * stream_reader);

extern ROUTERDllExport
const struct RTI_RoutingServiceStreamInfo *
RTI_RoutingServiceRoute_get_input_stream_info(
        RTI_RoutingServiceRoute * self,
        struct RTI_RoutingServiceStreamReaderExt * stream_reader);

extern ROUTERDllExport
int RTI_RoutingServiceRoute_get_output_count(RTI_RoutingServiceRoute * self);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamWriterExt * 
RTI_RoutingServiceRoute_get_output_at(
        RTI_RoutingServiceRoute * self,
        int index);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamWriterExt * 
RTI_RoutingServiceRoute_lookup_output_by_name(
        RTI_RoutingServiceRoute * self,
        const char * output_name);

extern ROUTERDllExport
const struct RTI_RoutingServiceStreamInfo *
RTI_RoutingServiceRoute_get_output_stream_info(
        RTI_RoutingServiceRoute * self,
        struct RTI_RoutingServiceStreamWriterExt * stream_writer);

extern ROUTERDllExport
void RTI_RoutingServiceRoute_wakeup_route(
        RTI_RoutingServiceRoute *route);

extern ROUTERDllExport
int RTI_RoutingServiceRoute_get_session_period(
        RTI_RoutingServiceRoute * self);

extern ROUTERDllExport
void RTI_RoutingServiceRoute_set_session_period(
        RTI_RoutingServiceRoute * self,
        unsigned long long period_millis);

extern ROUTERDllExport
const char *
RTI_RoutingServiceRoute_get_input_name(
        RTI_RoutingServiceRoute * self,
        struct RTI_RoutingServiceStreamReaderExt * stream_reader);

extern ROUTERDllExport
const char *
RTI_RoutingServiceRoute_get_output_name(
        RTI_RoutingServiceRoute * self,
        struct RTI_RoutingServiceStreamWriterExt * stream_writer);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamReaderExt *
RTI_RoutingServiceRoute_get_first_input(
        RTI_RoutingServiceRoute *self);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamReaderExt *
RTI_RoutingServiceRoute_get_next_input(
        RTI_RoutingServiceRoute *self,
        struct RTI_RoutingServiceStreamReaderExt *input);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamWriterExt *
RTI_RoutingServiceRoute_get_first_output(
        RTI_RoutingServiceRoute *self);

extern ROUTERDllExport
struct RTI_RoutingServiceStreamWriterExt *
RTI_RoutingServiceRoute_get_next_output(
        RTI_RoutingServiceRoute *self,
        struct RTI_RoutingServiceStreamWriterExt *output);


typedef enum {
    
    RTI_ROUTING_SERVICE_ROUTE_EVENT_NONE = 0,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_INPUT_ENABLED,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_INPUT_DISABLED,    
    RTI_ROUTING_SERVICE_ROUTE_EVENT_OUTPUT_ENABLED,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_OUTPUT_DISABLED,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_STARTED,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_STOPPED,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_RUNNING,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_ROUTE_PAUSED,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_DATA_ON_INPUTS,   
    RTI_ROUTING_SERVICE_ROUTE_EVENT_PERIODIC_ACTION,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_OUTPUT_STREAM_REQUEST,   
    RTI_ROUTING_SERVICE_ROUTE_EVENT_WAKEUP,
    RTI_RoutingServiceRouteEventKind_COUNT,
    RTI_ROUTING_SERVICE_ROUTE_EVENT_ALL = 0xffffffff,
            
} RTI_RoutingServiceRouteEventKind;


struct RTI_RoutingServiceRouteEventImpl;


typedef struct RTI_RoutingServiceRouteEventImpl RTI_RoutingServiceRouteEvent;

extern ROUTERDllExport 
RTI_RoutingServiceRouteEventKind RTI_RoutingServiceRouteEvent_get_kind(
        RTI_RoutingServiceRouteEvent * self);

extern ROUTERDllExport 
RTI_RoutingServiceRoute * RTI_RoutingServiceRouteEvent_get_route(
        RTI_RoutingServiceRouteEvent * self);

extern ROUTERDllExport 
void * RTI_RoutingServiceRouteEvent_get_event_data(
        RTI_RoutingServiceRouteEvent * self);

extern ROUTERDllExport 
void * RTI_RoutingServiceRouteEvent_get_affected_entity(
        RTI_RoutingServiceRouteEvent * self);

struct RTI_RoutingServiceProcessor;


typedef void (*RTI_RoutingServiceProcessor_OnRouteEventFcn)(
        void * processor_data,
        RTI_RoutingServiceRouteEvent * route_event,
        RTI_RoutingServiceEnvironment * env);

 
typedef void (*RTI_RoutingServiceProcessor_UpdateFcn)(
        void * processor_data,
        const struct RTI_RoutingServiceProperties * properties,
        RTI_RoutingServiceEnvironment * env);

 
struct RTI_RoutingServiceProcessor{
    
    /*i @brief Handles event processing (required. */
    RTI_RoutingServiceProcessor_OnRouteEventFcn on_route_event;
    /*i @brief Handles configuration changes in a Processor (optional). */
    RTI_RoutingServiceProcessor_UpdateFcn update;
    
    /*i @brief implementation data */
    void * processor_data;
    
};


struct RTI_RoutingServiceProcessorPlugin;


typedef struct RTI_RoutingServiceProcessorPlugin *
(*RTI_RoutingServiceProcessorPlugin_CreateFcn)(
        const struct RTI_RoutingServiceProperties * properties,
        RTI_RoutingServiceEnvironment * env);


typedef void (*RTI_RoutingServiceProcessorPlugin_DeleteFcn)(
        struct RTI_RoutingServiceProcessorPlugin * plugin,
        RTI_RoutingServiceEnvironment * env);

 
typedef struct RTI_RoutingServiceProcessor *
(*RTI_RoutingServiceProcessorPlugin_CreateProcessorFcn)(
        void * processor_plugin_data,
        RTI_RoutingServiceRoute * route,
        const struct RTI_RoutingServiceProperties * properties,
        RTI_RoutingServiceEnvironment * env);

 
typedef void (*RTI_RoutingServiceProcessorPlugin_DeleteProcessorFcn)(
        void * processor_plugin_data,
        struct RTI_RoutingServiceProcessor * processor,
        RTI_RoutingServiceRoute * route,
        RTI_RoutingServiceEnvironment * env);


struct RTI_RoutingServiceProcessorPlugin {
    int _init;
    struct RTI_RoutingServiceVersion _rs_version;

    /*i \brief The version of this ProcessorPlugin */
    struct RTI_RoutingServiceVersion plugin_version;

    /*i \brief Handles the deletion of the ProcessorPlugin. */
    RTI_RoutingServiceProcessorPlugin_DeleteFcn
        plugin_delete;
    /*i \brief Handles the creation of Processors. */
    RTI_RoutingServiceProcessorPlugin_CreateProcessorFcn
        create_processor;
    /*i \brief Handles the deletion of Processors. */
    RTI_RoutingServiceProcessorPlugin_DeleteProcessorFcn
        delete_processor;

    /*i @brief A place for Processor implementors to keep a pointer to data that 
        may be needed by the implementation. */
    void * processor_plugin_data;   
};



#define RTI_ROUTING_SERVICE_PROCESSOR_PLUGIN_INIT_NUMBER (8765432)

/*i \ingroup RTI_RoutingServiceProcessorModule
 * 
 * @brief Initializes the ProcessorPlugin structure.
 * 
 * This macro must be called to initialize the
 * 
 * return value of RTI_RoutingServiceProcessorPlugin_CreateFcn
 * @param processor Pointer to the ProcessorPlugin structure
 * 
 * @see RTI_RoutingServiceProcessorPlugin#CreateFcn
*/
#define RTI_RoutingServiceProcessorPlugin_initialize(plugin)                  \
{                                                                             \
    struct RTI_RoutingServiceVersion rsVersion = RTI_ROUTING_SERVICE_VERSION; \
    struct RTI_RoutingServiceVersion processorVersion = {0,0,0,0};            \
    (plugin)->_init = RTI_ROUTING_SERVICE_PROCESSOR_PLUGIN_INIT_NUMBER;       \
    (plugin)->_rs_version = rsVersion;                                        \
    (plugin)->plugin_version = processorVersion;                              \
    (plugin)->plugin_delete = 0;                                              \
    (plugin)->create_processor = 0;                                           \
    (plugin)->delete_processor = 0;                                           \
    (plugin)->processor_plugin_data = 0;                                      \
}



  #ifdef __cplusplus
    }	/* extern "C" */
  #endif

#endif /* routingservice_processor_h */
