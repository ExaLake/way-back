// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EventLog.pas' rev: 3.00

#ifndef EventLogHPP
#define EventLogHPP
#include <BrowsReg.hpp>
#include <NTCommon.hpp>
#include <ObjList.hpp>
#include <Classes.hpp>
#include <SysUtils.hpp>
#include <Windows.hpp>
#include <SysInit.hpp>
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Eventlog
{
//-- type declarations -------------------------------------------------------
typedef System::AnsiString TSourceName;

enum TEventType { EVT_SUCCESS, EVT_ERROR, EVT_WARNING, EVT_INFORMATION, EVT_AUDIT_SUCCESS, EVT_AUDIT_FAILURE 
	};

class DELPHICLASS TWaitThread;
class DELPHICLASS TNTEventLog;
class DELPHICLASS TEventItem;
class PASCALIMPLEMENTATION TNTEventLog : public Ntcommon::TNTPersistent 
{
	typedef Ntcommon::TNTPersistent inherited;
	
private:
	bool FActive;
	int FHandle;
	System::AnsiString FSourceName;
	System::AnsiString FBackupFileName;
	Browsreg::TBrowseRegistry* FRegistry;
	TWaitThread* FWaitThread;
	int FWaitEvent;
	int FTerminateEvent;
	Classes::TNotifyEvent FOnChange;
	int FEventSourceHandle;
	Objlist::TObjectList* FEventObjects;
	bool FIncludeUserName;
	bool FLocalUserNotFound;
	void *FLocalUserSid;
	System::AnsiString __fastcall GetMessageFile(System::AnsiString ASourceName);
	void __fastcall LogChanged(void);
	System::AnsiString __fastcall ErrorMessage(TEventItem* EventItem);
	
protected:
	void __fastcall OpenEventLog(void);
	void __fastcall CloseEventLog(void);
	void __fastcall SetActive(bool AValue);
	int __fastcall GetCount(void);
	System::AnsiString __fastcall GetItems(int AIndex);
	virtual void __fastcall Loaded(void);
	void __fastcall RegisterEventSource(void);
	void __fastcall DeregisterEventSource(void);
	void __fastcall OpenBackupEventLog(void);
	void __fastcall CheckSourceName(void);
	TEventItem* __fastcall GetObjects(int AIndex);
	virtual void __fastcall SetMachineName(System::AnsiString AValue);
	void * __fastcall GetLocalUserSid(void);
	__property void * LocalUserSid = {read=GetLocalUserSid};
	
public:
	__fastcall virtual TNTEventLog(Classes::TComponent* AOwner);
	__fastcall virtual ~TNTEventLog(void);
	void __fastcall Clear(void);
	void __fastcall Add(TEventType EventType, System::AnsiString S);
	void __fastcall BackupEventLog(void);
	void __fastcall AddObject(TEventItem* AObject);
	__property int Handle = {read=FHandle, nodefault};
	__property int Count = {read=GetCount, nodefault};
	__property System::AnsiString Items[int AIndex] = {read=GetItems};
	__property TEventItem* Objects[int AIndex] = {read=GetObjects};
	
__published:
	__property MachineName ;
	__property bool Active = {read=FActive, write=SetActive, nodefault};
	__property System::AnsiString SourceName = {read=FSourceName, write=FSourceName};
	__property System::AnsiString BackupFileName = {read=FBackupFileName, write=FBackupFileName};
	__property bool IncludeUserName = {read=FIncludeUserName, write=FIncludeUserName, default=1};
	__property Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
};

class PASCALIMPLEMENTATION TWaitThread : public Classes::TThread 
{
	typedef Classes::TThread inherited;
	
protected:
	TNTEventLog* Owner;
	
public:
	virtual void __fastcall Execute(void);
public:
	/* TThread.Create */ __fastcall TWaitThread(bool CreateSuspended) : Classes::TThread(CreateSuspended
		) { }
	/* TThread.Destroy */ __fastcall virtual ~TWaitThread(void) { }
	
};

struct TEventLogRecord;
typedef TEventLogRecord *PEventLogRecord;

struct TEventLogRecord
{
	int Length;
	int Reserved;
	int RecordNumber;
	int TimeGenerated;
	int TimeWritten;
	int EventID;
	Word EventType;
	Word NumStrings;
	Word EventCategory;
	Word ReservedFlags;
	int ClosingRecordNumber;
	int StringOffset;
	int UserSidLength;
	int UserSidOffset;
	int DataLength;
	int DataOffset;
} ;

class PASCALIMPLEMENTATION TEventItem : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	TNTEventLog* FOwner;
	int FNumber;
	System::TDateTime FTimeGenerated;
	System::TDateTime FTimeWritten;
	int FEventID;
	TEventType FEventType;
	Classes::TStringList* FStrings;
	System::AnsiString FUserName;
	Word FEventCategory;
	System::AnsiString FSourceName;
	System::AnsiString FComputername;
	int FDataLength;
	void *FData;
	void *FSID;
	int FSidLength;
	void __fastcall Clear(void);
	void __fastcall Refresh(PEventLogRecord P);
	System::AnsiString __fastcall GetUserName();
	void __fastcall SetSID(void * ASID, int SIDSize);
	
public:
	__fastcall TEventItem(TNTEventLog* AOwner);
	__fastcall virtual ~TEventItem(void);
	virtual void __fastcall Assign(Classes::TPersistent* Source);
	void __fastcall SetData(void * AData, int DataSize);
	__property System::TDateTime TimeGenerated = {read=FTimeGenerated};
	__property System::TDateTime TimeWritten = {read=FTimeWritten};
	__property int EventID = {read=FEventID, write=FEventID, nodefault};
	__property TEventType EventType = {read=FEventType, write=FEventType, nodefault};
	__property Classes::TStringList* Strings = {read=FStrings};
	__property System::AnsiString UserName = {read=GetUserName};
	__property Word EventCategory = {read=FEventCategory, write=FEventCategory, nodefault};
	__property System::AnsiString SourceName = {read=FSourceName};
	__property System::AnsiString Computername = {read=FComputername};
	__property int DataLength = {read=FDataLength, nodefault};
	__property void * Data = {read=FData};
	__property int Number = {read=FNumber, nodefault};
};

//-- var, const, procedure ---------------------------------------------------
#define cnstEventLogLocation "SYSTEM\\CurrentControlSet\\Services\\EventLog\\"
extern "C" BOOL __stdcall ReportEvent(int hEventLog, Word wType, Word wCategory, int dwEventID, void * 
	lpUserSid, Word wNumStrings, int dwDataSize, void * lpStrings, void * lpRawData);
extern PACKAGE Word __fastcall EventTypeToWord(TEventType EventType);
extern PACKAGE TEventType __fastcall WordToEventType(Word AValue);
inline BOOL __stdcall ReportEvent(int hEventLog, Word wType, Word wCategory, int dwEventID, void * lpUserSid
	, Word wNumStrings, int dwDataSize, void * lpStrings, void * lpRawData)
{
	return ReportEventA(hEventLog, wType, wCategory, dwEventID, lpUserSid, wNumStrings, dwDataSize, lpStrings
		, lpRawData);
}


}	/* namespace Eventlog */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Eventlog;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// EventLog
