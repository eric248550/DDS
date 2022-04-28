/* (c) Copyright 2003-2018, Real-Time Innovations, Inc. All rights reserved. */
/*
 * @(#)rtixml_object_impl.h    generated by: makeheader    Thu Feb 28 22:11:39 2019
 *
 *		built from:	object_impl.ifc
 */

#ifndef rtixml_object_impl_h
#define rtixml_object_impl_h


#include "reda/reda_inlineList.h"
#include "reda/reda_skiplist.h"
  #ifdef __cplusplus
      extern "C" {
  #endif


struct RTIXMLObject { 
    /*i
      @brief This node is used to link with the siblings list
    */
    struct REDAInlineListNode _node;
    /*i
      @brief This node is used to link with the parser processing list
    */
    struct REDAInlineListNode _node2;
    /*i 
      @brief Init flag 
    */
    int _init; 
    /*i 
      @brief Full qualified name 
    */
    char * _fullyQualifiedName;
    /*i
      @brief Object name 
    */
    char * _name;
    /*i
      @brief Indicates if the object was duplicated in the XML file.

      Duplicated objects are objects with the same fully qualified name.
    */
    RTIBool duplicated;
    /*i
      @brief Indicates if the object was created from an <include>
    */
    RTIBool included;

    /*i
      @brief root object 
    */
    struct RTIXMLObject * _root; 
    /*i 
      @brief parent object 
    */
    struct RTIXMLObject * _parent; 
    /*i 
      @brief Base Object
    */
    struct RTIXMLObject * _base;
    struct REDASkiplistDescription _listDesc;
    /*i
      @brief List of child objects maintained in a InlineList 
    */
    struct REDASkiplist _skipChildList;
    /*i 
      @brief List of child objects maintained in a Skiplist 
    */
    struct REDAInlineList _inlineChildList;
    /*i 
      @brief Extension class associated with the Object
    */
    struct RTIXMLExtensionClass * _cl;
    /*i 
      @brief Flag to indicate whether the save operation can be ignored
    */
    RTIBool ignoreSave;
};


#ifdef __cplusplus
    }	/* extern "C" */
#endif

#endif /* rtixml_object_impl_h */
