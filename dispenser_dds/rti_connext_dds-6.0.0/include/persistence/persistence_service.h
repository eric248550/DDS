/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)persistence_service.h    generated by: makeheader    Thu Feb 28 22:14:36 2019
 *
 *		built from:	service.ifc
 */

#ifndef persistence_service_h
#define persistence_service_h


  #ifndef persistence_dll_h
    #include "persistence/persistence_dll.h"
  #endif
  #ifndef ndds_h
    #include "ndds/ndds_c.h"
  #endif
  #ifdef __cplusplus
      extern "C" {
  #endif


struct RTI_PersistenceService;


struct RTI_PersistenceServiceProperty {  
    /*e
     * 
     * @brief Path to an RTI Persistence Service configuration file
     *
     * If not \c NULL, this file is loaded; otherwise,
     * if \c cfg_strings is not \c NULL, that XML code is loaded 
     *
     * \default NULL.
     */                                       
    char * cfg_file;

    /*e
     * @brief XML configuration represented as strings
     * 
     * An array of strings that altogether make up an
     * XML document to configure RTI Persistence Service. This parameter is used
     * only if \ref cfg_file is \c NULL.
     *
     * For example: 
     *
     * \code
     * int MY_PERSISTENCE_SERVICE_CFG_SIZE = 3;
     * const char * MY_PERSISTENCE_SERVICE_CFG[MY_PERSISTENCE_SERVICE_CFG_SIZE] = 
     *                          {"<dds><persistence_service>",
     *                           "<participant name=\"defaultParticipant\"><persistence_group name=,
     *                           "\"groupName\">...</dds>"};
     *
     * property.cfg_strings = MY_PERSISTENCE_SERVICE_CFG;
     * property.cfg_strings_count = MY_PERSISTENCE_SERVICE_CFG_SIZE;
     * \endcode
     * 
     * The reason for using an array instead of one single string is to
     * get around the limited size of literal strings in C.
     * In general, if you create the XML string dynamically 
     * using one single string in the array, 
     * setting \ref cfg_strings_count to 1 is enough:
     *
     * \code
     * property.cfg_strings = malloc(sizeof(char *));
     * property.cfg_strings[0] = "<dds><routing_service>...</dds>";
     * property.cfg_strings_count = 1;
     * \endcode
     *
     * If your target system doesn't support a file system, you can 
     * configure the service using XML strings.
     *
     * \default NULL.
     */
    const char ** cfg_strings;

    /*e
     * @brief Size of the array \ref cfg_strings
     *
     * \default 0.
     */
    int cfg_strings_count;

    /*e
     *
     * @brief Configuration name. This parameter is required
     *        and it is used to find a &lt;persistence_service&gt;
     *        matching tag in the configuration file
     *
     * \default NULL.
     */
    char * cfg_name;

    /*e
     * @brief Assigns a name to the execution of the RTI Persistence Service.
     *
     * Remote commands will refer to the persistence service
     * using this name.
     * In addition, the name of DomainParticipants created by RTI
     * Persistence Service will be based on this name.
     *
     * \default The value of cfg_name if different than NULL. Otherwise,
     * "RTI_Persistence_Service".
     */
    char * application_name;

    /*e
     * @brief Set this to true to append the host name and process ID
     * to the RTI Persistence Service application name.
     *
     * Used to get unique names for remote administration.
     *
     * \default DDS_BOOLEAN_FALSE
     */
    DDS_Boolean identify_execution;

    /*e
     * @brief DDS domain ID for the DomainParticipants
     *        created by the service
     *
     * \default -1 (Use the XML value)
     */
    int domain_id;

    /*e
     * @brief Set this to true to enable remote administration
     * or false to disable it.
     *
     * \default DDS_BOOLEAN_FALSE
     */
    DDS_Boolean enable_administration;

    /*e
     * @brief If \ref enable_administration is true, this is
     * the domain ID to use for remote administration.
     *
     * Takes precedence over the XML configuration.
     * If \ref enable_administration is false, this value is not used
     * even if remote administration is enabled in the XML configuration.
     *
     * \default 0
     */
    int administration_domain_id;

    /*e
     * @brief RTI Persistence Service thread stack size,
     *        used to specify a stack size for the main service thread
     *
     * \default RTI_OSAPI_THREAD_STACK_SIZE_DEFAULT
     */
    int thread_stack_size;

    /*e
     * @brief The info directory of the running RTI Persistence Service
     *
     * The service writes a ps.pid file into this directory when is started.
     * When the service finalizes the file is deleted.
     *
     * The ps.pid file is used to check if the last execution of
     * RTI Persistence Service finished gracefully or there were errors
     *
     * \default NULL (the file ps.pid will not be used)
     */
    char * info_dir;

    /*e
     * @brief Indicates whether or not RTI Persistence Service
     *        must restore its state from the persistent storage
     *
     *  Set to 0 to not restore the state
     *  Set to 1 to restore the state
     *  Set to -1 to use the XML value for restore
     *
     * \default -1 Use the XML value
     */
    int restore;

    /*e
     * @brief The verbosity of RTI Persistence Service
     *
     * Values:
     *  <ul>
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_SILENT
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_EXCEPTIONS
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_WARNINGS
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_INFO
     *  </ul>
     *
     * \default RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_EXCEPTIONS
     */
    int service_verbosity;

    /*e
     * @brief The verbosity of RTI Connext core libraries
     *
     * Values:
     *  <ul>
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_SILENT
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_EXCEPTIONS
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_WARNINGS
     *  <li> \ref RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_INFO
     *  </ul>
     *
     * \default RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_EXCEPTIONS
     */
    int dds_verbosity;

    /*e
     *
     * @brief Path to an RTI Persistence Service license  file
     *
     * If not \c NULL, this file is checked for a valid license; otherwise,
     * default location will be used. This parameter is not used in
     * unlicensed versions.
     *
     * \default NULL.
     */
    char * license_file;

    /*e
     *
     * @brief Enable database locking
     *
     * Persistence Service will lock the database by creating an entry in a
     * specific table in the datatabase
     *
     * This entry is to avoid multiple instances of RTI Persistence
     * Service are accessing to the same database at the same time.
     *
     * \default DDS_BOOLEAN_TRUE
     */
    DDS_Boolean enable_database_locking;
};

extern PERSISTENCEDllExport
const struct RTI_PersistenceServiceProperty  RTI_PersistenceServiceProperty_INITIALIZER;

extern PERSISTENCEDllExport
const int  RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_INFO;

extern PERSISTENCEDllExport
const int  RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_WARNINGS;

extern PERSISTENCEDllExport
const int  RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_EXCEPTIONS;

extern PERSISTENCEDllExport
const int  RTI_PERSISTENCE_SERVICE_LOG_VERBOSITY_SILENT;

extern PERSISTENCEDllExport 
struct RTI_PersistenceService * RTI_PersistenceService_new(struct RTI_PersistenceServiceProperty * property);

extern PERSISTENCEDllExport 
void RTI_PersistenceService_delete(struct RTI_PersistenceService * self);

extern PERSISTENCEDllExport 
DDS_Boolean RTI_PersistenceService_start(struct RTI_PersistenceService * self);

extern PERSISTENCEDllExport 
DDS_Boolean RTI_PersistenceService_stop(struct RTI_PersistenceService * self);

extern PERSISTENCEDllExport
DDS_Boolean RTI_PersistenceService_initialize_globals();

extern PERSISTENCEDllExport
void RTI_PersistenceService_finalize_globals();


  #ifdef __cplusplus
    }	/* extern "C" */
  #endif

#endif /* persistence_service_h */
