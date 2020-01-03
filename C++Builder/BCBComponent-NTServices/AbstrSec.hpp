// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'AbstrSec.pas' rev: 3.00

#ifndef AbstrSecHPP
#define AbstrSecHPP
#include <NTCommon.hpp>
#include <Security.hpp>
#include <DsgnList.hpp>
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

namespace Abstrsec
{
//-- type declarations -------------------------------------------------------
enum TAceFlag { acfObjInherit, acfContainer, acfInheritOnly, acfNoPropogate, acfSuccAudit, acfFailAudit 
	};

typedef Set<TAceFlag, acfObjInherit, acfFailAudit>  TAceFlags;

enum TDriveType { dtUnknown, dtError, dtRemovable, dtFixed, dtRemote, dtCDROM, dtRamDisk };

class DELPHICLASS TAccessList;
class DELPHICLASS TNTAbstractSecurity;
class PASCALIMPLEMENTATION TNTAbstractSecurity : public Ntcommon::TNTPersistent 
{
	typedef Ntcommon::TNTPersistent inherited;
	
protected:
	HWND FPropertyEditor;
	TAccessList* FAccessAllowed;
	TAccessList* FAccessDenied;
	TAccessList* FSystemAudit;
	void *RelativeSID;
	void *AbsoluteSID;
	_ACL *pDacl;
	_ACL *pSacl;
	void *pOwner;
	void *pPrimaryGroup;
	System::AnsiString __fastcall GetObjectOwner();
	void __fastcall SetObjectOwner(System::AnsiString AValue);
	void __fastcall SetAccessAllowed(TAccessList* AValue);
	TAccessList* __fastcall GetAccessAllowed(void);
	void __fastcall SetAccessDenied(TAccessList* AValue);
	TAccessList* __fastcall GetAccessDenied(void);
	void __fastcall SetSystemAudit(TAccessList* AValue);
	TAccessList* __fastcall GetSystemAudit(void);
	virtual void __fastcall GetObjectSecurityDescriptor(int WhatToRead) = 0;
	virtual void __fastcall SetObjectSecurityDescriptor(int WhatToWrite) = 0;
	bool __fastcall GetControlAccess(void);
	void __fastcall SetControlAccess(bool AValue);
	TAccessList* __fastcall GetAccessList(TAccessList* List, int AType);
	TAccessList* __fastcall GetSystemList(TAccessList* List, int AType);
	void __fastcall SetAccessControlLists(int AType);
	void __fastcall SetSystemLists(void);
	virtual int __fastcall DWORDToAccessDeniedMasks(int Avalue) = 0;
	virtual int __fastcall DWORDToAccessAllowedMasks(int Avalue) = 0;
	virtual int __fastcall DWORDToAccessAuditMasks(int Avalue) = 0;
	virtual int __fastcall DeniedAccessMasksToDWORD(int AValue) = 0;
	virtual int __fastcall AllowedAccessMasksToDWORD(int AValue) = 0;
	virtual int __fastcall AuditAccessMasksToDWORD(int AValue) = 0;
	TAceFlags __fastcall DWORDToAceFlags(int Avalue);
	Byte __fastcall AceFlagsToByte(TAceFlags AValue);
	__property System::AnsiString ObjectOwner = {read=GetObjectOwner, write=SetObjectOwner, stored=false
		};
	__property bool ControlAccess = {read=GetControlAccess, write=SetControlAccess, stored=false, nodefault
		};
	
public:
	void __fastcall SetPropertyEditor(HWND AWnd);
	__fastcall virtual TNTAbstractSecurity(Classes::TComponent* AOwner);
	__fastcall virtual ~TNTAbstractSecurity(void);
	void __fastcall TakeOwnerShip(void);
	void __fastcall InitializeEveryOneSD(void);
	__property MachineName ;
	__property TAccessList* AccessAllowed = {read=GetAccessAllowed, write=SetAccessAllowed, stored=false
		};
	__property TAccessList* AccessDenied = {read=GetAccessDenied, write=SetAccessDenied, stored=false};
		
	__property TAccessList* SystemAudit = {read=GetSystemAudit, write=SetSystemAudit, stored=false};
};

class DELPHICLASS TAccessItem;
class PASCALIMPLEMENTATION TAccessList : public Dsgnlist::TDesignList 
{
	typedef Dsgnlist::TDesignList inherited;
	
private:
	TNTAbstractSecurity* FOwner;
	bool DoNotPerformAPI;
	TAccessItem* __fastcall GetItem(int AIndex);
	virtual void __fastcall WriteToDisk(void) = 0;
	DYNAMIC System::AnsiString __fastcall GetNamePath();
	
public:
	__fastcall virtual TAccessList(Classes::TComponent* AOwner);
	virtual void __fastcall Delete(int Index);
	virtual void __fastcall Clear(void);
	TAccessItem* __fastcall Add(System::AnsiString UserName, int AMask, TAceFlags AFlags);
	__property TAccessItem* Items[int AIndex] = {read=GetItem/*, default*/};
	__property TNTAbstractSecurity* Owner = {read=FOwner};
public:
	/* TDesignList.Destroy */ __fastcall virtual ~TAccessList(void) { }
	
};

class PASCALIMPLEMENTATION TAccessItem : public Classes::TPersistent 
{
	typedef Classes::TPersistent inherited;
	
private:
	int FMask;
	TAceFlags FFlags;
	System::AnsiString FUserName;
	TAccessList* FOwner;
	void __fastcall SetUserName(System::AnsiString AValue);
	void __fastcall SetMask(int AValue);
	void __fastcall SetFlags(TAceFlags AValue);
	
public:
	DYNAMIC System::AnsiString __fastcall GetNamePath();
	__fastcall TAccessItem(TAccessList* AOwner);
	__property TAccessList* Owner = {read=FOwner};
	
__published:
	__property System::AnsiString UserName = {read=FUserName, write=SetUserName};
	__property int Mask = {read=FMask, write=SetMask, nodefault};
	__property TAceFlags Flags = {read=FFlags, write=SetFlags, nodefault};
public:
	/* TPersistent.Destroy */ __fastcall virtual ~TAccessItem(void) { }
	
};

//-- var, const, procedure ---------------------------------------------------
#define famRead (Byte)(1)
#define famWrite (Byte)(2)
#define famExecute (Byte)(4)
#define famDelete (Byte)(8)
#define famPermissions (Byte)(16)
#define famOwnership (Byte)(32)
#define famFullControl (int)(0x80000000)
#define cnstAccessAllowed "AccessAllowed"
#define cnstAccessDenied "AccessDenied"
#define cnstSystemAudit "SystemAudit"

}	/* namespace Abstrsec */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Abstrsec;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// AbstrSec
