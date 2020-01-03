// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'RegSecur.pas' rev: 3.00

#ifndef RegSecurHPP
#define RegSecurHPP
#include <NTCommon.hpp>
#include <AbstrSec.hpp>
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

namespace Regsecur
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TNTRegSecurity;
class PASCALIMPLEMENTATION TNTRegSecurity : public Abstrsec::TNTAbstractSecurity 
{
	typedef Abstrsec::TNTAbstractSecurity inherited;
	
private:
	int FRootKey;
	System::AnsiString FCurrentPath;
	
protected:
	void __fastcall SetRootKey(int AValue);
	void __fastcall SetCurrentPath(System::AnsiString AValue);
	virtual void __fastcall SetMachineName(System::AnsiString AValue);
	virtual int __fastcall DWORDToAccessDeniedMasks(int Avalue);
	virtual int __fastcall DWORDToAccessAllowedMasks(int Avalue);
	virtual int __fastcall DWORDToAccessAuditMasks(int Avalue);
	virtual int __fastcall DeniedAccessMasksToDWORD(int AValue);
	virtual int __fastcall AllowedAccessMasksToDWORD(int AValue);
	virtual int __fastcall AuditAccessMasksToDWORD(int AValue);
	virtual void __fastcall GetObjectSecurityDescriptor(int WhatToRead);
	virtual void __fastcall SetObjectSecurityDescriptor(int WhatToWrite);
	
public:
	__fastcall virtual TNTRegSecurity(Classes::TComponent* AOwner);
	__fastcall virtual ~TNTRegSecurity(void);
	
__published:
	__property MachineName ;
	__property int RootKey = {read=FRootKey, write=SetRootKey, default=-2147483646};
	__property System::AnsiString CurrentPath = {read=FCurrentPath, write=SetCurrentPath};
	__property AccessAllowed ;
	__property AccessDenied ;
	__property SystemAudit ;
	__property System::AnsiString KeyOwner = {read=GetObjectOwner, write=SetObjectOwner, stored=false};
		
	__property ControlAccess ;
};

//-- var, const, procedure ---------------------------------------------------
#define kamQueryValue (Byte)(1)
#define kamSetValue (Byte)(2)
#define kamCreateSubKey (Byte)(4)
#define kamEnumSubKey (Byte)(8)
#define kamNotify (Byte)(16)
#define kamCreateLink (Byte)(32)
#define kamDelete (int)(65536)
#define kamWriteDAC (int)(262144)
#define kamWriteOwner (int)(524288)
#define kamReadControl (int)(131072)
#define kamFullControl (int)(0x80000000)
#define KEY_FULL_CONTROL (int)(983103)
#define cnst_HKEY_CLASSES_ROOT "HKEY_CLASSES_ROOT"
#define cnst_HKEY_CURRENT_USER "HKEY_CURRENT_USER"
#define cnst_HKEY_LOCAL_MACHINE "HKEY_LOCAL_MACHINE"
#define cnst_HKEY_USERS "HKEY_USERS"
#define cnst_HKEY_PERFORMANCE_DATA "HKEY_PERFORMANCE_DATA"
#define cnst_HKEY_CURRENT_CONFIG "HKEY_CURRENT_CONFIG"
#define cnst_HKEY_DYN_DATA "HKEY_DYN_DATA"
extern PACKAGE System::AnsiString __fastcall GetRootName(int AValue);
extern PACKAGE int __fastcall GetRootValue(System::AnsiString AValue);

}	/* namespace Regsecur */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Regsecur;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// RegSecur
