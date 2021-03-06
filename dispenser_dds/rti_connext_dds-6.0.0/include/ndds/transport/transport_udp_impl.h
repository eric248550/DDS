/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)transport_udp_impl.h    generated by: makeheader    Thu Feb 28 22:11:53 2019
 *
 *		built from:	udp_impl.ifc
 */

#ifndef transport_udp_impl_h
#define transport_udp_impl_h


#include "osapi/osapi_type.h"
#include "osapi/osapi_socket.h"
#include "osapi/osapi_interfaceTracker.h"
#include "osapi/osapi_interfaces.h"
#ifndef reda_inlineList_h
  #include "reda/reda_inlineList.h"
#endif
#ifndef transport_common_h
  #include "transport/transport_common.h"
#endif
#ifndef transport_udp_h
  #include "transport/transport_udp.h"
#endif
#ifdef __cplusplus
    extern "C" {
#endif


struct NDDS_Transport_IP_Interface_t {
    NDDS_Transport_Interface_t        _interface;  
    unsigned int                      _interfaceFlags;
    char _interfaceName[RTI_OSAPI_INTERFACE_NAME_LENGTH];
    int                               _interfaceIndex;
};

extern NDDS_Transport_DllExport
RTIOsapiSocketAFKind
NDDS_Transport_IP_get_family(NDDS_Transport_Plugin * self);

extern NDDS_Transport_DllExport
RTIBool NDDS_Transport_IP_isAddressAllowed(
        RTI_INT32 *multicast_enabled_out,
        const NDDS_Transport_Interface_t *interface_in,
        const char* interface_name_in,
        struct NDDS_Transport_Property_t * property,
        RTIOsapiSocketAFKind family);

extern NDDS_Transport_DllExport
RTIBool NDDS_Transport_IP_interfacesAreEqual(
    const struct NDDS_Transport_IP_Interface_t * interfaceA,
    const struct NDDS_Transport_IP_Interface_t * interfaceB,
    RTIOsapiSocketAFKind family);

extern NDDS_Transport_DllExport
RTI_INT32 NDDS_Transport_IP_query_interfaces(
    NDDS_Transport_Plugin * self,
    struct RTIOsapiInterfaceTracker * interfaceTracker,
    struct NDDS_Transport_IP_Interface_t ** outInterfaceArray,
    int * outInterfaceCount,
    int * outInterfaceArraySize,
    unsigned int requestedInterfacesMask,
    unsigned int reportIgnoreInterfaceWarnings);

struct NDDS_Transport_IP_InterfaceListener;

typedef
RTI_INT32 (*NDDS_Transport_IP_OnIPInterfaceFnc)(
        struct NDDS_Transport_IP_InterfaceListener * interfaceListener,
        NDDS_Transport_Plugin * transportPlugin,
        struct NDDS_Transport_IP_Interface_t * ipInterface,
        RTI_INT32 * multicastEnabled);

struct NDDS_Transport_IP_InterfaceListener {
    NDDS_Transport_IP_OnIPInterfaceFnc onIpInterface;
};

extern NDDS_Transport_DllExport
RTIBool NDDS_Transport_IP_selectValidInterfaces(
    NDDS_Transport_Plugin * self,
    struct NDDS_Transport_IP_Interface_t * interfaceArray,
    struct NDDS_Transport_IP_Interface_t ** loopbackInterfaceOut,
    int * interfaceCountPt,
    RTIBool ignoreLoopbackInterfaceProperty,
    struct NDDS_Transport_IP_InterfaceListener * ipInterfaceListener);


struct NDDS_Transport_UDP_RecvResource_t {
    /*i Node structure for use in list. */
    struct REDAInlineListNode _node;
    RTI_INT32             socket;
    NDDS_Transport_Port_t port;
    RTIBool               is_multicast;
    /* multicast_address is used to send the unblock message. */
    NDDS_Transport_Address_t  multicast_address;
  #if !defined(RTI_VX653)    
    struct sockaddr *last_source_socket_address;
  #endif    
    RTIBool               is_unblocking;
};


struct NDDS_Transport_UDP_SendResource_t {
    /*i Node structure for use in list. */
    struct REDAInlineListNode _node;
    RTI_INT32             unisocket;
    NDDS_Transport_Port_t unisocket_port;
    RTI_INT32            *multisocket;
    int                   multiSocketArrayLength;
    RTI_INT32             transport_priority;
};


struct NDDS_Transport_UDP {
    NDDS_Transport_Plugin                       parent;
    RTIOsapiSocketAFKind                       _family;
    struct NDDS_Transport_UDP_Property_t     _property;
    struct NDDS_Transport_UDP_SocketFactory *_socketFactory;
    
    /* in charge of detecting and notifying interface changes */
    struct RTIOsapiInterfaceTracker  *           _interfaceTracker;

    /* for built-in performance measurement */
    struct RTIClock                   *_clock; 

    /* default sockets used to send */
    RTI_INT32                          _unisocket;
    NDDS_Transport_Port_t              _unisocket_port;
    RTI_INT32                         *_multisocket;
    int                                _multiSocketArrayLength;

    /* store system information about the running NICs */
    int                                _interfacesCount; 
    struct NDDS_Transport_IP_Interface_t *_interfaceArray;
    int                                _interfaceArraySize; 
    struct NDDS_Transport_IP_Interface_t * _loopbackInterface;
    
    /* Fake UDP interface for testing purposes */
    struct NDDS_Transport_IP_Interface_t _fakeInterface;
    RTIBool                                   _fakeInterfaceEnabled; 

    /* user installed function that will be used to prevent an
       instance from using the interface */
    struct NDDS_Transport_UDP_InterfaceListener* _interfaceListener;

    /* Listener used to notify upper layers when a interface has changed*/
    NDDS_Transport_Listener _networkListener;

    char _id[NDDS_TRANSPORT_UDP_UNBLOCK_MESSAGE_SIZE];

    struct NDDS_Transport_UDP_gatherSendBuffer* gatherSendBuffer;

    /* A list of multicast receive resources created for the transport.
       This will be used to add multicast sockets, destroy multicast sockets
       and join (or rejoin) multicast groups when the corresponding interfaces 
       are created, become available or unavailable, dissappear or change IP 
       address */
    struct REDAInlineList _multicastReceiveResourceList;
    /* A list of multicast send resources created for the transport.
       This will be used to create priority send sockets when new interfaces are
       available or destroy sockets when the interface is gone or becomes 
       unavailable */
    struct REDAInlineList _multicastSendResourceList;
    /*To guard the multicast receive and send resource lists*/
    struct RTIOsapiSemaphore * _mutex;
    /* TODO : Add HANDLE _callbackHandle for Windows Vista and above*/
    /* Public IP address of the transport instantiation */
    NDDS_Transport_Address_t _publicAddress;
    
    struct NDDS_Transport_UDP_Statistics _statistics;

    /* For internal use only. Keeps track of the min and max transport
       priorities that send resources are being created with */
    RTI_INT32 _min_priority;
    RTI_INT32 _max_priority;

    /* CORE-4052: Used for determining if ignore loopback interface */
    RTIBool _ignoreLoopbackInterface;

  #if defined(RTI_WIN32) || defined(RTI_WINCE)
    /* CORE-5954 -- Function pointer for the shutdown of the socket. */
    void * _cancelIoExFnc;
  #endif

    /* memory management */
    struct NDDS_Transport_IP_Interface_t * _interfaceArrayReplacement;
    int                                    _interfaceArrayReplacementSize;
    int                                     * _intArrayReplacement;
    int                                     _intArrayReplacementLength;
};

extern NDDS_Transport_DllExport
int NDDS_Transport_UDP_assert_fake_ip_address(
        NDDS_Transport_Plugin  *self,
        NDDS_Transport_Address_t *address);

extern NDDS_Transport_DllExport
int NDDS_Transport_UDP_remove_fake_ip_address(
        NDDS_Transport_Plugin  *self);


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* transport_udp_impl_h */
