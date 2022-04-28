/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)rtixml_extension.h    generated by: makeheader    Thu Feb 28 22:11:39 2019
 *
 *		built from:	extension.ifc
 */

#ifndef rtixml_extension_h
#define rtixml_extension_h


  #include "rtixml/rtixml_dll.h"
  #include "rtixml/rtixml_infrastructure.h"
  #include "rtixml/rtixml_object.h"

  #ifdef __cplusplus
      extern "C" {
  #endif


struct RTIXMLExtensionClass;

 
typedef void (*RTIXMLExtensionClassOnStartTagFunction)(
    struct RTIXMLObject * self, 
    const char * tagName,
    const char ** attr,
    struct RTIXMLContext * context);

 
typedef void (*RTIXMLExtensionClassOnEndTagFunction)(
    struct RTIXMLObject * self, 
    const char * tagName,
    const char * elementText,  
    struct RTIXMLContext * context);

 
typedef struct RTIXMLObject * (*RTIXMLExtensionClassNewObjectFunction)(
    const struct RTIXMLExtensionClass * extensionClass,
    const struct RTIXMLObject * parentObject,
    const char ** attr,
    struct RTIXMLContext * context);

 
typedef void (*RTIXMLExtensionClassDeleteObjectFunction)(
    struct RTIXMLObject * self);

 
typedef void (*RTIXMLExtensionClassSaveObjectFunction)(
    struct RTIXMLObject * self, struct RTIXMLSaveContext * dst);


extern	RTIXMLDllExport const char * RTIXMLExtensionClass_getTagName(
        const struct RTIXMLExtensionClass * self);


extern	RTIXMLDllExport void * RTIXMLExtensionClass_getUserData(struct RTIXMLExtensionClass * self);


extern	RTIXMLDllExport struct RTIXMLExtensionClass * RTIXMLExtensionClass_new(
    const char * tagName,
    void * userData,
    RTIBool allowDuplicatedObjects,
    RTIBool isRoot,
    RTIXMLExtensionClassOnStartTagFunction onStartTagFcn,
    RTIXMLExtensionClassOnEndTagFunction onEndTagFcn,
    RTIXMLExtensionClassNewObjectFunction newObjectFcn,
    RTIXMLExtensionClassDeleteObjectFunction deleteObjectFcn,
    RTIXMLExtensionClassSaveObjectFunction saveObjectFcn);


extern	RTIXMLDllExport void RTIXMLExtensionClass_delete(struct RTIXMLExtensionClass * self);


extern	RTIXMLDllExport void RTIXMLExtensionClass_finalize(struct RTIXMLExtensionClass * self);


extern	RTIXMLDllExport RTIBool RTIXMLExtensionClass_initialize(
    struct RTIXMLExtensionClass * self,
    const char * tagName,
    void * userData,
    RTIBool allowDuplicatedObjects,
    RTIBool isRoot,
    RTIXMLExtensionClassOnStartTagFunction onStartTagFcn,
    RTIXMLExtensionClassOnEndTagFunction onEndTagFcn,
    RTIXMLExtensionClassNewObjectFunction newObjectFcn,
    RTIXMLExtensionClassDeleteObjectFunction deleteObjectFcn,
    RTIXMLExtensionClassSaveObjectFunction saveObjectFcn);


  #ifdef __cplusplus
    }	/* extern "C" */
  #endif
  #include "rtixml/rtixml_extension_impl.h"

#endif /* rtixml_extension_h */
