

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from water.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef waterPlugin_215294087_h
#define waterPlugin_215294087_h

#include "water.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#define WaterDispenserPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

#define WaterDispenserPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
#define WaterDispenserPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

#define WaterDispenserPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
#define WaterDispenserPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

/* --------------------------------------------------------------------------------------
Support functions:
* -------------------------------------------------------------------------------------- */

NDDSUSERDllExport extern WaterDispenser*
WaterDispenserPluginSupport_create_data_w_params(
    const struct DDS_TypeAllocationParams_t * alloc_params);

NDDSUSERDllExport extern WaterDispenser*
WaterDispenserPluginSupport_create_data_ex(RTIBool allocate_pointers);

NDDSUSERDllExport extern WaterDispenser*
WaterDispenserPluginSupport_create_data(void);

NDDSUSERDllExport extern RTIBool 
WaterDispenserPluginSupport_copy_data(
    WaterDispenser *out,
    const WaterDispenser *in);

NDDSUSERDllExport extern void 
WaterDispenserPluginSupport_destroy_data_w_params(
    WaterDispenser *sample,
    const struct DDS_TypeDeallocationParams_t * dealloc_params);

NDDSUSERDllExport extern void 
WaterDispenserPluginSupport_destroy_data_ex(
    WaterDispenser *sample,RTIBool deallocate_pointers);

NDDSUSERDllExport extern void 
WaterDispenserPluginSupport_destroy_data(
    WaterDispenser *sample);

NDDSUSERDllExport extern void 
WaterDispenserPluginSupport_print_data(
    const WaterDispenser *sample,
    const char *desc,
    unsigned int indent);

/* ----------------------------------------------------------------------------
Callback functions:
* ---------------------------------------------------------------------------- */

NDDSUSERDllExport extern PRESTypePluginParticipantData 
WaterDispenserPlugin_on_participant_attached(
    void *registration_data, 
    const struct PRESTypePluginParticipantInfo *participant_info,
    RTIBool top_level_registration, 
    void *container_plugin_context,
    RTICdrTypeCode *typeCode);

NDDSUSERDllExport extern void 
WaterDispenserPlugin_on_participant_detached(
    PRESTypePluginParticipantData participant_data);

NDDSUSERDllExport extern PRESTypePluginEndpointData 
WaterDispenserPlugin_on_endpoint_attached(
    PRESTypePluginParticipantData participant_data,
    const struct PRESTypePluginEndpointInfo *endpoint_info,
    RTIBool top_level_registration, 
    void *container_plugin_context);

NDDSUSERDllExport extern void 
WaterDispenserPlugin_on_endpoint_detached(
    PRESTypePluginEndpointData endpoint_data);

NDDSUSERDllExport extern void    
WaterDispenserPlugin_return_sample(
    PRESTypePluginEndpointData endpoint_data,
    WaterDispenser *sample,
    void *handle);    

NDDSUSERDllExport extern RTIBool 
WaterDispenserPlugin_copy_sample(
    PRESTypePluginEndpointData endpoint_data,
    WaterDispenser *out,
    const WaterDispenser *in);

/* ----------------------------------------------------------------------------
(De)Serialize functions:
* ------------------------------------------------------------------------- */

NDDSUSERDllExport extern RTIBool
WaterDispenserPlugin_serialize_to_cdr_buffer(
    char * buffer,
    unsigned int * length,
    const WaterDispenser *sample); 

NDDSUSERDllExport extern RTIBool
WaterDispenserPlugin_serialize_to_cdr_buffer_ex(
    char *buffer,
    unsigned int *length,
    const WaterDispenser *sample,
    DDS_DataRepresentationId_t representation);

NDDSUSERDllExport extern RTIBool 
WaterDispenserPlugin_deserialize(
    PRESTypePluginEndpointData endpoint_data,
    WaterDispenser **sample, 
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_sample, 
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern RTIBool
WaterDispenserPlugin_deserialize_from_cdr_buffer(
    WaterDispenser *sample,
    const char * buffer,
    unsigned int length);    
#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport extern DDS_ReturnCode_t
WaterDispenserPlugin_data_to_string(
    const WaterDispenser *sample,
    char *str,
    DDS_UnsignedLong *str_size, 
    const struct DDS_PrintFormatProperty *property);    
#endif

NDDSUSERDllExport extern unsigned int 
WaterDispenserPlugin_get_serialized_sample_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

/* --------------------------------------------------------------------------------------
Key Management functions:
* -------------------------------------------------------------------------------------- */
NDDSUSERDllExport extern PRESTypePluginKeyKind 
WaterDispenserPlugin_get_key_kind(void);

NDDSUSERDllExport extern unsigned int 
WaterDispenserPlugin_get_serialized_key_max_size(
    PRESTypePluginEndpointData endpoint_data,
    RTIBool include_encapsulation,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern unsigned int 
WaterDispenserPlugin_get_serialized_key_max_size_for_keyhash(
    PRESTypePluginEndpointData endpoint_data,
    RTIEncapsulationId encapsulation_id,
    unsigned int current_alignment);

NDDSUSERDllExport extern RTIBool 
WaterDispenserPlugin_deserialize_key(
    PRESTypePluginEndpointData endpoint_data,
    WaterDispenser ** sample,
    RTIBool * drop_sample,
    struct RTICdrStream *stream,
    RTIBool deserialize_encapsulation,
    RTIBool deserialize_key,
    void *endpoint_plugin_qos);

NDDSUSERDllExport extern
struct RTIXCdrInterpreterPrograms *WaterDispenserPlugin_get_programs();

/* Plugin Functions */
NDDSUSERDllExport extern struct PRESTypePlugin*
WaterDispenserPlugin_new(void);

NDDSUSERDllExport extern void
WaterDispenserPlugin_delete(struct PRESTypePlugin *);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* waterPlugin_215294087_h */

