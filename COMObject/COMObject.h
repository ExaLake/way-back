/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Sun Nov 28 18:24:24 1999
 */
/* Compiler settings for C:\project\COMObject\COMObject.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __COMObject_h__
#define __COMObject_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IObject1_FWD_DEFINED__
#define __IObject1_FWD_DEFINED__
typedef interface IObject1 IObject1;
#endif 	/* __IObject1_FWD_DEFINED__ */


#ifndef __Object1_FWD_DEFINED__
#define __Object1_FWD_DEFINED__

#ifdef __cplusplus
typedef class Object1 Object1;
#else
typedef struct Object1 Object1;
#endif /* __cplusplus */

#endif 	/* __Object1_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IObject1_INTERFACE_DEFINED__
#define __IObject1_INTERFACE_DEFINED__

/* interface IObject1 */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IObject1;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C1ADB650-A5BF-11D3-8651-00C01501BDC4")
    IObject1 : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE PopMessageBox( 
            CHAR __RPC_FAR *message,
            INT hWnd) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IObject1Vtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IObject1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IObject1 __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IObject1 __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IObject1 __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IObject1 __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IObject1 __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IObject1 __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *PopMessageBox )( 
            IObject1 __RPC_FAR * This,
            CHAR __RPC_FAR *message,
            INT hWnd);
        
        END_INTERFACE
    } IObject1Vtbl;

    interface IObject1
    {
        CONST_VTBL struct IObject1Vtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IObject1_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IObject1_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IObject1_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IObject1_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IObject1_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IObject1_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IObject1_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IObject1_PopMessageBox(This,message,hWnd)	\
    (This)->lpVtbl -> PopMessageBox(This,message,hWnd)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IObject1_PopMessageBox_Proxy( 
    IObject1 __RPC_FAR * This,
    CHAR __RPC_FAR *message,
    INT hWnd);


void __RPC_STUB IObject1_PopMessageBox_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IObject1_INTERFACE_DEFINED__ */



#ifndef __COMOBJECTLib_LIBRARY_DEFINED__
#define __COMOBJECTLib_LIBRARY_DEFINED__

/* library COMOBJECTLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_COMOBJECTLib;

EXTERN_C const CLSID CLSID_Object1;

#ifdef __cplusplus

class DECLSPEC_UUID("C1ADB651-A5BF-11D3-8651-00C01501BDC4")
Object1;
#endif
#endif /* __COMOBJECTLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
