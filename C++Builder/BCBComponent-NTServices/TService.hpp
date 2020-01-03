// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'TService.pas' rev: 3.00

#ifndef TServiceHPP
#define TServiceHPP
#include <NTCommon.hpp>
#include <DsgnIntf.hpp>
#include <WinSvc.hpp>
#include <Dialogs.hpp>
#include <Forms.hpp>
#include <Controls.hpp>
#include <Graphics.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Messages.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Tservice
{
//-- type declarations -------------------------------------------------------
enum TDesiredManagerAccess { M_CONNECT, M_CREATE_SERVICE, M_ENUMERATE_SERVICE, M_LOCK, M_QUERY_LOCK_STATUS, 
	M_MODIFY_BOOT_CONFIG };

typedef Set<TDesiredManagerAccess, M_CONNECT, M_MODIFY_BOOT_CONFIG>  TManagerAccess;

enum TDesiredServiceAccess { S_ALL_ACCESS, S_CHANGE_CONFIG, S_ENUMERATE_DEPENDENTS, S_INTERROGATE, S_PAUSE_CONTINUE, 
	S_QUERY_CONFIG, S_QUERY_STATUS, S_START, S_STOP, S_USER_DEFINED_CONTROL, S_DELETE };

typedef Set<TDesiredServiceAccess, S_ALL_ACCESS, S_DELETE>  TServiceAccess;

enum TStartType { BOOT_START, SYSTEM_START, AUTO_START, DEMAND_START, DISABLED };

enum TErrorType { ERROR_IGNORE, ERROR_NORMAL, ERROR_SEVERE, ERROR_CRITICAL };

enum TServiceType { KERNEL_DRIVER, FILE_SYSTEM_DRIVER, ADAPTER, RECOGNIZER_DRIVER, WIN32_OWN_PROCESS, 
	WIN32_SHARE_PROCESS, INTERACTIVE_PROCESS };

typedef Set<TServiceType, KERNEL_DRIVER, INTERACTIVE_PROCESS>  TServiceTypes;

enum TServiceState { STATE_ACTIVE, STATE_INACTIVE };

typedef Set<TServiceState, STATE_ACTIVE, STATE_INACTIVE>  TServiceStates;

enum TEnumSevice { DRIVER, PROCESS };

typedef Set<TEnumSevice, DRIVER, PROCESS>  TEnumSevices;

enum TCurrentState { STOPPED, START_PENDING, STOP_PENDING, RUNNING, CONTINUE_PENDING, PAUSE_PENDING, 
	PAUSED };

enum TControlAccepted { ACCEPT_STOP, ACCEPT_PAUSE_CONTINUE, ACCEPT_SHUTDOWN };

typedef Set<TControlAccepted, ACCEPT_STOP, ACCEPT_SHUTDOWN>  TControlAcceptedSet;

enum TControlCode { CONTROL_STOP, CONTROL_PAUSE, CONTROL_CONTINUE, CONTROL_INTERROGATE, CONTROL_SHUTDOWN 
	};

typedef System::AnsiString TLoadOrder;

class DELPHICLASS TServiceStatusClass;
class PASCALIMPLEMENTATION TServiceStatusClass : public System::TObject 
{
	typedef System::TObject inherited;
	
public:
	System::AnsiString ServiceName;
	System::AnsiString DisplayedName;
	TServiceTypes ServiceType;
	TCurrentState CurrentState;
	TControlAcceptedSet ControlsAccepted;
	int Win32ExitCode;
	int ServiceSpecificExitCode;
	int CheckPoint;
	int WaitHint;
public:
	/* TObject.Create */ __fastcall TServiceStatusClass(void) : System::TObject() { }
	/* TObject.Destroy */ __fastcall virtual ~TServiceStatusClass(void) { }
	
};

class DELPHICLASS TEnumList;
class PASCALIMPLEMENTATION TEnumList : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	Classes::TList* FList;
	System::TObject* FParent;
	
protected:
	int __fastcall GetCount(void);
	TServiceStatusClass* __fastcall GetItem(int AIndex);
	void __fastcall SetItem(int AIndex, TServiceStatusClass* AValue);
	
public:
	__fastcall virtual TEnumList(System::TObject* AOwner);
	__fastcall virtual ~TEnumList(void);
	void __fastcall Delete(int AIndex);
	void __fastcall Clear(void);
	__property TServiceStatusClass* Items[int AIndex] = {read=GetItem, write=SetItem/*, default*/};
	int __fastcall IndexOf(System::AnsiString AServiceName);
	__property int Count = {read=GetCount, nodefault};
	TServiceStatusClass* __fastcall Add(void);
};

class DELPHICLASS TNTService;
class PASCALIMPLEMENTATION TNTService : public Ntcommon::TNTPersistent 
{
	typedef Ntcommon::TNTPersistent inherited;
	
private:
	int FManagerHandle;
	int FServiceHandle;
	System::AnsiString FDatabaseName;
	System::AnsiString FServiceName;
	System::AnsiString FDisplayName;
	System::AnsiString FBinaryPathName;
	bool FActiveManager;
	bool FActiveService;
	TManagerAccess FManagerAccess;
	TServiceAccess FServiceAccess;
	TStartType FStartType;
	TErrorType FErrorControl;
	TServiceTypes FServiceType;
	System::AnsiString FLoadOrder;
	int FTagId;
	Classes::TStrings* FDependencies;
	System::AnsiString FServiceStartName;
	System::AnsiString FPassword;
	bool FDBLocked;
	void *FDBLockHandle;
	TServiceTypes __fastcall DWORDToServiceType(int dw);
	int __fastcall ServiceTypeToDWORD(TServiceTypes AValue);
	TCurrentState __fastcall DWORDToCurrentState(int dw);
	TControlAcceptedSet __fastcall DWORDToControlsAccepted(int dw);
	TStartType __fastcall DWORDToStartType(int dw);
	TErrorType __fastcall DWORDToErrorType(int dw);
	int __fastcall ErrorControlToDWORD(TErrorType AValue);
	int __fastcall StartTypeToDWORD(TStartType AValue);
	int __fastcall ManagerAccessToDWORD(TManagerAccess AValue);
	int __fastcall ServiceAccessToDWORD(TServiceAccess AValue);
	virtual void __fastcall Loaded(void);
	
protected:
	void __fastcall OpenSCmanager(void);
	void __fastcall Openservice(void);
	void __fastcall CloseService(void);
	void __fastcall CloseSCManager(void);
	void __fastcall ChangeServiceconfig(void);
	virtual void __fastcall SetMachineName(System::AnsiString AValue);
	void __fastcall SetDatabaseName(System::AnsiString AValue);
	void __fastcall SetActiveManager(bool AValue);
	void __fastcall SetActiveService(bool AValue);
	void __fastcall SetServiceName(System::AnsiString AValue);
	void __fastcall SetDisplayName(System::AnsiString AValue);
	void __fastcall SetBinaryPathName(System::AnsiString AValue);
	void __fastcall SetStartType(TStartType AValue);
	void __fastcall SetErrorControl(TErrorType AValue);
	void __fastcall SetServiceType(TServiceTypes AValue);
	void __fastcall SetLoadOrder(System::AnsiString AValue);
	void __fastcall SetTagId(int AValue);
	void __fastcall SetDependencies(Classes::TStrings* AValue);
	void __fastcall SetServiceStartName(System::AnsiString AValue);
	void __fastcall SetPassword(System::AnsiString AValue);
	void __fastcall SetManagerAccess(TManagerAccess AValue);
	void __fastcall SetServiceAccess(TServiceAccess AValue);
	void __fastcall SetDBLocked(bool AValue);
	
public:
	__fastcall virtual TNTService(Classes::TComponent* AOwner);
	__fastcall virtual ~TNTService(void);
	__property int ManagerHandle = {read=FManagerHandle, nodefault};
	__property int ServiceHandle = {read=FServiceHandle, nodefault};
	__property void * DBLockHandle = {read=FDBLockHandle};
	__property bool DBLocked = {read=FDBLocked, write=SetDBLocked, nodefault};
	void __fastcall DeleteService(void);
	void __fastcall Createservice(void);
	void __fastcall Startservice(void);
	void __fastcall ControlService(TControlCode Code);
	System::AnsiString __fastcall GetServiceDisplayName(System::AnsiString AServiceName);
	System::AnsiString __fastcall GetServiceKeyName(System::AnsiString ADisplayName);
	TServiceStatusClass* __fastcall QueryServiceStatus(void);
	void __fastcall NotifyBootConfigStatus(bool BootAcceptable);
	_QUERY_SERVICE_LOCK_STATUSA __fastcall QueryServiceLockStatus();
	TEnumList* __fastcall GetServiceList(TServiceStates AState, TEnumSevices AType);
	TEnumList* __fastcall GetDependentServiceList(TServiceStates AState);
	void __fastcall GetOrderGroupList(Classes::TStrings* List);
	
__published:
	__property MachineName ;
	__property System::AnsiString DatabaseName = {read=FDatabaseName, write=SetDatabaseName};
	__property bool ActiveManager = {read=FActiveManager, write=SetActiveManager, nodefault};
	__property bool ActiveService = {read=FActiveService, write=SetActiveService, nodefault};
	__property TManagerAccess ManagerAccess = {read=FManagerAccess, write=SetManagerAccess, nodefault};
		
	__property TServiceAccess ServiceAccess = {read=FServiceAccess, write=SetServiceAccess, nodefault};
		
	__property System::AnsiString ServiceName = {read=FServiceName, write=SetServiceName};
	__property System::AnsiString DisplayName = {read=FDisplayName, write=SetDisplayName};
	__property System::AnsiString BinaryPathName = {read=FBinaryPathName, write=SetBinaryPathName};
	__property TStartType StartType = {read=FStartType, write=SetStartType, nodefault};
	__property TErrorType ErrorControl = {read=FErrorControl, write=SetErrorControl, nodefault};
	__property TServiceTypes ServiceType = {read=FServiceType, write=SetServiceType, nodefault};
	__property System::AnsiString LoadOrder = {read=FLoadOrder, write=SetLoadOrder};
	__property int TagId = {read=FTagId, write=SetTagId, nodefault};
	__property Classes::TStrings* Dependencies = {read=FDependencies, write=SetDependencies};
	__property System::AnsiString ServiceStartName = {read=FServiceStartName, write=SetServiceStartName
		};
	__property System::AnsiString Password = {read=FPassword, write=SetPassword};
};

//-- var, const, procedure ---------------------------------------------------
#define SERVICE_KERNEL_DRIVER (Byte)(1)
#define SERVICE_FILE_SYSTEM_DRIVER (Byte)(2)
#define SERVICE_ADAPTER (Byte)(4)
#define SERVICE_RECOGNIZER_DRIVER (Byte)(8)
#define SERVICE_DRIVER (Byte)(11)
#define SERVICE_WIN32_OWN_PROCESS (Byte)(16)
#define SERVICE_WIN32_SHARE_PROCESS (Byte)(32)
#define SERVICE_WIN32 (Byte)(48)
#define SERVICE_INTERACTIVE_PROCESS (Word)(256)
#define SERVICE_TYPE_ALL (Word)(319)
#define SERVICE_BOOT_START (Byte)(0)
#define SERVICE_SYSTEM_START (Byte)(1)
#define SERVICE_AUTO_START (Byte)(2)
#define SERVICE_DEMAND_START (Byte)(3)
#define SERVICE_DISABLED (Byte)(4)
#define SERVICE_ERROR_IGNORE (Byte)(0)
#define SERVICE_ERROR_NORMAL (Byte)(1)
#define SERVICE_ERROR_SEVERE (Byte)(2)
#define SERVICE_ERROR_CRITICAL (Byte)(3)

}	/* namespace Tservice */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Tservice;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// TService
