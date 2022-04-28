/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)dds_c_monitoring.h    generated by: makeheader    Thu Feb 28 22:12:56 2019
 *
 *		built from:	monitoring.ifc
 */

#ifndef dds_c_monitoring_h
#define dds_c_monitoring_h


  #ifndef dds_c_infrastructure_h
    #include "dds_c/dds_c_infrastructure.h"
  #endif

    #include "dds_c/dds_c_domain.h"

#define DDS_MONITORING_LIBRARY_PROPERTY_NAME		 	"rti.monitor.library"
#define DDS_MONITORING_CREATE_FUNCTION_PROPERTY_NAME 		"rti.monitor.create_function"
#define DDS_MONITORING_CREATE_FUNCTION_PTR_PROPERTY_NAME 	"rti.monitor.create_function_ptr"

/* description topic names */
#define DDS_MONITORING_PARTICIPANT_DESC_TOPIC_NAME "rti/dds/monitoring/domainParticipantDescription"
#define DDS_MONITORING_TOPIC_DESC_TOPIC_NAME "rti/dds/monitoring/topicDescription"
#define DDS_MONITORING_PUBLISHER_DESC_TOPIC_NAME "rti/dds/monitoring/publisherDescription"
#define DDS_MONITORING_SUBSCRIBER_DESC_TOPIC_NAME "rti/dds/monitoring/subscriberDescription"
#define DDS_MONITORING_READER_DESC_TOPIC_NAME "rti/dds/monitoring/dataReaderDescription"
#define DDS_MONITORING_WRITER_DESC_TOPIC_NAME "rti/dds/monitoring/dataWriterDescription"

/* statistics topic names */
#define DDS_MONITORING_PROCESS_STAT_TOPIC_NAME "rti/dds/monitoring/processStatistics"
#define DDS_MONITORING_PARTICIPANT_STAT_TOPIC_NAME "rti/dds/monitoring/domainParticipantEntityStatistics"
#define DDS_MONITORING_READER_STAT_TOPIC_NAME "rti/dds/monitoring/dataReaderEntityStatistics"
#define DDS_MONITORING_WRITER_STAT_TOPIC_NAME "rti/dds/monitoring/dataWriterEntityStatistics"
#define DDS_MONITORING_TOPIC_STAT_TOPIC_NAME "rti/dds/monitoring/topicEntityStatistics"

/* matched statistics topic names */
#define DDS_MONITORING_READER_MATCHED_TOPIC_NAME "rti/dds/monitoring/dataReaderEntityMatchedPublicationStatistics"
#define DDS_MONITORING_WRITER_MATCHED_TOPIC_NAME "rti/dds/monitoring/dataWriterEntityMatchedSubscriptionStatistics"
#define DDS_MONITORING_WRITER_MATCHED_W_LOCATOR_TOPIC_NAME "rti/dds/monitoring/dataWriterEntityMatchedSubscriptionWithLocatorStatistics"

#define DDS_MONITORING_TOPIC_NAMES { \
    DDS_MONITORING_PARTICIPANT_DESC_TOPIC_NAME, \
    DDS_MONITORING_TOPIC_DESC_TOPIC_NAME, \
    DDS_MONITORING_PUBLISHER_DESC_TOPIC_NAME, \
    DDS_MONITORING_SUBSCRIBER_DESC_TOPIC_NAME, \
    DDS_MONITORING_READER_DESC_TOPIC_NAME, \
    DDS_MONITORING_WRITER_DESC_TOPIC_NAME, \
    DDS_MONITORING_PROCESS_STAT_TOPIC_NAME, \
    DDS_MONITORING_PARTICIPANT_STAT_TOPIC_NAME, \
    DDS_MONITORING_READER_STAT_TOPIC_NAME, \
    DDS_MONITORING_WRITER_STAT_TOPIC_NAME, \
    DDS_MONITORING_TOPIC_STAT_TOPIC_NAME, \
    DDS_MONITORING_READER_MATCHED_TOPIC_NAME, \
    DDS_MONITORING_WRITER_MATCHED_TOPIC_NAME, \
    DDS_MONITORING_WRITER_MATCHED_W_LOCATOR_TOPIC_NAME \
}


struct RTIMonitorParticipantObject;

typedef enum {
	RTI_MONITOR_RETCODE_VERSION_MISMATCH,
	RTI_MONITOR_RETCODE_ERROR,
	RTI_MONITOR_RETCODE_SUCCESS
} RTIMonitorReturnCode;

typedef 
struct RTIMonitorClass *(*RTIMonitor_createFnc)(
	RTIMonitorReturnCode *retcode, /* out */
        DDS_DomainParticipantFactory * factory,
	struct DDS_ProductVersion_t productVersion);

typedef
RTIMonitorReturnCode (*RTIMonitor_deleteFnc)(
	struct RTIMonitorClass *monitoringClass);

typedef
struct RTIMonitorParticipantObject * (*RTIMonitor_domainParticipantAttach)(
	RTIMonitorReturnCode *retcode, /* out */
	struct RTIMonitorClass *monitoringClass,
	DDS_DomainParticipant *participant);

typedef 
RTIMonitorReturnCode (*RTIMonitor_domainParticipantDetach)(
	struct RTIMonitorParticipantObject *monitorParticipantObject);

typedef enum {
	/* Participant */
	PARTICIPANT_ENABLE_AFTER                     = 0x010,
	PARTICIPANT_QOS_CHANGE_AFTER                 = 0x020,
	PARTICIPANT_DELETE_CONTAINED_ENTITIES_BEFORE = 0x041,

	/* Topic */
	TOPIC_CREATE_AFTER                           = 0x100,
	TOPIC_ENABLE_AFTER                           = 0x110,
	TOPIC_QOS_CHANGE_AFTER                       = 0x120,
	TOPIC_DELETE_BEFORE                          = 0x131,

	/* Publisher */
	PUBLISHER_CREATE_AFTER                       = 0x200,
	PUBLISHER_ENABLE_AFTER                       = 0x210,
	PUBLISHER_QOS_CHANGE_AFTER                   = 0x220,
	PUBLISHER_DELETE_BEFORE                      = 0x231,
	PUBLISHER_DELETE_CONTAINED_ENTITIES_BEFORE   = 0x241,

	/* Subscriber */
	SUBSCRIBER_CREATE_AFTER                      = 0x300,
	SUBSCRIBER_ENABLE_AFTER                      = 0x310,
	SUBSCRIBER_QOS_CHANGE_AFTER                  = 0x320,
	SUBSCRIBER_DELETE_BEFORE                     = 0x331,
	SUBSCRIBER_DELETE_CONTAINED_ENTITIES_BEFORE  = 0x341,

	/* Datawriter */
	DATAWRITER_CREATE_AFTER                      = 0x400,
	DATAWRITER_ENABLE_AFTER                      = 0x410,
	DATAWRITER_QOS_CHANGE_AFTER                  = 0x420,
	DATAWRITER_DELETE_BEFORE                     = 0x431,

	/* Datareader */
	DATAREADER_CREATE_AFTER                      = 0x500,
	DATAREADER_ENABLE_AFTER                      = 0x510,
	DATAREADER_QOS_CHANGE_AFTER                  = 0x520,
	DATAREADER_DELETE_BEFORE                     = 0x531,

	/* Matching pairs */
	DATAWRITER_LOCATOR_PAIR_CREATE_AFTER	     = 0x600,
	DATAWRITER_LOCATOR_PAIR_DELETE_AFTER	     = 0x630,

	ENTITY_MATCH_PAIR_CREATE_AFTER		     = 0x700,
	ENTITY_MATCH_PAIR_DELETE_AFTER		     = 0x730
} RTIMonitorEventKind;

typedef 
RTIMonitorReturnCode (*RTIMonitor_eventNotifyFnc)(
    	struct RTIMonitorParticipantObject *monitorParticipantObject,
	RTIMonitorEventKind eventKind,
	DDS_Entity *affectedDDSEntity,
	void *eventInfo);

struct RTIMonitorClass {
        DDS_DomainParticipantFactory * factory;
	RTIMonitor_deleteFnc               deleteFnc;
	RTIMonitor_domainParticipantAttach domainParticipantAttachFnc;
	RTIMonitor_domainParticipantDetach domainParticipantDetachFnc;
	RTIMonitor_eventNotifyFnc          eventNotifyFnc;

	void * userData;
};

#endif /* dds_c_monitoring_h */