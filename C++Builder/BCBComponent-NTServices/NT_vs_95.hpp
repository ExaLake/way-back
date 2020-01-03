// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'NT_vs_95.pas' rev: 3.00

#ifndef NT_vs_95HPP
#define NT_vs_95HPP
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Nt_vs_95
{
//-- type declarations -------------------------------------------------------
typedef void *PSomeChar;

typedef BOOL __stdcall (*TLookupAccountName)(char * lpSystemName, char * lpAccountName, void * Sid, 
	int &cbSid, char * ReferencedDomainName, int &cbReferencedDomainName, int &peUse);

typedef BOOL __stdcall (*TLookupAccountSid)(char * lpSystemName, void * Sid, char * Name, int &cbName
	, char * ReferencedDomainName, int &cbReferencedDomainName, int &peUse);

typedef BOOL __stdcall (*TLookupPrivilegeValue)(char * lpSystemName, char * lpName, _LARGE_INTEGER &
	lpLuid);

typedef BOOL __stdcall (*TLookupPrivilegeName)(char * lpSystemName, _LARGE_INTEGER &lpLuid, char * lpName
	, int &cbName);

typedef BOOL __stdcall (*TAllocateAndInitializeSid)(const _SID_IDENTIFIER_AUTHORITY &pIdentifierAuthority
	, Byte nSubAuthorityCount, int nSubAuthority0, int nSubAuthority1, int nSubAuthority2, int nSubAuthority3
	, int nSubAuthority4, int nSubAuthority5, int nSubAuthority6, int nSubAuthority7, void * &pSid);

typedef BOOL __stdcall (*TEqualSid)(void * pSid1, void * pSid2);

typedef BOOL __stdcall (*TBackupEventLog)(int hEventLog, char * lpBackupFileName);

typedef BOOL __stdcall (*TClearEventLog)(int hEventLog, char * lpBackupFileName);

typedef BOOL __stdcall (*TCloseEventLog)(int hEventLog);

typedef BOOL __stdcall (*TDeregisterEventSource)(int hEventLog);

typedef BOOL __stdcall (*TGetNumberOfEventLogRecords)(int hEventLog, int &NumberOfRecords);

typedef BOOL __stdcall (*TGetOldestEventLogRecord)(int hEventLog, int &OldestRecord);

typedef BOOL __stdcall (*TNotifyChangeEventLog)(int hEventLog, int hEvent);

typedef int __stdcall (*TOpenBackupEventLog)(char * lpUNCServerName, char * lpFileName);

typedef int __stdcall (*TOpenEventLog)(char * lpUNCServerName, char * lpSourceName);

typedef BOOL __stdcall (*TReadEventLog)(int hEventLog, int dwReadFlags, int dwRecordOffset, void * lpBuffer
	, int nNumberOfBytesToRead, int &pnBytesRead, int &pnMinNumberOfBytesNeeded);

typedef int __stdcall (*TRegisterEventSource)(char * lpUNCServerName, char * lpSourceName);

typedef BOOL __stdcall (*TReportEvent)(int hEventLog, Word wType, Word wCategory, int dwEventID, void * 
	lpUserSid, Word wNumStrings, int dwDataSize, void * lpStrings, void * lpRawData);

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE TLookupAccountName LookupAccountName;
extern PACKAGE TLookupAccountSid LookupAccountSid;
extern PACKAGE TLookupPrivilegeValue LookupPrivilegeValue;
extern PACKAGE TLookupPrivilegeName LookupPrivilegeName;
extern PACKAGE TAllocateAndInitializeSid AllocateAndInitializeSid;
extern PACKAGE TEqualSid EqualSid;
extern PACKAGE TBackupEventLog BackupEventLog;
extern PACKAGE TClearEventLog ClearEventLog;
extern PACKAGE TCloseEventLog CloseEventLog;
extern PACKAGE TDeregisterEventSource DeregisterEventSource;
extern PACKAGE TGetNumberOfEventLogRecords GetNumberOfEventLogRecords;
extern PACKAGE TGetOldestEventLogRecord GetOldestEventLogRecord;
extern PACKAGE TNotifyChangeEventLog NotifyChangeEventLog;
extern PACKAGE TOpenBackupEventLog OpenBackupEventLog;
extern PACKAGE TOpenEventLog OpenEventLog;
extern PACKAGE TReadEventLog ReadEventLog;
extern PACKAGE TRegisterEventSource RegisterEventSource;
extern PACKAGE TReportEvent ReportEvent;
extern PACKAGE bool __fastcall IsWindowsNt(void);
extern PACKAGE void __fastcall ErrorMessage(System::AnsiString AStr);
extern PACKAGE void * __fastcall StringToSomeChar(const System::AnsiString Source, void * Dest, int 
	DestSize);
extern PACKAGE System::AnsiString __fastcall SomeCharToString(void * AChar);

}	/* namespace Nt_vs_95 */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Nt_vs_95;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// NT_vs_95
