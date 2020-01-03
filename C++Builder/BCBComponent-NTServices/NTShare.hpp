// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'NTShare.pas' rev: 3.00

#ifndef NTShareHPP
#define NTShareHPP
#include <Security.hpp>
#include <AbstrSec.hpp>
#include <NT_vs_95.hpp>
#include <ObjList.hpp>
#include <NetApi32.hpp>
#include <DsgnIntf.hpp>
#include <NTCommon.hpp>
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

namespace Ntshare
{
//-- type declarations -------------------------------------------------------
typedef System::AnsiString TShareName;

enum TShareType { stUnknown, stDisk, stPrint, stDevice, stIPC };

enum TAccessType { actRead, actWrite, actCreate, actExec, actDelete, ActAtrib, actPerm, actFindFirst, 
	actGroup };

typedef Set<TAccessType, actRead, actGroup>  TAccessTypes;

enum TSecurityLevel { slShareLevel, slUserLevel, slUnknown };

enum TSessionFlag { sessUnknown, sessNone, sessGuest, sessNoEncryption };

class DELPHICLASS TSession;
class PASCALIMPLEMENTATION TSession : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	System::AnsiString FClientName;
	System::AnsiString FUserName;
	int FOpenResourses;
	System::TDateTime FSessionTime;
	System::TDateTime FIdleTime;
	TSessionFlag FUserFlags;
	System::AnsiString FClientType;
	System::AnsiString FTransport;
	
public:
	__property System::AnsiString ClientName = {read=FClientName};
	__property System::AnsiString UserName = {read=FUserName};
	__property int OpenResourses = {read=FOpenResourses, nodefault};
	__property System::TDateTime SessionTime = {read=FSessionTime};
	__property System::TDateTime IdleTime = {read=FIdleTime};
	__property TSessionFlag UserFlags = {read=FUserFlags, nodefault};
	__property System::AnsiString ClientType = {read=FClientType};
	__property System::AnsiString transport = {read=FTransport};
public:
	/* TPersistent.Destroy */ __fastcall virtual ~TSession(void) { }
	
public:
	/* TObject.Create */ __fastcall TSession(void) : Classes::TPersistent() { }
	
};

class DELPHICLASS TUsage;
class PASCALIMPLEMENTATION TUsage : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FResourceId;
	TAccessTypes FPermissions;
	int FNumLocks;
	System::AnsiString FPathName;
	System::AnsiString FUserName;
	
public:
	__property int ResourceId = {read=FResourceId, nodefault};
	__property TAccessTypes Permissions = {read=FPermissions, nodefault};
	__property int NumLocks = {read=FNumLocks, nodefault};
	__property System::AnsiString PathName = {read=FPathName};
	__property System::AnsiString UserName = {read=FUserName};
public:
	/* TPersistent.Destroy */ __fastcall virtual ~TUsage(void) { }
	
public:
	/* TObject.Create */ __fastcall TUsage(void) : Classes::TPersistent() { }
	
};

class DELPHICLASS TAbstractShareList;
class DELPHICLASS TNTShare;
class DELPHICLASS TUsageList;
class PASCALIMPLEMENTATION TAbstractShareList : public Objlist::TObjectList 
{
	typedef Objlist::TObjectList inherited;
	
public:
	TNTShare* Owner;
	__fastcall virtual TAbstractShareList(System::TObject* AOwner);
	virtual void __fastcall Clear(void);
public:
	/* TObjectList.Destroy */ __fastcall virtual ~TAbstractShareList(void) { }
	
};

class PASCALIMPLEMENTATION TUsageList : public Ntshare::TAbstractShareList 
{
	typedef Ntshare::TAbstractShareList inherited;
	
protected:
	TUsage* __fastcall GetItem(int AIndex);
	
public:
	virtual void __fastcall Delete(int Index);
	__property TUsage* Items[int AIndex] = {read=GetItem/*, default*/};
public:
	/* TAbstractShareList.Create */ __fastcall virtual TUsageList(System::TObject* AOwner) : Ntshare::TAbstractShareList(
		AOwner) { }
	
public:
	/* TObjectList.Destroy */ __fastcall virtual ~TUsageList(void) { }
	
};

class DELPHICLASS TSessionList;
class PASCALIMPLEMENTATION TSessionList : public Ntshare::TAbstractShareList 
{
	typedef Ntshare::TAbstractShareList inherited;
	
protected:
	TSession* __fastcall GetItem(int AIndex);
	
public:
	virtual void __fastcall Delete(int Index);
	__property TSession* Items[int AIndex] = {read=GetItem/*, default*/};
	virtual void __fastcall Clear(void) = 0;
public:
	/* TAbstractShareList.Create */ __fastcall virtual TSessionList(System::TObject* AOwner) : Ntshare::
		TAbstractShareList(AOwner) { }
	
public:
	/* TObjectList.Destroy */ __fastcall virtual ~TSessionList(void) { }
	
};

class DELPHICLASS TResourceList;
class DELPHICLASS TResourceItem;
class PASCALIMPLEMENTATION TResourceList : public Ntshare::TAbstractShareList 
{
	typedef Ntshare::TAbstractShareList inherited;
	
protected:
	TResourceItem* __fastcall GetItem(int AIndex);
	
public:
	virtual void __fastcall Delete(int Index);
	void __fastcall Add(System::AnsiString NetName, System::AnsiString Path, TShareType ShareType);
	__property TResourceItem* Items[int AIndex] = {read=GetItem/*, default*/};
public:
	/* TAbstractShareList.Create */ __fastcall virtual TResourceList(System::TObject* AOwner) : Ntshare::
		TAbstractShareList(AOwner) { }
	
public:
	/* TObjectList.Destroy */ __fastcall virtual ~TResourceList(void) { }
	
};

class DELPHICLASS TConnectionList;
class DELPHICLASS TConnection;
class PASCALIMPLEMENTATION TConnectionList : public Ntshare::TAbstractShareList 
{
	typedef Ntshare::TAbstractShareList inherited;
	
protected:
	TConnection* __fastcall GetItem(int AIndex);
	
public:
	virtual void __fastcall Delete(int Index);
	void __fastcall Add(System::AnsiString LocalName, System::AnsiString RemoteName, TShareType AType);
		
	void __fastcall AddEx(System::AnsiString LocalName, System::AnsiString RemoteName, TShareType AType
		, System::AnsiString Username, System::AnsiString Password);
	__property TConnection* Items[int AIndex] = {read=GetItem/*, default*/};
public:
	/* TAbstractShareList.Create */ __fastcall virtual TConnectionList(System::TObject* AOwner) : Ntshare::
		TAbstractShareList(AOwner) { }
	
public:
	/* TObjectList.Destroy */ __fastcall virtual ~TConnectionList(void) { }
	
};

class PASCALIMPLEMENTATION TNTShare : public Abstrsec::TNTAbstractSecurity 
{
	typedef Abstrsec::TNTAbstractSecurity inherited;
	
private:
	System::AnsiString FShareName;
	TShareType FShareType;
	System::AnsiString FShareComment;
	int FMaxUsers;
	int FCurrentUsers;
	System::AnsiString FPath;
	TUsageList* FUsages;
	TSessionList* FSessions;
	TResourceList* FResources;
	TConnectionList* FConnections;
	void __fastcall GetAccessibleValues(void);
	void __fastcall GetOtherValues(void);
	
protected:
	virtual void __fastcall SetMachineName(System::AnsiString AValue);
	void __fastcall SetShareName(System::AnsiString AValue);
	void __fastcall SetShareType(TShareType AValue);
	TShareType __fastcall GetShareType(void);
	void __fastcall SetShareComment(System::AnsiString AValue);
	System::AnsiString __fastcall GetShareComment();
	int __fastcall GetMaxUsers(void);
	void __fastcall SetMaxUsers(int AValue);
	int __fastcall GetCurrentUsers(void);
	void __fastcall SetCurrentUsers(int AValue);
	System::AnsiString __fastcall GetPath();
	void __fastcall SetPath(System::AnsiString AValue);
	TUsageList* __fastcall GetUsages(void);
	void __fastcall SetUsages(TUsageList* AValue);
	TSessionList* __fastcall GetSessions(void);
	void __fastcall SetSessions(TSessionList* AValue);
	TResourceList* __fastcall GetResources(void);
	void __fastcall SetResources(TResourceList* AValue);
	TSessionList* __fastcall GetSessionInfo(int ALevel);
	TResourceList* __fastcall GetResourceListOfLevel(System::AnsiString AMachineName, int ALevel);
	void __fastcall SetConnections(TConnectionList* AValue);
	TConnectionList* __fastcall GetConnections(void);
	virtual void __fastcall GetObjectSecurityDescriptor(int WhatToRead);
	virtual void __fastcall SetObjectSecurityDescriptor(int WhatToWrite);
	virtual int __fastcall DWORDToAccessDeniedMasks(int Avalue);
	virtual int __fastcall DWORDToAccessAllowedMasks(int Avalue);
	virtual int __fastcall DWORDToAccessAuditMasks(int Avalue);
	virtual int __fastcall DeniedAccessMasksToDWORD(int AValue);
	virtual int __fastcall AllowedAccessMasksToDWORD(int AValue);
	virtual int __fastcall AuditAccessMasksToDWORD(int AValue);
	
public:
	__fastcall virtual TNTShare(Classes::TComponent* AOwner);
	__fastcall virtual ~TNTShare(void);
	
__published:
	__property MachineName ;
	__property System::AnsiString ShareName = {read=FShareName, write=SetShareName};
	__property TShareType ShareType = {read=GetShareType, write=SetShareType, stored=false, nodefault};
		
	__property System::AnsiString ShareComment = {read=GetShareComment, write=SetShareComment, stored=false
		};
	__property int MaxUsers = {read=GetMaxUsers, write=SetMaxUsers, stored=false, nodefault};
	__property int CurrentUsers = {read=GetCurrentUsers, write=SetCurrentUsers, stored=false, nodefault
		};
	__property System::AnsiString Path = {read=GetPath, write=SetPath, stored=false};
	__property TUsageList* Usages = {read=GetUsages, write=SetUsages, stored=false};
	__property TSessionList* Sessions = {read=GetSessions, write=SetSessions, stored=false};
	__property TResourceList* Resources = {read=GetResources, write=SetResources, stored=false};
	__property TConnectionList* Connections = {read=GetConnections, write=SetConnections, stored=false}
		;
	__property AccessAllowed ;
	__property AccessDenied ;
};


class PASCALIMPLEMENTATION TResourceItem : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
protected:
	System::AnsiString FShareName;
	TShareType FShareType;
	System::AnsiString FShareComment;
	int FMaxUsers;
	int FCurrentUsers;
	System::AnsiString FPath;
	
public:
	__property System::AnsiString ShareName = {read=FShareName};
	__property TShareType ShareType = {read=FShareType, nodefault};
	__property System::AnsiString ShareComment = {read=FShareComment};
	__property int MaxUsers = {read=FMaxUsers, nodefault};
	__property int CurrentUsers = {read=FCurrentUsers, nodefault};
	__property System::AnsiString Path = {read=FPath};
public:
	/* TPersistent.Destroy */ __fastcall virtual ~TResourceItem(void) { }
	
public:
	/* TObject.Create */ __fastcall TResourceItem(void) : Classes::TPersistent() { }
	
};

class PASCALIMPLEMENTATION TConnection : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
protected:
	System::AnsiString FLocalName;
	System::AnsiString FRemoteName;
	System::AnsiString FUserName;
	
public:
	__property System::AnsiString LocalName = {read=FLocalName};
	__property System::AnsiString RemoteName = {read=FRemoteName};
	__property System::AnsiString UserName = {read=FUserName};
public:
	/* TPersistent.Destroy */ __fastcall virtual ~TConnection(void) { }
	
public:
	/* TObject.Create */ __fastcall TConnection(void) : Classes::TPersistent() { }
	
};

//-- var, const, procedure ---------------------------------------------------
extern PACKAGE System::AnsiString __fastcall ShareTypeToStr(TShareType AValue);
extern PACKAGE System::AnsiString __fastcall AccessTypesToStr(TAccessTypes AValue);
extern PACKAGE System::AnsiString __fastcall SessionFlagToStr(TSessionFlag AValue);

}	/* namespace Ntshare */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Ntshare;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// NTShare
