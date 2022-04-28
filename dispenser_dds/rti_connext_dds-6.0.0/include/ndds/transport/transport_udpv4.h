/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)transport_udpv4.h    generated by: makeheader    Thu Feb 28 22:11:57 2019
 *
 *		built from:	udpv4.ifc
 */

#ifndef transport_udpv4_h
#define transport_udpv4_h


   #ifndef transport_udp_h
    #include "transport/transport_udp.h"
  #endif
#ifdef __cplusplus
    extern "C" {
#endif


#define NDDS_Transport_UDPv4   NDDS_Transport_UDP


#define NDDS_Transport_UDPv4_InterfaceListener   NDDS_Transport_UDP_InterfaceListener


#define NDDS_Transport_UDPv4_Property_t   NDDS_Transport_UDP_Property_t


#define NDDS_TRANSPORT_UDPV4_CLASS_NAME		"udpv4"


#define NDDS_TRANSPORT_BUILTIN_UDPV4_ALIAS      "builtin.udpv4"


#define NDDS_TRANSPORT_UDPV4_ADDRESS_BIT_COUNT  (32)


#define NDDS_TRANSPORT_UDPV4_PROPERTIES_BITMAP_DEFAULT  NDDS_TRANSPORT_UDP_PROPERTIES_BITMAP_DEFAULT


#define NDDS_TRANSPORT_UDPV4_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT  NDDS_TRANSPORT_UDP_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT


#define NDDS_TRANSPORT_UDPV4_SOCKET_BUFFER_SIZE_OS_DEFAULT  NDDS_TRANSPORT_UDP_SOCKET_BUFFER_SIZE_OS_DEFAULT


#define NDDS_TRANSPORT_UDPV4_SEND_SOCKET_BUFFER_SIZE_DEFAULT  NDDS_TRANSPORT_UDP_SEND_SOCKET_BUFFER_SIZE_DEFAULT


#define NDDS_TRANSPORT_UDPV4_RECV_SOCKET_BUFFER_SIZE_DEFAULT  NDDS_TRANSPORT_UDP_RECV_SOCKET_BUFFER_SIZE_DEFAULT


#define NDDS_TRANSPORT_UDPV4_PAYLOAD_SIZE_MAX  (65507)


#if defined(RTI_INTY)
#define NDDS_TRANSPORT_UDPV4_MESSAGE_SIZE_MAX_DEFAULT (9216)
#else
#define NDDS_TRANSPORT_UDPV4_MESSAGE_SIZE_MAX_DEFAULT  NDDS_TRANSPORT_UDPV4_PAYLOAD_SIZE_MAX
#endif


#define NDDS_TRANSPORT_UDPV4_DATAGRAM_LENGTH_MAX  NDDS_TRANSPORT_UDP_DATAGRAM_LENGTH_MAX


#define NDDS_TRANSPORT_UDPV4_MULTICAST_TTL_DEFAULT  NDDS_TRANSPORT_UDP_MULTICAST_TTL_DEFAULT


#define NDDS_TRANSPORT_UDPV4_USE_MULTICAST_DEFAULT  NDDS_TRANSPORT_UDP_USE_MULTICAST_DEFAULT


/*e \dref_UDPv4Transport_IGNORE_LOOPBACK_DISABLED
 */
  #define NDDS_TRANSPORT_UDPV4_IGNORE_LOOPBACK_DISABLED        NDDS_TRANSPORT_UDP_IGNORE_LOOPBACK_DISABLED

/*e \dref_UDPv4Transport_IGNORE_LOOPBACK_ENABLED
 */
  #define NDDS_TRANSPORT_UDPV4_IGNORE_LOOPBACK_ENABLED         NDDS_TRANSPORT_UDP_IGNORE_LOOPBACK_ENABLED

/*e \dref_UDPv4Transport_IGNORE_LOOPBACK_AUTO
 */
  #define NDDS_TRANSPORT_UDPV4_IGNORE_LOOPBACK_AUTO            NDDS_TRANSPORT_UDP_IGNORE_LOOPBACK_AUTO


/*e \dref_UDPv4Transport_USE_CHECKSUM_DISABLED
 */
  #define NDDS_TRANSPORT_UDPV4_USE_CHECKSUM_DISABLED        (0)

/*e \dref_UDPv4Transport_USE_CHECKSUM_ENABLED
 */
  #define NDDS_TRANSPORT_UDPV4_USE_CHECKSUM_ENABLED         (1)



/*e \dref_UDPv4Transport_BLOCKING_NEVER
 */
  #define NDDS_TRANSPORT_UDPV4_BLOCKING_NEVER        NDDS_TRANSPORT_UDP_BLOCKING_NEVER

/*e \dref_UDPv4Transport_BLOCKING_ALWAYS
 */
  #define NDDS_TRANSPORT_UDPV4_BLOCKING_ALWAYS       NDDS_TRANSPORT_UDP_BLOCKING_ALWAYS
  #define NDDS_TRANSPORT_UDPV4_BLOCKING_UNICAST_ONLY       NDDS_TRANSPORT_UDP_BLOCKING_UNICAST_ONLY

/*e \dref_UDPv4Transport_BLOCKING_DEFAULT
 */
  #define NDDS_TRANSPORT_UDPV4_BLOCKING_DEFAULT     NDDS_TRANSPORT_UDP_BLOCKING_DEFAULT
            


#define NDDS_TRANSPORT_UDPV4_PROPERTY_DEFAULT { \
    { NDDS_TRANSPORT_CLASSID_UDPv4, \
      NDDS_TRANSPORT_UDPV4_ADDRESS_BIT_COUNT, \
      NDDS_TRANSPORT_UDPV4_PROPERTIES_BITMAP_DEFAULT, \
      NDDS_TRANSPORT_UDPV4_GATHER_SEND_BUFFER_COUNT_MAX_DEFAULT, \
      NDDS_TRANSPORT_UDPV4_MESSAGE_SIZE_MAX_DEFAULT, \
      NULL, 0, /* allow_interfaces_list */ \
      NULL, 0, /* deny_interfaces_list */ \
      NULL, 0, /* allow_multicast_interfaces_list */ \
      NULL, 0, /* deny_multicast_interfaces_list */ \
      NULL /* domain_participant_ptr */ \
    }, \
    NDDS_TRANSPORT_UDPV4_SEND_SOCKET_BUFFER_SIZE_DEFAULT, \
    NDDS_TRANSPORT_UDPV4_RECV_SOCKET_BUFFER_SIZE_DEFAULT, \
    1, /* use unicast */   \
    NDDS_TRANSPORT_UDPV4_USE_MULTICAST_DEFAULT, /* use multicast */ \
    NDDS_TRANSPORT_UDPV4_MULTICAST_TTL_DEFAULT, \
    0, /* multicast loopback enabled */ \
    NDDS_TRANSPORT_UDPV4_IGNORE_LOOPBACK_AUTO, /* (auto-)ignore loopback */ \
    1, /* ignore_nonup_interfaces */ \
    1, /* ignore_nonrunning_interfaces */ \
    0, /* no_zero_copy */ \
    NDDS_TRANSPORT_UDPV4_BLOCKING_DEFAULT, \
    0,  /* enable_v4mapped */ \
    NDDS_TRANSPORT_UDPV4_USE_CHECKSUM_ENABLED, /* use_checksum */ \
    0, 0, 0xff /* no mapping to IP_TOS by default */, \
    1, /* send_ping */ \
    500, /* 500 millisecs is the default polling period*/ \
    1, /* reuse multicast receive resource */ \
    28, /* protocol_overhead_max (UDP(8)+IP(20)) */ \
    0, /* disable interface tracking */ \
    NULL /* public_address */ \
}



#define NDDS_Transport_UDPv4_InterfaceListener  NDDS_Transport_UDP_InterfaceListener


#define NDDS_Transport_UDPv4_Interface_Filter_Fcn  NDDS_Transport_UDP_Interface_Filter_Fcn

extern NDDS_Transport_DllExport 
RTI_INT32 NDDS_Transport_UDPv4_InterfaceListener_onInterface(
    struct NDDS_Transport_UDPv4_InterfaceListener* self,
    struct NDDS_Transport_UDPv4      *plugin,
    RTI_INT32                        *multicast_enabled_out,
    const NDDS_Transport_Interface_t *interface_in,
    const char*                       interface_name_in);

extern NDDS_Transport_DllVariable
struct NDDS_Transport_UDP_InterfaceListener
         NDDS_Transport_UDPv4_g_interfaceListener;


#define NDDS_Transport_UDPv4_SocketFactory_Send_Socket_Create_Fcn   NDDS_Transport_UDP_SocketFactory_Send_Socket_Create_Fcn


#define NDDS_Transport_UDPv4_SocketFactory_Receive_Socket_Create_Fcn   NDDS_Transport_UDP_SocketFactory_Receive_Socket_Create_Fcn


#define NDDS_Transport_UDPv4_SocketFactory_Socket_Destroy_Fcn   NDDS_Transport_UDP_SocketFactory_Socket_Destroy_Fcn


#define NDDS_Transport_UDPv4_SocketFactory   NDDS_Transport_UDP_SocketFactory


#define NDDS_Transport_UDPv4_SocketFactory_is_valid   NDDS_Transport_UDP_SocketFactory_is_valid

extern NDDS_Transport_DllExport 
RTI_INT32 NDDS_Transport_UDPv4_SocketFactory_create_send_socket(
    struct NDDS_Transport_UDPv4_SocketFactory *me,
    NDDS_Transport_Port_t                     *port_out,
    const struct NDDS_Transport_UDPv4         *ip_in,
    const NDDS_Transport_Address_t            *interface_address_in,
    const int			              *interface_index_in);

extern NDDS_Transport_DllExport 
RTI_INT32 NDDS_Transport_UDPv4_SocketFactory_create_receive_socket(
    struct NDDS_Transport_UDPv4_SocketFactory *me,
    NDDS_Transport_Port_t                     *port_inout,
    const struct NDDS_Transport_UDPv4         *ip_in,
    const NDDS_Transport_Address_t            *multicast_address_in);

extern NDDS_Transport_DllExport 
RTI_INT32 NDDS_Transport_UDPv4_SocketFactory_destroy_socket(
    struct NDDS_Transport_UDPv4_SocketFactory   *me,
    RTI_INT32                                   s_in);

extern NDDS_Transport_DllExport 
NDDS_Transport_Port_t NDDS_Transport_UDPv4_Socket_bind(
    RTI_INT32                   s_in, 
    const NDDS_Transport_Port_t port_desired_in);

extern NDDS_Transport_DllExport 
NDDS_Transport_Port_t NDDS_Transport_UDPv4_Socket_bind_with_ip(
    RTI_INT32                   s_in, 
    const NDDS_Transport_Port_t port_desired_in,
    unsigned int ip_in);

extern NDDS_Transport_DllVariable
struct NDDS_Transport_UDPv4_SocketFactory  NDDS_Transport_UDPv4_g_socketFactory;


#define NDDS_Transport_UDPv4_get_class_name_cEA   NDDS_Transport_UDP_get_class_name_cEA


#define NDDS_Transport_UDPv4_string_to_address_cEA   NDDS_Transport_UDP_string_to_address_cEA

extern NDDS_Transport_DllExport 
NDDS_Transport_Plugin *NDDS_Transport_UDPv4_new(
    const struct NDDS_Transport_UDPv4_Property_t *property_in);

extern NDDS_Transport_DllExport 
NDDS_Transport_Plugin *NDDS_Transport_UDPv4_newI(
    const struct NDDS_Transport_UDPv4_Property_t *property_in,
    struct NDDS_Transport_UDPv4_SocketFactory    *socket_factory_in,
    struct NDDS_Transport_UDPv4_InterfaceListener* interface_listener_in,
    struct RTIClock                              *clock_in);


#define NDDS_Transport_UDPv4_get_receive_interfaces_cEA  NDDS_Transport_UDP_get_receive_interfaces_cEA


#define NDDS_Transport_UDPv4_get_ignore_loopback_interface_status  NDDS_Transport_UDP_get_ignore_loopback_interface_status


#define NDDS_Transport_UDPv4_is_local_address  NDDS_Transport_UDP_is_local_address


#define NDDS_Transport_UDPv4_map_transport_priority  NDDS_Transport_UDP_map_transport_priority


#define NDDS_TRANSPORT_UDPV4_ADDRESS_LOCALHOST {{0,0,0,0, 0,0,0,0, 0,0,0,0, 127,0,0,1}}


#define NDDS_TRANSPORT_UDPV4_UNBLOCK_MESSAGE_SIZE  NDDS_TRANSPORT_UDP_UNBLOCK_MESSAGE_SIZE


#define NDDS_Transport_UDPv4_Statistics  NDDS_Transport_UDP_Statistics


#define NDDS_Transport_UDPv4_get_statistics  NDDS_Transport_UDP_get_statistics


#define NDDS_Transport_UDPv4_get_priority_range  NDDS_Transport_UDP_get_priority_range

extern NDDS_Transport_DllExport
RTI_INT32 NDDS_Transport_UDPv4_Address_to_string(
    const NDDS_Transport_Address_t *me,
    char                           *buffer,
    RTI_INT32                       buffer_length_in);


#define NDDS_Transport_UDPv4_Address_print  NDDS_Transport_UDP_Address_print


#ifdef __cplusplus
    }	/* extern "C" */
#endif

  #include "transport/transport_udpv4_impl.h"

#endif /* transport_udpv4_h */