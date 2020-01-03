// Borland C++ Builder
// Copyright (c) 1995, 1998 by Borland International
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FilSecur.pas' rev: 3.00

#ifndef FilSecurHPP
#define FilSecurHPP
#include <AbstrSec.hpp>
#include <DsgnList.hpp>
#include <ObjList.hpp>
#include <Security.hpp>
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

namespace Filsecur
{
//-- type declarations -------------------------------------------------------
class DELPHICLASS TNTFileSecurity;
class PASCALIMPLEMENTATION TNTFileSecurity : public Abstrsec::TNTAbstractSecurity 
{
	typedef Abstrsec::TNTAbstractSecurity inherited;
	
private:
	System::AnsiString FFileName;
	System::AnsiString __fastcall GetFileDrive();
	System::AnsiString __fastcall GetFileSystem();
	Abstrsec::TDriveType __fastcall GetDriveType(void);
	void __fastcall SetFileSystem(System::AnsiString AValue);
	void __fastcall SetFileName(System::AnsiString AValue);
	
protected:
	__property System::AnsiString FileDrive = {read=GetFileDrive};
	virtual void __fastcall GetObjectSecurityDescriptor(int WhatToRead);
	virtual void __fastcall SetObjectSecurityDescriptor(int WhatToWrite);
	virtual int __fastcall DWORDToAccessDeniedMasks(int Avalue);
	virtual int __fastcall DWORDToAccessAllowedMasks(int Avalue);
	virtual int __fastcall DWORDToAccessAuditMasks(int Avalue);
	virtual int __fastcall DeniedAccessMasksToDWORD(int AValue);
	virtual int __fastcall AllowedAccessMasksToDWORD(int AValue);
	virtual int __fastcall AuditAccessMasksToDWORD(int AValue);
	virtual System::AnsiString __fastcall GetMachineName();
	
public:
	__property Abstrsec::TDriveType DriveType = {read=GetDriveType, nodefault};
	
__published:
	__property System::AnsiString FileName = {read=FFileName, write=SetFileName};
	__property System::AnsiString FileSystem = {read=GetFileSystem, write=SetFileSystem, stored=false};
		
	__property AccessAllowed ;
	__property AccessDenied ;
	__property SystemAudit ;
	__property System::AnsiString FileOwner = {read=GetObjectOwner, write=SetObjectOwner, stored=false}
		;
	__property ControlAccess ;
	__property ObjectOwner ;
public:
	/* TNTAbstractSecurity.Create */ __fastcall virtual TNTFileSecurity(Classes::TComponent* AOwner) : 
		Abstrsec::TNTAbstractSecurity(AOwner) { }
	/* TNTAbstractSecurity.Destroy */ __fastcall virtual ~TNTFileSecurity(void) { }
	
};

//-- var, const, procedure ---------------------------------------------------

}	/* namespace Filsecur */
#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using namespace Filsecur;
#endif
//-- end unit ----------------------------------------------------------------
#endif	// FilSecur
