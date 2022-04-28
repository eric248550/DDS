
/* water_subscriber.c

A subscription example

This file is derived from code automatically generated by the rtiddsgen 
command:

rtiddsgen -language C -example <arch> water.idl

Example subscription of type WaterDispenser automatically generated by 
'rtiddsgen'. To test them, follow these steps:

(1) Compile this file and the example publication.

(2) Start the subscription on the same domain used for RTI Data Distribution
Service  with the command
objs/<arch>/water_subscriber <domain_id> <sample_count>

(3) Start the publication on the same domain used for RTI Data Distribution
Service with the command
objs/<arch>/water_publisher <domain_id> <sample_count>

(4) [Optional] Specify the list of discovery initial peers and 
multicast receive addresses via an environment variable or a file 
(in the current working directory) called NDDS_DISCOVERY_PEERS. 

You can run any number of publishers and subscribers programs, and can 
add and remove them dynamically from the domain.

Example:

To run the example application on domain <domain_id>:

On UNIX systems: 

objs/<arch>/water_publisher <domain_id> 
objs/<arch>/water_subscriber <domain_id> 

On Windows systems:

objs\<arch>\water_publisher <domain_id>  
objs\<arch>\water_subscriber <domain_id>   

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "ndds/ndds_c.h"
#include "water.h"
#include "waterSupport.h"
#include <bson/bson.h>
#include <mongoc.h>


char *UploadTime;
bool Hot_Valve;
bool Cooling;
int Usage_L;
bool Warm_Valve;
int ColdTemp_Insulation;
bool Status;
int Usage_MT;
int WaterLevel;
int ErrorCode;
int HotTemp_Insulation;
char *Device_ID;
bool Refilling;
bool SavingPower;
long long TimeStamp;
bool Heating;
bool Cold_Valve;
int WarmTemp;
int ColdTemp;
int Usage_CC;
int HotTemp;
bool Sterilizing;
char *Hardware;
char *Mac_Address;
int TDS;
long long SendTime;

char *str_replace(char *orig, char *rep, char *with) {
	char *result; /// the return string
	char *ins;    /// the next insert point
	char *tmp;    /// varies
	int len_rep;  /// length of rep (the string to remove)
	int len_with; /// length of with (the string to replace rep with)
	int len_front; /// distance between rep and end of last rep
	int count;    /// number of replacements

	/// sanity checks and initialization
	if (!orig || !rep)
			return NULL;
	len_rep = strlen(rep);
	if (len_rep == 0)
			return NULL; /// empty rep causes infinite loop during count
	if (!with)
			with = "";
	len_with = strlen(with);

	/// count the number of replacements needed
	ins = orig;
	for (count = 0; (tmp = strstr(ins, rep)); ++count) {
		ins = tmp + len_rep;
	}

	tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

	if (!result)
			return NULL;

	/// first time through the loop, all the variable are set correctly
	/// from here on,
	///    tmp points to the end of the result string
	///    ins points to the next occurrence of rep in orig
	///    orig points to the remainder of orig after "end of rep"
	while (count--) {
			ins = strstr(orig, rep);
			len_front = ins - orig;
			tmp = strncpy(tmp, orig, len_front) + len_front;
			tmp = strcpy(tmp, with) + len_with;
			orig += len_front + len_rep; /// move to next "end of rep"
	}
	strcpy(tmp, orig);
	return result;
}

void log_printf(const struct WaterDispenser * WaterDispenser, long long delay){
	printf("[ %s - %s ] ::: SUCCESS :::  ", strtok(WaterDispenser -> Hardware,"\r\n"), strtok(WaterDispenser -> Device_ID,"\r\n"));
	printf("{ UploadTime: %s, ", strtok(WaterDispenser -> UploadTime,"\r\n"));
	printf("CWH: %d - %d - %d, ", WaterDispenser -> ColdTemp, WaterDispenser -> WarmTemp, WaterDispenser -> HotTemp);
	if(WaterDispenser -> ErrorCode > 0){
		printf("ErrorCode: %d ", WaterDispenser -> ErrorCode);
	};

	printf("STATUS: ");
	if(WaterDispenser -> Refilling > 0){
		printf("REFILLING, ");
	}
	else if(WaterDispenser -> SavingPower > 0){
		printf("SAVING_POWER, ");
	}
	else if(WaterDispenser -> Heating > 0){
		printf("HEATING, ");
	}
	else if(WaterDispenser -> Sterilizing > 0){
		printf("STERILIZING, ");
	}
	else{
		printf("IDLE, ");
	}

	printf("MAC Addr: %s, ", strtok(WaterDispenser -> Mac_Address,"\r\n"));
	printf("ReceiveTime: %lld, ", WaterDispenser -> SendTime);
	if(delay > 0){
		printf("Delay: %lld, ", delay);
	}
	printf("TimeStamp: %lld }", WaterDispenser -> TimeStamp);
}

/*
void WaterDispenserListener_on_requested_deadline_missed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedDeadlineMissedStatus *status)
{
}

void WaterDispenserListener_on_requested_incompatible_qos(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_RequestedIncompatibleQosStatus *status)
{
}

void WaterDispenserListener_on_sample_rejected(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleRejectedStatus *status)
{
}

void WaterDispenserListener_on_liveliness_changed(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_LivelinessChangedStatus *status)
{
}

void WaterDispenserListener_on_sample_lost(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SampleLostStatus *status)
{
}

void WaterDispenserListener_on_subscription_matched(
    void* listener_data,
    DDS_DataReader* reader,
    const struct DDS_SubscriptionMatchedStatus *status)
{
}

void WaterDispenserListener_on_data_available(
    void* listener_data,
    DDS_DataReader* reader)
{
    WaterDispenserDataReader *WaterDispenser_reader = NULL;
    struct WaterDispenserSeq data_seq = DDS_SEQUENCE_INITIALIZER;
    struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;
    DDS_ReturnCode_t retcode;
    int i;

    WaterDispenser_reader = WaterDispenserDataReader_narrow(reader);
    if (WaterDispenser_reader == NULL) {
        fprintf(stderr, "DataReader narrow error\n");
        return;
    }
    


    retcode = WaterDispenserDataReader_take(
        WaterDispenser_reader,
        &data_seq, &info_seq, DDS_LENGTH_UNLIMITED,
        DDS_ANY_SAMPLE_STATE, DDS_ANY_VIEW_STATE, DDS_ANY_INSTANCE_STATE);
        if (retcode == DDS_RETCODE_NO_DATA) {
        return;
        } else if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "take error %d\n", retcode);
        return;
    }
    
    for (i = 0; i < WaterDispenserSeq_get_length(&data_seq); ++i) {
        if (DDS_SampleInfoSeq_get_reference(&info_seq, i)->valid_data) {
            printf("Received data\n");
            WaterDispenserTypeSupport_print_data(
                WaterDispenserSeq_get_reference(&data_seq, i));
            
                          
        }
       
        UploadTime=WaterDispenserSeq_get_reference(&data_seq, i)->UploadTime;
        ColdTemp_Insulation=WaterDispenserSeq_get_reference(&data_seq, i)->ColdTemp_Insulation;
        HotTemp_Insulation=WaterDispenserSeq_get_reference(&data_seq, i)->HotTemp_Insulation;
        Device_ID=WaterDispenserSeq_get_reference(&data_seq, i)->Device_ID;
        
        TimeStamp=WaterDispenserSeq_get_reference(&data_seq, i)->TimeStamp;
        Mac_Address=WaterDispenserSeq_get_reference(&data_seq, i)->Mac_Address;
        SendTime=WaterDispenserSeq_get_reference(&data_seq, i)->SendTime;
        // printf(" data %s,%D,%s \n",UploadTime,Hot_Valve,Cooling,Usage_L,Warm_Valve,ColdTemp_Insulation,Status,
        // Usage_MT,WaterLevel,ErrorCode,HotTemp_Insulation,Device_ID,Refilling,SavingPower,TimeStamp,Heating,
        // Cold_Valve,WarmTemp,ColdTemp,Usage_CC,HotTemp,Sterilizing,Hardware,Mac_Address,TDS);  
                    
    }
    
    

    retcode = WaterDispenserDataReader_return_loan(
        WaterDispenser_reader,
        &data_seq, &info_seq);
        if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "return loan error %d\n", retcode);
    }
    return UploadTime,ColdTemp_Insulation,HotTemp_Insulation,Device_ID,TimeStamp,Mac_Address;
}
*/
/** Delete all entities */
static int subscriber_shutdown(
    DDS_DomainParticipant *participant)
{
    DDS_ReturnCode_t retcode;
    int status = 0;

    if (participant != NULL) {
        retcode = DDS_DomainParticipant_delete_contained_entities(participant);
        if (retcode != DDS_RETCODE_OK) {
            fprintf(stderr, "delete_contained_entities error %d\n", retcode);
            status = -1;
        }

        retcode = DDS_DomainParticipantFactory_delete_participant(
            DDS_TheParticipantFactory, participant);
        if (retcode != DDS_RETCODE_OK) {
            fprintf(stderr, "delete_participant error %d\n", retcode);
            status = -1;
        }
    }

    /** RTI Data Distribution Service provides the finalize_instance() method on
    domain participant factory for users who want to release memory used
    by the participant factory. Uncomment the following block of code for
    clean destruction of the singleton. */
    /*
    retcode = DDS_DomainParticipantFactory_finalize_instance();
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "finalize_instance error %d\n", retcode);
        status = -1;
    }
    */

    return status;
}


static int subscriber_main(int domainId, int sample_count)
{
    DDS_DomainParticipant *participant = NULL;
    DDS_Subscriber *subscriber = NULL;
    DDS_Topic *topic = NULL;
    //struct DDS_DataReaderListener reader_listener = DDS_DataReaderListener_INITIALIZER;
    
    DDS_DataReader *reader = NULL;
    DDS_ReturnCode_t retcode;
    const char *type_name = NULL;
    int count = 0;
    DDS_StatusCondition *status_condition;
    DDS_WaitSet *waitset=NULL;
    WaterDispenserDataReader *WaterDispenserReader=NULL; //WaterDispenserDataReader->waitset_statuscondDataReader
    struct DDS_Duration_t timeout = {1,0};
    //struct DDS_Time_t current;
    /** To customize participant QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    participant = DDS_DomainParticipantFactory_create_participant_with_profile(
        DDS_TheParticipantFactory, domainId, "TCP_Library", "TCP_Subscriber",
        NULL /* listener */, DDS_STATUS_MASK_NONE);
    if (participant == NULL) {
        fprintf(stderr, "create_participant error\n");
        subscriber_shutdown(participant);
        return -1;
    }
    
    /** To customize subscriber QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    subscriber = DDS_DomainParticipant_create_subscriber(
        participant, &DDS_SUBSCRIBER_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (subscriber == NULL) {
        fprintf(stderr, "create_subscriber error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /** Register the type before creating the topic */
    type_name = WaterDispenserTypeSupport_get_type_name();//WaterDispenserTypeSupport->waitset_statuscondTypeSupport
    retcode = WaterDispenserTypeSupport_register_type(participant, type_name);
    if (retcode != DDS_RETCODE_OK) {
        fprintf(stderr, "register_type error %d\n", retcode);
        subscriber_shutdown(participant);
        return -1;
    }

    /** To customize topic QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    topic = DDS_DomainParticipant_create_topic(
        participant, "Example WaterDispenser",
        type_name, &DDS_TOPIC_QOS_DEFAULT, NULL /* listener */,
        DDS_STATUS_MASK_NONE);
    if (topic == NULL) {
        fprintf(stderr, "create_topic error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /** Set up a data reader listener */
    /*
    reader_listener.on_requested_deadline_missed  =
    WaterDispenserListener_on_requested_deadline_missed;
    reader_listener.on_requested_incompatible_qos =
    WaterDispenserListener_on_requested_incompatible_qos;
    reader_listener.on_sample_rejected =
    WaterDispenserListener_on_sample_rejected;
    reader_listener.on_liveliness_changed =
    WaterDispenserListener_on_liveliness_changed;
    reader_listener.on_sample_lost =
    WaterDispenserListener_on_sample_lost;
    reader_listener.on_subscription_matched =
    WaterDispenserListener_on_subscription_matched;
    reader_listener.on_data_available =
    WaterDispenserListener_on_data_available;
   */
    /** To customize data reader QoS, use 
    the configuration file USER_QOS_PROFILES.xml */
    reader = DDS_Subscriber_create_datareader(
        subscriber, DDS_Topic_as_topicdescription(topic),
        &DDS_DATAREADER_QOS_DEFAULT, NULL/*&reader_listener*/, DDS_STATUS_MASK_ALL);
    if (reader == NULL) {
        fprintf(stderr, "create_datareader error\n");
        subscriber_shutdown(participant);
        return -1;
    
    }
    status_condition= DDS_Entity_get_statuscondition((DDS_Entity *) reader);
    if(status_condition==NULL){
        fprintf(stderr, "get_statuscondition error\n");
        subscriber_shutdown(participant);
        return -1;

    }
    /** Since a single status condition can match many statuses,
     enable only those we're interested in.*/
    retcode = DDS_StatusCondition_set_enabled_statuses(
            status_condition,
            DDS_DATA_AVAILABLE_STATUS 
            );
    if (retcode != DDS_RETCODE_OK) {
        printf("set_enabled_statuses error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /// Create WaitSet, and attach conditions
    waitset = DDS_WaitSet_new();
    if (waitset == NULL) {
        printf("create waitset error\n");
        subscriber_shutdown(participant);
        return -1;
    }


    retcode = DDS_WaitSet_attach_condition(
            waitset,
            (DDS_Condition *) status_condition);
    if (retcode != DDS_RETCODE_OK) {
        printf("attach_condition error\n");
        subscriber_shutdown(participant);
        return -1;
    }

    /// Get narrowed datareader
    WaterDispenserReader = WaterDispenserDataReader_narrow(reader);//waitset_statuscondDataReader_narrow(reader);
    if (WaterDispenserReader == NULL) {
        printf("DataReader narrow error\n");
        return -1;
    }
	
	/** Libmongoc Database Connection Initialization */
    mongoc_client_t	*client;
    mongoc_database_t *database;
    mongoc_collection_t *collection;
    bson_t *command, reply, *insert;
    bson_error_t error;
    char *str;
    bool retval;
    const char* mongo_address = getenv("MONGO_ADDRESS");
    mongoc_init ();
    printf("CONNECTING TO %s VERSION %s \n", mongo_address, mongoc_get_version());
    client = mongoc_client_new(mongo_address);
    database = mongoc_client_get_database(client, "water");
    collection = mongoc_client_get_collection(client, "water", "dispenser_data_DDS");
    command = BCON_NEW ("ping", BCON_INT32(1));
    retval = mongoc_client_command_simple (client, "admin", command, NULL, &reply, &error);
    if (!retval) {
        fprintf (stderr, "%s\n", error.message);
        return EXIT_FAILURE;
    }
    str = bson_as_json (&reply, NULL);
    printf ("%s\n", str);
    
    
    /** Main loop */
    bson_t *water_doc;
    
    struct DDS_ConditionSeq active_conditions = DDS_SEQUENCE_INITIALIZER;
    int i, j;     
    for (count=0; (sample_count == 0) || (count < sample_count); ++count) {
		struct DDS_Time_t current;
		time_t machine_time;
		struct tm * timeinfo;
			
		retcode = DDS_WaitSet_wait(waitset, &active_conditions, &timeout);
		if (retcode == DDS_RETCODE_TIMEOUT) {
			time(&machine_time);
			timeinfo = localtime (&machine_time);
			printf("TIMEOUT : %s UTC\n", strtok(asctime(timeinfo),"\n" ));
			count += 2;
			continue;
		} else if (retcode != DDS_RETCODE_OK) {
			printf("ERROR: %d\n", retcode);
			break;
		}
		printf("got %d active conditions\n", DDS_ConditionSeq_get_length(&active_conditions));

		for (i = 0; i < DDS_ConditionSeq_get_length(&active_conditions); ++i) {
			/** Compare with Status Conditions */
			if (DDS_ConditionSeq_get(&active_conditions, i)	== (DDS_Condition *) status_condition) {
				/** A status condition triggered--see which ones */
				//DDS_Condition* status_condition = ColdTemp_Insulation->get_statuscondition();
				DDS_StatusMask triggeredmask;
				//DDS_StatusMask triggeredmask2;
				//code = dataReader->take_next_sample(sample,info);
				// for (j = 0;
				//             j < WaterDispenserSeq_get_length(&data_seq);
				//             ++j){
				// ColdTemp_Insulation=WaterDispenserSeq_get_reference(&data_seq ,j)->ColdTemp_Insulation;}

				//DDS_Condition* my_status_condition = *ColdTemp_Insulation->get_statuscondition();

				triggeredmask = DDS_Entity_get_status_changes((DDS_Entity *) WaterDispenserReader);

				//DDS_Entity_get_status_changes(ColdTemp_Insulation);													
				
				/** Subscription matched */
				if (triggeredmask  & DDS_DATA_AVAILABLE_STATUS ) {
					/** Current conditions match our conditions to read data, so
					* we can read data just like we would do in any other
					* example.
					*/
					struct WaterDispenserSeq data_seq = DDS_SEQUENCE_INITIALIZER;
					struct DDS_SampleInfoSeq info_seq = DDS_SEQUENCE_INITIALIZER;

					/** Access data using read(), take(), etc.  If you fail to do
					* this the condition will remain true, and the WaitSet will
					* wake up immediately - causing high CPU usage when it does
					* not sleep in the loop */
					retcode = DDS_RETCODE_OK;
					while (retcode != DDS_RETCODE_NO_DATA) {
						retcode = WaterDispenserDataReader_take(
							WaterDispenserReader,
							&data_seq,
							&info_seq,
							DDS_LENGTH_UNLIMITED,
							DDS_ANY_SAMPLE_STATE,
							DDS_ANY_VIEW_STATE,
							DDS_ANY_INSTANCE_STATE
						);
							
						for (j = 0;j < WaterDispenserSeq_get_length(&data_seq);j++) {
							if (!DDS_SampleInfoSeq_get_reference(&info_seq, j) -> valid_data) {
								printf("Got metadata\n");
								continue;
							}

							UploadTime = WaterDispenserSeq_get_reference(&data_seq, j) -> UploadTime;
							Hot_Valve = WaterDispenserSeq_get_reference(&data_seq, j) -> Hot_Valve;
							Cooling = WaterDispenserSeq_get_reference(&data_seq, j) -> Cooling;
							Usage_L = WaterDispenserSeq_get_reference(&data_seq, j) -> Usage_L;
							Warm_Valve = WaterDispenserSeq_get_reference(&data_seq, j) -> Warm_Valve;
							ColdTemp_Insulation = WaterDispenserSeq_get_reference(&data_seq, j) -> ColdTemp_Insulation;
							Status = WaterDispenserSeq_get_reference(&data_seq, j) -> Status;
							Usage_MT = WaterDispenserSeq_get_reference(&data_seq, j) -> Usage_MT;
							WaterLevel = WaterDispenserSeq_get_reference(&data_seq, j) -> WaterLevel;
							ErrorCode = WaterDispenserSeq_get_reference(&data_seq, j) -> ErrorCode;
							HotTemp_Insulation = WaterDispenserSeq_get_reference(&data_seq, j) -> HotTemp_Insulation;
							Device_ID = WaterDispenserSeq_get_reference(&data_seq, j) -> Device_ID;
							Refilling = WaterDispenserSeq_get_reference(&data_seq, j) -> Refilling;
							SavingPower = WaterDispenserSeq_get_reference(&data_seq, j) -> SavingPower;
							TimeStamp = WaterDispenserSeq_get_reference(&data_seq, j) -> TimeStamp;
							Heating = WaterDispenserSeq_get_reference(&data_seq, j) -> Heating;
							Cold_Valve = WaterDispenserSeq_get_reference(&data_seq, j) -> Cold_Valve;
							WarmTemp = WaterDispenserSeq_get_reference(&data_seq, j) -> WarmTemp;
							ColdTemp = WaterDispenserSeq_get_reference(&data_seq, j) -> ColdTemp;
							Usage_CC = WaterDispenserSeq_get_reference(&data_seq, j) -> Usage_CC;
							HotTemp = WaterDispenserSeq_get_reference(&data_seq, j) -> HotTemp;
							Sterilizing = WaterDispenserSeq_get_reference(&data_seq, j) -> Sterilizing;
							Hardware = WaterDispenserSeq_get_reference(&data_seq, j) -> Hardware;
							Mac_Address = WaterDispenserSeq_get_reference(&data_seq, j) -> Mac_Address;
							TDS = WaterDispenserSeq_get_reference(&data_seq, j) -> TDS;
							SendTime = WaterDispenserSeq_get_reference(&data_seq, j) -> SendTime;

							/* Old Log Print Function WaterDispenserTypeSupport_print_data(WaterDispenserSeq_get_reference(&data_seq,j));*/
									
							DDS_DomainParticipant_get_current_time(participant, &current); 
							long long toolong = current.sec;
							long long delay = toolong * 1000 + current.nanosec/1000000 - SendTime;

							// New Log Print Function
							log_printf(WaterDispenserSeq_get_reference(&data_seq,j), delay);

							water_doc = BCON_NEW(
								"UploadTime", BCON_UTF8(str_replace(UploadTime,"\r\n","")),
								"ReceiveTime", BCON_INT64(SendTime),
								"Hot_Valve", BCON_INT32(Hot_Valve),
								"Cooling", BCON_INT32(Cooling),   
								"Usage_L", BCON_INT32(Usage_L),
								"Warm_Valve", BCON_INT32(Warm_Valve), 
								"ColdTemp_Insulation", BCON_INT32(ColdTemp_Insulation),
								"Status", BCON_INT32(Status),
								"Usage_MT", BCON_INT32(Usage_MT), 
								"WaterLevel", BCON_INT32(WaterLevel),
								"ErrorCode", BCON_INT32(ErrorCode),
								"HotTemp_Insulation", BCON_INT32(HotTemp_Insulation), 
								"Device_ID", BCON_UTF8(str_replace(Device_ID,"\r\n","")),
								"Refilling", BCON_INT32(Refilling),
								"SavingPower", BCON_INT32(SavingPower),
								"TimeStamp", BCON_INT64(TimeStamp),
								"Heating", BCON_INT32(Heating),
								"Cold_Valve", BCON_INT32(Cold_Valve),
								"WarmTemp", BCON_INT32(WarmTemp), 
								"ColdTemp", BCON_INT32(ColdTemp),
								"Usage_CC", BCON_INT32(Usage_CC),
								"HotTemp", BCON_INT32(HotTemp),
								"Sterilizing", BCON_INT32(Sterilizing),
								"Hardware", BCON_UTF8(str_replace(Hardware,"\r\n","")),
								"Mac_Address", BCON_UTF8(str_replace(Mac_Address,"\r\n","")),
								"TDS", BCON_INT32(TDS),
								"delay", BCON_INT64(delay)
							);
										
							if(TimeStamp!=0){  
								if (!mongoc_collection_insert_one (collection, water_doc, NULL, &reply, &error)) {
									fprintf (stderr, "%s\n", error.message);
								}
								str = bson_as_json (&reply, NULL);
								printf (" >> DB\n"); 
							}                
						}
							
						WaterDispenserDataReader_return_loan(WaterDispenserReader, 
															&data_seq, 
															&info_seq);						
					}	
				}
			}
		}

		
	
		//printf("WaterDispenser subscriber sleeping for %d sec...\n",poll_period.sec);

		//NDDS_Utility_sleep(&poll_period);
    }


    bson_destroy (&reply);
    bson_destroy (command);
    bson_free (str);
    /**
        * Release our handles and clean up libmongoc
        */
    mongoc_collection_destroy (collection);///释放表对象
    mongoc_database_destroy (database);///释放数据库对象
    mongoc_client_destroy (client);///释放连接对象
    mongoc_cleanup ();///释放libmongoc驱动 kc
    
    /** Delete all entities */
    retcode = DDS_WaitSet_delete(waitset);
    if (retcode != DDS_RETCODE_OK) {
        printf("delete waitset error %d\n", retcode);
    }

    /** Cleanup and delete all entities */
    return subscriber_shutdown(participant);
}

int main(int argc, char *argv[])
{
    int domain_id = 0;
    int sample_count = 0; /** infinite loop */

    if (argc >= 2) {
        domain_id = atoi(argv[1]);
    }
    if (argc >= 3) {
        sample_count = atoi(argv[2]);
    }

    // * Uncomment this to turn on additional logging
    // NDDS_Config_Logger_set_verbosity_by_category(
    //     NDDS_Config_Logger_get_instance(),
    //     NDDS_CONFIG_LOG_CATEGORY_API, 
    //     NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL);
    

    return subscriber_main(domain_id, sample_count);
}
            


