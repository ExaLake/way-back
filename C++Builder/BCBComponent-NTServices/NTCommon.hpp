// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'NTCommon.pas' rev: 3.00

#ifndef NTCommonHPP
#define NTCommonHPP
#include <DsgnIntf.hpp>
#include <NetApi32.hpp>
#include <BrowsReg.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ntcommon
{
//-- type declarations -------------------------------------------------------
typedef Set<char, 0, 255>  TCharSet;

typedef Byte TByteArray[2147483647];

typedef TByteArray *PByteArray;

typedef char TCharArray[2147483647];

typedef TCharArray *PCharArray;

typedef int TDWORDArray[536870911];

typedef TDWORDArray *PDWORDArray;

typedef System::AnsiString TMachineName;

class DELPHICLASS TNTPersistent;
class PASCALIMPLEMENTATION TNTPersistent : public Classes::TComponent 
{
	typedef Classes::TComponent inherited;
	
protected:
	System::AnsiString FMachineName;
	virtual void __fastcall SetMachineName(System::AnsiString AValue) = 0;
	virtual System::AnsiString __fastcall GetMachineName();
	bool __fastcall ProperState(void);
	__property System::AnsiString MachineName = {read=GetMachineName, write=SetMachineName};
	
public:
	System::AnsiString __fastcall GetPrimaryDomainServerName();
	Classes::TStringList* __fastcall GetServers(System::AnsiString AServerName);
public:
	/* TComponent.Create */ __fastcall virtual TNTPersistent(Classes::TComponent* AOwner) : Classes::TComponent(
		AOwner) { }
	/* TComponent.Destroy */ __fastcall virtual ~TNTPersistent(void) { }
	
};

typedef int NTSTATUS;

//-- var, const, procedure ---------------------------------------------------
#define cnst1970 (Word)(25569)
#define smallBufSize (Byte)(255)
#define readBufSize (Word)(16383)
#define shortBufSize (Byte)(127)
#define advapi32dll "advapi32.dll"
extern "C" BOOL __stdcall OpenProcessToken(int ProcessHandle, int DesiredAccess, int &TokenHandle);
extern PACKAGE void __fastcall ClearLogFile(void);
extern PACKAGE void __fastcall AddToLogFile(System::AnsiString S);
extern PACKAGE int __fastcall WordCount(const System::AnsiString S, const TCharSet &WordDelims);
extern PACKAGE System::AnsiString __fastcall ExtractWord(int N, const System::AnsiString S, const TCharSet 
	&WordDelims);
extern PACKAGE void __fastcall CreateException(void);
extern PACKAGE System::AnsiString __fastcall GetLastErrorString(int ErrorID);
extern PACKAGE void __fastcall LoadListFromNullSeparatedArray(char * Buf, int Len, Classes::TStrings* 
	List);
extern PACKAGE void __fastcall UnloadListToNullSeparatedArray(char * Buf, const int Buf_Size, int Len
	, Classes::TStrings* List);
extern PACKAGE char * __fastcall GetPointer(System::AnsiString &s);
extern PACKAGE System::AnsiString __fastcall FindRegistryLocation(HKEY ARootKey, System::AnsiString 
	ABranchName, System::AnsiString AKeyName);
extern PACKAGE System::AnsiString __fastcall GetNetApiErrorString(int ErrorID);
extern PACKAGE void __fastcall CreateNetApiException(int ACod);
extern PACKAGE void * __fastcall AllocSID(System::AnsiString MachineName, System::AnsiString UserName
	, System::AnsiString &RefDomain);
extern PACKAGE System::TDateTime __fastcall GetDateTimeFrom1970(int Seconds);
extern PACKAGE int __fastcall GetSecondsFrom1970(System::TDateTime ADate);
extern PACKAGE void __fastcall CreateWNetException(int ACod);
extern PACKAGE void __fastcall CreateLsaApiException(int ACod);
extern PACKAGE System::AnsiString __fastcall GetPrimaryDomainServerName();
extern PACKAGE bool __fastcall GetAcountNameBySid(System::AnsiString MachineName, void * SID, System::AnsiString 
	&AName, System::AnsiString &ADomain);
extern PACKAGE bool __fastcall IsPrivilageEnabled(System::AnsiString MachineName, System::AnsiString 
	PrivName);
extern PACKAGE bool __fastcall AddPrivilege(System::AnsiString MachineName, System::AnsiString PrivName
	);
extern PACKAGE Classes::TStringList* __fastcall GetProcessPrivilegeList(System::AnsiString MachineName
	);
extern PACKAGE System::AnsiString __fastcall GetLogonUserName();
extern PACKAGE void * __fastcall AllocEveryOneSid(void);
extern PACKAGE System::AnsiString __fastcall GetEveryOneName(System::AnsiString AMachine);
extern PACKAGE System::AnsiString __fastcall GetPrimaryDomainName();
extern PACKAGE System::AnsiString __fastcall GetFullName(System::AnsiString AReferencedDomainName, System::AnsiString 
	AName);

}	/* namespace Ntcommon */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ntcommon;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// NTCommon
