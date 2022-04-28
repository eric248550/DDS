

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from water.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_c_h
#include "ndds/ndds_c.h"
#endif
#ifndef dds_c_log_infrastructure_h                      
#include "dds_c/dds_c_infrastructure_impl.h"       
#endif 

#ifndef cdr_type_h
#include "cdr/cdr_type.h"
#endif    

#ifndef osapi_heap_h
#include "osapi/osapi_heap.h" 
#endif
#else
#include "ndds_standalone_type.h"
#endif

#include "water.h"

#ifndef NDDS_STANDALONE_TYPE
#include "waterPlugin.h"
#endif

/* ========================================================================= */
const char *WaterDispenserTYPENAME = "WaterDispenser";

#ifndef NDDS_STANDALONE_TYPE
DDS_TypeCode* WaterDispenser_get_typecode()
{
    static RTIBool is_initialized = RTI_FALSE;

    static DDS_TypeCode WaterDispenser_g_tc_UploadTime_string = DDS_INITIALIZE_STRING_TYPECODE((32));
    static DDS_TypeCode WaterDispenser_g_tc_Device_ID_string = DDS_INITIALIZE_STRING_TYPECODE((32));
    static DDS_TypeCode WaterDispenser_g_tc_Hardware_string = DDS_INITIALIZE_STRING_TYPECODE((4));
    static DDS_TypeCode WaterDispenser_g_tc_Mac_Address_string = DDS_INITIALIZE_STRING_TYPECODE((32));

    static DDS_TypeCode_Member WaterDispenser_g_tc_members[26]=
    {

        {
            (char *)"UploadTime",/* Member name */
            {
                0,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Hot_Valve",/* Member name */
            {
                1,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Cooling",/* Member name */
            {
                2,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Usage_L",/* Member name */
            {
                3,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Warm_Valve",/* Member name */
            {
                4,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"ColdTemp_Insulation",/* Member name */
            {
                5,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Status",/* Member name */
            {
                6,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Usage_MT",/* Member name */
            {
                7,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"WaterLevel",/* Member name */
            {
                8,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"ErrorCode",/* Member name */
            {
                9,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"HotTemp_Insulation",/* Member name */
            {
                10,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Device_ID",/* Member name */
            {
                11,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Refilling",/* Member name */
            {
                12,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SavingPower",/* Member name */
            {
                13,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TimeStamp",/* Member name */
            {
                14,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Heating",/* Member name */
            {
                15,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Cold_Valve",/* Member name */
            {
                16,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"WarmTemp",/* Member name */
            {
                17,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"ColdTemp",/* Member name */
            {
                18,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Usage_CC",/* Member name */
            {
                19,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"HotTemp",/* Member name */
            {
                20,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Sterilizing",/* Member name */
            {
                21,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Hardware",/* Member name */
            {
                22,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"Mac_Address",/* Member name */
            {
                23,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"TDS",/* Member name */
            {
                24,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }, 
        {
            (char *)"SendTime",/* Member name */
            {
                25,/* Representation ID */
                DDS_BOOLEAN_FALSE,/* Is a pointer? */
                -1, /* Bitfield bits */
                NULL/* Member type code is assigned later */
            },
            0, /* Ignored */
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            RTI_CDR_REQUIRED_MEMBER, /* Is a key? */
            DDS_PUBLIC_MEMBER,/* Member visibility */
            1,
            NULL, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER
        }
    };

    static DDS_TypeCode WaterDispenser_g_tc =
    {{
            DDS_TK_STRUCT, /* Kind */
            DDS_BOOLEAN_FALSE, /* Ignored */
            -1, /*Ignored*/
            (char *)"WaterDispenser", /* Name */
            NULL, /* Ignored */      
            0, /* Ignored */
            0, /* Ignored */
            NULL, /* Ignored */
            26, /* Number of members */
            WaterDispenser_g_tc_members, /* Members */
            DDS_VM_NONE, /* Ignored */
            RTICdrTypeCodeAnnotations_INITIALIZER,
            DDS_BOOLEAN_TRUE, /* _isCopyable */
            NULL, /* _sampleAccessInfo: assigned later */
            NULL /* _typePlugin: assigned later */
        }}; /* Type code for WaterDispenser*/

    if (is_initialized) {
        return &WaterDispenser_g_tc;
    }

    WaterDispenser_g_tc._data._annotations._allowedDataRepresentationMask = 5;

    WaterDispenser_g_tc_members[0]._representation._typeCode = (RTICdrTypeCode *)&WaterDispenser_g_tc_UploadTime_string;
    WaterDispenser_g_tc_members[1]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[2]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[3]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[4]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[5]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[6]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[7]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[8]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[9]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[10]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[11]._representation._typeCode = (RTICdrTypeCode *)&WaterDispenser_g_tc_Device_ID_string;
    WaterDispenser_g_tc_members[12]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[13]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[14]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;
    WaterDispenser_g_tc_members[15]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[16]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[17]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[18]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[19]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[20]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[21]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[22]._representation._typeCode = (RTICdrTypeCode *)&WaterDispenser_g_tc_Hardware_string;
    WaterDispenser_g_tc_members[23]._representation._typeCode = (RTICdrTypeCode *)&WaterDispenser_g_tc_Mac_Address_string;
    WaterDispenser_g_tc_members[24]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_long;
    WaterDispenser_g_tc_members[25]._representation._typeCode = (RTICdrTypeCode *)&DDS_g_tc_longlong;

    /* Initialize the values for member annotations. */
    WaterDispenser_g_tc_members[0]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
    WaterDispenser_g_tc_members[0]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

    WaterDispenser_g_tc_members[1]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[1]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[1]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[1]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[1]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[1]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[2]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[2]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[2]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[2]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[2]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[2]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[3]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[3]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[3]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[3]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[3]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[3]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[4]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[4]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[4]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[4]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[4]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[4]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[5]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[5]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[5]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[5]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[5]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[5]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[6]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[6]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[6]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[6]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[6]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[6]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[7]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[7]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[7]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[7]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[7]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[7]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[8]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[8]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[8]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[8]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[8]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[8]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[9]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[9]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[9]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[9]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[9]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[9]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[10]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[10]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[10]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[10]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[10]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[10]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[11]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
    WaterDispenser_g_tc_members[11]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

    WaterDispenser_g_tc_members[12]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[12]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[12]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[12]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[12]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[12]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[13]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[13]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[13]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[13]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[13]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[13]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[14]._annotations._defaultValue._d = RTI_XCDR_TK_LONGLONG;
    WaterDispenser_g_tc_members[14]._annotations._defaultValue._u.long_long_value = 0ll;
    WaterDispenser_g_tc_members[14]._annotations._minValue._d = RTI_XCDR_TK_LONGLONG;
    WaterDispenser_g_tc_members[14]._annotations._minValue._u.long_long_value = RTIXCdrLongLong_MIN;
    WaterDispenser_g_tc_members[14]._annotations._maxValue._d = RTI_XCDR_TK_LONGLONG;
    WaterDispenser_g_tc_members[14]._annotations._maxValue._u.long_long_value = RTIXCdrLongLong_MAX;

    WaterDispenser_g_tc_members[15]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[15]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[15]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[15]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[15]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[15]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[16]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[16]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[16]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[16]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[16]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[16]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[17]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[17]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[17]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[17]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[17]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[17]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[18]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[18]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[18]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[18]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[18]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[18]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[19]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[19]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[19]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[19]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[19]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[19]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[20]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[20]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[20]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[20]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[20]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[20]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[21]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[21]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[21]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[21]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[21]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[21]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[22]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
    WaterDispenser_g_tc_members[22]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

    WaterDispenser_g_tc_members[23]._annotations._defaultValue._d = RTI_XCDR_TK_STRING;
    WaterDispenser_g_tc_members[23]._annotations._defaultValue._u.string_value = (DDS_Char *) "";

    WaterDispenser_g_tc_members[24]._annotations._defaultValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[24]._annotations._defaultValue._u.long_value = 0;
    WaterDispenser_g_tc_members[24]._annotations._minValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[24]._annotations._minValue._u.long_value = RTIXCdrLong_MIN;
    WaterDispenser_g_tc_members[24]._annotations._maxValue._d = RTI_XCDR_TK_LONG;
    WaterDispenser_g_tc_members[24]._annotations._maxValue._u.long_value = RTIXCdrLong_MAX;

    WaterDispenser_g_tc_members[25]._annotations._defaultValue._d = RTI_XCDR_TK_LONGLONG;
    WaterDispenser_g_tc_members[25]._annotations._defaultValue._u.long_long_value = 0ll;
    WaterDispenser_g_tc_members[25]._annotations._minValue._d = RTI_XCDR_TK_LONGLONG;
    WaterDispenser_g_tc_members[25]._annotations._minValue._u.long_long_value = RTIXCdrLongLong_MIN;
    WaterDispenser_g_tc_members[25]._annotations._maxValue._d = RTI_XCDR_TK_LONGLONG;
    WaterDispenser_g_tc_members[25]._annotations._maxValue._u.long_long_value = RTIXCdrLongLong_MAX;

    WaterDispenser_g_tc._data._sampleAccessInfo =
    WaterDispenser_get_sample_access_info();
    WaterDispenser_g_tc._data._typePlugin =
    WaterDispenser_get_type_plugin_info();    

    is_initialized = RTI_TRUE;

    return &WaterDispenser_g_tc;
}

RTIXCdrSampleAccessInfo *WaterDispenser_get_sample_access_info()
{
    static RTIBool is_initialized = RTI_FALSE;

    static RTIXCdrMemberAccessInfo WaterDispenser_g_memberAccessInfos[26] =
    {RTIXCdrMemberAccessInfo_INITIALIZER};

    static RTIXCdrSampleAccessInfo WaterDispenser_g_sampleAccessInfo = 
    RTIXCdrSampleAccessInfo_INITIALIZER;

    if (is_initialized) {
        return (RTIXCdrSampleAccessInfo*) &WaterDispenser_g_sampleAccessInfo;
    }

    WaterDispenser_g_memberAccessInfos[0].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->UploadTime);

    WaterDispenser_g_memberAccessInfos[1].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Hot_Valve);

    WaterDispenser_g_memberAccessInfos[2].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Cooling);

    WaterDispenser_g_memberAccessInfos[3].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Usage_L);

    WaterDispenser_g_memberAccessInfos[4].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Warm_Valve);

    WaterDispenser_g_memberAccessInfos[5].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->ColdTemp_Insulation);

    WaterDispenser_g_memberAccessInfos[6].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Status);

    WaterDispenser_g_memberAccessInfos[7].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Usage_MT);

    WaterDispenser_g_memberAccessInfos[8].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->WaterLevel);

    WaterDispenser_g_memberAccessInfos[9].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->ErrorCode);

    WaterDispenser_g_memberAccessInfos[10].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->HotTemp_Insulation);

    WaterDispenser_g_memberAccessInfos[11].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Device_ID);

    WaterDispenser_g_memberAccessInfos[12].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Refilling);

    WaterDispenser_g_memberAccessInfos[13].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->SavingPower);

    WaterDispenser_g_memberAccessInfos[14].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->TimeStamp);

    WaterDispenser_g_memberAccessInfos[15].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Heating);

    WaterDispenser_g_memberAccessInfos[16].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Cold_Valve);

    WaterDispenser_g_memberAccessInfos[17].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->WarmTemp);

    WaterDispenser_g_memberAccessInfos[18].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->ColdTemp);

    WaterDispenser_g_memberAccessInfos[19].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Usage_CC);

    WaterDispenser_g_memberAccessInfos[20].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->HotTemp);

    WaterDispenser_g_memberAccessInfos[21].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Sterilizing);

    WaterDispenser_g_memberAccessInfos[22].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Hardware);

    WaterDispenser_g_memberAccessInfos[23].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->Mac_Address);

    WaterDispenser_g_memberAccessInfos[24].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->TDS);

    WaterDispenser_g_memberAccessInfos[25].bindingMemberValueOffset[0] = 
    (RTIXCdrUnsignedLong) RTIXCdrUtility_pointerToULongLong(&((WaterDispenser *)NULL)->SendTime);

    WaterDispenser_g_sampleAccessInfo.memberAccessInfos = 
    WaterDispenser_g_memberAccessInfos;

    {
        size_t candidateTypeSize = sizeof(WaterDispenser);

        if (candidateTypeSize > RTIXCdrUnsignedLong_MAX) {
            WaterDispenser_g_sampleAccessInfo.typeSize[0] =
            RTIXCdrUnsignedLong_MAX;
        } else {
            WaterDispenser_g_sampleAccessInfo.typeSize[0] =
            (RTIXCdrUnsignedLong) candidateTypeSize;
        }
    }

    WaterDispenser_g_sampleAccessInfo.languageBinding = 
    RTI_XCDR_TYPE_BINDING_C ;

    is_initialized = RTI_TRUE;
    return (RTIXCdrSampleAccessInfo*) &WaterDispenser_g_sampleAccessInfo;
}

RTIXCdrTypePlugin *WaterDispenser_get_type_plugin_info()
{
    static RTIXCdrTypePlugin WaterDispenser_g_typePlugin = 
    {
        NULL, /* serialize */
        NULL, /* serialize_key */
        NULL, /* deserialize_sample */
        NULL, /* deserialize_key_sample */
        NULL, /* skip */
        NULL, /* get_serialized_sample_size */
        NULL, /* get_serialized_sample_max_size_ex */
        NULL, /* get_serialized_key_max_size_ex */
        NULL, /* get_serialized_sample_min_size */
        NULL, /* serialized_sample_to_key */
        (RTIXCdrTypePluginInitializeSampleFunction) 
        WaterDispenser_initialize_ex,
        NULL,
        (RTIXCdrTypePluginFinalizeSampleFunction)
        WaterDispenser_finalize_w_return,
        NULL
    };

    return &WaterDispenser_g_typePlugin;
}
#endif

RTIBool WaterDispenser_initialize(
    WaterDispenser* sample) {
    return WaterDispenser_initialize_ex(sample,RTI_TRUE,RTI_TRUE);
}

RTIBool WaterDispenser_initialize_ex(
    WaterDispenser* sample,RTIBool allocatePointers, RTIBool allocateMemory)
{

    struct DDS_TypeAllocationParams_t allocParams =
    DDS_TYPE_ALLOCATION_PARAMS_DEFAULT;

    allocParams.allocate_pointers =  (DDS_Boolean)allocatePointers;
    allocParams.allocate_memory = (DDS_Boolean)allocateMemory;

    return WaterDispenser_initialize_w_params(
        sample,&allocParams);

}

RTIBool WaterDispenser_initialize_w_params(
    WaterDispenser* sample, const struct DDS_TypeAllocationParams_t * allocParams)
{

    if (sample == NULL) {
        return RTI_FALSE;
    }
    if (allocParams == NULL) {
        return RTI_FALSE;
    }

    if (allocParams->allocate_memory) {
        sample->UploadTime = DDS_String_alloc((32));
        RTICdrType_copyStringEx(
            &sample->UploadTime,
            "",
            (32),
            RTI_FALSE);
        if (sample->UploadTime == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->UploadTime != NULL) {
            RTICdrType_copyStringEx(
                &sample->UploadTime,
                "",
                (32),
                RTI_FALSE);
            if (sample->UploadTime == NULL) {
                return RTI_FALSE;
            }
        }
    }

    sample->Hot_Valve = 0;

    sample->Cooling = 0;

    sample->Usage_L = 0;

    sample->Warm_Valve = 0;

    sample->ColdTemp_Insulation = 0;

    sample->Status = 0;

    sample->Usage_MT = 0;

    sample->WaterLevel = 0;

    sample->ErrorCode = 0;

    sample->HotTemp_Insulation = 0;

    if (allocParams->allocate_memory) {
        sample->Device_ID = DDS_String_alloc((32));
        RTICdrType_copyStringEx(
            &sample->Device_ID,
            "",
            (32),
            RTI_FALSE);
        if (sample->Device_ID == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->Device_ID != NULL) {
            RTICdrType_copyStringEx(
                &sample->Device_ID,
                "",
                (32),
                RTI_FALSE);
            if (sample->Device_ID == NULL) {
                return RTI_FALSE;
            }
        }
    }

    sample->Refilling = 0;

    sample->SavingPower = 0;

    sample->TimeStamp = 0ll;

    sample->Heating = 0;

    sample->Cold_Valve = 0;

    sample->WarmTemp = 0;

    sample->ColdTemp = 0;

    sample->Usage_CC = 0;

    sample->HotTemp = 0;

    sample->Sterilizing = 0;

    if (allocParams->allocate_memory) {
        sample->Hardware = DDS_String_alloc((4));
        RTICdrType_copyStringEx(
            &sample->Hardware,
            "",
            (4),
            RTI_FALSE);
        if (sample->Hardware == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->Hardware != NULL) {
            RTICdrType_copyStringEx(
                &sample->Hardware,
                "",
                (4),
                RTI_FALSE);
            if (sample->Hardware == NULL) {
                return RTI_FALSE;
            }
        }
    }

    if (allocParams->allocate_memory) {
        sample->Mac_Address = DDS_String_alloc((32));
        RTICdrType_copyStringEx(
            &sample->Mac_Address,
            "",
            (32),
            RTI_FALSE);
        if (sample->Mac_Address == NULL) {
            return RTI_FALSE;
        }
    } else {
        if (sample->Mac_Address != NULL) {
            RTICdrType_copyStringEx(
                &sample->Mac_Address,
                "",
                (32),
                RTI_FALSE);
            if (sample->Mac_Address == NULL) {
                return RTI_FALSE;
            }
        }
    }

    sample->TDS = 0;

    sample->SendTime = 0ll;

    return RTI_TRUE;
}

RTIBool WaterDispenser_finalize_w_return(
    WaterDispenser* sample)
{
    WaterDispenser_finalize_ex(sample, RTI_TRUE);

    return RTI_TRUE;
}

void WaterDispenser_finalize(
    WaterDispenser* sample)
{

    WaterDispenser_finalize_ex(sample,RTI_TRUE);
}

void WaterDispenser_finalize_ex(
    WaterDispenser* sample,RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParams =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;

    if (sample==NULL) {
        return;
    } 

    deallocParams.delete_pointers = (DDS_Boolean)deletePointers;

    WaterDispenser_finalize_w_params(
        sample,&deallocParams);
}

void WaterDispenser_finalize_w_params(
    WaterDispenser* sample,const struct DDS_TypeDeallocationParams_t * deallocParams)
{

    if (sample==NULL) {
        return;
    }

    if (deallocParams == NULL) {
        return;
    }

    if (sample->UploadTime != NULL) {
        DDS_String_free(sample->UploadTime);
        sample->UploadTime=NULL;

    }

    if (sample->Device_ID != NULL) {
        DDS_String_free(sample->Device_ID);
        sample->Device_ID=NULL;

    }

    if (sample->Hardware != NULL) {
        DDS_String_free(sample->Hardware);
        sample->Hardware=NULL;

    }
    if (sample->Mac_Address != NULL) {
        DDS_String_free(sample->Mac_Address);
        sample->Mac_Address=NULL;

    }

}

void WaterDispenser_finalize_optional_members(
    WaterDispenser* sample, RTIBool deletePointers)
{
    struct DDS_TypeDeallocationParams_t deallocParamsTmp =
    DDS_TYPE_DEALLOCATION_PARAMS_DEFAULT;
    struct DDS_TypeDeallocationParams_t * deallocParams =
    &deallocParamsTmp;

    if (sample==NULL) {
        return;
    } 
    if (deallocParams) {} /* To avoid warnings */

    deallocParamsTmp.delete_pointers = (DDS_Boolean)deletePointers;
    deallocParamsTmp.delete_optional_members = DDS_BOOLEAN_TRUE;

}

RTIBool WaterDispenser_copy(
    WaterDispenser* dst,
    const WaterDispenser* src)
{

    if (dst == NULL || src == NULL) {
        return RTI_FALSE;
    }

    if (!RTICdrType_copyStringEx (
        &dst->UploadTime, src->UploadTime, 
        (32) + 1, RTI_FALSE)){
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Hot_Valve, &src->Hot_Valve)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Cooling, &src->Cooling)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Usage_L, &src->Usage_L)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Warm_Valve, &src->Warm_Valve)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->ColdTemp_Insulation, &src->ColdTemp_Insulation)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Status, &src->Status)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Usage_MT, &src->Usage_MT)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->WaterLevel, &src->WaterLevel)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->ErrorCode, &src->ErrorCode)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->HotTemp_Insulation, &src->HotTemp_Insulation)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyStringEx (
        &dst->Device_ID, src->Device_ID, 
        (32) + 1, RTI_FALSE)){
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Refilling, &src->Refilling)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->SavingPower, &src->SavingPower)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLongLong (
        &dst->TimeStamp, &src->TimeStamp)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Heating, &src->Heating)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Cold_Valve, &src->Cold_Valve)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->WarmTemp, &src->WarmTemp)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->ColdTemp, &src->ColdTemp)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Usage_CC, &src->Usage_CC)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->HotTemp, &src->HotTemp)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->Sterilizing, &src->Sterilizing)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyStringEx (
        &dst->Hardware, src->Hardware, 
        (4) + 1, RTI_FALSE)){
        return RTI_FALSE;
    }
    if (!RTICdrType_copyStringEx (
        &dst->Mac_Address, src->Mac_Address, 
        (32) + 1, RTI_FALSE)){
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLong (
        &dst->TDS, &src->TDS)) { 
        return RTI_FALSE;
    }
    if (!RTICdrType_copyLongLong (
        &dst->SendTime, &src->SendTime)) { 
        return RTI_FALSE;
    }

    return RTI_TRUE;

}

/**
* <<IMPLEMENTATION>>
*
* Defines:  TSeq, T
*
* Configure and implement 'WaterDispenser' sequence class.
*/
#define T WaterDispenser
#define TSeq WaterDispenserSeq

#define T_initialize_w_params WaterDispenser_initialize_w_params

#define T_finalize_w_params   WaterDispenser_finalize_w_params
#define T_copy       WaterDispenser_copy

#ifndef NDDS_STANDALONE_TYPE
#include "dds_c/generic/dds_c_sequence_TSeq.gen"
#else
#include "dds_c_sequence_TSeq.gen"
#endif

#undef T_copy
#undef T_finalize_w_params

#undef T_initialize_w_params

#undef TSeq
#undef T

