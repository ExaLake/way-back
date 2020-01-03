// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AdvApi32.pas' rev: 3.00

#ifndef AdvApi32HPP
#define AdvApi32HPP
#include <WinSvc.hpp>
#include <NT_vs_95.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Advapi32
{
//-- type declarations -------------------------------------------------------
typedef BOOL __stdcall (*TChangeServiceConfig)(int hService, int dwServiceType, int dwStartType, int 
	dwErrorControl, char * lpBinaryPathName, char * lpLoadOrderGroup, PDWORD lpdwTagId, char * lpDependencies
	, char * lpServiceStartName, char * lpPassword, char * lpDisplayName);

typedef BOOL __stdcall (*TCloseServiceHandle)(int hSCObject);

typedef BOOL __stdcall (*TControlService)(int hService, int dwControl, _SERVICE_STATUS &lpServiceStatus
	);

typedef int __stdcall (*TCreateService)(int hSCManager, char * lpServiceName, char * lpDisplayName, 
	int dwDesiredAccess, int dwServiceType, int dwStartType, int dwErrorControl, char * lpBinaryPathName
	, char * lpLoadOrderGroup, PDWORD lpdwTagId, char * lpDependencies, char * lpServiceStartName, char * 
	lpPassword);

typedef BOOL __stdcall (*TDeleteService)(int hService);

typedef BOOL __stdcall (*TEnumDependentServices)(int hService, int dwServiceState, _ENUM_SERVICE_STATUSA 
	&lpServices, int cbBufSize, int &pcbBytesNeeded, int &lpServicesReturned);

typedef BOOL __stdcall (*TEnumServicesStatus)(int hSCManager, int dwServiceType, int dwServiceState, 
	_ENUM_SERVICE_STATUSA &lpServices, int cbBufSize, int &pcbBytesNeeded, int &lpServicesReturned, int 
	&lpResumeHandle);

typedef BOOL __stdcall (*TGetServiceDisplayName)(int hSCManager, char * lpServiceName, char * lpDisplayName
	, int &lpcchBuffer);

typedef BOOL __stdcall (*TGetServiceKeyName)(int hSCManager, char * lpDisplayName, char * lpServiceName
	, int &lpcchBuffer);

typedef void * __stdcall (*TLockServiceDatabase)(int hSCManager);

typedef BOOL __stdcall (*TNotifyBootConfigStatus)(BOOL BootAcceptable);

typedef int __stdcall (*TOpenSCManager)(char * lpMachineName, char * lpDatabaseName, int dwDesiredAccess
	);

typedef int __stdcall (*TOpenService)(int hSCManager, char * lpServiceName, int dwDesiredAccess);

typedef BOOL __stdcall (*TFQueryServiceConfig)(int hService, _QUERY_SERVICE_CONFIGA &lpServiceConfig
	, int cbBufSize, int &pcbBytesNeeded);

typedef BOOL __stdcall (*TFQueryServiceLockStatus)(int hSCManager, _QUERY_SERVICE_LOCK_STATUSA &lpLockStatus
	, int cbBufSize, int &pcbBytesNeeded);

typedef BOOL __stdcall (*TQueryServiceStatus)(int hService, _SERVICE_STATUS &lpServiceStatus);

typedef BOOL __stdcall (*TStartService)(int hService, int dwNumServiceArgs, char * &lpServiceArgVectors
	);

typedef BOOL __stdcall (*TUnlockServiceDatabase)(void * ScLock);

typedef int __stdcall (*TRegConnectRegistry)(char * lpMachineName, HKEY hKey, HKEY &phkResult);

typedef int __stdcall (*TRegOpenKeyEx)(HKEY hKey, char * lpSubKey, int ulOptions, int samDesired, HKEY 
	&phkResult);

typedef int __stdcall (*TRegCloseKey)(HKEY hKey);

typedef int __stdcall (*TRegEnumKeyEx)(HKEY hKey, int dwIndex, char * lpName, int &lpcbName, void * 
	lpReserved, char * lpClass, PDWORD lpcbClass, Windows::PFileTime lpftLastWriteTime);

typedef int __stdcall (*TRegQueryValueEx)(HKEY hKey, char * lpValueName, void * lpReserved, PDWORD lpType
	, Windows::PByte lpData, PDWORD lpcbData);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TChangeServiceConfig ChangeServiceConfig;
extern PACKAGE TCloseServiceHandle CloseServiceHandle;
extern PACKAGE TControlService ControlService;
extern PACKAGE TCreateService CreateService;
extern PACKAGE TDeleteService DeleteService;
extern PACKAGE TEnumDependentServices EnumDependentServices;
extern PACKAGE TEnumServicesStatus EnumServicesStatus;
extern PACKAGE TGetServiceDisplayName GetServiceDisplayName;
extern PACKAGE TGetServiceKeyName GetServiceKeyName;
extern PACKAGE TLockServiceDatabase LockServiceDatabase;
extern PACKAGE TNotifyBootConfigStatus NotifyBootConfigStatus;
extern PACKAGE TOpenSCManager OpenSCManager;
extern PACKAGE TOpenService OpenService;
extern PACKAGE TFQueryServiceConfig QueryServiceConfig;
extern PACKAGE TFQueryServiceLockStatus QueryServiceLockStatus;
extern PACKAGE TQueryServiceStatus QueryServiceStatus;
extern PACKAGE TStartService StartService;
extern PACKAGE TUnlockServiceDatabase UnlockServiceDatabase;
extern PACKAGE TRegConnectRegistry RegConnectRegistry;
extern PACKAGE TRegOpenKeyEx RegOpenKeyEx;
extern PACKAGE TRegCloseKey RegCloseKey;
extern PACKAGE TRegEnumKeyEx RegEnumKeyEx;
extern PACKAGE TRegQueryValueEx RegQueryValueEx;

}	/* namespace Advapi32 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Advapi32;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// AdvApi32
