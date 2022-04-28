

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from water.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef water_215294087_h
#define water_215294087_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_c_h
#include "ndds/ndds_c.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern const char *WaterDispenserTYPENAME;

typedef struct WaterDispenser {

    DDS_Char *   UploadTime ;
    DDS_Long   Hot_Valve ;
    DDS_Long   Cooling ;
    DDS_Long   Usage_L ;
    DDS_Long   Warm_Valve ;
    DDS_Long   ColdTemp_Insulation ;
    DDS_Long   Status ;
    DDS_Long   Usage_MT ;
    DDS_Long   WaterLevel ;
    DDS_Long   ErrorCode ;
    DDS_Long   HotTemp_Insulation ;
    DDS_Char *   Device_ID ;
    DDS_Long   Refilling ;
    DDS_Long   SavingPower ;
    DDS_LongLong   TimeStamp ;
    DDS_Long   Heating ;
    DDS_Long   Cold_Valve ;
    DDS_Long   WarmTemp ;
    DDS_Long   ColdTemp ;
    DDS_Long   Usage_CC ;
    DDS_Long   HotTemp ;
    DDS_Long   Sterilizing ;
    DDS_Char *   Hardware ;
    DDS_Char *   Mac_Address ;
    DDS_Long   TDS ;
    DDS_LongLong   SendTime ;

} WaterDispenser ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* WaterDispenser_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *WaterDispenser_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *WaterDispenser_get_sample_access_info(void);
#endif

DDS_SEQUENCE(WaterDispenserSeq, WaterDispenser);

NDDSUSERDllExport
RTIBool WaterDispenser_initialize(
    WaterDispenser* self);

NDDSUSERDllExport
RTIBool WaterDispenser_initialize_ex(
    WaterDispenser* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool WaterDispenser_initialize_w_params(
    WaterDispenser* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool WaterDispenser_finalize_w_return(
    WaterDispenser* self);

NDDSUSERDllExport
void WaterDispenser_finalize(
    WaterDispenser* self);

NDDSUSERDllExport
void WaterDispenser_finalize_ex(
    WaterDispenser* self,RTIBool deletePointers);

NDDSUSERDllExport
void WaterDispenser_finalize_w_params(
    WaterDispenser* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void WaterDispenser_finalize_optional_members(
    WaterDispenser* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool WaterDispenser_copy(
    WaterDispenser* dst,
    const WaterDispenser* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* water */

