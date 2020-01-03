
#ifndef _H_CORBA12
#define _H_CORBA12

#include <som.h>
#include <somapi.h>
#include <somcorba.h>
#include <somd.h>
#include <request.h>
#include <nvlist.h>
#include <cntxt.h>
#include <containd.h>
#include <containr.h>
#include <repostry.h>
#include <moduledf.h>
#include <intfacdf.h>
#include <attribdf.h>
#include <operatdf.h>
#include <paramdef.h>
#include <typedef.h>
#include <constdef.h>
#include <excptdef.h>
#include <orb.h>
#include <somdobj.h>
#include <boa.h>

/* Basic data types  CORBA 5.7, pp 93-94 */

#define CORBA_short           short
#define CORBA_long            long
#define CORBA_unsigned_short  unsigned short
#define CORBA_unsigned_long   unsigned_long
#define CORBA_float           float
#define CORBA_double          double
#define CORBA_char            char
#define CORBA_boolean         boolean
#define CORBA_octet           octet
#define CORBA_enum            enum
#define CORBA_TypeCode        TypeCode
typedef struct CORBA_any {
        CORBA_TypeCode _type;
        void *_value;} CORBA_any;

/* CORBA 5.16, p. 101 */
#define CORBA_free      ORBfree

/* CORBA 5.19, p. 104 */

CORBA_enum CORBA_exception_type { 
      CORBA_NO_EXCEPTION, CORBA_USER_EXCEPTION, CORBA_SYSTEM_EXCEPTION};
#define CORBA_Environment     Environment 

#define CORBA_exception_id     somExceptionId
#define CORBA_exception_value  somExceptionValue 
#define CORBA_exception_free   somExceptionFree 

/* CORBA 6.1.1 pp. 110-111 */
#define CORBA_NamedValue        NamedValue 
#define CORBA_Flags       Flags 

#define CORBA_ARG_IN      ARG_IN
#define CORBA_ARG_OUT     ARG_OUT
#define CORBA_ARG_IN_OUT  ARG_IN_OUT

/* CORBA 6.2.1. p. 114 */
#define CORBA_OUT_LIST_MEMORY   OUT_LIST_MEMORY

/* CORBA 6.3.2 p. 117 */
#define CORBA_INV_NO_RESPONSE   INV_NO_RESPONSE
#define CORBA_INV_TERM_ON_ERR   INV_TERM_ON_ERR

/* CORBA 6.3.4 p. 118 */
#define CORBA_RESP_NO_WAIT      RESP_NO_WAIT 

/* CORBA 6.4.2 p. 120 */
#define CORBA_IN_COPY_VALUE     IN_COPY_VALUE
#define CORBA_DEPENDENT_LIST    DEPENDENT_LIST

#define CORBA_OBJECT_NIL        OBJECT_NIL
  
/* CORBA 6.1.3 p. 112 */
#define CORBA_ORBStatus    Status 

/* CORBA 6.2 p. 113 */  
#define CORBA_Request              Request
#define CORBA_Request_add_arg      Request_add_arg
#define CORBA_Request_invoke       Request_invoke
#define CORBA_Request_delete       Request_delete
#define CORBA_Request_send         Request_send
#define CORBA_Request_get_response Request_get_response

/* CORBA 6.3.2 p. 117 */
#define CORBA_send_multiple_requests   send_multiple_requests

/* CORBA 6.3.4 p. 118 */
#define CORBA_get_next_response    get_next_response

/* CORBA 6.4. p. 119  */
#define CORBA_NVLIST               NVList 
#define CORBA_NVList_add_item      NVList_add_item
#define CORBA_NVList_free          NVList_free
#define CORBA_NVList_free_memory   NVList_free_memory
#define CORBA_NVList_get_count     NVList_get_count


/* CORBA 6.6 p. 123 */
#define CORBA_Context                  Context 
#define CORBA_Context_set_one_value    Context_set_one_value
#define CORBA_Context_set_values       Context_set_values
#define CORBA_Context_get_values       Context_get_values
#define CORBA_Context_delete_values    Context_delete_values
#define CORBA_Context_create_child     Context_create_child
#define CORBA_Context_delete           Context_delete

/* CORBA 6.6.4 p. 125 */
#define CORBA_CTX_RESTRICT_SCOPE       CTX_RESTRICT_SCOPE
/* CORBA 6.6.7 p. 126 */
#define CORBA_CTX_DELETE_DESCENDENTS   CTX_DELETE_DESCENDENTS


/* CORBA 7.5.1 pp 134-135 */
#define CORBA_Contained                Contained 
#define CORBA_Contained_Description    Contained_Description
#define CORBA_Contained_within         Contained_within
#define CORBA_Contained_Describe       Contained_Describe

#define CORBA_Container                   Container 
#define CORBA_Container_Description       Container_Description
#define CORBA_Container_contents          Container_contents
#define CORBA_Container_lookup_name       Container_lookup_name
#define CORBA_Container_describe_contents Container_describe_contents

/* CORBA 7.5.2 p 137 */
#define CORBA_Repository                  Repository 
#define CORBA_Repository_lookup_id  Repository_lookup_id 

/* CORBA 7.5.3 p. 137 */
#define CORBA_ModuleDef                   ModuleDef 
#define CORBA_ModuleDef_ModuleDescription ModuleDef_ModuleDescription  

/* CORBA 7.5.4 p. 138 */
#define CORBA_InterfaceDef                            InterfaceDef 
#define CORBA_InterfaceDef_FullDescription            InterfaceDef_FullInterfaceDef     
#define CORBA_InterfaceDef_InterfaceDescription       InterfaceDef_InterfaceInterfaceDef     
#define CORBA_InterfaceDef_base_interfaces      InterfaceDef_base_interfaces
#define CORBA_InterfaceDef_describe_interface   InterfaceDef_describe_interface

/* CORBA 7.5.5  p. 139 */
#define CORBA_AttributeDef                      AttributeDef 
#define CORBA_AttributeDef_AttributeDescription AttributeDef_AttributeDescription 


/* CORBA 7.5.6  p. 139 */
#define CORBA_OperationDef                      OperationDef 
#define CORBA_OperationDef_OperationDescription OperationDef_OperationDescription 

/* CORBA 7.5.7  p. 140 */
#define CORBA_ParameterDef                      ParameterDef 
#define CORBA_ParameterDef_ParameterDescription ParameterDef_ParameterDescription 

/* CORBA 7.5.8  p. 141 */
#define CORBA_TypeDef                  TypeDef 
#define CORBA_TypeDef_TypeDescription  TypeDef_TypeDescription 

/* CORBA 7.5.9  p. 141 */
#define CORBA_ConstantDef                      ConstantDef 
#define CORBA_ConstantDef_ConstantDescription  ConstantDef_ConstantDescription 

/* CORBA 7.5.10  p. 142 */
#define CORBA_ExceptionDef                      ExceptionDef 
#define CORBA_ExceptionDef_ExceptionDescription ExceptionDef_ExceptionDescription 

/* CORBA 7.5.11  p. 143 */
#define CORBA_ExceptionDef                      ExceptionDef 
#define CORBA_ExceptionDef_ExceptionDescription ExceptionDef_ExceptionDescription 

/* CORBA 7.6.1  p. 143 */
#define CORBA_TCKind               TCKind 
#define CORBA_TypeCode_Bounds      TypeCode_Bounds
#define CORBA_TypeCode_equal       TypeCode_equal
#define CORBA_TypeCode_kind        TypeCode_kind
#define CORBA_TypeCode_param_count TypeCode_param_count
#define CORBA_TypeCode_parameter   TypeCode_parameter

/* CORBA 8.1, p. 148 */
#define CORBA_ORB                       ORB 
#define CORBA_ORB_object_to_string      ORB_object_to_string
#define CORBA_ORB_string_to_object      ORB_string_to_object
#define CORBA_ORB_create_list           ORB_create_list
#define CORBA_ORB_create_operation_list ORB_create_operation_list

/* CORBA 8.2 p. 149 */
#define  CORBA_Object                     SOMDObject 
#define  CORBA_Object_get_implementation  SOMDObject_get_implementation 
#define  CORBA_Object_get_interface       SOMDObject_get_interface
#define  CORBA_Object_is_nil              SOMDObject_is_nil
#define  CORBA_Object_duplicate           SOMDObject_duplicate
#define  CORBA_Object_release             SOMDObject_release  
#define  CORBA_Object_create_request      SOMDObject_create_request

/* CORBA 9.2, p. 154 */
#define  CORBA_BOA                        BOA 
#define  CORBA_BOA_create	          BOA_create
#define  CORBA_BOA_dispose	          BOA_dispose
#define  CORBA_BOA_get_id		  BOA_get_id
#define  CORBA_BOA_change_implementation  BOA_change_implementation
#define  CORBA_BOA_get_principal          BOA_get_principal
#define  CORBA_BOA_set_exception          BOA_set_exception
#define  CORBA_BOA_impl_is_ready          BOA_impl_is_ready
#define  CORBA_BOA_deactivate_impl        BOA_deactivate_impl
#define  CORBA_BOA_obj_is_ready           BOA_obj_is_ready 
#define  CORBA_BOA_deactivate_obj         BOA_deactivate_obj

#endif /* _H_CORBA12 */













